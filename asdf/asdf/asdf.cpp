#include <iostream>

int main()
{
	//자릿수
	printf("%3d\n", 3);
	printf("%-3d\n", 3);
	printf("%03d\n", 7);

	printf("time %02d:%02d\n", 7, 36);

	printf("%4d\n", 654536);

	double dData = 123.456;
	printf("%lf,%f\n", dData, -123.456);

	printf("%.1f\n", dData);
	printf("%.2f\n", dData);
	printf("%.3f\n", dData);
	printf("%12.3f\n", dData);
	printf("%012.3f\n", dData);


	/*printf("Hello World!\n");
	printf("level %d\n", 10);
	printf("level %c\n", 'A');
	printf("level %s\n", "abc");

	printf("%d %s %f\n", 3, "hello",12.25);

	printf("number %d %d\n", 10,10);*/

	//printf() => format을 알고 서식문자를 알아야 한다.
	//%d 서식문자: 십진수 문자
	//printf("%d\n",100);
	//int num = 1.5; // 예외사항

	//표현식(expression) , 문장 (statement)

	/*표현식 ex>
	1 + 2
	level > 10
	c = a * b

	문장 ex>
	int a = 1;
	printf("%d",num);
	문자의 끝은 ;
	*/

	/*printf("%d %d %d\n", 1, 2, 3);
	printf("%d,%d,%d\n", 1, 2, 3);
	printf("%d, %d, %d\n", 1, 2, 3);
	printf("(%d,%d,%d)\n", 1, 2, 3);*/

}

