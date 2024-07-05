#pragma once

#define MAX_LOADSTRING 100

class WinAppMain
{
	HINSTANCE hInst;							  //윈도우 인스턴스
	HWND hWnd;									  //윈도우 핸들
	std::wstring szTitle;                  // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
	D2DRender* pD2DRender;

	public:
		WinAppMain();
		WinAppMain(const wchar_t* szTitle);
		~WinAppMain();
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
		void RunMessageLoop();
		void Finalize();
};

