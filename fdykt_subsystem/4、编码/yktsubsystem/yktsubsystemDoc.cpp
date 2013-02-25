// yktsubsystemDoc.cpp : implementation of the CYktsubsystemDoc class
/** 
 * ģ����						�����ϵͳ
 * �ļ���						yktsubsystemDoc.cpp
 * �ļ�ʵ�ֹ���					Document �࣬����ϵͳ��������
 * ����							����
 * �汾							V0.2
 * ����							2005-07-02
 * ��ע
 * $Id: yktsubsystemDoc.cpp 23 2005-09-02 08:41:36Z cheng.tang $
 *
 *
 *	�޸�ʱ��		�汾	����	˵��
 *	2005-08-29		V0.2	����	�����������ʱȡ����ȷMAC��ַ�Ĵ���
 *	
 */


#include "stdafx.h"
#include "yktsubsystem.h"

#include <vector>
#include <string>
#include <algorithm>

#include "yktsubsystemDoc.h"
#include "sysutil.h"
#include "SysSettingPage.h"
#include "MainFrm.h"
#include "KLogfile.h"
#include "LogFactory.h"
#include "RequestSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

def(int,registe_module,(ksf_plugin_module * module));
def(int,unregiste_module,(ksf_plugin_module * module));
/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemDoc

IMPLEMENT_DYNCREATE(CYktsubsystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CYktsubsystemDoc, CDocument)
	//{{AFX_MSG_MAP(CYktsubsystemDoc)
	ON_COMMAND(ID_SERVER_CFG, OnServerCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemDoc construction/destruction

CYktsubsystemDoc::CYktsubsystemDoc()
:m_listenSock(NULL),m_runRequest(0)
{
	memset(&m_svr_conf,0,sizeof(ksf_server_conf));
	m_allowIPList.clear();
	InitializeCriticalSection(&m_mutex);
}

CYktsubsystemDoc::~CYktsubsystemDoc()
{
	DeleteCriticalSection(&m_mutex);
}

BOOL CYktsubsystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// ���� plugin 
	m_plugin_manage.LoadModuleConfig(TRUE);
	LoadServerConfig();
	LoadAllowIPList();
	if( m_plugin_manage.IsModuleLoaded() )
	{
		// ������سɹ�����������
		StartListening();
	}
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);
	SetTitle(title);
	//AfxGetMainWnd()->SetWindowText(title);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemDoc serialization

void CYktsubsystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemDoc diagnostics

#ifdef _DEBUG
void CYktsubsystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CYktsubsystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYktsubsystemDoc commands

void CYktsubsystemDoc::OnServerCfg() 
{
	CPropertySheet ps(IDS_SERVER_PROP);
	
	CSysSettingPage settingPage(this);
	ps.AddPage(&settingPage);

	ps.DoModal();
}

void CYktsubsystemDoc::OnCloseDocument() 
{
	StopListening();
	m_plugin_manage.UnRegistePluginModule();
	SaveServerConfig();
	CDocument::OnCloseDocument();
}

BOOL CYktsubsystemDoc::StopListening()
{
	if( m_listenSock )
	{
		if(GetRunningRequest())
		{
			if(AfxMessageBox(
				"���ڴ�������,�رշ�����ܵ������ݴ������!\n�Ƿ�Ҫ�رգ�",
				MB_YESNO|MB_DEFBUTTON2) == IDNO)
			{
				return FALSE;
			}
			ReleaseTimeoutSocket(0);
		}
		KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
		m_listenSock->Close();
		delete m_listenSock;
		m_listenSock = NULL;
		log->WriteLog("�رշ�����������");
		m_runRequest = 0;
	}
	return TRUE;
}

BOOL CYktsubsystemDoc::StartListening()
{
	BOOL bOk = FALSE;
	if(!m_plugin_manage.IsModuleLoaded())
	{
		return bOk;
	}
	if(!StopListening())
	{
		return bOk;
	}
	m_listenSock = new CListenSocket( this );
	if ( m_listenSock )
	{
		KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
		if ( m_listenSock->Create( m_svr_conf.port, SOCK_STREAM, FD_ACCEPT ) )
			bOk = m_listenSock->Listen();
		
		if ( !bOk )
		{
			CString strMsg;
			int nErr = m_listenSock->GetLastError();
			if ( nErr == WSAEADDRINUSE )
			{
				strMsg.Format( IDS_LISTEN_INUSE, m_svr_conf.port );
			}
			else
			{
				strMsg.Format( IDS_LISTEN_ERROR, m_svr_conf.port );
				
			}
			log->WriteLog("�������ڶ˿�[%d]����ʧ�ܣ�", m_svr_conf.port);
			AfxMessageBox( strMsg, MB_OK|MB_ICONSTOP );
			m_listenSock->Close();
			delete m_listenSock;
			m_listenSock = NULL;
		}
		else
		{
			log->WriteLog("�������ڶ˿�[%d]��ʼ����...",m_svr_conf.port);
			/*
			CString status;
			status.LoadString(IDS_SEVER_START);
			CMainFrame * pWnd = (CMainFrame*)AfxGetMainWnd();
			CStatusBar * bar = (CStatusBar*)pWnd->GetStatusBar();
			UINT nIndex = bar->CommandToIndex(ID_INDICATOR_SCRL);
			*/
			//bar->setItem
			//AfxGetMainWnd()->GetDlgItem(ID_INDICATOR_SCRL)->SetWindowText(status);
		}
	}
	else
		AfxMessageBox( IDS_CANT_LISTEN, MB_OK|MB_ICONSTOP );
	m_timeStarted = CTime::GetCurrentTime();
	return bOk;
}

void CYktsubsystemDoc::LoadServerConfig()
{
	CString port;
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	port.LoadString(IDD_DEFAULT_PORT);
	port = AfxGetApp()->GetProfileString(INI_SVR_SECT,INI_SVR_PORT,port);
	m_svr_conf.port = atoi(port);
	// ����ж������,��ȡ�󶨵�IP
	CString tmpip = AfxGetApp()->GetProfileString(INI_SVR_SECT,INI_SVR_BINDIP,"");
	string bindip(tmpip);
	vector<string> ip_list;
	ksf_get_local_ip(ip_list);
	if( !ip_list.empty() )
	{
		string ip;
		string mac;
		if(!bindip.empty())
		{
			// ����а󶨵�IP
			vector<string>::iterator iter;
			iter = find(ip_list.begin(),ip_list.end(),bindip);
			if(iter == ip_list.end())
			{
				// �����IP��ϵͳIP��ͬ,ʹ�õ�һ��IP
				ip = * ip_list.begin();
			}
			else
			{
				// ��IP��ϵͳIP��ͬ,ʹ�����IP
				ip = *iter;
			}
		}
		else
		{
			// ���û�а�IP,ʹ�õ�һ��IP
			ip = * (ip_list.begin());
		}
		
		ksf_get_mac_by_ip(ip,mac);
		strncpy(m_svr_conf.ip,ip.c_str(),ip.length());
		strncpy(m_svr_conf.mac,mac.c_str(),mac.length());
		//strcpy(m_svr_conf.ip,"10.55.100.105");
		//strcpy(m_svr_conf.mac,"000BDBD05447");
		log->WriteLog("��ȡ��ϵͳ��Ϣ��[%s][%s]",m_svr_conf.ip
			,m_svr_conf.mac);
	}
	else
	{
		AfxMessageBox("��ȡIPʧ��,ϵͳ���ܲ�����������!");
	}
}

BOOL CYktsubsystemDoc::IsListening()
{
	return (m_listenSock != NULL);
}
void CYktsubsystemDoc::SaveServerConfig()
{
	CString strPort;
	strPort.Format("%d",m_svr_conf.port);
	AfxGetApp()->WriteProfileString(INI_SVR_SECT,INI_SVR_PORT,strPort);
}

void CYktsubsystemDoc::LoadAllowIPList()
{
	int i,j,pos;
	int count;
	CString sectName;
	CString ip;
	long sock;
	char * p;
	char c;
	count = AfxGetApp()->GetProfileInt(INI_CONNECT_SECT,INI_CONNECT_COUNT,0);
	for(i = 1;i <= count;++i)
	{
		sectName.Format("%s%d",INI_CONNECT_IP,i);
		ip = AfxGetApp()->GetProfileString(INI_CONNECT_SECT,sectName,"");
		if(!ip.IsEmpty())
		{
			p = (char*)&sock;
			memset(p,0,sizeof(sock));
			j = 0;
			pos = ip.Find('.',j);
			while(pos != -1 && j < ip.GetLength())
			{
				c = (char)atoi(ip.Mid(j,pos));
				*p++ = c;
				j = pos + 1;
				pos = ip.Find('.',j);
			}
			if(j < ip.GetLength() )
			{
				*p++ = atoi(ip.Mid(j));
			}
			if((p - sizeof(sock)) == (char*)&sock)
			{
				m_allowIPList.push_back(sock);
			}
		}
	}
}
BOOL CYktsubsystemDoc::IsAllowIP(in_addr * sockin)
{
	vector<long>::iterator iter;
	long addr;
	in_addr * in;
	char *p;
	char *q;
	int i;
	for(iter = m_allowIPList.begin();iter != m_allowIPList.end();++iter)
	{
		addr = (*iter);
		in = (in_addr*)&addr;
		if(memcmp(&addr,sockin,sizeof(addr)) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}
int CYktsubsystemDoc::ReleaseTimeoutSocket(long timeout)
{
	CRequestSocket* req;
	KLogfile * log = KLogFactory::GetInstance()->GetLogSys();
	int count;
	EnterCriticalSection(&m_mutex);
	if(m_runningSocket.empty())
	{
		LeaveCriticalSection(&m_mutex);
		return 0;
	}
	vector<CRequestSocket*> temp(m_runningSocket.begin(),m_runningSocket.end());
	LeaveCriticalSection(&m_mutex);
	vector<CRequestSocket*>::iterator iter = temp.begin();
	long currentTick = GetTickCount();
	for(count = 0;iter != temp.end();++iter)
	{
		req = *iter;
		try
		{
			if(!req->IsRunning())
			{
				if((currentTick - req->GetStartTick() >= timeout) 
					|| (timeout == -1))
				{
					log->WriteLog("�ͷų�ʱSocket!");
					count++;
					delete req;
				}
			}
		}
		catch (...) 
		{
			log->WriteLog("ָ���쳣!!");
			// ignore all 
			// ��֤��ִ�� LeaveCriticalSection
		}
	}
	log->WriteLog("�ͷ�[%d]����ʱ���ӣ�����[%d]������",
		count,m_runningSocket.size());
	return count;
}
int CYktsubsystemDoc::DecRunningRequest(CRequestSocket* sock)
{
	EnterCriticalSection(&m_mutex);
	if(sock != NULL)
	{
		vector<CRequestSocket*>::iterator iter;
		iter = find(m_runningSocket.begin(),m_runningSocket.end(),sock);
		if(iter != m_runningSocket.end())
		{
			m_runningSocket.erase(iter);
			--m_runRequest;
			if(m_runRequest <0 )
			{
				m_runRequest = 0;
			}
		}	
	}
	LeaveCriticalSection(&m_mutex);
	return m_runRequest;
}
