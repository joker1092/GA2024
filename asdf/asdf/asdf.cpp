#include <iostream>

int main()
{
	int size = 3;
	int* p = new int[size] {1, 2, 3};

	

	size = 4;
	int* temp = new int[size];
	
	/*for (size_t i = 0; i < 3; i++)
	{
		temp[i] = p[i];
	}*/
	memcpy(temp, p, sizeof(int) * 3);
	//memcpy_s(temp, sizeof(int)*size, p, sizeof(int) * 3);

	delete[] p;

	p = temp;

	p[3] = 4;


	for (size_t i = 0; i < size; i++)
	{
		std::cout << p[i] << " ";
	}

	delete[] p;

	return 0;
}