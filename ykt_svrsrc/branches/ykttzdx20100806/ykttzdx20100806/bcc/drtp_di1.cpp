/********************************************************************
	created:	2003/09/27
	created:	27:9:2003   15:33
	filename: 	E:\linux\ksappsvr\drtp_di1.cpp
	file path:	E:\linux\ksappsvr
	file base:	drtp_di1
	file ext:	cpp
	author:		陈永华
	
	purpose:	兼容原来的通讯平台版本的接口，且与集中交易兼容的版本
            20040420: 修改bByteReverse＝true时候，对CRC计算和判断的错误
*********************************************************************/
#include "stdafx.h"
#include "comstru.h"
#include "mutex.h"
#include "tcp.h"

/* ****** Updated by CHENYH at 2003-10-27 16:41:00 ****** 
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ipc.h>
#include <pthread.h>
*/

#include "drtp_di.h"

bool bByteReverse = false;

enum DRTPERRORS 
{
};

const char *szDRTPErrors[]=
{
   "没有足够的资源创建连接!\tNo enough resource to build connection!",
   "输入的连接句柄为空!\tInput link handle is null!",
   "没有需要注册的功能号，不能建立服务连接!",
   "通讯发送数据太长，发送失败!",
   ""
};

void CopyString(const char *source,char *dest,int destsize)
{
   int i;
   if (dest==NULL||destsize<=1||source==NULL)
      return;
   for (i=0;i<destsize-1;i++)
   {
      if (source[i]=='\0') break;
      dest[i]=source[i];
   }
   dest[i]='\0';
}

void reverse(void *data,int len)
{
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;
   
   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
   }
}

unsigned int CRC(void *pData, long DataLen)
{
	unsigned short acc = 0, i;
	unsigned char* Data = (unsigned char*) pData;
	while(DataLen--)
	{
		acc = acc ^ (*Data++ << 8);
		for(i = 0; i++ < 8; )
			if(acc & 0x8000)
				acc = (acc << 1) ^ 0x1021;
			else
				acc <<= 1;
	}

	// Swap High and Low byte
	i = ( (unsigned short) ( ((unsigned char)acc) << 8) ) | ((unsigned short)(acc >> 8));

	return i;
}

void ReverseSysHead(SYS_HEAD *phead)
{
   int i;
   reverse(&(phead->Function),sizeof(phead->Function));
   reverse(&(phead->DestNo),sizeof(phead->DestNo));
   reverse(&(phead->UserDataRealSize),sizeof(phead->UserDataRealSize));
   reverse(&(phead->UserDataSize),sizeof(phead->UserDataSize));
   reverse(&(phead->LastConnectTime),sizeof(phead->LastConnectTime));
   for (i=0;i<MAXROUTERCOUNT;i++)
   {
      reverse(phead->RouterIn+i,sizeof(phead->RouterIn[0]));
      reverse(phead->RouterOut+i,sizeof(phead->RouterOut[0]));
   }
   // reverse(&(phead->CRC),sizeof(phead->CRC));  这一般要在此后才赋值
}


// 函数名: DRTPInitialize
// 编程  : 陈永华 2003-9-27 15:53:46
// 描述  : 通讯平台的初始化
// 返回  : bool 
// 参数  : int nrouters
bool DRTPInitialize(int nrouters)
{
   bByteReverse = (htons(1)==1);
   return(true);
}


// 函数名: DRTPUninitialize
// 编程  : 陈永华 2003-9-27 16:02:33
// 描述  : 结束通讯平台接口的使用
// 返回  : void 
void DRTPUninitialize()
{
}

CDRTPClient::CDRTPClient()
{
   classdataid = DRTPCLIENTID;
}

CDRTPClient::~CDRTPClient()
{
   Close();
}


bool CDRTPClient::Connect(char *routerip, int port, char *szMsg, int nMsgSize)
{
   int trys;
   char buf[1024];
   CPMUTEX amutex(&m_mutex);
   for (trys=0;trys<3;trys++)
   {
      if (m_socket.ConnectTcp(routerip,(short)port))
         break;
   }
   if (trys>=3)
   {
      sprintf(buf,"不能与通讯平台服务器<%s> 端口<%d>建立连接!",routerip,port);
      CopyString(buf,szMsg,nMsgSize);
      m_socket.Close();
      return(false);
   }
   sprintf(buf,"与通讯平台服务器<%s> 端口<%d>建立连接!",routerip,port);
   CopyString(buf,szMsg,nMsgSize);
   return(true);
}

bool CDRTPClient::Close()
{
//   CPMUTEX amutex(&m_mutex);
   m_socket.Close();
   return(true);
}

bool CDRTPClient::Send(unsigned short branchno, unsigned short function, void *senddata, int senddatalen, char *szMsg, int nMsgSize, bool bDesign)
{
   SYS_HEAD head;
   int rtn;
   char buf[1024];

   CPMUTEX amutex(&m_mutex);
   memset(&head,0,sizeof(SYS_HEAD));
   if (bDesign && (m_recvhead.MessageType==6))
   {
      memcpy(&head,&m_recvhead,sizeof(head));
      head.RouterDesignate = 1;
   }
   head.Ver = 2;
   head.CompressFlag = 0;
   head.DestNo = branchno;
   head.Function = function;
   head.FunctionPriority = 2;
   head.MessageType = 5;
   head.UserDataRealSize = head.UserDataSize = senddatalen;
   rtn = sendpack(&head,senddata,senddatalen);
   if (rtn<=0)
   {
      CopyString("数据发送失败，本连接已经被关闭!",szMsg,nMsgSize);
      return(false);
   }
   else
   {
      sprintf(buf,"数据发送成功，实际长度:%d",rtn);
      CopyString(buf,szMsg,nMsgSize);
      return(true);
   }
}


// 函数名: CDRTPClient::Receive
// 编程  : 陈永华 2003-9-30 15:34:15
// 描述  : 通讯客户端等待接收请求后的应答数据
// 返回  : int 
/*
            <0 接收错误：
            -100: 收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 应该接收通讯数据头长度%d>实际长度%d!
            -99:  收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 通讯包头数据格式非法
            -98:  接收数据的缓冲长度(%d)不足，真正数据包长度为:(%d)，关闭本连接，重新与通讯平台建立连接!
            -90:  在收到系统包头后的限定时间(%u)里，收不到实际的应用数据包(实际收到%d<需要数据长度%u)

            其他<0: 
               停止接收，本连接已经被关闭!;
               通讯接口在等待接收数据时候出错%d-%s!
               通讯接口在接收数据时候出错%d-%s!
               通讯接口在等待接收数据时,通讯接口被对方关闭%d-%s!


            =0:   检查szMsg消息，往往是数据无法送达目标地址；或收到一个没有包体的应用数据包
            >0:   OK, 收到应答数据包，长度为%d
*/
// 参数  : void *recvbuf
// 参数  : int recvbufsize
// 参数  : char *szMsg
// 参数  : int nMsgSize
// 参数  : int wtime
int CDRTPClient::Receive(void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
   int rtn;
   char buf[1024];
   unsigned int crc,crc1;
   SYS_HEAD *phead;
   char *pb;
   if (m_socket.IsFree())
   {
      CopyString("停止接收，本连接已经被关闭!",szMsg,nMsgSize);
      return(-1);
   }


   phead = (SYS_HEAD *)buf;
   memset(recvbuf,0,recvbufsize);
   while (1)
   {
      rtn = m_socket.Recv((char *)phead,sizeof(SYS_HEAD),wtime);
      if (rtn<=0)
      {
         // =0: 没有数据；<0:通讯端口有问题了，需要重新连接
         recvbufsize = 0;
         if (rtn==0)
         {
            CopyString("在指定的时间里，没有收到数据！",szMsg,nMsgSize);
         }
         else
         {
            CopyString("本连接出错，系统自动关闭了连接!",szMsg,nMsgSize);
         }
         return(rtn); 
      }
      if (rtn<(int)sizeof(SYS_HEAD))
      {
         // 收到数据段不足，应该是同步问题，还是关闭了这个连接端口
         sprintf(buf,"收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 应该接收通讯数据头长度%d>实际长度%d!",
            sizeof(SYS_HEAD),rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(-100);
      }
      // 是否通过检查CRC来判断是否为正确的SYS_HEAD?
      crc = phead->CRC;
      phead->CRC = 0;
      crc1 = CRC(phead,sizeof(SYS_HEAD));
      if (bByteReverse)
      {
         reverse(&crc,sizeof(crc));
      }
      if (crc1!=crc || phead->Ver!=2)
      {
         sprintf(buf,"收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 通讯包头数据格式非法");
         CopyString(buf,szMsg,nMsgSize);
         return(-99);
      }
      phead->CRC = crc;
      if (bByteReverse)
      {
         // 属于非x86类CPU: 需要转换为本机可辨认的格式 big-endian 低地址存高位字节
         ReverseSysHead(phead);
      }
      if (recvbufsize<phead->UserDataSize)
      {
         // 属于接收缓冲不够，只有关闭本连接，清除连接中的数据，重新连接通讯平台
         // 往往有如下原因造成的：
         /*
         1. 接收缓冲长度不足；（属于程序错）
         2. 接收的请求数据不正确；
         3. 连接中的接收缓冲中数据不同步，需要reset本通讯平台连接；
         */
         sprintf(buf,"接收数据的缓冲长度(%d)不足，真正数据包长度为:(%d)，关闭本连接，重新与通讯平台建立连接!",
            recvbufsize,phead->UserDataSize);
         CopyString(buf,szMsg,nMsgSize);
         return(-98);
      }
      if (phead->UserDataSize<=0)
      {
         // 应该属于内部交换数据：不属于应用数据
         rtn = 0;
      }
      else
      {
         rtn = m_socket.Recv((char *)recvbuf,phead->UserDataSize,1000); // 要求在1秒钟内接收到后续包数据
         if (rtn<0)
         {
            return(rtn);
         }
         else if (rtn!=phead->UserDataSize)
         {
            // 通讯可能有问题，还是关闭本连接算了，重新与通讯平台连接吧
            sprintf(buf,"在收到系统包头后的限定时间(%u)里，收不到实际的应用数据包(实际收到%d<需要数据长度%u)",
               wtime,rtn,phead->UserDataSize);
            CopyString(buf,szMsg,nMsgSize);
            return(-90);
         }
      }
      switch (phead->MessageType)
      {
      case 10:
         phead->MessageType = 11;
         phead->UserDataRealSize = phead->UserDataSize = 0;
         sendpack(phead,NULL,0);
         break;
      case 5:  // 不应该为这个数
      case 6:  // 应该为6  2003-10-13 added
         recvbufsize = rtn;
         memcpy(&m_recvhead,phead,sizeof(SYS_HEAD));
         sprintf(buf,"收到应答数据包，长度为%d",rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(rtn);
      case 12:  // 错误通知消息：
         //"数据包路由路径太长");
         //"应用已注销");
         //"网络异常,目标地址不可到达");
         //"路由已注销");
         //"应用服务器未注册或目的网关无法到达");
         pb = (char *)recvbuf;
         pb[rtn] = '\0';
         recvbufsize = rtn;
         CopyString(pb,szMsg,nMsgSize);
         return(0);  // 无法抵达的请求
      }
   }
}




int CDRTPClient::sendpack(SYS_HEAD *phead, void *vdata, int datalen)
{
   int len;
   char *data = (char *)vdata;
   char buf[MAXDATASIZE+100];
   phead->Ver = 2;
   phead->CompressFlag = 0;
   phead->CRC = 0;
   if (data==NULL) 
      datalen = 0;
   phead->UserDataRealSize = phead->UserDataSize = datalen;
   if (bByteReverse)
   {
      // 属于非x86类CPU: big-endian
      ReverseSysHead(phead);
   }
   phead->CRC = CRC(phead,sizeof(SYS_HEAD));
   if (bByteReverse)
   {
      reverse(&(phead->CRC),sizeof(phead->CRC));
   }

   memcpy(buf,phead,sizeof(SYS_HEAD));
   memcpy(buf+sizeof(SYS_HEAD),vdata,datalen);
   len = sizeof(SYS_HEAD)+datalen;
   datalen = m_socket.Send(buf,len);

/* ****** Updated by CHENYH at 2004-2-12 23:10:30 ****** 
   if (datalen<len)
   {
      // Send Error: -1:链路没有正常建立，被关闭；-2:发送数据时候出错，被关闭；
   }
*/
   return(datalen);
}




////////////////////////////////////////////////////////////////////////////////////////////////
CDRTPServer::CDRTPServer()
{
   classdataid = DRTPSERVERID;
   m_recvnullcounts = 0;
   m_mainfuncno = 0;
}

CDRTPServer::~CDRTPServer()
{
}

bool CDRTPServer::Connect(char *routerip, int port, int funcount, unsigned short *functions, char *szMsg, int nMsgSize)
{
   char buf[1024];
   int trys,i;
   unsigned short *pword;
   SYS_HEAD head;
   CPMUTEX amutex(&m_mutex);
   if (funcount<1) 
   {
      CopyString(szDRTPErrors[2],szMsg,nMsgSize);
      return(false);
   }
   for (trys=0;trys<3;trys++)
   {
      if (m_socket.ConnectTcp(routerip,(short)port+2))
         break;
   }
   if (trys>=3)
   {
      sprintf(buf,"不能与通讯平台服务器<%s> 端口<%d>建立连接!",routerip,port);
      CopyString(buf,szMsg,nMsgSize);
      m_socket.Close();
      return(false);
   }
   
   memset(&head,0,sizeof(head));
   head.Ver=2;
   head.MessageType=1;
   head.CompressFlag=0;

   pword = (unsigned short *)buf;
   pword[0] = (unsigned short)funcount;
   for (i=0;i<funcount;i++)
   {
      pword[i+1]=functions[i];
   }

   if (bByteReverse)
   {
      // Not x86:
      reverse(pword,sizeof(unsigned short));
      for (i=0;i<funcount;i++)
      {
         reverse(pword+i+1,sizeof(unsigned short));
      }
   }

   i = sendpack(&head,buf,sizeof(unsigned short)*(funcount+1));
   if (i<=0)
   {
      CopyString("功能注册失败(发送注册功能失败)!",szMsg,nMsgSize);
      return(false);
   }

   m_recvnullcounts = 0;
   m_mainfuncno = functions[0];
   return (true);  
}

bool CDRTPServer::Close()
{
//   CPMUTEX amutex(&m_mutex);
   m_socket.Close();
   return(true);
}

bool CDRTPServer::Send(SYS_HEAD *pHead, void *senddata, int senddatalen, char *szMsg, int nMsgSize)
{
   char buf[1024];
   CPMUTEX amutex(&m_mutex);
   int rtn;
   if (m_socket.IsFree())
   {
      CopyString("停止发送，本连接已经被关闭!",szMsg,nMsgSize);
      return(false);
   }
   if (pHead->MessageType==5)
      pHead->MessageType = 6;
   rtn = sendpack(pHead,senddata,senddatalen);
   if (rtn<=0)
   {
      CopyString("数据发送失败，本连接已经被关闭!",szMsg,nMsgSize);
      return(false);
   }
   else
   {
      sprintf(buf,"数据发送成功，实际长度:%d",rtn);
      CopyString(buf,szMsg,nMsgSize);
      return(true);
   }
}


// 函数名: CDRTPServer::Receive
// 编程  : 陈永华 2003-9-29 22:35:31
// 描述  : 在限定的时间里wtime(毫秒)，根据通讯平台协议，接收应用数据的头和具体数据内容
// 返回  : int 
/*
            <-1: 错误，需要关闭本连接，重新建立连接
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
*/
// 参数  : SYS_HEAD *pHead  OUT, 与接收数据相关的包头，也可认为属于接收数据的句柄APPHANDLE
// 参数  : void *recvbuf  OUT, 存放接收到的应用数据缓冲
// 参数  : int recvbufsize IN, 缓冲长度尺寸
// 参数  : char *szMsg  OUT, 返回的接收处理消息 NULL不返回
// 参数  : int nMsgSize IN, =0不返回消息，>0 返回信息的最大长度
// 参数  : int wtime IN, 等待接收的等待时间 (毫秒计) =0 一直等待，直到连接出错或接收到正式数据
int CDRTPServer::Receive(SYS_HEAD *pHead, void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
   int rtn;
   char buf[1024];
   unsigned int crc,crc1;

   if (m_socket.IsFree())
   {
      CopyString("停止接收，本连接已经被关闭!",szMsg,nMsgSize);
      return(-1);
   }

   while (1)
   {
      memset(pHead,0,sizeof(SYS_HEAD));
      memset(recvbuf,0,recvbufsize);
      rtn = m_socket.Recv((char *)pHead,sizeof(SYS_HEAD),wtime);
      if (rtn<=0)
      {
         // =0: 没有数据；<0:通讯端口有问题了，需要重新连接
         if (rtn==0)
         {
            recvbufsize = 0;
            // 没有数据：
            m_recvnullcounts++;
            if (m_recvnullcounts>5)
            {
               sprintf(buf,"通讯平台故障，发送5次心跳测试，都没有得到通讯平台的应答，重新连接!");
               CopyString(buf,szMsg,nMsgSize);
               return(-300);
            }
            // 作一次心跳测试包:
            pHead = (SYS_HEAD *)buf;
            memset(pHead,0,sizeof(SYS_HEAD));
            pHead->Ver = 2;
            pHead->MessageType = 10;
            pHead->DestNo = 0xFFFF;
            pHead->Function = m_mainfuncno;
            pHead->FunctionPriority = 1;
            Send(pHead,NULL,0,szMsg,nMsgSize);
         }
         return(rtn);
      }
      if (rtn<(int)sizeof(SYS_HEAD))
      {
         // 收到数据段不足，应该是同步问题，还是关闭了这个连接端口
         sprintf(buf,"收到数据不符合通讯平台规则，也可能属于同步问题，建议关闭连接! 应该接收通讯数据头长度%d>实际长度%d!",
            sizeof(SYS_HEAD),rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(-100);
      }
      // 是否通过检查CRC来判断是否为正确的SYS_HEAD?
      crc = pHead->CRC;
      pHead->CRC = 0;
      crc1 = CRC(pHead,sizeof(SYS_HEAD));
      if (bByteReverse)
      {
         reverse(&crc,sizeof(crc));
      }
      if (crc1!=crc)
      {
         sprintf(buf,"接收数据包头不正确 - CRC-检查错误!(%X!=%X)",crc,crc1);
         CopyString(buf,szMsg,nMsgSize);
         return(-99);
      }
      pHead->CRC = crc;  // restore...
      
      if (bByteReverse)
      {
         // 属于非x86类CPU: 需要转换为本机可辨认的格式 big-endian 低地址存高位字节
         ReverseSysHead(pHead);
      }
      if (recvbufsize<(int)pHead->UserDataSize)
      {
         // 属于接收缓冲不够，只有关闭本连接，清除连接中的数据，重新连接通讯平台
         // 往往有如下原因造成的：
         /*
         1. 接收缓冲长度不足；（属于程序错）
         2. 接收的请求数据不正确；
         3. 连接中的接收缓冲中数据不同步，需要reset本通讯平台连接；
         */
         sprintf(buf,"接收数据的缓冲长度(%d)不足，真正数据包长度为:(%u)，关闭本连接，重新与通讯平台建立连接!",
            recvbufsize,pHead->UserDataSize);
         CopyString(buf,szMsg,nMsgSize);
         return(-98);
      }
      if (pHead->UserDataSize<=0)
      {
         // 应该属于内部交换数据：不属于应用数据
         rtn = 0;
      }
      else
      {
         rtn = m_socket.Recv((char *)recvbuf,pHead->UserDataSize,1000);
         if (rtn<0)
         {
            return(rtn);
         }
         else if (rtn!=(int)pHead->UserDataSize)
         {
            // 通讯可能有问题，还是关闭本连接算了，重新与通讯平台连接吧
            sprintf(buf,"在收到系统包头后的限定时间(%d)里，收不到实际的应用数据包(实际收到%d<需要数据长度%u)",
               wtime,rtn,pHead->UserDataSize);
            CopyString(buf,szMsg,nMsgSize);
            return(-90);
         }
      }
      m_recvnullcounts = 0;
      if (pHead->MessageType==10)
      {
         pHead->MessageType = 11;
         pHead->UserDataRealSize = pHead->UserDataSize = 0;
         Send(pHead,NULL,0,szMsg,nMsgSize);
      }
      else if (pHead->MessageType==5)
      {
         recvbufsize = rtn;
         sprintf(buf,"收到请求数据包，长度为%d",rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(rtn);
      }
   }
}



int CDRTPServer::sendpack(SYS_HEAD *phead, void *vdata, int datalen)
{
   int len;
   char *data = (char *)vdata;
   char buf[MAXDATASIZE+100];

   phead->Ver = 2;
   phead->CompressFlag = 0;
   phead->CRC = 0;
   if (data==NULL) 
      datalen = 0;
   phead->UserDataRealSize = phead->UserDataSize = datalen;
   if (bByteReverse)
   {
      // 属于非x86类CPU: big-endian
      ReverseSysHead(phead);
   }
   phead->CRC = CRC(phead,sizeof(SYS_HEAD));
   if (bByteReverse)
   {
      reverse(&(phead->CRC),sizeof(phead->CRC));
   }
/* ****** Updated by CHENYH at 2003-12-5 17:19:27 ****** 

   alen = write(m_socket,phead,sizeof(SYS_HEAD));
   if (alen<=0)
      return(alen);
   if (datalen<=0)
      return(sizeof(SYS_HEAD));
   len = 0;
   while (len<datalen)
   {
      alen = datalen-len;
      if (alen>TCP_BLOCK_SIZE)
         alen = TCP_BLOCK_SIZE;
      alen = write(m_socket,data+len,datalen-len);
      if (alen<=0)
      {
         // 不知道是否会有WOULDBLOCK
         return(alen);
      }
      len += alen;
   }
   return(len+sizeof(SYS_HEAD));

*/
   memcpy(buf,phead,sizeof(SYS_HEAD));
   memcpy(buf+sizeof(SYS_HEAD),vdata,datalen);
   len = sizeof(SYS_HEAD)+datalen;

   datalen = m_socket.Send(buf,len);

/* ****** Updated by CHENYH at 2004-2-12 23:10:30 ****** 
   if (datalen<len)
   {
      // Send Error: -1:链路没有正常建立，被关闭；-2:发送数据时候出错，被关闭；
   }
*/
   return(datalen);
}


// 函数名: CDRTPServer::receivedata
// 编程  : 陈永华 2003-9-28 22:00:04
// 描述  : 在wtime（毫秒）时间里，等待接收指定长度的数据
// 返回  : int <0 端口出错，需要重新连接；0 在指定时间里没有数据可以接收；>0收到数据的实际长度，也有可能在指定时间里收到的数据长度不足
// 参数  : void *recvbuf
// 参数  : int recvlen 指定的接收数据长度
// 参数  : char *szMsg
// 参数  : int nMsgSize
// 参数  : unsigned int wtime 0一直以等待方式接收数据；>0以毫秒单位时间内等待接收





bool CDRTPServer::IsOpenning()
{
   return(m_socket.IsFree()==false);
}

bool CDRTPClient::IsOpenning()
{
   return(m_socket.IsFree()==false);
}
