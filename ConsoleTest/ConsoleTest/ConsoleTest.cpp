#include <Windows.h>
#include "Frame.h"

int main()
{
	Frame::Init();
	bool isClear = Frame::isClear();
	while (Frame::g_bQuit)
	{
		Time::UpdateTime();
		Frame::ProcessInput();
		Frame::FixedUpdate();
		Frame::Update();
		Frame::Render();
	};

	Frame::Quit();
}