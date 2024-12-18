//
//! \file   dxAfx.h
//! \brief	���� / ���� / �׷��Ƚ�(DX) ��� �� ����
//!	\details DirectX ��� ���� : DX12
//! 
//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
//! \date  2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \date  2003.11.4. �� ��ȫ Kihong Kim / onlysonim@gmail.com
//! \date  2010.12.01. Update. (DX11.Jun.2010)
//! \date  2016.12.27. Update. (DX11/12 Windows SDK 8.1/10.0.x)
//! \date  2018.01.18. Update. (DX12)
//! \date  2020.08.22. Update. (DX12.x Windows 10 SDK 10.0.x)
//!
#pragma once
#pragma warning(disable:4996)

///////////////////////////////////////////////////////////////////////////////
//
// Platform Header �� �⺻ Library
//
///////////////////////////////////////////////////////////////////////////////
/*
#include "windows.h"
#include "tchar.h"
#include "stdio.h"

#include "map"
#include "chrono"
using namespace std::chrono;
#define TIME_MAX  9223372036854775807
*/


///////////////////////////////////////////////////////////////////////////////
//
// �׷��Ƚ� API �� ǥ�� ��� �� Ȯ����̺귯�� ��� ���. 
//
///////////////////////////////////////////////////////////////////////////////
#include "DirectX.h"			// DX �� ǥ�� ��� �� Ȯ�� ���̺귯�� 
//#include "Vulkan.h"			// VK �� ǥ�� ��� �� Ȯ�� ���̺귯�� 
//#include "OpenGL.h"			// GL �� ǥ�� ��� �� Ȯ�� ���̺귯�� 
//#include "Metal.h"			// Mac�� ǥ�� ��� �� Ȯ�� ���̺귯�� 



namespace YENA
{
 
///////////////////////////////////////////////////////////////////////////////
//
// �׷��Ƚ� �������̽� �� �ڷ��� ������
// API �Ϲ�ȭ�� ��ȯ ������ ȣȯ�� �� �̽ļ� ����
// 
///////////////////////////////////////////////////////////////////////////////
typedef ID3D12Device*				LPDEVICE;
//typedef ID3D11DeviceContext*		LPDXDC;
//typedef IDXGISwapChain*			LPSWAPCHAIN;
//typedef ID3D12RenderTargetView*	LPRTVIEW;
typedef ID3D12Resource*				LPRESOURCE; 
typedef LPRESOURCE					LPXBUFFER; 
typedef LPRESOURCE					LPVERTEXBUFFER; 
typedef LPRESOURCE					LPINDEXBUFFER; 
typedef LPRESOURCE					LPCONSTBUFFER;
typedef LPRESOURCE					LPTEXTURE;
typedef LPRESOURCE					LPTEXTUREBUFFER;
typedef LPVERTEXBUFFER				LPVB; 
typedef LPINDEXBUFFER				LPIB; 
typedef LPCONSTBUFFER				LPCB;
typedef LPTEXTUREBUFFER				LPTB;
typedef LPTEXTURE					LPTEX;
typedef D3D12_RESOURCE_DESC			RESOURCE_DESC;
typedef D3D12_SUBRESOURCE_DATA		SUBRESOURCE_DATA;

typedef ID3D12DescriptorHeap*		LPDESCHEAP;
typedef ID3D12DescriptorHeap*		LPDESCRIPTORHEAP;
typedef D3D12_DESCRIPTOR_HEAP_DESC	DESCRIPTOR_HEAP_DESC;
typedef D3D12_CPU_DESCRIPTOR_HANDLE	CPU_DESCHANDLE;
typedef D3D12_CPU_DESCRIPTOR_HANDLE	CPU_DESCRIPTOR_HANDLE;
typedef D3D12_GPU_DESCRIPTOR_HANDLE	GPU_DESCHANDLE;
typedef D3D12_GPU_DESCRIPTOR_HANDLE	GPU_DESCRIPTOR_HANDLE;

typedef D3D12_VERTEX_BUFFER_VIEW	VERTEXBUFFERVIEW;
typedef VERTEXBUFFERVIEW			VBVIEW;
typedef VERTEXBUFFERVIEW			VBV;
typedef D3D12_VERTEX_BUFFER_VIEW*	LPVERTEXBUFFERVIEW;
typedef LPVERTEXBUFFERVIEW			LPVBVIEW;
typedef LPVERTEXBUFFERVIEW			LPVBV;
typedef D3D12_INDEX_BUFFER_VIEW		INDEXBUFFERVIEW;
typedef INDEXBUFFERVIEW				IBVIEW;
typedef INDEXBUFFERVIEW				IBV;
typedef D3D12_INDEX_BUFFER_VIEW*	LPINDEXBUFFERVIEW;
typedef LPINDEXBUFFERVIEW			LPIBVIEW;
typedef LPINDEXBUFFERVIEW			LPIBV;

typedef D3D12_INPUT_LAYOUT_DESC		INPUTLAYOUT;
typedef D3D12_INPUT_LAYOUT_DESC*	LPINPUTLAYOUT;
//typedef LPINPUTLAYOUT				LPLAYOUT;
typedef D3D12_INPUT_ELEMENT_DESC	INPUTELEMENT;
typedef D3D12_INPUT_ELEMENT_DESC*	LPINPUTELEMENT;
//typedef LPINPUTELEMENT			LPELEMENT;

typedef ID3D12CommandAllocator*		LPCOMMANDALLOCATOR;
typedef LPCOMMANDALLOCATOR			LPCOMMANDALLOC;
typedef LPCOMMANDALLOC				LPCMDALLOC;
typedef ID3D12CommandQueue*			LPCOMMANDQUEUE;
typedef LPCOMMANDQUEUE				LPCMDQUEUE;
typedef ID3D12GraphicsCommandList*	LPGRAPHICSCOMMANDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPGRAPHCMDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPGRPCMDLIST;
typedef LPGRAPHICSCOMMANDLIST		LPCMDLIST;

typedef D3D12_VIEWPORT				VIEWPORT;
typedef D3D12_CLEAR_FLAGS			CLEAR_FLAGS;

// ��ġ ���� ���� ����ü. (DX9/10/11 ���� ȣȯ�� ������)
//using ADAPTER_DESC = DXGI_ADAPTER_DESC1;
typedef DXGI_ADAPTER_DESC1			ADAPTER_DESC;
typedef DXGI_MODE_DESC				MODE_DESC;		//DXGI 1.0 ����
//typedef DXGI_MODE_DESC1			MODE_DESC;		//DXGI 1.1 ����
//typedef D3DDISPLAYMODE			DISPLAYMODE;	//DX9 ��.

// ���̴� ���� ������  (DX9/10/11 ���� ȣȯ�� ������)
//typedef ID3DBlob*  LPFXCODE;				//���̴� �ڵ� ����(�����Ͽ�, ����������, �ӽ�)
typedef ID3DBlob*  LPXDATA;					//���̴� �ڵ� ����(�����Ͽ�, ����������)
typedef ID3DBlob*  LPSHADER;				//���̴� �ڵ� ����(�����ϵ�, ����������)
typedef LPSHADER   LPVERTEXSHADER;
typedef LPSHADER   LPPIXELSHADER;
typedef LPSHADER   LPGEOMETRYSHADER;

typedef ID3D12PipelineState*				LPPIPELINESTATE;
typedef ID3D12PipelineState*				LPPSO;
typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC	GRAPHICS_PIPELINE_STATE_DESC;
typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC	GPSO_DESC;
typedef D3D12_COMPUTE_PIPELINE_STATE_DESC	COMPUTE_PIPELINE_STATE_DESC;
typedef D3D12_COMPUTE_PIPELINE_STATE_DESC	CPSO_DESC;

typedef D3D12_GPU_VIRTUAL_ADDRESS			GPU_VIRTUAL_ADDR;
typedef D3D12_GPU_VIRTUAL_ADDRESS			GPU_VADDR;
typedef D3D12_CPU_DESCRIPTOR_HANDLE			CPU_DESCRIPTOR_HANDLE;
typedef D3D12_CPU_DESCRIPTOR_HANDLE			CPU_DESCH;

/*
// DirectX Math Ÿ�� ������ : ȣȯ�� ���
// DX9/DX10 : DirectX SDK June.2010 ����
typedef D3DXMATRIXA16	MATRIXA; 
typedef D3DXMATRIX		MATRIX;	
typedef D3DXVECTOR4		VECTOR4;
typedef D3DXVECTOR3		VECTOR3;
typedef D3DXVECTOR2		VECTOR2;
*/
// DirectX Math Ÿ�� ������ : ���� �ҽ����� ȣȯ�� ����� ����.
typedef XMMATRIX		MATRIXA; 
typedef XMFLOAT4X4		MATRIX; 
typedef XMVECTOR		VECTOR; 
typedef XMFLOAT4		VECTOR4; 
typedef XMFLOAT3		VECTOR3;
typedef XMFLOAT2		VECTOR2;

//���� Ÿ��: 2����.
//typedef XMCOLOR		Color;		// r, g, b, a.  [������ 0~255]
//typedef XMFLOAT4		Color;		// r, g, b, a.  [�Ǽ��� 0~1.0]





///////////////////////////////////////////////////////////////////////////////
//
//! \brief	���� / ���� / ���� ���ӽ����̽�
//!	\details ���꼺 ����� ���� �پ��� ���, �Լ�, ���� Ŭ����(Helper) �� 
//!			������Ƽ ���̺귯���� �غ�Ǿ� �ֽ��ϴ�.
//! 
//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com 
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
///////////////////////////////////////////////////////////////////////////////
namespace Helpers
{

//////////////////////////////////////////////////////////////////////////////////
//
//! \class	Color
//! \brief	���� / ���� / ���� Ŭ����
//! \details 4���� ���� ����(R,G,B,A)�� ������ ���� �������Դϴ�.
//!			�������� ���� ǥ������ ���� Ư���� Ŭ����ȭ �Ͽ�����
//!			���� DirectX �ڷ������� ȣȯ���� �����ϰ� �ֽ��ϴ�.
//!			DirectXTK �� �����ϴ� \b Color Ŭ������ �Բ� ���캸�� �ٶ��ϴ�.
//! \see	DirectX::SimpleMath::Color 
//! \note	�� Ŭ������ ��� �����ڵ��� SIMD �������� �����Ͽ����ϴ�. 
//!			SISD �� SIMD ����� ������� ������ ���ô�.
//! 
//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
////////////////////////////////////////////////////////////////////////////////
struct ynColor
{
	union
	{
		struct { float r, g, b, a; };
		struct { float x, y, z, w; };
		float    c[4];
		XMFLOAT4 v;
	};

#if defined( __cplusplus )
	ynColor() noexcept :r(1), g(1), b(1), a(1) {}
	explicit ynColor(float _r, float _g, float _b, float _a = 1.0f) noexcept :r(_r), g(_g), b(_b), a(_a) {}
	explicit ynColor(float _c[4]) noexcept :r(_c[0]), g(_c[1]), b(_c[2]), a(_c[3]) {}
	explicit ynColor(const XMFLOAT4& _v) noexcept :v(_v) {}
	//explicit Color(const XMFLOAT4& _v) noexcept: r(_v.x), g(_v.y), b(_v.z), a(_v.w) {}
	ynColor(const XMVECTOR& _v) noexcept { XMStoreFloat4(&v, _v); }

	//virtual ~Color() = default;
	ynColor(ynColor&) = default;
	ynColor& operator = (const ynColor&) = default;
	ynColor(ynColor&&) = default;
	ynColor& operator = (ynColor&&) = default;

	//operator XMFLOAT4 () const noexcept { return XMFLOAT4(r, g, b, a); }
	operator XMFLOAT4 () const noexcept { return v; }
	operator XMVECTOR () const noexcept { return XMLoadFloat4(&v); }
	operator const float* () const noexcept { return c; }
	//operator	   float* () noexcept { return c; }

	//operator XMFLOAT4 () { return XMFLOAT4(a, b, g, r); }
	//Color operator = (XMFLOAT4)
	
	//---------------------------------------------------------------------
	// ������ �������̽����� SISD �� SIMD �������� �����Ͽ����ϴ�.
	// �� ������ ���ϰ� ������� ������ ���ô�. (���� ����)
	//---------------------------------------------------------------------
	//! ����� ��Į�� ���� ������. \n
	//! SIMD Ÿ��1 : SSE/AVX ��ɾ� ��� (������)
	//! \n\n 
	//! \b ���� 
	//! \code  
	//! Color col;  
	//! col = col * 0.5f; 
	//! \endcode
	ynColor operator * (float s)
	{
		float col[4];
		__m128 v0, v1, v2;
		__declspec(align(16)) float a1[] = { r, g, b, a };
		__declspec(align(16)) float a2[] = { s, s, s, s };
		v1 = _mm_load_ps(a1);
		v2 = _mm_load_ps(a2);
		v0 = _mm_mul_ps(v1, v2);
		_mm_storeu_ps(col, v0);
		return ynColor(col);
	}

	/*// SIMD Ÿ��2 : SSE/AVX ��ɾ� ��� (��������)
	Color operator * (float s)
	{
		Color col;
		__m128 v0, v1, v2;

		//...(��������)...

		return col;
	}

	// ���� * ��Į�� ��  (ex)  col = col * 0.5f
	// SISD Ÿ�� : �Ϲ� ��ɾ� ���.
	/*Color operator * (float s)
	{
		Color col;
		col.r = r * s;
		col.g = g * s;
		col.b = b * s;
		col.a = a * s;
		return col;
	}*/

#endif	//__cplusplus
};	//end of ynColor

using Color = YENA::Helpers::ynColor;


//! \namespace	gp3::Helpers::colors
//! \brief		���� / ���� / ���� ���ӽ����̽�
//! \details	Color ���� ��ü���� �̸� ���ǵǾ� ������ ���� ��ü���� �����˴ϴ�.
//! \ingroup Yena
namespace colors {

	GLOBALCONST Color black		(0, 0, 0, 1);
	GLOBALCONST Color white		(1, 1, 1, 1);				//100% white
	GLOBALCONST Color silverlt	(0.9f, 0.9f, 0.9f, 1);		//90% white : Light Silver
	GLOBALCONST Color silver	(0.7f, 0.7f, 0.7f, 1);		//70% white : 
	GLOBALCONST Color gray		(0.5f, 0.5f, 0.5f, 1);		//50% white : gray
	GLOBALCONST Color graydk	(0.3f, 0.3f, 0.3f, 1);		//30% white : Dark-gray
	GLOBALCONST Color graydp	(0.15f, 0.15f, 0.15f, 1);	//15% white : Deep-gray 

	GLOBALCONST Color red		(1.0f, 0.0f, 0.0f, 1);
	GLOBALCONST Color reddk		(0.5f, 0.0f, 0.0f, 1);		//Dark-red
	GLOBALCONST Color green		(0.0f, 1.0f, 0.0f, 1);
	GLOBALCONST Color greendk	(0.0f, 0.5f, 0.0f, 1);		//Dark-pink
	GLOBALCONST Color blue		(0.0f, 0.0f, 1.0f, 1);
	GLOBALCONST Color bluedk	(0.0f, 0.0f, 0.5f, 1);		//Dark-blue
	GLOBALCONST Color bluedp	(0.0f, 0.125f, 0.3f, 1);	//Deep-blue 

	GLOBALCONST Color yellow	(1, 1, 0, 1);
	GLOBALCONST Color yellowdk	(0.5f, 0.5f, 0, 1);			//Dark-yellow.
	GLOBALCONST Color pink		(1.0f, 0.5f, 1.0f, 1);
	GLOBALCONST Color pinkdk	(0.5f, 0.2f, 0.5f, 1);		//Dark-pink
	GLOBALCONST Color cyan		(0.0f, 1.0f, 1.0f, 1);
	GLOBALCONST Color cyandk	(0.0f, 0.5f, 0.5f, 1);		//Dark-cyan
	GLOBALCONST Color orange	(1.0f, 0.6f, 0.0f, 1);
	GLOBALCONST Color orangedk	(0.5f, 0.3f, 0.0f, 1);		//Dark-orange

	//�⺻ ����.
	GLOBALCONST Color& bgBlue = bluedp;		//Deep-blue
	GLOBALCONST Color& bgGray = graydp;		//Deep-gray

	//���� �߰��� ���⿡...
	//...

};
using namespace colors;

#define ynColorTest(_x, _y, _col) \
	ynTextDraw(_x, _y, _col, _T("%s = {%.2f, %.2f, %.2f, %.2f}"), ynToString(_col), _col.x, _col.y, _col.z, _col.w)		
	//ynTextDraw(_x, _y, _col, _T("%s = {%.2f, %.2f, %.2f, %.2f}"), toString(_col), _col.r, _col.g, _col.b, _col.a)




///////////////////////////////////////////////////////////////////////////////
//
// DX �� ��ġ ���� ���� ������  
//
///////////////////////////////////////////////////////////////////////////////

//...



///////////////////////////////////////////////////////////////////////////////
//
// DX Helper Ŭ���� �߰� ������ 
//
// d3dx12.h �� ������� ���� ������ �߰� �� ����
// DX Helper ��Ÿ���� �ִ��� �ؼ�.
// ���ȫ Kihong Kim / Update. 2018.08.22
//
///////////////////////////////////////////////////////////////////////////////
#if defined( __cplusplus )

#ifndef CDXGI_SWAP_CHAIN_DESC1
	struct CDXGI_SWAP_CHAIN_DESC1 : DXGI_SWAP_CHAIN_DESC1
	{
		CDXGI_SWAP_CHAIN_DESC1() = default;
		explicit CDXGI_SWAP_CHAIN_DESC1(const DXGI_SWAP_CHAIN_DESC1& o) noexcept :
			DXGI_SWAP_CHAIN_DESC1(o) 
		{}
		CDXGI_SWAP_CHAIN_DESC1(
			UINT width,
			UINT height,
			DXGI_FORMAT format,
			BOOL stereo = FALSE,
			DXGI_SAMPLE_DESC sampleDesc = { 1, 0 },
			DXGI_USAGE bufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
			UINT bufferCount = 2,
			DXGI_SCALING scaling = DXGI_SCALING_STRETCH,
			DXGI_SWAP_EFFECT swapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
			DXGI_ALPHA_MODE alphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
			UINT flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
		) noexcept
		{
			Width = width;
			Height = height;
			Format = format;
			Stereo = stereo;
			SampleDesc = sampleDesc;
			BufferUsage = bufferUsage;
			BufferCount = bufferCount;
			Scaling = scaling;
			AlphaMode = alphaMode;
			Flags = flags;
		}
		CDXGI_SWAP_CHAIN_DESC1(
			UINT width, UINT height, DXGI_FORMAT format, 
			DXGI_SWAP_EFFECT swapEffect, UINT bufferCount = 2, UINT samplerCount = 1
		) noexcept
		{
			Width = width;  Height = height;  Format = format;
			Stereo = FALSE;
			SampleDesc = { samplerCount, 0 };
			BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			BufferCount = bufferCount;
			Scaling = DXGI_SCALING_STRETCH;
			SwapEffect = swapEffect;
			AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		}
		CDXGI_SWAP_CHAIN_DESC1(
			const DXGI_MODE_DESC& m,
			DXGI_SWAP_EFFECT swapEffect, UINT bufferCount = 2, UINT samplerCount = 1
		) noexcept
		{
			Width = m.Width;  Height = m.Height;  Format = m.Format;
			Stereo = FALSE;
			SampleDesc = { samplerCount, 0 };
			BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			BufferCount = bufferCount;
			Scaling = DXGI_SCALING_STRETCH;
			SwapEffect = swapEffect;
			AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
			Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		}
		/*CDXGI_SWAP_CHAIN_DESC1( const DXGI_MODE_DESC& md ) noexcept : 		 
		{
			//CDXGI_SWAP_CHAIN_DESC1(md.Width, md.Height, md.Format);
		}*/
		static inline CDXGI_SWAP_CHAIN_DESC1 FlipModel(UINT width, UINT height, DXGI_FORMAT format, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(width, height, format, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, buffCount, samplerCount);
		}
		static inline CDXGI_SWAP_CHAIN_DESC1 FlipModel(const DXGI_MODE_DESC& mode, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(mode, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, buffCount, samplerCount);
		}
		static inline CDXGI_SWAP_CHAIN_DESC1 DiscardModel(const DXGI_MODE_DESC& mode, UINT buffCount = 2, UINT samplerCount = 1)
		{
			return CDXGI_SWAP_CHAIN_DESC1(mode, DXGI_SWAP_EFFECT_FLIP_DISCARD, buffCount, samplerCount);
		}

	};
#endif


#ifndef CD3DX12_DESCRIPTOR_HEAP_DESC
	struct CD3DX12_DESCRIPTOR_HEAP_DESC : D3D12_DESCRIPTOR_HEAP_DESC
	{
		CD3DX12_DESCRIPTOR_HEAP_DESC() = default;
		explicit CD3DX12_DESCRIPTOR_HEAP_DESC(const D3D12_DESCRIPTOR_HEAP_DESC& o) noexcept :
			D3D12_DESCRIPTOR_HEAP_DESC(o)
		{}
		CD3DX12_DESCRIPTOR_HEAP_DESC(
			D3D12_DESCRIPTOR_HEAP_TYPE type,
			UINT numDescriptors,
			D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
			UINT nodeMask = 0
		) noexcept
		{
			Type = type;
			NumDescriptors = numDescriptors;
			Flags = flags;
			NodeMask = nodeMask;
		}
	};
#endif


	// ���ҽ� �� 
	// D3D12 ���� ���ǵǾ� ���� ������ VB/IB/Texture ����� ���ϼ��� ���� ������.
	//
#ifndef CD3DX12_RESOURCE_VIEW
	struct CD3DX12_RESOURCE_VIEW
	{
		//...
	};

	//typedef D3D12_RESOURCE_VIEW RESOURCEVIEW;
	//typedef void* LPRESOURCEVIEW;
#endif


#ifndef CD3DX12_CONSTANT_BUFFER_VIEW
	// ������� �� 
	// D3D12 ���� ���ǵǾ� ���� ������ VB/IB/Texture ����� ���ϼ��� ���� ������.
	// ���� : D3D12_CONSTANT_BUFFER_VIEW_DESC https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_constant_buffer_view_desc
	struct CD3DX12_CONSTANT_BUFFER_VIEW
	{
		D3D12_GPU_VIRTUAL_ADDRESS BufferLocation = 0;		//���� ��ġ.
		UINT SizeInBytes = 0;								//���� ũ�� (+����)
		UINT StrideInBytes = 0;								//��� ũ�� (�迭������ ���1���� ũ��)(+����)
	};

	typedef CD3DX12_CONSTANT_BUFFER_VIEW		CONSTANTBUFFERVIEW;
	typedef CONSTANTBUFFERVIEW					CBVIEW;
	typedef CONSTANTBUFFERVIEW					CBV;
	typedef CD3DX12_CONSTANT_BUFFER_VIEW*		LPCONSTANTBUFFERVIEW;
	typedef LPCONSTANTBUFFERVIEW				LPCBVIEW;
	typedef LPCONSTANTBUFFERVIEW				LPCBV;
	typedef D3D12_CONSTANT_BUFFER_VIEW_DESC		CONSTANT_BUFFER_VIEW_DESC;
#endif



	// �߰� ���۴� ���⿡...
	// ...



#endif // defined( __cplusplus )







///////////////////////////////////////////////////////////////////////////////
//
// ���� ���� Ŭ����.
//
///////////////////////////////////////////////////////////////////////////////
// ������ �������̽����� SISD �� SIMD �������� �����Ͽ����ϴ�.
// �Ϲ� ������ �� SIMD Ÿ�� ���ۿ� ���� ���ô�. (���� ����)
// Color operator *  (Color& lhs, float s);
// Color operator +  (Color& lhs, float s);
// Color operator -  (Color& lhs, float s);
// Color operator *= (Color& lhs, float s);
// Color operator += (Color& lhs, float s);
// Color operator -= (Color& lhs, float s);
// ... 




}//end of namespace Helpers.
using namespace Helpers;






//////////////////////////////////////////////////////////////////////////////// 
//
//! \brief		���� / ���� / ���ҽ� ���ӽ����̽�
//! \details	������ �ڿ� �� ���� ����� ���� ��ũ��, �Լ� �� Ŭ������ ���ǵǾ� �ֽ��ϴ�.
//! \remark	�׷��Ƚ� API �� �Ϲ�ȭ(Generic)�� ���� �������̰� �ܼ��� ������ �����ϸ�
//!				������ (�ڵ�ȭ) Ŭ���� ����� �����Ͽ����ϴ�. \n
//!	\note		�������� ���� �ڿ��� �������� �����ؾ� �մϴ�. \n 
//!				������ �ڿ������� �������� �߿� �����̸� �� ������ ������ǥ ���� �ϳ��̴�.
//! 
//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
// 
////////////////////////////////////////////////////////////////////////////////
namespace Resources
{
	static int ynUpdateBuffer(LPXBUFFER pBuff, LPVOID pData, UINT size);

	//! �� ���۸� �����մϴ�.
	//! \param pDev		D3D ��ġ
	//! \param size		������ ���� ũ��
	//! \param ppBuff	������ ���۸� �������� (���ҽ�) ������
	//! \return ������ OK, ���н� FAIL.
	//!
	static int ynCreateBuffer( LPDEVICE pDev, UINT size, out LPXBUFFER* ppBuff )
	{
		try 
		{
			ID3D12Resource* buff = nullptr;
			ynChkFailed(pDev->CreateCommittedResource( 
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(size),
						D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&buff))); 
			*ppBuff = buff;
		}
		catch (ynError& e)
		{
			ynError(e, _T("���� ���� ����"));
			return e.hr();
		}

		return YN_OK;
	}


	//! �� ���۸� �����մϴ�.
	//! \param pDev		D3D ��ġ
	//! \param pCmdList Ŀ�ǵ� ����Ʈ
	//! \param rd		���ҽ� ��ũ���� 
	//! \param srd		���� ���ҽ� ������ 
	//! \param ppBuff	������ ���۸� �������� (���ҽ�) ������
	//! \return ������ OK, ���н� FAIL.
	//! 
	static int ynCreateBuffer( LPDEVICE pDev, LPGRPCMDLIST pCmdList, 
							 RESOURCE_DESC& rd, SUBRESOURCE_DATA& srd, out LPXBUFFER* ppBuff )
	{
		try 
		{
			ID3D12Resource* pHB = nullptr;
			ynChkFailed(pDev->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
						D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_COMMON, 
						nullptr, IID_PPV_ARGS(&pHB)));
			ID3D12Resource* pUB = nullptr;
			ynChkFailed(pDev->CreateCommittedResource(
						&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
						D3D12_HEAP_FLAG_NONE, &rd, D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr, IID_PPV_ARGS(&pUB)));
			pCmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pHB,
						D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST));
			UpdateSubresources<1>(pCmdList, pHB, pUB, 0, 0, 1, &srd);
			pCmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(pHB,
						D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ));

			//�۾���� & �ӽ� ���� ����
			//...

			*ppBuff = pHB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("���� ���� ����"));
			return e.hr();
		}

		return YN_OK;
	}


	//! �� ���۸� �����ϰ� ������ �����ͷ� ���۸� ä���.
	//! \param pDev		D3D ��ġ
	//! \param pData	���ۿ� ������ ������.
	//! \param size		������ ���� ũ��
	//! \param ppBuff	������ ���۸� �������� (���ҽ�) ������
	//! \return ������ OK, ���н� FAIL.
	//! 
	static int ynCreateBuffer( LPDEVICE pDev, LPVOID pData, UINT size, out LPXBUFFER* ppBuff )
	{
		try
		{
			LPXBUFFER pUB = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, size, &pUB));
			ynChkFailed(ynUpdateBuffer(pUB, pData, size));

			*ppBuff = pUB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("���� ���� ����"));
			return e.hr();
		}

		return YN_OK;
	}


	//! ������ �����ͷ� ���۸� �����մϴ�.
	//! \param pBuff	������ ���� ������
	//! \param pData	���ۿ� ������ ������.
	//! \param size		������ �������� ũ��
	//! \return ������ OK, ���н� FAIL.
	//! 
	static int ynUpdateBuffer(LPXBUFFER pBuff, LPVOID pData, UINT size)
	{
		HRESULT hr = S_YN_OK;
		if (pData == nullptr) return hr;

		UINT8* buff = nullptr;
		hr = pBuff->Map(0, nullptr, (void**)&buff);
		if (FAILED(hr) || buff == nullptr)
		{
			ynError(hr, _T("���� ���� ����. \npBuff=0x%x Size=%d"), buff, size);
			return hr;
		}
		memcpy(buff, pData, size);	 
		pBuff->Unmap(0, nullptr);

		return hr;
	}

	//! ���۸� �����մϴ�. 
	//! \param rpBuff  ������ ����
	//! 
	static void ynReleaseBuffer(LPXBUFFER& rpBuff)
	{
		safeRelease(rpBuff);
	}


	//! �Էµ� \a size ��  \a align ��ŭ �����մϴ�.  
	//! \param	size	������ ��.  
	//! \param	align	���� ���ذ�. 
	//! \return UINT ���ĵ� ��
	//! \remark �� �Լ��� ����(ũ��) ���Ŀ� ���˴ϴ�.
	//!			�޸� ����� ȿ������ ���� 256 ����Ʈ ������ �����մϴ�.
	//! 
	static UINT ynSizeAligned(UINT size, UINT align)
	{
		align -= 1;
		return (size + align) & ~align;
	}

	//! �Էµ� \a size �� 256(����Ʈ)���� �����մϴ�.  
	//! \param size ������ ��.  
	//! \return UINT ���ĵ� ��
	//! \remark �� �Լ��� ����(ũ��) ���Ŀ� ���˴ϴ�.
	//!			�޸� ����� ȿ������ ���� 256 ����Ʈ ������ �����մϴ�.
	//! 
	static UINT ynSizeAligned(UINT size)
	{
		return (size + 255) & ~255;
	}


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// ���۷� �ڿ� ���� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	/*struct ynIBuffer
	{
		LPRESOURCE			pRes = nullptr;
		LPVOID				pView = nullptr;
		//LPRESOURCEVIEW		pView = nullptr;
		//LPRESOURCEVIEW		pView = {};
		//UINT				uSize = 0;
		
		//...
	};*/


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// ���� ���� ��� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynVertexBuffer
	//! \brief	���� / ���� / ���� ���� ����ü 
	//! \details VB �� VBV ��� ���� ����ü.
	//! \sample def_VB
	//! \remark �ڷ����� �̸��� �������� '���� ����'�� �������� ����ü ������
	//!			D3D12 �������� �ʿ��� VB �� VBV �� ��� �����ϰ� �ֽ��ϴ�.
 	//!			�� �����ϰ� �������� ǥ������ ���� ���� �������̽��� �߰����� �ʾҽ��ϴ�.\n
	//!			ynConstantBuffer Ŭ������ �����Ͽ� �������� ���� �߰��غ��� �ٶ��ϴ�.
	//! \see ynIndexBuffer, ynConstantBuffer
	//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena 
	struct ynVertexBuffer
	{
		LPXBUFFER			pBuff = nullptr;		//!< ���� ����
		LPVERTEXBUFFERVIEW	pView = nullptr;		//!< ���� ����-��
	};
	

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// ���� ���� ��� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynIndexBuffer
	//! \brief	���� / ���� / ���� ���� ����ü 
	//! \details IB �� IBV ��� ���� ����ü.
	//! \sample def_IB
	//! \remark �ڷ����� �̸��� �������� '���� ����'�� �������� ����ü ������
	//!			D3D12 �������� �ʿ��� IB �� IBV �� ��� �����ϰ� �ֽ��ϴ�.
 	//!			�� �����ϰ� �������� ǥ������ ���� ���� �������̽��� �߰����� �ʾҽ��ϴ�. \n
	//!			ynConstantBuffer Ŭ������ �����Ͽ� �������� ���� �߰��غ��� �ٶ��ϴ�.
	//! \see ynVertexBuffer, ynConstantBuffer
	//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	struct ynIndexBuffer 
	{
		LPXBUFFER			pBuff = nullptr;		//!< ���� ����
		LPINDEXBUFFERVIEW	pView = nullptr;		//!< ���� ����-��
	};

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// ��� ���� ��� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	/*struct ynConstantBuffer
	{ 
		LPRESOURCE			pRes = nullptr;
		CONSTANTBUFFERVIEW	view = {};
	};*/

	//////////////////////////////////////////////////////////////////////////////// 
	//
	// ��� ���� ��� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	_mdata
	//! \brief	���� / ���� / ��Ÿ ������ ���ø�
	//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	template<typename T>
	struct _mdata : T
	{
		_mdata() noexcept = default;
		virtual ~_mdata() = default;		
		operator T() {	return *(T*)this;	}
		virtual void set	(T& data)	{ *(T*)this = data;	}	
		virtual T*   data	()			{ return this;		} 
		virtual UINT size	()			{ return sizeof(T);	}
		virtual UINT alignOf()			{ return alignof(T);}
	};
	
	
	//-------------------------------------------------------------------
	// ��� ���� Ŭ���� ���ø�
	//-------------------------------------------------------------------
	//! \class	ynConstantBuffer
	//! \brief	���� / ���� / ��� ���� Ŭ���� ���ø�
	//! \details CB �� CBV �� ����ϸ� ���ø� ��� ������ T �� �����ϰ� �ֽ��ϴ�.
	//! \tparam	 T	��� ��Ÿ ������ YENA::Resources::_mdata<T>
	//!
	//! \sample     def_CB
	//! 
	//! \note ��� ������ ������ �����ϰ� �������� ǥ���� ����� �����ϰ� �ֽ��ϴ�. \n
	//!		������,	��� ���۴� ���̴� ���� �� ǥ���İ��� ��ü���� ���ؼ� Ư���� ���ø�ȭ �Ͽ����ϴ�. \n
	//!		�ǿ뼺���ٴ� ������ ���� ���������� ��ġ ä�ָ� ���ڽ��ϴ�. \emoji sunglasses \n 
	//!		2020.08.22 ���ȫ Kihong.Kim
	//! 
	//! \b ��뿹 : ���ø����̼� (demo.cpp)
	//! \sample     sample_CB1
	//! 
	//! \b ��뿹 : ���̴� (demo.fx)  
	//! \sample     sample_CB2
	//!
	//! \see		YENA::Resources::_mdata,  ynVertexBuffer, ynIndexBuffer
	//!
	//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	//! \ingroup Yena
	//!   
	template<typename T>
	struct ynConstantBuffer : _mdata<T>
	{
		LPXBUFFER pBuff = nullptr;
		CONSTANT_BUFFER_VIEW_DESC  viewDesc = {};

		ynConstantBuffer() = default;
		virtual ~ynConstantBuffer() { safeRelease(pBuff);		}
		virtual void			 set	(LPXBUFFER _buff)	{ pBuff = _buff;	}	
		virtual LPXBUFFER&		 get	()					{ return pBuff;		}		 
		virtual GPU_VIRTUAL_ADDR addr	()					{ return pBuff->GetGPUVirtualAddress();	}
		virtual GPU_VIRTUAL_ADDR view	()					{ return addr();	}		
		virtual GPU_VIRTUAL_ADDR getGPUVirtualAddress	()	{ return addr();	}
 	};

	//template<typename T> int  createConstantBuffer	(out ConstantBuffer<T>** ppCB);
	//template<typename T> int  updateConstantBuffer	(ConstantBuffer<T>* pCB);
	//template<typename T> void releaseConstantBuffer	(ConstantBuffer<T>*& rpCB);


	//-------------------------------------------------------------------
	// ��� ���� ��� �Լ� ���ø�
	//-------------------------------------------------------------------
	//! ������۸� �����մϴ�.
	//! \tparam T		������ Ÿ��.
	//! \param	pDev	D3D ��ġ.
	//! \param	ppCB	������ ������۸� �������� ��ü�� ������.
	//! \return ������ OK, ���н� FAIL.
	//! \author ���ȫ / Kihong Kim / onlysonim@gmail.com
	//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
	template<typename T>
	int ynCreateConstantBuffer(LPDEVICE pDev, out ynConstantBuffer<T>** ppCB)
	{
		try
		{
			UINT size = sizeof(T);
			UINT sizeA = ynSizeAligned(size); 
			ID3D12Resource* pBuff = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, sizeA, &pBuff));
			ynChkFailed(ynUpdateBuffer(pBuff, &T{}, sizeA));
			//ynChkFailed(createBuffer(pDev, sizeof(T), &pBuff));
			//ynChkFailed(updateBuffer(pBuff, &T{}, sizeof(T)));		
			ynConstantBuffer<T>* pCB = new ynConstantBuffer<T>; 	
			assert(pCB != NULL);
			pCB->set(pBuff);		 

			*ppCB = pCB;
		}
		catch (ynError& e)
		{
			ynError(e, _T("ConstantBuffer<%s> ���� ����"), toString(T));
			return e.hr();
		}

		return YN_OK;
	}

	//! ������۸� �����մϴ�.
	//! \tparam T		������ Ÿ��.
	//! \param pDev		D3D ��ġ.
	//! \param pData	������ ��� ������.
	//! \param size		������ ���� ũ��.
	//! \param cnt		���ۿ� ����� ����� ũ��.
	//! \param ppCB		������ ������۸� �������� ������.
	//! \param pSizeAligned	������ ���ĵ� ũ�⸦ �������� ���� ������.
	//! \return ������ OK, ���н� FAIL.
	//! 
	template<typename T>
	int ynCreateConstantBuffer(LPDEVICE pDev, LPVOID pData, UINT size, UINT cnt, 
								out LPXBUFFER* ppCB, out UINT* pSizeAligned)
	{
		UINT sizeA = ynSizeAligned(size); 
		UINT totSizeA = sizeA * cnt;
		try
		{
			LPXBUFFER pCB = nullptr;
			ynChkFailed(ynCreateBuffer(pDev, totSizeA, &pCB));
			ynChkFailed(ynUpdateBuffer(pCB, pData, totSizeA));
			//ynChkFailed(Error::test(1, 2, _T("createCB-Array ����!")));
			*ppCB = pCB;
			*pSizeAligned = sizeA;
		}Z
		catch (ynError& e)
		{
			ynError(e, _T("ConstantBuffer<%s> ���� ���� : \n" 
						"Element[%d] : Size=%d Aligned=%d Total=%dBytes"), 
						ynToString(T), cnt, size, sizeA, totSizeA);
			return e.hr();
		}

		return YN_OK;
	}

	//! ������� ��ü�� �����մϴ�. ��ü ���� ��� �����ͷ� ���۸� �����մϴ�.
	//! \tparam T		������ Ÿ��.
	//! \param pCB		������ ������� ��ü.
	//! \return ������ OK, ���н� FAIL.
	//! 
	template<typename T>
	int ynUpdateConstantBuffer(ynConstantBuffer<T>* pCB)
	{
		return ynUpdateBuffer(pCB->get(), pCB->data(), pCB->size());
	}

	//! ������� ��ü�� �����մϴ�. ���� ������ �� ���۵� �Բ� ���ŵ˴ϴ�.
	//! \tparam T		������ Ÿ��.
	//! \param	rpCB	������ ������� ��ü.
	//! \return ����.
	//! 
	template<typename T>
	void ynReleaseConstantBuffer(ynConstantBuffer<T>*& rpCB)
	{
		safeDelete(rpCB);
	}

	//! ������� ��ü�� �����մϴ�. ���� ������ �� ���۵� �Բ� ���ŵȴ�
	//! \tparam T		������ Ÿ��
	//! \param	rCB		������ ������� ��ü.
	//! \return ����.
	//! 
	template<typename T>
	void ynReleaseConstantBuffer(ynConstantBuffer<T>& rCB)
	{
		safeRelease(rCB.pBuff);
	}


	//////////////////////////////////////////////////////////////////////////////// 
	//
	// �ؽ�ó ��� �������̽�.
	//
	//////////////////////////////////////////////////////////////////////////////// 
	//! \class	ynTexture
	//! \brief	���� / ���� / �ؽ�ó Ŭ����
	//! \details
	//! \ingroup Yena
	//! 
	struct ynTexture //: public IBuffer
	{
		//...
	};

	//! �ؽ�ó�� �ε��մϴ�.
	//! 
	static int ynCreateTexture  () 
	{ 
		//...
		return YN_OK;
	}
	
	//! �ؽ�ó�� �����մϴ�.
	//! 
	static int ynReleaseTexture () 
	{
		//...
		return YN_OK;
	}


};//end of namespace Resources

using namespace Resources;





///////////////////////////////////////////////////////////////////////////////
//
// ���� / ����ó�� Ŭ����.
//
///////////////////////////////////////////////////////////////////////////////

//... ynError.h ����.
 




///////////////////////////////////////////////////////////////////////////////
//
// ��Ʈ �������̽�.
//
///////////////////////////////////////////////////////////////////////////////

//... ynFont.h ����.




}// end of namespace YENA


using namespace YENA;


/**************** The end of file : "dxAfx.h" *********************************/