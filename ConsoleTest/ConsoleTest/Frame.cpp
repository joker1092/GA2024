#include "Frame.h";

namespace Frame {

	void Init() {
		ConsoleRenderer::ScreenInit();
		Time::InitTime();
	}

	int ProcessInput()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //����
			return 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //������
			return 0;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) { //��
			return 0;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //�Ʒ�
			return 0;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //����
			return 0;
		}
		return 1;
	}

	void FixedUpdate() {
		static ULONGLONG futime;
		//ULONGLONG detatime = Time::GetDeltaTime();
		double speed = 0.2;
		//futime += Time::GetDeltaTime();
		if (futime > 50)
		{

		}

	}
	void Update() {

	}
	void Render() {
		ConsoleRenderer::ScreenClear();
		ConsoleRenderer::DrawMovableRect();
		//ConsoleRenderer::ScreenSetString(0, 0, "Hello �ȳ�", FG_PINK_DARK);
		//ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y, 'P', FG_WHITE);
		ConsoleRenderer::ScreenFlipping();
	}

	void Quit() {
		ConsoleRenderer::ScreenRelease();
	}
}