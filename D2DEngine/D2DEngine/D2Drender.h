#pragma once
#include "framework.h"
#include <d2d1.h>
#include <comdef.h>
#include <d2d1_1helper.h>

#pragma comment(lib,"d2d1.lib")

class D2Drender
{
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTaget;
public:
	BOOL D2DIntialize(HWND hwnd);
	void D2DUnintialize();
	void BeginDraw();
	void Clear(D2D1::ColorF(color));
	void EndDraw();
};

