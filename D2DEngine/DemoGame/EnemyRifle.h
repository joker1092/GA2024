#pragma once
#include "Charector.h"

class EnemyRifleFSM;
class Movement;
class BoxCollider;
class EnemyBulletScene;
class EnemyRifle : public Charector
{
	EnemyRifleFSM* pEnemyRifleFSM;
	SideMovement* pMovement;
	BoxCollider* pBoxCollider;
	EnemyBulletScene* pEnemyBulletScene;
public:
	bool flip = false;
	bool isDead = false;
	int blockCount = 0; //tick 당 블록 충돌 횟수

	bool isFire = true;

	float firePostDelay = 1.0f;
	float fireTime = 0.0f;
	float fireDelay = 4.0f;

	EnemyRifle();
	virtual ~EnemyRifle() = default;
	virtual void Update(float deltaTime);
	void SetIsDead(bool dead) { isDead = dead;}
	bool GetIsDead() { return isDead; }

	void EnemyFire(MathHelper::Vector2F dir);

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

};

