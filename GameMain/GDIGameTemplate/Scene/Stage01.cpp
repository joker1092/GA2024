#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"
void Stage01::Init()
{
	// 작성요령
	// 1. object를 생성자로 생성 ex) (원하는 클래스) obj = new (원하는 클래스)();
	// 2. AddObject(obj); 를 통해 생성된 오브젝트 씬에 넣기.
	// 3. 콜라이더가 필요한 object의 경우 object가 내부적으로 콜라이더를 생성하지 않는다면 직접 넣기.
	// 3-1. 콜라이더를 넣을 때 콜라이더안에 object도 넣어주기.
	// 3-2. 해당 콜라이더를 ColliderManager에 넣기.
	// 4. 이벤트도 필요하다면 붙이기.

	// 따로 존재하는 객체 ex)Button은 Update에서 마우스 클릭시 마우스가 해당 콜라이더 안인지 판단하는 용도로 사용 가능.
	// 또는 오브젝트 자체가 Update에서 마우스 클릭을 받아서 사용도 가능.
	// 하나하나 event나 객체 생성을 해야하므로 init함수 내부가 꽉찰 예정.

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

	UIButton* resume = new UIButton(Vector2{ 710,200 }, e_resume);
	UIButton* retry = new UIButton(Vector2{ 710,400 }, e_retry);
	UIButton* exit = new UIButton(Vector2{ 710,600 }, e_exit);
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
	CResourceManager* CRM = CResourceManager::GetInstance();
	Gdiplus::Bitmap* pauseBackImage = CRM->LoadBitmapResouce(L"pauseBackImage",L"image1.png");
	pauseBack->Init(pauseBackImage,Vector2{500.f,400.f});

	

	pauseBack->m_isActive = false;
	resume->m_isActive = false;
	retry->m_isActive = false;
	exit->m_isActive = false;


	SelectScnEvent* nextScnEvent = new SelectScnEvent(3);
	UITimer* myTimer = new UITimer(Vector2{910,100}, e_retry);

	UIImage* myBackGround = new UIImage();
	Gdiplus::Bitmap* waterBack = CRM->LoadBitmapResouce(L"waterImage", L"Water.png");
	myBackGround->Init(waterBack, { 640.f, 360.f });
	//UIBackGround* myBackGround = new UIBackGround();
	//myBackGround->Init(L"Water_Down_00.bmp",CRM);
	AddObject(myBackGround);
	AddObject(myTimer);
	Fish* myFish;
	srand(std::time(NULL));
	for (int i = 0; i < 16; i++) {
		myFish = new Fish();
		myFish->LoadAnimImage(L"BossFish_00.png", CRM);
		myFish->Init();
		AddObject(myFish);
		colliderManager->PushCollider(myFish->m_collider, TYPE::FISH);
	}
	
	AddObject(m_Player);
	m_Player->m_pos = { 600.f, 350.f };
	UIBackGround* myUPBackGround = new UIBackGround();
	myUPBackGround->Init(L"물결+그림자_00.png", CRM);
	AddObject(myUPBackGround);
	AddObject(pauseBack);
	AddObject(resume);
	AddObject(retry);
	AddObject(exit);
	

	alpha = 1.0f;

}

Stage01::~Stage01() {
	for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}

	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
		delete colliderManager;
}

void Stage01::Start()
{
}

void Stage01::FixedUpdate() {
	//myBackGround->FixedUpdate();
	//myUPBackGround->FixedUpdate();
}

void Stage01::Exit()
{
	for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}
		
	}
	m_arrObj.clear();
	if (colliderManager != nullptr)
	delete colliderManager;
}
