#include <iostream>
#include <Windows.h>
#include "Frame.h"

int main()
{
	Frame::Init();

	while (Frame::g_bQuit)
	{
		Frame::ProcessInput();
		Frame::FixedUpdate();
		Frame::Update();
		Frame::Render();
	};

	Frame::Quit();
}