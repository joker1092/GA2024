#include "framework.h"
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BitmapScene.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/Collider.h"
#include "../D2DEngine/BoxCollider.h"
#include "PlayerBodyFSM.h"
#include "PlayerWorkFSM.h"
#include "PlayerBodyScene.h"
#include "PlayerWorkScene.h"
#include "Player.h"

Player::Player()
{
	m_ZOrder =ZOrder::PLAYER;
	//Scene
	m_pRootScene = CreateComponent<Scene>(); // 루트 씬 생성
	PlayerTop = CreateComponent<PlayerBodyScene>(); // 상체 애니메이션 씬 생성
	PlayerBottom = CreateComponent<PlayerWorkScene>(); // 하체 애니메이션 씬 생성

	SetRootScene(m_pRootScene); // 상체 애니메이션을 루트로 설정
	PlayerTop->SetParentScene(m_pRootScene); // 상체 애니메이션을 루트의 자식으로 설정
	PlayerBottom->SetParentScene(m_pRootScene); // 하체 애니메이션을 상체 애니메이션의 자식으로 설정

	PlayerTop->LoadD2DBitmap(L"../Resource/Marco_trans_death.png");
	PlayerTop->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	PlayerTop->LoadAnimationAsset(L"marcoIdleTop");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveT.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpT.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(3, L"../Resource/Marco_death_defuat.csv");

	PlayerBottom->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	PlayerBottom->LoadAnimationAsset(L"marcoIdleBottom");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveB.csv");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpB.csv");
	
	//FSM
	//todo:
	//상체와 하체의 상태를 분리하여 관리
	//상체의 FSM과 하체의 FSM을 따로 생성
	//공통으로 가져야 하는 상태  => Idle, Move, Jump, Dead
	//상체만 가져야 하는 상태 => Attack, Boom, UP, Down
	//하체만 가져야 하는 상태 => MoveJump
	pPlayerBodyFSM = CreateComponent<PlayerBodyFSM>();
	pPlayerWorkFSM = CreateComponent<PlayerWorkFSM>();
	pPlayerBodyFSM->Initialize();
	pPlayerWorkFSM->Initialize();
	


	//Movement
	pMovement = CreateComponent<SideMovement>();
	pMovement->SetScene(m_pRootScene);
	
	//BoxCollider
	PlayerBox = CreateComponent<BoxCollider>();
	PlayerBox->SetParentScene(m_pRootScene);
	PlayerBox->SetNotify(this);

	//todo:
	//RootScene에 자체적인 Collider의 크기를 가질것
	//DebugDraw를 통해 확인할 수 있게 할것 
}


void Player::PlayerInit(InputSystem* in)
{
	pInput = in;
	PlayerBottom->SetAnimation(0, false);
	PlayerBottom->m_RelativeLocation = { 0, 0 };
	PlayerTop->SetAnimation(0, false);
	PlayerTop->m_RelativeLocation = { 0, 0 };
	m_pRootScene->m_RelativeLocation = { 100, 100 };
	pMovement->SetSpeed(100);
	m_BoundBox.SetExtent(18, 22);
	PlayerBox->m_collider = m_BoundBox;
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
	
	if (pInput->IsKey('0'))
	{
		isDead = true; //죽음 상태로 변경
		//todo : 차후 collision을 통해 죽음 상태로 변경
	}


	PlayerBox->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x, m_pRootScene->GetWorldLocation().y);
	Charector::Update(deltaTime);

	//PlayerBox->m_collider = m_BoundBox;
	//PlayerBox->ProcessOverlap();
	//PlayerBox->ProcessBlock(nullptr);
}

void Player::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	pMovement->EndJump();
	std::cout << "Player OnBlock" << std::endl;
}

void Player::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	std::cout << "Player OnBeginOverlap" << std::endl;
}

void Player::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	std::cout << "Player OnEndOverlap" << std::endl;
}
