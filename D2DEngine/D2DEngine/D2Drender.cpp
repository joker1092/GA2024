#include "D2DRender.h"

BOOL D2DRender::D2DIntialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		return FALSE;
	}
	
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if (FAILED(hr)) {
		return FALSE;
	}
	
	RECT rc;
	GetClientRect(hwnd,&rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, size), &pRenderTaget);
	

	if (FAILED(hr)) {
		return FALSE;
	}

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
		return FALSE;

	hr = pDWriteFactory->CreateTextFormat(
		L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,   // Font Size
		L"", //locale
		&pDWriteTextFormat
	);

	if (SUCCEEDED(hr))
	{
		hr = pRenderTaget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &pBrush);
	}

	hr = CoCreateInstance(CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&pWICFactorry));
	
	if (FAILED(hr)) {
		return FALSE;
	}

	// Create DXGI factory
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
	// VRAM 정보얻기 위한 개체 생성
	if (FAILED(hr))
	{
		return FALSE;
	}

	m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
	if (FAILED(hr))
	{
		return FALSE;
	}


	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hwnd, err.ErrorMessage(), L"FAILED", MB_OK);
		return false;
	}

	return TRUE;
}

void D2DRender::D2DUnintialize()
{
	
	if (pBrush)pBrush->Release();
	if (pDWriteTextFormat)pDWriteTextFormat->Release();
	if (pDWriteFactory)pDWriteFactory->Release();
	if (pWICFactorry)pWICFactorry->Release();
	if (pRenderTaget)pRenderTaget->Release();
	if (pFactory)pFactory->Release();
	if (m_pDXGIAdapter)m_pDXGIAdapter->Release();
	if (m_pDXGIFactory)m_pDXGIFactory->Release();



	CoUninitialize();
}

void D2DRender::BeginDraw()
{
	pRenderTaget->BeginDraw();
}

void D2DRender::Clear(D2D1::ColorF(color))
{
	pRenderTaget->Clear(D2D1::ColorF(color));
}

void D2DRender::EndDraw()
{
	pRenderTaget->EndDraw();
}

void D2DRender::DrawTextRect(const wchar_t* str, D2D1_RECT_F rect)
{
	pRenderTaget->DrawText(
		str, (UINT32)wcslen(str),
		pDWriteTextFormat,
		rect,
		pBrush
	);
}

void D2DRender::DrawRect(D2D1_RECT_F rect)
{
	pRenderTaget->DrawRectangle(rect, pBrush, 1.0f);
}


size_t D2DRender::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}



HRESULT D2DRender::D2DBitmapFromFile(const WCHAR* path, ID2D1Bitmap** ppID2DBitmap) {
	
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder;
	IWICFormatConverter* pConverter;

	hr = pWICFactorry->CreateDecoderFromFilename(path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (FAILED(hr))
	{
		//::MessageBox(hWnd, L"CreateDecoderFromFilename Error", L"FAILED", MB_OK);
		return hr;
	}

	IWICBitmapFrameDecode* pFrame = NULL;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr))
	{
		//::MessageBox(hWnd, L"GetFrame Error", L"FAILED", MB_OK);
		return hr;
	}

	hr = pWICFactorry->CreateFormatConverter(&pConverter);
	if (FAILED(hr))
	{
		//::MessageBox(hWnd, L"CreateFormatConverter Error", L"FAILED", MB_OK);
		return hr;
	}
	
	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPRGBA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr))
	{
		//::MessageBox(hWnd, L"pConverter Initialize Error", L"FAILED", MB_OK);
		return hr;
	}

	hr = pRenderTaget->CreateBitmapFromWicBitmap(pConverter,NULL,ppID2DBitmap);
	{
		//::MessageBox(hWnd, L"CreateBitmapFromWicBitmap Error", L"FAILED", MB_OK);
		return hr;
	}

	if (pConverter) pConverter->Release();
	if (pDecoder) pDecoder->Release();
	if (pFrame) pFrame->Release();

	return hr;
}