
// MFChat_ClientDlg.h: 헤더 파일
//

#pragma once
#include "CConnectSocket.h"


// CMFChatClientDlg 대화 상자
class CMFChatClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFChatClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CConnectSocket m_Socket;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHAT_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox ChatList;
	afx_msg void OnBnClickedButton1();
	CEdit textfield;
};
