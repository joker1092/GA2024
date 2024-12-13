/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3/YENA : 2D/3D ������ ����.						                       // 
//                                                                         //
//  �� �� : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive  http://www.zero-g.kr					   //	
//  �ʱⰳ�� : 2003.12 - 2004.03.                                           //
//  ����ȯ�� : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008       //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0c(2007, November)                           //
//                  OpenGL 1.x / 2.x                                       //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  �׽�Ʈ ȯ�� : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                      Core2 w/Quad                                       //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6 Series                       //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9xxx Series.                //
//                             GeForce 2/4xx GTS Series.                   //
//                             GeForce 7xx GTX Series.                     //
//                             GeForce 2Way-SLI / 3Way-SLI		   	       //
//                OS - Windows 98 / 2K / XP / VISTA / Win7 x32:x64         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
// DirectX.h: DirectX SDK �ʼ� ���.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04. Update.
// 2017.01. Update. B3Yena / DX11.1 (Windows SDK 8.1)
// 2020.08. Update. B3Yena / DX12.x (Windows 10 SDK 10.18362)
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma warning(disable:4996)


///////////////////////////////////////////////////////////////////////////////
//
// �������� ǥ�� �÷��� ��� �� ���̺귯��
//
///////////////////////////////////////////////////////////////////////////////

#include "windows.h" 
//#include "tchar.h"  
//#include "stdio.h"

//Window Runtime C++ Template Library.
//����: https://docs.microsoft.com/en-us/cpp/cppcx/wrl/windows-runtime-cpp-template-library-wrl?view=vs-2019
#include "wrl.h"
using namespace Microsoft::WRL;
//GUID ���� ��� : IID_xxx ���� ���� DX ��� ���� �߰��ؾ� ��.
#include "initguid.h"   





///////////////////////////////////////////////////////////////////////////////
//
// DirectX ǥ�� ���̺귯��
//
///////////////////////////////////////////////////////////////////////////////
// < DirectX ������ ���� ���̺귯�� >
// DX9         : DirectX SDK 2002 Nov.
// DX10.x/DX11 : DirectX SDK 2010 June (DX ���� ���� ������ ����)
// DX11.X/DX12 : Windows SDK 8.x / 10.x (DX �� ���ԵǾ� ������)
// DX12.X      : Windows SDK 10.x       (DX �� ���ԵǾ� ������)

// DX ǥ�� ���
//#include "D3D11.h"				//DX ǥ�� ���. (DX 11.0)
//#include "D3D11_1.h"				//DX ǥ�� ���. (DX 11.1)
#include "D3D12.h"					//DX ǥ�� ���. (DX 12.0)
//#include "D3D12_1.h"				//DX ǥ�� ���. (DX 12.1)
#pragma comment(lib, "D3D12")		//DX ���̺귯�� �ε�.  D3D12.dll �ʿ�.

//DirectX Math : Dx ���� ���̺귯��
//#include "XNAMath.h"				//XNA Math ���̺귯��.(ver.2.0) DirectX SDK 2010 June. ����.
#include "DirectXMath.h"			//XNA Math ���̺귯��.(ver.3.0) VS2012 (Windows SDK 8) �̻�.
using namespace DirectX;

//DXGI : DirectX Graphics Infrastructure
//DX �� ������ �������� �ϵ���� ������ ���� ����� �����մϴ�.
//#include "DXGI.h"					//DXGI ���. (d3d12.h �� ���Ե�)
//#include "DXGI1_4.h"
#include "DXGI1_6.h"				//DXGIAdpater4 ��.
#pragma comment(lib, "dxgi")		//DXGI ���̺귯��. DXGI.dll �ʿ�.

//DX ���̴� ��� ���̺귯��.
#include "D3DCompiler.h"				//DX ���̴� �����Ϸ� ���.
#pragma comment(lib, "d3dcompiler")		//DX ���̴� �����Ϸ� ���̺귯��.  D3DCompiler.dll �ʿ�.



///////////////////////////////////////////////////////////////////////////////
//
// DirectX Ȯ�� ���̺귯�� : DirectX Extensions
//
// DX Ȯ�� ���̺귯�� �� ��ƿ��Ƽ ������.
// ���� ������Ʈ/�Ӽ��� �߰������� �ʿ��մϴ�.
// �� Ȯ�� ���̺귯�� ������ ����. 
//
///////////////////////////////////////////////////////////////////////////////

// �� DirectXTK  (ver. Aug.15, 2020)
// DX ��ƿ��Ƽ �� �Ϲ�ȭ ���̺귯�� ������. 
// DX ���� �ʿ��� ���� ��� Ŭ���� �� ���񽺸� �����մϴ�.
// ����1 :  DXTK/ReadMe.txt
// ����2 :  Yena/DXTK/DirecrtXTK ����.txt
// ���� : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
//
#include "DXTK.h"



// �� DirectXTex  (ver. February 9, 2018)
// DX �ؽ�ó ��ƿ��Ƽ �� Ȯ�� ���̺귯�� ������.  
// DX �ؽ�ó ���� �ʿ��� ���� ��� Ŭ���� �� ���񽺸� �����մϴ�.
// ����1 :  DXTex/ReadMe.txt
// ����2 :  Yena/DXTex/DirecrtXTex ����.txt
// ���� : https://blogs.msdn.microsoft.com/chuckw/2011/10/27/directxtex/
// 
//#include "DXTex.h"								//������Ʈ �Ӽ����� �ʿ�. DirectXTex ����.txt ����.

/*// ������Ʈ �Ӽ��������� ��������, ����ϴ� ��� 
#include "../../Yena/DXTex/Inc/DirectXTex.h"		//���� ������������ ������Ʈ ȣȯ���� ���� ����� ����.
#ifdef _DEBUG
#pragma comment(lib, "../Yena/DXTex/Lib/DirectXTexd.lib")
#else
#pragma comment(lib, "../Yena/DXTex/Lib/DirectXTex.lib")
#endif
*/


// �� DXErr  (ver. Nov, 2015)
// DirectX ���� ������ ó�� ���̺귯��
// HRESULT ���� ���ڿ��� ����մϴ�.
// ���� : https://blogs.msdn.microsoft.com/chuckw/2012/04/24/wheres-dxerr-lib/
//
#include "DXErr.h"


// �� D3DX Helper  (ver. Aug.13, 2020)
// D3D �ڿ����� ��� �Ϲ�ȭ �������̽���.
// D3DX12 Helper ���� �Բ� �����.
// ���� : https://docs.microsoft.com/en-us/windows/win32/direct3d12/helper-structures-and-functions-for-d3d12#in-this-section
// ����2: https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12
//
#include "D3DX12.h"			// DXHelper\D3DX12.h
//#include "D3DX12_1.h"		// DXHelper\D3DX12_1.h for DX12.1 --> Windows 10 SDK 10.0.19041 ���� ���ʿ�.


 
/****************** end of file "DirectX.h" *******************************/