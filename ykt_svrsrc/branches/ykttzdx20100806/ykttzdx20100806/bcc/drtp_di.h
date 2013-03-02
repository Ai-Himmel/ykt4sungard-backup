/********************************************************************
	created:	2003/09/25
	created:	25:9:2003   20:33
	filename: 	E:\linux\ksappsvr\drtp_di.h
	file path:	E:\linux\ksappsvr
	file base:	drtp_di
	file ext:	h
	author:		陈永华
	
	purpose:	为了处理新、旧通讯平台接口，采用统一的接口，只是内部完成过程
   根据版本不同而不同。
*********************************************************************/
#ifndef _DRTP_DI_
#define _DRTP_DI_

#include "comstru.h"
#include "tcp.h"
#include "mutex.h"

#define TCP_BLOCK_SIZE 1024

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)       
#endif

#ifndef NULL
#define NULL 0
#endif


void reverse(void *data,int len);

/* ****** Updated by CHENYH at 2003-9-25 22:41:41 ****** 
  对应推送消息模式，需要推送请求中，包括
  可发送路由编号irouter（在登记的时候记录的RECIEVEDATA->SourceNo）,
  目标端的nDest,目标登记的nFunctionNo
*/


bool DRTPInitialize(int nrouters=1);
void DRTPUninitialize();


class CDRTPClient
{
public:
	bool IsOpenning();
#define DRTPCLIENTID 660215
	int classdataid;

   // 函数名: Receive
   // 编程  : 陈永华 2004-3-17 15:05:05
   // 描述  : 通讯客户端等待接收请求后的应答数据
   // 返回  : int 
   /*
               <0 接收错误：
               -100: 收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 应该接收通讯数据头长度%d>实际长度%d!
               -99:  收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 通讯包头数据格式非法
               -98:  接收数据的缓冲长度(%d)不足，真正数据包长度为:(%d)，关闭本连接，重新与通讯平台建立连接!
               -90:  在收到系统包头后的限定时间(%u)里，收不到实际的应用数据包(实际收到%d<需要数据长度%u)

               -1: 没有收到数据，连接应该还可以使用，不用关闭，也可关闭重新连接处理
               其他<0: 
                  停止接收，本连接已经被关闭!;
                  通讯接口在等待接收数据时候出错%d-%s!
                  通讯接口在接收数据时候出错%d-%s!
                  通讯接口在等待接收数据时,通讯接口被对方关闭%d-%s!
               =0:   检查szMsg消息，往往是数据无法送达目标地址；或收到一个没有包体的应用数据包
               >0:   OK, 收到应答数据包，长度为%d
   */
   // 参数  : void *recvbuf      接收应用数据的缓冲
   // 参数  : int recvbufsize    缓冲区的大小
   // 参数  : char *szMsg        接收处理的消息
   // 参数  : int nMsgSize       消息缓冲区的大小
   // 参数  : unsigned int wtime 等待接收的超时时间（毫秒）
	int Receive(void *recvbuf,int &recvbufsize,char *szMsg,int nMsgSize=256,int wtime=1000);

   // 函数名: Send
   // 编程  : 陈永华 2004-3-17 15:06:47
   // 描述  : 客户端发送数据
   // 返回  : bool true 成功发送（但是不一定发送到目标应用端）
   // 参数  : H_DRTPCLI linkidx           客户端连接句柄  由DRTPCConnect返回
   // 参数  : unsigned short branchno     服务端的目标节点号
   // 参数  : unsigned short function     服务端的通讯功能号
   // 参数  : void *senddata              需要发送的数据
   // 参数  : int senddatalen             需要发送的数据长度
   // 参数  : char *szMsg                 发送处理时处理消息
   // 参数  : int nMsgSize                接收处理消息的缓冲区大小            
   // 参数  : bool bDesign                是否将请求数据发送到上次发送成功的目标点
	bool Send(unsigned short branchno,unsigned short function,void *senddata,int senddatalen,char *szMsg,int nMsgSize=256,bool bDesign=true);

   // 函数名: Close
   // 编程  : 陈永华 2004-3-17 15:07:36
   // 描述  : 关闭与通讯平台建立一个客户端连接
   // 返回  : bool 
	bool Close();

   // 函数名: Connect
   // 编程  : 陈永华 2004-3-17 15:07:59
   // 描述  : 与通讯平台建立一个客户端连接
   // 参数  : char *routerip     通讯平台的IP地址
   // 参数  : int port          通讯平台的端口号
   // 参数  : char *szMsg        连接处理的返回消息
   // 参数  : int nMsgSize=256   消息缓冲区的大小
	bool Connect(char *routerip,int port,char *szMsg,int nMsgSize=256);
	CDRTPClient();
	~CDRTPClient();
protected:
	
private:
#ifdef _DRTP_V4
   long handle;     // DRTP4使用的句柄
#else
	int sendpack(SYS_HEAD *pHead,void *senddata,int senddatalen);
   CTcpSocket m_socket;
   SYS_HEAD m_recvhead;  // 上次应答回来的数据头
#endif

   CMUTEX m_mutex;
};


class CDRTPServer
{
public:
	bool IsOpenning();

   /* ****** Updated by CHENYH at 2004-3-17 15:00:01 ****** 
   // 编程  : 陈永华 2003-9-29 22:57:39
   // 描述  : 在限定的时间里wtime(毫秒)，根据通讯平台协议，接收应用数据的头和具体数据内容
   // 返回  : int 
               <-1: 错误，需要关闭本连接，重新建立连接
                  -2000 linkidx为空
                  -300  通讯平台故障，发送5次心跳测试，都没有得到通讯平台的应答，重新连接!
                  -100  收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 应该接收通讯数据头长度%d>实际长度%d!
                  -99   接收数据包头不正确 - CRC-检查错误!(%X!=%X)  ???
                  -98   接收数据的缓冲长度(%d)不足，真正数据包长度为:(%d)，关闭本连接，重新与通讯平台建立连接!
                        往往有如下原因造成的：         
                           接收缓冲长度不足；（属于程序错）
                           接收的请求数据不正确；
                           连接中的接收缓冲中数据不同步，需要reset本通讯平台连接；
                  -90   在收到系统包头后的限定时间(%u)里，收不到实际的应用数据包(实际收到%d<需要数据长度%u)
                  其他  属于通讯底层返回的错误
                  -11   可能被对方关闭 ???
               =-1 等待时间里，没有收到数据
               >=0 收到数据包，返回的是实际数据包recvbuf的长度
   // 参数  : SYS_HEAD *pHead  OUT, 与接收数据相关的包头，也可认为属于接收数据的句柄APPHANDLE
   // 参数  : void *recvbuf  OUT, 存放接收到的应用数据缓冲
   // 参数  : int recvbufsize IN, 缓冲长度尺寸
   // 参数  : char *szMsg  OUT, 返回的接收处理消息 NULL不返回
   // 参数  : int nMsgSize IN, =0不返回消息，>0 返回信息的最大长度
   // 参数  : unsigned int wtime IN, 等待接收的等待时间 (毫秒计) =0 一直等待，直到连接出错或接收到正式数据
   */
	int Receive(SYS_HEAD *pHead,void *recvbuf,int &recvbufsize,char *szMsg,int nMsgSize=256,int wtime=5000);

   // 函数名: Send
   // 编程  : 陈永华 2004-3-17 15:00:38
   // 描述  : 
   // 返回  : bool 
   // 参数  : SYS_HEAD *pHead
   // 参数  : void *senddata
   // 参数  : int senddatalen
   // 参数  : char *szMsg
   // 参数  : int nMsgSize=256
	bool Send(SYS_HEAD *pHead,void *senddata,int senddatalen,char *szMsg,int nMsgSize=256);

   // 函数名: Close
   // 编程  : 陈永华 2004-3-17 15:01:08
   // 描述  : 关闭应用服务端的连接
   // 返回  : bool 
	bool Close();

   // 函数名: Connect
   // 编程  : 陈永华 2004-3-17 15:01:39
   // 描述  : 与通讯平台建立一个应用服务端连接
   // 返回  : bool               连接是否成功
   // 参数  : char *routerip     通讯平台的IP地址
   // 参数  : int port          通讯平台的端口号
   // 参数  : int funcount       注册功能的个数
   // 参数  : unsigned short *functions 功能列表
   // 参数  : char *szMsg        连接处理消息返回
   // 参数  : int nMsgSize=256   消息缓冲区的大小
	bool Connect(char *routerip,int port,int funcount,unsigned short *functions,char *szMsg,int nMsgSize=256);
	CDRTPServer();
	~CDRTPServer();

#define DRTPSERVERID  730428
   int classdataid;  // 本类的ID,判断是否属于本类的数据结构

protected:
	
private:
#ifdef _DRTP_V4
   long handle;   // DRTP4使用的句柄
#else
   int sendpack(SYS_HEAD *pHead,void *data,int datalen);

   unsigned short m_mainfuncno;  // 注册的主功能号
   int m_recvnullcounts;  // 在约定时间里，没有接收到请求数据的次数
   CTcpSocket m_socket;
#endif

   CMUTEX m_mutex;
};


#endif
