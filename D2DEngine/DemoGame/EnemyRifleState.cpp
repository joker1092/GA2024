#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/AnimationScene.h"
#include "../D2DEngine/AnimationAsset.h"
#include "../D2DEngine/World.h"

#include "Player.h"
#include "EnemyRifleState.h"
#include "EnemyRifle.h"



void EnemyRifleIdle::Enter()
{
	//std::cout << "EnemyRifleIdle Enter" << std::endl;
	m_pEnemyRifle = m_pOwnerFSM->GetOwner();
	m_pWorld = m_pEnemyRifle->m_pOwner;
	m_pPlayer =m_pWorld->FindPointGameObject<Player>();
	if (m_pEnemyRifle->GetComponent<SideMovement>()->GetDirection().x < 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	EnemyRifle* enemyRifle = dynamic_cast<EnemyRifle*>(m_pEnemyRifle);

	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pEnemyRifle->m_pRootScene);
	//bool b = root->GetCurrMirror();
	for (Component* c : (m_pEnemyRifle->m_OwnedComponents))
		if (dynamic_cast<AnimationScene*>(c))
		{
			AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
			//anima->SetAnimationIndex(0);
			anima->SetAnimation(0, flip);
		}
}

void EnemyRifleIdle::Update(float daltatime)
{
	//std::cout << "EnemyRifleIdle Update" << std::endl;
}

void EnemyRifleIdle::CheckTransition()
{
	//std::cout << "EnemyRifleIdle CheckTransition" << std::endl;
	MathHelper::Vector2F m_pPlayerLocation = m_pPlayer->GetWorldLocation();
	MathHelper::Vector2F m_pEnemyRifleLocation = m_pEnemyRifle->GetWorldLocation();
	float distance = (m_pPlayerLocation- m_pEnemyRifleLocation).Length();
	if (distance <= 500)
		m_pOwnerFSM->setNextState(std::string("EnemyRifleMove"));
}

void EnemyRifleIdle::Exit()
{
		//std::cout << "EnemyRifleIdle Exit" << std::endl;
}

std::string EnemyRifleIdle::GetName()
{
	return m_Name;
}

void EnemyRifleMove::Enter()
{
	m_pEnemyRifle = m_pOwnerFSM->GetOwner();
	m_pWorld = m_pEnemyRifle->m_pOwner;
	m_pPlayer = m_pWorld->FindPointGameObject<Player>();
	m_pPlayerLocation=m_pPlayer->GetWorldLocation();
	m_pEnemyRifleLocation=m_pEnemyRifle->GetWorldLocation();
	movement = m_pEnemyRifle->GetComponent<SideMovement>();
	movement->SetSpeed(50);
	movement->SetDirection((m_pPlayerLocation - m_pEnemyRifleLocation));

	if (m_pEnemyRifle->GetComponent<SideMovement>()->GetDirection().x > 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	EnemyRifle* enemyRifle = dynamic_cast<EnemyRifle*>(m_pEnemyRifle);

	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pEnemyRifle->m_pRootScene);
	//bool b = root->GetCurrMirror();
	for (Component* c : (m_pEnemyRifle->m_OwnedComponents))
		if (dynamic_cast<AnimationScene*>(c))
		{
			AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
			//anima->SetAnimationIndex(0);
			anima->SetAnimation(1, flip);
		}
}

void EnemyRifleMove::Update(float daltatime)
{
	m_pPlayerLocation = m_pPlayer->GetWorldLocation();
	m_pEnemyRifleLocation = m_pEnemyRifle->GetWorldLocation();
	movement->SetDirection(m_pPlayerLocation - m_pEnemyRifleLocation);
	
}

void EnemyRifleMove::CheckTransition()
{
	float distance = (m_pPlayerLocation - m_pEnemyRifleLocation).Length();
	if (distance > 500)
	{
		m_pOwnerFSM->setNextState(std::string("EnemyRifleIdle"));
	}
	else if (distance <= 100){
		m_pOwnerFSM->setNextState(std::string("EnemyRifleAttack"));
	}
}

void EnemyRifleMove::Exit()
{
	//std::cout << "EnemyRifleMove Exit" << std::endl;
	movement->SetSpeed(0);
}

std::string EnemyRifleMove::GetName()
{
	return m_Name;
}

void EnemyRifleAttack::Enter()
{
	m_pEnemyRifle = m_pOwnerFSM->GetOwner();
	m_pWorld = m_pEnemyRifle->m_pOwner;
	m_pPlayer = m_pWorld->FindPointGameObject<Player>();
	m_pPlayerLocation = m_pPlayer->GetWorldLocation();
	m_pEnemyRifleLocation = m_pEnemyRifle->GetWorldLocation();
	movement = m_pEnemyRifle->GetComponent<SideMovement>();
	movement->SetDirection(m_pPlayerLocation - m_pEnemyRifleLocation);

	if (m_pEnemyRifle->GetComponent<SideMovement>()->GetDirection().x > 0) {
		flip = true;
	}
	else {
		flip = false;
	}
	EnemyRifle* enemyRifle = dynamic_cast<EnemyRifle*>(m_pEnemyRifle);

	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pEnemyRifle->m_pRootScene);
	//bool b = root->GetCurrMirror();
	for (Component* c : (m_pEnemyRifle->m_OwnedComponents))
		if (dynamic_cast<AnimationScene*>(c))
		{
			AnimationScene* anima = dynamic_cast<AnimationScene*>(c);
			//anima->SetAnimationIndex(0);
			anima->SetAnimation(2, flip);
		}
}

void EnemyRifleAttack::Update(float daltatime)
{
	m_pPlayerLocation = m_pPlayer->GetWorldLocation();
	m_pEnemyRifleLocation = m_pEnemyRifle->GetWorldLocation();
	movement->SetDirection(m_pPlayerLocation - m_pEnemyRifleLocation);
	if (m_pEnemyRifle->GetComponent<SideMovement>()->GetDirection().x > 0) {
		flip = true;
	}
	else {
		flip = false;
	}
}

void EnemyRifleAttack::CheckTransition()
{
	float distance = (m_pPlayerLocation - m_pEnemyRifleLocation).Length();
	AnimationScene* root = dynamic_cast<AnimationScene*>(m_pEnemyRifle->m_pRootScene);
	bool isEndMotion = root->isEndMotion;
	std::cout << isEndMotion << std::endl;
	if (isEndMotion&&distance > 100)
	{
		m_pOwnerFSM->setNextState(std::string("EnemyRifleMove"));
	}else if (isEndMotion && distance > 500) {
		m_pOwnerFSM->setNextState(std::string("EnemyRifleIdle"));
	}
}

void EnemyRifleAttack::Exit()
{
	//std::cout << "EnemyRifleAttack Exit" << std::endl;
}

std::string EnemyRifleAttack::GetName()
{
	return m_Name;
}
