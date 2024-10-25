#pragma once

// CChatSocket 명령 대상
#define WM_CONNECT (WM_USER + 1)
#define WM_DISCONNECT (WM_USER + 2)
#define WM_RECEIVE (WM_USER + 3)
class CChatSocket : public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();
    virtual void OnClose(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnSend(int nErrorCode);
};


