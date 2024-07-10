#include "framework.h"
#include "PlayerFSM.h"
#include "PlayerState.h"

void PlayerFSM::Initialize()
{
	createState<PlayerIdle>(std::string("Idle"));
	createState<PlayerMove>(std::string("Move"));
	//createState<FSMState>(std::string("Move"));
	//createState<FSMState>(std::string("Atk"));

	setNextState("Idle");
}

//FSMState* m_pCurrentState = nullptr; //현재 상태
//FSMState* m_pNextState = nullptr; //다음 상태
void PlayerFSM::Update(float deltaTime)
{
	FSM::Update(deltaTime);
}

void PlayerFSM::Release()
{
}
