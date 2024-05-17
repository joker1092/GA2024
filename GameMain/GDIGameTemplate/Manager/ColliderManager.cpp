#include "ColliderManager.h"

bool ColliderManager::CheckCollision(Collider* lhs, Collider* rhs) {
	if (lhs->isActive == false || rhs->isActive == false) return false;
	if (const CircleCollider* c = dynamic_cast<const CircleCollider*>(lhs)) {
		if(c->isColliding(*rhs)) {
			if(lhs->parent != nullptr)
				lhs->parent->OnTrigger();
			if (rhs->parent != nullptr)
				rhs->parent->OnTrigger();
			return true;
		}
	}
	else if(const RectangleCollider* r = dynamic_cast<const RectangleCollider*>(lhs)){
		if (r->isColliding(*rhs)) {
			if (lhs->parent != nullptr)
				lhs->parent->OnTrigger();
			if (rhs->parent != nullptr)
				rhs->parent->OnTrigger();
			return true;
		}
	}
	return false;
}

ColliderManager::ColliderManager() {
	
}

ColliderManager::~ColliderManager() {
	int k = (UINT)TYPE::END;
	for (int i = 0; i < k; i++) {
		colliders[i].clear();
	}
}
void ColliderManager::Init() {
	
}

void ColliderManager::Update() {
	/*int length = colliders.size();

	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			CheckCollision(colliders[i], colliders[j]);
		}
	}*/
}


void ColliderManager::PushCollider(Collider* collider, TYPE type) {
	colliders[(UINT)type].push_back(collider);
}

void ColliderManager::ClearColliders() {
	for (int i = 0; i < (UINT)TYPE::END; i++) {
		colliders[i].clear(); // 오류발생 가능성 있음.
	}
}

void ColliderManager::PointCollision(Vector2 point, Collider* rhs) {
	rhs->isPointColliding(point);
}

Collider* ColliderManager::GetCurrentPointCollider(Vector2 point) {
	int k = (UINT)TYPE::END;
	for (int i = k - 1; i >= 0; i--) {
		for (int j = colliders[i].size() - 1; j >= 0; j--) {
			if ((colliders[i])[j]->parent->m_isActive == false) continue;
			else {
				if ((colliders[i])[j]->isPointColliding(point)) {
					return (colliders[i])[j];
				}
			}
		}
	}
	return nullptr;
}

Collider* ColliderManager::GetCurrentPointCollider(Vector2 point, TYPE type) {
	int k = colliders[(UINT)type].size();
	if (k == 0) return nullptr;
	for (int j = k - 1; j >= 0; j--) {
		if ((colliders[(UINT)type])[j]->parent->m_isActive == false) continue;
		else {
			if ((colliders[(UINT)type])[j]->isPointColliding(point)) {
				return (colliders[(UINT)type])[j];
			}
		}
	}
	return nullptr;
}

int ColliderManager::GetCountCollidersAtType(Collider* collider, Collider** arrCollider, int length, TYPE type){
	int count = 0;
	int k = colliders[(UINT)type].size();
	if (k == 0) return count;
	for (int i = k - 1; i >= 0; i--) {
		if (colliders[(UINT)type][i]->parent->m_isActive == false) continue;
		else {
			if ((colliders[(UINT)type])[i]->isColliding(*collider)) {
				arrCollider[count] = (colliders[(UINT)type][i]);
				count++;
			}
		}
	}

	return count;
}