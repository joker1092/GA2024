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
		input::UpdateInput();
		g_bQuit = !input::IsEscapeKeyOn();
	}

	void FixedUpdate() {
		
	}


	void Clamp(short& n, short min, short max) {
		if (n < min)n = min;
		if (n > max)n = max;
	}

	void UpdatePosition(int x, int y) {
		int left = ConsoleRenderer::playerMovableRect.Left;
		int top = ConsoleRenderer::playerMovableRect.Top;
		int right = ConsoleRenderer::playerMovableRect.Right;
		int bottom = ConsoleRenderer::playerMovableRect.Bottom;
		if (Player::getCurPosion().X + x <left|| Player::getCurPosion().X + x > right)
		{
			return;
		}
		if (Player::getCurPosion().Y + y < top || Player::getCurPosion().Y + y > bottom)
		{
			return;
		}
		COORD curtemp = { Player::getCurPosion().X, Player::getCurPosion().Y };
		COORD temp = { (short)(Player::getCurPosion().X - left + x) ,(short)(Player::getCurPosion().Y- top + y) };
		if (Map::PositionState(temp)==0)
		{
			Player::setPrePosition(curtemp);
			Player::setCurPosition({ (short)(Player::getCurPosion().X + x) ,(short)(Player::getCurPosion().Y + y) });
			
		}
	}

	void Update() {
		
		
		if (input::IsUpKeyOn())
		{
			input::Set(input::UP_KEY_INDEX, false);
			UpdatePosition(0, -1);
		}
		else if (input::IsDownKeyOn())
		{
			input::Set(input::DOWN_KEY_INDEX, false);
			UpdatePosition(0, 1);
		}
		else if (input::IsLeftKeyOn())
		{
			input::Set(input::LEFT_KEY_INDEX, false);
			UpdatePosition(-1, 0);
		}
		else if (input::IsRightKeyOn())
		{
			input::Set(input::RIGHT_KEY_INDEX, false);
			UpdatePosition(1, 0);
		}
		
	}
	

	void Render() {
		ConsoleRenderer::ScreenClear();
		ConsoleRenderer::DrawMovableRect();
		ConsoleRenderer::DrawMap();
		ConsoleRenderer::ScreenSetString(100, 2, "½Ã°£", FG_PINK_DARK);
		ConsoleRenderer::ScreenSetChar(100,4, Player::getCurPosion().X+'0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(103,4, Player::getCurPosion().Y + '0', FG_WHITE);

		ConsoleRenderer::ScreenSetChar(100, 6, input::IsUpKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(101, 6, input::IsDownKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(102, 6, input::IsLeftKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(103, 6, input::IsRightKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(Player::getCurPosion().X, Player::getCurPosion().Y, 'P', FG_WHITE);
		ConsoleRenderer::ScreenFlipping();
	}

	void Quit() {
		ConsoleRenderer::ScreenRelease();
	}
}