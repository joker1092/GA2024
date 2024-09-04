#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/World.h"
#include "Bullet.h"
#include "PlayerBodyState.h"
#include "Player.h"
#include "FireScene.h"
#include "PlayerBodyScene.h"

void BodyIdle::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	Player* player = dynamic_cast<Player*>(m_pPlayer);

	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());

	body->SetAnimation(0, flip);
}

void BodyIdle::Update(float daltatime)
{

}

void BodyIdle::CheckTransition()
{
	if (m_pPlayer->GetComponent<SideMovement>()->GetSpeed() != 0)
		m_pOwnerFSM->setNextState(std::string("Move"));
	if (m_pPlayer->GetComponent<SideMovement>()->isJumping())
		m_pOwnerFSM->setNextState(std::string("Jump"));
}

void BodyIdle::Exit()
{

}

void BodyMove::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;


	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());

	body->SetAnimationIndex(1);
}

void BodyMove::Update(float daltatime)
{
	Player* m_pPlayer = dynamic_cast<Player*>(m_pOwnerFSM->GetOwner());

	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());

	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0)
	{
		m_pPlayer->flip = true;
		//object�� flip�� ��ü������ �����Ѵ�.
		body->SetMirror(true);
	}
	else {
		m_pPlayer->flip = false;	
		//object�� flip�� ��ü������ �����Ѵ�.
		body->SetMirror(false);

	}
}

void BodyMove::CheckTransition()
{
	if (m_pPlayer->GetComponent<Movement>()->GetSpeed() == 0)
		m_pOwnerFSM->setNextState(std::string("Idle"));
	if (m_pPlayer->GetComponent<SideMovement>()->isJumping())
		m_pOwnerFSM->setNextState(std::string("MoveJump"));
}

void BodyMove::Exit()
{
}

void BodyJump::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	body->SetAnimationIndex(2);
}

void BodyJump::Update(float daltatime)
{
	//jump������ flip�� �Ǿ��ִ� ���·� ���� ���� �ʴ´�.
}

void BodyJump::CheckTransition()
{
	if (!(m_pPlayer->GetComponent<SideMovement>()->isJumping()))
		m_pOwnerFSM->setNextState(std::string("Idle"));
	//jump���� <==> moveJump���� ��ȯ �Ұ�
	/*if (m_pPlayer->GetComponent<SideMovement>()->GetSpeed() != 0)
		m_pOwnerFSM->setNextState(std::string("MoveJump"));*/
}

void BodyJump::Exit()
{
}


void BodyAttack::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	m_pWorld = m_pPlayer->m_pOwner;
	flip = player->flip;

	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());

	body->SetAnimationIndex(4); // ���� ���ϸ��̼��� �ε����� �Ҵ��մϴ�.
}

void BodyAttack::Update(float daltatime)
{
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	
	// ���� �ִϸ��̼��� ������ �߻�ü�� �����մϴ�.
	if (player->GetComponent<Movement>()->GetDirection().x < 0)
	{
		player->flip = true;
		//object�� flip�� ��ü������ �����Ѵ�.
		body->SetMirror(true);
	}
	else {
		player->flip = false;
		//object�� flip�� ��ü������ �����Ѵ�.
		body->SetMirror(false);

	}
	if (body->m_FrameIndexCurr == 2) // ���÷� 5��° �����ӿ��� �߻�ü�� �����մϴ�.
	{
		if (player->isFire==true)
		{
			// �߻�ü ���� ������ �߰��մϴ�.
			Bullet* bullet = m_pWorld->CreateGameObject<Bullet>();
			bullet->m_ZOrder = GameObject::ZOrder::EFFECT;
			MathHelper::Vector2F dir = { 0,0 };
			if (player->flip)
				dir = { -1,0 };
			else
				dir = { 1,0 };
			bullet->SetDirection(dir);
			bullet->m_pRootScene->SetRelativeLocation(player->pFireScene->GetWorldLocation());
			player->isFire = false;
			player->fireDelay = 0;
		}
	}
	// jump������ flip�� �Ǿ��ִ� ���·� �������� �ʽ��ϴ�.
}

void BodyAttack::CheckTransition()
{
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	bool isEndMotion = body->isEndMotion;

	if ((body->m_FrameIndexCurr > 2) && (player->pInput->IsKey('Z') || player->pInput->IsKey('z')))
	{
		m_pOwnerFSM->setNextState(std::string("Attack"));
		body->SetAnimationIndex(4);
	}

	if (isEndMotion)
	{
		// ���� �ִϸ��̼��� ������ Idle ���·� ��ȯ�մϴ�.
		m_pOwnerFSM->setNextState(std::string("Idle"));
	}
}

void BodyAttack::Exit()
{
}

void BodyDead::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	body->LoadD2DBitmap(L"../Resource/Marco_trans_death.png");
	body->SetAnimationIndex(3); //�״� ���ϸ��̼� ���� ���� ����
}

void BodyDead::Update(float daltatime)
{
	
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	bool isEndMotion = body->isEndMotion;
	if (isEndMotion)
	{
		int index = body->pAnimationAsset->GetMotionInfo(3)->Frames.size()-1;
		body->m_FrameIndexCurr = index;
		//todo : �״� ���ϸ��̼� ���� respawn or gameover
	}
	//Dead������ flip�� �Ǿ��ִ� ���·� ���� ���� �ʴ´�.
}

void BodyDead::CheckTransition()
{
	
}

void BodyDead::Exit()
{
}
