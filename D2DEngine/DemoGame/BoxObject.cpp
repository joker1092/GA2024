#include "framework.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/BoxCollider.h"
#include "BoxObject.h"

BoxObject::BoxObject()
{
	m_ZOrder = ZOrder::OBJECT;
	m_pBitmapScene = CreateComponent<BitmapScene>();
	m_pBoxCollider = CreateComponent<BoxCollider>();
	m_pBitmapScene->LoadD2DBitmap(L"../Resource/Object/Crate.png");
	SetRootScene(m_pBitmapScene);
	m_pBoxCollider->SetParentScene(m_pBitmapScene);
	m_BoundBox.m_Extent = { 30, 30 };
	m_pBoxCollider->m_collider = m_BoundBox;	

}

void BoxObject::Update(float deltaTime)
{
	float x = m_pBoxCollider->m_collider.m_Extent.x;
	float y = m_pBoxCollider->m_collider.m_Extent.y;
	m_pBoxCollider->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x+x, m_pRootScene->GetWorldLocation().y-y);
	GameObject::Update(deltaTime);
	//m_pBoxCollider->m_collider = m_BoundBox;
}
