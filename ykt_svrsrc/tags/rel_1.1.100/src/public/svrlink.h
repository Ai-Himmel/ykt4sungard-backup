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
   int sno;  // 首次调用ExtCall保留的souceno
   int dno;  // 首次调用ExtCall保留的destno
   int fno;  // 首次调用ExtCall保留的funcno
   int bno;  // 首次调用ExtCall保留的batchno
   ST_PACKHEAD ahead;  // 应答返回的头数据保留用
} ST_PDKEEP;


class CSvrLink  
{
public:
   int  bccBFuncNo;        // 连接的BCC注册的通讯功能号
   int  bccID;             // 连接的BCC编号>0
   
   bool bExit;             // 是否要退出...
   ST_PACKHEAD head;       // 当前使用的CPACK的头包括parmbit等
   ST_PDKEEP xcdata;       // 用于保留ExtCall和ExtCallNext的数据用
private:
   unsigned char iGRFrame;     // 帧号
   unsigned int iLastReqType;  // 上次或本次调用的功能号
   int iLastRetCode;  // 上次处理结果的成功或失败，用于通知BCC
   char eMsg[256];
   CTcpSocket linksock;    // 与调度中心的TCPIP连接
   short svr_hs1;          // 调度中心（short）1，用于判断是否与本业务单元主机的字序相同
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // 包括起始的消息头
   char iAnswerMode;       // 当前有效的应答模式，见AM_AUTO / AM_CONFIRM
   TRUSERID ruserid;       // 本请求提交的客户端ID
   
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

// 函数名: CSvrLink::SendMsg
// 编程  : 陈永华 2004-2-10 21:08:11
// 描述  : 以MSG格式发送消息数据给调度中心
// 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
// 参数  : short msgtype ：IN 发送的消息类型
// 参数  : unsigned short msglen ：IN 消息体数据长度
// 参数  : void *msgbuf ： IN 消息数据缓存
	int SendMsg(short msgtype,unsigned short msglen=0,void *msgbuf=NULL);

   // 函数名: CSvrLink::RecvMsg
   // 编程  : 陈永华 2004-2-10 22:40:18
   // 描述  : 按照MSG协议接收数据
   // 返回  : int -1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；0:超时；-3:在接收数据的时候，出错而被关闭
   // 参数  : int timeout
	int RecvMsg(int timeout=3000);

	MSGBUF * GetRecvMsg();


};

#endif // !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
