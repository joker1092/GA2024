#pragma once
#include "../D2DEngine/D2DRender.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
class FSMState;
class PlayerFSM :  public FSM
{
	public:
	PlayerFSM()=default;
	~PlayerFSM()=default;
	void Initialize();
	void Update(float deltaTime);
	void Release();
};

