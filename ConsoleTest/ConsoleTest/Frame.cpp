#include "Frame.h";




namespace Frame {
	
	bool g_bQuit = true;
	bool g_clear = false;
	int elepsedTime = 0;
	const int TIMER_BUFF = 10;
	char timer[TIMER_BUFF];



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
		g_clear = Frame::isClear();

		if (!g_clear)
		{
			elepsedTime += Time::GetDeltaTime();
		}
		Frame::setTimer(timer);
		static int update;
		update += Time::GetDeltaTime();
		

		if (input::IsUpKeyOn())
		{
			input::Set(input::UP_KEY_INDEX, false);
			if (update / 10 > 5)
			{
				UpdatePosition(0, -1);
			}
		}
		else if (input::IsDownKeyOn())
		{
			input::Set(input::DOWN_KEY_INDEX, false);
			if (update / 10 > 5)
			{
				UpdatePosition(0, 1);
			}
		}
		else if (input::IsLeftKeyOn())
		{
			input::Set(input::LEFT_KEY_INDEX, false);
			if (update / 10 > 5)
			{
				UpdatePosition(-1, 0);
			}
		}
		else if (input::IsRightKeyOn())
		{
			input::Set(input::RIGHT_KEY_INDEX, false);
			if (update / 10 > 5)
			{
				UpdatePosition(1, 0);
			}
		}
		if (update / 10 > 5) {
			update -= 5*10;
		}
	}
	

	void Render() {
		char str1[10];
		
		sprintf_s(str1, "%02d,%02d", Player::getCurPosion().X, Player::getCurPosion().Y);
		ConsoleRenderer::ScreenClear();
		ConsoleRenderer::DrawMovableRect();
		ConsoleRenderer::DrawMap();
		ConsoleRenderer::ScreenSetString(100, 2, "½Ã°£", FG_PINK_DARK);
		ConsoleRenderer::ScreenSetString(100,20, str1, FG_WHITE);
		/*ConsoleRenderer::ScreenSetString(103,4, Player::getCurPosion().Y+'0', FG_WHITE);*/

		/*ConsoleRenderer::ScreenSetChar(100, 6, input::IsUpKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(101, 6, input::IsDownKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(102, 6, input::IsLeftKeyOn() + '0', FG_WHITE);
		ConsoleRenderer::ScreenSetChar(103, 6, input::IsRightKeyOn() + '0', FG_WHITE);*/
		if (g_clear) {
			ConsoleRenderer::ScreenSetString(100, 10, "isClear", FG_WHITE);
		}
		ConsoleRenderer::ScreenSetString(100, 4, timer, FG_WHITE);
		ConsoleRenderer::ScreenSetChar(Player::getCurPosion().X, Player::getCurPosion().Y, 'P', FG_WHITE);
		ConsoleRenderer::ScreenFlipping();
		
	}

	void Quit() {
		ConsoleRenderer::ScreenRelease();
	}

	void setTimer(char* str) {
		char str1[10];
		char str2[10];
		int mineat = 00;
		int second = 00;
		mineat = elepsedTime / 1000 /60;
		second = elepsedTime / 1000 % 60;
		
		//sprintf_s(str1, "%03d", elepsedTime);
		
		sprintf_s(str1, "%03d : %02d", mineat, second);
		//sprintf_s(str2, "%02d", second);
		int i = 0;
		while (str1[i] == '\0'|| i < TIMER_BUFF) {
			str[i] = str1[i];
			i++;
		}
		str[i] = '\0';
	}

	bool isClear() {
		COORD p_pos = Player::getCurPosion();
		COORD goal = { 61,20 };
		if (p_pos.X == goal.X && p_pos.Y == goal.Y)
		{
			return true;
		}
		return false;
	}
}