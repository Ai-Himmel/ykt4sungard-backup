// WThread.cpp: implementation of the CWThread class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#include <process.h>
#else
#include <pthread.h>
#endif
#include "stdafx.h"
#include "mypub.h"
#include "WThread.h"

int CWThread::thread_count=0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWThread::CWThread(char *threadname)
{
   strncpy(szName,threadname,sizeof(szName)-1);
   szName[sizeof(szName)-1]='\0';
   thread_count++;
#ifdef WIN32
   m_hThread = (HANDLE)-1L;
#else
   m_hThread = (pthread_t)-1;
#endif
}

CWThread::~CWThread()
{
	if((int)m_hThread != -1)
#ifdef WIN32
	{
		TerminateThread(m_hThread, -1);
		m_hThread = (HANDLE)-1;
	}
#else
	// Force the thread to terminate if it has not already done so.
	// Is it safe to do this to a thread that has already terminated?
   {
      pthread_cancel(m_hThread); 
      m_hThread = (pthread_t)-1;
   }
#endif
   thread_count--;
}



bool CWThread::Terminate()
{
   return(true);
}

int CWThread::Run()
{
   return(0);
}

void CWThread::Kill()
{
	delete this;   
}

#ifdef WIN32
void CWThread::ThreadProc(void *p)
#else
void* CWThread::ThreadProc(void *p)
#endif
{
	try{

		CWThread* pThread = (CWThread*) p;
		if(pThread->Init ())
		{
         pThread->m_starttime = time(NULL);
			pThread->Run();
			pThread->Terminate();
		}
#ifdef WIN32
      pThread->m_hThread = (HANDLE)-1L;
#else
      pThread->m_hThread = (pthread_t)-1L;
#endif
	}
	catch(...)
	{
		DebugFileOut("runtimedebug","WThread::ThreadProc Exception !!!!!!",__FILE__,__LINE__);
	}
}

bool CWThread::Init()
{
   return(true);
}

bool CWThread::CreateThread()
{
#ifdef WIN32
	m_hThread = (HANDLE)_beginthread(ThreadProc,0, this);	
	return ((int)m_hThread!=-1);
#else
	int ret=false;
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if((pthread_create(&m_hThread,&attr,ThreadProc, this))==0)
	{
		ret=true;
	}
   else
   {
      m_hThread = (pthread_t)-1;
   }
	pthread_attr_destroy(&attr);
	return ret;
#endif
}

bool CWThread::IsStoped()
{
   return ((int)m_hThread==-1);
}
