#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleRenderer.h"
#include "timer.h"


bool g_bQuit = false;
void FixedUpdate();
void Update();
void Render();
void ProcessInput();
void PrintCountsPerSecond();

COORD g_Player = { 0,0 };
int p_Xpower = 0;
int p_Ypower = 0;
ULONGLONG elapsedTime = 0;

int main()
{
	ConsoleRenderer::ScreenInit();
	timer::InitTime();

	while (!g_bQuit)
	{
		timer::UpdateTime();
		ProcessInput();
		FixedUpdate();
		Update();
		Render();
	};

	ConsoleRenderer::ScreenRelease();
}


void ProcessInput()
{
	/*ULONGLONG detatime = timer::GetDeltaTime();
	double speed = 0.1;*/
	p_Xpower = 0;
	p_Ypower = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		//g_Player.X-=detatime* speed;
		p_Xpower = (-1);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
		//g_Player.X+=detatime * speed;
		p_Xpower = 1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		//g_Player.Y-=detatime * speed;
		p_Ypower = (-1);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		//g_Player.Y+=detatime * speed;
		p_Ypower = 1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //종료
		g_bQuit = true;
	}
}
void FixedUpdate() {
	static ULONGLONG futime;
	ULONGLONG detatime = timer::GetDeltaTime();
	double speed = 0.2;
	futime += timer::GetDeltaTime();
	if (futime >50)
	{
		timer::fixedUpdateCount++;
		g_Player.X += p_Xpower * (detatime * speed);
		g_Player.Y += p_Ypower * (detatime * speed);
		futime = 0;
	} 
}

void Update()
{
	timer::updateCount++;
	if (g_Player.X < 0) g_Player.X = 0;
	if (g_Player.X >= ConsoleRenderer::ScreenWidth()) g_Player.X = ConsoleRenderer::ScreenWidth() - 1;
	if (g_Player.Y < 0) g_Player.Y = 0;
	if (g_Player.Y >= ConsoleRenderer::ScreenHeight()) g_Player.Y = ConsoleRenderer::ScreenHeight() - 1;
}

void Render()
{


	ConsoleRenderer::ScreenClear();
	PrintCountsPerSecond();
	ConsoleRenderer::ScreenSetString(0, 0, "Hello 안녕", FG_PINK_DARK);
	ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y, 'P', FG_WHITE);

	ConsoleRenderer::ScreenFlipping();
}

void PrintCountsPerSecond() {
	char s1[17];
	int updateCount = timer::updateCount;
	int fixedUpdateCount = timer::fixedUpdateCount;
	char cUtime[10];
	char cFUtime[10];
	/*char ustamp[] = "update Count : ";
	char fstamp[] = "fixed Update Count : ";*/
	elapsedTime += timer::GetDeltaTime();
	sprintf_s(s1, "%lld", elapsedTime);
	sprintf_s(cUtime, "%d", updateCount);
	sprintf_s(cFUtime, "%d", fixedUpdateCount);
	/*strcat(ustamp, cUtime);
	strcat(fstamp, cFUtime);*/
	ConsoleRenderer::ScreenSetString(0, 1, s1, FG_PINK_DARK);
	ConsoleRenderer::ScreenSetString(0, 2, cUtime, FG_PINK_DARK);
	ConsoleRenderer::ScreenSetString(1, 3, cFUtime, FG_PINK_DARK);
	if (elapsedTime>=1000)
	{
		elapsedTime = 0;
		timer::updateCount = 0;
		timer::fixedUpdateCount = 0;
	}
}
