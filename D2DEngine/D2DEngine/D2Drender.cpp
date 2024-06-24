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

	hr = CoCreateInstance(CLSID_WICImagingFactory,NULL,CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&pWICFactorry));
	
	if (FAILED(hr)) {
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
	if (pRenderTaget)pRenderTaget->Release();
	if (pFactory)pFactory->Release();

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