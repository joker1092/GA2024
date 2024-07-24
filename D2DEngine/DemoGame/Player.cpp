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
#include "Player.h"

Player::Player()
{
	m_ZOrder =ZOrder::PLAYER;
	//Scene
	m_pRootScene = CreateComponent<Scene>(); // ��Ʈ �� ����
	PlayerTop = CreateComponent<PlayerBodyScene>(); // ��ü �ִϸ��̼� �� ����
	PlayerBottom = CreateComponent<PlayerWorkScene>(); // ��ü �ִϸ��̼� �� ����
	pFireScene = CreateComponent<FireScene>(); // �� �߻� �� ����

	SetRootScene(m_pRootScene); // ��ü �ִϸ��̼��� ��Ʈ�� ����
	PlayerTop->SetParentScene(m_pRootScene); // ��ü �ִϸ��̼��� ��Ʈ�� �ڽ����� ����
	PlayerBottom->SetParentScene(m_pRootScene); // ��ü �ִϸ��̼��� ��ü �ִϸ��̼��� �ڽ����� ����

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
	//todo:
	//��ü�� ��ü�� ���¸� �и��Ͽ� ����
	//��ü�� FSM�� ��ü�� FSM�� ���� ����
	//�������� ������ �ϴ� ����  => Idle, Move, Jump, Dead
	//��ü�� ������ �ϴ� ���� => Attack, Boom, UP, Down
	//��ü�� ������ �ϴ� ���� => MoveJump
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

	PlayerPlate = CreateComponent<BoxCollider>();
	PlayerPlate->SetParentScene(m_pRootScene);
	PlayerPlate->SetNotify(this);
	//todo:
	//RootScene�� ��ü���� Collider�� ũ�⸦ ������
	//DebugDraw�� ���� Ȯ���� �� �ְ� �Ұ� 

	//player�� ���� ������ ���� ��� �׼��� ���ϰ� �ʹ�
	//�� ���� ���� �Ѿ��� �����ؼ� �Ѿ��� �߻��ϴ� ����� �����ϰ� �ʹ�
	//�Ѿ��� ���� ��� �׼��� ���ϸ� �����Ǿ� ���� ��� �������� �߻�Ǿ�� �Ѵ�
	//�Ѿ��� ���� ��� �׼��� ������ ������� �Ѵ�
	
	setDelay(0.5f);
	
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
	PlayerBox->m_collider.SetExtent(18, 18);
	PlayerPlate->m_RelativeLocation = { 9, -15 };
	PlayerPlate->m_collider.SetExtent(6, 5);
	
}

void Player::Update(float deltaTime)
{
	//pMovement->SetDirection({ 0,0 });
	pMovement->SetSpeed(0);
	
	

	if (!isDead) {

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

		if (pInput->IsKey('Z')|| pInput->IsKey('z'))
		{
			pPlayerBodyFSM->setNextState("Attack");
		}


		if (pInput->IsKey('0'))
		{
			isDead = true; //���� ���·� ����
			//todo : ���� collision�� ���� ���� ���·� ����
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
	
	//���ī��Ʈ �ʱ�ȭ
	blockCount = 0;
}

void Player::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	//std::cout << "Player OnBlock" << std::endl;
	if (pOwnedComponent == PlayerBox) {
		//std::cout << "Player PlayerBox OnBlock" << std::endl;
	}

	if (pOwnedComponent == PlayerPlate) {
		GameObject* pOtherOwner = pOtherComponent->GetOwner();
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
	GameObject* pOtherOwner = pOtherComponent->GetOwner();
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
