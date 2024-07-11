#include "framework.h"
#include "EnemyRifleFSM.h"
#include "EnemyRifleState.h"

void EnemyRifleFSM::Initialize()
{
	createState<EnemyRifleIdle>(std::string("EnemyRifleIdle"));
	createState<EnemyRifleMove>(std::string("EnemyRifleMove"));
	createState<EnemyRifleAttack>(std::string("EnemyRifleAttack"));

	setNextState("EnemyRifleIdle");
}

void EnemyRifleFSM::Update(float deltaTime)
{
	FSM::Update(deltaTime);
}

void EnemyRifleFSM::Release()
{
}
