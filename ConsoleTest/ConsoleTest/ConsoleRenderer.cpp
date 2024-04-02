#include "ConsoleRenderer.h"
#include <stdio.h>

namespace ConsoleRenderer {
	HANDLE hConsoleHandle;

	int screenWidth = 0;
	int screenHeight = 0;
	int screenBufferSize = 0;
	int screenBufferIndex = 0;
	HANDLE screenBuffer[2];

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


	void DrawRect(int x, int y, int width, int height)
	{
		
		ScreenSetChar(x, y, char(201), FG_WHITE);
		for (int i = 1; i < width; i++)
		ScreenSetChar(x+i, y, char(205), FG_WHITE);
		ScreenSetChar(x + width, y, char(187), FG_WHITE);
		ScreenSetChar(x , height+ y, char(200), FG_WHITE);
		for (int i = 1; i < width; i++)
		ScreenSetChar(x + i, y, char(205), FG_WHITE);
		ScreenSetChar(x + width, y, char(188), FG_WHITE);
		for (int i = y + 1; i < height + y; i++)
		{
			ScreenSetChar(x, i, char(186), FG_WHITE);
			ScreenSetChar(x+ width, i, char(186), FG_WHITE);
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
}