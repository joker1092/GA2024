#pragma once
#include <windows.h>
#define MAX_LOADSTRING 100

class WinApp
{
public:
	WinApp(HINSTANCE hInstance);
	virtual ~WinApp();

	static HWND m_hWnd;		//�����ʿ��ϴ� ������ ���������� ���ϱ����� ��������� �������.
	static WinApp* m_pInstance;

	HINSTANCE m_hInstance;                                // ���� �ν��Ͻ��Դϴ�.
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WNDCLASSEXW m_wcex;
	MSG m_msg;
	UINT m_ClientWidth;
	UINT m_ClientHeight;


	virtual bool Initialize(UINT Width, UINT Height);
	virtual bool Run();
	virtual void Update(); // ��� ���� Ŭ�������� ����
	virtual void Render() = 0; // ��� ���� Ŭ�������� ����

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

