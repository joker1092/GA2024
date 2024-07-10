#include "framework.h"
#include "../D2DEngine/FSM.h"
#include "../D2DEngine/FSMState.h"
#include "PlayerState.h"

void PlayerIdle::Enter()
{
	m_pPlayer = m_pOwnerFSM->GetOwner();
}

void PlayerIdle::Update(float daltatime)
{
	if (m_pPlayer->get
	{

	}
}

void PlayerIdle::CheckTransition()
{
	std::cout << "PlayerIdle CheckTransition" << std::endl;
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
	std::cout << "PlayerMove Enter" << std::endl;
}

void PlayerMove::Update(float daltatime)
{
	std::cout << "PlayerMove Update" << std::endl;
}

void PlayerMove::CheckTransition()
{
	std::cout << "PlayerMove Update" << std::endl;
}

void PlayerMove::Exit()
{
	std::cout << "PlayerMove Exit" << std::endl;
}

std::string PlayerMove::GetName()
{
	return m_Name;
}
