#include "framework.h"
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
		// 원의 중심과 사각형의 각 변에 대해 가장 가까운 점 찾기
		float closestX = Utill::Clamp(m_Center.x, BoxAABB.m_Center.x - BoxAABB.m_Extent.x, BoxAABB.m_Center.x + BoxAABB.m_Extent.x);
		float closestY = Utill::Clamp(m_Center.y, BoxAABB.m_Center.y - BoxAABB.m_Extent.y, BoxAABB.m_Center.y + BoxAABB.m_Extent.y);
		// 원의 중심과 가장 가까운 점 사이의 거리 계산
		float distance = Utill::Distance(m_Center, { closestX, closestY });
	}
    return false;
}
