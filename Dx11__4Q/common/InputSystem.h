#pragma once
#include <directxtk/Mouse.h>
#include <directxtk/Keyboard.h>

using namespace DirectX;

class InputPrecesser {
public:
	virtual void OnInputProcess(const Keyboard::State& KeyState, const Keyboard::KeyboardStateTracker& KeyTracker,
		const Mouse::State& MouseState, const Mouse::ButtonStateTracker& MouseTracker) = 0;
};


class InputSystem
{
private:
	InputPrecesser* m_pInputPrecesser = nullptr;

	DirectX::Mouse::State m_MouseState;
	DirectX::Keyboard::State m_KeyboardState;
	DirectX::Mouse::ButtonStateTracker m_MouseTracker;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

public:
	InputSystem();
	~InputSystem() {};

	static InputSystem* Instance;
	std::unique_ptr<DirectX::Mouse> m_pMouse;
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;

	static InputSystem* GetInstance() { return Instance; }

	DirectX::Mouse* GetMouse() { return m_pMouse.get(); }

	bool Initialize(HWND hwnd, InputPrecesser* processer);
	void Update(float DeltaTime);
};


