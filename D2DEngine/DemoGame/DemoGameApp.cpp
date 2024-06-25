#include "DemoGameApp.h"

void DemoGameApp::Initialize(HINSTANCE hInstance, LPCTSTR szTitle)
{
	WinGameApp::Initialize(hInstance, szTitle);
	//todo
	bg.LoadD2DBitmap(L"../Resource/midnight.png", pD2DRender);
	bg.LoadAnimationAsset(L"Background");
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	bg.SetDstRect(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom));
	player.LoadD2DBitmap(L"../Resource/run.png", pD2DRender);
	player.LoadAnimationAsset(L"Run");
	player.SetDstRect(D2D1::RectF(0, 0, 100, 100));
	/*Sun.LoadD2DBitmap(L"../Resource/sun.jpg", pD2DRender);
	Earth.LoadD2DBitmap(L"../Resource/earth.jpg", pD2DRender);
	Moon.LoadD2DBitmap(L"../Resource/moon.jpg", pD2DRender);
	Sun.SetLocation({ 640,480 });
	Sun.SetScale({1.5,1.5});
	Earth.SetParant(&Sun);
	Earth.SetScale({ 0.5,0.5 });
	Earth.SetLocation({ 200,200 });
	Moon.SetParant(&Earth);
	Moon.SetScale({ 0.5,0.5 });
	Moon.SetLocation({ 200,200 });*/

}
void DemoGameApp::UnInitialize()
{
	//todo
	/*Sun.~BitmapScene();
	Earth.~BitmapScene();
	Moon.~BitmapScene();*/
	bg.~AnimationScene();
	player.~AnimationScene();
	WinGameApp::UnInitialize();
}

void DemoGameApp::Update(float deltatime)
{
	std::cout << deltatime << std::endl;
	//todo
	bg.Update(deltatime);
	player.Update(deltatime);
	/*Sun.SetRotation(rotate);
	Sun.Update();
	Earth.SetRotation(rotate);
	Earth.Update();
	Moon.SetRotation(rotate);
	Moon.Update();
	rotate++;
	Sun.Update();
	Earth.Update();
	Moon.Update();*/
}

void DemoGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	//todo
	bg.Render(pRenderTarget);
	player.Render(pRenderTarget);
	/*Sun.Render(pRenderTarget);
	Earth.Render(pRenderTarget);
	Moon.Render(pRenderTarget);*/
}
