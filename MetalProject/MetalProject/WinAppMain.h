#pragma once

#define MAX_LOADSTRING 100

class WinAppMain
{
	HINSTANCE hInst;							  //������ �ν��Ͻ�
	HWND hWnd;									  //������ �ڵ�
	std::wstring szTitle;                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	D2DRender* pD2DRender;

	public:
		WinAppMain();
		WinAppMain(const wchar_t* szTitle);
		~WinAppMain();
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
		void RunMessageLoop();
		void Finalize();
};

