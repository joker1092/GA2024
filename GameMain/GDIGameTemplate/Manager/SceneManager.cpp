#include "SceneManager.h"
SceneManager* SceneManager::m_Instance = nullptr;

void SceneManager::Init() {
	for (int i = 0; i < (UINT)SceneType::END; i++) {
		m_sceneArr[i] = nullptr;
	}
	m_sceneArr[(UINT)SceneType::START] = new StartScene();
	m_sceneArr[(UINT)SceneType::INTRO] = new IntroScene();
	m_sceneArr[(UINT)SceneType::STAGE_01] = new Stage01();
	SetCurScene((UINT)SceneType::START);
}

void SceneManager::SetCurScene(int i) {
	m_curScene = m_sceneArr[i];
	m_curScene->Init();
}

CScene* SceneManager::GetCurScene() {
	return m_curScene;
}

SceneManager* SceneManager::GetInstance() {
	if (m_Instance == nullptr) {
		m_Instance = new SceneManager();
		m_Instance->Init();
	}
	return m_Instance;
}

SceneManager::~SceneManager() {
	for (int i = 0; i < (UINT)SceneType::END; i++) {
		if (m_sceneArr[i] != nullptr)
		{
			delete m_sceneArr[i];
		}

	}
}