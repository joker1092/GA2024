#include <iostream>
using namespace std;
template<typename ... types>
void print(types ... agrs) {
    ((cout <<agrs<<" "), ...)<<endl;
}

template<typename T,typename ... types>
T diff_from(T init, types ... nums) {
    return (init - ... - nums);
}

template<typename ... types>
int foo(types ... nums) {
    
    return int((nums + ...));
}

template<typename ... types>
constexpr bool equal_val(types ... nums) {
    return ((nums == ...));
}

struct A { void func() { cout << "A::func()" << endl; } };
struct B { void func() { cout << "B::func()" << endl; } };

template<typename ... types>
struct overload:types...
{
    using types::func...;
};

template<int N>     //템플릿 인자로 정수를 받는 템플릿
struct Int {
    static const int num = N; //템플릿 Int //변수
};

template<typename T,typename U>     //템플릿 add //메타 함수
struct add {
    typedef Int<T::num + U::num> result; 
};;

template<typename T>
struct var {
    typedef T type;
    T value;
    operator = (T v) { value = v; }
};

int main()
{
    /*auto x = diff_from(100, 10, 20, 30);
    cout << x << endl;*/


    //std::cout << foo(1, 2, 3, 4, 5) << std::endl;

    /*cout << equal_val(1) << endl;
    cout << equal_val(1, 2) << endl;
    cout << equal_val(1, 2, 3) << endl;
    cout << equal_val(1, 1, 1, 1) << endl;*/

    /*A a;
    B b;

    auto func = overload{ a,b };

    func.A::func();
    func.B::func();*/

    typedef Int<1> one;
    typedef Int<2> two;

    typedef add<one, two>::result three;

    var v = { 10 };
    var str = { "Hello" };

    

    std::cout << "Addition resullt : " << three::num << std::endl;

    std::cout << add<Int<100>, Int<50>>::result::num << std::endl;


    return 0;
}