#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class A
{
	int c;
public:
	A(int c):c(c){	}

	int class_func(){return c;}
	int class_func_const()const {return c;}
	static void class_static_func(){std::cout << "static func" << std::endl;}
};

int func() {return 0;}

int main()
{
	std::function<int()> f = &func;
	
	A a(5);
	std::function<int(A&)> cf1 = &A::class_func;
	std::function<int(A&)> cf2 = &A::class_func_const;
	std::function<void()> sf = &A::class_static_func;
	std:: cout << cf1(a) << " "
	<<cf2(a); 
	sf();
}