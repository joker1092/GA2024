#pragma once
#include "CScene.h"
#include "RenderSystem.h"
class StartScene : public CScene
{
	void Update() override {
		
	}
	void Render(HDC hdc) override {
		Render::DrawRect(0, 0, 100, 100, RGB(255, 0, 0));
	}
	// CScene��(��) ���� ��ӵ�
public:
	virtual void Start() override;

	virtual void Exit() override;
	StartScene() {};
	~StartScene() {};
};

