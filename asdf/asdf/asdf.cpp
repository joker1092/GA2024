//RTTI
#include <iostream>

using namespace std;

class Base
{
public:
	virtual ~Base() {}
};

class Derived1 : public Base
{};
class Derived2 : public Base
{};

void F(Base* pB) {
	if (typeid(*pB) == typeid(Derived2)) {
		cout<< typeid(*pB).name() << endl;
	}
	else {
		cout << "Not Derived2" << endl;
	}
}

int main()
{
	Base* pb1 = new Derived1;
	Base* pb2 = new Derived2;

	F(pb1);
	F(pb2);

	delete pb1;
	delete pb2;
}