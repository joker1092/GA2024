#include "WinApp.h"
#include "RenderSystem.h"

#pragma comment(lib, "msimg32.lib")

HWND hWnd;

HDC frontMemDC;    // ¾Õ¸é DC
HDC backMemDC;    // µÞ¸é DC

HBITMAP backBitmap = nullptr;

void RenderSystem::InitRender() {
    hWnd = global::GetWinApp().GetWindow();

    frontMemDC = GetDC(hWnd);

    backMemDC = CreateCompatibleDC(frontMemDC);

    backBitmap = CreateCompatibleBitmap(frontMemDC, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight());
}

void ClearScreen()
{
    ::PatBlt(backMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), WHITENESS);
}

void RenderSystem::BeginDraw() {
    ClearScreen();

    ::SelectObject(backMemDC, backBitmap);
}

void RenderSystem::EndDraw() {
    ::BitBlt(frontMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), backMemDC, 0, 0, SRCCOPY);
}

void RenderSystem::ReleaseRender() {
    DeleteObject(backBitmap);

    DeleteDC(backMemDC);

    ReleaseDC(hWnd, frontMemDC);
}

void RenderSystem::DrawLine(int x1, int y1, int x2, int y2, COLORREF color) {
    HPEN hPen = CreatePen(PS_SOLID, 5, color);

    HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

    MoveToEx(backMemDC, x1, y1, NULL);

    LineTo(backMemDC, x2, y2);

    SelectObject(backMemDC, hOldPen);

    DeleteObject(hPen);
}

void RenderSystem::DrawRect(int x, int y, int width, int height, COLORREF color) {
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

void RenderSystem::DrawCircle(int x, int y, int radius, COLORREF color) {
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

void RenderSystem::DrawPolygon(POINT points[], int count, COLORREF color) {
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

void RenderSystem::DrawText(int x, int y, const char* text, COLORREF color) {
    SetTextColor(backMemDC, color);

    TextOutA(backMemDC, x, y, text, strlen(text));
}

void RenderSystem::DrawBitmap(int x, int y, HBITMAP hBitmap) {
    HDC bitmapMemDC = CreateCompatibleDC(frontMemDC);

    HBITMAP hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hBitmap);

    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    ::BitBlt(backMemDC, x, y, bm.bmWidth, bm.bmHeight, bitmapMemDC, 0, 0, SRCCOPY);

    DeleteDC(bitmapMemDC);
}


void RenderSystem::TransparentDrawBitmap(int x, int y, HBITMAP hBitmap) {
    HDC bitmapMemDC = CreateCompatibleDC(frontMemDC);

    HBITMAP hOldBitmap = (HBITMAP)SelectObject(bitmapMemDC, hBitmap);

    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    ::TransparentBlt(backMemDC, x, y, bm.bmWidth, bm.bmHeight, bitmapMemDC, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255,255,255));

    DeleteDC(bitmapMemDC);
}

HBITMAP RenderSystem::LoadImdage(const char* path) {
    HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    return hBitmap;
}

void RenderSystem::ReleaseImage(HBITMAP hBitmap) {
    DeleteObject(hBitmap);
}



