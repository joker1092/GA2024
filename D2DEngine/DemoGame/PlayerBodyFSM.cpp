#include "../D2DEngine/D2DRender.h"
#include "framework.h"
#include "PlayerBodyState.h"
#include "PlayerBodyFSM.h"
#include "Player.h"

void PlayerBodyFSM::Initialize()
{
	createState<BodyIdle>(std::string("Idle"));
	createState<BodyMove>(std::string("Move"));
	createState<BodyJump>(std::string("Jump"));
	//createState<BodyAttack>(std::string("Attack"));
	createState<BodyDead>(std::string("Dead"));
	setNextState("Idle");
}

void PlayerBodyFSM::Update(float deltaTime)
{
	Player* pPlayer = dynamic_cast<Player*>(m_pOwner);
	if (pPlayer->GetIsDead())
	{
		setNextState("Dead");
	}
	FSM::Update(deltaTime);
}
