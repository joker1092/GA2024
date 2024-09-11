#pragma once
#include <windows.h>
#define MAX_LOADSTRING 100

class WinApp
{
public:
	WinApp(HINSTANCE hInstance);
	virtual ~WinApp();

	static HWND m_hWnd;		//자주필요하니 포인터 간접접근을 피하기위해 정적멤버로 만들었다.
	static WinApp* m_pInstance;

	HINSTANCE m_hInstance;                                // 현재 인스턴스입니다.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	WNDCLASSEXW m_wcex;
	MSG m_msg;
	UINT m_ClientWidth;
	UINT m_ClientHeight;


	virtual bool Initialize(UINT Width, UINT Height);
	virtual bool Run();
	virtual void Update(); // 상속 받은 클래스에서 구현
	virtual void Render() = 0; // 상속 받은 클래스에서 구현

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

