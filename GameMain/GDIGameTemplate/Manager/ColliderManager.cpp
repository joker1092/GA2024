#include "ColliderManager.h"

bool ColliderManager::CheckCollision(Collider* lhs, Collider* rhs) {
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

void ColliderManager::PushCollider(Collider* collider) {
	colliders.push_back(collider);
}

void ColliderManager::ClearColliders() {
	colliders.clear(); // 오류발생 가능성 있음.
}

void ColliderManager::PointCollision(Vector2 point, Collider* rhs) {
	rhs->isPointColliding(point);
}