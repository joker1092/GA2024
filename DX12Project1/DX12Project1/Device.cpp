#pragma warning(disable:4996)
#include "Device.h"

// DX 및 장치 관련 전역 데이터들 
// 
//D3D 장치 인터페이스
IDXGIAdapter4* g_pAdapter = NULL;
ID3D12Device* g_pDevice = NULL;

//D3D 스왑체인 인터페이스
IDXGISwapChain4* g_pSwapChain = NULL;

//다중버퍼링 운용 인터페이스들
const UINT g_RTCnt = 2;
UINT g_RTDescSize = 0;
UINT g_RTIndex = 0;
ID3D12DescriptorHeap* g_pRTDescHeap = NULL;
//D3D12_CPU_DESCRIPTOR_HANDLE g_RTDescs;
ID3D12Resource* g_pRT[g_RTCnt] = { NULL, };
#define g_BB g_pRT[g_RTIndex]
#define g_BackBuffer g_pBB
//#define g_RTViews g_pRTDesc

//명령어큐 인터페이스들
ID3D12CommandQueue*         g_pCommandQueue = NULL;
ID3D12CommandAllocator*     g_pCommandAllocator = NULL;
ID3D12GraphicsCommandList*  g_pCommandList = NULL;

//렌더링 동기화 인터페이스
ID3D12Fence* g_pFence = NULL;
UINT64 g_FenceValue = 0;
//UINT64 g_FenceValues[g_RTCnt] = { 0, };
//UINT g_FrameIndex = 0;
HANDLE g_FenceEvent = NULL;

//뷰포트
D3D12_VIEWPORT g_VP;

//장치 설정 기본 정보
DISPLAYMODE g_Mode = { 960,600,0,1,DXGI_FORMAT_R8G8B8A8_UNORM };

//AA & AF Option
DWORD g_dwAA = 1;
DWORD g_dwAF = 1;
BOOL g_bMipMap = TRUE;

//D3D 기능 레벨
D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_0; //DX12
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_1; //DX12.1
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_11_0; //DX11
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_9_3; //DX9.0c
TCHAR* g_strFeatLv = _T("N/A");

//장치 정보
//DXGI_ADAPTER_DESC1 g_Adc;

//전체화면 여부
BOOL g_bWindowMode = TRUE;

//수직동기화 여부
BOOL g_bVSync = FALSE;

//===============================================================
//D3D 장치 운용함수

//DX 및 관련 객체 초기화
int DXSetup(HWND hwnd)
{
	CreateDeviceSwapChain(hwnd);
	CreateRenderTarget();
	SetViewPort();

	//GetDeviceInfo();

    return YN_OK;
}

//장치 및 객체 제거
void DXRelease()
{
	GPUSyncObjsRelease();
	CommandsRelease();

    for (UINT i = 0; i < g_RTCnt; i++)
    {
        SAFE_RELEASE(g_pRT[i]);
    }

	SAFE_RELEASE(g_pRTDescHeap);
	SAFE_RELEASE(g_pSwapChain);

	SAFE_RELEASE(g_pDevice);
}

//D3D 장치 생성 및 스왑체인 생성
HRESULT CreateDeviceSwapChain(HWND Hwnd)
{
	HRESULT hr = S_OK;

    //DXGI 인터페이스 생성
	IDXGIFactory4* pFactory = nullptr;
	CreateDXGIFactory2(0, IID_PPV_ARGS(&pFactory));

    //DX 렌더링 장치 구성
    hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_pDevice));
    //hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device),(void**)&g_pDevice);
	//hr = D3D12CreateDevice(g_pAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), (void**)&g_pDevice);
    if (FAILED(hr)) 
    {
        ynError(hr, _T("디바이스 생성 실패."));
    }

	//커맨드 객체 생성
	CommandsCreate();

    //동기화 객체 생성
	GPUSyncObjsCreate();

    //다중 버퍼링 구성
    //스왑체인 정보 구성
    DXGI_SWAP_CHAIN_DESC1 sd = {};
    sd.Width = g_Mode.Width;                            //해상도
    sd.Height = g_Mode.Height;
    sd.Format = g_Mode.Format;                          //백버퍼 규격
    sd.SampleDesc.Count = g_dwAA;                       //AA설정
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //용도설정
    sd.BufferCount = g_RTCnt;                           //백버퍼 개수
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      //다중 버퍼링 (옵션)
    //sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;      //다중 버퍼링 (옵션)

    //스왑체인 생성
    IDXGISwapChain1* pSwapchain = nullptr;
    hr = pFactory->CreateSwapChainForHwnd(g_pCommadQueue, g_hWnd, &sd, nullptr, nullptr, &pSwapchain);
    if (FAILED(hr))
    {
        ynError(hr, _T("디바이스 / 스왑체인 / CreateSwapChainForHwnd 생성 실패""\nRes={%dx%d} RT=%d AA=%d \n"),
            g_Mode.Width,g_Mode.Height,g_RTCnt,g_dwAA);
    }

    //스왑체인 : 신규 인터페이스 획득.
    hr = pSwapchain->QueryInterface(IID_PPV_ARGS(&g_pSwapChain));
    if (FAILED(hr))
    {
        ynError(hr, _T("디바이스 / 스왑체인 생성 실패"));
    }

    //현재 프레임 "백버퍼"얻기
    g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

    //장치 추가
    //전체화면 방지
    pFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

    //임시 인터페이스 제거
    SAFE_RELEASE(pFactory);
    SAFE_RELEASE(pSwapchain);

    return hr;
}

//장치-스왑체인의 렌더타겟(백버퍼) 획득
HRESULT CreateRenderTarget()
{
    HRESULT hr = S_OK;

    //백버퍼 인덱스 얻기
    //UINT bbidx = g_pSwapChain->GetCurrentBackBufferIndex();

    //디스크립터-힙 구성
    D3D12_DESCRIPTOR_HEAP_DESC hd = {};
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hd.NumDescriptors = g_RTCnt;
    //hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    //hd.NodeMask = 0;
    hr = g_pDevice->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&g_pRTDescHeap));
    if (FAILED(hr))
    {
        ynError(hr, _T("백버퍼-렌더타겟 : 디스크립터-힙 생성 실패"));
        return hr;
    }

    //렌더타겟-뷰 생성
    g_RTDescSize = g_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE dh = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < g_RTCnt; i++) {
        hr = g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_pRT[i]));
        g_pDevice->CreateRenderTargetView(g_pRT[i], nullptr, dh);
        dh.ptr += g_RTDescSize;
    }

    if (FAILED(hr))
    {
        ynError(hr, _T("백버퍼-렌더타겟뷰 생성 실패"));
    }

    return hr;
}

//뷰포트 설정
void SetViewPort()
{
    D3D12_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width = (FLOAT)g_Mode.Width;
    vp.Height = (FLOAT)g_Mode.Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    //g_CmdList->RSSetViewports(1, &vp);
    g_VP = vp;
}

//===============================================================
//커맨드 객체 생성
int CommandsCreate()
{
    HRESULT hr = S_OK;

    D3D12_COMMAND_QUEUE_DESC qd = {};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qd.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	qd.NodeMask = 0;
	hr = g_pDevice->CreateCommandQueue(&qd, IID_PPV_ARGS(&g_pCommandQueue));
	hr = g_pDevice->CreateCommandAllocator(qd.Type, IID_PPV_ARGS(&g_pCommandAllocator));
	hr = g_pDevice->CreateCommandList(0, qd.Type, g_pCommandAllocator, nullptr, IID_PPV_ARGS(&g_pCommandList));
	g_pCommandList->Close();
	
    if (FAILED(hr))
    {
		ynError(hr, _T("커맨드 객체생성 실패"));
    }

    return YN_OK;
}

//명령어 객체 리셋
int CommandsReset()
{
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

	return YN_OK;
}

//명령어를 실행
int CommandsExecute()
{
	ID3D12CommandList* cmdLists[] = { g_CmdList, };
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	return YN_OK;
}

//명령어 객체 제거
void CommandsRelease()
{
	SAFE_RELEASE(g_pCommandQueue);
	SAFE_RELEASE(g_pCommandAllocator);
	SAFE_RELEASE(g_pCommandList);
}

//===============================================================
//GPU 동기화 / 병렬화 함수

//동기화 객체 생성
int GPUSyncObjsCreate()
{
	HRESULT hr = S_OK;

	//GPU측 동기화 객체 생성
	hr = g_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_pFence));
	g_FenceValue = 1;

	//CPU측 동기화 객체 생성
	g_FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (FAILED())
    {

    }

}

void GPUSyncObjsRelease()
{
}

int GPUSync()
{
    return 0;
}

int ClearBackBuffer(COLOR col)
{
    return 0;
}

int Flip()
{
    return 0;
}

float GetEngindTime()
{
    return 0.0f;
}

void PutFPS(int x, int y)
{
}

void GetDeviceInfo()
{
}

void GetFeatureLevel()
{
}

COLOR operator*(COLOR& lhs, float s)
{
    return COLOR();
}

int ynErrorW(TCHAR* file, UINT line, TCHAR* func, BOOL bMBox, HRESULT hr, TCHAR* msg, ...)
{
    return 0;
}
