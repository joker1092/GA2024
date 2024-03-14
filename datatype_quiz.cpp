#include <iostream>
using namespace std;

int main(void)
{
	// 아래 코드에서 상수와 변수를 찾아보세요
	int a = 3;
	int b = a;
	float num = 3.14;
	const double PI = 3.141592;
	const char* str = "abc";
	//변수 a,b,num;
	//상수 PI , str, 3, 3.14, 3.141592, "abc";

	// 상수 자료형은?
	cout << 12 << endl;				//int
	cout << 1.5 << endl;			//double
	cout << 1.5f << endl;			//float
	cout << 'a' << endl;			//char
	cout << "abcdef" << endl;		//const char [7] //const char * 

	// 리터럴 표기 //다음 상수값의 자료형은?
	cout << 12u << endl; //unsigned int
	cout << 12L << endl; //long 
	cout << 1.5 << endl; //double
	cout << 1.5f << endl; //float

	// 진법 표기	//10진수 10을  2진수,8진수, 16진수로 표시해 보세요.
	cout << 10 << endl;
	cout << 0b1010 << endl;
	cout << 012 << endl;
	cout << 0x0A << endl;


	// "hello" 문자열 을 변수에 담아 출력 하기 
	char hello[6] = "hello";
	cout << hello;
	// 문자열 입력받아 출력하세요.
	char str[] = "";
	cin >> str;
	cout << str;

	char st1[10];						// 크기가 10인 char형 배열을 선언

	// char, unsigned char 가 표현가능한 수의 범위는 ?

	// int 자료형의 크기(바이트수)를 출력하세요. 

	// float 자료 형식의 메모리 크기(바이트 단위)를 출력하세요.

	// int의 최댓값을 출력하세요.

	printf("%d\n", INT32_MAX);  //INT_MAX

	// int의 범위를 출력하세요.  

	printf("%d\n", INT32_MAX);	//#include <stdint.h>  ***
	printf("%d\n", INT32_MIN);

	// 문자 'K' 의 아스키코드를 출력하세요. 

	// 식별자 이름을 만드는 규칙을 설명하세요.


	// 다음 코드에서 출력은?		
	int value = 20 / 3.0;
	cout << value << endl;

	// 소숫점 까지 정확하게 나오도록 수정하세요
	/*int a = 10, b = 3;
	int c = a / b;
	cout << c << endl;*/

	// 상수의 자료형 // 결과는?   //0.3 되도록 수정하라.
	//double c = 3 / 10;
	//printf("%f", c);

	// 오버플로우 //출력은 ?
	int level = INT_MAX;
	cout << level + 1 << endl;		//???

	//형변환 //출력은 ?

	int n = 1.2;
	cout << n + 2 << endl;			//???
	cout << 1 / 2 + 1 / 2 << endl;	//???

	// 출력 값은? 이유는?	
	/*unsigned int num = -1;
	printf("%d\n", num);*/

	return 0;
}

