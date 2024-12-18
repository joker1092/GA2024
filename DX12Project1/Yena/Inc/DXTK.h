//
// DirectXTK.h : DirectX Toolkit ���
//
// DirectXTK for DX12 (Aug.15, 2020) 
// ���� Present : Chuck Walbourn @ Microsoft / MSFT (https://walbourn.github.io/)
// ���� Edit    : Kihong Kim / onlysonim@gmail.com 
// ���� Update  : 2020.08.26
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
// DirectX Took Kit  ���̺귯�� 
//
///////////////////////////////////////////////////////////////////////////////
//
// DX ��ƿ��Ƽ �� �Ϲ�ȭ ���̺귯�� ������. 
// DX ���� �ʿ��� ���� ��� Ŭ���� �� ���񽺸� �����մϴ�.
// �ڼ��� ������ �Ʒ��� �����ϼ���.
// ���̺귯�� ���� :  DXTK/ReadMe.txt
// ���� : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
// 
// <����> DirectXTK, December 5, 2016 (DX11)
// <��� �÷���>
// Windows Desk Top Apps(Windows 7/8/10), XBox One, Windows Mobile (Windows Phone 8.1), Windows Store Apps ����.
// <���� ���>
// Math, State Objects, Texture, EffectSystem, Model(XFile) Animation, Font, Audio (XAudio �� Wave), ��..
// <���� ����ȯ��>
// Windows 8.x SDK
// Visual Studio 2013 (update 5), Visual Studio 2015 (update 3), Windows 7 (sp1) �̻�.
//
//
// DirectXTK �� ���� ���ϰ� ����ϱ� ���ؼ� Project �Ӽ� �߰��� �ʿ��մϴ�.
// ���� ������� Project �Ӽ��� ����/�߰� �Ͻʽÿ�.
 //
// 1. C/C++>�Է�>�Ϲ�>�߰� ���� ���͸� : "../Yena/DXTK/Inc" �߰�
// 2. ��Ŀ>�Ϲ�>�߰� ���̺귯�� ���͸� : "../Yena/DXTK/Lib " �߰�
// 3. ��Ŀ>�Է�>�߰� ���Ӽ� : DirectXTK.lib �߰� (�Ǵ� �Ʒ��� ���� ���� ����� ��)
// 4. DirectXTK Ŭ������ ��� ���� :  �������� ������Ʈ�� �ʿ��� ����� �߰�. (�Ʒ� ����)
//
///////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG 
	#ifdef _WIN64
		#pragma comment(lib, "DirectXTK12_64d")		//64bit + ����� ����.
	#elif _WIN32
		#pragma comment(lib, "DirectXTK12d")		//32bit + ����� ����.
	#endif
#else
	#ifdef _WIN64 
		#pragma comment(lib, "DirectXTK12_64")		//64bit ���� 
	#elif _WIN32 
		#pragma comment(lib, "DirectXTK12")			//32bit ����.
	#endif
#endif

//-----------------------------------------------------------------------------
// DirectXTK ��� ���� : �츮 ������Ʈ�� �ʿ��� �͸� �߰��ϰڽ��ϴ�.
//-----------------------------------------------------------------------------
// DirectXTK : SimpleMath 
// SIMD ���� ���� �ڷ���(XMVECTOR �� XMMATRIX)�� ���� ���⼺�� �ּ�ȭ�� ���� ���̺귯��. 
// �����ϰ� �������� �������� �ټ��� �������ϸ� ����մϴ�.
// ���� : https://github.com/Microsoft/DirectXTK/wiki/SimpleMath
// 
#include "SimpleMath.h"	
using namespace DirectX::SimpleMath;

// DirectXTK : SpriteFont
// 2D Texture / Sprite ����� ��Ʈ ��� ���̺귯��.
// ������ ����������, CJK �迭�� ��Ʈ�� ��� �ϼ����� �����˴ϴ�.
// ���� : Yena/DXTK/MakeSpriteFont/SpriteFont ����.txt
// ���� : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
//
#include "SpriteFont.h"	
  

// DirectXTK �� �ؽ�ó API 
// DirectXTex �� ���ߵ� �������� �⺻���� ����� DirectXTK ���� ���Խ��� ���� ��.
// DDS : dds ���� �Լ� ���.
// WIC : bmp, jpg, png ���� �Ϲ� ���� ����.
// TGA : tga ���� �Լ� ���.
// ����1 : https://blogs.msdn.microsoft.com/chuckw/2012/03/02/directxtk/
// ����2 : http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx
//
#include "DDSTextureLoader.h"	//DDS ���� �Լ���.
#include "WICTextureLoader.h"	//WIC ���� �Լ���.


// DirectXTK : DescritprHeap 
// ��ũ����-�� ��� Ŭ����.
//
#include "DescriptorHeap.h"



// DirectXTK : ResourceUploadBatch 
// ���ҽ� ���ε� ��� Ŭ����.
//
#include "ResourceUploadBatch.h"




/**************** end of "DirectXTK.h" ***********************************/