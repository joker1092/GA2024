#include <iostream>
using namespace std;

void main()
{

	//1. 배열을 선언하고, 문자 'A', 'B', 'C' 를 담아보세요.
	char cha[] = { 'A','B','C' };


	//2. 아래 코드의 출력값은?
	{
		int aList[5] = { 10, 20, 30, 40, 50 };
		aList[0] = 100;
		aList[1] = aList[0];
		aList[2] += aList[1]; //30+100
		cout << aList[2] << endl; //130
	}

	//3. 아래 코드의 출력값은?
	{
		int arr2d[2][3] = {
			{1, 2, 3},
			{4, 5, 6}
		};
		cout << arr2d[1][1] << endl; //5
	}

	//4. 각 배열의 바이트수를 출력한 결과는 얼마인가?
	{
		char arr1[] = { '1','2','3','4','5' };
		char arr2[] = "12345";
		cout << sizeof(arr1) << endl; //5
		cout << sizeof(arr2) << endl; //6
	}

	//5. 아래 char 배열의 갯수를 출력하는 코드 작성하세요.
	{
		char array[] = "Hello World";

		cout << sizeof(array) / sizeof(array[0]);
	}


	//6. 배열을 선언하고 1부터 10까지 숫자로 초기화해 보세요. ( for 문 )
	int nums[10] = {};
	for (int i = 0; i < 10; i++)
	{
		nums[i] = i + 1;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << nums[i] << " ";
	}


	//7. 5번의 플레이 결과 다음과 같은 점수가 발생했습니다.
	//   각 점수를 배열에 담아서, 평균 점수를 구하세요. (소숫점 2자리)  
	//	 65 75 50 80 99 

	int score[5] = { 65 ,75, 50, 80, 99 };
	int sum = 0;
	double avrg = 0;
	for (int i = 0; i < 5; i++)
	{
		sum += score[i];
	}
	avrg = sum / (double)5;

	printf("%.2f", avrg);


	//8. 아래 배열에서 가장 큰 숫자를 찾아 출력하는 코드를 작성하세요.
	{
		int arraynumber[] = { 1, 8, 13, 24, 7, 17, 3 };

		int max = 0;

		for (int i = 0; i < sizeof(arraynumber) / sizeof(arraynumber[0]); i++)
		{
			if (max < arraynumber[i]) max = arraynumber[i];
		}

		cout << max;
	}

	//9. 정수 5개를 배열로 선언하여 입력을 받고, 입력받은 수 중에 짝수만 출력하는 코드를 작성하시오
	{
		int array[5];

		for (int i = 0; i < 5; i++)
		{
			cin >> array[i];
		}

		for (int i = 0; i < 5; i++)
		{
			if (array[i] % 2 == 0)
			{
				cout << array[i] << " ";
			}
		}
	}

	//10. 문자 5개를 배열로 선언하여 입력을 받고, 입력받은 소문자를 대문자로 출력하는 코드를 작성하시오
	{
		char arr[5];

		for (int i = 0; i < 5; i++)
		{
			cin >> arr[i];
		}

		for (int i = 0; i < 5; i++)
		{
			if ('a' <= arr[i] && arr[i] <= 'z') {
				cout << (char)(arr[i] - ('a' - 'A'));
			}
		}
	}
}

