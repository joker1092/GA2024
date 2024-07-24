#pragma once
#include "Charector.h"

class EnemyRifleFSM;
class Movement;
class BoxCollider;
class EnemyRifle : public Charector
{
	EnemyRifleFSM* pEnemyRifleFSM;
	SideMovement* pMovement;
	BoxCollider* pBoxCollider;
public:
	bool flip = false;
	bool isDead = false;
	int blockCount = 0; //tick �� ��� �浹 Ƚ��
	EnemyRifle();
	virtual ~EnemyRifle() = default;
	virtual void Update(float deltaTime);
	void SetIsDead(bool dead) { isDead = dead; }
	bool GetIsDead() { return isDead; }

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

