#include "pch.h"
#include "WinGameApp.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool WinGameApp::Intialize(HINSTANCE hInstance, LPCTSTR appName)
{
	//m_hInstance = hInstance;
	//const TCHAR* appName = TEXT("Test Game Framework");
	pRender = D2DRenderer::GetInstance();
	/*pInput = new InputManager();
	pTime = new TimeSystem();*/
	
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = appName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

	RegisterClassExW(&wcex);

	m_hWnd = CreateWindowW(appName, appName, WS_OVERLAPPEDWINDOW,
		0, 0, 1280, 960, nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd)
	{
		MessageBox(NULL, L"CreateWindowW fail", L"error", MB_OK | MB_ICONERROR);
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	UpdateWindow(m_hWnd);

	if (!pRender->D2DInitialize(m_hWnd)) {
		MessageBox(NULL, L"D2DInitialize fail", L"error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void WinGameApp::Run()
{
	MSG msg;
	// 기본 메시지 루프입니다:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			//pTime->UpdateTime();

			//Update(pInput);
			Update();

			//pInput->ResetInput();

			pRender->BeginDraw();

			pRender->Clear(D2D1::ColorF(D2D1::ColorF::Black));

			Render();

			pRender->EndDraw();
		}
	}
}



void WinGameApp::UnIntialize()
{
	pRender->D2DUninitialize();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::wstring str;
	switch (message)
	{

	case WM_KEYDOWN:
		//todo : intput

		//if (wParam == VK_F11)
		//{
		//	// Toggle fullscreen mode
		//	if (IsWindowFullscreen(hWnd))
		//		ExitFullscreen(hWnd);
		//	else
		//		EnterFullscreen(hWnd);
		//}


		//str = L"Camera X : " + std::to_wstring(g_posCamera.x) + L" Camera Y : " + std::to_wstring(g_posCamera.y);
		//SetWindowText(hWnd, str.c_str());
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case 104:
			//DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case 105:
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