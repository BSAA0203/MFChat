#include "stdafx.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include "MFChat_ServerDlg.h"

CClientSocket::CClientSocket()
{
	m_pListenSocket = NULL;
}


CClientSocket::~CClientSocket()
{
}

void CClientSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CSocket::OnClose(nErrorCode);
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString strTmp = L"";
	CString strIPAdress = L"";
	UINT uPortNumber = 0;
	TCHAR szBuffer[1024];
	::ZeroMemory(szBuffer, sizeof(szBuffer));

	GetPeerName(strIPAdress, uPortNumber);
	if (Receive(szBuffer, sizeof(szBuffer)) > 0)
	{
		CMFChatServerDlg* pMain = (CMFChatServerDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[IP - %s, Port - %d] : %s"), strIPAdress, uPortNumber, szBuffer);
		pMain->Chat_list.AddString(strTmp);
		pMain->Chat_list.SetCurSel(pMain->Chat_list.GetCount() - 1);

		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->SendChatDataAll(szBuffer);
	}

	CSocket::OnReceive(nErrorCode);
}
