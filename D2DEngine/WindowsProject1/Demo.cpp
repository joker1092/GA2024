#include "Demo.h"


void Demo::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	pRenderTaget = pD2DRender->GetRenderTarget();


}

void Demo::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTaget->DrawLine(D2D1::Point2F(0, 0), D2D1::Point2F(400, 400), pD2DRender->getBrush(), 1.0f);
}


