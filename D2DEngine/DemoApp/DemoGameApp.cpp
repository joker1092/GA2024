#include "DemoGameApp.h"

bool DemoGameApp::Intialize(HINSTANCE hInstance, LPCTSTR appName)
{
	if (!WinGameApp::Intialize(hInstance, appName))
	{
		return false;
	}
	return true;
}

void DemoGameApp::Update()
{

}

void DemoGameApp::Render()
{

}
