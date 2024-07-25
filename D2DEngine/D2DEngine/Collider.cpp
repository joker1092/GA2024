#include "framework.h"
#include "Collider.h"

void Collider::ClearCollideState()
{
	m_CollideStatePrev = m_CollideStateCurr;
	m_CollideStateCurr.clear();
}

//void Collider::ProcessOverlap()
//{
//	for (auto& pColliderComponent : m_CollideStateCurr)
//	{
//		if (m_CollideStatePrev.find(pColliderComponent)==m_CollideStatePrev.end())
//		{
//			if(m_pNotify)
//				m_pNotify->OnBeginOverlap(this, pColliderComponent);
//		}
//	}
//
//	for (auto& pColliderComponent : m_CollideStatePrev)
//	{
//		if (m_CollideStateCurr.find(pColliderComponent) == m_CollideStateCurr.end())
//		{
//			if (m_pNotify)
//				m_pNotify->OnEndOverlap(this, pColliderComponent);
//		}
//	}
//
//}
void Collider::ProcessOverlap()
{
    for (auto& pColliderComponent : m_CollideStateCurr)
    {
        if (m_CollideStatePrev.find(pColliderComponent) == m_CollideStatePrev.end())
        {
            if (m_pNotify && pColliderComponent && !IsBadReadPtr(pColliderComponent, sizeof(Collider)))
                m_pNotify->OnBeginOverlap(this, pColliderComponent);
        }
    }

    for (auto& pColliderComponent : m_CollideStatePrev)
    {
        if (m_CollideStateCurr.find(pColliderComponent) == m_CollideStateCurr.end())
        {
            if (m_pNotify && pColliderComponent && !IsBadReadPtr(pColliderComponent, sizeof(Collider)))
                m_pNotify->OnEndOverlap(this, pColliderComponent);
        }
    }
}



void Collider::ProcessBlock(Collider* pOtherComponent)
{
	for (auto& pColliderComponent : m_CollideStateCurr) {
		if (pColliderComponent == pOtherComponent) {
			if (m_pNotify)
				m_pNotify->OnBlock(this, pColliderComponent);
		}
	}
}

void Collider::Render(ID2D1RenderTarget* pRenderTarget)
{
	
}
