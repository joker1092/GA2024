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

//FSMState* m_pCurrentState = nullptr; //���� ����
//FSMState* m_pNextState = nullptr; //���� ����
void PlayerFSM::Update(float deltaTime)
{
	FSM::Update(deltaTime);
}

void PlayerFSM::Release()
{
}
