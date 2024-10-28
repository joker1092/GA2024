#pragma once
#include "WinSocket.h"
#include "StreamQue.h"

_MYNETWORK_BEGIN

class TCPSocket : public WinSocket
{
	struct TCPBuffer
	{	
		short count;
		short done;
		short bufSize;
		char* pBuffer;
	};
public:	
	TCPSocket(const int sendBufSize, const int recvBufSize);
	~TCPSocket();

	void Reset() { /*소켓풀로 재활용 하려면 필요*/ }

	bool SendUpdate();
	bool RecvUpdate();

	bool PostPacket(char* buffer, int nSize);
	bool ReadPacket(char* buffer, int nSize);
	bool PeekPacket(char* buffer, int nSize);

protected:
	TCPBuffer m_SendBuf;
	TCPBuffer m_RecvBuf;

	StreamQue* m_pSendQ;
	StreamQue* m_pRecvQ;

private:
	TCPSocket() = delete;
	TCPSocket(const TCPSocket&) = delete;
	TCPSocket& operator=(const TCPSocket&) = delete;
};

_MYNETWORK_END