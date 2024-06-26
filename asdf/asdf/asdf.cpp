#include <iostream>
using namespace std;

class First
{
private : 
	char* one;
public:
	First(const char* str) { one = new char[strlen(str) + 1]; };
	virtual ~First() { cout << "~First()" << endl; delete[] one; };
};

class Second : public First
{
private:
	char* two;
public:
	Second(const char* str1, const char* str2) : First(str1) { two = new char[strlen(str2) + 1]; }
	~Second() { cout << "~Second()" << endl; delete[] two; }
};


int main()
{	
	First* ptr = new Second("simple", "complex");
	delete ptr;
	return 0;
}
