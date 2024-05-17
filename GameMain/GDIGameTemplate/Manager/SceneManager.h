#pragma once
//#include "../Scene/CScene.h"
#include "../Scene/StartScene.h"
#include "../Scene/Stage01.h"
#include "../Scene/IntroScene.h"
#include "../Scene/Stage02.h"
#include "../Scene/Stage03.h"
#include "../Scene/Stage04.h"
#include "../Scene/Stage05.h"

class CScene;
enum class SceneType
{
	NONE,
	START,
	INTRO,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	END
};

class SceneManager
{
public:


	void Init();

	void SetCurScene(int i);

	CScene* GetCurScene();

	static SceneManager* GetInstance();

	void DestroyInstance();
	

private:
	SceneManager() {};
	~SceneManager();
	
	CScene* m_curScene;
	CScene* m_sceneArr[(UINT)SceneType::END];
	SceneType curSceneType;
	static SceneManager* m_Instance;
};

