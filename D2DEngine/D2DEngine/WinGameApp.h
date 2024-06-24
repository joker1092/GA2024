#pragma once
#include "framework.h"
#include "D2DRender.h"
#include "ResourceManager.h"
#define MAX_LOADSTRING 100

class WinGameApp
{
private :
	HINSTANCE hInst = { 0 };  // HINSTANCE is a handle to an instance of a module.
	HWND m_hWnd = { 0 };
	
public:
	WinGameApp();
	~WinGameApp();
	D2DRender* pD2DRender;
	ResourceManager* pResouceManager;
	virtual void Initialize(HINSTANCE hInstance, LPCTSTR szTitle);
	virtual int Run();
	virtual void UnInitialize();
	virtual void Update() = 0;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) = 0;

	HINSTANCE GetHintance() { return hInst; }
};

