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
	/*UIBackGround* myBack; // 이런 변수는 m_arrObj에서 관리.
	Player* m_Player; */
	//UIBackGround* myBackGround; //fixedUpdate 처리해야해서 부득이하게 선언.
	//UIBackGround* myUPBackGround;
public:
	// CScene을(를) 통해 상속됨
	void Init() override;
	void Start() override;
	void Exit() override;
	void FixedUpdate() override;

	Stage04() {};
	~Stage04();
};

