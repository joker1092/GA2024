#include "ConsoleRenderer.h"
#include <stdio.h>


/*

    Windows 11 22H2에서는 콘솔 창을 호스트하는 데 사용되는 기본 앱이 Windows 터미널 변경되었습니다.
    * 몇몇 콘솔창 관련 함수가 작동안함.
    https://support.microsoft.com/ko-kr/windows/windows-11-%EB%8C%80%ED%95%9C-%EB%AA%85%EB%A0%B9-%ED%94%84%EB%A1%AC%ED%94%84%ED%8A%B8-%EB%B0%8F-windows-powershell-6453ce98-da91-476f-8651-5c14d5777c20
*/
namespace ConsoleRenderer
{
    HANDLE hConsoleHandle;      // 초기 화면 콘솔의 핸들

    int nScreenWidth = 0; // 콘솔창의 너비
    int nScreenHeight = 0; // 콘솔창의 높이
    int nScreenBufferSize = 0; // 콘솔창의 스크린버퍼 크기
    int nScreenBufferIndex = 0; // 콘솔창이 사용할 스크린버퍼의 인덱스
    HANDLE hScreenBuffer[2];

    HANDLE GetCurrentScreenBufferHandle()
    {
        return hScreenBuffer[nScreenBufferIndex];
    }

    void ScreenInit()
    {
        // 현재 화면크기에 맞는 화면 콘솔스크린버퍼 2개를 만든다.    
        hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        hScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        hScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        // 기본 콘솔,생성된 콘솔스크린 모두 커서 안보이게 설정
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.bVisible = FALSE;
        cursorInfo.dwSize = 1; // 커서의 크기를 결정 (1~100 사이만 가능)
        SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
        SetConsoleCursorInfo(hScreenBuffer[0], &cursorInfo);
        SetConsoleCursorInfo(hScreenBuffer[1], &cursorInfo);

        //기본 콘솔의 화면 크기 정보를 얻는다.
        CONSOLE_SCREEN_BUFFER_INFO Info; // 초기 화면 콘솔의 화면 정보
        GetConsoleScreenBufferInfo(hConsoleHandle, &Info);

        nScreenHeight = Info.srWindow.Bottom - Info.srWindow.Top + 1;
        nScreenWidth = Info.srWindow.Right - Info.srWindow.Left + 1;
        nScreenBufferSize = nScreenWidth * nScreenHeight;
    }

    void ScreenFlipping()
    {
        // 실제 콘솔이 사용할 스크린버퍼의 Handle을 설정하여 화면에 보여준다.
        SetConsoleActiveScreenBuffer(GetCurrentScreenBufferHandle());
        // 다음에 사용할 스크린 버퍼의 인덱스를 증가시켜 준비한다.
        nScreenBufferIndex++;
        nScreenBufferIndex = nScreenBufferIndex % 2;  // 0,1,0,1,0,1,0,1....
    }

    void ScreenClear()
    {
        COORD Coor = { 0, 0 };
        DWORD dw;
        FillConsoleOutputCharacter(GetCurrentScreenBufferHandle(), ' ', nScreenBufferSize, Coor, &dw);
    }

    void ScreenRelease()
    {
        CloseHandle(hScreenBuffer[0]);
        CloseHandle(hScreenBuffer[1]);
    }




    /*
        FOREGROUND_BLUE	텍스트 색에 파란색이 포함됩니다.
        COMMON_LVB_LEADING_BYTE	선행 바이트입니다.

        https://learn.microsoft.com/ko-kr/windows/console/console-screen-buffers#character-attributes
    */


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
        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), attr, nScreenBufferSize, cdPos, &dwCharsWritten);
        if (bRval == false)
        {
            printf("Error, FillConsoleOutputCharacter()\n");
            return bRval;
        }

        return bRval;
    }


    int ScreenWidth()
    {
        return nScreenWidth;
    }
    int ScreenHeight()
    {
        return nScreenHeight;
    }
};



