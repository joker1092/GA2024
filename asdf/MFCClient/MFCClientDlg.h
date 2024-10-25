
// MFCClientDlg.h: 헤더 파일
//

#pragma once

class CChatSocket;

// CMFCClientDlg 대화 상자
class CMFCClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnection();
    virtual void OnFinalRelease();

private:
    CChatSocket* m_pChatSocket;
protected:
    afx_msg LRESULT OnConnect(WPARAM wParam, LPARAM lParam);
private:
    // 이벤트 및 메세지 출력 리스트
    CListBox m_NetMsgList;
    BOOL m_bConnected; // 연결 상태
protected:
    afx_msg LRESULT OnDisconnect(WPARAM wParam, LPARAM lParam);
private:
    // 메세지 입력창
    CEdit m_ChatInput;
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
};
