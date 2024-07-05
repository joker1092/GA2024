#include <iostream>
#include <string>
using namespace std;
//템플릿

//Generic Programming
//일반화 프로그래밍
//하나의 함수나 클래스를 여러 자료형에 대해 사용할 수 있도록 하는 프로그래밍 기법
//C++에서는 템플릿을 이용하여 구현

//템플릿 함수
//함수를 정의할 때 자료형을 일반화시킨다.

//템플릿 함수 정의
//t는 템플릿 매개변수
// 
// 컴파일러는 템플릿 함수를 기반으로 같은 형태의 함수를 생성한다.
// 템플릿 함수는 템플릿 매개변수에 따라 여러 형태의 함수로 생성된다.
// 이렇게 생성된 함수를 템플릿 함수라고 한다.
// 이렇게 함수가 생성되는 것을 함수의 인스턴스화라고 한다.
// 
// ==============================================================
// 
// 템플릿 클래스
// 다양한 자료형이 처리되는 클래스에서 사용
// 
// 
// 형식매개변수의 자동 추론 - decltype(auto)
//
//템플릿 특수화
//특정 자료형에 대해 템플릿 함수를 재정의하는 것
//템플릿 특수화는 템플릿 함수의 특수한 경우에 대해 별도로 정의하는 것
//ex>>
//template <typename T>
//T Add(T a, T b)
// {
// return a + b;
// }
//template <>
//char* Add(char* a, char* b)
// {
// return strcat(a, b);
// }

// 템플릿 특수화에서 주의사항
// 부분 특수화
// 함수는 부분 특수화가 불가능하다.


#include <iostream>
using namespace std;

template <typename T>
class A {
public:
    A(T t) : m_t(t) {}
    void print() {
		cout << "A::print()" << endl;
	}

    template <typename TT>      // 멤버 함수 템플릿
    void doSomething() {
        		cout << "A::doSomething()" << endl;
    };
    template <>      // 멤버 함수 템플릿
    void doSomething<float>() {
				cout << "A::doSomething<float>()" << endl;
	};
};





    int main()
    {
        A<int> a_int(123);
        a_int.print();
        a_int.doSomething<float>();
    }




