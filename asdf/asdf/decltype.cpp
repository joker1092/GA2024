//RTTI
#include <iostream>


const int&& fx();
struct A { double x; };

int main()
{
	int var;
	const A* a = new A();


	decltype(fx());		// ������ ??? const int&&
	decltype(var);		// ������ ??? int
	decltype(a->x);		// ������ ??? double
	decltype((a->x));	// ������ ??? double&
}