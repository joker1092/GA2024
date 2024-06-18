#include <iostream>
using namespace std;

struct PrintAddNumber
{
	//PrintAddNumber(int a, int b) { cout << a + b << std::endl; }
	void operator()(int a, int b) { cout << a + b << std::endl; }
};


void main()
{
	PrintAddNumber()(3, 5);
}

