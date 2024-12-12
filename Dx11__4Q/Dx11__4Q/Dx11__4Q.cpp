// Dx11__4Q.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinMainApp.h"
#include "Dx11__4Q.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WinMainApp app(hInstance);

    if (!app.Initialize(1024, 768))
    {
        return -1;
    }

    return app.Run();
}