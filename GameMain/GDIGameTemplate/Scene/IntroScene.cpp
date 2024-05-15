#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"

IntroScene::IntroScene()
{

}

void IntroScene::Init()
{
	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1", L"image1.png");
	UIImage* myBack = new UIImage(); // °´Ã¼ Å×½ºÆ®
	myBack->Init(myBitmap, { 500.f,400.f });
}

void IntroScene::Update()
{
}

void IntroScene::Render(HDC dc)
{
}

void IntroScene::Start()
{
}

void IntroScene::Exit()
{
}


