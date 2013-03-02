// ForwardThread.h: interface for the CForwardThread class.
//
//////////////////////////////////////////////////////////////////////
/********************************************************************
	created:	2004/03/13
	created:	13:3:2004   16:25
	filename: 	E:\proj\goldmem\ksbcc\ForwardThread.h
	file path:	E:\proj\goldmem\ksbcc
	file base:	ForwardThread
	file ext:	h
	author:		CHENYH
	
	purpose:	
*********************************************************************/

#if !defined(AFX_FORWARDTHREAD_H__8D43C587_80D1_4997_8EB5_21586D13082A__INCLUDED_)
#define AFX_FORWARDTHREAD_H__8D43C587_80D1_4997_8EB5_21586D13082A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cpack.h"
#include "comstru.h"
#include "mutex.h"
#include "WThread.h"


class CReqPack  
{
public:
   RECEIVEDATA rdata;      // 接收到的请求数据包
   unsigned int rtime;      // 接收到的时间点

	CReqPack();
   CReqPack(const CReqPack &rpack);
	virtual ~CReqPack();
};


class CFReqPack  
{
public:
   RECEIVEDATA rdata;      // 接收到的请求数据包
   ST_PACKHEAD head;       // 请求数据包头
   unsigned int rtime;      // 接收到的时间点

	CFReqPack();
   CFReqPack(const CFReqPack &rpack);
	virtual ~CFReqPack();

};


typedef std::deque<CReqPack> RPQUEUE;
typedef std::list<CFReqPack> RPLIST;

typedef struct
{
   RPQUEUE  packs;
   CMUTEX   m_mutex;
} RPACKQUEUE;

typedef struct
{
   RPLIST packs;
   CMUTEX m_mutex;
} RPACKLIST;

class CForwardThread : public CWThread  
{
public:

private:
   RPACKLIST tFRQueue;

public:
	bool PutFRPackToQueue(RECEIVEDATA *recvdata,ST_PACKHEAD *phead);
	bool ProcessFRequest(RECEIVEDATA *recvdata,ST_PACKHEAD *phead,bool bTimeOut=false);
	CForwardThread();
	virtual ~CForwardThread();

private:
	int Run();
};


#endif // !defined(AFX_FORWARDTHREAD_H__8D43C587_80D1_4997_8EB5_21586D13082A__INCLUDED_)
