#include <iostream>
#include <type_traits>
#include <functional>

class S
{
public:
    void func_print_hello() { std::cout << "Hello" << std::endl; }
    std::function<void(S&)> obj_print_hello = &S::func_print_hello;		//
    int v = 999;
} s;

int main() {
    s.func_print_hello();				// Hello
    s.obj_print_hello(s);				// Hello

    std::invoke(&S::func_print_hello, s); // Hello
    std::invoke(&S::obj_print_hello, s);  // ?! ==>&S::func_print_hello;

    //std::invoke는 객체 레퍼런스 맴버로 대체합니다. 
    //따라서 invoke에 값을 할당하면 객체 레퍼런스의 맴버에 값을 할당하는 것과 같습니다. 

    std::invoke(&S::v, s);				// s.v		//맴버에 값 v
    std::invoke(&S::v, s) = 1;			// s.v = 1
    int x = std::invoke(&S::v, s);		// int x = s.v
}