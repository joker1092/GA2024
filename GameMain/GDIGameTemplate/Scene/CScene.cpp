#include "CScene.h"
#include "../System/TimeSystem.h"
#include "../Manager/ColliderManager.h"


void CScene::Update() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Update(High_Resolution_Time::GetDeltaTime() / 1000.0f);
	}
}

void CScene::Render() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Render(alpha);
	}
}

//void CScene::Exit() {
//	if(Game::GameManager::GetInstance()->sceneBitmap != nullptr)
//		delete Game::GameManager::GetInstance()->sceneBitmap;
//	Game::GameManager::GetInstance()->sceneBitmap = Render::GetFrontHDC();
//	//CScene::~CScene();
//	if (colliderManager != nullptr)
//		delete colliderManager;
//	
//	for (int i = 0; i < m_eventArr.size(); i++) {
//		if (m_eventArr[i] != nullptr) {
//			delete (m_eventArr[i]);
//		}
//	}
//	for (int i = 0; i < m_arrObj.size(); i++) {
//
//		if (m_arrObj[i] != nullptr) {
//			delete m_arrObj[i];
//		}
//	}
//	m_arrObj.clear();
//	m_eventArr.clear();
//}

void CScene::AddObject(Object* obj) {
	m_arrObj.push_back(obj); //이 코드 세철씨한테 물어볼 것.
}

void CScene::AddEvent(Event* evt) {
	m_eventArr.push_back(evt); //이 코드 세철씨한테 물어볼 것.
}

void CScene::FixedUpdate() {

}

CScene::~CScene() {
	if (colliderManager != nullptr) {
		int count = colliderManager->colliders->capacity();
		std::cout << count << std::endl;
	}
	//if (colliderManager != nullptr)					// 오류검출 중복제거 의심
	//	delete colliderManager;
	for (int i = 0; i < m_arrObj.size(); i++) {

		if (m_arrObj[i] != nullptr) {
			delete m_arrObj[i];
		}
	}
	for (int i = 0; i < m_eventArr.size(); i++) {

		if (m_eventArr[i] != nullptr) {
			delete m_eventArr[i];
		}
	}
	m_arrObj.clear();
	m_eventArr.clear();
};