#pragma once
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include "Resource.h"
#include "InputManager.h"
#include "TimeSystem.h"

class WinGameApp
{
public:
	virtual void Initialize(HINSTANCE hInstance, LPCTSTR appName);
	virtual void Run();
	virtual void Update(InputManager* pInput) = 0;
	virtual void Render(D2DRenderer* pRender)=0;
	virtual void Uninitialize();

	HINSTANCE GetInstance() const { return m_hInstance; }

	HWND GetWindow() const { return m_hWnd; }

	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }
	
private:
	HINSTANCE m_hInstance = { 0 };  // HINSTANCE is a handle to an instance of a module.
	HWND m_hWnd = { 0 };			// HWND is a handle to a window.

	D2DRenderer* pRender = nullptr;
	InputManager* pInput = nullptr;
	TimeSystem* pTime = nullptr;

	int width;
	int height;
};

