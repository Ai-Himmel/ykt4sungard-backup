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
   BULS_NOTSTART=-1,   // 本线程尚未启动，需要启动然后才能正常工作
   BULS_NOTREADY=0,    // BU 尚未连接上来
   BULS_TOLINK,        // 物理连接成功，但是还需要交换连接初始化
   BULS_LINKOK,        // 与BU连接上来，但还没有要求
   BULS_WAITREQ,       // BU已经发出等待接收请求处理
   BULS_REQPROC        // 与之连接的BU正在处理请求，在提交了请求后，没有收到BU发出等待REQPACK的请求
};


class CBULinkThread : public CWThread  
{
public:
   int   iID;             // BU Link ID
   char  szBUGroupID[12];  // 业务处理单元组别
   int   iBUVersion;       // BU的版本号
   CTcpSocket linksock;    // BU Link Socket
   int   iStep;           // 目前所处的状态
   time_t iLinkTime;      // 连接时间点  用time(NULL)得到的秒时间点
   unsigned int iLastSendTime;  // 最后提交请求包的时间点 GetTickCount() 得到的毫秒时间点

   // 为了标注本BU错误状态
   int iErrorCode;         // BU当前的错误状态码 （如目前该BU连接的后台出现问题了）
   char szErrorMsg[256];  // BU当前的错误状态信息

private:
   CMUTEX m_mutex;         // 由于g_MWThread线程中需要SendRequest(...)，可能与本线程有冲突
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // 包括起始的消息头
   short bu1;             // BUnit 1
   unsigned char iBURFrame;   // 这次BU需要在MT_GETREQ时候的iGRFrame
   char LastRData[MAXMSG];  // 上次发送的请求包：AP_REQUEST + encodepackdata...
   unsigned int iLastReqType;  // 上次或本次调用的功能号
   ST_PACKHEAD head;       // 当前使用的CPACK的头包括parmbit等
   // 用于记录应答数据的发送：
   bool bHaveSent;                  // 是否已经调用AnswerData或其他类似功能
	unsigned short SourceNo;         // 通讯平台的编号
	SYS_HEAD syshead;                // 通讯平台使用的用于收发数据，业务处理部分不要关心内部数据，只要复制即可
   char iAnswerMode;                // 当前应答模式 见 AM_xxxx
   char iDefaultAM;                 // 本类BU缺省应答模式
   
   unsigned int iqueueno;  // 内部用于生成唯一队列名的序号
   int ad_ksfseg;          // 目前存放到文件中的数据段偏移位置

   short ad_dklen; // 当前保留在数据缓存的数据长度
   char rowedata[MAXDATASIZE+MAXDATASIZE];  // 防止Encode的时候内存超界，所以需要两倍的缓存
   unsigned int maxrows;    // 前端或系统指定的每次返回最大记录数

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

   // 函数名: CBULinkThread::SendMsg
   // 编程  : 陈永华 2004-2-15 22:28:06
   // 描述  : 以MSG格式发送消息数据给调度中心
   // 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
   // 参数  : short msgtype ：IN 发送的消息类型
   // 参数  : unsigned short msglen ：IN 消息体数据长度
   // 参数  : void *MSGBUF ： IN 消息数据缓存
   int SendMsg(short msgtype, unsigned short msglen, void *MSGBUF);

   // 函数名: CBULinkThread::RecvMsg
   // 编程  : 陈永华 2004-2-15 22:22:51
   // 描述  : 按照MSG协议接收数据
   // 返回  : int >0:接收到正常数据包；0:超时；-1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；-3:在接收数据的时候，出错而被关闭
   // 参数  : int timeout
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
