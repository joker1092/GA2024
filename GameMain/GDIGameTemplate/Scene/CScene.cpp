#include "CScene.h"
#include "../System/TimeSystem.h"

void CScene::Update() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Update(High_Resolution_Time::GetDeltaTime() / 1000.f);
		std::cout << (High_Resolution_Time::GetDeltaTime() / 1000.f) << std::endl;
	}
}

void CScene::Render() {
	for (int i = 0; i < m_arrObj.size(); i++) {
		m_arrObj[i]->Render();
	}
}

void CScene::AddObject(Object* obj) {
	m_arrObj.push_back(obj); //�� �ڵ� ��ö������ ��� ��.
}

void CScene::FixedUpdate() {

}