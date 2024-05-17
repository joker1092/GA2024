#include "SceneManager.h"

SceneManager* SceneManager::m_Instance = nullptr;

void SceneManager::Init() {
	for (int i = 0; i < (UINT)SceneType::END; i++) {
		m_sceneArr[i] = nullptr;
	}
	m_sceneArr[(UINT)SceneType::START] = new StartScene();
	m_sceneArr[(UINT)SceneType::INTRO] = new IntroScene();
	m_sceneArr[(UINT)SceneType::STAGE_01] = new Stage01();
	/*m_sceneArr[(UINT)SceneType::STAGE_02] = new Stage02();
	m_sceneArr[(UINT)SceneType::STAGE_03] = new Stage03();
	m_sceneArr[(UINT)SceneType::STAGE_04] = new Stage04();
	m_sceneArr[(UINT)SceneType::STAGE_05] = new Stage05();*/
	SetCurScene((UINT)SceneType::START);
}

void SceneManager::SetCurScene(int i) {

	if (m_curScene != nullptr)
		m_curScene->Exit();
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

void SceneManager::DestroyInstance()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}


SceneManager::~SceneManager() {
	for (int i = 0; i < (UINT)SceneType::END; i++) {
		if (m_sceneArr[i] != nullptr)
		{
			delete m_sceneArr[i];
		}

	}
}