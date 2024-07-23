#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "PlayerBodyState.h"
#include "Player.h"
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
		//object의 flip은 상체에서만 수정한다.
		body->SetMirror(true);
	}
	else {
		m_pPlayer->flip = false;	
		//object의 flip은 상체에서만 수정한다.
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
	//jump에서는 flip이 되어있는 상태로 수정 하지 않는다.
}

void BodyJump::CheckTransition()
{
	if (!(m_pPlayer->GetComponent<SideMovement>()->isJumping()))
		m_pOwnerFSM->setNextState(std::string("Idle"));
	//jump에서 <==> moveJump으로 전환 불가
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
	flip = player->flip;

	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());

	body->SetAnimationIndex(4);//추가예정
	//3 인덱스 moveJump 배정 4 인덱스로 할당
}

void BodyAttack::Update(float daltatime)
{
	//jump에서는 flip이 되어있는 상태로 수정 하지 않는다.
}

void BodyAttack::CheckTransition()
{

	Player* player = dynamic_cast<Player*>(m_pPlayer);
	PlayerBodyScene* body = dynamic_cast<PlayerBodyScene*>(m_pPlayer->GetComponent<PlayerBodyScene>());
	bool isEndMotion = body->isEndMotion;
	if (isEndMotion)
	{
		//todo : 공격 에니메이션 이후 Idle로 전환
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
	body->SetAnimationIndex(3); //죽는 에니메이션 차후 변경 가능
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
		//todo : 죽는 에니메이션 이후 respawn or gameover
	}
	//Dead에서는 flip이 되어있는 상태로 수정 하지 않는다.
}

void BodyDead::CheckTransition()
{
	
}

void BodyDead::Exit()
{
}
