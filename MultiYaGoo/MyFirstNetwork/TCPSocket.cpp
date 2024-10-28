#include "DebugUtils.h"
#include "TCPSocket.h"
_MYNETWORK_BEGIN

TCPSocket::TCPSocket(const int sendBufSize, const int recvBufSize)
{
	m_SendBuf.count = 0;
	m_SendBuf.done = 0;
	m_SendBuf.bufSize = sendBufSize;
	m_SendBuf.pBuffer = (char*)malloc(sendBufSize);

	m_RecvBuf.count = 0;
	m_RecvBuf.bufSize = sendBufSize;
	m_RecvBuf.pBuffer = (char*)malloc(sendBufSize);

	m_pSendQ = new StreamQue(sendBufSize * 4);
	m_pRecvQ = new StreamQue(recvBufSize * 4);
}

TCPSocket::~TCPSocket()
{
	free(m_SendBuf.pBuffer);
	free(m_RecvBuf.pBuffer);

	delete m_pSendQ;
	delete m_pRecvQ;
}

bool TCPSocket::SendUpdate()
{
	int error = 0;
	int nSent = 0;
	char* pStart = nullptr;
	// �۽� ������ �����͸� (���� ���۷�) �� ���´��� Ȯ��
	int remain = m_SendBuf.count - m_SendBuf.done;
	
	if (remain > 0)
	{
		// ���� �۽� ������ �����͸� ���� ������.
		pStart = &m_SendBuf.pBuffer[m_SendBuf.done];	
	}
	else if (remain == 0)
	{
		// �۽� ������ �����͸� �� ���´ٸ� ��Ʈ��ť���� �����͸� ��������.
		m_SendBuf.count = m_pSendQ->Read(m_SendBuf.pBuffer, m_SendBuf.bufSize);
		m_SendBuf.done = 0;
		remain = m_SendBuf.count;

		pStart = m_SendBuf.pBuffer;
	}
	
	_ASSERT(remain >= 0);

	nSent = WinSocket::Send(pStart, remain, error);
	if (nSent < 0)return false; /*TODO: error Log...*/

	m_SendBuf.done += nSent;

	return true;
}

bool TCPSocket::RecvUpdate()
{
	int error = 0;

	// ���� ������ �����͸� ��������.
	int space = m_RecvBuf.bufSize - m_RecvBuf.count;
	if (space > 0)
	{
		int nRecv = WinSocket::Recv(&m_RecvBuf.pBuffer[m_RecvBuf.count], space, error);
		if (nRecv > 0) m_RecvBuf.count += nRecv;
	}

	// ���� ������ �����͸� ��Ʈ��ť�� ������
	int remain = m_RecvBuf.count - m_RecvBuf.done;

	_ASSERT(remain >= 0);

	if (remain > 0)
	{
		m_RecvBuf.done += m_pRecvQ->Write(&m_RecvBuf.pBuffer[m_RecvBuf.done], remain);
	}

	if (m_RecvBuf.done == m_RecvBuf.count) // ���� ���� ���� ��������
	{
		m_RecvBuf.count = 0;
		m_RecvBuf.done = 0;
	}
	
	return true;

}

bool TCPSocket::PostPacket(char* buffer, int nSize)
{
	if (m_pSendQ->Space() < nSize) return false;

	m_pSendQ->Write(buffer, nSize);

	return true;
}

bool TCPSocket::ReadPacket(char* buffer, int nSize)
{
	if (m_pRecvQ->Count() < nSize) return false;

	m_pRecvQ->Read(buffer, nSize);

	return true;
}

bool TCPSocket::PeekPacket(char* buffer, int nSize)
{
	return m_pRecvQ->Peek(buffer, nSize);
}
_MYNETWORK_END