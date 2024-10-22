#include <iostream>
#include <list>
#include <type_traits>
using namespace std;


class Widget {};

template <typename T>
class MyAlloc {};

template <typename T>
struct MyAllocLIst{
    typedef std::list<T, MyAlloc<T>> type;
};

template <typename T>
using MyAllocLIst_t = std::list<T, MyAlloc<T>>;




int main() {

    


    MyAllocLIst<Widget>::type lw; 

    MyAllocLIst_t<Widget> lw;

    return 0;
}

//POD >> Plain Old Data
//메모리 상에서 연속전인 바이트 열
//개체를 POD로 취급하여야 하는 경우가 있다

//POD의 조건
//표준 레이아웃 타입 이어야 한다
//간단한 타입(trivial type)이어야 한다
//--->
//<type_traits> 헤더의 is_pod<T> 템플릿을 사용하여 확인 가능

//표준 레이아웃 타입
//C와 분명하게 호환되는 같은 레이아웃을 가진 타입
//--->
//가상함수나 가상 기저 클래스를 갖지 않는 클래스
//모든 비정적 데이터 멤버를 동일한 접근 지정자로 선언
//모든 기저 클래스가 표준 레이아웃 타입이어야 한다
//--->
// <type_traits> 헤더의 is_standard_layout<T> 템플릿을 사용하여 확인 가능

//간단한 타입
//간단한 기본 생성자 및 소멸자 함수를 가진 타입
//복사 생성자, 복사 대입 연산자, 이동 생성자, 이동 대입 연산자가 모두 없거나 각각이 간단한 형태로 존재
//--->
// <type_traits> 헤더의 is_trivial<T> 템플릿을 사용하여 확인 가능