#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	

	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1",L"startback.bmp");
	UIImage* myBack = new UIImage(); // 객체 테스트 
	myBack->Init(myBitmap, { 640.f,360.f });

	/*SelectScnEvent* a = new SelectScnEvent(3);
	delete a;*/
	Gdiplus::Bitmap* startBtn = CR->LoadBitmapResouce(L"startBtn", L"startbtn_sample.bmp");
	Gdiplus::Bitmap* exitBtn = CR->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::STAGE_01,mySound::SoundList::Singing); // 씬전환 이벤트 테스트
	UIButton* gameStartButton = new UIButton(Vector2{200.0f,300.0f}, e_nextScn, startBtn); // 객체 테스트
	
	scoreRect = { 400,200,800,800 };
	
	WCHAR* _str = new WCHAR[255];
	WCHAR t_str[] = L"랭킹 보드 구현할 장소\n 불러오는건 사이즈 보고 구현할것";

	wcscpy_s(_str, 255, t_str);

	UIDialog* dialog = new UIDialog();
	dialog->Init({ 400.f,200.f }, { 800.f,800.f}, _str, RGB(255, 0, 0), 20);

	ExitEvent* e_exit = new ExitEvent;
	UIButton* exit = new UIButton(Vector2{ 200.0f,600.0f }, e_exit, exitBtn);

	

	AddObject(myBack);
	AddObject(dialog);
	AddObject(gameStartButton);
	AddObject(exit);
	AddEvent(e_nextScn);
	AddEvent(e_exit);


	
	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	AddObject(backEffect);

	alpha = 1.0f;
}

StartScene::~StartScene() {

}

void StartScene::Exit() {
	if (Game::GameManager::GetInstance()->sceneBitmap != nullptr)
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