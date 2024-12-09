// doSomething 함수의 호출 결과가
// rvalue, lvalue 모두 처리할 수 있도록,
// doSomething 함수를 수정하세요. ( 아래의 두가지 방식으로 각각 구현하세요.)
//
// 1. 함수 오버로딩을 활용하기
// 
// 2. 템플릿을 활용하여 하나의 코드로 해결하기

#include <iostream>
#include <vector>
using namespace std;

class Widget {
public:
    void doWork(void)& { cout << "&" << endl; }
    void doWork(void)&& { cout << "&&" << endl; }
};

//void doSomething(Widget w) { w.doWork(); }  //수정하세요. 
template<typename T>
void doSomething(T&& w) {forward<T>(w).doWork(); }

int main()
{
    Widget widget;

    doSomething(widget);                // 출력: &
    doSomething(Widget());              // 출력: &&  
}

