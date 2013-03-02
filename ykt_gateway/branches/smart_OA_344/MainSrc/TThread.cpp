#include "stdafx.h"
#include "TThread.h"

/*=================================================================
 * Notice	   :  ���캯��
 *=================================================================*/
CTThread::CTThread()
{
	m_bStart    = FALSE;
	m_bShutdown = TRUE ;
	m_hThread   = NULL ;
	m_dwThreadID= 0;
	m_bSuspend  = TRUE ;
}

/*=================================================================
 * Notice	   :  ��������
 *=================================================================*/
CTThread::~CTThread()
{
	WaitFor();
}

/*=================================================================
 * Notice	   :  �߳�����ʱ����
 *				  	
 *=================================================================*/
void CTThread::OnStart()
{
	m_bStart    = TRUE ;
	m_bSuspend  = FALSE;
	m_bShutdown = FALSE;
}

/*=================================================================
 * Notice	   :  �߳���ֹʱ����
 *=================================================================*/
void CTThread::OnShutdown()
{
	if( m_hThread != NULL )
	{
		CloseHandle(m_hThread);
		m_hThread = NULL ;
	}
}

/*=================================================================
 * Notice	   :  �����߳�
 *=================================================================*/

void CTThread::Start()
{
	if( m_hThread != NULL )
	{
		AfxMessageBox("�Ѿ����У�����");
	}
	else
	{
		OnStart();
		m_hThread = (HANDLE)_beginthreadex(NULL, 0,	ThreadProc, this, 0, (unsigned int*)&m_dwThreadID);
		if( m_hThread == NULL )
		{
			m_bStart    = FALSE ;
			m_bSuspend  = TRUE;
			m_bShutdown = TRUE;			
			AfxMessageBox("����ʱ����_beginthreadex()ʧ��!!!");
			return;
		}				
	}
	return ;
}

/*=================================================================
 * Notice	   :  �߳�Shutdown
 *=================================================================*/
void CTThread::Shutdown()
{
	m_bShutdown = TRUE ;
}

/*=================================================================
 * Notice	   :  �����߳�
 *=================================================================*/
void CTThread::Suspend()
{
	if( !m_bSuspend )
	{
		m_bSuspend = TRUE ;
		SuspendThread(m_hThread);
	}
}

/*=================================================================
 * Notice	   :  �ָ��߳�
 *=================================================================*/
void CTThread::Resume()
{
	if( !m_bSuspend )
	{
		ResumeThread(m_hThread);
		m_bSuspend = FALSE ;
	}
}

/*=================================================================
 * Notice	   :  ǿ����ֹ�߳�
 *=================================================================*/
void CTThread::Terminate(DWORD dwExitCode)
{
	if( m_hThread != NULL )
	{
		TerminateThread(m_hThread, dwExitCode);
		CloseHandle(m_hThread);
		m_hThread = NULL ;
	}
	m_bShutdown = TRUE ;
}

/*=================================================================
 * Notice	   :  �ȴ�ֱ����ֹ�߳�
 *=================================================================*/
BOOL CTThread::WaitForQuit()
{
	if( IsSuspend() )
	{
		Resume();
	}
	Shutdown();
	return WaitFor();
}

/*=================================================================
 *=================================================================*/
BOOL CTThread::WaitFor(DWORD dwTimeOut)
{
	if( m_hThread == NULL )
	{
		return FALSE;
	}

	DWORD dwResult = WaitForSingleObject(m_hThread, dwTimeOut);
	if( dwResult == WAIT_TIMEOUT )
	{
		Terminate();
		return FALSE;
	}
	else if( dwResult == WAIT_FAILED ) 
	{
		Terminate();
		return FALSE;
	}

	CloseHandle(m_hThread);
	m_hThread = NULL ;
	return TRUE;
}

/*=================================================================
 * Notice	   :  �߳���
 *=================================================================*/
unsigned int __stdcall CTThread::ThreadProc(LPVOID lpvoid)
{
	CTThread *pThread = (CTThread*)lpvoid;

	if( !pThread->IsShutdown() )
	{
			pThread->Run();
	}			
	pThread->OnShutdown();
	pThread->m_bStart = FALSE ;
	_endthreadex(0);	
	return 0L;
}

