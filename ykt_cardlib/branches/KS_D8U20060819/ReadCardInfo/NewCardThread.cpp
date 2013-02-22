// NewCardThread.cpp : implementation file
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "NewCardThread.h"
#include "KSCardCom.h"
#include "ReadCardInfoDlg.h"

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
	unsigned long SNR = 0;

	ret = ReadCardSNR(&SNR);
	if (ret)
	{
		Sleep(500);
		return 0;
	}
	CARD_INFO CI;
	char msg[256] = "";
	memset(&CI, 0, sizeof(CI));
	ret = ReadCardInfo(&CI);
	if (ret)
	{
		//GetLastErrMsg(msg);
		//::AfxMessageBox(msg);
		return 0;
	}
	((CReadCardInfoDlg*)m_pMainWnd)->SimulateKeyPress(CI);
	// 就是上一张卡
	/*
	if (SNR == pre_card_id)
	{
		Sleep(500);
		return 0;
	}
	pre_card_id = SNR;

	if (m_pMainWnd)
	{
		ComBeep();
		m_pMainWnd->PostMessage(WM_READ_CARD, ++m_index, 0);
	}
	*/
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
	while (!m_terminate)
	{
		if (DoInit() != 0)
		{
			AfxMessageBox("读卡失败!");
			break;
		}
	}
	if (m_pMainWnd)
	{
		m_pMainWnd->PostMessage(WM_INIT_THREAD_TERM, 0, 0);
	}
	Reset();
	return CWinThread::Run();
}

CNewCardThread::Reset()
{
	pre_card_id = 0;
	if (m_hThread != NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_index = 0;
}
