// SvrLink.h: interface for the CSvrLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
#define AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_

#include "tcp.h"
#include "cpack.h"
#include "bupub.h"
#include "comstru.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
   int sno;  // �״ε���ExtCall������souceno
   int dno;  // �״ε���ExtCall������destno
   int fno;  // �״ε���ExtCall������funcno
   int bno;  // �״ε���ExtCall������batchno
   ST_PACKHEAD ahead;  // Ӧ�𷵻ص�ͷ���ݱ�����
} ST_PDKEEP;


class CSvrLink  
{
public:
   int  bccBFuncNo;        // ���ӵ�BCCע���ͨѶ���ܺ�
   int  bccID;             // ���ӵ�BCC���>0
   
   bool bExit;             // �Ƿ�Ҫ�˳�...
   ST_PACKHEAD head;       // ��ǰʹ�õ�CPACK��ͷ����parmbit��
   ST_PDKEEP xcdata;       // ���ڱ���ExtCall��ExtCallNext��������
private:
   unsigned char iGRFrame;     // ֡��
   unsigned int iLastReqType;  // �ϴλ򱾴ε��õĹ��ܺ�
   int iLastRetCode;  // �ϴδ������ĳɹ���ʧ�ܣ�����֪ͨBCC
   char eMsg[256];
   CTcpSocket linksock;    // ��������ĵ�TCPIP����
   short svr_hs1;          // �������ģ�short��1�������ж��Ƿ��뱾ҵ��Ԫ������������ͬ
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // ������ʼ����Ϣͷ
   char iAnswerMode;       // ��ǰ��Ч��Ӧ��ģʽ����AM_AUTO / AM_CONFIRM
   TRUSERID ruserid;       // �������ύ�Ŀͻ���ID
   
public:
	void CopyAnswerHead(ST_PACKHEAD *phead);
	bool CheckLink();
	int ResetAnswerData();
	int SetAnswerTimeout(unsigned int atimeout);
	int SetBUError(int errcode,char *szErrMsg);
	int SetMaxRow(int maxrows);
	void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount);
	int BCCLogOut(char logtype,int logid,int textlen,char *text,int datalen=0,void *data=NULL);
	int SetAnswerMode(char iAnswerMode);
	bool CheckProcCancel();
	int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays);
	int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays);
	int PushRowEx(TPUSHDEST *pushdests,int pdcount,ST_PACK *pack,char pushmode,int batchno,int acktime);
	int PushRow(int sourceno,int destno,int funcno,ST_PACK *pack,char pushmode,int batchno,int acktime);
	bool LinkOK();
	int Err_Deal(char *emsg, int retcode);
	int PutRow(TRUSERID *handle,ST_PACK *pdata,int retcode,char *rtnMsg);
	int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime);
	int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime);
	int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg);
	int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg,unsigned char nextflag);
	int PutRowData(ST_PACK *pdata);
	int SetCol(TRUSERID *puserid,unsigned char *parmbits);
	int Processing(ST_BUNIT *pBUnit);
	void Close();
	int ToLink(ST_BUNIT *pBUnit);
	CSvrLink();
	virtual ~CSvrLink();

private:
	int DataDone(int retcode,char *szMsg);
	int CallBPFunction(MSGBUF *pmb);

// ������: CSvrLink::SendMsg
// ���  : ������ 2004-2-10 21:08:11
// ����  : ��MSG��ʽ������Ϣ���ݸ���������
// ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
// ����  : short msgtype ��IN ���͵���Ϣ����
// ����  : unsigned short msglen ��IN ��Ϣ�����ݳ���
// ����  : void *msgbuf �� IN ��Ϣ���ݻ���
	int SendMsg(short msgtype,unsigned short msglen=0,void *msgbuf=NULL);

   // ������: CSvrLink::RecvMsg
   // ���  : ������ 2004-2-10 22:40:18
   // ����  : ����MSGЭ���������
   // ����  : int -1:���Է������رգ�-10:�����nDesignedSize<=0��-11:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-2:��Ϊ��·��������رգ�0:��ʱ��-3:�ڽ������ݵ�ʱ�򣬳�������ر�
   // ����  : int timeout
	int RecvMsg(int timeout=3000);

	MSGBUF * GetRecvMsg();


};

#endif // !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
