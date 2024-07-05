#include "DemoGame.h"
#include "DemoGameApp.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    DemoGameApp App;
    App.Initialize(hInstance,L"���� ����");
    App.Run();
    App.Uninitialize();

    bool bUseConsole = true;
    if (bUseConsole)
    {
        AllocConsole();
        FILE* _tempFile;
        freopen_s(&_tempFile, "CONOUT$", "w", stdout);
    }
}
