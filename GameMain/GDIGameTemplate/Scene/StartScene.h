#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/UIObject.h"

#include "../System/RenderSystem.h"

#include "../Manager/ColliderManager.h"
class StartScene : public CScene
{	
private:
	/*ColliderManager coll; // 이런 변수는 m_arrObj에서 관리.
	UIBackGround* myBack;
	UIButton* gameStartButton;
	UIButton* gameExitButton;*/
	// CScene을(를) 통해 상속됨
	Gdiplus::Bitmap* myBitmap = nullptr;
	RECT scoreRect;
public:
	void Init() override;
	void Start() override;
	void Exit() override;

	StartScene() {};
	~StartScene();

};

