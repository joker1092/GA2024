#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "PlayerState.h"
#include "Player.h"

void PlayerIdle::Enter()
{
	std::cout << "PlayerIdle Update" << std::endl;
	m_pPlayer= m_pOwnerFSM->GetOwner();
	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	
	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pPlayer->m_pRootScene);
	//bool b = root->GetCurrMirror();
	for( Component* c : (m_pPlayer->m_OwnedComponents))
		if (dynamic_cast<AnimationScene*>(c))
		{
			AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
			//anima->SetAnimationIndex(0);
			anima->SetAnimation(0, flip);
		}
}

void PlayerIdle::Update(float daltatime)
{
	std::cout << "PlayerIdle Update" << std::endl;
}

void PlayerIdle::CheckTransition()
{
	std::cout << "PlayerIdle CheckTransition" << std::endl;

	if (m_pPlayer->GetComponent<Movement>()->GetSpeed()!=0)
		m_pOwnerFSM->setNextState(std::string("Move"));
}

void PlayerIdle::Exit()
{
	std::cout << "PlayerIdle Exit" << std::endl;
}

std::string PlayerIdle::GetName()
{
	return m_Name;
}

void PlayerMove::Enter()
{
	//m_pPlayer = m_pOwnerFSM->GetOwner();
	m_pPlayer = m_pOwnerFSM->GetOwner();
	Player* player = dynamic_cast<Player*>(m_pPlayer);
	flip = player->flip;
	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pPlayer->m_pRootScene);
	bool b = root->GetCurrMirror();
	for (Component* c : (m_pPlayer->m_OwnedComponents))
		if (dynamic_cast<AnimationScene*>(c))
		{
			AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
			anima->SetAnimationIndex(1);
		}
}

void PlayerMove::Update(float daltatime)
{
	Player* m_pPlayer = dynamic_cast<Player*>(m_pOwnerFSM->GetOwner());

	if (m_pPlayer->GetComponent<Movement>()->GetDirection().x < 0)
	{
		m_pPlayer->flip = true;
		for (Component* c : (m_pPlayer->m_OwnedComponents))
			if (dynamic_cast<AnimationScene*>(c))
			{
				AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
				anima->SetMirror(true);
				
			}
	}else{
		m_pPlayer->flip = false;
		for (Component* c : (m_pPlayer->m_OwnedComponents))
			if (dynamic_cast<AnimationScene*>(c))
			{
				AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
				anima->SetMirror(false);
				
			}
	}
	std::cout << "PlayerMove Update" << std::endl;
}

void PlayerMove::CheckTransition()
{
	std::cout << "PlayerMove Update" << std::endl;
	if (m_pPlayer->GetComponent<Movement>()->GetSpeed() == 0)
		m_pOwnerFSM->setNextState(std::string("Idle"));
}

void PlayerMove::Exit()
{
	std::cout << "PlayerMove Exit" << std::endl;
	
}

std::string PlayerMove::GetName()
{
	return m_Name;
}
