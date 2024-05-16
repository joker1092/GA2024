#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Fish.h"
#include "../System/TimeSystem.h"
#include "../GameLogic/Event.h"
void Stage01::Init()
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
	myUPBackGround->Init(L"����+�׸���_00.png", CRM);
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
