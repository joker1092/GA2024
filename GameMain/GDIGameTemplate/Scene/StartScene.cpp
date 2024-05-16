#include "StartScene.h"
#include "../System/InputSystem.h"

#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	

	CResourceManager* CR = CResourceManager::GetInstance();
	myBitmap = CR->LoadBitmapResouce(L"image1",L"image1.png");
	UIImage* myBack = new UIImage(); // ��ü �׽�Ʈ
	myBack->Init(myBitmap, { 500.f,400.f });

	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // ����ȯ �̺�Ʈ �׽�Ʈ
	UIButton* gameStartButton = new UIButton(Vector2{800.0f,600.0f},nextScnEvent); // ��ü �׽�Ʈ
	
	AddObject(myBack);
	AddObject(gameStartButton);

	ExitEvent* e_exit = new ExitEvent;
	UIButton* exit = new UIButton(Vector2{ 100,1000 }, e_exit);
	AddObject(exit);

	alpha = 1.0f;
}

StartScene::~StartScene() {

}

void StartScene::Exit() 
{
	for (int i = 0; i < m_arrObj.size(); i++) {
		/*if (m_arrObj[i]->m_Event != nullptr) {


		}*/
		delete m_arrObj[i];
	}
	m_arrObj.clear();
	if(colliderManager != nullptr)
	delete colliderManager;
}
