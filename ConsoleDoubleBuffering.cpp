// ConsoleDoubleBuffering.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleRenderer.h"


bool g_bQuit = false;
void Update();
void Render();
void ProcessInput();

COORD g_Player = { 0,0 };

int main()
{
	ConsoleRenderer::ScreenInit();

	while (!g_bQuit)
	{
		ProcessInput();
		Update();
		Render();
	};

	ConsoleRenderer::ScreenRelease();
}


void ProcessInput()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { //왼쪽
		g_Player.X--;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { //오른쪽
		g_Player.X++;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { //위
		g_Player.Y--;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //아래
		g_Player.Y++;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //종료
		g_bQuit = true;
	}

}

void Update()
{
	if (g_Player.X < 0) g_Player.X = 0;
	if (g_Player.X >= ConsoleRenderer::ScreenWidth()) g_Player.X = ConsoleRenderer::ScreenWidth() - 1;
	if (g_Player.Y < 0) g_Player.Y = 0;
	if (g_Player.Y >= ConsoleRenderer::ScreenHeight()) g_Player.Y = ConsoleRenderer::ScreenHeight() - 1;
}

void Render()
{
	ConsoleRenderer::ScreenClear();
	ConsoleRenderer::ScreenSetString(0, 0, "Hello 안녕", FG_PINK_DARK);
	ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y, 'P', FG_WHITE);
	ConsoleRenderer::ScreenFlipping();
}


