//c++ 타입변환 연산자 4가지
//1. static_cast
//2. dynamic_cast
//3. const_cast
//4. reinterpret_cast

//dynamic_cast<new_type>(expression)
//safe downcasting에 사용
//부모클래스의 포인터를 자식클래스의 포인터로 변환할때 사용
//실행시간에 다운캐스팅이 가능한지 검사
//참조 변수 에서도 사용 가능

//성공한 경우 : new_type의 value를 반환
//실패한 경우 : nullptr 반환
//참조에서 실패한 경우 : std::bad_cast 예외를 던짐


#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base()\n"; };
    virtual ~Base() { std::cout << "~Base()\n"; };
    void Show() { std::cout << "Base Show()" << std::endl; }
};

class Derived : public Base
{
public:
    int n = 0;
    Derived() { std::cout << "Derived()\n"; };
    ~Derived() { std::cout << "~Derived()\n"; };
    void Show() { std::cout << "Derived  Show()" << std::endl; }
};



int main()
{
    Base* b = new Derived(); //업캐스팅 Derived* -> Base*
    //Derived* d = new Base(); //다운캐스팅 Base* -> Derived* //error 
    //Derived* d = (Derived*)new Base(); //다운캐스팅 Base* -> Derived* //명시적 형변환은 가능 하나 위험
    //d->n = 0; //runtime error

    Derived* d = (Derived*)b; //안전한 다운캐스팅 //자식 --> 부모 --> 자식 으로 가는 경우
    d->n = 0; //ok


    return 0;
}