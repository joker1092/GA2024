#include "../D2DEngine/D2DRender.h"
#include "framework.h"
#include "PlayerWorkState.h"
#include "PlayerWorkFSM.h"
#include "Player.h"


void PlayerWorkFSM::Initialize()
{
	createState<WorkIdle>(std::string("Idle"));
	createState<WorkMove>(std::string("Move"));
	createState<WorkJump>(std::string("Jump"));
	//createState<WorkMoveJump>(std::string("Move"));
	createState<WorkDead>(std::string("Dead"));

	setNextState("Idle");
}

void PlayerWorkFSM::Update(float deltaTime)
{
	Player* pPlayer = dynamic_cast<Player*>(m_pOwner);
	if (pPlayer->GetIsDead())
	{
		setNextState("Dead");
	}
	FSM::Update(deltaTime);
}
