#include "WinApp.h"

namespace global
{
	WinApp winApp;

	const WinApp& GetWinApp()
	{
		return winApp;
	}
}

constexpr int SCREEN_START_LEFT = 10;

constexpr int SCREEN_START_TOP = 10;

constexpr int SCREEN_WIDTH = 1024;

constexpr int SCREEN_HEIGHT = 768;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    global::winApp.Initialize(hInstance);

    global::winApp.Run();

    global::winApp.Finalize();

    return EXIT_SUCCESS;
}

void WinApp::Initialize(HINSTANCE hInstance) {
    
    m_hInstance = hInstance;

    const TCHAR* appName = TEXT("Game Title");

    //Step 1: Registering the Window Class

    WNDCLASS wndClass;

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = appName;

    RegisterClass(&wndClass);

    // Step 2: Creating the Window
    
    RECT rect{ SCREEN_START_LEFT,SCREEN_START_TOP,SCREEN_START_LEFT + SCREEN_WIDTH,SCREEN_START_TOP + SCREEN_HEIGHT };

    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
}