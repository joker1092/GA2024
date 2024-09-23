//RTTI
#include <iostream>


const int&& fx();
struct A { double x; };

int main()
{
	int var;
	const A* a = new A();


	decltype(fx());		// 형식은 ??? const int&&
	decltype(var);		// 형식은 ??? int
	decltype(a->x);		// 형식은 ??? double
	decltype((a->x));	// 형식은 ??? double&
}