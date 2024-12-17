#pragma warning(disable:4996)
#include "Device.h"

// DX �� ��ġ ���� ���� �����͵� 
// 
//D3D ��ġ �������̽�
IDXGIAdapter4* g_pAdapter = NULL;
ID3D12Device* g_pDevice = NULL;

//D3D ����ü�� �������̽�
IDXGISwapChain4* g_pSwapChain = NULL;

//���߹��۸� ��� �������̽���
const UINT g_RTCnt = 2;
UINT g_RTDescSize = 0;
UINT g_RTIndex = 0;
ID3D12DescriptorHeap* g_pRTDescHeap = NULL;
//D3D12_CPU_DESCRIPTOR_HANDLE g_RTDescs;
ID3D12Resource* g_pRT[g_RTCnt] = { NULL, };
#define g_BB g_pRT[g_RTIndex]
#define g_BackBuffer g_pBB
//#define g_RTViews g_pRTDesc

//��ɾ�ť �������̽���
ID3D12CommandQueue*         g_pCommandQueue = NULL;
ID3D12CommandAllocator*     g_pCommandAllocator = NULL;
ID3D12GraphicsCommandList*  g_pCommandList = NULL;

//������ ����ȭ �������̽�
ID3D12Fence* g_pFence = NULL;
UINT64 g_FenceValue = 0;
//UINT64 g_FenceValues[g_RTCnt] = { 0, };
//UINT g_FrameIndex = 0;
HANDLE g_FenceEvent = NULL;

//����Ʈ
D3D12_VIEWPORT g_VP;

//��ġ ���� �⺻ ����
DISPLAYMODE g_Mode = { 960,600,0,1,DXGI_FORMAT_R8G8B8A8_UNORM };

//AA & AF Option
DWORD g_dwAA = 1;
DWORD g_dwAF = 1;
BOOL g_bMipMap = TRUE;

//D3D ��� ����
D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_0; //DX12
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_12_1; //DX12.1
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_11_0; //DX11
//D3D_FEATURE_LEVEL g_FeatLv = D3D_FEATURE_LEVEL_9_3; //DX9.0c
TCHAR* g_strFeatLv = _T("N/A");

//��ġ ����
//DXGI_ADAPTER_DESC1 g_Adc;

//��üȭ�� ����
BOOL g_bWindowMode = TRUE;

//��������ȭ ����
BOOL g_bVSync = FALSE;

//===============================================================
//D3D ��ġ ����Լ�

//DX �� ���� ��ü �ʱ�ȭ
int DXSetup(HWND hwnd)
{
	CreateDeviceSwapChain(hwnd);
	CreateRenderTarget();
	SetViewPort();

	//GetDeviceInfo();

    return YN_OK;
}

//��ġ �� ��ü ����
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

//D3D ��ġ ���� �� ����ü�� ����
HRESULT CreateDeviceSwapChain(HWND Hwnd)
{
	HRESULT hr = S_OK;

    //DXGI �������̽� ����
	IDXGIFactory4* pFactory = nullptr;
	CreateDXGIFactory2(0, IID_PPV_ARGS(&pFactory));

    //DX ������ ��ġ ����
    hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&g_pDevice));
    //hr = D3D12CreateDevice(0, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device),(void**)&g_pDevice);
	//hr = D3D12CreateDevice(g_pAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), (void**)&g_pDevice);
    if (FAILED(hr)) 
    {
        ynError(hr, _T("����̽� ���� ����."));
    }

	//Ŀ�ǵ� ��ü ����
	CommandsCreate();

    //����ȭ ��ü ����
	GPUSyncObjsCreate();

    //���� ���۸� ����
    //����ü�� ���� ����
    DXGI_SWAP_CHAIN_DESC1 sd = {};
    sd.Width = g_Mode.Width;                            //�ػ�
    sd.Height = g_Mode.Height;
    sd.Format = g_Mode.Format;                          //����� �԰�
    sd.SampleDesc.Count = g_dwAA;                       //AA����
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   //�뵵����
    sd.BufferCount = g_RTCnt;                           //����� ����
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;      //���� ���۸� (�ɼ�)
    //sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;      //���� ���۸� (�ɼ�)

    //����ü�� ����
    IDXGISwapChain1* pSwapchain = nullptr;
    hr = pFactory->CreateSwapChainForHwnd(g_pCommadQueue, g_hWnd, &sd, nullptr, nullptr, &pSwapchain);
    if (FAILED(hr))
    {
        ynError(hr, _T("����̽� / ����ü�� / CreateSwapChainForHwnd ���� ����""\nRes={%dx%d} RT=%d AA=%d \n"),
            g_Mode.Width,g_Mode.Height,g_RTCnt,g_dwAA);
    }

    //����ü�� : �ű� �������̽� ȹ��.
    hr = pSwapchain->QueryInterface(IID_PPV_ARGS(&g_pSwapChain));
    if (FAILED(hr))
    {
        ynError(hr, _T("����̽� / ����ü�� ���� ����"));
    }

    //���� ������ "�����"���
    g_RTIndex = g_pSwapChain->GetCurrentBackBufferIndex();

    //��ġ �߰�
    //��üȭ�� ����
    pFactory->MakeWindowAssociation(g_hWnd, DXGI_MWA_NO_ALT_ENTER);

    //�ӽ� �������̽� ����
    SAFE_RELEASE(pFactory);
    SAFE_RELEASE(pSwapchain);

    return hr;
}

//��ġ-����ü���� ����Ÿ��(�����) ȹ��
HRESULT CreateRenderTarget()
{
    HRESULT hr = S_OK;

    //����� �ε��� ���
    //UINT bbidx = g_pSwapChain->GetCurrentBackBufferIndex();

    //��ũ����-�� ����
    D3D12_DESCRIPTOR_HEAP_DESC hd = {};
    hd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    hd.NumDescriptors = g_RTCnt;
    //hd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    //hd.NodeMask = 0;
    hr = g_pDevice->CreateDescriptorHeap(&hd, IID_PPV_ARGS(&g_pRTDescHeap));
    if (FAILED(hr))
    {
        ynError(hr, _T("�����-����Ÿ�� : ��ũ����-�� ���� ����"));
        return hr;
    }

    //����Ÿ��-�� ����
    g_RTDescSize = g_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE dh = g_pRTDescHeap->GetCPUDescriptorHandleForHeapStart();
    for (UINT i = 0; i < g_RTCnt; i++) {
        hr = g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_pRT[i]));
        g_pDevice->CreateRenderTargetView(g_pRT[i], nullptr, dh);
        dh.ptr += g_RTDescSize;
    }

    if (FAILED(hr))
    {
        ynError(hr, _T("�����-����Ÿ�ٺ� ���� ����"));
    }

    return hr;
}

//����Ʈ ����
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
//Ŀ�ǵ� ��ü ����
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
		ynError(hr, _T("Ŀ�ǵ� ��ü���� ����"));
    }

    return YN_OK;
}

//��ɾ� ��ü ����
int CommandsReset()
{
	g_CmdAlloc->Reset();
	g_CmdList->Reset(g_CmdAlloc, nullptr);

	return YN_OK;
}

//��ɾ ����
int CommandsExecute()
{
	ID3D12CommandList* cmdLists[] = { g_CmdList, };
	g_CmdList->Close();
	g_CmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	return YN_OK;
}

//��ɾ� ��ü ����
void CommandsRelease()
{
	SAFE_RELEASE(g_pCommandQueue);
	SAFE_RELEASE(g_pCommandAllocator);
	SAFE_RELEASE(g_pCommandList);
}

//===============================================================
//GPU ����ȭ / ����ȭ �Լ�

//����ȭ ��ü ����
int GPUSyncObjsCreate()
{
	HRESULT hr = S_OK;

	//GPU�� ����ȭ ��ü ����
	hr = g_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_pFence));
	g_FenceValue = 1;

	//CPU�� ����ȭ ��ü ����
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
