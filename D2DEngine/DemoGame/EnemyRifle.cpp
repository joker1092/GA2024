#include "framework.h"
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/BoxCollider.h"
#include "Bullet.h"
#include "Player.h"
#include "EnemyBulletScene.h"
#include "EnemyRifle.h"

EnemyRifle::EnemyRifle()
{
	m_ZOrder = ZOrder::ENEMY;
	pAnimationSc = CreateComponent<AnimationScene>();
	SetRootScene(pAnimationSc);
	pAnimationSc->LoadD2DBitmap(L"../Resource/Rebel_Soldier_Default.png.png");
	pAnimationSc->LoadD2DBitmap(L"../Resource/Enemy_Rifle.png");
	pAnimationSc->LoadAnimationAsset(L"EnemyRifleIdel");
	pAnimationSc->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/EnemyRifleMove.csv");
	pAnimationSc->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/EnemyRifleAteck.csv");
	pAnimationSc->pAnimationAsset->LoadAnimationFromFile(3, L"../Resource/EnemyDead.csv");
	pMovement = CreateComponent<SideMovement>();
	pMovement->SetScene(pAnimationSc);
	pMovement->SetSpeed(50);
	pAnimationSc->SetAnimation(0, false);
	pEnemyRifleFSM = CreateComponent<EnemyRifleFSM>();
	pEnemyRifleFSM->Initialize();
	//pAnimationSc->m_RelativeLocation = { 700,100 };
	pBoxCollider = CreateComponent<BoxCollider>();
	//pBoxCollider->SetParentScene(m_pRootScene);
	pBoxCollider->SetNotify(this);
	m_BoundBox.SetExtent(18, 22);
	pBoxCollider->m_collider = m_BoundBox;
	pBoxCollider->SetCollisionType(CollisionType::Blockm);
	pEnemyBulletScene = CreateComponent<EnemyBulletScene>();
	pEnemyBulletScene->SetParentScene(pAnimationSc);
}

void EnemyRifle::Update(float deltaTime)
{
	
	pBoxCollider->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x, m_pRootScene->GetWorldLocation().y);
	/*std::cout <<"ENEMY RelativeLocation()" << pAnimationSc->GetRelativeLocation().x << pAnimationSc->GetRelativeLocation().y << std::endl;
	std::cout << "ENEMY GetWorldLocation()" << pAnimationSc->GetWorldLocation().x << pAnimationSc->GetWorldLocation().y << std::endl;*/

	if (blockCount > 0) {
		pMovement->SetGravityScale(0);
		pMovement->ResetGravity();
	}
	else {
		pMovement->SetGravityScale(50);
		pMovement->ResetGravity();
	}

	Charector::Update(deltaTime);

	blockCount = 0; 
}

void EnemyRifle::EnemyFire(MathHelper::Vector2F dir)
{
	if (!isDead) {
		if (isFire)
		{
			pEnemyBulletScene ->CreateBullet(dir);
		}
	}
}

void EnemyRifle::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	GameObject* pOtherOwner = pOtherComponent->GetOwner();
	if (pOtherOwner->m_ZOrder == ZOrder::OBJECT)
	{
		pMovement->EndJump();
		blockCount++;
	}
	Bullet* bullet = dynamic_cast<Bullet*>(pOtherComponent->GetOwner());
	if (bullet == nullptr) return;

	isDead = true;
}

void EnemyRifle::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void EnemyRifle::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}


