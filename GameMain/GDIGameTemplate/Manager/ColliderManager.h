#pragma once
#include "../stdafx.h"
#include "../GameLogic/Collider.h"
#include "../Scene/CScene.h"

class ColliderManager
{
private:
	std::vector<Collider*> colliders[(UINT)TYPE::END];
public:
	ColliderManager();
	~ColliderManager();

	void Init();
	void Update();
	
	void PushCollider(Collider* collider, TYPE type);
	void ClearColliders();

	bool CheckCollision(Collider* lhs, Collider* rhs);

	void PointCollision(Vector2 point, Collider* rhs);

	Collider* GetCurrentPointCollider(Vector2 point);

	Collider* GetCurrentPointCollider(Vector2 point, TYPE type);

	// 충돌체크할 collider와 충돌체들을 담을 arrCollider, length, 가져올 type을 이용해 colliders와 개수 리턴
	int GetCountCollidersAtType(Collider* collider, Collider** arrCollider, int length, TYPE type);
};

