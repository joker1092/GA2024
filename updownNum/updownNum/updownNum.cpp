#include <iostream>
#include <Windows.h>

int input() {
    int a;
    std::cout << "1~100사이의 숫자를 선택하세요(0.종료)" << std::endl;
    scanf_s("%d", &a);
    while(0<=a&&a>100)
    {
        std::cout << "잘 못 입력하셨습니다." << std::endl;
        std::cout << "1~100사이의 숫자를 선택하세요(0.종료)" << std::endl;
        scanf_s("%d", &a);
    }
    return a;
}

void rander(int set,int a) {
    if (a == 0) {
        std::cout << "게임을 종료합니다." << std::endl;
    }
    else if (set == a) {
        std::cout << "정답입니다." << std::endl;
        std::cout << "초기화 됩니다." << std::endl;
    }
    else if (set > a) {
        std::cout << "UP! 정답은 좀 더 큰 수 입니다." << std::endl;
    }
    else if (set < a) {
        std::cout << "DOWN! 정답은 좀 더 작은 수 입니다." << std::endl;
    }
    else {
        std::cout << "있을 수 없는 선택지 입니다." << std::endl;
    }
}

int main()
{
    srand(time(nullptr));
    int set;
    int a = -1;
    while (a != 0) {
        set = 1 + rand() % 100;
        while (set != a) {
            a = input();
            rander(set,a);
            if (a == 0) {
                break;
            }
        }
        
        Sleep(1000);
        system("cls");
        Sleep(1000);
    }
    return 0;
}


