#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleRenderer.h"
#include "timer.h"
#include "InputSystem.h"


bool g_bQuit = false;
void FixedUpdate();
void Update();
void Render();
void ProcessInput();
//void PrintCountsPerSecond();

//COORD g_Player = { 0,0 };
//int p_Xpower = 0;
//int p_Ypower = 0;
//ULONGLONG elapsedTime = 0;

int main()
{
	ConsoleRenderer::ScreenInit();
	global::time::InitTime();

	global::curPlayerPos.X = 5;
	global::curPlayerPos.Y = 5;
	while (!g_bQuit)
	{
		global::time::UpdateTime();
		ProcessInput();
		FixedUpdate();
		Update();
		Render();
	};

	ConsoleRenderer::ScreenRelease();
}


void ProcessInput()
{
	global::input::UpdateInput();
	/*ULONGLONG detatime = timer::GetDeltaTime();
	double speed = 0.1;*/
	//p_Xpower = 0;
	//p_Ypower = 0;
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
	//	//g_Player.X-=detatime* speed;
	//	p_Xpower = (-1);
	//}
	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
	//	//g_Player.X+=detatime * speed;
	//	p_Xpower = 1;
	//}
	//if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
	//	//g_Player.Y-=detatime * speed;
	//	p_Ypower = (-1);
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
	//	//g_Player.Y+=detatime * speed;
	//	p_Ypower = 1;
	//}
	//if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //종료
	//	g_bQuit = true;
	//}
}
void FixedUpdate() {
	/*static ULONGLONG futime;
	ULONGLONG detatime = global::time::GetDeltaTime();
	double speed = 0.2;
	futime += global::time::GetDeltaTime();
	if (futime >50)
	{
		global::time::fixedUpdateCount++;
		g_Player.X += p_Xpower * (detatime * speed);
		g_Player.Y += p_Ypower * (detatime * speed);
		futime = 0;
	} */
}

void Clamp(short& n, short min, short max) {
	if (n < min)n = min;
	if (n > max)n = max;
}


void UpdatePlayerPosition()
{
	global::prePlayerPos = global::curPlayerPos; // 현재 위치 경신 전에 일단, 저장. 구조체를 쓰면 이런게 편한겁니다. :)

	if (global::input::IsUpKeyOn())
	{
		global::input::Set(global::input::UP_KEY_INDEX, false);

		global::curPlayerPos.Y--;
		Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom); // 이동 범위를 제한 합니다. 
	}

	if (global::input::IsDownKeyOn())
	{
		global::input::Set(global::input::DOWN_KEY_INDEX, false);

		global::curPlayerPos.Y++;
		Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);
	}

	if (global::input::IsLeftKeyOn())
	{
		global::input::Set(global::input::LEFT_KEY_INDEX, false);

		global::curPlayerPos.X--;
		Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
	}

	if (global::input::IsRightKeyOn())
	{
		global::input::Set(global::input::RIGHT_KEY_INDEX, false);

		global::curPlayerPos.X++;
		Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
	}
}

void UpdatePlayer()
{
	// 키 입력과 화면 출력과 게임 로직 갱신을 분리해서 생각해 봅시다.
	static ULONGLONG elapsedTime;

	elapsedTime += global::time::GetDeltaTime();

	while (elapsedTime >= global::playerMoveSpeed)
	{
		UpdatePlayerPosition();

		elapsedTime -= global::playerMoveSpeed;
	}
}

void Update()
{
	UpdatePlayer();
	/*global::time::updateCount++;
	if (g_Player.X < 0) g_Player.X = 0;
	if (g_Player.X >= ConsoleRenderer::ScreenWidth()) g_Player.X = ConsoleRenderer::ScreenWidth() - 1;
	if (g_Player.Y < 0) g_Player.Y = 0;
	if (g_Player.Y >= ConsoleRenderer::ScreenHeight()) g_Player.Y = ConsoleRenderer::ScreenHeight() - 1;*/
}

void DrawMovableRect()
{
	// 위쪽 라인. Y 값이 고정 된다.
	for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++)
	{
		/*GotoXY(x, global::playerMovableRect.Top - 1);
		putchar('#');*/
		ConsoleRenderer::ScreenSetChar(x, global::playerMovableRect.Top - 1, '#', FG_WHITE);
	}

	// 아래쪽 라인. Y 값이 고정 된다.
	for (int x = global::playerMovableRect.Left - 1; x < global::playerMovableRect.Right + 1; x++)
	{
		/*GotoXY(x, global::playerMovableRect.Bottom + 1);
		putchar('#');*/
		ConsoleRenderer::ScreenSetChar(x, global::playerMovableRect.Bottom + 1, '#', FG_WHITE);
	}

	// 왼쪽 라인, X 값이 고정 된다.
	for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++)
	{
		/*GotoXY(global::playerMovableRect.Left - 1, y);
		putchar('#');*/
		ConsoleRenderer::ScreenSetChar(global::playerMovableRect.Left - 1, y, '#', FG_WHITE);
	}

	// 오른쪽 라인, X 값이 고정 된다.
	for (int y = global::playerMovableRect.Top - 1; y < global::playerMovableRect.Bottom + 1; y++)
	{
		/*GotoXY(global::playerMovableRect.Right + 1, y);
		putchar('#');*/
		ConsoleRenderer::ScreenSetChar(global::playerMovableRect.Right + 1, y, '#', FG_WHITE);
	}
}

void Render()
{


	ConsoleRenderer::ScreenClear();
	DrawMovableRect();
	//PrintCountsPerSecond();
	//ConsoleRenderer::ScreenSetString(0, 0, "Hello 안녕", FG_PINK_DARK);
	ConsoleRenderer::ScreenSetChar(global::curPlayerPos.X, global::curPlayerPos.Y, 'P', FG_WHITE);

	ConsoleRenderer::ScreenFlipping();
}

//void PrintCountsPerSecond() {
//	char s1[17];
//	int updateCount = global::time::updateCount;
//	int fixedUpdateCount = global::time::fixedUpdateCount;
//	char cUtime[10];
//	char cFUtime[10];
//	/*char ustamp[] = "update Count : ";
//	char fstamp[] = "fixed Update Count : ";*/
//	//elapsedTime += global::time::GetDeltaTime();
//	//sprintf_s(s1, "%lld", elapsedTime);
//	sprintf_s(cUtime, "%d", updateCount);
//	sprintf_s(cFUtime, "%d", fixedUpdateCount);
//	/*strcat(ustamp, cUtime);
//	strcat(fstamp, cFUtime);*/
//	ConsoleRenderer::ScreenSetString(0, 1, s1, FG_PINK_DARK);
//	ConsoleRenderer::ScreenSetString(0, 2, cUtime, FG_PINK_DARK);
//	ConsoleRenderer::ScreenSetString(1, 3, cFUtime, FG_PINK_DARK);
//	if (elapsedTime>=1000)
//	{
//		elapsedTime = 0;
//		global::time::updateCount = 0;
//		global::time::fixedUpdateCount = 0;
//	}
//}


