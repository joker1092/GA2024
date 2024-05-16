#pragma once
#include "../stdafx.h"

namespace Render
{

	void InitRender(HWND hWindow, int witdh, int height);

	void BeginDraw();

	void EndDraw();

	void ReleaseRender();

	void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);

	void DrawRect(int x, int y, int width, int height, COLORREF color);

	void DrawCircle(int x, int y, int radius, COLORREF color);

	void DrawPolygon(POINT points[], int count, COLORREF color);

	void DrawText(int x, int y, const char* text, COLORREF color);

	
	void DrawFont(int x, int y, int cx, int cy, const WCHAR* text, COLORREF color, int fontSize, const wchar_t* fontName, int fontStyle);

	SIZE GetScreenSize();

	void DrawImage(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcWitdh, int srcHeight, float alpha, float scale = 1.f);

	void DrawRotateImage(int centerX, int centerY, Gdiplus::Bitmap* bitmap, float rad);

	void DrawBitmap(int x, int y, Gdiplus::Bitmap* bitmap, int srcX, int srcY, int srcWitdh, int srcHeight);
}