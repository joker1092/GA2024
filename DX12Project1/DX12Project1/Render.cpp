#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"
#include "Shader.h"

TCHAR* g_WindowName = _T("DX12Project1");

//기하 데이터

//정점 구조체
struct VERTEX
{
	float x, y, z;
	float r, g, b, a;
};

//정점 버퍼
ID3D12Resource* g_pVB = nullptr;
D3D12_VERTEX_BUFFER_VIEW* g_pVBView = nullptr;

//입력 레이아웃
D3D12_INPUT_LAYOUT_DESC* g_pVBLayout = nullptr; //DX12


int ObjLoad();
void ObjRelease();
void ObjUpdate(float dtime=0);
void ObjDraw(float dtime=0);


//렌더링 상태 조절 데이터/함수

//전역 데이터들
//일시정지
BOOL g_bPause = FALSE;

//와이어 프레임
BOOL g_bWireFrame = FALSE;

//배경색
COLOR g_ClearColor = { 0.0f, 0.125f, 0.3f, 1 }; 

//렌더링 모드
enum RENDER_STATE
{
	RS_SOLID,
	RS_WIREFRM,

	RS_MAX
};

//그래픽스 파이프라인 상태객체
ID3D12PipelineState* g_pPSO[RS_MAX] = { };
int PSOCreate();
void PSORelease();

CONSTS g_Consts;
ID3D12Resource* g_pCB = nullptr;

COLANI g_ColAni;
ID3D12Resource* g_pCB2 = nullptr;



//게임 데이터 및 레더링 자원을 불러온다
int DataLoading()
{
	//데이터 로딩/생성 코드
	CommandsReset();

	//todo:...
	ShaderCreate();
	ObjLoad();
	PSOCreate();

	//로딩 완료
	CommandsExecute();
	GPUSync();

	return TRUE;
}

//게임 데이터 및 레더링 자원을 해재한다
void DataRelease()
{
	//todo:...
	ShaderRelease();
	ObjRelease();
	PSORelease();
}



//=============================================================================
//렌더링 오브젝트
int ObjLoad() {
	HRESULT hr = S_OK;

	VERTEX verts[] = {
		{-0.5f,-0.5f, 0.0f,	1,0,0,1},
		{ 0.0f, 0.5f, 0.0f,	0,1,0,1},
		{ 0.5f,-0.5f, 0.0f,	0,0,1,1}
	};

	//vertex buffer 생성
	hr = CreateVertexBuffer(g_pDevice,verts,sizeof(verts),sizeof(VERTEX), &g_pVB, &g_pVBView);
	if (FAILED(hr))
	{
		ynError(hr, _T("정점버퍼 생성 실패"));
		return hr;
	}

	//input layout 생성
	D3D12_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,	0},
		{"COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,	0}
	};
	CreateInputLayout(layout, ARRAYSIZE(layout), &g_pVBLayout);

	return YN_OK;
}

void ObjRelease() {
	SAFE_RELEASE(g_pVB);
	SAFE_DELETE(g_pVBView);
	InputLayoutRelease(g_pVBLayout);
}

void ObjUpdate(float dtime) {

	//update const
	static float r = 0;
	r += XM_PI / 2 * dtime;

	g_Consts.trans = 0.5f*sin(r);

	g_Consts.scale = 0.5f * abs(cosf(r)) + 0.5;

	g_Consts.rot = r;

	UpdateCB(g_pCB, &g_Consts, sizeof(CONSTS));
	//end update const

	//update const2
	static float r2 = 0;
	static DWORD frm = 0;
	r2 += XM_PI / 2 * dtime * 0.3f;
	if (r2>XM_PI/2)
	{
		r2 = 0;

		if (++frm >= 3)frm = 0;
	}

	g_ColAni.color = COLOR(sinf(r), cosf(r), 1 - (sinf(r) + cosf(r)), 1);
	g_ColAni.per = sinf(r2);
	g_ColAni.frm = frm;

	UpdateCB(g_pCB2, &g_ColAni, sizeof(COLANI));
	//end update const2

}


//오브젝트 그리기
void ObjDraw(float dtime) {

	ID3D12GraphicsCommandList* cmdList = g_pCommandList;

	//루트 시그니처 설정
	cmdList->SetGraphicsRootSignature(g_pRootSign);
	//루트 파라미터 설정
	cmdList->SetGraphicsRootConstantBufferView(0, g_pCB->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, g_pCB2->GetGPUVirtualAddress());

	//파이프라인 상태 설정
	cmdList->SetPipelineState(g_pCurrPSO);

	//정점 버퍼 설정
	cmdList->IASetVertexBuffers(0, 1, g_pVBView);

	//위상 기하구조 설정
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//그리기
	cmdList->DrawInstanced(3, 1, 0, 0);
}

//=============================================================================
//엔진 - 시스템 갱신
float EngineUpdate() {
	float dTime = GetEnginTime();

	if (IsKeyUp(VK_P)) g_bPause ^= TRUE;

	if (g_bWireFrame)
	{
		g_ClearColor = COLOR(0.2f, 0.2f, 0.2f, 1.0f);
		g_pCurrPSO = g_pPSO[RS_WIREFRM];
	}
	else {
		g_ClearColor = COLOR(0.0f, 0.125f, 0.3f, 1.0f);
		g_pCurrPSO = g_pPSO[RS_SOLID];
	}

	ShaderUpdate();

	return dTime;
}

//=============================================================================
//렌더링 파이프라인 운용 함수

//파이프라인 상태 객체 생성
int PSOCreate() {
	HRESULT hr = S_OK;

	//레스터라이즈 스테이지
	D3D12_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D12_FILL_MODE_SOLID;
	rd.CullMode = D3D12_CULL_MODE_NONE;
	//rd.FrontCounterClockwise = false;

	//블렌딩 스테이지
	D3D12_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = false;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//깊이-스텐실 스테이지
	D3D12_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = false;
	dsd.StencilEnable = false;

	//셰이더 상태
	D3D12_SHADER_BYTECODE vs = { g_pVS->GetBufferPointer(),g_pVS->GetBufferSize() };
	D3D12_SHADER_BYTECODE ps = { g_pPS->GetBufferPointer(),g_pPS->GetBufferSize() };
	//D3D12_SHADER_BYTECODE gs = todo:...


	//파이프라인 상태 객체 생성
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psd = {};
	psd.pRootSignature = g_pRootSign;
	psd.VS = vs;
	psd.PS = ps;
	//psd.GS = gs;
	//psd.streamOutput = {};
	psd.BlendState = bd;
	psd.SampleMask = UINT_MAX;
	psd.RasterizerState = rd;
	psd.DepthStencilState = dsd;
	psd.InputLayout = *g_pVBLayout;
	//psd.IBStripCutValue = 0;
	psd.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psd.NumRenderTargets = 1;
	psd.RTVFormats[0] = g_Mode.Format;
	//psd.DSVFormat = 0;
	psd.SampleDesc = { 1,0 };
	//psd.NodeMask = 0;
	//psd.CachedPSO = nullptr;
	//psd.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;


	//"Solid" 상태 객체
	ID3D12PipelineState* pPSO = nullptr;
	hr = g_pDevice->CreateGraphicsPipelineState(&psd, IID_PPV_ARGS(&pPSO));

	if (FAILED(hr))
	{
		ynError(hr, _T("그래픽 파이프라인 상태객체 생성 실패 : %s %s"), ToString(RS_SOLID),psd);
		return hr;
	}

	g_pPSO[RS_SOLID] = pPSO;

	//"WireFrame" 상태 객체
	rd.FillMode = D3D12_FILL_MODE_WIREFRAME;
	psd.RasterizerState = rd;
	hr = g_pDevice->CreateGraphicsPipelineState(&psd, IID_PPV_ARGS(&pPSO));
	if (FAILED(hr))
	{
		ynError(hr, _T("그래픽 파이프라인 상태객체 생성 실패 : %s"), ToString(RS_WIREFRM));
		return hr;
	}

	g_pPSO[RS_WIREFRM] = pPSO;

	g_pCurrPSO = g_pPSO[RS_SOLID];

	return YN_OK;

}

//상태객체 제거
void PSORelease() {
	for (int i = 0; i < RS_MAX; i++)
		SAFE_RELEASE(g_pPSO[i]);
}

//도움말 출력
void ShowInfo(float dTime)
{
	PutFPS(1, 1);

	static bool bShow = true;

	if (IsKeyUp(VK_F1)) bShow ^= true;

	if (!bShow)
	{
		//ynTextDraw(1,20, COLOR(1, 1, 0, 1), _T("[Help] F1"));
		return;
	}

	//topic
	{
		//int x = 300, y = 50;
		int x = g_Mode.Width/2 - 150, y = 1;
		COLOR col(1, 1, 1, 1);
		COLOR col2(1, 1, 0, 1);
		COLOR col3(0.6f, 0.6f, 0.0f, 1);
		COLOR col4(0.4f, 0.4f, 0.4f, 1);
		COLOR col5(0.8f, 0.8f, 0.8f, 1);
		ynTextDraw(x, y, col, _T("■ %s"), g_WindowName);

		y += 14;
		WCHAR* msg = _T(
			"과제.\n"
			"셰이더 와 상수 버퍼\n"
			"삼각형 그리기\n"
			"뷰포트 나눠서 그려보기\n"
		);
		ynTextDraw(x, y, col2, msg);

	}

	//시스템 정보
	{
		int x = 1, y = 14;
		COLOR col(0, 1, 0, 1);
		SystemInfo(x, y, col);
	}


	//추가 도움말..
	int x = 1, y = 150;
	COLOR col(1, 1, 1, 1);
	COLOR col2(1, 1, 0, 1);
	COLOR col3(1, 0.7f, 1, 1);
	COLOR col4(0.1f, 0.6f, 0.6f, 1);
	//COLOR col3(0.6f, 0.6f, 0, 1);
	y += 14;
	ynTextDraw(x, y += 14, col, _T("[렌더링 상태]"));
	ynTextDraw(x, y += 14, col2, _T("일시정지: P (%s)"), g_bPause ? _T("ON") : _T("OFF"));
	ynTextDraw(x, y += 14, col, _T("채우기: Space (%s)"), g_bWireFrame ? _T("WIRE") : _T("SOLID"));


	{
		COLOR col = g_bPause ? COLOR(0.4f, 0.4f, 0.4f, 1) : COLOR(0.9f, 0.9f, 0.9f, 1);
		y += 14;
		//y = g_Mode.Height - 14 * 5;
		ynTextDraw(x, y += 14, col, _T("[Timer]"));
		ynTextDraw(x, y += 14, col, _T("dTime = %.5f"), dTime);
	}

	y += 14;
	ynTextDraw(x, y += 14, col2, _T("[CB.0]"));
	ynTextDraw(x, y += 14, col3, _T("Trans = %.2f"), g_Consts.trans);
	ynTextDraw(x, y += 14, col3, _T("Scale = %.2f"), g_Consts.scale);
	ynTextDraw(x, y += 14, col3, _T("Rot   = %.2f"), g_Consts.rot);
	y += 14;
	ynTextDraw(x, y += 14, col2, _T("[CB.1]"));
	ynTextDraw(x, y += 14, col3, _T("Per   = %.2f%%"), g_ColAni.per);
	ynTextDraw(x, y += 14, col3, _T("Frm   = %d"), g_ColAni.frm);
	ynTextDraw(x, y += 14, col3, _T("Color = { %+.2f, %+.2f, %+.2f, %.2f }"), g_ColAni.color.x, g_ColAni.color.y, g_ColAni.color.z, g_ColAni.color.w);

}

//게임 장면 렌더링
void SceneRender()
{
	//===============================================================
	//엔진 / 시스템 갱신

	//렌더링 상태, 조명, 카메라 등 조절
	float dTime = EngineUpdate();

	//장면 갱신
	ObjUpdate(dTime);
	//===============================================================
	//장면 그리기
	//렌더타겟 지우기
	ClearBackBuffer(g_ClearColor);

	//장면 렌더링
	ObjDraw();

	//도움말 출력
	ShowInfo(dTime);

	//===============================================================
	//장면 그리기 종료
	Flip();
}
