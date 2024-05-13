#include "StartScene.h"
#include "../System/InputSystem.h"
#include "../GameLogic/Objects/UIObject.h"
#include "../System/RenderSystem.h"
#include "../Manager/ColliderManager.h"
#include "../GameLogic/Event.h"
void StartScene::Start() 
{

}

void StartScene::Init()
{	
	UIBackGround* myBack = new UIBackGround(); // 객체 테스트
	SelectScnEvent* nextScnEvent = new SelectScnEvent(2); // 씬전환 이벤트 테스트
	UIButton* gameStartButton = new UIButton(Vector2{1600.0f,800.0f},nextScnEvent); // 객체 테스트
	
	AddObject(myBack);
	AddObject(gameStartButton);
}

StartScene::~StartScene() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		delete m_arrObj[i];
	}
}

void StartScene::Exit() 
{

}
