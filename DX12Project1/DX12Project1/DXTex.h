//
// DirectXTex.h : DirectX Texture Library ���
//
// DirectX Texture Library : DX11 ( Dec.13, 2017) 
// ���� Present : Chuck Walbourn @ Microsoft / MSFT (http://blogs.msdn.com/b/chuckw/)
// ���� Edit    : Kihong Kim / onlysonim@gmail.com 
// ���� Update  : 2017.12.03
//
#pragma once
#pragma warning(disable:4996)

// Platform Header �� Library
//
#include "Windows.h"
#include "stdio.h"

/*
///////////////////////////////////////////////////////////////////////////////
//
// DirectX ǥ�� ���̺귯�� 
//
///////////////////////////////////////////////////////////////////////////////
// < DirectX ������ ���� ���̺귯�� >
// DX9         : DirectX SDK 2002 Nov.
// DX10.x/DX11 : DirectX SDK 2010 June (DX ���� ���� ������ ����)
// DX11.X/DX12 : Windows SDK 8.x  (DX �� ���ԵǾ� ������)

// DX ǥ�� ���
#include "D3D11.h"					//DX ǥ�� ���. (DX 11.0)
//#include "D3D11_1.h"				//DX ǥ�� ���. (DX 11.1)
#pragma comment(lib, "D3D11")		//DX ���̺귯�� �ε�.  D3D11.dll �ʿ�.

//DirectX Math : Dx ���� ���̺귯��
//#include "XNAMath.h"				//XNA Math ���̺귯��.(ver.2.0) DirectX SDK 2010 June. ����.
#include "DirectXMath.h"			//XNA Math ���̺귯��.(ver.3.0) VS2012 (Windows SDK 8) �̻�.
using namespace DirectX;

//DXGI : DirectX Graphics Infrastructure
//DX �� ������ �������� �ϵ���� ������ ���� ����� �����մϴ�.
//#include "DXGI.h"					//DXGI ���. (d3d11.h �� ���Ե�)
#pragma comment(lib, "dxgi")		//DXGI ���̺귯��. DXGI.dll �ʿ�.

//DX ���̴� ��� ���̺귯��.
#include "D3DCompiler.h"				//DX ���̴� �����Ϸ� ���.
#pragma comment(lib, "d3dcompiler")		//DX ���̴� �����Ϸ� ���̺귯��.  D3DCompiler.dll �ʿ�.
*/


///////////////////////////////////////////////////////////////////////////////
//
// DirectX �ؽ�ó ���̺귯�� 
//
///////////////////////////////////////////////////////////////////////////////
//
// DX �ؽ�ó ��ƿ��Ƽ �� �Ϲ�ȭ ���̺귯�� ������. 
// DX �ؽ�ó ���� �ʿ��� ���� ��� Ŭ���� �� ���񽺸� �����մϴ�.
// �Ϲ����� �̹��� ����(JPG, BMP, PNG ��..) �� Ư�� ���� (TGA, DDS) �� �Բ� �����ϸ� 
// ���˺�ȯ, �÷�Ű(Color-Key), ��������(BCX) ���� �߰� ��ɵ� �����մϴ�.
//
// DDS ���� : ���� �Լ� ����  ex) Create-DDS-Texture
// WIC ���� : bmp, jpg, png ���� �Ϲ� ���� ����.  ex) Create-WIC-Texture
// TGA ���� : ���� �Լ� ���. ex) LoadFrom-TGA-File
//
// �⺻���� ����� DirectXTK ���� ���ԵǾ� ���� ���Դϴ�. �ڼ��� ������ �Ʒ��� �����ϼ���.
// ���̺귯�� ���� :  DXTK/ReadMe.txt
// ���� : http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx
// 
// <����>  DirecXTex, December 13, 2017 (DX11)
// <��� �÷���>
// Windows Desk Top Apps(Windows 7/8/10), XBox One, Windows Mobile (Windows Phone 8.1), Windows Store Apps ����.
// <���� ���>
//  DirectXTex, TexConv (+ColorKey), DDSViwer, DDSTextureLoader,  WICTextureLoader, ScreenGrab  
// <���� ����ȯ��>
//  Windows 8.x SDK, Visual Studio 2013/2015/2017 
//
//
// DirectXTex �� ���� ���ϰ� ����ϱ� ���ؼ� Project �Ӽ� �߰��� �ʿ��մϴ�.
// ���� ������� Project �Ӽ��� ����/�߰� �Ͻʽÿ�.
 //
// 1. C/C++>�Է�>�Ϲ�>�߰� ���� ���͸� : "../Yena/DXTex/Inc" �߰�
// 2. ��Ŀ>�Ϲ�>�߰� ���̺귯�� ���͸� : "../Yena/DXTex/Lib " �߰�
// 3. ��Ŀ>�Է�>�߰� ���Ӽ� : DirectXTex.lib �߰� (�Ǵ� �Ʒ��� ���� ���� ����� ��)
// 4. DirectXTex Ŭ������ ��� ���� :  �������� ������Ʈ�� �ʿ��� ����� �߰�. (�Ʒ� ����)
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG 
	#ifdef _WIN64
		#pragma comment(lib, "DirectXTex64d")	//����� ����.(64bit)
	#elif _WIN32
		#pragma comment(lib, "DirectXTexd")		//����� ����.
	#endif
#else
	#ifdef _WIN64 
		#pragma comment(lib, "DirectXTex64")	//������ ���� (64bit)
	#elif _WIN32 
		#pragma comment(lib, "DirectXTex")		//������ ����.
	#endif
#endif


//-----------------------------------------------------------------------------
// DirectXTex ��� ���� : �츮 ������Ʈ�� �ʿ��� �͸� �߰��ϰڽ��ϴ�.
//-----------------------------------------------------------------------------
// DirectXTex �� �ؽ�ó API 
//
#include "DirectXTex.h"			//DirectXTK ���� ���.			
//#include "../../Yena/DXTex/Inc/DirectXTex.h"		//���� ������������ ������Ʈ ȣȯ���� ���� ����� ����.


/**************** end of "DirectXTex.h" ***********************************/