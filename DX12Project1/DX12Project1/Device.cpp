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
const TCHAR* g_strFeatLv = _T("N/A");

int DXSetup(HWND hwnd)
{
    return 0;
}

void DXRelease()
{
}

HRESULT CreateDeviceSwapChain(HWND Hwnd)
{
    return E_NOTIMPL;
}

HRESULT CreateRenderTarget()
{
    return E_NOTIMPL;
}

void SetViewPort()
{
}

int CommandsCreate()
{
    return 0;
}

int CommandsReset()
{
    return 0;
}

int CommandsExecute()
{
    return 0;
}

void CommandsRelease()
{
}

int GPUSyncObjsCreate()
{
    return 0;
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
