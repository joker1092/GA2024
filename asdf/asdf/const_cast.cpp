//c++ 타입변환 연산자 4가지
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//const_cast<new_type>(expression)
//const_cast는 const나 volatile 속성을 없애는 연산자
//상수성을 없에는 연산자

#include <iostream>



int main()
{
    //포인터 변수의 상수성 제거
    char str[] = "apple";
    const char* ptr = str;
    std::cout << "before : " << str << std::endl;

    //ptr[0] = "Q"; //error
    //char* c = (char*)ptr;  //const를 제거
    char* c = const_cast<char*>(ptr);  //const를 제거
    c[0] = 'Q';
    std::cout << "after : " << str << std::endl;

    //참조형 변수의 상수성 제거
    int tmp = 15;
    const int& ref = tmp;
    std::cout << "before : " << tmp << std::endl;

    //ref = 20; //error

    int& ref2 = const_cast<int&>(ref);
    ref2 = 20;
    std::cout << "after : " << tmp << std::endl;

    // const가 나오면 같이 나오는 경우가 많음
    // cv_  ===> c : const, v : volatile
    // cvr_ ===> c : const, v : volatile, r : reference

    volatile int v = 10;
    //volatile 휘발성
    //항상 메모리에 있는 변수를 읽어옴
    //컴파일러가 최적화를 하지 않음


    return 0;
}