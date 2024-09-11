#include "framework.h"
#include "DX3DPersonal.h"
#include "Tutorial.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize memory validation
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Tutorial app(hInstance);

    if (!app.Initialize(1024, 768))
	{
		return -1;
	}

    return app.Run();

    // check memory validation
#ifdef _DEBUG
    _ASSERT(_CrtCheckMemory());
#endif
}


