#include "WinSocket.h"

_MYNETWORK_BEGIN

bool	WinSocket::Open(int iProtocol)
{
	if (iProtocol == IPPROTO_TCP)
	{
		m_s = WSASocket(AF_INET, SOCK_STREAM, iProtocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
	}
	else if (iProtocol == IPPROTO_UDP)
	{
		m_s = WSASocket(AF_INET, SOCK_DGRAM, iProtocol, NULL, NULL, WSA_FLAG_OVERLAPPED);
	}

	//Check for socket validity
	if (!IsValid()) return false;

	return true;
}

bool	WinSocket::Bind(SOCKADDR_IN& localAddr)
{
	if (SOCKET_ERROR == ::bind(m_s, (SOCKADDR*)(&localAddr), sizeof(SOCKADDR_IN)))
		return false;

	m_localAddr = localAddr;

	return true;
}

bool	WinSocket::Connect(SOCKADDR_IN& remoteAddr)
{
	if (SOCKET_ERROR == WSAConnect(m_s, (SOCKADDR*)(&remoteAddr), sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL))
	{
		if (WSAEWOULDBLOCK != WSAGetLastError()) return false;
	}

	return true;
}

bool	WinSocket::Listen()
{
	if (SOCKET_ERROR == ::listen(m_s, SOMAXCONN)) return false;

	return true;
}

SOCKET	WinSocket::Accept(SOCKADDR_IN& remoteAddr)
{
	int iAddrLen = sizeof(remoteAddr);

	return WSAAccept(m_s, (SOCKADDR*)&remoteAddr, &iAddrLen, NULL, 0);
}

int		WinSocket::Recv(char* pInBuf, int nLen, int& error, LPWSAOVERLAPPED pOv, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	WSABUF	wsa;
	wsa.buf = pInBuf;
	wsa.len = nLen;

	DWORD nRecv = 0, flag = 0;

	if (SOCKET_ERROR != WSARecv(m_s, &wsa, 1, &nRecv, &flag, (LPWSAOVERLAPPED)pOv, lpCompletionRoutine))
	{
		return nRecv;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err || WSA_IO_PENDING == err) return 0;

	return -1;
}

int		WinSocket::Send(char* pOutBuf, int nLen, int& error, LPWSAOVERLAPPED pOv, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	WSABUF	wsa;
	wsa.buf = pOutBuf;
	wsa.len = nLen;

	DWORD nSent = 0, flag = 0;

	if (SOCKET_ERROR != WSASend(m_s, &wsa, 1, &nSent, flag, pOv, lpCompletionRoutine))
	{
		return nSent;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err || WSA_IO_PENDING == err) return 0;

	return -1;
}

int		WinSocket::RecvFrom(char* pInBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv)
{
	WSABUF	wsa;
	wsa.buf = pInBuf;
	wsa.len = nLen;

	DWORD nRecv = 0, flag = 0;

	int	iAddrLen = sizeof(remoteAddr);

	if (SOCKET_ERROR != WSARecvFrom(m_s, &wsa, 1, &nRecv, &flag, (SOCKADDR*)&remoteAddr, &iAddrLen, pOv, NULL))
	{
		return nRecv;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err) return 0;

	return -1;
}

int		WinSocket::SendTo(char* pOutBuf, int nLen, int& error, SOCKADDR_IN& remoteAddr, LPWSAOVERLAPPED pOv)
{
	WSABUF	wsa;
	wsa.buf = pOutBuf;
	wsa.len = nLen;

	DWORD nSent = 0, flag = 0;
	if (SOCKET_ERROR != WSASendTo(m_s, &wsa, 1, &nSent, flag, (SOCKADDR*)&remoteAddr, sizeof(remoteAddr), pOv, NULL))
	{
		return nSent;
	}

	int err = WSAGetLastError();
	error = err;

	if (WSAEWOULDBLOCK == err) return 0;

	return -1;
}


void	WinSocket::Close()
{
	closesocket(m_s);
	m_s = INVALID_SOCKET;
}

void	WinSocket::Shutdown(int how)
{
	::shutdown(m_s, how);
}

_MYNETWORK_END