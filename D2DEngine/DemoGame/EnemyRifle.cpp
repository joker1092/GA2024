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
	pAnimationSc->m_RelativeLocation = { 700,100 };
	pBoxCollider = CreateComponent<BoxCollider>();
	//pBoxCollider->SetParentScene(m_pRootScene);
	pBoxCollider->SetNotify(this);
	m_BoundBox.SetExtent(18, 22);
	pBoxCollider->m_collider = m_BoundBox;
}

void EnemyRifle::Update(float deltaTime)
{
	
	pBoxCollider->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x, m_pRootScene->GetWorldLocation().y);
	/*std::cout <<"ENEMY RelativeLocation()" << pAnimationSc->GetRelativeLocation().x << pAnimationSc->GetRelativeLocation().y << std::endl;
	std::cout << "ENEMY GetWorldLocation()" << pAnimationSc->GetWorldLocation().x << pAnimationSc->GetWorldLocation().y << std::endl;*/
	Charector::Update(deltaTime);
}

void EnemyRifle::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
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


