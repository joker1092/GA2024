#include "WinMain.h"
// �� ����
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)



//AnimationResource* g_PlayerAnim;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool g_Mirror = false;
// ���־� ��Ʃ����� ���� ���ø��� �ٸ� �߰����� ������ ���� �����ϱ� ����� ���� �����ϰ� �ۼ���.

// ������ ���ν��� �Լ� ����

//void LoadResource();
//void ReleaseResource();

namespace global
{
	WinApp winApp;

	const WinApp& GetWinApp()
	{
		return winApp;
	}
}

constexpr int SCREEN_START_LEFT = 0;

constexpr int SCREEN_START_TOP = 0;

#define SCREEN_WIDTH  1920									// We want a 800 pixel width resolution
#define SCREEN_HEIGHT 1080	

BOOL bFullScreen = FALSE;
const TCHAR* appName = TEXT("Test Game Framework");

void ChangeToFullScreen(int width, int height);

void WinApp::Initialize(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	//const TCHAR* appName = TEXT("Test Game Framework");

	//Step 1: Registering the Window Class

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);


	

	// Step 2: Creating the Window

	// ���ϴ� ũ�Ⱑ �����Ǿ� ����
	SIZE clientSize = { 1280, 720 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CXSCREEN);
	//RECT clientRect = { 0, 0, width, height };
	
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);


	m_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		SCREEN_START_LEFT, SCREEN_START_TOP, clientSize.cx, clientSize.cy, NULL, NULL, hInstance, NULL);
	//m_hWnd = CreateWindow(appName, appName, WS_POPUP | WS_SYSMENU,
	//	SCREEN_START_LEFT, SCREEN_START_TOP, width, height, NULL, NULL, hInstance, NULL);

	
	if (!m_hWnd)
	{
		MessageBox(NULL, L"������ ���� ����", L"����", MB_OK | MB_ICONERROR);
		return;
	}


	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	//ShowWindow(m_hWnd, SW_MAXIMIZE);
	
	UpdateWindow(m_hWnd);

	//Render::InitRender(m_hWnd, clientSize.cx, clientSize.cy);
	Render::InitRender(m_hWnd, width, height);

	// Step 3: Game Initialize Here
	Game::GameManager::GetInstance()->Initialize();
}


// ������Ʈ �Ӽ� -> ��Ŀ -> �ý��� -> ���� �ý��� -> Windows�� ����
// ������ �Լ� ����


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetBreakAlloc(170);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	global::winApp.Initialize(hInstance);

	bool bUseConsole = true;
	if (bUseConsole)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}	

	
	//LoadResource();

	// ��Ⱑ ���� �޼��� ����
	MSG msg;
	while (true)
	{
		// �޽����� ������ ó��, ������ �ٷ� ���� ������ �̵�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT �޽��� Ȯ��
			if (msg.message == WM_QUIT)
				break;

			if (msg.message == WM_KEYDOWN)
			{
				Input::KeyDown(msg.wParam);
			}
			else if (msg.message == WM_KEYUP)
			{
				Input::KeyUp(msg.wParam);
			}
			else
			{
				DispatchMessage(&msg);
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���� ����			
			Game::GameManager::GetInstance()->Run();
		}
	}

	//ReleaseResource();
	Game::GameManager::GetInstance()->Finalize();
	Game::GameManager::GetInstance()->ReleaseResource();
	Game::GameManager::GetInstance()->DestroyInstance();
	if (bUseConsole)
	{
		FreeConsole();
	}
	
	//UnregisterClass(appName, hInstance);

	return static_cast<int>(msg.wParam);
}

// ������ ���ν��� �Լ� ����
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Game::GameManager::GetInstance()->Finalize();
		Game::GameManager::GetInstance()->ReleaseResource();
		Game::GameManager::GetInstance()->DestroyInstance();

		_CrtDumpMemoryLeaks();
		PostQuitMessage(0);
		
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
