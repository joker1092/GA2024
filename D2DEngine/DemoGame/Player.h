#pragma once
#include "Charector.h"

//GameObject를 상속 받은 Charector를 상속받은 플레이어 클레스
class InputSystem;
class Player :   public Charector
{
	AnimationScene* PlayerTop; //플레이어 상체 애니메이션
	AnimationScene* PlayerBottom; //플레이어 하체 애니메이션
	PlayerFSM* pPlayerFSM;
public:
	InputSystem* pInput;
	bool flip = false;
	Player(); 
	virtual ~Player() = default;
	void PlayerInit(InputSystem* in);
	virtual void Update(float deltaTime);
};

