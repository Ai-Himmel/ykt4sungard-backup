// WThread.h: interface for the CWThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTHREAD_H__9C1211C0_8173_49B9_B5D0_0E8AFC291FEC__INCLUDED_)
#define AFX_WTHREAD_H__9C1211C0_8173_49B9_B5D0_0E8AFC291FEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef HP_UX     // 2006-7-4 10:41:18 for aCC (HP-UX64)
#include <pthread.h>
#endif

class CWThread  
{
public:
   char szName[32];
#ifdef WIN32
	HANDLE m_hThread;
#else
	pthread_t m_hThread;   
#endif
	static int thread_count;
   time_t m_starttime;   // 线程启动时间点，用time(NULL)
   
public:
	bool IsStoped();
	bool CreateThread();
	virtual bool Init();
	virtual void Kill();
	CWThread(char *threadname="wthread");
	virtual ~CWThread();

private:
#ifdef WIN32
	static void ThreadProc(void* p);
#else
	static void* ThreadProc(void* p);
#endif
	virtual int Run();
	virtual bool Terminate();
};

#endif // !defined(AFX_WTHREAD_H__9C1211C0_8173_49B9_B5D0_0E8AFC291FEC__INCLUDED_)
