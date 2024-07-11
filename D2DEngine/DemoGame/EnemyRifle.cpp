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
#include "Player.h"
#include "EnemyRifle.h"

EnemyRifle::EnemyRifle()
{
	m_ZOrder = ZOrder::ENEMY;
	pAnimationSc = CreateComponent<AnimationScene>();
	pEnemyRifleFSM = CreateComponent<EnemyRifleFSM>();
	pEnemyRifleFSM->Initialize();
	SetRootScene(pAnimationSc);
	pAnimationSc->LoadD2DBitmap(L"../Resource/Enemy_Rifle.png");
	pAnimationSc->LoadAnimationAsset(L"EnemyRifleIdel");
	pAnimationSc->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/EnemyRifleMove.csv");
	pAnimationSc->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/EnemyRifleAteck.csv");
	pMovement = CreateComponent<Movement>();
	pMovement->SetScene(pAnimationSc);
	pAnimationSc->SetAnimation(0, false);
	pAnimationSc->m_RelativeLocation = { 700,100 };
}

void EnemyRifle::Update(float deltaTime)
{
	Charector::Update(deltaTime);
}
