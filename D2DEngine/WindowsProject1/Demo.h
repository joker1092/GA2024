#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/D2DRender.h"

class Demo:public WinGameApp
{
	ID2D1HwndRenderTarget* pRenderTaget = nullptr;
public:
	void Initialize(HINSTANCE hInstance, LPCTSTR szTitle) override;
	void Render(ID2D1RenderTarget* pRenderTarget) override;
};

