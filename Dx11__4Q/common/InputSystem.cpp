#include "pch.h"
#include "InputSystem.h"


InputSystem::InputSystem() : m_MouseState(), m_KeyboardState()
{
	if (Instance == nullptr) Instance = this;
}

InputSystem* InputSystem::Instance = nullptr;

bool InputSystem::Initialize(HWND hwnd, InputPrecesser* processer)
{
	m_pInputPrecesser = processer;
	m_pKeyboard = std::make_unique<Keyboard>();
	m_pMouse = std::make_unique<Mouse>();
	m_pMouse->SetWindow(hwnd);
	return true;
}

void InputSystem::Update(float DeltaTime)
{
	m_MouseState = m_pMouse->GetState();
	m_MouseTracker.Update(m_MouseState);

	m_KeyboardState = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(m_KeyboardState);

	if (m_pInputPrecesser != nullptr)
	{
		m_pInputPrecesser->OnInputProcess(m_KeyboardState, m_KeyboardTracker, m_MouseState, m_MouseTracker);
	}
}