#include "stdafx.h"
#include "TThread.h"

/*=================================================================
 * Notice	   :  构造函数
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
 * Notice	   :  析构函数
 *=================================================================*/
CTThread::~CTThread()
{
	WaitFor();
}

/*=================================================================
 * Notice	   :  线程启动时触发
 *				  	
 *=================================================================*/
void CTThread::OnStart()
{
	m_bStart    = TRUE ;
	m_bSuspend  = FALSE;
	m_bShutdown = FALSE;
}

/*=================================================================
 * Notice	   :  线程终止时触发
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
 * Notice	   :  启动线程
 *=================================================================*/

void CTThread::Start()
{
	if( m_hThread != NULL )
	{
		AfxMessageBox("已经运行！！！");
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
			AfxMessageBox("启动时调用_beginthreadex()失败!!!");
			return;
		}				
	}
	return ;
}

/*=================================================================
 * Notice	   :  线程Shutdown
 *=================================================================*/
void CTThread::Shutdown()
{
	m_bShutdown = TRUE ;
}

/*=================================================================
 * Notice	   :  挂起线程
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
 * Notice	   :  恢复线程
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
 * Notice	   :  强制中止线程
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
 * Notice	   :  等待直至终止线程
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
 * Notice	   :  线程体
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

