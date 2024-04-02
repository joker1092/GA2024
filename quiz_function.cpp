#include <iostream>
void Display(char in); //1.
void isEven(int n); //2.
void OctaDecHexa(int n); //3.
void Calc(int n, int m); //4.
void RepeatInt(int n); //5.
int Sigma(int n, int m); //6.
int Bigger(int n, int m); //7.
double AvrInt3(int n, int m, int l); //8.
void ScoreToGrade(int n); //9.
int Smaller(int n, int m, int l); //10.
void ToStr3(int n); //11.
void NineX(int n); //12.
char CharShift(char c); //13.
void SecondToTimeFormat(int s); //14.
double FahrenToCels(int f); //15.

int main()
{
	return 0;
}

//함수 문제 ------------------------------------------------------------------------------
 
#include <iostream>

using namespace std;

//1. 매개변수로 넘어온 문자의 아스키 코드를 출력 시키는 함수를 작성하세요
void Display(char in) {
	cout << (int)in << endl;
}

//2. 매개변수로 넘어온 정수가 홀수인지, 짝수인지 출력시키는 함수를 작성하세요
void isEven(int n) {
	if (n % 2 == 0)
	{
		cout << "짝수";
	}
	else {
		cout << "홀수";
	}

}

//3. 매개변수로 넘어온 정수를 8진수, 10진수, 16진수로 출력하는 함수를 작성하세요
void OctaDecHexa(int n) {
	printf("%s", "8진수 :");
	printf("%o", n);
	printf("%c", '\n');
	printf("%s", "10진수 :");
	printf("%d", n);
	printf("%c", '\n');
	printf("%s", "16진수 :");
	printf("%x", n);
	printf("%c", '\n');
}

//4. 두 정수를 매개변수로 받아 두 수의 덧셈, 뺄셈, 곱셈, 나눗셈의 결과를 출력하는 함수를 작성하세요
void Calc(int n, int m) {
	cout << "덧셈" << n + m << endl;
	cout << "뺄셈" << n - m << endl;
	cout << "곱셈" << n * m << endl;
	cout << "나눗셈" << n / m << endl;
}

//5. 매개변수로 넘어온 정수보다 10만큼 큰 수까지 출력하는 함수를 작성하세요
//	(매개변수로 5를 넣으면 5에서 15사이의 정수 출력)
void RepeatInt(int n) {
	for (int i = n; i <= n + 10; i++)
	{
		cout << i << endl;
	}
}

//6. 매개변수로 정수 2개를 넘겨받아 두 수 사이에 있는 정수의 합을 리턴하는 함수를 작성하세요
//	(매개변수로 넘어온 두 수는 서로 다르며 작은수부터 입력한다)
int Sigma(int n, int m) {
	int sum = 0;
	for (int i = n + 1; i < m; i++)
	{
		sum += i;
	}
	return sum;
}

//7. 정수 2개를 매개변수로 넘겨받아, 두 수 중 큰 수를 리턴하는 함수를 작성하세요
int Bigger(int n, int m) {
	if (n > m)return n;
	else if (n < m)return m;
	else return n;
}

//8. 정수 3개를 매개변수로 넘겨받아 평균을 구해 리턴하는 함수를 작성하세요.
double AvrInt3(int n, int m, int l) {
	return (n + m + l) / 3.0;
}

//9. 1에서 100사이의 정수값을 매개변수로 넘겨받아, 해당 학점을 출력하는 함수를 작성하세요
//	(90점이상 = 'A', 80점이상 = 'B', 70점이상 = 'C', 60점이상 = 'D', 그 외는 'F')
void ScoreToGrade(int n) {
	if (n >= 90)
		cout << 'A' << endl;
	else if (n >= 80)
		cout << 'B' << endl;
	else if (n >= 70)
		cout << 'C' << endl;
	else if (n >= 60)
		cout << 'D' << endl;
	else
		cout << 'F' << endl;
}
//10. 3개의 정수를 매개변수로 넘겨받아 가장 작은 수를 리턴하는 함수를 작성하세요
int Smaller(int n, int m, int l) {
	int small = 0;
	if (n < m)
	{
		if (n < l) {
			small = n;
		}
		else {
			small = l;
		}
	}
	else {
		if (m < l) {
			small = m;
		}
		else {
			small = l;
		}
	}
	return small;
}
//11. 매개변수로 넘어온 정수값이 1이면 ONE, 2는 TWO, 3은 THREE, 
//	 1~3이 아닌 값은 ERROR를 출력하는 함수를 작성하시오
void ToStr3(int n) {
	switch (n)
	{
	case 1: cout << "ONE" << endl; break;
	case 2: cout << "TWO" << endl; break;
	case 3: cout << "THREE" << endl; break;
	default:
		cout << "ERROR" << endl;
		break;
	}
}
//12. 매개변수로 단을 넘겨받아 해당 구구단을 화면에 출력하는 함수를 작성하세요
void NineX(int n) {
	for (int i = 1; i <= 9; i++)
	{
		cout << n << "*" << i << "=" << n * i << endl;
	}
}

//13. 매개변수로 문자 하나를 넘겨받아 대문자를 소문자로, 소문자는 대문자로 변환한 후 
//	 해당 문자를 리턴하는 함수를 작성하세요
char CharShift(char c) {
	int shift = 'a' - 'A';
	if ('a' <= c || 'z' >= c)
		return (char)(c - shift);
	else if ('A' <= c || 'Z' >= c)
		return (char)(c + shift);
	else
		return c;
}

//14. 초를 매개변수로 넘겨받아 이를[시:분:초] 형태로 출력하는 함수를 작성하세요
void SecondToTimeFormat(int s) {
	cout << "[" << s / 60 / 60 << ":" << s / 60 % 60 << ":" << s % 60 << "]" << endl;
}

//15. 화씨온도를 섭씨온도로 변환하여 리턴하는 함수를 작성하세요
//	(변환공식 : 섭씨 = (화씨 - 32) / 1.8)
//	(예 : 화씨를 50으로 입력했다면 섭씨 = (50 - 32) / 1.8 이므로 10의 결과값을 얻을 수 있다)
double FahrenToCels(int f) {
	double cels = 0.0;
	cels = (f - 32) / 1.8;
	return cels;
}


//재귀호출 문제 ------------------------------------------------------------------------------

//16.  실제 컴퓨터에서 문제 크기가 줄지 않는 재귀호출을 가하면 그 결과는 어떻게 되는가 ?	
	/*가.운영체제가 무한 재.귀호출이 일어나는 것을 발견한다.
	나.[Ctrl] + [C] 키를 누를 때까지 프로그램은 계속 돌아간다.
	다.결과를 예측할 수 없다.*/
	라.스택 오버플로우에 의해 프로그램이 멈춘다.

//17.  함수 호출 결과, 활성화 레코드에 저장되지 않는 정보는 다음 중 무엇인가 ?	
	가.현재 재귀호출의 깊이
	//나.전달된 파라미터 값
	//다.함수 실행이 끝나고 되돌아갈 주소
	//라.지역 변수

//18. 아래 코드를 해석하고 출력을 예상해보세요.
	void Asterisk(int i)
	{
		if (i > 1) {
			Asterisk(i / 2);
			Asterisk(i / 2);
		}
		std::cout << "*";
	}

	int main()
	{
		Asterisk(5);	//출력은?
		return 0;
	}
	//*******

//19. 아래 코드를 해석하고 출력을 예상해보세요.
	int fun1(int x)
	{
		if (x < 5)
			return (3 * x);
		else
			return (2 * fun1(x - 5) + 7); 
	}

	int main()
	{
		std::cout << fun1(4) << std::endl;		//출력은? 12
		std::cout << fun1(10) << std::endl;		//출력은? 21
		return 0;
	}

//20. 다음 함수에서 Recurse(4)를 불렀을 때 그 결과는 무엇인가 ? 

	void Recurse(int n)
	{
		if (n > 0)
			Recurse(n - 2);
		cout << n << " ";
	}

	가. 0 2 4      //나. 0 2      //다. 2 4      //라. 4 2      //마. 4 2 0


//21. 자연수 N이 입력될 때, 1 2 3 ... N을 순차적으로 출력하는 프로그램을 재귀호출로 작성하세요.
void Recurse(int n)
{
	if (n > 1)
		Recurse(n - 1);
	cout << n << " ";
}


//22. 함수를 재귀호출로 작성하라
//	Asterisk(5); 라는 명령에 의해
//	애스터리스크(*) 다섯 개를 화면에 출력하는 함수를 재귀호출로 작성하라.
void Asterisk(int i)
{
	if (i > 1) {
		Asterisk(i - 1);
	}
	std::cout << "*";
}

//23. 10진수 N을 2진수로 변환하여 출력하기 위한 다음 함수의 빈 곳을 완성하라.
void Convert(int N)
{
	if (N == 0)
		return;
	else
	{
		Convert(N / 2);
		printf("%d", N % 2);
	}
}


//24. 주어진 십진수를 거꾸로 쓰기 위한 다음 소스 코드를 완성하라.
void PrintDecimalReverse(int n)
{
	if (n == 0)                        //베이스 케이스
		cout << endl;
	else
	{
		cout << n % 10;						//뒷자리 수를 출력
		PrintDecimalReverse(n / 10);		//문제 크기를 줄임
	}
}