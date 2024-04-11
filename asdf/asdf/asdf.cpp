#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	const int count = 10;

	//int* p = new int[count];
	int* p = (int*)malloc(sizeof(int) * count);

	for (int i = 0; i < count; i++)
	{
		*(p + i)=i+1;
	}

	for (int i = 0; i < count; i++)
	{
		cout << *(p + i) << endl;
	}
	
	//delete[] p;
	free(p);

	return 0;
}