
// 맴버함수의 반환값을 리턴하는 call_function 함수를 작성하려고 합니다.
// 아래 코드가 잘 실행되도록,
// 
// 1. call_function 함수를 template 으로 작성하세요.

#include <utility>
#include <iostream>

struct A { int func() { return 10; } };
struct B { char func() { return 'A'; } };

// 함수 템플릿 작성
template <typename T>
auto call_function(T& obj){
	return obj.func();
}

int main() {
	A a;
	auto val_a = call_function(a);			// a.func() 리턴
	std::cout << val_a << std::endl;		// 출력 : 10

	B b;
	auto val_b = call_function(b);			// b.func() 리턴
	std::cout << val_b << std::endl;		// 출력 : 'A'
}
