// bulinkthread.h: interface for the CBULinkThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULINKTHREAD_H__4A51712C_3621_45D8_BBF7_646C960BF684__INCLUDED_)
#define AFX_BULINKTHREAD_H__4A51712C_3621_45D8_BBF7_646C960BF684__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "tcp.h"
#include "cpack.h"
#include "comstru.h"
#include "mutex.h"

enum BULSTEP
{
   BULS_NOTSTART=-1,   // ���߳���δ��������Ҫ����Ȼ�������������
   BULS_NOTREADY=0,    // BU ��δ��������
   BULS_TOLINK,        // �������ӳɹ������ǻ���Ҫ�������ӳ�ʼ��
   BULS_LINKOK,        // ��BU��������������û��Ҫ��
   BULS_WAITREQ,       // BU�Ѿ������ȴ�����������
   BULS_REQPROC        // ��֮���ӵ�BU���ڴ����������ύ�������û���յ�BU�����ȴ�REQPACK������
};


class CBULinkThread : public CWThread  
{
public:
   int   iID;             // BU Link ID
   char  szBUGroupID[12];  // ҵ����Ԫ���
   int   iBUVersion;       // BU�İ汾��
   CTcpSocket linksock;    // BU Link Socket
   int   iStep;           // Ŀǰ������״̬
   time_t iLinkTime;      // ����ʱ���  ��time(NULL)�õ�����ʱ���
   unsigned int iLastSendTime;  // ����ύ�������ʱ��� GetTickCount() �õ��ĺ���ʱ���

   // Ϊ�˱�ע��BU����״̬
   int iErrorCode;         // BU��ǰ�Ĵ���״̬�� ����Ŀǰ��BU���ӵĺ�̨���������ˣ�
   char szErrorMsg[256];  // BU��ǰ�Ĵ���״̬��Ϣ

private:
   CMUTEX m_mutex;         // ����g_MWThread�߳�����ҪSendRequest(...)�������뱾�߳��г�ͻ
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // ������ʼ����Ϣͷ
   short bu1;             // BUnit 1
   unsigned char iBURFrame;   // ���BU��Ҫ��MT_GETREQʱ���iGRFrame
   char LastRData[MAXMSG];  // �ϴη��͵��������AP_REQUEST + encodepackdata...
   unsigned int iLastReqType;  // �ϴλ򱾴ε��õĹ��ܺ�
   ST_PACKHEAD head;       // ��ǰʹ�õ�CPACK��ͷ����parmbit��
   // ���ڼ�¼Ӧ�����ݵķ��ͣ�
   bool bHaveSent;                  // �Ƿ��Ѿ�����AnswerData���������ƹ���
	unsigned short SourceNo;         // ͨѶƽ̨�ı��
	SYS_HEAD syshead;                // ͨѶƽ̨ʹ�õ������շ����ݣ�ҵ�����ֲ�Ҫ�����ڲ����ݣ�ֻҪ���Ƽ���
   char iAnswerMode;                // ��ǰӦ��ģʽ �� AM_xxxx
   char iDefaultAM;                 // ����BUȱʡӦ��ģʽ
   
   unsigned int iqueueno;  // �ڲ���������Ψһ�����������
   int ad_ksfseg;          // Ŀǰ��ŵ��ļ��е����ݶ�ƫ��λ��

   short ad_dklen; // ��ǰ���������ݻ�������ݳ���
   char rowedata[MAXDATASIZE+MAXDATASIZE];  // ��ֹEncode��ʱ���ڴ泬�磬������Ҫ�����Ļ���
   unsigned int maxrows;    // ǰ�˻�ϵͳָ����ÿ�η�������¼��

private:
	bool ResetAnswerData();
	bool SetBUError(unsigned short len,RP_SETERROR *prp,char *eMsg);
	bool BULogOut(unsigned short len,char *rdata,char *eMsg);
	void SetAMode(char *pAMode);
	bool DataDone(unsigned short len, char *rdata, char *eMsg);
	int ResendRequestData();
	int GetReq(unsigned short len,char *rdata,char *szmsg);
	bool PutRow(unsigned short len,char *rdata,char *eMsg);
	bool PushData(unsigned short len,char *rdata,char *eMsg);
	bool AnswerDataEx(unsigned short len,char *rdata,char *eMsg);
	bool AnswerData(unsigned short len,char *rdata,char *eMsg);
	int FlushToKSF(unsigned char nextflag=1);
	int PutRowData(unsigned short len,char *prowdata);
	void SetCol(void *parmbits);
	void LastRequestOver(RP_REQUEST *prp);
	bool AnswerLinkBegin(MSGBUF *pmb);
	int Recv_Processing();
	MSGBUF * GetRecvMsg();

   // ������: CBULinkThread::SendMsg
   // ���  : ������ 2004-2-15 22:28:06
   // ����  : ��MSG��ʽ������Ϣ���ݸ���������
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : short msgtype ��IN ���͵���Ϣ����
   // ����  : unsigned short msglen ��IN ��Ϣ�����ݳ���
   // ����  : void *MSGBUF �� IN ��Ϣ���ݻ���
   int SendMsg(short msgtype, unsigned short msglen, void *MSGBUF);

   // ������: CBULinkThread::RecvMsg
   // ���  : ������ 2004-2-15 22:22:51
   // ����  : ����MSGЭ���������
   // ����  : int >0:���յ��������ݰ���0:��ʱ��-1:���Է������رգ�-10:�����nDesignedSize<=0��-11:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-2:��Ϊ��·��������رգ�-3:�ڽ������ݵ�ʱ�򣬳�������ر�
   // ����  : int timeout
	int RecvMsg(int timeout);
	bool LinkWithBU();
	int Run();
   
public:
	int ToCancelProcess();
	int ExtCallReturn(int dlen,void *rtndata);
	char * GetRunTimeInformation(char *szbuf);
	int SendRequestData(RECEIVEDATA *rdata,unsigned int rtime);
	bool IsWaitReqStep();
	void ToLink();
	bool IsFree();
	CBULinkThread();
	virtual ~CBULinkThread();

};

#endif // !defined(AFX_BULINKTHREAD_H__4A51712C_3621_45D8_BBF7_646C960BF684__INCLUDED_)
