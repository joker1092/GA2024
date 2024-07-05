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
	HRESULT hr = CoInitialize(NULL);	// COM ���̺귯�� �ʱ�ȭ
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"COM ���̺귯�� �ʱ�ȭ ����", L"����", MB_OK);
		return false;
	}
	// D2D1Factory ����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"D2D1CreateFactory ����", L"����", MB_OK);
		return false;
	}
	// D2D1HwndRenderTarget ����
	RECT rc;
	GetClientRect(hWnd, &rc);
	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&pRT);
	if (FAILED(hr)) 
	{
		MessageBox(hWnd, L"CreateHwndRenderTarget ����", L"����", MB_OK);
		return false;
	}
	// DWriteFactory ����
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"DWriteCreateFactory ����", L"����", MB_OK);
		return false;
	}
	// TextFormat ����
	hr = pDWriteFactory->CreateTextFormat(
		L"���� ���", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"ko-kr", &pTextFormat);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateTextFormat ����", L"����", MB_OK);
		return false;
	}
	// Brush ����
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush ����", L"����", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pWhiteBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush ����", L"����", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &pRedBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush ����", L"����", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &pGreenBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush ����", L"����", MB_OK);
		return false;
	}
	hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBlueBrush);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CreateSolidColorBrush ����", L"����", MB_OK);
		return false;
	}
	// WICFactory ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICFactory);
	if (FAILED(hr))
	{
		MessageBox(hWnd, L"CoCreateInstance ����", L"����", MB_OK);
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
	//�̹��� ������ ���ڵ�
	hr = pWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateDecoderFromFilename ����", L"����", MB_OK);
		return false;
	}
	//�̹����� ���������� ���ڵ�
	hr = pDecoder->GetFrame(0, &pSource);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"GetFrame ����", L"����", MB_OK);
		return false;
	}
	
	//�̹����� D2D�������� ��ȯ
	hr = pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateFormatConverter ����", L"����", MB_OK);
		return false;
	}
	hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Initialize ����", L"����", MB_OK);
		return false;
	}
	//D2D��Ʈ�� ����
	hr = pRT->CreateBitmapFromWicBitmap(pConverter, NULL, ppBitmap);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateBitmapFromWicBitmap ����", L"����", MB_OK);
		return false;
	}

	//��ü ����
	if (pDecoder) pDecoder->Release();
	if (pSource) pSource->Release();
	if (pConverter) pConverter->Release();


	return false;
}

void D2DRender::UninitD2D()
{
	//com ��ü ����
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
