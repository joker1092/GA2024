#pragma once
#include "framework.h"
#include "D2DRender.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "ResourceManager.h"
#include "Camera.h"
#define MAX_LOADSTRING 100

class WinGameApp
{
private :
protected:
	HINSTANCE hInst = { 0 };  // HINSTANCE is a handle to an instance of a module.
	HWND m_hWnd = { 0 };
	float elepsedTime = 0;
public:
	WinGameApp();
	~WinGameApp();
	D2DRender* pD2DRender;
	ResourceManager* pResouceManager;
	TimeSystem* pTime;
	InputSystem* pInput;
	Camera* pCamera;
	virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle);
	virtual int Run();
	virtual void UnInitialize();
	virtual void Update(float deltatime) = 0;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) = 0;
	HINSTANCE GetHintance() { return hInst; }
};

