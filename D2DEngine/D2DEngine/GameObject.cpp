#include "framework.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (auto& pComponent : m_OwnedComponents)
	{
		delete pComponent;
	}
	m_OwnedComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Update(deltaTime);
	}

	if (m_pRootScene) {
		m_BoundBox.m_Extent = { m_pRootScene->width / 2, m_pRootScene->height / 2 };
		float x = m_pRootScene->GetWorldLocation().x + m_pRootScene->width / 2;
		float y = m_pRootScene->GetWorldLocation().y + m_pRootScene->height / 2;
		//m_BoundBox.m_Center = m_pRootScene->GetWorldLocation();
		m_BoundBox.m_Center = { x,y };
	}	
}

void GameObject::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& pComponent : m_OwnedComponents)
	{
		pComponent->Render(pRenderTarget);
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	m_OwnedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{
	D2D1_VECTOR_2F temp{ 0,0 };
	if (m_pRootScene)
		temp = m_pRootScene->GetWorldLocation();

	return temp;
}

void GameObject::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void GameObject::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void GameObject::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
