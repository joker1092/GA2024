#pragma once
#include "Charector.h"
class EnemyRifle : public Charector
{
	EnemyRifleFSM* pEnemyRifleFSM;
	Movement* pMovement;
	public:
	bool flip = false;
	EnemyRifle();
	virtual ~EnemyRifle() = default;
	virtual void Update(float deltaTime);
};

