#include "framework.h"
#include "../D2DEngine/D2DRender.h"
#include "AABB.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

bool BoxCollider::IsCollide(Collider* pOtherComponent)
{
	if (pOtherComponent->GetColliderType() == ColliderType::Box) {
		BoxCollider* pBoxCollider = dynamic_cast<BoxCollider*>(pOtherComponent);
		if (!m_collider.CheckIntersect(pBoxCollider->m_collider)) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (pOtherComponent->GetColliderType() == ColliderType::Circle) {
		CircleCollider* pCircleCollider = dynamic_cast<CircleCollider*>(pOtherComponent);
		// 원의 중심과 사각형의 각 변에 대해 가장 가까운 점 찾기
		float closestX = Utill::Clamp(pCircleCollider->m_Center.x, m_collider.m_Center.x - m_collider.m_Extent.x, m_collider.m_Center.x + m_collider.m_Extent.x);
		float closestY = Utill::Clamp(pCircleCollider->m_Center.y, m_collider.m_Center.y - m_collider.m_Extent.y, m_collider.m_Center.y + m_collider.m_Extent.y);
		// 원의 중심과 가장 가까운 점 사이의 거리 계산
		float distance = Utill::Distance(pCircleCollider->m_Center, { closestX, closestY });
		if (distance < pCircleCollider->m_Radius) {
			return true;
		}
	}
    return false;
}

void BoxCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_Rect = D2D1::RectF(m_collider.m_Center.x - m_collider.m_Extent.x, m_collider.m_Center.y - m_collider.m_Extent.y, m_collider.m_Center.x + m_collider.m_Extent.x, m_collider.m_Center.y + m_collider.m_Extent.y);
	D2D1_MATRIX_3X2_F m_ScreenTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(0.0f, D2DRender::Instance->GetClientSize().height);
	D2D1_MATRIX_3X2_F Transform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_WorldTransform * pD2DRender->m_CameraTransform * m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawRectangle(m_Rect, D2DRender::Instance->RedBrush());
}
