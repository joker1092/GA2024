// Dx2Dtest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "framework.h"
#include "Dx2Dtest.h"
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib,"dwrite.lib")

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ID2D1Factory* pD2DFactory;
ID2D1HwndRenderTarget* pRenderTarget;

ID2D1SolidColorBrush* pBlackBrush;
ID2D1SolidColorBrush* pGrayBrush;

IDWriteFactory* pDWriteFactory;
IDWriteTextFormat* pDWriteFormat;

IWICImagingFactory* pWICFactory;

ID2D1Bitmap* pD2DBitmap = nullptr;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL InitDirect2D();
void UninitDirect2D();
HRESULT D2DBitmapFromFile(const WCHAR* path, ID2D1Bitmap** ppID2D1Bitmap);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DX2DTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    if (!InitDirect2D())
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DX2DTEST));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0,PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            pRenderTarget->BeginDraw();

            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

            
            
            
            D2D1_SIZE_F screenSize = pRenderTarget->GetSize();
            for (float y = 0; y < screenSize.height; y += 10) {
                pRenderTarget->DrawLine(D2D1::Point2F(0.0f, y), D2D1::Point2F(screenSize.width, y), pBlackBrush, 0.5f);
            }

            pRenderTarget->FillRectangle(D2D1::RectF(screenSize.width / 2 - 150.0f, screenSize.height / 2 - 150.0f, screenSize.width / 2 + 150.0f, screenSize.height / 2 + 150.0f), pGrayBrush);
            pRenderTarget->DrawRectangle(D2D1::RectF(screenSize.width / 2 - 50.0f, screenSize.height / 2 - 50.0f, screenSize.width / 2 + 50.0f, screenSize.height / 2 + 50.0f), pBlackBrush);

            WCHAR wc_text[] = L"Hello, 대충 텍스트";
            pRenderTarget->DrawText(wc_text, ARRAYSIZE(wc_text) - 1, pDWriteFormat, D2D1::RectF(0, 0, screenSize.width, screenSize.height / 2), pBlackBrush);
            
            pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            D2D1_VECTOR_2F pos{ 0,0 };
            D2D1_SIZE_F bitmapSize = pD2DBitmap->GetSize();
            D2D1_RECT_F rect = { pos.x,pos.y,pos.x + bitmapSize.width * 1.5f,pos.y + bitmapSize.height * 1.5f };
            pRenderTarget->DrawBitmap(pD2DBitmap, rect);
            //pRenderTarget->DrawBitmap(pD2DBitmap);

            pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, pos.y + bitmapSize.height * 1.5f));
            pRenderTarget->DrawBitmap(pD2DBitmap);
            D2D1_MATRIX_3X2_F Matrix = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0));
            pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

            pRenderTarget->EndDraw();
        }
    }

    UninitDirect2D();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX2DTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DX2DTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
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


BOOL InitDirect2D() {
    HRESULT hr = S_OK;

    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    if (FAILED(hr))
    {
        return FALSE;
    }

    RECT rc;
    GetClientRect(hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(), 
        D2D1::HwndRenderTargetProperties(hWnd, size),
        &pRenderTarget);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBlackBrush);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &pGrayBrush);

    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = pDWriteFactory->CreateTextFormat(L"Cooper", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50.0f, L"", &pDWriteFormat);
    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
    if (FAILED(hr))
    {
        return FALSE;
    }
    hr = D2DBitmapFromFile(L"./Resource/kitten.png", &pD2DBitmap);
    if (FAILED(hr))
    {
        _com_error err(hr);
        ::MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
        //::MessageBox(hWnd, L"D2DBitmapFromFile Error", L"FAILED", MB_OK);
        return false;
    }

    pDWriteFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    pDWriteFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    return TRUE;
}

void UninitDirect2D() {

    if (pWICFactory)pWICFactory->Release();
    if (pDWriteFormat)pDWriteFormat->Release();
    if (pDWriteFactory)pDWriteFactory->Release();
    if (pBlackBrush) pBlackBrush->Release();
    if (pGrayBrush) pGrayBrush->Release();
    if (pRenderTarget) pRenderTarget->Release();
    if (pD2DFactory) pD2DFactory->Release();

    CoUninitialize();
}

HRESULT D2DBitmapFromFile(const WCHAR* path, ID2D1Bitmap** ppID2D1Bitmap) {
    HRESULT hr;
    IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

    hr = pWICFactory->CreateDecoderFromFilename(path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
    if (FAILED(hr))
    {
        //::MessageBox(hWnd, L"CreateDecoderFromFilename Error", L"FAILED", MB_OK);
        return hr;
    }

    IWICBitmapFrameDecode* pFrame = NULL;
    hr = pDecoder->GetFrame(0, &pFrame);
    if (FAILED(hr))
    {
       //::MessageBox(hWnd, L"GetFrame Error", L"FAILED", MB_OK);
        return hr;
    }

    hr = pWICFactory->CreateFormatConverter(&pConverter);
    if (FAILED(hr))
    {
        //::MessageBox(hWnd, L"CreateFormatConverter Error", L"FAILED", MB_OK);
        return hr;
    }

    hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
    if (FAILED(hr))
    {
        //::MessageBox(hWnd, L"pConverter Initialize Error", L"FAILED", MB_OK);
        return hr;
    }

    hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
    if (FAILED(hr))
    {
        //::MessageBox(hWnd, L"CreateBitmapFromWicBitmap Error", L"FAILED", MB_OK);
        return hr;
    }

    if (pConverter)pConverter->Release();
    if (pDecoder)pDecoder->Release();
    if (pFrame)pFrame->Release();
    

    return hr;

}