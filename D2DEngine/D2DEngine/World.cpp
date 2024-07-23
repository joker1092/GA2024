#include "framework.h"
#include "Collider.h"
#include "World.h"


World::World()
{
	// ȭ��ũ�� ������ �����ͼ�
	float width = 1920;
	float height = 1280;
	m_CullingBoundDefault.SetExtent(width / 2, height / 2);
	m_CullingBoundDefault.SetCenter(0, 0);
	SetCullingBound(&m_CullingBoundDefault);
	// ī�޶� �����Ѵ�.
	m_pCamera = new Camera();
	m_pCamera->m_RelativeLocation= {0,0};
	m_pCamera->m_RelativeTransform = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_pCamera->m_RelativeTransform;
	SetCullingBound(&m_pCamera->m_ViewBoundBox);
}

World::~World()
{
	
}


void World::Update(float deltaTime)
{
	// ī�޶��� ������Ʈ�� �����ϰ�
	m_pCamera->Update(deltaTime);
	for (auto& obj : m_GameObjects)
	{
		
		obj->Update(deltaTime);
	}
	
	// �浹üũ�� �Ѵ�.
	for (auto& obj1 : m_GameObjects)
	{ 
		Collider* pCollider1 = obj1->GetComponent<Collider>();
		if (pCollider1!=nullptr)
		{
			pCollider1->ClearCollideState();
			for (auto& obj2 : m_GameObjects)
			{
				if (obj1 == obj2) continue;
				Collider* pCollider2 = obj2->GetComponent<Collider>();
				if (pCollider2 != nullptr)
				{
					if (pCollider1->IsCollide(pCollider2)) {
						pCollider1->AddCollideStateCurr(pCollider2);
						pCollider1->ProcessBlock(pCollider2);
					}
				}
			}
			pCollider1->ProcessOverlap();
		}
	}

	// ������ ������Ʈ�� �����Ѵ�.
	for (auto& obj : m_DeleteObjects)
	{
		DeleteGameObject(obj);
	}
	m_DeleteObjects.clear();
}


bool RenderSortOrder(GameObject* a, GameObject* b)
{
	return a->m_ZOrder < b->m_ZOrder;
}


void World::Render(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* brush)
{
	// �̰� �ø� �׽�Ʈ ���� ���� Render �ϴ°�
	/*for (auto& obj : m_GameObjects){
		obj->Render(pRenderTarget);
	}*/
	// �ø� �׽�Ʈ�� �ϱ� ���ؼ�


	
	objectCount= m_GameObjects.size();
	for (auto& obj : m_GameObjects) {
		
		if ((obj->m_ZOrder==GameObject::BACKGROUND|| obj->m_ZOrder == GameObject::MAP)||m_pCullingBound->CheckIntersect(obj->m_BoundBox)) {
			m_RenderQueue.push_back(obj);
		}
	}
	std::sort(m_RenderQueue.begin(), m_RenderQueue.end(), RenderSortOrder);
	
	renderCount = m_RenderQueue.size();
	for (auto& obj : m_RenderQueue){
		obj->Render(pRenderTarget);
	}
	m_RenderQueue.clear();
}

void World::Clear()
{
	m_GameObjects.clear();
}

