#pragma once
class D2DRender
{
	//D2DRender 클래스는 싱글톤으로 구현한다.
	static D2DRender* instance;

	
	D2DRender();
	~D2DRender();
public:
	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRT;
	IWICImagingFactory* pWICFactory;

	IDWriteFactory* pDWriteFactory;
	IDWriteTextFormat* pTextFormat;

	ID2D1SolidColorBrush* pBlackBrush;
	ID2D1SolidColorBrush* pWhiteBrush;
	ID2D1SolidColorBrush* pRedBrush;
	ID2D1SolidColorBrush* pGreenBrush;
	ID2D1SolidColorBrush* pBlueBrush;
	static D2DRender* GetInstance();
	bool InitD2D(HWND hWnd);
	//Wic 이용하여 D2Dbitmap 생성하여 받은 비트맵 포인트에 저장
	bool LoadBitmapFromFile(const wchar_t* uri, ID2D1Bitmap** ppBitmap);

	
	void UninitD2D();
};

