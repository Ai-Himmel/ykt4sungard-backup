// DRTPRecvThread.h: interface for the CDRTPRecvThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRTPRECVTHREAD_H__13E13F1A_5BB5_40C9_BA96_49CCBEFDD856__INCLUDED_)
#define AFX_DRTPRECVTHREAD_H__13E13F1A_5BB5_40C9_BA96_49CCBEFDD856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "drtp_di.h"
#include "cpack.h"

class CDRTPRouter  
{
public:
   int               iID;           // DRTPRouter ID  ��0��ʼ
	char              IP[32];        // ROUTER��IP��ַ
	unsigned int      Port;          // ROUTER�������˿�
   unsigned short    tSFuncNos[2];  // ��Ϊ����˵�ע��ͨѶ���ܺ���

   CDRTPServer       hSvr;
   time_t            s_connect_time; // ���ӽ���ʱ��
   time_t            s_lasttime;   // �ϴη��ͳɹ���ʱ���
	unsigned int      s_connect_counts; // ���Ӵ���
	unsigned int      s_recv_count;
	unsigned int	   s_recv_len;
	unsigned int	   s_send_count;
	unsigned int	   s_send_len; 
   

   CDRTPClient       hCli;
   time_t            c_connect_time; // ���ӽ���ʱ��
   time_t            c_lasttime;   // �ϴη��ͳɹ���ʱ���
	unsigned int      c_connect_counts; // ���Ӵ���
	unsigned int      c_recv_count;
	unsigned int	   c_recv_len;
	unsigned int	   c_send_count;
	unsigned int	   c_send_len; 

public:
	bool CliToSendData(unsigned short branchno,unsigned short function,void *senddata,int datalen,char *rtnmsg);
	int CliToReceive(void *recvbuf,int &recvbufsize,char *rtnmsg,int wtime=1000);
	void CliToClose();
	bool CliToConnect(char *rtnmsg);
	char * GetRunTimeInformation(char *szbuf);
	int SvrToReceive(RECEIVEDATA *recvdata,char *rtnmsg,int wtimeout);
	void SvrToClose();
	bool SvrToConnect(char *rtnmsg);
	bool SvrToSendData(SYS_HEAD *head, ST_CPACK *pack, ST_PACK *array, char *rtnmsg);
	bool SvrToSendData(RECEIVEDATA *recvdata, char *rtnmsg);
	CDRTPRouter();
	virtual ~CDRTPRouter();

};

enum DSRTSTEPS
{
   DSRT_NOTSTART = -1,
   DSRT_RUNNING = 0
};


class CDRTPRecvThread : public CWThread  
{
public:
   int iStep;
   CDRTPRouter *pRouter;    // ��Ӧ��DRTPRouter
private:
	int Run();

public:
	CDRTPRecvThread();
	virtual ~CDRTPRecvThread();

};

#endif // !defined(AFX_DRTPRECVTHREAD_H__13E13F1A_5BB5_40C9_BA96_49CCBEFDD856__INCLUDED_)
