#pragma once



class D2DRenderer
{
private:
	static D2DRenderer* rInstance;
	D2DRenderer() {}
	~D2DRenderer() {}
	ID2D1Factory* pD2DFactorty;
	ID2D1HwndRenderTarget* pRenderTarget;

	IWICImagingFactory* g_pWICFactory;

	// DWrite
	IDWriteFactory* g_pDWriteFactory;
	IDWriteTextFormat* g_pDWriteTextFormat;

	ID2D1SolidColorBrush* g_pBrush; // 브러시 개체 인터페이스 포인터 변수
public:
	static D2DRenderer* GetInstance();
	BOOL D2DInitialize(HWND hWnd);
	void D2DUninitialize();
	void BeginDraw();
	void Clear(D2D1::ColorF color);
	void EndDraw();
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	void DrawBitmap(ID2D1Bitmap* pID2D1Bitmap, D2D_MATRIX_3X2_F mat = D2D1::Matrix3x2F::Identity());
	void DWDrawText(const wchar_t* str, D2D1_RECT_F rect);
	void RenderSetTransform(D2D_MATRIX_3X2_F Transform);
};

