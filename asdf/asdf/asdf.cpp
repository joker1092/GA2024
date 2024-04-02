#include <iostream>

using namespace std;

//15. 화씨온도를 섭씨온도로 변환하여 리턴하는 함수를 작성하세요
//	(변환공식 : 섭씨 = (화씨 - 32) / 1.8)
//	(예 : 화씨를 50으로 입력했다면 섭씨 = (50 - 32) / 1.8 이므로 10의 결과값을 얻을 수 있다)

void PrintDecimalReverse(int n)
{
	if (n == 0)                        //베이스 케이스
		cout << endl;
	else
	{
		cout << n % 10;						//뒷자리 수를 출력
		PrintDecimalReverse(n/10);		//문제 크기를 줄임
	}
}

int main()
{
	PrintDecimalReverse(123456789);	//출력은?
	return 0;
}