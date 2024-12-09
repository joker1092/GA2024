#include "framework.h"
#include "personer3D.h"
#include "WinMainApp.h"

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