#pragma once
#include "Charector.h"

class EnemyRifleFSM;
class Movement;
class BoxCollider;
class EnemyRifle : public Charector
{
	EnemyRifleFSM* pEnemyRifleFSM;
	Movement* pMovement;
	BoxCollider* pBoxCollider;
public:
	bool flip = false;
	bool isDead = false;
	EnemyRifle();
	virtual ~EnemyRifle() = default;
	virtual void Update(float deltaTime);
	void SetIsDead(bool dead) { isDead = dead; }
	bool GetIsDead() { return isDead; }

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

