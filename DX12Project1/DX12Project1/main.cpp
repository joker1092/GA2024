#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"

int width = 900;
int height = 600;

HWND g_hWnd = NULL;
BOOL g_bLoop = TRUE;

TCHAR* g_ClassName = _T("ExDx12");
extern TCHAR* g_WindowName;


BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
BOOL MessagePump();
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevIstance, LPSTR lpCmdLine, int nCmdShow) {

	//윈도우 초기화
	if (!InitWindow(width,height))
	{
		return 0;
	}

	//todo:dx초기화
	if (FAILED(DXSetup(g_hWnd)))
	{
		return 0;
	}

	//todo:렌더데이터 로딩
	if (!DataLoading())
	{
		g_bLoop = FALSE;
	}

	while (g_bLoop) {

		if (!MessagePump()) { //윈도우 및 입력 메세지 처리
			break;
		}

		//todo:장면 렌더링
		SceneRender();

	}

	//종료
	DataRelease();
	DXRelease();
	
	return 0;
}

//윈도우 프로시저
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//윈도우 초기화
BOOL InitWindow(int width, int height) {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0,0,GetModuleHandle(NULL),NULL,NULL ,NULL ,NULL ,g_ClassName ,NULL };
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	if (hWnd == NULL)
	{
		return FALSE;
	}
	
	ResizeWindow(hWnd, width, height);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	g_hWnd = hWnd;
	
	return TRUE;
}

//메세지 처리
BOOL MessagePump() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message==WM_QUIT)
			{
				return FALSE;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			return TRUE;
		}
	}

	return FALSE;
}

//윈도우 크기 조정
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight) {

	RECT oldrc;
	GetWindowRect(hWnd, &oldrc);

	DWORD style = (DWORD)GetWindowLong(hWnd, GWL_STYLE);
	DWORD exstyle = (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE);

	RECT newrc = { 0,0,(LONG)NewWidth,(LONG)NewHeight };

	AdjustWindowRectEx(&newrc, style, NULL, exstyle);

	int newWidth = (newrc.right - newrc.left);
	int newHeight = (newrc.bottom - newrc.top);

	SetWindowPos(hWnd, HWND_NOTOPMOST, oldrc.left, oldrc.top, newWidth, newHeight, SWP_SHOWWINDOW);
}