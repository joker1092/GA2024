#include "framework.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/World.h"
#include "Enemybullet.h"

Enemybullet::Enemybullet()
{
	pBitmapSc = CreateComponent<BitmapScene>();
	pMovement = CreateComponent<Movement>();
	pCircleCollider = CreateComponent<CircleCollider>();
	pBitmapSc->LoadD2DBitmap(L"../Resource/Enemy_bullet.png");
	pBitmapSc->m_RelativeScale = { 1.5f, 1.5f };
	

	SetRootScene(pBitmapSc);
	pMovement->SetScene(pBitmapSc);
	pMovement->SetSpeed(200.0f);


	//pCircleCollider->SetParentScene(pBitmapSc);
	pCircleCollider->SetNotify(this);
	pCircleCollider->m_Center = { GetWorldLocation().x, GetWorldLocation().y };
	pCircleCollider->m_Radius = 10.0f;
	pCircleCollider->SetCollisionType(CollisionType::Blockm);
}

Enemybullet::~Enemybullet()
{
}

void Enemybullet::Initialize()
{
}

void Enemybullet::Update(float deltaTime)
{
	pCircleCollider->m_Center = { GetWorldLocation().x, GetWorldLocation().y };
	m_fLifeTime += deltaTime;
	if (m_fLifeTime > m_destroyTime)
	{
		m_pOwner->DeleteObject(this);
	}

	if (block)
	{
		//
		pBitmapSc->isVisable = false;
		pCircleCollider->SetCollisionType(CollisionType::NoCollision);
	}

	GameObject::Update(deltaTime);
}

void Enemybullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Enemybullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Enemybullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
