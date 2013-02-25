// ListenSocket.cpp : implementation file
//
/** 
 * ģ����						�����ϵͳ
 * �ļ���						ListenSocket.cpp
 * �ļ�ʵ�ֹ���					��������Socket��
 * ����							����
 * �汾							V0.1
 * ����							2005-07-02
 * ��ע
 * $Id: ListenSocket.cpp 15 2005-08-22 02:39:12Z cash $
 */

#include "stdafx.h"
#include "yktsubsystem.h"
#include "ListenSocket.h"
#include "RequestSocket.h"
#include "LogFactory.h"
#include "KLogfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenSocket

CListenSocket::CListenSocket(CYktsubsystemDoc * pDoc)
:m_pDoc(pDoc)
{
}

CListenSocket::~CListenSocket()
{
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions
BOOL CListenSocket::IsAllowAddr(SOCKADDR * inaddr)
{
	sockaddr_in * addr_in;
	//char addr_str[5] = "";
	//CString ipaddr;
	addr_in = (sockaddr_in*)inaddr;
	//memcpy(addr_str,&addr_in->sin_addr,sizeof(addr_str) - 1);
	
	//ipaddr.Format("%d.%d.%d.%d",addr_str[0],addr_str[1],addr_str[2],addr_str[3]);
	return m_pDoc->IsAllowIP(&addr_in->sin_addr);
}
void CListenSocket::OnAccept(int nErrorCode) 
{
	SOCKADDR inaddr;
	KLogfile * log;
	int addrlen;
	// TODO: Add your specialized code here and/or call the base class
	CRequestSocket * reqSock = new CRequestSocket(m_pDoc);
	addrlen = sizeof(inaddr);
	if( Accept( *reqSock,&inaddr,&addrlen) )
	{
		CString ipaddr;
		unsigned char* addr_str = (unsigned char*)&((sockaddr_in*)&inaddr)->sin_addr;
		ipaddr.Format("%d.%d.%d.%d",addr_str[0],addr_str[1],addr_str[2],addr_str[3]);
		log = KLogFactory::GetInstance()->GetLogSys();
		log->WriteLog("���մ�IP[%s]����",ipaddr);
		if(IsAllowAddr(&inaddr))
		{
			m_pDoc->IncRunningRequest(reqSock);
			reqSock->AsyncSelect(FD_READ|FD_CLOSE);
			//reqSock->ProcessRequest();			
		}
		else
		{
			log->WriteLog("����IP[%s]�����󱻾ܾ���",ipaddr);
			delete reqSock;
		}
	}
}
