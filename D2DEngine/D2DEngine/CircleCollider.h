#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{
public:
	CircleCollider() { m_ColliderType = ColliderType::Circle; }
	D2D_POINT_2F m_Center;
	float m_Radius;

	// Collider을(를) 통해 상속됨
	bool IsCollide(Collider* pOtherComponent) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

