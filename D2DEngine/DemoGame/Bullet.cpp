#include "framework.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/World.h"
#include "Bullet.h"

Bullet::Bullet()
{
	pBitmapSc = CreateComponent<BitmapScene>();
	pMovement = CreateComponent<Movement>();
	pCircleCollider = CreateComponent<CircleCollider>();
	pBitmapSc->LoadD2DBitmap(L"../Resource/player_default_bullet_trance.png");

	SetRootScene(pBitmapSc);
	pMovement->SetScene(pBitmapSc);
	pMovement->SetSpeed(200.0f);
	

	//pCircleCollider->SetParentScene(pBitmapSc);
	pCircleCollider->SetNotify(this);
	pCircleCollider->m_Center = { GetWorldLocation().x, GetWorldLocation().y };
	pCircleCollider->m_Radius = 10.0f;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{

}

void Bullet::Update(float deltaTime)
{
	pCircleCollider->m_Center = { GetWorldLocation().x, GetWorldLocation().y };
	m_fLifeTime += deltaTime;
	if (m_fLifeTime > m_destroyTime)
	{
		m_pOwner->DeleteObject(this);
	}
	GameObject::Update(deltaTime);
}

void Bullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	GameObject* pOtherOwner = pOtherComponent->GetOwner();
	if (pOtherOwner->m_ZOrder == ZOrder::ENEMY)
	{
		m_pOwner->DeleteObject(this);
	}
}

void Bullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
