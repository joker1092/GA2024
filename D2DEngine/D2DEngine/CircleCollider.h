#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	CircleCollider() { m_ColliderType = ColliderType::Circle; }
	D2D_POINT_2F m_Center;
	float m_Radius;

	// Collider��(��) ���� ��ӵ�
	bool IsCollide(Collider* pOtherComponent) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

