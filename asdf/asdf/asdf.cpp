#include <iostream>
using namespace std;

struct TEST {
	int age;
	int gender;
};

int set_human(TEST &human,int a, int b) {
	
	human.age = a;
	human.gender = b;
	return 0;
}

int main(int argc, char* argv[])
{
	TEST human = {};
	set_human(human, 10, 1);
	
	cout << human.age << human.gender;

	return 0;
}