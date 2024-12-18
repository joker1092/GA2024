// 
//! \file   ynWindow.h
//! \brief  ���� / ���� �����ӿ�ũ ���. 
//! 
//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
//! \date  2003.11.04
//! \date  2010.08.20. Updated. VS08, VS10, Yena 1.01 ���� 
//! \date  2012.12.10. Updated. C++11 / GCC5 / VS12
//! \date  2015.10.20. Updated. C++11/14 / GCC6.1 / VS15 
//! \date  2016.12.27. Updated. Windows SDK 8.1/10.0.x (DX11/12)
//! \date  2018.03.05. Updated. C++17  / GCC11 / VS17
//! \date  2020.08.22. Updated. Windows 10 SDK 10.0.x (DX12.x)
//
#pragma once
#pragma warning(disable:4996)

///////////////////////////////////////////////////////////////////////////////
//
// �÷��� ��� �� ���̺귯�� ����.
//
///////////////////////////////////////////////////////////////////////////////
#include "windows.h"
#include "tchar.h"

#include "wrl.h"
using namespace Microsoft::WRL;

#include "map"
#include "chrono"
using namespace std::chrono;
#define TIME_MAX  milliseconds::max()
//#define TIME_MAX  9223372036854775807



//! \namespace	YENA::Window
//! \brief		���� / ���� ���ӽ����̽�
//! \details	���� ����, �޼��� ó�� �� �Ϲ����� ���� ��� ���� �Լ��� ��ũ�ΰ� ���ǵ˴ϴ�.\n
//! \note		������ �������� ���� Ŭ����ȭ ������ �ʾҽ��ϴ�. \n
//!				���� ����� �Ǵ� ���� ���� ȯ���� ��� ���� ��ü�� Ŭ������ �ʿ��ϸ�
//!				���� Ŭ����(e.g., Yena)���� ���� ��ü �����̳�(e.g., �迭)�� ����� ���� ��õ�մϴ�.
//! \ingroup	Engine
namespace YENA::Window
{

///////////////////////////////////////////////////////////////////////////////
//
// ���� �����ӿ�ũ : ������ �������� ���� �� Ŭ����ȭ.
//
///////////////////////////////////////////////////////////////////////////////

int  ynCreateWindow		(HWND& rhWnd, UINT width, UINT height, BOOL resize = TRUE);
void ynResizeWindow		(HWND hWnd, UINT NewWidth, UINT NewHeight);
int  ynMessagePump		();
void ynSetWindowTitle	(HWND hWnd, TCHAR* title);

LRESULT CALLBACK ynMsgProc(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (CALLBACK *LPAFXMSGPROC)(HWND, UINT, WPARAM, LPARAM);
//extern LRESULT (CALLBACK * yn_MsgProcExt)(HWND, UINT, WPARAM, LPARAM);
extern TCHAR*		yn_ClassName;
extern TCHAR*		yn_WindowName;
extern LPAFXMSGPROC yn_MsgProcExt;

//!���� ���α׷� ����
enum AFX_STATE {
	AFX_QUIT,			//!< ����/������
	AFX_RUNNING,		//!< ������
	AFX_SUSPEND,		//!< �����
	AFX_RESUME,			//!< �̾� ����
	AFX_HIDE,			//!< ���� (Iconic)
	AFX_RESTORE,		//!< ������
	AFX_LOSTDEVICE,		//!< ��ġ �ҽ�

	AFX_MAX,
};

#define ynChkState(st)  ( (st) == AFX_QUIT )
#define ynChkBreak(st)  if(ynChkState(st)) break;




///////////////////////////////////////////////////////////////////////////////
//
// ��Ÿ �ý��� ���� �Լ� �� ��ũ��.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef KEY_UP
//! Ű ���� �׽�Ʈ. 
#define KEY_UP(key)	    ((GetAsyncKeyState(key)&0x8001) == 0x8001)
#define KEY_DOWN(key)	((GetAsyncKeyState(key)&0x8000) == 0x8000)
#define ynKeyUp			KEY_UP
#define ynKeyDn			KEY_DOWN
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = nullptr; }
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff); (pBuff) = nullptr;	 }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff); (pBuff) = nullptr;  }
#define ynSafeRelease			SAFE_RELEASE
#define ynSafeDelete			SAFE_DELETE
#define ynSafeDelArry			SAFE_DELARRY

#define SAFE_CLEAR(Buff)	if(Buff){ ZeroMemory(&Buff, sizeof(Buff)); }
#define SAFE_ZEROMEM		SAFE_CLEAR
#define ynSafeClear			SAFE_CLEAR
#define ynSafeZeroMem		SAFE_ZEROMEM
#endif	//SAFE_RELEASE

#ifndef YES_
#define YES_	TRUE
#define NO_		FALSE
#endif

#ifndef ON
#define ON		TRUE
#define OFF		FALSE
#define ENABLE  TRUE
#define DISABLE	FALSE
#endif

#ifndef YN_OK
#define YN_OK	   0					//���� ����. Ư���� ���� ����.
#define YN_FAIL   -1					//���� �߻�.
#define YN_FAILED(v)   ((v) != YN_OK)	//���� üũ ��ũ��.
#endif

/*
#ifndef OK
#define OK    0							//�۾� ����. ���� ����.
#define FAIL -1							//�۾� ����. ��Ÿ ���� ����..
#define CHK_FAILED(v)  ((v) != OK)
#endif*/

#ifndef pure
#define pure	PURE 
//#define pure	=0 
#endif
 
#ifndef in
#define in			
#define out
#define inout
#endif

#define DEFAULT  0
//#define ynToStr(v)   #v
//#define ynPutValule(v)  printf(#v" = %d \n"), v)


#ifndef toKB
//�ް�����Ʈ ȯ��
//2���� ���� : 1 MB = 1,048,576 bytes (1024^2 = 2^20) 
//            1 GB = 1024^3 bytes (1 GiB)
#define toKB(a)  ((a)/1024)
#define toMB(a)  ((a)/1024/1024)		
#define toMBf(a) ((a)/1024/1024.0f)		
//#define toGB(a)  (toMB((a))/1024)		
//#define toGBf(a) (toMBf((a))/1024.0f)		
#define toGB(a)  (toMB((a))/1000)		//GB ǥ���� �������� ���� 10������ ó��.
#define toGBf(a) (toMBf((a))/1000.0f)		
#endif


} //end of namespace YENA::Window;


using namespace YENA::Window;



/*************** end of file : "ynWindow.h" ********************************/