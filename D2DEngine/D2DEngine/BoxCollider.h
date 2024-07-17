#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{	
public:
	BoxCollider() { m_ColliderType = ColliderType::Box; }
	D2D_RECT_F m_Rect;
	AABB m_collider;
	// Collider을(를) 통해 상속됨
	bool IsCollide(Collider* pOtherComponent) override;
	const AABB& GetColliderBox() const { return m_collider; }
};

