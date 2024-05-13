#include <vector>
#include "Collider.h"
#pragma once
class ColliderManager
{
private:
	std::vector<Collider*> colliders;

	bool CheckCollision(Collider* lhs , Collider* rhs);
public:
	ColliderManager();

	void Init();
	void Update();
	
	void PushCollider();
	void ClearColliders();

	bool IsCollide();
};

