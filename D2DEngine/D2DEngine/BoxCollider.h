#pragma once
#include "Collider.h"
class BoxCollider : public Collider
{	
public:
	D2D_RECT_F m_Rect;
	AABB m_collider;
	// Collider��(��) ���� ��ӵ�
	bool IsCollide(Collider* pOtherComponent) override;
	const AABB& GetColliderBox() const { return m_collider; }
};

