// NewCardThread.cpp : implementation file
//

#include "stdafx.h"
#include <mbstring.h>
#include "ReadCardInfo.h"
#include "NewCardThread.h"
#include "KSCardCom.h"
#include "ReadCardInfoDlg.h"
//#include "GwGetCardInfo.h"
//#include "CIniFile.h"
//#include "DRTPHelper.h"
//#include "netutil.h"
#include "AlgorithmForString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread


CNewCardThread::~CNewCardThread()
{
}

BOOL CNewCardThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CNewCardThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CNewCardThread, CWinThread)
	//{{AFX_MSG_MAP(CNewCardThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCardThread message handlers

int CNewCardThread::DoInit()
{
	int ret = -1;
	BYTE ucCardNo[5] = "";
	BYTE max_cardno[5] = {0xFE, 0xFF, 0xFF, 0xFF, 0x00};
	char stuemp_no[21] = ""; 
	SMT_SleepCard();
	// ��ȡ��Ȩ��
	ret = ReadSerial(ucCardNo);
	if (ret < 0)
	{
		Sleep(1000);
		return 0;
	}
		
	if (_mbsncmp(ucCardNo, max_cardno, sizeof(ucCardNo) - 1) == 0)
	{
		Sleep(1000);
		return 0;
	}

	((CReadCardInfoDlg*)m_pMainWnd)->SimulateKeyPress(ucCardNo);

	Sleep(1000);
	return 0;
}

CNewCardThread::CNewCardThread(CWnd *pWnd)
{
	pre_card_id = 0;	
	m_pMainWnd = pWnd;
}

int CNewCardThread::Run()
{
/*
	if (m_pMainWnd)
	{
		m_pMainWnd->PostMessage(WM_INIT_THREAD_TERM, 0, 0);
	}
*/
	while (!m_terminate)
	{
		if (DoInit() != 0)
		{
			::AfxMessageBox("����ʧ��!");
			break;
		}
	}
	Reset();
	SMT_SleepCard();
	return CWinThread::Run();
}

void CNewCardThread::Reset()
{
	pre_card_id = 0;
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_index = 0;
	return ;
}
