#include "InputManager.h"



void InputManager::InitInput(HWND _hwnd,int screenX,int screenY)
{
	hwnd = _hwnd;
	screenWidth = screenX;
	screenHeight = screenY;
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
		isKey[i] = false;
	}
	memset(buffer, '\0', 255);
	InitMouse();
}

void InputManager::ResetInput()
{
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
	}
}

void InputManager::KeyDown(unsigned int key)
{
	isKeyDown[key] = true;
	isKey[key] = false;
}

void InputManager::KeyUp(unsigned int key)
{
	isKeyUp[key] = true;
	isKey[key] = false;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	return isKeyDown[key];
}

bool InputManager::IsKeyUp(unsigned int key)
{
	return isKeyUp[key];
}

bool InputManager::IsKey(unsigned int key)
{
	return isKey[key];
}

void InputManager::UpdateMouse()
{
	prevMouse = curMouse;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);

	curMouse.x = pt.x;
	curMouse.y = pt.y;
	curMouse.wheel = 0;

	curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

bool InputManager::IsSame(const MouseState& a, const MouseState& b)
{
	return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;
}

const InputManager::MouseState& InputManager::GetMouseState()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return curMouse;
}

const InputManager::MouseState& InputManager::GetPrevMouseState()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return prevMouse;
}

void InputManager::AddBuffer(TCHAR _buffer)
{
	if (isInputKey == true) {
		buffer[length++] = _buffer;
	}
}

void InputManager::SetInputState(bool on)
{
	isInputKey = on;
}

int InputManager::GetInputBuffer(TCHAR* in, int count, int maxLength)
{
	for (int i = count; i < maxLength - 1; i++) {
		in[i] = buffer[i - count];
	}
	in[maxLength - 1] = L'\0';
	for (int i = 0; i < 255; i++) buffer[i] = L'\0';
	int a = length;
	length = 0;
	if (a + count > maxLength - 1)
		return maxLength - 1;

	return a + count;
}
