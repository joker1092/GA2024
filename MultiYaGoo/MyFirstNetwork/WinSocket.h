#pragma once
#include <winsock2.h>
#include <Ws2ipdef.h>

#include "CommonDefines.h"
#include "StreamQue.h"

_MYNETWORK_BEGIN

struct SOCKET_INFO
{
	SOCKET	s;
	SOCKADDR_IN addr;
};


class WinSocket
{
public:
	WinSocket() 
	{ 
		m_s = INVALID_SOCKET;  
		memset(&m_localAddr, 0, sizeof(m_localAddr));
	}

	~WinSocket()
	{
		if (m_s != INVALID_SOCKET) closesocket(m_s);
	}

	
	SOCKET	GetHandle() { return m_s; }
	bool	IsValid() { return ((INVALID_SOCKET == m_s) ? false : true); }

	void	Attach(SOCKET s) { m_s = s; }
	SOCKET	Detach()
	{
		SOCKET	s = m_s;
		m_s = INVALID_SOCKET;
		return s;
	}

	bool	Open(int iProtocol);
	bool	Bind(SOCKADDR_IN& localAddr);
	bool	Connect(SOCKADDR_IN& remoteAddr);

	bool	Listen();
	SOCKET	Accept(SOCKADDR_IN& remoteAddr);

	int		Recv(char* pInBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL);
	int		Send(char* pOutBuf, int nLen, int& error, LPWSAOVERLAPPED pOv = NULL, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = NULL);
	int		RecvFrom(char* pInBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv = NULL);
	int		SendTo(char* pOutBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv = NULL);


	void	Close();
	void	Shutdown(int how = SD_BOTH);

protected:

	SOCKET m_s;
	SOCKADDR_IN	m_localAddr;

private:
	WinSocket(const WinSocket& rhs) = delete;
	WinSocket& operator=(const WinSocket& rhs) = delete;
};

_MYNETWORK_END
