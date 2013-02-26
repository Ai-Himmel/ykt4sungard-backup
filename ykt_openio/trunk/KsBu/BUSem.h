/********************************************************************
	created:	2007/11/15
	created:	15:11:2007   11:38
	filename: 	D:\proj\ksbass\testipc\MQDLL\BUSem.h
	file path:	D:\proj\ksbass\testipc\MQDLL
	file base:	BUSem
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	为了能够创建一个适合于Windows或Unix或Linux下的一个信号灯
         由于Windows下的信号灯不采用成组操作，因此，其他平台也就只选用一个信号量
*********************************************************************/
// BUSem.h: interface for the CBUSem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_)
#define AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>
#define H_SEMP HANDLE
#define INVALID_SEMP NULL
#else
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define H_SEMP int
#define INVALID_SEMP -1

//#define MAXSEMPNO 100 在AIX下测试过程中，发现在用64个以上的线程测试的时候，会显得相当的慢, 由此怀疑这个问题
#define MAXSEMPNO 50
#endif


class CBUSem  
{
private:
   H_SEMP m_sempid;
   int    m_sempno;

public:
	void Remove(const char *name, int semid);
	bool Open(const char *name, int semid, int maxvalue);
	void SetValue(int value);
	int GetValue();
	bool IsOpened();
	int V();               // 释放可用资源计数，增加SEMP计数 +1
	int P(int usTimeout);  // 减少可用资源计数，减少SEMP计数 -1
	void Close();
	CBUSem();
	virtual ~CBUSem();

private:
   
};

#endif // !defined(AFX_BUSEM_H__A7F8F520_79EE_4798_ABB6_9F2846FA15DB__INCLUDED_)
