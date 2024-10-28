#include <cstdio>
#include "SessionManager.h"

ClientSession::~ClientSession()
{
}

void ClientSession::OnConnect()
{
    m_isConnected = true;
   
}

void ClientSession::OnClose()
{
    //todo
    printf("ClientSession::OnClose\n");
}

void ClientSession::OnReceive()
{
    //todo
    printf("ClientSession::OnReceive\n");
}


void ClientSession::SendUpdate()
{
    //todo
    printf("ClientSession::SendUpdate\n");
}
    
ClientSessionManager::ClientSessionManager()
{
    //todo
}

ClientSessionManager::~ClientSessionManager()
{
}

bool ClientSessionManager::Start(const char* ip, int port)
{
    if (Create(SOCK_STREAM, FD_ACCEPT) == false)
    {
        return false;
    }

    if (Bind(port, ip) == false)
    {
        return false;
    }

    if (Listen() == false)
    {
        return false;
    }

	m_wsaEvents.push_back(this->GetEvent());

    return true;
}

void ClientSessionManager::Update()
{
    NetUpdate();
}

void ClientSessionManager::OnAccept()
{
    ClientSession* pSession = new ClientSession();

	this->Accept(*pSession);

    pSession->SetSessionId(m_nextSessionId++);
    pSession->OnConnect();

    m_sessions.push_back(pSession);
}

void ClientSessionManager::OnReceive(ClientSession* pSession)
{
    //todo

}

void ClientSessionManager::OnClose(ClientSession* pSession)
{
    pSession->OnClose();
}

void ClientSessionManager::NetUpdate()
{
    DWORD index = WSAWaitForMultipleEvents(m_wsaEvents.size(), m_wsaEvents.data(), FALSE, 0, FALSE);
   
	if (index == WSA_WAIT_FAILED) return;
  
    if (index == WSA_WAIT_TIMEOUT) return;

    index -= WSA_WAIT_EVENT_0;

    AsyncSocket* pSocket = nullptr;

    if (index == 0) pSocket = this;
    else pSocket = m_sessions[index - 1];
  
   
    WSANETWORKEVENTS networkEvents;

    if (::WSAEnumNetworkEvents(pSocket->GetHandle(), m_wsaEvents[index], &networkEvents) == SOCKET_ERROR)
    {
     
        return;
    }

    if (networkEvents.lNetworkEvents & FD_ACCEPT)
    {
        if (networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
        {
            OnNetError(networkEvents.iErrorCode[FD_ACCEPT_BIT], "Accept");
            return;
        }

        OnAccept();
    }
    
    if (networkEvents.lNetworkEvents & FD_READ)
    {
        if (networkEvents.iErrorCode[FD_READ_BIT] != 0)
        {
            OnNetError(networkEvents.iErrorCode[FD_READ_BIT], "Read", pSocket);
            return;
        }

        ClientSession* pSession = (ClientSession*)pSocket;
        pSession->OnReceive();
    }
    
    if (networkEvents.lNetworkEvents & FD_CLOSE)
    {
        if (networkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
        {
            OnNetError(networkEvents.iErrorCode[FD_CLOSE_BIT], "Close", pSocket);
            return;
        }

        ClientSession* pSession = (ClientSession*)pSocket;
        pSession->OnClose();
    }
  

    // 각 세션 별로 수신 버퍼에 받아온 데이터를 처리하고
    // 송신 버퍼에 있는 데이터를 실제 소켓 송신을 처리해야 합니다.
    for (auto& session : m_sessions)
    {
       session->SendUpdate();
    }
}

void ClientSessionManager::OnNetError(int errorCode, const char* errorMsg, AsyncSocket* pSocket)
{
    if (errorMsg)
    {
        printf("\n onNetError %s \t", errorMsg);
    }

    if (pSocket)
    {
        printf("\n onNetError  %s : %d \t", pSocket->GetIP().c_str(), pSocket->GetPort());
    }

    printf("NetErrorCode  %d  \n", errorCode);
}

void ClientSessionManager::AddClientSession(ClientSession* pSession)
{
    m_sessions.push_back(pSession);
}

void ClientSessionManager::RemoveClientSession(SessionId id)
{
    for (auto it = m_sessions.begin(); it != m_sessions.end(); ++it)
    {
        if ((*it)->GetSessionId() == id)
        {
            delete *it;
            m_sessions.erase(it);
            break;
        }
    }
}

ClientSession* ClientSessionManager::FindClientSession(SessionId id)
{
    for (auto& session : m_sessions)
    {
        if (session->GetSessionId() == id)
        {
            return session;
        }
    }
    return nullptr;
}

void ClientSessionManager::Broadcast(const char* buf, int len)
{
    for (auto& session : m_sessions)
    {
        session->Send(buf, len);
    }
}