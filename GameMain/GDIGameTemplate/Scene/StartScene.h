#pragma once
#include "CScene.h"

class StartScene : public CScene
{	
private:
	/*ColliderManager coll; // �̷� ������ m_arrObj���� ����.
	UIBackGround* myBack;
	UIButton* gameStartButton;
	UIButton* gameExitButton;*/
	// CScene��(��) ���� ��ӵ�
public:
	void Init() override;
	void Start() override;
	void Exit() override;

	StartScene() {};
	~StartScene();

};

