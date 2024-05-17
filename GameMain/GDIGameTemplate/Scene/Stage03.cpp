#include "Stage03.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"
void Stage03::Init()
{
	// �ۼ����
	// 1. object�� �����ڷ� ���� ex) (���ϴ� Ŭ����) obj = new (���ϴ� Ŭ����)();
	// 2. AddObject(obj); �� ���� ������ ������Ʈ ���� �ֱ�.
	// 3. �ݶ��̴��� �ʿ��� object�� ��� object�� ���������� �ݶ��̴��� �������� �ʴ´ٸ� ���� �ֱ�.
	// 3-1. �ݶ��̴��� ���� �� �ݶ��̴��ȿ� object�� �־��ֱ�.
	// 3-2. �ش� �ݶ��̴��� ColliderManager�� �ֱ�.
	// 4. �̺�Ʈ�� �ʿ��ϴٸ� ���̱�.

	// ���� �����ϴ� ��ü ex)Button�� Update���� ���콺 Ŭ���� ���콺�� �ش� �ݶ��̴� ������ �Ǵ��ϴ� �뵵�� ��� ����.
	// �Ǵ� ������Ʈ ��ü�� Update���� ���콺 Ŭ���� �޾Ƽ� ��뵵 ����.
	// �ϳ��ϳ� event�� ��ü ������ �ؾ��ϹǷ� init�Լ� ���ΰ� ���� ����.

	//UIBackGround* myBack = new UIBackGround();
	//AddObject(myBack);

	colliderManager = new ColliderManager();

	Player* m_Player = new Player();
	UIImage* pauseBack = new UIImage();
	m_Player->Init();

	PauseEvent* e_pause = new PauseEvent;
	ResumeEvent* e_resume = new ResumeEvent;
	RetryEvent* e_retry = new RetryEvent;
	ExitEvent* e_exit = new ExitEvent;
	AddEvent(e_pause);
	AddEvent(e_resume);
	AddEvent(e_retry);
	AddEvent(e_exit);

	CResourceManager* CRM = CResourceManager::GetInstance();
	Gdiplus::Bitmap* exitBtn = CRM->LoadBitmapResouce(L"exitBtn", L"exitbtn_sample.bmp");

	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage", L"image1.png");

	UIButton* resume = new UIButton(Vector2{ 710,200 }, e_resume, exitBtn);
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry, exitBtn);
	UIButton* exit = new UIButton(Vector2{ 710,600 }, e_exit, exitBtn);

	e_resume->Resume = resume;
	e_resume->Retry = retry;
	e_resume->PauseBack = pauseBack;
	e_resume->Exit = exit;
	e_pause->Resume = resume;
	e_pause->Retry = retry;
	e_pause->PauseBack = pauseBack;
	e_pause->Exit = exit;

	e_resume->OnTrigger();
	m_Player->pauseEvent = e_pause;
	
	pauseBack->Init(pauseBackImage, Vector2{ 500.f,400.f });



	pauseBack->m_isActive = false;
	resume->m_isActive = false;
	retry->m_isActive = false;
	exit->m_isActive = false;


	SelectScnEvent* e_nextScn = new SelectScnEvent((UINT)SceneType::STAGE_04);
	AddEvent(e_nextScn);
	UITimer* myTimer = new UITimer(Vector2{ 910,200 }, e_nextScn, 40.f);

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	//UIBackGround* myBackGround = new UIBackGround();
	//myBackGround->Init(L"Water_Down_00.bmp",CRM);
	AddObject(myBackGround);
	AddObject(myTimer);

	//*************����� ����****************
	srand(std::time(NULL));
	Fish* myFish;
	for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish1", 50.f, 4.36f, L"Fish_01_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish2", 50.f, 4.36f, L"Fish_02_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish3", 50.f, 4.36f, L"Fish_03_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}for (int i = 0; i < 4; i++) {
		myFish = new Fish(L"Fish4", 50.f, 4.36f, L"Fish_04_Anim_00.png", CRM, L".png", 3.f, 4.f, 23.f, 23.f);
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}
	myFish = new Fish(L"CrawFish", 40.f, 3.5f, L"CrawFish_01_Anim_00.png", CRM, L".png", 4.f, 5.f, 23.f, 23.f);
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	myFish = new Fish(L"BossFish", 60.f, 8.7f, L"BossFish_03_Anim_00.png", CRM, L".png", 2.f, 4.f, 30.f, 30.f);
	AddObject(myFish);
	colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	//***************************************
	AddObject(m_Player);
	m_Player->m_pos = { 600.f, 350.f };
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"����+�׸���_00.png", CRM);
	AddObject(myUPBackGround);
	AddObject(pauseBack);
	AddObject(resume);
	AddObject(retry);
	AddObject(exit);


	UICrossDissolve* backEffect = new UICrossDissolve({ 640.f, 360.f }, Game::GameManager::GetInstance()->sceneBitmap);
	AddObject(backEffect);

	alpha = 1.0f;

}

Stage03::~Stage03() {
	/*for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}

	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
		delete colliderManager;*/
}

void Stage03::Start()
{
}

void Stage03::FixedUpdate() {
	//myBackGround->FixedUpdate();
	//myUPBackGround->FixedUpdate();
}

void Stage03::Exit() {
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