#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    

    std::srand((unsigned int)std::time(nullptr)); 
    //std::time  Epoch 이후 달력 일수 에 마지막 Epoch 이후 경과한 초 수를 더한 86400배를 포함하는 정수 유형 값
    //std::srand std::rand()에서 사용하는 의사 난수 생성기에 값을 시드로 시드합니다.

    num1 = 1 + rand() % 9; 
    while (num1==num2||num1==num3||num2==num3) {
        num2 = 1 + rand() % 9;
        num3 = 1 + rand() % 9;
    }
    //중복 제거용 중복이 생기지 않을 시 까지 2번째 3번째 숫자를 다시 굴림
    //std::cout << num1 << num2 << num3; 
    
    int count = 0;
    int strike = 0;
    int ball = 0;
    int out = 0;
    while (count != 10)
    {
        char d[4]="";

        while (true) {
            std::cout << "3개의 숫자를 입력해주세요" << std::endl;
            std::cin >> d;
            if ((d[0] < '0' || d[0] >'9') || (d[1] < '0' || d[1] >'9') || (d[2] < '0' || d[2] >'9')) {
                std::cout << "잘 못 입력하셨습니다." << std::endl;
            }
            else {
                break;
            }
        }

        /*std::cout << "3개의 숫자를 입력해주세요" << std::endl;
        std::cin >> d;
        if ((d[0] < '0' || d[0] >'9')|| (d[1] < '0' || d[1] >'9')|| (d[2] < '0' || d[2] >'9')) {
            std::cout << "잘 못 입력하셨습니다." << std::endl;
        }*/
        

        /*std::cout << "d0" << d[0] << std::endl;;
        std::cout << "d1" << d[1] << std::endl;;
        std::cout << "d2" << d[2] << std::endl;;*/


        int temp[3] = { (d[0] - '0'),(d[1] - '0'),(d[2] - '0') };


        strike = 0;
        ball = 0;
        out = 0;

        if (temp[0] == num1) {
            strike++;
        }
        else if (temp[0] == num2 || temp[0] == num3)
        {
            ball++;
        }
        else {
            out++;
        }

        if (temp[1] == num2) {
            strike++;
        }
        else if (temp[1] == num1 || temp[1] == num3)
        {
            ball++;
        }
        else {
            out++;
        }

        if (temp[2] == num3) {
            strike++;
        }
        else if (temp[2] == num1 || temp[2] == num2)
        {
            ball++;
        }
        else {
            out++;
        }

        std::cout << "strike" << strike << std::endl;;
        std::cout << "ball" << ball << std::endl;;
        std::cout << "out" << out << std::endl;;

        count++;

        std::cout << 10-count << "기회가 남으셨습니다." << std::endl;;

        if (strike == 3) {
            break;
        }
    }

    if (strike == 3)
    {
        std::cout << "축하합니다. 정답은" << std::endl;
        std::cout << num1 << num2 << num3 << std::endl;
    }
    else if (count == 10)
    {
        std::cout << "아쉽지만. 정답은" << std::endl;
        std::cout << num1 << num2 << num3 << std::endl;
    }
    else {
        std::cout << "이건 뭐야 왜 나와" << std::endl;
    }

 
}