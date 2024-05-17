
#include "RenderSystem.h"
#include "../Manager/SceneManager.h"


#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "gdiplus.lib")


namespace Render
{
	HWND hWnd;
	int nWidth;
	int nHeight;
	HDC frontMemDC;    // 앞면 DC
	HDC backMemDC;    // 뒷면 DC

	HBITMAP backBitmap = nullptr;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::Graphics* graphics = nullptr;
	//Gdiplus::Image image;
	// https://learn.microsoft.com/ko-kr/windows/win32/gdiplus/-gdiplus-about-gdi--about


	void InitRender(HWND hWindow, int width, int height)
	{
		hWnd = hWindow;
		nWidth = width;
		nHeight = height;

		frontMemDC = GetDC(hWnd);
		backMemDC = CreateCompatibleDC(frontMemDC);
		backBitmap = CreateCompatibleBitmap(frontMemDC, nWidth, nHeight);
		::SelectObject(backMemDC, backBitmap);

		// GDI+ 초기화
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		graphics = Gdiplus::Graphics::FromHDC(backMemDC);
		//Gdiplus::Image image(L"image1.png");
	}

	Gdiplus::Bitmap* GetFrontHDC()
	{
		HDC hdcScreen = GetDC(hWnd);

		// Create compatible DC and Bitmap
		HDC hdcCapture = CreateCompatibleDC(hdcScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, 1280, 720);
		SelectObject(hdcCapture, hBitmap);

		// Capture screen to HDC
		BitBlt(hdcCapture, 0, 0, 1280, 720, hdcScreen, 0, 0, SRCCOPY);

		// Create GDI+ Bitmap from HDC
		Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(hBitmap, NULL);


		return bitmap;//new Gdiplus::Bitmap(1280, 720, Gdiplus::Graphics::FromHDC(frontMemDC));
	}

	void BeginDraw()
	{
		::PatBlt(backMemDC, 0, 0, nWidth, nHeight, BLACKNESS);
	}

	void EndDraw()
	{
		
		//SceneManager::GetInstance()->GetCurScene()->prevBitmap = new Gdiplus::Bitmap(nWidth, nHeight, Gdiplus::Graphics::FromHDC(frontMemDC));

		::BitBlt(frontMemDC, 0, 0, nWidth, nHeight, backMemDC, 0, 0, SRCCOPY);
	}

	void ReleaseRender()
	{
		Gdiplus::GdiplusShutdown(gdiplusToken);
		DeleteObject(backBitmap);
		DeleteDC(backMemDC);
		ReleaseDC(hWnd, frontMemDC);
	}

	void DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 5, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		MoveToEx(backMemDC, x1, y1, NULL);

		LineTo(backMemDC, x2, y2);

		SelectObject(backMemDC, hOldPen);

		DeleteObject(hPen);
	}


	void DrawRect(int x, int y, int width, int height, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		Rectangle(backMemDC, x, y, x + width, y + height);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);
	}


	void DrawCircle(int x, int y, int radius, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		Ellipse(backMemDC, x - radius, y - radius, x + radius, y + radius);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);

	}

	void DrawPolygon(POINT points[], int count, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		Polygon(backMemDC, points, count);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);

	}

	void DrawText(int x, int y, const char* text, COLORREF color)
	{
		SetTextColor(backMemDC, color);

		TextOutA(backMemDC, x, y, text, (int)strlen(text));
	}

	SIZE GetScreenSize()
	{
		SIZE size;
		size.cx = nWidth;
		size.cy = nHeight;

		return size;
	}

	//bitmap은 GdiplusShutdown 하기전에 해제해야함
	void DrawImage(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcWitdh, int srcHeight, float alpha, float scale)
	{
		if (bitmap == nullptr)
			return;

		Gdiplus::ImageAttributes imageAttributes;

		Gdiplus::ColorMatrix colorMatrix{ 
			{
				{1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, alpha, 0.0f},
				{0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
			}
		};

		imageAttributes.SetColorMatrix(&colorMatrix);

		Gdiplus::Rect srcRect(srcX, srcY, srcWitdh, srcHeight); // 소스의 영역
		Gdiplus::Rect destRect(x + srcWitdh / 2 - (srcWitdh * scale) / 2, y + srcHeight / 2 - (srcHeight * scale) / 2, srcRect.Width * scale, srcRect.Height * scale); // 화면에 그릴 영역		
		// 이미지 그리기
		graphics->DrawImage(bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel, &imageAttributes);

		//graphics->DrawImage()
	}

	void DrawRotateImage(int centerX, int centerY, Gdiplus::Bitmap* bitmap, float rad, float alpha) {
		Gdiplus::Graphics ScreenG(backMemDC);
		Gdiplus::Matrix mat;

		Gdiplus::ImageAttributes imageAttributes;

		Gdiplus::ColorMatrix colorMatrix{
			{
				{1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f, alpha, 0.0f},
				{0.0f, 0.0f, 0.0f, 0.0f, 1.0f}
			}
		};

		imageAttributes.SetColorMatrix(&colorMatrix);

		mat.RotateAt(rad, Gdiplus::PointF((float)centerX + bitmap->GetWidth() / 2.f, (float)centerY + bitmap->GetHeight()/ 2.f));
		ScreenG.SetTransform(&mat);
		Gdiplus::Rect srcRect(0, 0, bitmap->GetWidth(), bitmap->GetHeight()); // 소스의 영역
		Gdiplus::Rect destRect(centerX, centerY, srcRect.Width, srcRect.Height);

		ScreenG.DrawImage(bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel, &imageAttributes);
		//ScreenG.DrawImage(bitmap, centerX, centerY);
	}

	void DrawBitmap(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcWitdh, int srcHeight) {
		Gdiplus::ImageAttributes imgAttr;
		Gdiplus::Rect srcRect(srcX, srcY, srcWitdh, srcHeight); // 소스의 영역
		Gdiplus::Rect destRect(x, y, srcRect.Width, srcRect.Height);
		//imgAttr.SetColorKey(Gdiplus::Color(0, 0, 0), Gdiplus::Color(0, 0, 0), Gdiplus::ColorAdjustTypeBitmap);
		graphics->DrawImage(bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, Gdiplus::UnitPixel);
	}

	void DrawFont(int x, int y, int cx, int cy , const WCHAR* text, COLORREF color, int fontSize, const wchar_t* fontName, int fontStyle) {

		Gdiplus::Color f_color;
		f_color.SetFromCOLORREF(color);
		Gdiplus::SolidBrush semiTransBrush(Gdiplus::Color(0, 0, 0, 0)); // 투명 
		graphics->FillRectangle(&semiTransBrush, x, y, cx, cy);

		Gdiplus::FontFamily   fontFamily(fontName);
		Gdiplus::Font         font(&fontFamily, fontSize, fontStyle, Gdiplus::UnitPoint);
		Gdiplus::RectF        rectF(x, y, cx, cy);
		Gdiplus::SolidBrush   solidBrush(f_color);

		//graphics.DrawString(string, -1, &font, rectF, NULL, &solidBrush);
		graphics->DrawString(text, -1, &font, rectF, NULL, &solidBrush);
		Gdiplus::Pen pen(Gdiplus::Color(0, 0, 0, 1));
		graphics->DrawRectangle(&pen, rectF);
	}
}