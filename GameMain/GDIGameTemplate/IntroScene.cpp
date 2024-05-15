#include "IntroScene.h"
#include "../../GameLogic/Objects/UIObject.h"
#include "../../GameLogic/Event.h"

IntroScene::IntroScene()
{

}

void IntroScene::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"Draw text in a rectangle by passing a RectF to the DrawString method.";
	
	wcscpy(_str, t_str);
	

	CResourceManager* CR = CResourceManager::GetInstance();
	Gdiplus::Bitmap* myBitmap = CR->LoadBitmapResouce(L"image1", L"image1.png");
	UIImage* myBack = new UIImage(); // 객체 테스트
	myBack->Init(myBitmap, { 500.f,400.f });

	UIDialog* dialog = new UIDialog();
	dialog->Init({ 500.f,400.f }, { 500.f,400.f }, _str);

	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // 씬전환 이벤트 테스트
	AddObject(myBack);
	AddObject(dialog);
}


void IntroScene::Start()
{
}

void IntroScene::Exit()
{
}


