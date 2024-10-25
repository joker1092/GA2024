// CChatSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCClient.h"
#include "CChatSocket.h"



// CChatSocket

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}


// CChatSocket 멤버 함수


void CChatSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    AfxGetApp()->m_pMainWnd->PostMessage(WM_DISCONNECT, nErrorCode, 0);
	CAsyncSocket::OnClose(nErrorCode);
}


void CChatSocket::OnConnect(int nErrorCode)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    AfxGetApp()->m_pMainWnd->PostMessage(WM_CONNECT, nErrorCode, 0);

    CAsyncSocket::OnConnect(nErrorCode);
}


void CChatSocket::OnReceive(int nErrorCode)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    AfxGetApp()->m_pMainWnd->PostMessage(WM_RECEIVE, nErrorCode, 0);
    CAsyncSocket::OnReceive(nErrorCode);
}


void CChatSocket::OnSend(int nErrorCode)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

    CAsyncSocket::OnSend(nErrorCode);
}
