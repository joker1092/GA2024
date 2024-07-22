#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "PlayerWorkState.h"
#include "Player.h"
#include "PlayerWorkScene.h"

void WorkIdle::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());

	work->SetAnimation(0, flip);
}

void WorkIdle::Update(float daltatime)
{

}

void WorkIdle::CheckTransition()
{
	if (m_pPlayer->GetComponent<SideMovement>()->GetSpeed() != 0)
		m_pOwnerFSM->setNextState(std::string("Move"));
	if (m_pPlayer->GetComponent<SideMovement>()->isJumping())
		m_pOwnerFSM->setNextState(std::string("Jump"));
}

void WorkIdle::Exit()
{

}

void WorkMove::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	

	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());
	
	work->SetAnimationIndex(1);		
}

void WorkMove::Update(float daltatime)
{
	Player* m_pPlayer = dynamic_cast<Player*>(m_pOwnerFSM->GetOwner());
	
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());

	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0)
	{
		//m_pPlayer->flip = true;
		//object의 flip은 상체에서만 수정한다.
		work->SetMirror(true);
	}
	else {
		//m_pPlayer->flip = false;	
		//object의 flip은 상체에서만 수정한다.
		work->SetMirror(false);

	}
}

void WorkMove::CheckTransition()
{
	if (m_pPlayer->GetComponent<Movement>()->GetSpeed() == 0 )
		m_pOwnerFSM->setNextState(std::string("Idle"));
	if (m_pPlayer->GetComponent<SideMovement>()->isJumping())
		m_pOwnerFSM->setNextState(std::string("MoveJump"));
}

void WorkMove::Exit()
{
}

void WorkJump::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());
	work->SetAnimationIndex(2);
}

void WorkJump::Update(float daltatime)
{
	//jump에서는 flip이 되어있는 상태로 수정 하지 않는다.
}

void WorkJump::CheckTransition()
{
	if (!(m_pPlayer->GetComponent<SideMovement>()->isJumping()))
		m_pOwnerFSM->setNextState(std::string("Idle"));
	//jump에서 <==> moveJump으로 전환 불가
	/*if (m_pPlayer->GetComponent<SideMovement>()->GetSpeed() != 0)
		m_pOwnerFSM->setNextState(std::string("MoveJump"));*/
}

void WorkJump::Exit()
{
}

void WorkMoveJump::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;

	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());

	work->SetAnimationIndex(3);//추가예정
}

void WorkMoveJump::Update(float daltatime)
{
	//jump에서는 flip이 되어있는 상태로 수정 하지 않는다.
}

void WorkMoveJump::CheckTransition()
{
	//jump에서 <==> moveJump으로 전환 불가
	/*if (m_pPlayer->GetComponent<Movement>()->GetSpeed() == 0)
		m_pOwnerFSM->setNextState(std::string("Jump"));*/
	if (!(m_pPlayer->GetComponent<SideMovement>()->isJumping()))
		m_pOwnerFSM->setNextState(std::string("Move"));
}

void WorkMoveJump::Exit()
{

}

void WorkDead::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());

	work->SetVisable(false);
}

void WorkDead::Update(float daltatime)
{
	//죽었을시 하체부 비표시
}

void WorkDead::CheckTransition()
{
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());
	bool isEndMotion = work->isEndMotion;
	if (isEndMotion)
	{
		//todo : 죽는 에니메이션 이후 respawn or gameover
		//상체와 동일
	}
}

void WorkDead::Exit()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	PlayerWorkScene* work = dynamic_cast<PlayerWorkScene*>(m_pPlayer->GetComponent<PlayerWorkScene>());

	work->SetVisable(true);
}
