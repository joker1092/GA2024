#pragma once
#include "framework.h"
#include "D2Drender.h"
#define MAX_LOADSTRING 100

class WinGameApp
{
private :
	HINSTANCE hInst = { 0 };  // HINSTANCE is a handle to an instance of a module.
	HWND m_hWnd = { 0 };
	D2Drender* pD2Drender;
public:
	virtual bool Initialize(HINSTANCE hInstance, LPCTSTR szTitle);
	virtual int Run();
	virtual void UnInitialize();
	virtual void Update() = 0;
	virtual void Render() = 0;

	HINSTANCE GetHintance() { return hInst; }
};

