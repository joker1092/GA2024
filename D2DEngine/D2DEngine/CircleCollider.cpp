#include "framework.h"
#include "../D2DEngine/D2DRender.h"
#include "AABB.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


bool CircleCollider::IsCollide(Collider* pOtherComponent)
{
	if (pOtherComponent->GetColliderType() == ColliderType::Circle) {
		CircleCollider* pCircleCollider = dynamic_cast<CircleCollider*>(pOtherComponent);
		float distance = Utill::Distance(m_Center,pCircleCollider->m_Center);
		if (distance < m_Radius + pCircleCollider->m_Radius) {
			return true;
		}
	}
	else if (pOtherComponent->GetColliderType() == ColliderType::Box) {
		BoxCollider* pBoxCollider = dynamic_cast<BoxCollider*>(pOtherComponent);
		AABB BoxAABB = pBoxCollider->GetColliderBox();
		// ���� �߽ɰ� �簢���� �� ���� ���� ���� ����� �� ã��
		float closestX = Utill::Clamp(m_Center.x, BoxAABB.m_Center.x - BoxAABB.m_Extent.x, BoxAABB.m_Center.x + BoxAABB.m_Extent.x);
		float closestY = Utill::Clamp(m_Center.y, BoxAABB.m_Center.y - BoxAABB.m_Extent.y, BoxAABB.m_Center.y + BoxAABB.m_Extent.y);
		// ���� �߽ɰ� ���� ����� �� ������ �Ÿ� ���
		float distance = Utill::Distance(m_Center, { closestX, closestY });
		if (distance < m_Radius) {
			return true;
		}
		return false;
	}
}

void CircleCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->DrawEllipse(D2D1::Ellipse(m_Center, m_Radius, m_Radius), D2DRender::Instance->RedBrush());
}
