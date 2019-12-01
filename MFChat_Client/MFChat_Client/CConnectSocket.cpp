#include "stdafx.h"
#include "CConnectSocket.h"
#include "MFChat_ClientDlg.h"


CConnectSocket::CConnectSocket()
{
}


CConnectSocket::~CConnectSocket()
{
}


void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
	AfxMessageBox(L"ERROR: Disconnected from server!");
	::PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTmp = L"";
	CString strIPAdress = L"";
	UINT uPortNumber = 0;
	GetPeerName(strIPAdress, uPortNumber); 

	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CMFChatClientDlg* pMain = (CMFChatClientDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[IP- %s] : %s"), strIPAdress, szBuffer);
		pMain->ChatList.AddString(strTmp);
		pMain->ChatList.SetCurSel(pMain->ChatList.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
