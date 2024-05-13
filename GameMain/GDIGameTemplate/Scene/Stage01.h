#pragma once
#include "CScene.h"

class Stage01 : public CScene
{
private:
	/*UIBackGround* myBack; // 이런 변수는 m_arrObj에서 관리.
	Player* m_Player; */

public:
	// CScene을(를) 통해 상속됨
	void Init() override;
	void Start() override;
	void Exit() override;

	Stage01() {};
	~Stage01();
};

