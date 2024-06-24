#include "DemoGameApp.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	Sun.LoadD2DBitmap(L"../Resource/sun.jpg", pD2DRender);
	Earth.LoadD2DBitmap(L"../Resource/earth.jpg", pD2DRender);
	Moon.LoadD2DBitmap(L"../Resource/moon.jpg", pD2DRender);
	Sun.SetLocation({ 640,480 });
	Sun.SetScale({1.5,1.5});
	Earth.SetParant(&Sun);
	Earth.SetScale({ 0.5,0.5 });
	Earth.SetLocation({ 200,200 });
	Moon.SetParant(&Earth);
	Moon.SetScale({ 0.5,0.5 });
	Moon.SetLocation({ 200,200 });

}
void DemoGameApp::UnInitialize()
{
	//todo
	WinGameApp::UnInitialize();
}

void DemoGameApp::Update()
{
	//todo
	Sun.SetRotation(rotate);
	Sun.Update();
	Earth.SetRotation(rotate);
	Earth.Update();
	Moon.SetRotation(rotate);
	Moon.Update();
	rotate++;
	Sun.Update();
	Earth.Update();
	Moon.Update();
}

void DemoGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	//todo
	Sun.Render(pRenderTarget);
	Earth.Render(pRenderTarget);
	Moon.Render(pRenderTarget);
}
