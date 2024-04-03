#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int x = 0;
int y = 0;

void Test_GetAsyncKeyState() {
	if (GetAsyncKeyState(VK_UP) & 0x8000)y--;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)y++;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)x--;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)x++;
}

void Test_GetKeyState() {
	if (GetAsyncKeyState(VK_UP) < 0)y--;
	if (GetAsyncKeyState(VK_DOWN) < 0)y++;
	if (GetAsyncKeyState(VK_LEFT) < 0)x--;
	if (GetAsyncKeyState(VK_RIGHT) < 0)x++;
}

int main(void) {
	while (true)
	{
		gotoxy(x, y);
		putchar('@');
		Test_GetAsyncKeyState();
		Test_GetKeyState();
		Sleep(500);
	}
	return 0;
}