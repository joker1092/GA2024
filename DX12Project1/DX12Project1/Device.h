#pragma once
#pragma warning(disable:4996)
#include "Windows.h"
#include "tchar.h"
#include "stdio.h"

#include <memory>
#include <chrono>

using namespace std::chrono;

#define TIME_MAX 9223372056854775807 //std::chrono::millseconds::max()

//Window Runtime C++ Template Library
#include "wrl.h"
using namespace Microsoft::WRL;


//#ifndef in
//#define in
//#define out
//#define inout
//#endif // !in


#include "D3D12.h"
//#include "D3D12_1.h"
#pragma comment(lib,"D3D12")

#include "DirectXMath.h"
using namespace DirectX;

#include <dxgi1_4.h>
#include <dxgi1_6.h>
#pragma comment(lib,"dxgi")

//DirectX Tool Kit
#include "DXTK.h"


//DX타입과 상수 재정의 ==> 버전별 호환성 목적
//장치관련
typedef ID3D12Device*	LPDEVICE;

//math 타입
typedef XMMATRIX	MATRIXA;
typedef XMFLOAT4X4	MATRIX;
typedef XMVECTOR	VECTOR;
typedef XMFLOAT4	VECTOR4;
typedef XMFLOAT3	VECTOR3;
typedef XMFLOAT2	VECTOR2;

//색상
typedef XMFLOAT4	COLOR;

//DX 및 장치 관련 함수 및 데이터

int DXSetup(HWND hwnd);
void DXRelease();

HRESULT CreateDeviceSwapChain(HWND Hwnd);
HRESULT CreateRenderTarget();
void SetViewPort();

int CommandsCreate();
int CommandsReset();
int CommandsExecute();
void CommandsRelease();

int GPUSyncObjsCreate();
void GPUSyncObjsRelease();
int GPUSync();

int Clear();
int ClearBackBuffer(COLOR col);
int ClearBackBuffer(UINT flag,COLOR col, float depth = 1.0f,UINT stencill = 0);
int Flip();
//int wait();

float GetEngindTime();
void PutFPS(int x, int y);

void GetDeviceInfo();
HRESULT GetAdapterInfo(DXGI_ADAPTER_DESC1* pAd);
//void SystemUpdate(float dTime);
void SystemInfo(int x,int y,COLOR col);

void GetFeatureLevel();
//int GetFeatureAA(LPDEVICE pDev,DXGI_FORMAT fmt,DWORD dwAA);

extern ID3D12Device* g_pDevice;
extern IDXGISwapChain4* g_pSwapChain;
//extern ID3D12RenderTargetView g_pRTView;
extern ID3D12CommandQueue* g_pCommandQueue;
extern ID3D12CommandAllocator* g_pCommandAllocator;
extern ID3D12GraphicsCommandList* g_pCommandList;
//#define g_dxCmd g_pCommandList
#define g_CmdQueue g_pCommandQueue
#define g_CmdList g_pCommandList
#define g_CmdAlloc g_pCommandAllocator

//extern D3D12_CPU_DESCRIPTOR_HANDLE g_CpuDesc;

//장치 설정 정보 구조체
typedef DXGI_MODE_DESC DISPLAYMODE; //DX11/12
//typedef D3DDISPLAYMODE DISPLAYMODE; //DX9

extern DISPLAYMODE g_Mode;
extern HWND g_hWnd;
extern BOOL g_bShowFrame;

extern BOOL g_bWindowMode;
extern BOOL g_bVsync;
extern TCHAR* g_strFeatLv;

//기타 시스템 관련 함수 및 재정의

#ifndef _YNGLOBAL
#define _YNGLOBAL  __declspec(selectany)
#define _YNGLOBALCONST extern const __declspec(selectany)
#define GLOBALCONST _YNGLOBALCONST
#endif // !_YNGLOBAL

//타겟 플렛폼 디버깅 표시용
GLOBALCONST TCHAR* g_Platform =
#ifdef _WIN64
_T("x64");
#elif _WIN32
_T("x86");
#endif


//비동기 키보드 입력 처리
#ifndef IsKeyDown
#define IsKeyDown(key)	 ((GetAsyncKeyState(key) & 0x8000) == 0x8000)
#define IsKeyUp(key)	((GetAsyncKeyState(key) & 0x8001) == 0x0001)
#endif // !IsKeyDown

//메모리	해제
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#define SAFE_DELETE(pBuff) if((pBuff)){ delete (pBuff); (pBuff) = NULL; }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = NULL; }
#endif // !SAFE_RELEASE


//플레그	정의
#ifndef YES_
#define YES_ TRUE
#define NO_ FALSE
#endif // !YES_


//에러체크
#ifndef YN_OK
#define YN_OK 0
#define YN_FAIL -1
#define YN_FAILED(v) ((v)!= YN_OK_)
#endif // !YN_OK

//바이트 환산
#ifndef toKB
#define toKB(a) ((a)/1024)
#define toMB(a) ((a)/1024/1024)
#define toMBf(a) ((a)/1024/1024.0f)
//#define toGB(a) (toMB(a)/1024)
//#define toGBf(a) (toMBf(a)/1024.0f)
#define toGB(a) (toMB(a)/1000)
#define toGBf(a) (toMBf(a)/1000.0f)

#define toLU(a) (a)##LU
#endif // !toKB






//색상*스칼라 곱
COLOR operator*(COLOR & lhs, float s);

//에러 출력 함수
int ynErrorW(TCHAR * file, UINT line, TCHAR * func, BOOL bMBox, HRESULT hr, TCHAR * msg, ...);

#define ynError(hr,msg,...)	\
ynErrorW(__FILEW__,__LINE__,__FUNCTIONW__,TRUE,hr,msg,__VA_ARGS__)

#define ToStromg(v) #v

//=============================================================================
//폰트 엔진 : 일반 함수 버전
int ynFontCreate(LPDEVICE pDev);
void ynFontRelease();
void ynTextDraw(int x, int y, COLOR col, TCHAR* msg, ...);