void Test_01()
{
	const int SIZE = 10;

	char iamCharArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10개
	int iamIntArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10개 - 아스키코드 테이블을 검색해 봅시다!

	// --------------------------------------------------------------------------------
	// 문자 배열
	// --------------------------------------------------------------------------------
	for (int i = 0; i < SIZE; i++)
	{
		printf("%c\t", iamCharArray[i]); // 문자로 출력 해보아요.
	}

	printf("\n"); // 라인 변경. "" -> 문자열인걸 확인하세요.

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\t", iamCharArray[i]); // 숫자로 출력 해보아요. 아스키코드 값을 찾아 보아요.
	}

	printf("\n"); // 라인 변경

	for (int i = 0; i < SIZE; i++)
	{
		printf("%c \t %p\n", iamCharArray[i], &iamCharArray[i]); // 주소값을 출력해 보아요.
	}

	// --------------------------------------------------------------------------------
	// 정수 배열
	// --------------------------------------------------------------------------------
	for (int i = 0; i < SIZE; i++)
	{
		printf("%c\t", iamIntArray[i]); //  문자로 출력 해보아요.
	}

	printf("\n"); // 라인 변경

	for (int i = 0; i < SIZE; i++)
	{
		printf("%c \t %p\n", iamCharArray[i], &iamIntArray[i]); // 주소값을 출력해 보아요.
	}
}

void Test_02()
{
	// --------------------------------------------------------------------------------
	// 배열과 포인터의 관계에 대해 확인해 봅시다.
	// --------------------------------------------------------------------------------

	const int SIZE = 10;

	char iamCharArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10개
	int iamIntArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10개 - 아스키코드 테이블을 검색해 봅시다!

	//1. 배열의 주소
	printf("%c \t %p \t %p \n", iamCharArray[0], iamCharArray, &iamCharArray[0]); // 첫 번째 인덱스의 주소를 알아 봅시다.
	printf("%c \t %p \t %p \n", iamIntArray[0], iamIntArray, &iamIntArray[0]);

	printf("\n"); // 라인 변경

	//2. 포인터 변수에 배열의 주소를 저장해 봅시다.
	char* pChar0 = iamCharArray;		// &iamIntArray[0]; 와 주소값이 같다는 걸 기억하세요.

	int* pInt0 = iamIntArray;			// 포인터 변수의 타입을 확인하세요.

	// * 포인터 변수(주소)가 가르키고 있는 변수 메모리의 값
	// 변수의 값
	// & 변수의 주소
	printf("%c \t %p \t %p \n", *pChar0, pChar0, &pChar0);
	printf("%c \t %p \t %p \n", *pInt0, pInt0, &pInt0);
}

void Test_03()
{
	// --------------------------------------------------------------------------------
	// 1차원 배열과 2차원 배열의 관계에 대해 생각해 봅시다.
	// --------------------------------------------------------------------------------
	int array10[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int array52[5][2] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int array25[2][5] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

	//5행 2열
	int matrix52[5][2] =
	{
		{'a', 'b'},
		{'c', 'd'},
		{'e', 'f'},
		{'g', 'h'},
		{'i', 'j'}
	};

	//2행 5열
	int matrix25[2][5] =
	{
		{'a', 'b', 'c', 'd', 'e'},
		{'f', 'g', 'h', 'i', 'j'}
	};

	//F9 디버그 브레이크를 걸고 변수값을 확인해 봅시다.

	//배열과 포인터
	int* pArray = array10;
	int(*pMat52)[2] = array52;
	int(*pMat25)[5] = array25;
	//////////////////////////////////////////////

	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			printf("%c\t", array52[row][col]);
		}

		printf("\n");
	}

	printf("\n");

	int index = 0;
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			index = row * 2 + col;

			printf("%c\t", array10[index]);
		}

		printf("\n");
	}

	printf("\n");

	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			index = row * 5 + col;

			printf("%c\t", array10[index]);
		}

		printf("\n");
	}

	printf("\n");

	/* 퀴즈! 아래 코드 결과는? 컴파일 에러? 실행 에러?
	for (int i = 0; i < 10; i++)
	{
		printf("%c\t", array52[i]); .
	}
	printf("\n");

	for (int i = 0; i < 10; i++)
	{
		printf("%c\t", array25[i]);
	}
	printf("\n");
	*/
}