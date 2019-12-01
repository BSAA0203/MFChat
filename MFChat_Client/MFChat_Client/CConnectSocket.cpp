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
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CMFChatClientDlg* pMain = (CMFChatClientDlg*)AfxGetMainWnd();
		pMain->ChatList.AddString(szBuffer);
		pMain->ChatList.SetCurSel(pMain->ChatList.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
