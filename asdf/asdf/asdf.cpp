#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


bool foo1(int a) { return true; }
void foo2(int a, int b) {}
string foo3(float m, double b) { return ""; }
void foo4(){}

int main() {

	function<bool(int)> f1 = foo1;	f1(1);
	function<void(int,int)> f2 = foo2; f2(1,2);
	function<string(float, double)> f3 = foo3; f3(1.0f, 2.5);
	function<void()> f4 = foo4;  f4();
	

	return 0;
}