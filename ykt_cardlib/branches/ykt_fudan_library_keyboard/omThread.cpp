// omThread.cpp : implementation file
//

#include "stdafx.h"
#include "KeyInspect.h"
#include "omThread.h"
#include "KeyInspectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ComThread

IMPLEMENT_DYNCREATE(ComThread, CWinThread)

ComThread::ComThread()
{

}

ComThread::~ComThread()
{
}

BOOL ComThread::InitInstance()
{
	m_pucReadBuf   = new BYTE[1024];
	m_pucSmtBuf    = new BYTE[1024];
	m_bAutoDelete  = FALSE;
	m_dwReadMaxNum = sizeof(BYTE)*1024;
	m_dwReadLength = 0;
	m_nReadNum     = 0;
	m_nReadOffset  = 0;
	return TRUE;
	
}

int ComThread::ExitInstance()
{
	delete[] m_pucReadBuf;
	delete[] m_pucSmtBuf;
	return 0;
	//return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(ComThread, CWinThread)
	//{{AFX_MSG_MAP(ComThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ComThread message handlers

int ComThread::Run() 
{
	DWORD dwEvtMask ;
	//int nLength ;

	if (!::SetCommMask(m_pDlg->m_hCom,EV_RXCHAR ))
		return ( FALSE );
	while (!m_bAutoDelete)
	{
		dwEvtMask = 0 ;
		::WaitCommEvent(m_pDlg->m_hCom,&dwEvtMask,NULL);
		if ((dwEvtMask&EV_RXCHAR)==EV_RXCHAR)
		{
			//AfxMessageBox("hell",MB_OK);
			ReadCommBlock();
		}
	}
	return (ExitInstance());
	
	//return CWinThread::Run();
}

void ComThread::ReadCommBlock()
{
	COMSTAT    ComStat ;
    DWORD      dwLength;
    DWORD      dwErrorFlags;
    BYTE       ucReadBuf[1024];
	HWND hWnd;
	hWnd = m_pDlg->m_hWnd;

	ClearCommError(m_pDlg->m_hCom, &dwErrorFlags, &ComStat ) ;
	dwLength = min(m_dwReadMaxNum,ComStat.cbInQue);
	if (dwLength > 0)
	{
		::ReadFile(m_pDlg->m_hCom,ucReadBuf,dwLength,&dwLength,&m_pDlg->m_osRead);
		memcpy(m_pucSmtBuf,ucReadBuf,dwLength);
		PostMessage(hWnd,WM_RECV_MESSAGE,dwLength,m_nPortNo);
	}


}
