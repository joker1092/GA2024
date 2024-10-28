#include <memory.h>
#include <algorithm>
#include "StreamQue.h"

_MYNETWORK_BEGIN

bool StreamQue::Peek(char* peekBuf, int peekLen)
{
	if (peekLen > Count()) return false;

	if (m_readIndex < m_writeIndex)
	{
		memcpy(peekBuf, &m_buffer[m_readIndex], peekLen);
	}
	else
	{
		int nBackPart = m_size - m_readIndex;

		if (peekLen <= nBackPart)
		{
			memcpy(peekBuf, &m_buffer[m_readIndex], peekLen);

		}
		else
		{
			int nForePart = peekLen - nBackPart;
			memcpy(&peekBuf[0], &m_buffer[m_readIndex], nBackPart);
			memcpy(&peekBuf[nBackPart], &m_buffer[0], nForePart);
		}
	}

	return true;
}


int StreamQue::Read(char* desBuf, int bufLen)
{
	if (IsEmpty()) return 0;

	int nRead = std::min<short>(m_nData, bufLen);
	if (m_readIndex < m_writeIndex)
	{
		memcpy(desBuf, &m_buffer[m_readIndex], nRead);
	}
	else
	{
		int nBackPart = m_size - m_readIndex;

		if (nRead <= nBackPart)
		{
			memcpy(desBuf, &m_buffer[m_readIndex], nRead);

		}
		else
		{
			int nForePart = nRead - nBackPart;
			memcpy(&desBuf[0], &m_buffer[m_readIndex], nBackPart);
			memcpy(&desBuf[nBackPart], &m_buffer[0], nForePart);
		}
	}

	m_nData -= nRead;
	m_readIndex += nRead;
	if (m_readIndex >= m_size) m_readIndex -= m_size;

	return nRead;
}

int StreamQue::Write(const char* srcData, int bytesData)
{
	if (IsFull()) return 0;

	int nSpace = Space();
	int nWrite = std::min<short>(nSpace, bytesData);

	if (m_readIndex > m_writeIndex)
	{
		memcpy(&m_buffer[m_writeIndex], srcData, nWrite);
	}
	else
	{
		int nBackSpace = m_size - m_writeIndex;

		if (nBackSpace >= nWrite)
		{
			memcpy(&m_buffer[m_writeIndex], srcData, nWrite);
		}
		else
		{
			int nForeSpace = nWrite - nBackSpace;
			memcpy(&m_buffer[m_writeIndex], &srcData[0], nBackSpace);
			memcpy(&m_buffer[0], &srcData[nBackSpace], nForeSpace);
		}
	}

	m_nData += nWrite;
	m_writeIndex += nWrite;
	if (m_writeIndex >= m_size) m_writeIndex -= m_size;

	return nWrite;
}

_MYNETWORK_END