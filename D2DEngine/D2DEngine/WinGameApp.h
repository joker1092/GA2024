#pragma once
#include "framework.h"
#include "D2DRender.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "ResourceManager.h"
#include "World.h"
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
	D2DRender* pD2DRender = nullptr;
	ResourceManager* pResouceManager = nullptr;
	TimeSystem* pTime = nullptr;
	InputSystem* pInput = nullptr;
	World* m_pWorld = nullptr;
	Camera* m_pCamera = nullptr;
	virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle);
	virtual int Run();
	virtual void UnInitialize();
	virtual void Update(float deltatime);
	void RectPoint();
	void DrawInfoRect();
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
	HINSTANCE GetHintance() { return hInst; }
};

