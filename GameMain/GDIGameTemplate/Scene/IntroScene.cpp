#include "IntroScene.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Event.h"

IntroScene::IntroScene()
{

}

IntroScene::~IntroScene()
{

}

void IntroScene::Init()
{
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"ㅂㅈㄷㅂㅈㄷㅂㅈㄷㅂㅈㄷㅂㅈㄷ by passing a RectF to the DrawString method.";

	wcscpy_s(_str, 255, t_str);


	CResourceManager* CR = CResourceManager::GetInstance();
	Gdiplus::Bitmap* myBitmap = CR->LoadBitmapResouce(L"image1", L"image1.png");
	UIImage* myBack = new UIImage(); // 객체 테스트
	myBack->Init(myBitmap, { 500.f,400.f });

	UIDialog* dialog = new UIDialog();
	dialog->Init({ 100.f,100.f }, { 500.f,400.f }, _str,RGB(0,0,0),20);

	SelectScnEvent* e_NextScn = new SelectScnEvent(2); // 씬전환 이벤트 테스트
	AddEvent(e_NextScn);
	AddObject(myBack);
	AddObject(dialog);

	delete[] _str;
}


void IntroScene::Start()
{
}

void IntroScene::Exit() {
	if(Game::GameManager::GetInstance()->sceneBitmap != nullptr)
		delete Game::GameManager::GetInstance()->sceneBitmap;
	Game::GameManager::GetInstance()->sceneBitmap = Render::GetFrontHDC();
	//CScene::~CScene();
	if (colliderManager != nullptr)
		delete colliderManager;
	
	for (int i = 0; i < m_eventArr.size(); i++) {
		if (m_eventArr[i] != nullptr) {
			delete (m_eventArr[i]);
		}
	}
	for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}
	}
	m_arrObj.clear();
	m_eventArr.clear();
}

