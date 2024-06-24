#pragma once
#include "framework.h"


class D2DRender
{
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTaget;
	
	IWICImagingFactory* pWICFactorry;
public:
	BOOL D2DIntialize(HWND hwnd);
	void D2DUnintialize();
	void BeginDraw();
	void Clear(D2D1::ColorF(color));
	void EndDraw();

	ID2D1HwndRenderTarget* GetRenderTarget() { return pRenderTaget; }

	HRESULT D2DBitmapFromFile(const WCHAR* path, ID2D1Bitmap** ppID2DBitmap);
};

