#include "framework.h"
#include "EnemyRifle.h"
#include "EnemyRifleFSM.h"
#include "EnemyRifleState.h"

void EnemyRifleFSM::Initialize()
{
	createState<EnemyRifleIdle>(std::string("EnemyRifleIdle"));
	createState<EnemyRifleMove>(std::string("EnemyRifleMove"));
	createState<EnemyRifleAttack>(std::string("EnemyRifleAttack"));
	createState<EnemyRifleDead>(std::string("EnemyRifleDead"));

	setNextState("EnemyRifleIdle");
}

void EnemyRifleFSM::Update(float deltaTime)
{
	EnemyRifle* pEnemyRifle = dynamic_cast<EnemyRifle*>(m_pOwner);
	if (pEnemyRifle->GetIsDead())
	{
		setNextState("EnemyRifleDead");
	}
	FSM::Update(deltaTime);
}

void EnemyRifleFSM::Release()
{
}
