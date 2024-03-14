#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib,"d2d1.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

ID2D1Factory* pFactory;
ID2D1HwndRenderTarget* pRenderTarget;

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstancem,LPSTR lpCmdLine ,int nCmdShow) {

	WNDCLASSEX  wc = {
		sizeof(WNDCLASSEX),CS_VREDRAW | CS_HREDRAW , WindowProc, 0, 0, GetModuleHandle(NULL),NULL,NULL,NULL,NULL,L"DX2DWindow",NULL
	};
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"DX2DWindow", L"DirectX 2D Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);

	RECT rc;
	GetClientRect(hWnd, &rc);
	pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right, rc.bottom)), &pRenderTarget);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;

	while (GetMessage(&msg , NULL, 0 ,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	pRenderTarget->Release();
	pFactory->Release();

	return msg.wParam;
}