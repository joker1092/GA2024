// 연습 ----------------------------------------------------------

#include <iostream>
using namespace std;

int main(void)
{
	//1. "Hello World" 가 출력되도록 해보자.
	cout << "\"Hello World\"" << endl;

	//2. 소숫점 두자리 출력 
	double PI = 3.141592;
	//3.14
	printf("%.2f", PI);
	printf("\n");

	//3. 10진수 100을 16진수로 출력 하면?
	printf("%x", 100);
	printf("\n");

	//4.   123, 456, 789 를 다음과 같이 5칸 간격으로 출력하라
	// 
	//00123 00456 00789

	printf("%05d%05d%05d", 123, 456, 789);
	printf("\n");


	//5.   다음과 같이 5칸 간격으로 출력하라
	//---------------
	//  123   34    5
	//    6   78  901
	//---------------
	printf("%5d%5d%5d\n", 123, 34, 5);
	printf("%5d%5d%5d\n", 6, 78, 901);
	printf("\n");

	//6. 1.5, 125, 365, 24  다음과 같이 간격 유지하기,  
	//5칸 간격,  소숫점은 한자리까지, 소숫점 빈자리는 0으로 채우기  
	// 
	//  1.5, 125.0
	//365.0,  24.0
	double a1 = 1.5;
	double a2 = 125;
	double b1 = 365;
	double b2 = 24;

	printf("%5.1f,%5.1f\n", a1, a2);
	printf("%5.1f,%5.1f\n", b1, b2);
	printf("\n");

	//7. 콘솔에 문자 ‘a’ 를 출력하는 프로그램을 작성하세요
	cout << 'a' << endl;

	//8. 콘솔에 문자열 "korea" 를 출력하는 프로그램을 작성하세요
	cout << "korea" << endl;

	//9. 변수 pi에 실수 3.14 를 할당하고, 콘솔에 출력하는 프로그램을 작성하세요
	float pi = 3.14;
	cout << pi << endl;

	//10. 콘솔에 숫자 5 와 2.5를 다음과 같이 출력하는 프로그램을 작성하세요
	//출력) 5, 2.5    

	cout << 5 << 2.5 << endl;

	//11. 콘솔에 아래와 같이 문자열을 출력하는 프로그램을 작성하세요
	// 
	//  *
	// ***
	//*****
	cout << "  *" << endl;
	cout << " ***" << endl;
	cout << "*****" << endl;

	//12. 아래 선언된 변수를 이용해 다음과 같이 출력하세요.
	// 
	//출력) Lv. 5
	int level = 10;  //Code
	level = 5;
	cout << "lv. " << level << endl;

	//13. 정수를 입력 받아 그 수를 콘솔에 출력하는 프로그램을 작성하세요
	int a;

	cout << "정수 입력 ";
	cin >> a;
	cout << "입력받은 값" << a << endl;

	//14. 정수를 입력 받아 그 수를 16진수로 콘솔에 출력하는 프로그램을 작성하세요
	int hex;
	cout << "16진수로 변환 하고 싶은 값을 입력 하세요";
	cin >> hex;
	printf("%x", hex);
	printf("\n");
	//15. 너비와 높이를 입력받아 면적을 출력하는 코드를 작성하세요. 
	// 
	//너비를 입력하세요 : 2
	//높이를 입력하세요 : 5
	//면적은 10 입니다.
	int w;
	int h;
	cout << "너비를 입력하세요 : ";
	cin >> w;
	cout << "높이를 입력하세요 : ";
	cin >> h;
	cout << "면적은 " << w * h << " 입니다.";

	return 0;
}
