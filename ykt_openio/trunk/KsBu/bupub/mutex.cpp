// mutex.cpp: implementation of the CMUTEX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mutex.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMUTEX::CMUTEX()
{
#ifdef  WIN32
   m_lock=CreateMutex(NULL,FALSE,NULL);
#else
   pthread_mutex_init(&m_lock,NULL);
#endif
}

CMUTEX::~CMUTEX()
{
#ifdef  WIN32
   CloseHandle(m_lock);
#else
   pthread_mutex_destroy(&m_lock);
#endif
}

void CMUTEX::Lock()
{
#ifdef  WIN32
   WaitForSingleObject(m_lock, INFINITE);
#else
   pthread_mutex_lock(&m_lock);
#endif
}

void CMUTEX::UnLock()
{
#ifdef  WIN32
	ReleaseMutex(m_lock);
#else
	pthread_mutex_unlock(&m_lock);
#endif
}



// 函数名: CMUTEX::TryLock
// 编程  : 陈永华 2005-7-1 9:27:14
// 描述  : 尝试去加锁占用该互斥体
// 返回  : int 
//          1: 成功加锁占用了该互斥体
//          0: 加锁不成功
//          -1: 出错（可能该对象不是互斥体或是其他原因）
int CMUTEX::TryLock()
{
//    int rtn;
#ifdef WIN32
   switch (WaitForSingleObject(m_lock,0))
   {
   case WAIT_OBJECT_0:
      return(1);  // 成功
   case WAIT_FAILED: 
      return(-1);  // 错误
   case WAIT_ABANDONED:  
      // The specified object is a mutex object that was not released by 
      // the thread that owned the mutex object before the owning thread terminated. 
      // Ownership of the mutex object is granted to the calling thread, and the mutex is set to nonsignaled
   case WAIT_TIMEOUT:
   default:  
      return(0);   
   }
#else
   switch (pthread_mutex_trylock(&m_lock))
   {
   case 0:        // 上锁成功
      return(1);
   case EINVAL:   // 互斥变量参数错误
      return(-1);
   default:       // EBUSY：互斥体此前已经被上锁了
      return(0);
   }
#endif
}

//////////////////////////////////////////////////////////////////////
// CPMUTEX Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPMUTEX::CPMUTEX(CMUTEX *pmutex)
{
   p_mutex = pmutex;
   p_mutex->Lock();
}

CPMUTEX::~CPMUTEX()
{
   p_mutex->UnLock();
}


//////////////////////////////////////////////////////////////////////
// CMutexEvent Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMutexEvent::CMutexEvent()
{
#ifdef WIN32
   m_event = CreateEvent(NULL,FALSE,FALSE,NULL);
#else
   pthread_cond_init(&m_event,NULL);
#endif
}

CMutexEvent::~CMutexEvent()
{
#ifdef WIN32
   CloseHandle(m_event);
#else
   pthread_cond_destroy(&m_event);
#endif
}

void CMutexEvent::WaitEvent()
{
#ifdef WIN32
   UnLock();
   WaitForSingleObject(m_event,INFINITE);
   Lock();
#else
   pthread_cond_wait(&m_event,&m_lock);
#endif
}



void CMutexEvent::SetEvent()
{
#ifdef WIN32
   ::SetEvent(m_event);
#else
   pthread_cond_signal(&m_event);   // 不采用加锁，因为只有一个线程会调用本实例的这个函数
#endif
}

void CMutexEvent::WaitEventTime(unsigned int wait_ms)
{
#ifdef WIN32
   UnLock();
   WaitForSingleObject(m_event,wait_ms);
   Lock();
#else
   struct timespec tms;
   struct timeval  now;
/* ****** Updated by CHENYH at 2008-11-28 15:49:39 ****** 
   struct timezone tz;
   gettimeofday(&now,NULL);
   now.tv_usec += (wait_ms%1000);
   if (now.tv_usec>1000)
   {
      now.tv_sec+=now.tv_usec/1000;
      now.tv_usec = now.tv_usec%1000;
   }
   tms.tv_sec = now.tv_sec + (wait_ms/1000);
   tms.tv_nsec = now.tv_usec*1000;
*****************************************************/
   unsigned int usecadd = (wait_ms%1000)*1000;
   //clock_gettime(CLOCK_REALTIME, &tms);
   gettimeofday(&now,NULL);
   now.tv_usec += usecadd;
   if (now.tv_usec>=1000000)
   {
      now.tv_sec += (now.tv_usec/1000000);
      now.tv_usec %= 1000000;
   }

   tms.tv_sec = wait_ms/1000+now.tv_sec;
   tms.tv_nsec = now.tv_usec*1000;
   pthread_cond_timedwait(&m_event,&m_lock,&tms);
#endif
}
