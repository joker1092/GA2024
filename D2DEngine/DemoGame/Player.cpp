#include "framework.h"
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/InputSystem.h"
#include "Player.h"

Player::Player()
{
	m_ZOrder =ZOrder::PLAYER;
	PlayerTop = CreateComponent<AnimationScene>();
	PlayerBottom =CreateComponent<AnimationScene>();
	pPlayerFSM = CreateComponent<PlayerFSM>();
	pPlayerFSM->Initialize();
	SetRootScene(PlayerTop); // 상체 애니메이션을 루트로 설정
	PlayerBottom->SetParentScene(PlayerTop); // 하체 애니메이션을 상체 애니메이션의 자식으로 설정
	PlayerTop->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	PlayerTop->LoadAnimationAsset(L"marcoIdleTop");
	//animeScenePlayer->pAnimationAsset->LoadAnimationFromFile(0, L"marcoIdleTop");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveT.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpT.csv");

	//animeScenePlayer->LoadAnimationAsset(L"Marco_MoveT");
	//animeScenePlayer->LoadAnimationAsset(L"Marco_JumpT");
	PlayerBottom->LoadAnimationAsset(L"marcoIdleBottom");
	//animePlayerbottom->pAnimationAsset->LoadAnimationFromFile(0, L"marcoIdleBottom");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveB.csv");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpB.csv");
	PlayerBottom->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	
		
	pMovement = CreateComponent<SideMovement>();
	pMovement->SetScene(PlayerTop);
	
}


void Player::PlayerInit(InputSystem* in)
{
	pInput = in;
	PlayerBottom->SetAnimation(0, false);
	PlayerBottom->m_RelativeLocation = { 0, 0 };
	PlayerTop->SetAnimation(0, false);
	PlayerTop->m_RelativeLocation = { 100, 100};
	pMovement->SetSpeed(100);
}

void Player::Update(float deltaTime)
{
	//pMovement->SetDirection({ 0,0 });
	pMovement->SetSpeed(0);
	if (pInput->IsKey(VK_LEFT))
	{
		pMovement->SetDirection({ -1,0 });
		//m_pWorld->GetCamera()->m_RelativeLocation.x -= 1;
		pMovement->SetSpeed(100);
	}
	if (pInput->IsKey(VK_RIGHT))
	{
		pMovement->SetDirection({ 1,0 });
		//m_pWorld->GetCamera()->m_RelativeLocation.x += 1;
		pMovement->SetSpeed(100);
	}
	if (pInput->IsKey(VK_UP))
	{
		//pMovement->SetDirection({ 0,1 });
		////m_pWorld->GetCamera()->m_RelativeLocation.y += 1;
		//pMovement->SetSpeed(100);
	}
	if (pInput->IsKey(VK_DOWN))
	{
		//pMovement->SetDirection({ 0,-1 });
		////m_pWorld->GetCamera()->m_RelativeLocation.y -= 1;
		//pMovement->SetSpeed(100);
	}

	if (pInput->IsKey(VK_SPACE))
	{
		pMovement->Jump();
	}
	


	Charector::Update(deltaTime);
}
