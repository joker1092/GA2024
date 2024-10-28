#pragma once
#include <stdlib.h>
#include "CommonDefines.h"

// TCP 네트워크 데이타는 바이트스트림으로 다룹니다.
// 환형 큐로 구현

_MYNETWORK_BEGIN

class StreamQue
{
public:
	StreamQue() = delete;
	StreamQue(const StreamQue&) = delete;
	StreamQue& operator=(const StreamQue&) = delete;

	StreamQue(const int size)
	{
		m_size = size;
		m_buffer = (char*)malloc(size);
		Clear();
	}
	~StreamQue()
	{
		free(m_buffer);
	}

	bool IsEmpty() { return (m_nData == 0) ? true : false; }
	bool IsFull() {
		return (m_size == m_nData) ? true : false;
	};

	void Clear()
	{
		m_nData = m_readIndex = m_writeIndex = 0;
		memset(m_buffer, 0, m_size);
	}

	int Space() { return m_size - m_nData; }
	int	Size() { return m_size; }
	int	Count() { return m_nData; }

	bool Peek(char* peekBuf, int peekLen);
	int Read(char* desBuf, int bufLen);
	int Write(const char* srcData, int bytesData);

private:
	short	m_size;
	short	m_nData;
	short	m_readIndex;
	short	m_writeIndex;
	char*	m_buffer;
};

_MYNETWORK_END