#pragma once
#include "AsyncSocket.h"
#include "StreamQue.h"
#include <vector>


typedef __int64 SessionId;

class ClientSession : public AsyncSocket
{
public:
    ClientSession(){}
    virtual ~ClientSession();

    void OnConnect();
    void OnClose();
    void OnReceive();

    bool IsConnected() { return m_isConnected; }

    void SetSessionId(SessionId id) { m_sessionId = id; }

    SessionId GetSessionId() { return m_sessionId; }

    void SendUpdate();

private:
    bool m_isConnected = false;

    SessionId m_sessionId = 0;

    StreamQue m_sendQue{ 8192 };
    StreamQue m_recvQue{ 8192 };
    
};

class ClientSessionManager : public AsyncSocket
{
public:
    ClientSessionManager();
    
    ~ClientSessionManager();

    bool Start(const char* ip, int port);

    void Update();

    void Stop() {/*todo*/};

 
private:

    void NetUpdate();
    

    void OnAccept();
    void OnReceive(ClientSession* pSession);
    void OnClose(ClientSession* pSession);

    void OnNetError(int errorCode, const char* errorMsg, AsyncSocket* pSocket = nullptr);
    
    void AddClientSession(ClientSession* pSession);
    
    void RemoveClientSession(SessionId id);
    
    ClientSession* FindClientSession(SessionId id);

    void Broadcast(const char* buf, int len);
     
    
    std::vector<WSAEVENT> m_wsaEvents;
    std::vector<ClientSession*> m_sessions;

    SessionId m_nextSessionId = 1;

};