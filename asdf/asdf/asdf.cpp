#include <iostream>
using namespace std;

//class MyError {
//	string message;
//public:
//	MyError(string msg) : message(msg) {}
//	void print() { cout<< message << endl; }
//};



int main()
{
    try{
		//throw MyError("My Error");
		throw exception("My Error");
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}

    return 0;
}
