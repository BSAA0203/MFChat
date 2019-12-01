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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
	AfxMessageBox(L"ERROR: Disconnected from server!");
	::PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
