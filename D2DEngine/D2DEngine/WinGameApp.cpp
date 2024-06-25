#include "WinGameApp.h"

ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR _szTitle);
BOOL InitInstance(HINSTANCE hInstance, HWND& m_hWnd, LPCTSTR _szTitle);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.


WinGameApp::WinGameApp()
{
    pD2DRender = new D2DRender;
    pTime = new TimeSystem;
    pResouceManager = new ResourceManager(pD2DRender);
}

WinGameApp::~WinGameApp()
{
    delete pResouceManager;
    delete pTime;
    delete pD2DRender;
}

void WinGameApp::Initialize(HINSTANCE _hInstance, LPCTSTR _szTitle)
{
    hInst = _hInstance;
    MyRegisterClass(hInst, _szTitle);

    

    bool bUseConsole = true;
    if (bUseConsole)
    {
        AllocConsole();
        FILE* _tempFile;
        freopen_s(&_tempFile, "CONOUT$", "w", stdout);
    }

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInst, m_hWnd,_szTitle))
    {
        return;
    }

    if (!pD2DRender->D2DIntialize(m_hWnd))
    {
        return;
    }

    pTime->InitTime();
}

int WinGameApp::Run()
{
    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(109));

    MSG msg;
    // 기본 메시지 루프입니다:
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
            DispatchMessage(&msg);
        }
        else {
            pTime->UpdateTime();
            Update(pTime->GetDeltaTime());
            pD2DRender->BeginDraw();
            pD2DRender->Clear(D2D1::ColorF(D2D1::ColorF::Black));
            Render(pD2DRender->GetRenderTarget());
            pD2DRender->EndDraw();
        }
       
    }
    return (int)msg.wParam;
}

void WinGameApp::UnInitialize()
{
    pD2DRender->D2DUnintialize();
}



// 
//
ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR _szTitle)
{
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
    wcex.lpszClassName = _szTitle;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));


    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance,HWND& m_hWnd, LPCTSTR _szTitle)
{

    m_hWnd = CreateWindowW(_szTitle, _szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }
    
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    //ShowWindow(m_hWnd, SW_MAXIMIZE);

    UpdateWindow(m_hWnd);

    return TRUE;
}


//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        //todo : intput
        //if (wParam == VK_F11)
        //{
        //    // Toggle fullscreen mode
        //    if (IsWindowFullscreen(hWnd))
        //        ExitFullscreen(hWnd);
        //    else
        //        EnterFullscreen(hWnd);
        //}
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case 104:
            //DialogBox(hInst, MAKEINTRESOURCE(103), hWnd, About);
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


//bool IsWindowFullscreen(HWND hWnd)
//{
//    // Get the window style
//    LONG style = GetWindowLong(hWnd, GWL_STYLE);
//
//    // Check if the window has the fullscreen style
//    return ((style & WS_POPUP) == WS_POPUP);
//}
//
//void EnterFullscreen(HWND hWnd)
//{
//    // Retrieve the monitor handle
//    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
//
//    // Get the monitor info
//    MONITORINFO monitorInfo = { sizeof(monitorInfo) };
//    GetMonitorInfo(hMonitor, &monitorInfo);
//
//    // Set the window style
//    SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
//
//    // Set the window position and size to cover the entire monitor
//    SetWindowPos(hWnd, HWND_TOP, monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
//        monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
//        monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
//        SWP_NOZORDER | SWP_FRAMECHANGED);
//}
//
//void ExitFullscreen(HWND hWnd)
//{
//    // Set the window style back to its original state
//    SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
//
//    // Restore the window position and size
//    SetWindowPos(hWnd, HWND_TOP, 0, 0, 1280, 960, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
//}