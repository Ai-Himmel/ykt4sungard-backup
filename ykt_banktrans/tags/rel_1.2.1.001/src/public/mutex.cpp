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
