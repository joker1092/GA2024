#include <iostream>
using namespace std;

int main(void)
{
	int A,B = 0;
	cin >> A;
	cin >> B;
	if (A > 0 && B > 0) {
		cout << 1 << endl;
	}
	else if (A > 0 && B < 0) {
		cout << 4 << endl;
	}
	else if (A < 0 && B < 0)
	{
		cout << 3 << endl;
	}
	else if (A < 0 && B > 0) {
		cout << 2 << endl;
	}
	else {
		cout << 0 << endl;
	}
	
	return 0;
}
