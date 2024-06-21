#include "D2Drender.h"

BOOL D2Drender::D2DIntialize(HWND hwnd)
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

	/*if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
		return false;
	}*/
	return TRUE;
}

void D2Drender::D2DUnintialize()
{
	if (pRenderTaget)pRenderTaget->Release();
	if (pFactory)pFactory->Release();

	CoUninitialize();
}

void D2Drender::BeginDraw()
{
	pRenderTaget->BeginDraw();
}

void D2Drender::Clear(D2D1::ColorF(color))
{
	pRenderTaget->Clear(D2D1::ColorF(color));
}

void D2Drender::EndDraw()
{
	pRenderTaget->EndDraw();
}
