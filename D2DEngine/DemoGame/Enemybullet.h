#pragma once

//적이 발사하는 총알

#include "../D2DEngine/GameObject.h"
class BitmapScene;
class Movement;
class CircleCollider;

class Enemybullet : public GameObject{
	BitmapScene* pBitmapSc;
	Movement* pMovement;
	CircleCollider* pCircleCollider;
	float m_fLifeTime = 0.0f;
	float m_destroyTime = 4.0f;

	bool block = false;

public:
	Enemybullet();
	~Enemybullet();
	void Initialize();
	void Update(float deltaTime);

	void SetDirection(MathHelper::Vector2F dir) { pMovement->SetDirection(dir); }

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

