// MWThread.h: interface for the CMWThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MWTHREAD_H__5E22896C_9AD2_407A_B185_F2276AC1C58F__INCLUDED_)
#define AFX_MWTHREAD_H__5E22896C_9AD2_407A_B185_F2276AC1C58F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sysgvars.h"
#include "comstru.h"
#include "WThread.h"
#include "dbf.h"
#include "ForwardThread.h"
#include "DRTPRecvThread.h"
#include "bulinkthread.h"
#include "bulistenthread.h"
#include "PushThread.h"

#define MAXBULINKS   50
#define MAXROUTERS   10
#define PRIORITIES   3     // 系统支持的优先级别数


class CMWThread : public CWThread  
{
private:
   CBUListenThread m_BUListen; 
   CForwardThread m_ForwardThread;
   CDRTPRecvThread tRecvThreads[MAXROUTERS];
   CPushThread  tPushThreads[MAXROUTERS];
   
   RPACKQUEUE tRPackQueue[PRIORITIES];

public:
   unsigned int nNoVBUWarnDelay;    // 在多少时间内，没有空闲或合适的BU可以处理，则向前台提示错误返回
   bool bToWriteAppInfo;            // 是否需要发起一个写AppInfo到数据库的动作
   bool bRPQProcFIFO[PRIORITIES];   // 各请求优先级队列的处理模式是否为FIFO
   int bumsgshowlevel;           // 对于大于等于该指定值的BULOG信息显示到BCC控制屏幕上
   unsigned int rptimeout;       // 在请求队列中挂了多久，还没有被处理，则排除其等待
   unsigned int freewait;        // 在空闲或BU特别忙碌的时候主控让出来的时间，以毫秒计
   //int nBULinks;               // 有效的
   CBULinkThread tBULinks[MAXBULINKS];

   int nRouters;               // DRTP Routers
   CDRTPRouter tRouters[MAXROUTERS]; 

   int nBUnits;      // 控制的BU个数，只是在本机的时候启动和监控有效
   char szBUProg[256];  // BU运行程序，其运行的目录，就是其带的目录
   char szBUPath[256];  // BU运行的目录
   int iLastFreeBU;     // 当前准备被挂接的BU编号
#ifdef WIN32
   PROCESS_INFORMATION pi[MAXBULINKS];
#else
   pid_t pi[MAXBULINKS];
#endif

   int  m_forwardclear; // 批数据文件有效时间
   bool m_bToPush;   // 系统是否支持推送
   int m_patime;     // 重复推送的延时时间，以秒计
   int nPushRecs;    // 在当前推送XDBF数据库中，共有多数记录数
   CDBF m_pdbf;      // 当前推送XDBF数据库
   int m_pdbfdate;   // 当前推送XDBF数据库的有效日期
   CMUTEX m_mutex;   // 为了多线程共享 (MWThread/BULinkThread)

private:
	int NoValidBUReturn(CReqPack *prp,int retcode,char *retmsg);
	bool CheckPushDBF();
	int RemoveTimeoutRPack();
	int FindValidBULink(unsigned int *retcode,char *retmsg);
	bool GetRPackFromQueue(RPACKQUEUE *pRQ,CReqPack &rpack,bool bFIFO=false);
	bool PutRPackToQueue(CReqPack *rpack, int iPriority);
	int GetPriority(ST_PACKHEAD *phead);
   

public:
	int CheckStartupBU();
	int RemoveForwardFiles(char *ksfile,int timeout=0);
	int AddPushRecord(int iBUnit,unsigned short sno,unsigned short dno,unsigned short fno,char pushmode,int acktime,void *pdata,int pdlen);
	int ListRPQStatus(char *outfile=NULL,int wmode=0);
	int ListRouterStatus(char *outfile=NULL,int wmode=0);
	int ListBULinkStatus(char *outfile=NULL,int wmode=0);
	unsigned short GetForwardData(ST_PACKHEAD *phead, int offset, void *buf, char *eMsg);
	unsigned short GetForwardData(char *queuename,int offset,void *buf,char *eMsg);
	int GetSuspendRPackCount();
	CBULinkThread * FindFreeBULink();
	bool Reset();
	bool HaveAClientRequest(RECEIVEDATA *recvdata,char *rtnmsg);
	int Run();
	CMWThread();
	virtual ~CMWThread();

};

extern CMWThread g_MWThread;   // 一个运行实例

#endif // !defined(AFX_MWTHREAD_H__5E22896C_9AD2_407A_B185_F2276AC1C58F__INCLUDED_)
