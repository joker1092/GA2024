#include <iostream>
using namespace std;

int main()
{
	//1. 출력값을 예상해 보세요.
	{
		int x = 0;
		printf("%d\n", x++); //0
		printf("%d\n", ++x); //2
	}

	//2. 출력값을 예상해 보세요.
	{
		int x = 1;
		int y = 5;
		printf("%d\n", y <= x + 5); //1
	}

	//3. 출력값을 예상해 보세요.
	printf("결과: %d\n", 0 < 1 || 0 < 1 && 2 < 3 || 4 < 5); //결과 : 1

	//4. 예상되는 출력값은?
	{
		int n1 = 2, n2 = 7;
		bool rt = n1 > 1 || ++n2 < 5;
		cout << rt << endl;				// 1
		cout << n1 + n2 << endl;		// 9
	}

	//5. 예상되는 출력값은?
	{
		int a = 3;
		int b = 5;
		cout << (a & b) << endl; //1
		cout << (a | b) << endl; //7
		cout << (a ^ b) << endl; //6
	}

	//6. 예상되는 출력값은?
	{
		int n = 2;
		cout << (n << 2) << endl; //8
	}

	//7. 예상되는 출력값은?
	{
		int x = 10;
		printf("%d\n", x * 10);  //100
		printf("%d\n", x * 10.0); //0
	}

	//8. 예상되는 출력값은?	
	printf("%f\n", 5 / 2);						//0.000000

	//9. 예상되는 출력값은?	
	{
		int a, b, c, d;
		a = 5 > 4;    //1
		b = 5 != 2;   //1
		c = (5 > 2) + (2 > 4) + (5 > 1);  //1+0+1
		d = 4 + !3 - !!2;    //4 +0 -1		
		printf("%d\n", b);  //1
		printf("%d\n", c);	//2
		printf("%d\n", d);  //3
	}

	//10. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a, b, c, d;
		a = 2;
		b = 3;
		c = b > a ? 10 : 20;  printf("%d\n", c);  //10
	}

	//11. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a = 1, b = 2;
		if (a > b && b < 1 || b < 3) { //true;
			a++;
		}
		cout << a << endl; //2
	}

	//12. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a, b, c, d, e;
		a = 35;				 //00100011
		b = a & 0xf0;		 //11110000  0010 0000 //32
		c = a & 0xf0 | 0x01; //11110001  0010 0010 //32+2
		d = 0xf0 ^ 0xf0 | a; //00000000  0010 0011 //32+2+1
		e = a & 0x0f;        //00001111  0000 0011 //3 
		printf("%d\n", b); //32
		printf("%d\n", c); //34
		printf("%d\n", d); //35
		printf("%d\n", e); //3
	}

	//13. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a = 2, b = 3, c = 10, d = 30, e = 30;
		a += 100;
		b -= 2;
		c *= 10;
		d /= 4;
		e %= 4;
		printf("%d\n", a); //102
		printf("%d\n", b); //1
		printf("%d\n", c); //100
		printf("%d\n", d); //7
		printf("%d\n", e); //2
	}


	//14. 두 변수 x와 y에 저장된 값을 서로 교환하세요.
	int x = 10, y = 20;
	int tmp = 0;
	tmp = x;
	x = y;
	y = tmp;
	cout << "x : " << x << "y : " << y << endl;


	//15. % 활용하여 두 정수 5를 3으로 나눈 몫과 나머지를 출력하세요
	int a = 5, b = 3;

	cout << a / b << endl;
	cout << a % b << endl;


	//16. % 활용하여 정수를 입력받아 3으로 나눈 몫과 나머지를 출력하세요
	int nInput = 0;
	cin >> nInput;
	cout << nInput / 3 << endl;
	cout << nInput % 3 << endl;


	//17. 입력한 숫자가 3의 배수인지 구하세요 (% 활용)
	int nInput1 = 0;
	cin >> nInput1;

	cout << (nInput1 % 3 == 0) << endl;


	//18. 입력한 값이 3보다 크고 20보다 작은지 출력하세요. (비교 연산자)
	int input = 0;
	scanf_s("%d", &input);

	bool bnum = 3 < input && input < 20;
	printf("%d", bnum);


	//19. 입력한 문자를 대문자, 소문자, 숫자로 구분하여 출력하세요. (아스키코드)
	char input;
	cin >> input;

	if ('0' <= input && input <= '9') {
		cout << "Num : " << input << endl;
	}
	else if ('A' <= input && input <= 'Z') {
		cout << "Upper : " << input << endl;
	}
	else if ('a' <= input && input <= 'z') {
		cout << "Lower : " << input << endl;
	}
	else {
		cout << "other : " << input << endl;
	}
}
