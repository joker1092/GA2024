

LRESULT CALLBACK WindowProc(HWND hwnd, UNIT uMsg, WPARAM wParam, LPARAM lParam);

ID2D1Factory* pFactory;
ID2dHwndRenderTarget* pRenderTarget;

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstancem,LPSTR lpCmdLine ,int nCmdShow) {

	WINDCLASSEX wc = {
		sizeof(WINDCLASSEX),CS_VREDRAW | CS_HREDRAW , WindowProc, 0, 0, GetModuleHandle(NULL),NULL,NULL,NULL,NULL,L"DX2DWindow",NULL
	};
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"DX2DWindow", L"DirectX 2D Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
}