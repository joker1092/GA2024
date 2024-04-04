#include "ConsoleRenderer.h"
#include <stdio.h>

namespace ConsoleRenderer {
	HANDLE hConsoleHandle;

	int screenWidth = 0;
	int screenHeight = 0;
	int screenBufferSize = 0;
	int screenBufferIndex = 0;
	HANDLE screenBuffer[2];

	SMALL_RECT consoleScreenSize;
	SMALL_RECT playerMovableRect = { 3,2,61,20 };
	COORD start = {3,2};
	HANDLE GetCurrentScreenBufferHandle() {
		return screenBuffer[screenBufferIndex];
	}

	

	void ScreenInit() {
		hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
		CONSOLE_CURSOR_INFO cursorInfo = { 0, };
		cursorInfo.bVisible = FALSE;
		cursorInfo.dwSize = 1;
		SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
		SetConsoleCursorInfo(screenBuffer[0], &cursorInfo);
		SetConsoleCursorInfo(screenBuffer[1], &cursorInfo);

		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsoleHandle, &info);

		screenHeight = info.srWindow.Bottom - info.srWindow.Top + 1;
		screenWidth = info.srWindow.Right - info.srWindow.Left + 1;
		screenBufferSize = screenHeight * screenWidth;
	}

	void ScreenFlipping() {
		SetConsoleActiveScreenBuffer(GetCurrentScreenBufferHandle());

		screenBufferIndex++;
		screenBufferIndex = screenBufferIndex % 2;
	}

	void ScreenClear() {
		COORD coor = { 0,0 };
		DWORD dw;
		FillConsoleOutputCharacter(GetCurrentScreenBufferHandle(), ' ', screenBufferSize, coor, &dw);
	}

	void ScreenRelease() {
		CloseHandle(screenBuffer[0]);
		CloseHandle(screenBuffer[1]);
	}



	


    bool ScreenSetChar(int x, int y, char ch, WORD attr)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        bRval = FillConsoleOutputCharacter(GetCurrentScreenBufferHandle(), ch, 1, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputCharacter()\n");

        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), attr, 1, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }

    bool ScreenSetString(int x, int y, const char* pStr, WORD attr)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        DWORD nNumberOfBytesToWrite = (DWORD)strlen(pStr);

        SetConsoleCursorPosition(GetCurrentScreenBufferHandle(), cdPos);
        WriteFile(GetCurrentScreenBufferHandle(), pStr, nNumberOfBytesToWrite, &dwCharsWritten, NULL);

        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), attr, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }

    bool ScreenSetAttr(WORD attr)
    {
        COORD	cdPos;
        bool	bRval = FALSE;
        DWORD	dwCharsWritten;
        //	int x,y;	

        cdPos.X = 0;
        cdPos.Y = 0;
        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), attr, screenBufferSize, cdPos, &dwCharsWritten);
        if (bRval == false)
        {
            printf("Error, FillConsoleOutputCharacter()\n");
            return bRval;
        }

        return bRval;
    }


	void DrawMovableRect()
	{
		
		// 위쪽 라인. Y 값이 고정 된다.
		for (int x = playerMovableRect.Left - 1; x < playerMovableRect.Right + 1; x++)
		{
			/*GotoXY(x, global::playerMovableRect.Top - 1);
			putchar('#');*/
			ConsoleRenderer::ScreenSetChar(x, playerMovableRect.Top - 1, '#', FG_WHITE);
		}

		// 아래쪽 라인. Y 값이 고정 된다.
		for (int x = playerMovableRect.Left - 1; x < playerMovableRect.Right + 1; x++)
		{
			/*GotoXY(x, global::playerMovableRect.Bottom + 1);
			putchar('#');*/
			ConsoleRenderer::ScreenSetChar(x, playerMovableRect.Bottom + 1, '#', FG_WHITE);
		}

		// 왼쪽 라인, X 값이 고정 된다.
		for (int y = playerMovableRect.Top - 1; y < playerMovableRect.Bottom + 1; y++)
		{
			/*GotoXY(global::playerMovableRect.Left - 1, y);
			putchar('#');*/
			ConsoleRenderer::ScreenSetChar(playerMovableRect.Left - 1, y, '#', FG_WHITE);
		}

		// 오른쪽 라인, X 값이 고정 된다.
		for (int y = playerMovableRect.Top - 1; y < playerMovableRect.Bottom + 1; y++)
		{
			/*GotoXY(global::playerMovableRect.Right + 1, y);
			putchar('#');*/
			ConsoleRenderer::ScreenSetChar(playerMovableRect.Right + 1, y, '#', FG_WHITE);
		}
	}
	void DrawMap()
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 59; j++)
			{
				COORD position = { j,i };
				char ch = ' ';
				if (Map::PositionState(position) == 1)
				{
					ch = '#';
				}
				ConsoleRenderer::ScreenSetChar(playerMovableRect.Left +j, playerMovableRect.Top + i, ch, FG_WHITE);
			}
		}
	}

    int ScreenWidth()
    {
        return screenWidth;
    }
    int ScreenHeight()
    {
        return screenHeight;
    }

	COORD InitPosition() {
		return start;
	}

}