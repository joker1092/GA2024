#pragma once
#include "../stdafx.h"
#include "../GameLogic/Collider.h"
class ColliderManager
{
private:
	std::vector<Collider*> colliders;
public:
	ColliderManager();
	~ColliderManager();

	void Init();
	void Update();
	
	void PushCollider(Collider* collider);
	void ClearColliders();

	bool CheckCollision(Collider* lhs, Collider* rhs);

	void PointCollision(Vector2 point, Collider* rhs);
};

