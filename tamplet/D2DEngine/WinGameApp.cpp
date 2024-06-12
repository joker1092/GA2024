#include "WinGameApp.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void WinGameApp::Initialize(HINSTANCE hInstance, LPCTSTR appName)
{
	m_hInstance = hInstance;
	//const TCHAR* appName = TEXT("Test Game Framework");
	pRender = new D2DRenderer();
	pInput = new InputManager();

	//Step 1: Registering the Window Class

	//ChangeResolution(1280, 720, 32, 60);

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D2DENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = appName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);




	// Step 2: Creating the Window

	SIZE clientSize = { 1280, 720 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CXSCREEN);
	//RECT clientRect = { 0, 0, width, height };

	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);


	m_hWnd = CreateWindowW(appName, appName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!m_hWnd)
	{
		MessageBox(NULL, L"CreateWindowW fail", L"error", MB_OK | MB_ICONERROR);
		return;
	}


	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	//ShowWindow(m_hWnd, SW_MAXIMIZE);

	UpdateWindow(m_hWnd);

	/*HIMC hIMC = ImmCreateContext();
	ImmAssociateContext(m_hWnd, hIMC);*/

	//Render::InitRender(m_hWnd, clientSize.cx, clientSize.cy);
	if (!pRender->D2DInitialize(m_hWnd)) {
		MessageBox(NULL, L"D2DInitialize fail", L"error", MB_OK | MB_ICONERROR);
		return;
	}
		
	// Step 3: Game Initialize Here
	//Game::GameManager::GetInstance()->Initialize();
	pInput->InitInput(m_hWnd,width,height);

}

void WinGameApp::Run()
{
	HACCEL hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_D2DENGINE));

	MSG msg;
	// 기본 메시지 루프입니다:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			else if (msg.message == WM_KEYDOWN)
			{
				pInput->IsKeyDown(msg.wParam);
				//Input::KeyDown(msg.wParam);
			}
			else if (msg.message == WM_KEYUP)
			{
				pInput->KeyUp(msg.wParam);
				//Input::KeyUp(msg.wParam);
			}

			// 마우스 좌클릭 메시지
			if (msg.message == WM_LBUTTONDOWN)
			{	
				pInput->IsKeyDown(msg.wParam);
			}
			else if (msg.message == WM_LBUTTONUP) {
				pInput->KeyUp(msg.wParam);
				//Input::KeyUp(msg.wParam);
			}

			// 마우스 좌클릭 메시지
			if (msg.message == WM_RBUTTONDOWN)
			{
				pInput->IsKeyDown(msg.wParam);
				//Input::KeyDown(msg.wParam);
			}
			else if (msg.message == WM_RBUTTONUP) {
				pInput->KeyUp(msg.wParam);
				//Input::KeyUp(msg.wParam);
			}

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			Update(pInput);
			pRender->BeginDraw();
			pRender->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
			Render(pRender);
			pRender->EndDraw();
		}
	}
}


void WinGameApp::Uninitialize()
{
	pRender->D2DUninitialize();
}



bool IsWindowFullscreen(HWND hWnd)
{
	// Get the window style
	LONG style = GetWindowLong(hWnd, GWL_STYLE);

	// Check if the window has the fullscreen style
	return ((style & WS_POPUP) == WS_POPUP);
}

void EnterFullscreen(HWND hWnd)
{
	// Retrieve the monitor handle
	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get the monitor info
	MONITORINFO monitorInfo = { sizeof(monitorInfo) };
	GetMonitorInfo(hMonitor, &monitorInfo);

	// Set the window style
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);

	// Set the window position and size to cover the entire monitor
	SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
		SWP_NOZORDER | SWP_FRAMECHANGED);
}

void ExitFullscreen(HWND hWnd)
{
	// Set the window style back to its original state
	SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);

	// Restore the window position and size
	SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::wstring str;
	switch (message)
	{

	case WM_KEYDOWN:
		//todo : intput
		
		if (wParam == VK_F11)
		{
			// Toggle fullscreen mode
			if (IsWindowFullscreen(hWnd))
				ExitFullscreen(hWnd);
			else
				EnterFullscreen(hWnd);
		}
		

		//str = L"Camera X : " + std::to_wstring(g_posCamera.x) + L" Camera Y : " + std::to_wstring(g_posCamera.y);
		//SetWindowText(hWnd, str.c_str());
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}