#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"
#include "Shader.h"

TCHAR* g_WindowName = _T("DX12Project1");

//���� ������

//���� ����ü
struct VERTEX
{
	float x, y, z;
	float r, g, b, a;
};

//���� ����
ID3D12Resource* g_pVB = nullptr;
D3D12_VERTEX_BUFFER_VIEW* g_pVBView = nullptr;

//�Է� ���̾ƿ�
D3D12_INPUT_LAYOUT_DESC* g_pVBLayout = nullptr; //DX12


int ObjLoad();
void ObjRelease();
void ObjUpdate(float dtime=0);
void ObjDraw(float dtime=0);


//������ ���� ���� ������/�Լ�

//���� �����͵�
//�Ͻ�����
BOOL g_bPause = FALSE;

//���̾� ������
BOOL g_bWireFrame = FALSE;

//����
COLOR g_ClearColor = { 0.0f, 0.125f, 0.3f, 1 }; 

//������ ���
enum RENDER_STATE
{
	RS_SOLID,
	RS_WIREFRM,

	RS_MAX
};

//�׷��Ƚ� ���������� ���°�ü
ID3D12PipelineState* g_pPSO[RS_MAX] = { };
int PSOCreate();
void PSORelease();

CONSTS g_Consts;
ID3D12Resource* g_pCB = nullptr;

COLANI g_ColAni;
ID3D12Resource* g_pCB2 = nullptr;



//���� ������ �� ������ �ڿ��� �ҷ��´�
int DataLoading()
{
	//������ �ε�/���� �ڵ�
	CommandsReset();

	//todo:...
	ShaderCreate();
	ObjLoad();
	PSOCreate();

	//�ε� �Ϸ�
	CommandsExecute();
	GPUSync();

	return TRUE;
}

//���� ������ �� ������ �ڿ��� �����Ѵ�
void DataRelease()
{
	//todo:...
	ShaderRelease();
	ObjRelease();
	PSORelease();
}



//=============================================================================
//������ ������Ʈ
int ObjLoad() {
	HRESULT hr = S_OK;

	VERTEX verts[] = {
		{-0.5f,-0.5f, 0.0f,	1,0,0,1},
		{ 0.0f, 0.5f, 0.0f,	0,1,0,1},
		{ 0.5f,-0.5f, 0.0f,	0,0,1,1}
	};

	//vertex buffer ����
	hr = CreateVertexBuffer(g_pDevice,verts,sizeof(verts),sizeof(VERTEX), &g_pVB, &g_pVBView);
	if (FAILED(hr))
	{
		ynError(hr, _T("�������� ���� ����"));
		return hr;
	}

	//input layout ����
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


//������Ʈ �׸���
void ObjDraw(float dtime) {

	ID3D12GraphicsCommandList* cmdList = g_pCommandList;

	//��Ʈ �ñ״�ó ����
	cmdList->SetGraphicsRootSignature(g_pRootSign);
	//��Ʈ �Ķ���� ����
	cmdList->SetGraphicsRootConstantBufferView(0, g_pCB->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, g_pCB2->GetGPUVirtualAddress());

	//���������� ���� ����
	cmdList->SetPipelineState(g_pCurrPSO);

	//���� ���� ����
	cmdList->IASetVertexBuffers(0, 1, g_pVBView);

	//���� ���ϱ��� ����
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�׸���
	cmdList->DrawInstanced(3, 1, 0, 0);
}

//=============================================================================
//���� - �ý��� ����
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
//������ ���������� ��� �Լ�

//���������� ���� ��ü ����
int PSOCreate() {
	HRESULT hr = S_OK;

	//�����Ͷ����� ��������
	D3D12_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D12_FILL_MODE_SOLID;
	rd.CullMode = D3D12_CULL_MODE_NONE;
	//rd.FrontCounterClockwise = false;

	//���� ��������
	D3D12_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = false;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//����-���ٽ� ��������
	D3D12_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = false;
	dsd.StencilEnable = false;

	//���̴� ����
	D3D12_SHADER_BYTECODE vs = { g_pVS->GetBufferPointer(),g_pVS->GetBufferSize() };
	D3D12_SHADER_BYTECODE ps = { g_pPS->GetBufferPointer(),g_pPS->GetBufferSize() };
	//D3D12_SHADER_BYTECODE gs = todo:...


	//���������� ���� ��ü ����
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


	//"Solid" ���� ��ü
	ID3D12PipelineState* pPSO = nullptr;
	hr = g_pDevice->CreateGraphicsPipelineState(&psd, IID_PPV_ARGS(&pPSO));

	if (FAILED(hr))
	{
		ynError(hr, _T("�׷��� ���������� ���°�ü ���� ���� : %s %s"), ToString(RS_SOLID),psd);
		return hr;
	}

	g_pPSO[RS_SOLID] = pPSO;

	//"WireFrame" ���� ��ü
	rd.FillMode = D3D12_FILL_MODE_WIREFRAME;
	psd.RasterizerState = rd;
	hr = g_pDevice->CreateGraphicsPipelineState(&psd, IID_PPV_ARGS(&pPSO));
	if (FAILED(hr))
	{
		ynError(hr, _T("�׷��� ���������� ���°�ü ���� ���� : %s"), ToString(RS_WIREFRM));
		return hr;
	}

	g_pPSO[RS_WIREFRM] = pPSO;

	g_pCurrPSO = g_pPSO[RS_SOLID];

	return YN_OK;

}

//���°�ü ����
void PSORelease() {
	for (int i = 0; i < RS_MAX; i++)
		SAFE_RELEASE(g_pPSO[i]);
}

//���� ���
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
		ynTextDraw(x, y, col, _T("�� %s"), g_WindowName);

		y += 14;
		WCHAR* msg = _T(
			"����.\n"
			"���̴� �� ��� ����\n"
			"�ﰢ�� �׸���\n"
			"����Ʈ ������ �׷�����\n"
		);
		ynTextDraw(x, y, col2, msg);

	}

	//�ý��� ����
	{
		int x = 1, y = 14;
		COLOR col(0, 1, 0, 1);
		SystemInfo(x, y, col);
	}


	//�߰� ����..
	int x = 1, y = 150;
	COLOR col(1, 1, 1, 1);
	COLOR col2(1, 1, 0, 1);
	COLOR col3(1, 0.7f, 1, 1);
	COLOR col4(0.1f, 0.6f, 0.6f, 1);
	//COLOR col3(0.6f, 0.6f, 0, 1);
	y += 14;
	ynTextDraw(x, y += 14, col, _T("[������ ����]"));
	ynTextDraw(x, y += 14, col2, _T("�Ͻ�����: P (%s)"), g_bPause ? _T("ON") : _T("OFF"));
	ynTextDraw(x, y += 14, col, _T("ä���: Space (%s)"), g_bWireFrame ? _T("WIRE") : _T("SOLID"));


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

//���� ��� ������
void SceneRender()
{
	//===============================================================
	//���� / �ý��� ����

	//������ ����, ����, ī�޶� �� ����
	float dTime = EngineUpdate();

	//��� ����
	ObjUpdate(dTime);
	//===============================================================
	//��� �׸���
	//����Ÿ�� �����
	ClearBackBuffer(g_ClearColor);

	//��� ������
	ObjDraw();

	//���� ���
	ShowInfo(dTime);

	//===============================================================
	//��� �׸��� ����
	Flip();
}
