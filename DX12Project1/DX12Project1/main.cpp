#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"

int width = 900;
int height = 600;

HWND g_hwnd = NULL;
BOOL g_bLoop = TRUE;

TCHAR* g_ClassName = _T("ExDx12");
extern TCHAR* g_WindowName;


BOOL InitWindow(int width, int height);
void ResizeWindow(HWND hWnd, UINT NewWidth, UINT NewHeight);
BOOL MessagePump();
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevIstance, LPSTR lpCmdLine, int nCmdShow) {

	//������ �ʱ�ȭ
	if (!InitWindow(width,height))
	{
		return 0;
	}

	//todo:dx�ʱ�ȭ

	//todo:���������� �ε�

	while (g_bLoop) {

		if (!MessagePump()) { //������ �� �Է� �޼��� ó��
			break;
		}

		//todo:��� ������

	}

	//����
	
	return 0;
}

//������ ���ν���
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

//������ �ʱ�ȭ
BOOL InitWindow(int width, int height) {
	WNDCLASSEX wc = { sizeof(WNDCLASS),CS_CLASSDC,MsgProc,0,0,GetModuleHandle(NULL),NULL,NULL ,NULL ,NULL ,g_ClassName ,NULL };
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	if (hWnd == NULL)
	{
		return FALSE;
	}
	
	ResizeWindow(hWnd, width, height);
	UpdateWindow(hWnd);
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	g_hwnd = hWnd;
	
	return TRUE;
}

//�޼��� ó��
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

//������ ũ�� ����
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