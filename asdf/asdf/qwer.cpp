void Test_01()
{
	const int SIZE = 10;

	char iamCharArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10��
	int iamIntArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10�� - �ƽ�Ű�ڵ� ���̺��� �˻��� ���ô�!

	// --------------------------------------------------------------------------------
	// ���� �迭
	// --------------------------------------------------------------------------------
	for (int i = 0; i < SIZE; i++)
	{
		printf("%c\t", iamCharArray[i]); // ���ڷ� ��� �غ��ƿ�.
	}

	printf("\n"); // ���� ����. "" -> ���ڿ��ΰ� Ȯ���ϼ���.

	for (int i = 0; i < SIZE; i++)
	{
		printf("%d\t", iamCharArray[i]); // ���ڷ� ��� �غ��ƿ�. �ƽ�Ű�ڵ� ���� ã�� ���ƿ�.
	}

	printf("\n"); // ���� ����

	for (int i = 0; i < SIZE; i++)
	{
		printf("%c \t %p\n", iamCharArray[i], &iamCharArray[i]); // �ּҰ��� ����� ���ƿ�.
	}

	// --------------------------------------------------------------------------------
	// ���� �迭
	// --------------------------------------------------------------------------------
	for (int i = 0; i < SIZE; i++)
	{
		printf("%c\t", iamIntArray[i]); //  ���ڷ� ��� �غ��ƿ�.
	}

	printf("\n"); // ���� ����

	for (int i = 0; i < SIZE; i++)
	{
		printf("%c \t %p\n", iamCharArray[i], &iamIntArray[i]); // �ּҰ��� ����� ���ƿ�.
	}
}

void Test_02()
{
	// --------------------------------------------------------------------------------
	// �迭�� �������� ���迡 ���� Ȯ���� ���ô�.
	// --------------------------------------------------------------------------------

	const int SIZE = 10;

	char iamCharArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10��
	int iamIntArray[SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' }; // 10�� - �ƽ�Ű�ڵ� ���̺��� �˻��� ���ô�!

	//1. �迭�� �ּ�
	printf("%c \t %p \t %p \n", iamCharArray[0], iamCharArray, &iamCharArray[0]); // ù ��° �ε����� �ּҸ� �˾� ���ô�.
	printf("%c \t %p \t %p \n", iamIntArray[0], iamIntArray, &iamIntArray[0]);

	printf("\n"); // ���� ����

	//2. ������ ������ �迭�� �ּҸ� ������ ���ô�.
	char* pChar0 = iamCharArray;		// &iamIntArray[0]; �� �ּҰ��� ���ٴ� �� ����ϼ���.

	int* pInt0 = iamIntArray;			// ������ ������ Ÿ���� Ȯ���ϼ���.

	// * ������ ����(�ּ�)�� ����Ű�� �ִ� ���� �޸��� ��
	// ������ ��
	// & ������ �ּ�
	printf("%c \t %p \t %p \n", *pChar0, pChar0, &pChar0);
	printf("%c \t %p \t %p \n", *pInt0, pInt0, &pInt0);
}

void Test_03()
{
	// --------------------------------------------------------------------------------
	// 1���� �迭�� 2���� �迭�� ���迡 ���� ������ ���ô�.
	// --------------------------------------------------------------------------------
	int array10[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int array52[5][2] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	int array25[2][5] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

	//5�� 2��
	int matrix52[5][2] =
	{
		{'a', 'b'},
		{'c', 'd'},
		{'e', 'f'},
		{'g', 'h'},
		{'i', 'j'}
	};

	//2�� 5��
	int matrix25[2][5] =
	{
		{'a', 'b', 'c', 'd', 'e'},
		{'f', 'g', 'h', 'i', 'j'}
	};

	//F9 ����� �극��ũ�� �ɰ� �������� Ȯ���� ���ô�.

	//�迭�� ������
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

	/* ����! �Ʒ� �ڵ� �����? ������ ����? ���� ����?
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