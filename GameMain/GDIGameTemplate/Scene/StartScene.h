#pragma once
#include "CScene.h"
#include "../GameLogic/Objects/UIObject.h"

#include "../System/RenderSystem.h"

#include "../Manager/ColliderManager.h"
class StartScene : public CScene
{	
private:
	/*ColliderManager coll; // �̷� ������ m_arrObj���� ����.
	UIBackGround* myBack;
	UIButton* gameStartButton;
	UIButton* gameExitButton;*/
	// CScene��(��) ���� ��ӵ�
	Gdiplus::Bitmap* myBitmap = nullptr;
	RECT scoreRect;
public:
	void Init() override;
	void Start() override;
	void Exit() override;

	StartScene() {};
	~StartScene();

};

