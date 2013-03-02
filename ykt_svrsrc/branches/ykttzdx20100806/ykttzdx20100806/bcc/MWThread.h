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
#define PRIORITIES   3     // ϵͳ֧�ֵ����ȼ�����


class CMWThread : public CWThread  
{
private:
   CBUListenThread m_BUListen; 
   CForwardThread m_ForwardThread;
   CDRTPRecvThread tRecvThreads[MAXROUTERS];
   CPushThread  tPushThreads[MAXROUTERS];
   
   RPACKQUEUE tRPackQueue[PRIORITIES];

public:
   unsigned int nNoVBUWarnDelay;    // �ڶ���ʱ���ڣ�û�п��л���ʵ�BU���Դ�������ǰ̨��ʾ���󷵻�
   bool bToWriteAppInfo;            // �Ƿ���Ҫ����һ��дAppInfo�����ݿ�Ķ���
   bool bRPQProcFIFO[PRIORITIES];   // ���������ȼ����еĴ���ģʽ�Ƿ�ΪFIFO
   int bumsgshowlevel;           // ���ڴ��ڵ��ڸ�ָ��ֵ��BULOG��Ϣ��ʾ��BCC������Ļ��
   unsigned int rptimeout;       // ����������й��˶�ã���û�б��������ų���ȴ�
   unsigned int freewait;        // �ڿ��л�BU�ر�æµ��ʱ�������ó�����ʱ�䣬�Ժ����
   //int nBULinks;               // ��Ч��
   CBULinkThread tBULinks[MAXBULINKS];

   int nRouters;               // DRTP Routers
   CDRTPRouter tRouters[MAXROUTERS]; 

   int nBUnits;      // ���Ƶ�BU������ֻ���ڱ�����ʱ�������ͼ����Ч
   char szBUProg[256];  // BU���г��������е�Ŀ¼�����������Ŀ¼
   char szBUPath[256];  // BU���е�Ŀ¼
   int iLastFreeBU;     // ��ǰ׼�����ҽӵ�BU���
#ifdef WIN32
   PROCESS_INFORMATION pi[MAXBULINKS];
#else
   pid_t pi[MAXBULINKS];
#endif

   int  m_forwardclear; // �������ļ���Чʱ��
   bool m_bToPush;   // ϵͳ�Ƿ�֧������
   int m_patime;     // �ظ����͵���ʱʱ�䣬�����
   int nPushRecs;    // �ڵ�ǰ����XDBF���ݿ��У����ж�����¼��
   CDBF m_pdbf;      // ��ǰ����XDBF���ݿ�
   int m_pdbfdate;   // ��ǰ����XDBF���ݿ����Ч����
   CMUTEX m_mutex;   // Ϊ�˶��̹߳��� (MWThread/BULinkThread)

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

extern CMWThread g_MWThread;   // һ������ʵ��

#endif // !defined(AFX_MWTHREAD_H__5E22896C_9AD2_407A_B185_F2276AC1C58F__INCLUDED_)
