#include "pch.h"
#include "D2DRender.h"

D2DRender* D2DRender::instance = nullptr;

D2DRender* D2DRender::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new D2DRender();
	}
	return instance;
}

D2DRender::D2DRender()
{
	
}

D2DRender::~D2DRender()
{
}

bool D2DRender::InitD2D(HWND hWnd)
{
	HRESULT hr = CoInitialize(NULL);	// COM 라이브러리 초기화
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"COM 라이브러리 초기화 실패", L"에러", MB_OK);
		return false;
	}
	// D2D1Factory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"D2D1CreateFactory 실패", L"에러", MB_OK);
		return false;
	}
	// D2D1HwndRenderTarget 생성
	RECT rc;
	GetClientRect(hWnd, &rc);
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&pRT);
	if (FAILED(hr)) 
	{
		MessageBox(hWnd, L"CreateHwndRenderTarget 실패", L"에러", MB_OK);
		return false;
	}
	// DWriteFactory 생성
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"DWriteCreateFactory 실패", L"에러", MB_OK);
		return false;
	}
	// TextFormat 생성
	hr = pDWriteFactory->CreateTextFormat(
		L"맑은 고딕", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"ko-kr", &pTextFormat);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateTextFormat 실패", L"에러", MB_OK);
		return false;
	}
	// Brush 생성
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush 실패", L"에러", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pWhiteBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush 실패", L"에러", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pRedBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush 실패", L"에러", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pGreenBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush 실패", L"에러", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBlueBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush 실패", L"에러", MB_OK);
		return false;
	}
	// WICFactory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CoCreateInstance 실패", L"에러", MB_OK);
		return false;
	}

	return true;
}

bool D2DRender::LoadBitmapFromFile(const wchar_t* uri, ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICFormatConverter* pConverter = NULL;

	HRESULT hr;
	//이미지 파일을 디코딩
	hr = pWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateDecoderFromFilename 실패", L"에러", MB_OK);
		return false;
	}
	//이미지를 프레임으로 디코딩
	hr = pDecoder->GetFrame(0, &pSource);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"GetFrame 실패", L"에러", MB_OK);
		return false;
	}
	
	//이미지를 D2D형식으로 변환
	hr = pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateFormatConverter 실패", L"에러", MB_OK);
		return false;
	}
	hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Initialize 실패", L"에러", MB_OK);
		return false;
	}
	//D2D비트맵 생성
	hr = pRT->CreateBitmapFromWicBitmap(pConverter, NULL, ppBitmap);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateBitmapFromWicBitmap 실패", L"에러", MB_OK);
		return false;
	}

	//객체 해제
	if (pDecoder) pDecoder->Release();
	if (pSource) pSource->Release();
	if (pConverter) pConverter->Release();


	return false;
}

void D2DRender::UninitD2D()
{
	//com 객체 해제
	if (pBlueBrush) pBlueBrush->Release();
	if (pGreenBrush) pGreenBrush->Release();
	if (pRedBrush) pRedBrush->Release();
	if (pWhiteBrush) pWhiteBrush->Release();
	if (pBlackBrush) pBlackBrush->Release();
	if (pTextFormat) pTextFormat->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pWICFactory) pWICFactory->Release();
	if (pRT) pRT->Release();
	if (pD2DFactory) pD2DFactory->Release();
	CoUninitialize();	
}
