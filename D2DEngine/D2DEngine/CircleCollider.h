#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	D2D_POINT_2F m_Center;
	float m_Radius;

	// Collider��(��) ���� ��ӵ�
	bool IsCollide(Collider* pOtherComponent) override;
};

