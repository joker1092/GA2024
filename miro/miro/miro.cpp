#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleRenderer.h"

using namespace std;

#define MAX 10

void ProcessInput();
void Update();
void Render();
bool g_bQuit = false;

enum EMAZETYPE
{
   PATH,WALL,VISIT,BACK
};

struct Position
{
    int x, y;
};

struct MyStack
{
	Position Array[1000];
	int nTopIndex = -1;

	bool Empty() {
		if (nTopIndex==-1)
		{
			return true;
		}
		else {
			return false;
		}
	}
	int Size() {
		if (nTopIndex != -1) {
			return nTopIndex + 1;
		}
	}
	void Push(Position data) {
		nTopIndex++;
		Array[nTopIndex] = data;
	}
	void Pop() {
		Array[nTopIndex] = {-1,-1};
		nTopIndex--;
	}
	Position Top() {
		return Array[nTopIndex];
	}
};

int Maze[MAX][MAX] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

COORD g_Player = { 1,1 };

MyStack stack;

int main()
{

	ConsoleRenderer::ScreenInit();
	
	while (!g_bQuit)
	{
		//timer::UpdateTime();
		ProcessInput();
		/*FixedUpdate();*/
		Update();
		Render();
	};
	
	ConsoleRenderer::ScreenRelease();
}



void ProcessInput()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //종료
		g_bQuit = true;
	}
}

void Update() {
	int x = g_Player.X;
	int y = g_Player.Y;
	Position pos;
	
	pos = { x,y };
	
	if (x == 8 && y == 8)
	{
		const char* str = "Conguration Maze Complete";
		ConsoleRenderer::ScreenSetString(20, 20, str, FG_BLUE);
	/*	g_bQuit = true;*/
	}
	else {
		if (Maze[x][y - 1] == 0)
		{
			Maze[x][y] = 2;
			stack.Push(pos);
			g_Player.X = x;
			g_Player.X = y - 1;
		}
		else if (Maze[x + 1][y] == 0) {
			Maze[x][y] = 2;
			stack.Push(pos);
			g_Player.X = x + 1;
			g_Player.Y = y;
		}
		else if (Maze[x][y + 1] == 0) {
			Maze[x][y] = 2;
			stack.Push(pos);
			g_Player.X = x;
			g_Player.Y = y + 1;
		}
		else if (Maze[x - 1][y] == 0) {
			Maze[x][y] = 2;
			stack.Push(pos);
			g_Player.X = x - 1;
			g_Player.Y = y;
		}
		else {
			Maze[x][y] = 3;
			Position tmppos = stack.Top();
			g_Player.X = tmppos.x;
			g_Player.Y = tmppos.y;
			stack.Pop();
		}

	}
}


void Render()
{
	ConsoleRenderer::ScreenClear();
	for (int i = 0; i < MAX; ++i)
	{
		for (int j = 0; j < MAX; ++j)
		{
			if (j == g_Player.X &&  i== g_Player.Y)
			{
				continue;
			}
			char ch='\0';
			if (Maze[j][i]==0)
			{
				ch = ' ';
			}
			else if (Maze[j][i] == 1)
			{
				ch = '#';
			}
			else if (Maze[j][i] == 2)
			{
				ch = 'V';
			}
			else if (Maze[j][i] == 3)
			{
				ch = 'B';
			}
			ConsoleRenderer::ScreenSetChar(i, j, ch, FG_WHITE);
		}
	}
	ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y, 'P', FG_PINK_DARK);

	

	ConsoleRenderer::ScreenFlipping();
}

