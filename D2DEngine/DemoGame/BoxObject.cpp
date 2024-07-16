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
	m_pBoxCollider->m_collider = m_BoundBox;
}

void BoxObject::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_pBoxCollider->m_collider = m_BoundBox;
}
