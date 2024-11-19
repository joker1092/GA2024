
// MFCClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"
#include "CChatSocket.h"
#include "PacketHeader.h"

//#define IP_ADRESS "127.0.0.1" //로컬
//#define IP_ADRESS "172.21.1.60" //민재
//#define IP_ADRESS "172.21.1.32" //용우
#define IP_ADRESS "172.21.1.35" //세민

#define PORT 6060


#ifdef _DEBUG
#define new DEBUG_NEW
//#define IP_ADRESS "127.0.0.1" //로컬
#endif

// CMFCClientDlg 대화 상자



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCClientDlg::~CMFCClientDlg()
{
    if (m_bConnected)
    {
        m_pChatSocket->Close();
        delete m_pChatSocket;
    }
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_NetMsgList);
    DDX_Control(pDX, IDC_EDIT1, m_ChatInput);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CONNECTION, &CMFCClientDlg::OnBnClickedConnection)
    ON_MESSAGE(WM_CONNECT, &CMFCClientDlg::OnConnect)
    ON_MESSAGE(WM_DISCONNECT, &CMFCClientDlg::OnDisconnect)
    ON_MESSAGE(WM_RECEIVE, &CMFCClientDlg::OnReceive)
END_MESSAGE_MAP()


// CMFCClientDlg 메시지 처리기

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
 

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCClientDlg::OnBnClickedConnection()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (!m_bConnected)
    {
        m_pChatSocket = new CChatSocket;
        m_pChatSocket->Create();
        m_pChatSocket->Connect(_T(IP_ADRESS), PORT);
    }
    else
    {
        //m_pChatSocket->Close();
        AfxGetApp()->m_pMainWnd->PostMessage(WM_DISCONNECT, 0, 0);
        //m_bConnected = FALSE;
    }
}


void CMFCClientDlg::OnFinalRelease()
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    if (m_bConnected)
    {
        m_pChatSocket->Close();
    }
    delete m_pChatSocket;

    CDialogEx::OnFinalRelease();
}




afx_msg LRESULT CMFCClientDlg::OnConnect(WPARAM wParam, LPARAM lParam)
{
    int errCode = (int)wParam;
    if (errCode != 0)
    {
        CString str;
        str.Format(_T("Connection failed (%u)"), errCode);
        m_NetMsgList.InsertString(-1,str);
    }
    else
    {
        m_NetMsgList.InsertString(-1,_T("Connected"));
        m_bConnected = TRUE;
    }

    return 0;
}


afx_msg LRESULT CMFCClientDlg::OnDisconnect(WPARAM wParam, LPARAM lParam)
{
    int errCode = (int)wParam;
    if (errCode != 0)
    {
        if(errCode==10053) {
            m_NetMsgList.InsertString(-1,_T("Server Disconnect"));
            
        }
        else {
            CString str;
            str.Format(_T("DisConnection failed (%u)"), errCode);
            m_NetMsgList.AddString(str);
        }
    }
    else
    {
        m_NetMsgList.InsertString(-1,_T("DisConnected"));
        
    }
    m_bConnected = FALSE;
    m_pChatSocket->Close();

    return 0;
}


BOOL CMFCClientDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

    if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
    {
        if (pMsg->wParam == VK_RETURN)
        {
            if (m_bConnected)
            {
                PacketC2S_Chat* packet = new PacketC2S_Chat();
                CString str;
                m_ChatInput.GetWindowText(str);
                memcpy_s(packet->msg, sizeof(packet->msg), str, sizeof(packet->msg));
                m_pChatSocket->Send(packet, packet->len);
                m_ChatInput.SetWindowText(_T(""));
                delete packet;
            }
            else {
                m_NetMsgList.InsertString(-1, _T("server not conneted"));
            }
            
        }
        return TRUE;
    }

    return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CMFCClientDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
    char buffer[1024] = "";
    char msg[512] = "";
    int nRecv = m_pChatSocket->Receive(buffer, 1024);

    if (nRecv > 0)
    {
        PacketType type = ((PacketHeader*)buffer)->type;
        switch (type)
        {
        case PacketType::S2C_ECHO:
            break;
        case PacketType::S2C_CONNECT:
            break;
        case PacketType::S2C_DISCONNECT:
            break;
        case PacketType::S2C_CHAT:
            {
                PacketS2C_Chat* chatPacket = (PacketS2C_Chat*)buffer;
                sprintf_s(msg, sizeof(msg), "[%d] : %s", chatPacket->id, chatPacket->msg);
                m_NetMsgList.InsertString(-1, msg);
            }
            break;
        case PacketType::S2C_TIME_OUT:
            break;
        case PacketType::HEADER_COUNT:
            break;
        }
    }
    else
    {
        int errCode = (int)wParam;
        CString str;
        str.Format(_T("ErrorCode  (% u)"), errCode);

        m_NetMsgList.InsertString(-1, str);
    }

    return 0;
}
