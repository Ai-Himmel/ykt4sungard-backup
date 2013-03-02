// mutex.h: interface for the CMUTEX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTEX_H__41E159AF_3A8F_471C_A5CB_03544AD54994__INCLUDED_)
#define AFX_MUTEX_H__41E159AF_3A8F_471C_A5CB_03544AD54994__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif


class CMUTEX  
{
public:
	void UnLock();
	void Lock();
	CMUTEX();
	virtual ~CMUTEX();


protected:
#ifdef WIN32
   HANDLE m_lock;
#else
   pthread_mutex_t m_lock;
#endif
};


class CPMUTEX  
{
public:
	CPMUTEX(CMUTEX *pmutex);
	virtual ~CPMUTEX();
private:
   CMUTEX *p_mutex;
};

#endif // !defined(AFX_MUTEX_H__41E159AF_3A8F_471C_A5CB_03544AD54994__INCLUDED_)
