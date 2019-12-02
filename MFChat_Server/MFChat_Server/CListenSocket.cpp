#include "stdafx.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "MFChat_ServerDlg.h"

CListenSocket::CListenSocket()
{
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CClientSocket* pClient = new CClientSocket;
	CString str;

	if (Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);

		CMFChatServerDlg* pMain = (CMFChatServerDlg*)AfxGetMainWnd(); // CSocketServerDlg�� �ڵ��� ������
		str.Format(_T("Client (%d)"), (int)m_ptrClientSocketList.Find(pClient)); // Ŭ���̾�Ʈ ��ȣ(POSITION(�ּ�) ��)
		pMain->Client_List.AddString(str);
	}
	else
	{
		delete pClient;
		AfxMessageBox(L"ERROR: Failed to accept new client!");
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	if (pos != NULL)
	{
		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}

		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
	}
}
