//c++ 타입변환 연산자 4가지
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast
//--> 
//c에서의 타입 변환의 문제점을 해결하기 위해 c++에서는 4가지 타입 변환 연산자를 제공
//c에서는 일반적이지 않은 형 변환도 가능했으며 암시적 형변환과 의도를 파악하기 어려운 형변환이 가능
//이는 일반적으로 프로그램의 가독성을 떨어뜨리고 버그를 발생시킬 수 있음

//static_cast<new_type>(expression)
//compile time에 타입을 변환하는 연산자
//논리적으로 변환 가능한 타입을 변환
//
//실수 -> 정수,열거형 -> 정수, 정수 -> 실수 등의 기본적 타입
//배열 -> 포인터
//함수 -> 함수 포인터
//클래스의 상속관계에서의 타입 변환 (자식 -> 부모(업캐스팅))
//예외적으로 부모 -> 자식(다운캐스팅)은 static_cast로 변환 불가능 (dynamic_cast 사용)
//다운케스팅은 컴파일에서 에러가 나지 않지만 런타임에서 에러가 날 수 있음
//이유는? 다운캐스팅은 런타임에 안전한지 확인해야 하기 때문


#include <iostream>

void foo() {};

void Func(void(*)()) {}

int main()
{
    Func(foo);
    auto func = foo;

    //일반 변수 타입 변환
    double d = 3.14;
    float f = 10.12f;

    d = f;          //암시적 형변환
    d = (double)f;  //명시적 형변환

    f = d;           // 8->4  데이터 손실
    f = (float)d;     // 손실은 있으나 명시적으로 의도를 표현

    int tmp_int;
    //tmp_int = (int)d; //c
    //tmp_int = int(d); //c++
    tmp_int = static_cast<int>(d);

    float tmp_float;
    tmp_float = static_cast<float>(d);

    int arr[3] = { 1,2,3 };
    //int* p = arr; 
    int* p = static_cast<int*>(arr); //배열을 포인터로 변환할때

    return 0;
}