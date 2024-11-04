#include <memory.h>
#include <algorithm>
#include "StreamQue.h"

StreamQue::StreamQue(const int size)
{
    m_size = size;
    m_buffer = (char*)malloc(size);
    Clear();
}

StreamQue::~StreamQue()
{
    free(m_buffer);
}

bool StreamQue::Peek(char* buffer, int size)
{
    if(size > Count()) return false;

    if (m_readPos < m_writePos)
    {
        memcpy(buffer, &m_buffer[m_readPos], size);
    }else{
        int nBackPart = m_size - m_readPos;

        if (size <= nBackPart)
        {
            memcpy(buffer, &m_buffer[m_readPos], size);
        }
        else {
            int nForePar = size - nBackPart;
            memcpy(&buffer[0], &m_buffer[m_readPos], nBackPart);
            memcpy(&buffer[nBackPart],&m_buffer[0], nForePar);
        }
    }

    return true;
}

int StreamQue::Read(char* destbuffer, int size)
{
    if (IsEmpty()) return 0;
    
    int nRead = std::min<short>(m_nData,size);
    if (m_readPos < m_writePos)
    {
        memcpy(destbuffer, &m_buffer[m_readPos], nRead);
    }
    else {
        int nBackPart = m_size - m_readPos;
        if (nRead < nBackPart)
        {
            memcpy(destbuffer, &m_buffer[m_readPos], nRead);
        }
        else {
            int nForePart = nRead - nBackPart;
            memcpy(&destbuffer[0], &m_buffer[m_readPos], nBackPart);
            memcpy(&destbuffer[nBackPart], &m_buffer[0], nForePart);
        }
    }

    m_nData -= nRead;
    m_readPos = (m_readPos + nRead) % m_size;

    return nRead;
}

int StreamQue::Write(const char* srcData, int size)
{
    if (IsFull()) return 0;
    
    int nSpace = Space();
    int nWrite = std::min<short>(nSpace, size);

    if (m_readPos > m_writePos) {
        memcpy(&m_buffer[m_writePos], srcData, nWrite);
    }
    else {
        int nBackPart = m_size - m_writePos;
        if (nBackPart >= nWrite)
        {
            memcpy(&m_buffer[m_writePos], srcData, nWrite);
        }
        else {
            int nForePart = nWrite - nBackPart;
            memcpy(&m_buffer[m_writePos], &srcData[0], nBackPart);
            memcpy(&m_buffer[0], &srcData[nBackPart], nForePart);
        }
    }

    m_nData += nWrite;
    m_writePos = (m_writePos + nWrite) % m_size;

    return nWrite;
}
