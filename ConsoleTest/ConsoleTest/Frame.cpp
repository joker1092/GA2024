#include "Frame.h";

namespace Frame {
	
	bool g_bQuit = true;

	void Init() {
		ConsoleRenderer::ScreenInit();
		Time::InitTime();
		Player::setCurPosition(ConsoleRenderer::InitPosition());
	}

	void ProcessInput()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽

		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
			
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
			
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
			
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //종료
			g_bQuit = false;
		}
	}

	void FixedUpdate() {
		
	}

	void Update() {

	}

	void Render() {
		ConsoleRenderer::ScreenClear();
		ConsoleRenderer::DrawMovableRect();
		ConsoleRenderer::DrawMap();
		ConsoleRenderer::ScreenSetString(100, 2, "시간", FG_PINK_DARK);
		ConsoleRenderer::ScreenSetChar(Player::getCurPosion().X, Player::getCurPosion().Y, 'P', FG_WHITE);
		ConsoleRenderer::ScreenFlipping();
	}

	void Quit() {
		ConsoleRenderer::ScreenRelease();
	}
}