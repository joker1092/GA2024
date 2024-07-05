// Metalslug.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Metalslug.h"
#include "MetalSlugWin.h"
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    MetalSlugWin* pMetalSlugWin = new MetalSlugWin();
    pMetalSlugWin->InitInstance(hInstance, nCmdShow);
    pMetalSlugWin->RunMessageLoop();
    


    return 0;
}






