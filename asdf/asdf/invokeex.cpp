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

    //std::invoke�� ��ü ���۷��� �ɹ��� ��ü�մϴ�. 
    //���� invoke�� ���� �Ҵ��ϸ� ��ü ���۷����� �ɹ��� ���� �Ҵ��ϴ� �Ͱ� �����ϴ�. 

    std::invoke(&S::v, s);				// s.v		//�ɹ��� �� v
    std::invoke(&S::v, s) = 1;			// s.v = 1
    int x = std::invoke(&S::v, s);		// int x = s.v
}