#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Player.h"
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
	Player* m_Player = new Player();
	AddObject(m_Player);
	SelectScnEvent* nextScnEvent = new SelectScnEvent(3);
	UITimer* myTimer = new UITimer(Vector2{910,100}, nextScnEvent);
	AddObject(myTimer);
	Fish* myFish;
	for (int i = 0; i < 20; i++) {
		myFish = new Fish();
		myFish->Init();
		myFish->m_pos = { 300.f, 300.f };
		AddObject(myFish);
	}
	
}

Stage01::~Stage01() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		delete m_arrObj[i];
	}
}

void Stage01::Start()
{
}

void Stage01::Exit()
{
	
}
