#include <iostream>
#include <Windows.h>
#include "Frame.h"

int main()
{
    int g_bQuit = -1;
	Frame::Init();

	while (g_bQuit!=0)
	{
		g_bQuit = Frame::ProcessInput();
		Frame::FixedUpdate();
		Frame::Update();
		Frame::Render();
	};

	Frame::Quit();
}