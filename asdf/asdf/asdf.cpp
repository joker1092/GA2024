#include <iostream>
using namespace std;

class MyClass
{
	int num = 0;
public:
	MyClass(int a) : num(a){}
	void show() { cout << num << endl; }
private:

};



int main()
{
	MyClass myclass(1);

	MyClass* p = &myclass;

	p->show();

	MyClass arr[3] = { MyClass(1), MyClass(2) ,MyClass(3) };

	MyClass* ptr = arr;

	ptr[2].show();

	return 0;

}