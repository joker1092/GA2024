#pragma once
#include "CScene.h"
//#include "../GameLogic/Objects/Object.h"
#include "../GameLogic/Objects/Player.h"

class UIImage;
//class Player;
class UIBackGround;
class Stage04 : public CScene
{
private:
	/*UIBackGround* myBack; // �̷� ������ m_arrObj���� ����.
	Player* m_Player; */
	//UIBackGround* myBackGround; //fixedUpdate ó���ؾ��ؼ� �ε����ϰ� ����.
	//UIBackGround* myUPBackGround;
public:
	// CScene��(��) ���� ��ӵ�
	void Init() override;
	void Start() override;
	void Exit() override;
	void FixedUpdate() override;

	Stage04() {};
	~Stage04();
};

