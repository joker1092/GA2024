#pragma once
#include "../D2DEngine/GameObject.h"

class BitmapScene;
class Movement;
class CircleCollider;
class Bullet : public GameObject
{
	BitmapScene* pBitmapSc;
	Movement* pMovement;
	CircleCollider* pCircleCollider;
	float m_fLifeTime = 0.0f;
	float m_destroyTime = 4.0f;
public:
	Bullet();
	~Bullet();
	void Initialize();
	void Update(float deltaTime);
	

	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

