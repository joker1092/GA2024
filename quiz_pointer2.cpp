//포인터 배열 문제

#include <iostream>
#include <string>
using namespace std;

int main() 
{

	//다음 코드 실행의 예상되는 결과는? **
	char str[50] = "I like C programming";
	str[8] = '\0';
	cout << str << endl;  //I like C


	//다음 코드 실행의 예상되는 결과는? **
	int arr[3] = { 11, 22, 33 };
	int* ptr = arr;
	cout << *(ptr + 2);  //33

	//다음 코드의 실행 결과를 쓰시오. *
	char arr2[] = "Hello World";
	char* str = arr2;
	cout << arr2[0] << *(str + 6) << endl; //HW

	//아래의 포인터 배열을 for 문을 이용해 출력하는 코드를 작성하세요. *
	const char* str[] = { "seoul","paris","london" };
	//
	for (int i = 0; i < sizeof(str)/sizeof(str[0]); i++)
	{
		cout << str[i] << endl;
	}


	// 결과는?
	char str_a[] = "abc";
	char str_b[] = "abc";
	printf("%d", str_a == str_b); //0  false;


	// 정확히 9문자로 구성된 문자열을 넣을 수 있는 C++ 배열을 선언하려 한다.다음 중 어떤 것이 가장 좋은가 ? 
	//	가. char s[8];          나. char s[9];          다. char s[10];          라. char s[11];          마. char s[12];
	//  다

	// C++에서 문자열(Character String) 두 개인 x와 y가 있다.
	// x, y가 완전히 동일한 문자열일 때 다음 중 어떤 표현이 TRUE 값을 되돌려 주는가 ? 
	// 
	//	가. (x = y)          나. (x == y)          다. (x != y)          라. (strcmp(x, y) == 0)
	//  라

	// *&*&p가 의미하는 것은 무엇인가 ? 이를 줄여 쓰면 어떻게 되는지 설명하라. 
	//  p

	// 2차원 C배열 int A[2][3]; 으로 선언했을 때, A[1][2]의 주소를  A를 사용하여 표시하라.
	// &A[1][2]


	return 0;
}

/*

//1. 다음과 같은 다차원 배열을 바르게 선언한 것은?
	1	2	3	4
	5	6	7	8

   (1) int Array[2][2];
   (2) int Array[2][4];
   (3) int Array[4][2];
   (4) int Array[4][4];

   //(2)


//2. 다음 코드의 실행 후 예상되는 결과는? *

  int main(void)
  {
	int Array[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	cout << Array[1][2] << endl; 
	//6;
  }

//3. ( )안에 들어갈 적당한 것을 고르시오  **

   int arr[10];      //arr의 포인터형은 ( int * )
   int * parr[20];  //parr의 포인터형은 (        )

   (1) int
   (2) int[]
   (3) int *
   (4) int **

   //(4);

//4. 2차원 배열의 연산에 관한 코드입니다. 예상되는 출력은 얼마입니까? *

	int main(void)
	{
		int arr[3][2] = { 1,2,3,4,5,6 };
		cout << **(arr + 1);
		return 0;
	}

	//3;


//5. 함수로 배열을 전달하기 위해서는 배열의 주소값을 전달하는 방식을 취한다. **
   다음 중 A, B 자리에 들어갈 값으로 적당한 것은?

	void SimpleFunc(  A  )
	{
		printf(“%d %d”, param[0], param[1]);
	}

	int main(void)
	{
		int arr[3] = {1, 2, 3};
		SimpleFunc(  B  );
	}

   (1) int param, &arr
   (2) int param, arr
   (3) int *param, &arr
   (4) int *param, arr

   //(4);

//6. Call-by-value 는 값을 전달하는 형태의 함수호출,
  Call-by-reference 는 주소 값을 전달하는 형태의 함수호출을 뜻합니다.
  다음 코드는 어떤 방식인가요?

	int Add(int num1, int num2)
	{
		return num1 + num2;
	}

	int main(void)
	{
		int num1 = 2, num2 = 3;
		int sum = Add(num1, num2);
	}
	//Call-by-value;

//7. 다음 중 A, B 자리에 들어갈 값으로 적당한 것은?

	int num;
	scanf(“%d”,   A   );
	char str[10];
	scanf(%s,  B   );

   (1) num, str
   (2) num, &str
   (3) &num, str
   (4) &num, &str

   //(3);


//8. 다음 코드에 필요한 두 변수의 값을 교환하는 swap 함수를 작성해 보세요. *

	void main()
	{
	    int num1 = 1;
	    int num2 = 2;
	    swap( &num1, &num2);
	}

	//void swap(int* n1, int* n2) {
	//int temp = *n1;
	//	*n1 = *n2;
	//	 *n2 = temp;
	//}



//9. 다음 코드에 필요한 두 변수의 값을 교환하는 swap 함수를 작성해 보세요. **

	void main()
	{
		int num1 = 1;
		int num2 = 2;
		swap( num1, num2);
	}

	//void swap(int& n1, int& n2) {
	//int temp = n1;
	//	n1 = n2;
	//	n2 = temp;
	//}

//10. 절대값을 구하는 함수 작성하기  //참조, 포인터 두가지 사용
	
	//포인터
	//int absolute(int* n) {
	//	if (*n < 0) {
	//		*n = -*n;
	//	}
	//	return  *n;
	//}

	//참조
	//int absolute(int &n) {
	//	if (n < 0) {
	//		n = -n;
	//	}
	//	return  n;
	//}

//-----------------------------------------------------------------
//11. 배열을 함수의 인자로 전달하여 출력하는 함수를 만들어 보세요.

#include <stdio.h>

int main(void)
{
	int arr[3] = { 1, 2, 3 };
	int len = sizeof(arr) / sizeof(int);
	ShowArray(arr, len);		//출력 함수 작성해 보자
	return 0;
}

	//void ShowArray(int* arr, int len) {
	//	for (int i = 0; i < len; i++)
	//	{
	//		cout << *(arr + i) << endl;
	//	}
	//}


//12. 포인터의 배열 //arr1 을 이용해서, 변수의 값을 아래와 같이 출력하세요.
	//10 20 30 40

	int num1 = 10, num2 = 20, num3 = 30, num4 = 40;
	int* arr1[4] = { &num1, &num2, &num3, &num4 };   // 포인터 배열
	
	//for (int i = 0; i < 4; i++)
	//{
	//	cout << **(arr1 + i) << " " << endl;
	//}


//13. 배열의 포인터 //아래와 같이 출력하세요.
	//1 2 3 4
	//5 6 7 8

	int arr2d[2][4] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int(*parr)[4] = arr2d;							 // 배열 포인터

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << *(*(parr + i)+j) << " ";
		}
		cout << "\n";
	}


//14. 이중 포인터 //출력하는 함수를 만들어 보세요. 

	#include <iostream>
	using namespace std;

	//void PrintStr(const char** str,int len) {
	//	for (int i = 0; i < len; i++)
	//	{
	//		cout << *(str + i) << endl;
	//	}
	//}

	int main(void)
	{
		const char* strArr[3] = { "Simple", "String", "Array" };

		printf("%s \n", strArr[0]); //const char * 형 주소
		printf("%s \n", strArr[2]);
		printf("%d \n", sizeof(strArr[0]));

		//PrintStr(strArr);		//출력하세요.
		//PrintStr(strArr,sizeof(strArr)/ sizeof(strArr[0]));
	}



//15. 함수포인터 //함수를 함수포인터로 선언해서 사용해 보세요. 

	void ShowString(const char * str)
	{
		printf("%s \n", str);
	}

	//void (*fptr)(const char *)=ShowString;
	//
	//fptr("가나다라");


//16. MyCompare 함수를 작성하세요. (void*, 콜백)

	//int MyCompare(void const* a, void const* b)
	//{
	//	return *(int*)a > *(int*)b;
	//}

	int main(void)
	{
		int aList[5] = { 30, 10, 40, 50, 20 };
		int i = 0;

		qsort(aList, 5, sizeof(int), MyCompare);

		for (i = 0; i < 5; ++i)
			printf("%d\t", aList[i]);
		return 0;
	}


//17. 문자열의 길이를 구하는 함수를 만드세요.

	#include <stdio.h>

	int str_length(char* str);

	int main() 
	{
		char str[] = { "What is your name?" };
		printf("이 문자열의 길이 : %d \n", str_length(str));
		return 0;
	}

	//int str_length(char* str) {
	//int rt = 0;
	//while (str[rt] != '\0') {
	//	rt++;
	//}
	//return rt+1;
}

*/