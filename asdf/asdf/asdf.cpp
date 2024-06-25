#include <iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}

	~Base()
	{
		cout << "~Base()" << endl;
	}
	void Show() {
		cout << "Base() Show()" << endl;
	}

private:

};

class Derived: public Base
{
public:
	Derived()
	{
		cout << "Derived()" << endl;
	}

	~Derived()
	{
		cout << "~Derived()" << endl;
	}

	void Show(){
		Base::Show();
		cout << "Derived() Show()" << endl;
	}

private:

};



int main(void)
{
	Derived obj;

	obj.Show();

    return 0;
}