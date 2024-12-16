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
