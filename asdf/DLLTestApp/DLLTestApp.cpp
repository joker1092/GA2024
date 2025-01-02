// DllTestApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <windows.h>
#include <iostream>
#include <cassert>
#include "../MyTestDll/FruitFactory.h"

#pragma comment(lib, "../x64/Debug/MyTestDll.lib")

#pragma data_seg("SHARDATA")

int g_shared_count = 0;

#pragma data_seg()

#pragma comment(linker, "/SECTION:SHARDATA,RWS")

//int TomatoFactory::stCount;
_declspec (dllexport) TomatoFactory g_TomatoFactory;


int main()
{
    TomatoFactory factory;
    factory.ShowCount();

    Tomato* tomato1 = factory.CreateTomato("뽀로로");
    Tomato* tomato2 = factory.CreateTomato("크롱");

    tomato1->ShowOwner();
    tomato2->ShowOwner();
    factory.ShowCount();

    system("pause");

    factory.DeleteTomato(tomato1);
    factory.DeleteTomato(tomato2);
    factory.ShowCount();

    return 0;
}
