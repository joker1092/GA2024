#pragma once
#include "CScene.h"

class Stage01 : public CScene
{
private:
	/*UIBackGround* myBack; // �̷� ������ m_arrObj���� ����.
	Player* m_Player; */

public:
	// CScene��(��) ���� ��ӵ�
	void Init() override;
	void Start() override;
	void Exit() override;

	Stage01() {};
	~Stage01();
};

