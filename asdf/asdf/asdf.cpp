#include <iostream>
using namespace std;

#include "Test.h"
int n = 0;

void fonc() {
	static int n1 = 0;
	int n2 = 0;

	cout << n++ << endl;
	cout << n1++ << endl;
	cout << n2++ << endl;
}

int main()
{
	fonc();
	fonc();

	return 0;
}