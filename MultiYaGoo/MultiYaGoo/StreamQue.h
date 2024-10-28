#pragma once

class StreamQue
{
public:
	StreamQue() = delete;
	StreamQue(const StreamQue&) = delete;
	StreamQue& operator=(const StreamQue&) = delete;

	StreamQue(const int size);
	~StreamQue();

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

protected:
	short	m_size = 0;
	short	m_nData = 0;
	short	m_readIndex = 0;
	short	m_writeIndex = 0;
	char*	m_buffer = nullptr;
};

