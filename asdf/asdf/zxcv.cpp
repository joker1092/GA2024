#include <iostream>
using namespace std;

int main()
{
	//1. 출력값을 예상해 보세요.
	{
		int x = 0;
		printf("%d\n", x++);
		printf("%d\n", ++x);
	}

	//2. 출력값을 예상해 보세요.
	{
		int x = 1;
		int y = 5;
		printf("%d\n", y <= x + 5);
	}

	//3. 출력값을 예상해 보세요.
	printf("결과: %d\n", 0 < 1 || 0 < 1 && 2 < 3 || 4 < 5);

	//4. 예상되는 출력값은?
	{
		int n1 = 2, n2 = 7;
		bool rt = n1 > 1 || ++n2 < 5;
		cout << rt << endl;				// ?
		cout << n1 + n2 << endl;		// ?
	}

	//5. 예상되는 출력값은?
	{
		int a = 3;
		int b = 5;
		cout << (a & b) << endl;
		cout << (a | b) << endl;
		cout << (a ^ b) << endl;
	}

	//6. 예상되는 출력값은?
	{
		int n = 2;
		cout << (n << 2) << endl;
	}

	//7. 예상되는 출력값은?
	{
		int x = 10;
		printf("%d\n", x * 10);
		printf("%d\n", x * 10.0);
	}

	//8. 예상되는 출력값은?	
	printf("%f\n", 5 / 2);						//

	//9. 예상되는 출력값은?	
	{
		int a, b, c, d;
		a = 5 > 4;
		b = 5 != 2;
		c = (5 > 2) + (2 > 4) + (5 > 1);
		d = 4 + !3 - !!2;						//
		printf("%d\n", b);
		printf("%d\n", c);
		printf("%d\n", d);
	}

	//10. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a, b, c, d;
		a = 2;
		b = 3;
		c = b > a ? 10 : 20;  printf("%d\n", c);
	}

	//11. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a = 1, b = 2;
		if (a > b && b < 1 || b < 3) {
			a++;
		}
		cout << a << endl;
	}

	//12. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a, b, c, d, e;
		a = 35;
		b = a & 0xf0;
		c = a & 0xf0 | 0x01;
		d = 0xf0 ^ 0xf0 | a;
		e = a & 0x0f;
		printf("%d\n", b);
		printf("%d\n", c);
		printf("%d\n", d);
		printf("%d\n", e);
	}

	//13. 아래의 코드를 실행시 화면에 출력되는 결과를 쓰시오
	{
		int a = 2, b = 3, c = 10, d = 30, e = 30;
		a += 100;
		b -= 2;
		c *= 10;
		d /= 4;
		e %= 4;
		printf("%d\n", a);
		printf("%d\n", b);
		printf("%d\n", c);
		printf("%d\n", d);
		printf("%d\n", e);
	}


	//14. 두 변수 x와 y에 저장된 값을 서로 교환하세요.
	int x = 10, y = 20;


	//15. % 활용하여 두 정수 5를 3으로 나눈 몫과 나머지를 출력하세요
	int a = 5, b = 3;


	//16. % 활용하여 정수를 입력받아 3으로 나눈 몫과 나머지를 출력하세요


	//17. 입력한 숫자가 3의 배수인지 구하세요 (% 활용)


	//18. 입력한 값이 3보다 크고 20보다 작은지 출력하세요. (비교 연산자)
	int input = 0;
	scanf_s("%d", &input);


	//19. 입력한 문자를 대문자, 소문자, 숫자로 구분하여 출력하세요. (아스키코드)
	char input;
	cin >> input;
}
