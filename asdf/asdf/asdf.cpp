#include <iostream>
using namespace std;

//void func1(int* (*p)) {
//
//	for (int i = 0; i < 3; i++)
//	{
//		cout << **(p + i) << endl;
//	}
//}
//
//void func2(int (*p)[4],int row) {
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			cout << *(*(p + i) + j) << " ";
//		}
//	}
//}

void strFunc1(const char** str ) {
	for (int i = 0; i < 3; i++)
	{
		cout << *(str+i) << " ";
	}
	cout << "\n";
}

void strFunc2(char (*p)[4], int row) {
	for (int i = 0; i < row; i++)
	{
		int j = 0;
		while (*(*(p + i)+j) != '\0')
		{
			cout << *(*(p + i) + j) << " ";
			j++;
		}
		cout << "\n";
	}
	
}


int main()
{
	/*int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	
	int* arr1[3] = { &num1,&num2,&num3 };
	
	func1(arr1);

	int arr2d[2][4] = { 1,2,3,4,5,6,7,8 };

	int(*arr2)[4] = arr2d;

	

	int row = sizeof(arr2d) / sizeof(arr2d[0]);
	func2(arr2, row);*/
	
	const char* strs1[3] = { "abc","def","ghi" };
	
	strFunc1(strs1);

	char strs2[3][4] = {"abc","def","ghi"};
	int row = sizeof(strs2) / sizeof(strs2[0]);
	strFunc2(strs2, row);

	return 0;	
}

