// 게임수학1Q평가.cpp

#include <iostream>
#include <cassert>
//****************************************************************
// 게임수학 12. 유클리드 호제법을 이용한 최대공약수 구하기
int GDC(int a, int b)
{
	int q = a / b;
	int r = a % b;
	if (r == 0)
	{
		return q;
	}
	else {
		return GDC(b, r);
	}
}

void TestGDC()
{
	std::cout << "유클리드 호제법을 이용한 최대공약수 구하기" << std::endl;

	//GCD(270,192) = 6
	//GDC(10007, 1013) = 1
	std::cout << GDC(270, 192) << std::endl; // 6
	std::cout << GDC(10007, 1013) << std::endl; // 1
}
//****************************************************************

//숫자를 N진법 문자열로 바꾸기
//게임수학: 진법 변환
//자료구조와 알고리즘: 스택 활용
//컴퓨터 개론: 수와 진법, 아스키코드
//1) 나머지 연산과 스택을 활용합니다. 스택 클래스를 사용하지 않고 배열을 사용합니다.
//2) 스택에 있는 나머지와 최종 몫을 가지고 문자열을 만듭니다. (숫자와 문자를 구분)


const char gNumberToCharTable[16] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F' };

char NumberToChar(int num)
{
	return gNumberToCharTable[num];
}

// num : 변환할 숫자
// N : 변환할 진법
// buffer : 변환된 문자열을 저장할 버퍼
// bufSize : 버퍼의 크기
bool IntToString(int num, const int N, char buffer[], const int bufSize)
{
	const int _max = 16;

	if (_max > bufSize) return false;

	int stackBuf[_max];
	int stackTop = 0;
	int quotient = num; // 몫

	while (quotient > N)
	{
		stackBuf[stackTop] = quotient % N;
		quotient = quotient / N;
		stackTop++;
	}
	stackBuf[stackTop] = quotient;


	int i = 0;
	for (stackTop >= 0; stackTop--;)
	{
		int a = stackBuf[stackTop];
		buffer[i] = NumberToChar(a);
		i++;
	}


	// 나머지 연산과 스택을 활용하여 N진수로 변환합니다.
	// 나머지 연산을 하여 스택에 저장하고, 몫을 다시 나누어 나머지를 구합니다.
	// 몫이 N보다 작아지면 나머지를 구하지 않고 몫을 문자로 변환하여 저장합니다.
	// 스택에 저장된 나머지를 역순으로 꺼내어 문자로 변환하여 저장합니다.

	return true;
}

void TestN2String()
{
	std::cout << "숫자를 N진법 문자열로 바꾸기" << std::endl;
	//IntToString 함수를 사용하여 10진수를 2진수, 8진수, 16진수로 변환하여 출력합니다.

	//1) 나머지 연산과 스택을 활용합니다. 
	//* 스택 클래스를 만들 필요 없습니다. 배열의 TopIndex 만 관리해도 충분합니다.
	//2) 스택에 있는 나머지와 최종 몫을 가지고 문자열을 만듭니다. (숫자와 문자를 구분)

	char buffer_dec[16] = { 0, };// 10진수 문자열을 저장할 버퍼
	char buffer_bin[16] = { 0, };// 2진수로 변환한 문자열을 저장할 버퍼
	char buffer_oct[16] = { 0, };// 16진수로 변환한 문자열을 저장할 버퍼
	char buffer_hex[16] = { 0, };// 16진수로 변환한 문자열을 저장할 버퍼

	std::cout << "DEC : BIN : OCT : HEX" << "\n";

	for (int i = 0; i <= 100; i++)
	{
		assert(true == IntToString(i, 10, buffer_dec, 16));

		assert(true == IntToString(i, 2, buffer_bin, 16));

		assert(true == IntToString(i, 8, buffer_oct, 16));

		assert(true == IntToString(i, 16, buffer_hex, 16));


		std::cout << buffer_dec <<
			" : " << buffer_bin <<
			" : " << buffer_oct <<
			" : " << buffer_hex << "\n";
	}
}
//****************************************************************
// 자료구조와 알고리즘: 평가 기준-->효율성을 고려한 문자열 뒤집기


	void ReverseString(char* str)
	{
		
		int i = 0;
		char temp[16];
		while (str[i] != '\0')
		{
			temp[i] = str[i];
			i++;
		}
		
		int j = 0;
		for (i >= 0; i--;)
		{
			str[j] = temp[i];
			j++;
		}

		
	}



void TestReverseString()
{
	//2. 문자열 뒤집기
	//ReverseString 함수를 사용하여 문자열을 뒤집어 출력합니다.

	char str1[] = "Hello, World!";
	char str2[] = "1234567890";
	char str3[] = "C++ Programming";
	ReverseString(str1);
	ReverseString(str2);
	ReverseString(str3);
	std::cout << str1 << "\n";
	std::cout << str2 << "\n";
	std::cout << str3 << "\n";
}


int main()
{

	TestGDC();
	TestN2String();
	TestReverseString();

	return 0;

}