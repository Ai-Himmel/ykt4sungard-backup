// PushThread.h: interface for the CPushThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_)
#define AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "dbf.h"
#include "vector"

class CDestStatus  
{
public:
   unsigned short iDestNo; // 目标点的通讯平台节点号
   unsigned short iFuncNo; // 目标点的注册功能号

   unsigned int  batchno; // 当前目标点的会话ID （在注册登录时分配，直到下次新登录时+1）

   int    iSourceNo;  // 本目标点可以通过哪个通讯平台发送递达数据
   time_t tSendTime;  // 上次发送的时间
   time_t tSendTime0; // 首次发送的时间
   unsigned int unAckRecord; // 上次未确认的记录

public:
	CDestStatus();
	CDestStatus(const CDestStatus &ds);
	virtual ~CDestStatus();

};

// 目的是为了从内存中扫描记录数据，而不是直接扫描推送记录库，以加快处理速度，减少机器负载
class CPushRecord  
{
public:
   int  bunit;             // 推送是由哪个BULink发起的，对ackflag='2'有效
   unsigned int recno;     // 原始推送记录号
   unsigned short destno;  
   unsigned short funcno;
   char ackflag;           // 确认状态编码 1/2 a/b-已推送未确认；
   time_t patime;          // 处理时间
   time_t valid_at;          // 在多久时间被确认才算有效，否则，就被抛弃，不再需要推送
   
public:
	CPushRecord();
   CPushRecord(const CPushRecord &pr);
	virtual ~CPushRecord();

};


typedef std::list<CDestStatus> VPUSHDEST;
typedef std::list<CPushRecord> VPUSHRECORD;


class CPushThread : public CWThread  
{
public:
   int         m_index;    // 当前连接的通讯平台编号
   CDRTPRouter *pRouter;    // 与其相关的通讯平台

private:
   CDBF        m_pdbf;
   int         m_pdbfdate; // 当前使用的推送记录库日期
   int         lastrecord;   // 当前处理的最后一个推送XDBF数据库记录号
   VPUSHDEST   vdeststatus;  // 目标状态表
   VPUSHRECORD vprecords;    // 与本连接相关的推送记录（需要确认的）

   char        pdata[MAXDATASIZE]; // 用于存放推送数据的缓存
   char        szMsg[256];   // 出错处理信息
   
public:
	CPushThread();
	virtual ~CPushThread();

private:
	bool ReadAckData();
	int PushDataInClient(CPushRecord *pPR, int pdlen=0);
	bool SetPushDbfRecord(unsigned int recno, char ackflag);
	int ReadPushRecord(CPushRecord *pData,int &routerid, char *packdata, int &pdlen);
	int Run();

};

#endif // !defined(AFX_PUSHTHREAD_H__255A119D_F398_422E_90BB_DFA47DF22B17__INCLUDED_)
