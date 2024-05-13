#include "Stage01.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../GameLogic/Objects/Player.h"
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
