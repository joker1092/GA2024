#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>
#include <string>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")

class D2DRenderer
{
public:
	BOOL D2DInitialize(HWND hWnd);
	void D2DUninitialize();
	void BeginDraw();
	void Clear(D2D1::ColorF color);
	HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap);
	//void DrawBitmap(ID2D1Bitmap* pID2D1Bitmap, int x, int y);
	void DrawBitmap(ID2D1Bitmap* pID2D1Bitmap, D2D_MATRIX_3X2_F mat = D2D1::Matrix3x2F::Identity());
	void PrintMatrix(const wchar_t* str, D2D_MATRIX_3X2_F& mat, float left, float top);
	void EndDraw();
	void DWDrawText(const wchar_t* str, D2D1_RECT_F rect);
	void RenderSetTransform(D2D_MATRIX_3X2_F Transform);
private:
	ID2D1Factory* pD2DFactorty;
	ID2D1HwndRenderTarget* pRenderTarget;

	IWICImagingFactory* g_pWICFactory;

	// DWrite
	IDWriteFactory* g_pDWriteFactory;
	IDWriteTextFormat* g_pDWriteTextFormat;

	ID2D1SolidColorBrush* g_pBrush; // 브러시 개체 인터페이스 포인터 변수
};

