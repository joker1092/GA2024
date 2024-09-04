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
#include "FireScene.h"
#include "Enemybullet.h"
#include "Player.h"

Player::Player()
{
	m_ZOrder =ZOrder::PLAYER;
	//Scene
	m_pRootScene = CreateComponent<Scene>(); // 루트 씬 생성
	PlayerTop = CreateComponent<PlayerBodyScene>(); // 상체 애니메이션 씬 생성
	PlayerBottom = CreateComponent<PlayerWorkScene>(); // 하체 애니메이션 씬 생성
	pFireScene = CreateComponent<FireScene>(); // 총 발사 씬 생성

	SetRootScene(m_pRootScene); // 상체 애니메이션을 루트로 설정
	PlayerTop->SetParentScene(m_pRootScene); // 상체 애니메이션을 루트의 자식으로 설정
	PlayerBottom->SetParentScene(m_pRootScene); // 하체 애니메이션을 상체 애니메이션의 자식으로 설정

	PlayerTop->LoadD2DBitmap(L"../Resource/Marco_trans_death.png");
	PlayerTop->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	PlayerTop->LoadAnimationAsset(L"marcoIdleTop");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveT.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpT.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(3, L"../Resource/Marco_death_defuat.csv");
	PlayerTop->pAnimationAsset->LoadAnimationFromFile(4, L"../Resource/Marco_pistol_atk.csv");

	PlayerBottom->LoadD2DBitmap(L"../Resource/Marco_trans0.png");
	PlayerBottom->LoadAnimationAsset(L"marcoIdleBottom");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(1, L"../Resource/Marco_MoveB.csv");
	PlayerBottom->pAnimationAsset->LoadAnimationFromFile(2, L"../Resource/Marco_JumpB.csv");
	
	pFireScene->SetParentScene(PlayerTop);
	pFireScene->SetRelativeLocation({ 30, 20 });
	//FSM
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
	PlayerBox->SetCollisionType(CollisionType::Blockm);

	PlayerPlate = CreateComponent<BoxCollider>();
	PlayerPlate->SetParentScene(m_pRootScene);
	PlayerPlate->SetNotify(this);
	PlayerPlate->SetCollisionType(CollisionType::Blockm);
	//todo:
	
	
	setDelay(0.2f);
	
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
	//m_BoundBox.SetExtent(18, 18);
	//PlayerBox->m_collider = m_BoundBox;
	PlayerBox->m_RelativeLocation = { 9,20 };
	PlayerBox->m_collider.SetExtent(16, 18);
	PlayerPlate->m_RelativeLocation = { 9, -15 };
	PlayerPlate->m_collider.SetExtent(10, 5);
	
}

void Player::Update(float deltaTime)
{
	//pMovement->SetDirection({ 0,0 });
	pMovement->SetSpeed(0);
	
	if (fireDelay > delay) {
		isFire = true;
	}
	fireDelay += deltaTime;

	if (!isDead) {

		if (pInput->IsKey(VK_LEFT)) 
		{
			pMovement->SetDirection({ -1,0 });
			//m_pWorld->GetCamera()->m_RelativeLocation.x -= 1;
			pMovement->SetSpeed(400);
		}
		if (pInput->IsKey(VK_RIGHT))
		{
			pMovement->SetDirection({ 1,0 });
			//m_pWorld->GetCamera()->m_RelativeLocation.x += 1;
			pMovement->SetSpeed(400);
		}
		//if (pInput->IsKey(VK_UP))
		//{
		//	//pMovement->SetDirection({ 0,1 });
		//	////m_pWorld->GetCamera()->m_RelativeLocation.y += 1;
		//	//pMovement->SetSpeed(100);
		//}
		//if (pInput->IsKey(VK_DOWN))
		//{
		//	//pMovement->SetDirection({ 0,-1 });
		//	////m_pWorld->GetCamera()->m_RelativeLocation.y -= 1;
		//	//pMovement->SetSpeed(100);
		//}

		if (pInput->IsKey(VK_SPACE))
		{
			//pMovement->Jump();
			if (pInput->IsKey(VK_DOWN))
			{
				pMovement->DownJump();
			}
			else {
				pMovement->Jump();
			}
		}

		if (pInput->IsKey('Z')|| pInput->IsKey('z'))
		{
			pPlayerBodyFSM->setNextState("Attack");
		}


		if (pInput->IsKey('0'))
		{
			isDead = true; //죽음 상태로 변경
			//todo : 차후 collision을 통해 죽음 상태로 변경
		}
	}
	

	PlayerPlate->m_collider.SetCenter(PlayerPlate->GetWorldLocation().x, PlayerPlate->GetWorldLocation().y);
	//PlayerPlate->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x, m_pRootScene->GetWorldLocation().y+40);
	//PlayerBox->m_collider.SetCenter(m_pRootScene->GetWorldLocation().x, m_pRootScene->GetWorldLocation().y);
	PlayerBox->m_collider.SetCenter(PlayerBox->GetWorldLocation().x, PlayerBox->GetWorldLocation().y);
	if (blockCount > 0) {
		pMovement->SetGravityScale(0);
		pMovement->ResetGravity();
	}
	else {
		pMovement->SetGravityScale(50);
		pMovement->ResetGravity();
	}
	//pMovement->ResetGravity();
	
	Charector::Update(deltaTime);

	//PlayerBox->m_collider = m_BoundBox;
	//PlayerBox->ProcessOverlap();
	//PlayerBox->ProcessBlock(nullptr);
	
	//블록카운트 초기화
	blockCount = 0;
}

void Player::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	GameObject* pOtherOwner = pOtherComponent->GetOwner();
	//std::cout << "Player OnBlock" << std::endl;
	if (pOwnedComponent == PlayerBox) {
		//적 총알과 충돌시 죽음
		Enemybullet* bullet = dynamic_cast<Enemybullet*>(pOtherComponent->GetOwner());

		if (bullet != nullptr) {
			isDead = true;
		}
		//std::cout << "Player PlayerBox OnBlock" << std::endl;
	}

	if (pOwnedComponent == PlayerPlate) {
		if (pOtherOwner->m_ZOrder == ZOrder::OBJECT)
		{
			std::cout << "Player PlayerPlate OnBlock" << std::endl;
			pMovement->EndJump();
			blockCount++;
		}
	}
}

void Player::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	GameObject* pOtherOwner = pOtherComponent->GetOwner();
	//PlayerBox RayCast 를 통한 선 충돌 확인을 하고 싶다
	//RayCast를 통해 충돌한 오브젝트의 위치를 받아오고 싶다
	//
	if (pOwnedComponent == PlayerBox) {
		if (pOtherOwner->m_ZOrder == ZOrder::OBJECT) {
			pMovement->EndJump();
			pMovement->SetIsMoving(true);
			std::cout << "Player PlayerBox OnBeginOverlap" << std::endl;	
		}
	}
	//std::cout << "Player OnBeginOverlap" << std::endl;
}

void Player::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{

	GameObject* pOtherOwner = pOtherComponent ? pOtherComponent->GetOwner() : nullptr;
	if (pOtherOwner == nullptr || IsBadReadPtr(pOtherOwner, sizeof(GameObject))) {
		// 오류 처리 또는 조기 반환
		return;
	}

	if (pOwnedComponent == PlayerBox) {
		std::cout << "Player PlayerBox OnEndOverlap" << std::endl;
		if (pOtherOwner->m_ZOrder == ZOrder::OBJECT) {
			pMovement->SetIsMoving(false);
			std::cout << "Player PlayerBox OnBeginOverlap" << std::endl;

		}
	}
	//std::cout << "Player OnEndOverlap" << std::endl;
	/*pMovement->SetGravityScale(100);
	pMovement->ResetGravity();*/
}
