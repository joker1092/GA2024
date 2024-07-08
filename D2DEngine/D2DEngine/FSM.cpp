#include "framework.h"
#include "FSMState.h"
#include "FSM.h"

FSM::~FSM()
{
	for (auto& state : m_vStates)
	{
		delete state.second;
	}
	m_vStates.clear();
}

void FSM::Update(float deltaTime)
{
	if (m_pCurrentState != m_pNextState)
	{
		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->Exit();
		}
		m_pCurrentState = m_pNextState;
		m_pCurrentState->Enter();
	}
	else
	{
		m_pCurrentState->Update(deltaTime);
		m_pCurrentState->CheckTransition();
	}
}

void FSM::setNextState(std::string nextStateName)
{
	auto it = m_vStates.find(nextStateName);
	if (it != m_vStates.end())
	{
		m_pNextState = it->second;
	}
}
