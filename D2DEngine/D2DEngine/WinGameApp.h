#pragma once
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#include <windows.h>
#include "D2DRenderer.h"

class WinGameApp
{
protected:
	D2DRenderer* pRender;
	HINSTANCE m_hInstance = { 0 };
	HWND m_hWnd = { 0 };
public:
	virtual bool Intialize(HINSTANCE hInstance, LPCTSTR appName);
	virtual void Run();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UnIntialize();
};

