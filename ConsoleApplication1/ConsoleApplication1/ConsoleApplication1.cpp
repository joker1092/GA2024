#include <iostream>
#include <random>
#include <string>
#include<array>


std::array<int, 3> isStrinke(int num[], int d[]) //function with return type std::array
{
    std::array<int, 3> f_array; //array declared

    int strike = 0;
    int ball = 0;
    int out = 0;

    if (d[0] == num[0]) {
        strike++;
    }
    else if (d[0] == num[1] || d[0] == num[2])
    {
        ball++;
    }
    else {
        out++;
    }

    if (d[1] == num[1]) {
        strike++;
    }
    else if (d[1] == num[0] || d[1] == num[2])
    {
        ball++;
    }
    else {
        out++;
    }

    if (d[2] == num[2]) {
        strike++;
    }
    else if (d[2] == num[0] || d[2] == num[1])
    {
        ball++;
    }
    else {
        out++;
    }

    f_array[0] = strike;
    f_array[1] = ball;
    f_array[2] = out;

    return f_array; //array returned
}



int main()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> dist{0,9};
    int setnum[3] = { 0,0,0 };
    /*int a = dist(eng);
    int b = dist(eng);
    int c = dist(eng);*/
    //int selectnum[3] = { 0,0,0 };
    //int d = 0, e = 0, f =0;
    std::string d;
    std::array<int, 3> selectnum;

    setnum[0] = dist(eng);
    while (setnum[0] == setnum[1] || setnum[0] == setnum[2] || setnum[1] == setnum[2])
    {

        setnum[1] = dist(eng);
        setnum[2] = dist(eng);
    }
    int count = 0;
    int strike = 0;
    int ball = 0;
    int out = 0;
    while (count != 10)
    {
        selectnum = { 0,0,0 };


        //std::cout << a << b << c << std::endl;
        //int setnum[3] = { 0, 0, 0 };

        //std::cin >> d >> e >> f;
        std::cout << "3개의 숫자를 입력해주세요" << std::endl;
        std::cin >> d;

        /*std::cout << "d0" << d[0] << std::endl;;
        std::cout << "d1" << d[1] << std::endl;;
        std::cout << "d2" << d[2] << std::endl;;*/
        int temp[3] = { (d[0]-'0'),(d[1] - '0'),(d[2] - '0') };
        
        

        selectnum = isStrinke(setnum, temp);

        strike = selectnum[0];
        ball = selectnum[1];
        out = selectnum[2];

        std::cout << "strike" << strike << std::endl;;
        std::cout << "ball" << ball << std::endl;;
        std::cout << "out" << out << std::endl;;

        /*if (d[0] == a) {
            strike++;
        }else if (d[0]==b|| d[0] == c)
        {
            ball++;
        }
        else {
            out++;
        }*/
        count++;
        if (strike == 3) {
            break;
        }
    }

    if (strike == 3)
    {
        std::cout << "축하합니다. 정답은" << std::endl;
        std::cout << setnum[0] << setnum[1] << setnum[2] << std::endl;
    }else if (count == 10)
    {
        std::cout << "아쉽지만. 정답은" << std::endl;
        std::cout << setnum[0] << setnum[1] << setnum[2] << std::endl;
    }
    else {
        std::cout << "이건 뭐야 왜 나와" << std::endl;
    }
   
    //std::cout << "Hello World!\n";
}
