#pragma once
#include "framework.h"



class D2DRender
{
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTaget;
	
	IWICImagingFactory* pWICFactorry;

	// DWrite
	IDWriteFactory* pDWriteFactory;
	IDWriteTextFormat* pDWriteTextFormat;

	ID2D1SolidColorBrush* pBrush; // �귯�� ��ü �������̽� ������ ����

	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;

public:
	BOOL D2DIntialize(HWND hwnd);
	void D2DUnintialize();
	void BeginDraw();
	void Clear(D2D1::ColorF(color));
	void EndDraw();
	void DrawTextRect(const wchar_t* str, D2D1_RECT_F rect);
	void DrawRect(D2D1_RECT_F rect);
	size_t GetUsedVRAM();
	ID2D1HwndRenderTarget* GetRenderTarget() { return pRenderTaget; }

	HRESULT D2DBitmapFromFile(const WCHAR* path, ID2D1Bitmap** ppID2DBitmap);
};

