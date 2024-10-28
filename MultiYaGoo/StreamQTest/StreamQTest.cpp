// StreamQTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "../MultiYaGoo/StreamQue.h"

class TestStreamQue : public StreamQue
{
public:
	TestStreamQue(int size) : StreamQue(size) {}
    ~TestStreamQue() {}
	void DebugPrint()
	{
		for (int i = 0; i < m_size; i++)
		{
			printf("%c, ", m_buffer[i]);
		}

		printf("\n %d / %d, R = %d, W = %d\n", m_nData, m_size, m_readIndex, m_writeIndex);
    }
};

void Test_StreamQue()
{
	char writeStr[] = "*0123456789@";
	char readBuf[20] = "";
	TestStreamQue streamQ(12);
	int nRead = 0;

	printf("-------- StreamQue TEST --------------\n");
	// 딱 맞추서 넣기
	streamQ.Clear();
	printf("Write %d\n", streamQ.Write(writeStr, 12));
	streamQ.DebugPrint();

	printf("-------- StreamQue TEST --------------\n");
	// 그냥, 넣기
	streamQ.Clear();
	printf("Write %d\n", streamQ.Write(writeStr, 1));
	printf("Write %d\n", streamQ.Write(writeStr, 2));
	printf("Write %d\n", streamQ.Write(writeStr, 10));
	printf("Write %d\n", streamQ.Write(writeStr, 10));
	streamQ.DebugPrint();

	printf("-------- StreamQue TEST --------------\n");
	// 읽기
	streamQ.Clear();
	printf("Write %d\n", streamQ.Write(writeStr, 12));
	streamQ.DebugPrint();
	nRead = streamQ.Read(readBuf, 1);
	readBuf[nRead] = 0;
	printf("Read %d\t %s\n", nRead, readBuf);

	printf("Write %d\n", streamQ.Write(writeStr, 12));
	streamQ.DebugPrint();
	nRead = streamQ.Read(readBuf, 2);
	readBuf[nRead] = 0;
	printf("Read %d\t %s\n", nRead, readBuf);

	printf("Write %d\n", streamQ.Write(writeStr, 12));
	streamQ.DebugPrint();
	nRead = streamQ.Read(readBuf, 20);
	readBuf[nRead] = 0;
	printf("Read %d\t %s\n", nRead, readBuf);

	printf("-------- StreamQue TEST --------------\n");
	streamQ.Clear();
	for (int i = 0; i < 5; i++)
	{
		printf("Write %d\n", streamQ.Write(writeStr, 5));
		streamQ.DebugPrint();
		nRead = streamQ.Read(readBuf, 4);
		readBuf[nRead] = 0;
		printf("Read %d\t %s\n", nRead, readBuf);
	}
}

int main()
{
	Test_StreamQue();
}

