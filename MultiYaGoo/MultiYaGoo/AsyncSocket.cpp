#include "AsyncSocket.h"
#include <ws2tcpip.h>

AsyncSocket::AsyncSocket()
{
}

AsyncSocket::~AsyncSocket()
{
	WSACloseEvent(m_hEvent);

	Close();

}

bool AsyncSocket::Create(int nSocketType, long lEvent)
{
	m_hSocket = ::WSASocket(AF_INET, nSocketType, 0, nullptr, 0, 0);

	if (m_hSocket == INVALID_SOCKET)
	{
		m_error = ::WSAGetLastError();
		return false;
	}

	// �񵿱� ���� �̺�Ʈ ����
	m_hEvent = ::WSACreateEvent();
	if (m_hEvent == WSA_INVALID_EVENT) return false;

	if (::WSAEventSelect(m_hSocket, m_hEvent, lEvent) == SOCKET_ERROR)
	{
		m_error = ::WSAGetLastError();
		return false;
	}

	return true;
}


bool AsyncSocket::Bind(int port, const char* lpszSocketAddress)
{
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;

	::inet_pton(AF_INET, lpszSocketAddress, &(serverAddr.sin_addr));

	serverAddr.sin_port = ::htons(port);

	if (::bind(m_hSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		m_error = ::WSAGetLastError();
		return false;
	}

	return true;
}

bool AsyncSocket::Listen(int backlog)
{
	if (::listen(m_hSocket, backlog) == SOCKET_ERROR)
	{
		m_error = ::WSAGetLastError();
		return false;
	}

	return true;
}

bool AsyncSocket::Accept(AsyncSocket& acceptSocket)
{
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);

	SOCKET hClientSocket = ::accept(m_hSocket, (SOCKADDR*)&clientAddr, &addrLen);

	if (hClientSocket == INVALID_SOCKET)
	{
		m_error = ::WSAGetLastError();
		return false;
	}

	acceptSocket.Attach(hClientSocket);

	char ipv4AddressAsString[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(clientAddr.sin_addr), ipv4AddressAsString, INET_ADDRSTRLEN);
	acceptSocket.m_ip = ipv4AddressAsString;

	acceptSocket.m_port = ::ntohs(clientAddr.sin_port);

	WSAEVENT clientEvent = ::WSACreateEvent();
	acceptSocket.SetEvent(clientEvent);

	if (::WSAEventSelect(hClientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		m_error = ::WSAGetLastError();

		WSACloseEvent(clientEvent);

		closesocket(hClientSocket);

		return false;
	}

	return true;
}

bool AsyncSocket::Connect(const char* ip, int port)
{
	//TODO:
	return false;
}

void AsyncSocket::Close()
{
	::closesocket(m_hSocket);
}

int AsyncSocket::Send(const char* buf, int len)
{
	int sendLen = ::send(m_hSocket, buf, len, 0);

	m_error = ::WSAGetLastError();

	if (sendLen == SOCKET_ERROR && m_error != WSAEWOULDBLOCK)
	{
		return SOCKET_ERROR;
	}

	return sendLen;
}

int AsyncSocket::Recv(char* buf, int len)
{
	int recvLen = ::recv(m_hSocket, buf, len, 0);

	m_error = ::WSAGetLastError();

	if (recvLen == SOCKET_ERROR && m_error != WSAEWOULDBLOCK)
	{
		return SOCKET_ERROR;
	}

	return recvLen;
}

int AsyncSocket::SendTo(const char* buf, int len, const char* ip, int port)
{
	// TODO:
	return 0;
}
int AsyncSocket::RecvFrom(char* buf, int len, char* ip, int* port)
{
	// TODO:
	return 0;
}

bool InitWinSock()
{
	WSAData wsaData;

	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}


	return true;
}

void CleanupWinSock()
{
	::WSACleanup();
}