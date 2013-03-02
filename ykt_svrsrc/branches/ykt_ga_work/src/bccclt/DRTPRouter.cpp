// DRTPRouter.cpp: implementation of the CDrtpRouter class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mutex.h"
#include "DRTPRouter.h"
#include "XPData.h"

#ifdef DRTP_V3
#include "DRTPAPI.h"
#elif defined DRTP_V3X
#include "tcp.h"
bool bByteReverse = false;

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
   register char *pb=(char *)data;
   register char *pe=pb+len-1;
   register char b;
   while (pe>pb)
   {
      b = *pb;
      *pb = *pe;
      *pe = b;
      pe--; pb++;
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

#else
#include "drtplib.h"
#include "drtperr.h"
#endif

class  CDRTPInit
{
public:
	CDRTPInit();
   ~CDRTPInit();
};

static CDRTPInit _DRTP_INIT;
CDRTPInit::CDRTPInit()
{
#ifdef DRTP_V3
   DRTPInitialize();
#elif defined DRTP_V3X
   bByteReverse = (htons(1)==1);	
#else
   int errcode;   
   char errmsg[300];   
   DrtpInit(&errcode,errmsg);
#endif
}

CDRTPInit::~CDRTPInit()
{
#ifdef DRTP_V3
   DRTPUninitialize();
#elif defined DRTP_V3X
#else
   DrtpExit();
#endif
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrtpRouter::CDrtpRouter()
{

}

CDrtpRouter::~CDrtpRouter()
{

}

//////////////////////////////////////////////////////////////////////
// CDrtpClient Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrtpClient::CDrtpClient()
{
#ifdef DRTP_V3X
#else
   m_handle = NULL;
#endif
   m_lasttime = 0;
}

CDrtpClient::~CDrtpClient()
{
   Close();
}

int CDrtpRouter::Broad(int branchno, int funcno, char *sbuf, int sblen, char *errmsg)
{
   CDrtpClient *pCli=NULL;
   CLILIST::iterator icl;
   int i;
   CDrtpClient *pcli;
   for (icl=m_CliList.begin();icl!=m_CliList.end();icl++)
   {
      pcli = *icl;
      if (pcli->m_mutex.TryLock())
      {
         pCli = pcli;
         break;
      }
   }
   if (pCli==NULL)
   {
      pCli = new CDrtpClient;
      if (pCli==NULL)
      {
         sprintf(errmsg,"Cannot build DRTPClient(%s,%d) to link DRTP!",m_IP,m_port);
         return(-100);
      }
      pCli->m_mutex.Lock();
      m_CliList.push_back(pCli);
   }
   else
   {
      if (pCli->IsOpenning() && time(NULL)>pCli->m_lasttime+60)
      {
         // 空闲超时，该连接可能被router关闭了：
         pCli->Close();
      }
   }
   for (i=0;i<2;i++)
   {
      if (!(pCli->IsOpenning()))
      {
         if (!(pCli->Connect(m_IP,m_port,errmsg)))
         {
            pCli->m_mutex.UnLock();
            return(-101);
         }
      }
      if (pCli->Broad(branchno,funcno,sbuf,sblen,errmsg))
      {
         pCli->m_mutex.UnLock();
         return(0);
      }
   }
   // 发送失败：
   pCli->Close();
   pCli->m_mutex.UnLock();
   return(-102);
}


int CDrtpRouter::CLISendReceive(int branchno, int funcno, int timeout, char *sbuf, int sblen, char *rbuf, int rbsize, char *errmsg)
{
   CDrtpClient *pCli=NULL;
   CLILIST::iterator icl;
   int i,rtn;
   CDrtpClient *pcli;
   for (icl=m_CliList.begin();icl!=m_CliList.end();icl++)
   {
      pcli = *icl;
      if (pcli->m_mutex.TryLock())
      {
         pCli = pcli;
         break;
      }
   }
   if (pCli==NULL)
   {
      pCli = new CDrtpClient;
      if (pCli==NULL)
      {
         sprintf(errmsg,"Cannot build DRTPClient(%s,%d) to link DRTP!",m_IP,m_port);
         return(-100);
      }
      pCli->m_mutex.Lock();
      m_CliList.push_back(pCli);
   }
   else
   {
      if (pCli->IsOpenning() && time(NULL)>pCli->m_lasttime+60)
      {
         // 空闲超时，该连接可能被router关闭了：
         pCli->Close();
      }
   }
   for (i=0;i<2;i++)
   {
      if (!(pCli->IsOpenning()))
      {
         if (!(pCli->Connect(m_IP,m_port,errmsg)))
         {
            pCli->m_mutex.UnLock();
            return(-101);
         }
      }
      if (pCli->Send(branchno,funcno,sbuf,sblen,errmsg))
         break;
   }
   if (i>=2)
   {
      // 发送失败：
      pCli->Close();
      pCli->m_mutex.UnLock();
      return(-102);
   }
   if (timeout<=0)
      timeout=60000;
   /* ****** Updated by CHENYH at 2008-3-6 16:53:11 ****** 
   为了专门用于发收标准的XPACK数据，结合通讯平台和XPAKC协议
   应该检查包头中的userdata，以确认接收的应答中的userdata
   就是本次发送的userdata数据，防止对方程序错误发送乱七八糟的数据。
   鉴于金融事业部黄金二级系统报盘程序中错误，
   以强壮本模块。
   rtn = pCli->Receive(rbuf,rbsize,errmsg,timeout);
   if (rtn<=0)
   {
      pCli->Close();
      pCli->m_mutex.UnLock();
      return(-103);
   }
   pCli->m_mutex.UnLock();
   return(rtn);
   ******************************************************/
   ST_PACKHEAD *pHead = (ST_PACKHEAD *)sbuf;
   unsigned int userdata = pHead->userdata;
   while (1)
   {
      rtn = pCli->Receive(rbuf,rbsize,errmsg,timeout);
      if (rtn<=0)
      {
         pCli->Close();
         pCli->m_mutex.UnLock();
         return(-103);
      }
      if (rtn>=(int)sizeof(ST_PACKHEAD))
      {
         pHead = (ST_PACKHEAD *)rbuf;
         if (pHead->userdata==userdata)
         {
            pCli->m_mutex.UnLock();
            return(rtn);
         }
      }
   }
}

bool CDrtpClient::IsOpenning()
{
#ifdef DRTP_V3
   return(m_handle!=NULL);
#elif defined DRTP_V3X
	return(m_handle.IsConnected());
#else
   return(m_handle>0);
#endif
}

bool CDrtpClient::Connect(char *ip, int port, char *errmsg)
{
   Close();
#ifdef DRTP_V3
   m_handle = DRTPConnect(ip,port,0);
   if (m_handle==NULL)
   {
      sprintf(errmsg,"Fail to connect with DRTP(%s,%d)",ip,port);
      return(false);
   }
#elif defined DRTP_V3X
	int trys;
   for (trys=0;trys<3;trys++)
   {
      if (m_handle.ConnectTcp(ip,(short)port))
         break;
   }
   if (trys>=3)
   {
      sprintf(errmsg,"Fail to connect with DRTP<%s:%d>!",ip,port);
      m_handle.Close();
      return(false);
   }
   sprintf(errmsg,"Linked to DRTP<%s:%d>!",ip,port);
#else
   int errcode;
   m_handle=DrtpConnect(ip,port,&errcode,errmsg);   
   if (m_handle <= 0)
   {
      return false;
   }
#endif
   m_lasttime = time(NULL);
   return(true);   
}

#ifdef DRTP_V3X
int CDrtpClient::sendpack(SYS_HEAD *phead, void *vdata, int datalen)
{
   int len;
   char *data = (char *)vdata;
   char buf[8192+100];
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
   len = (int)sizeof(SYS_HEAD)+datalen;
   datalen = m_handle.Send(buf,len);
	
   return(datalen);
}
#endif

bool CDrtpClient::Send(int destno, int funcno, char *sbuf, int sblen, char *errmsg)
{
   if (!IsOpenning())
   {
      sprintf(errmsg,"Cannot Send Data, because not link with DRTP!");
      return(false);
   }
#ifdef DRTP_V3X
   SYS_HEAD head;
   int rtn;
   memset(&head,0,sizeof(SYS_HEAD));
   head.Ver = 2;
   head.CompressFlag = 0;
   head.DestNo = destno;
   head.Function = funcno;
   head.FunctionPriority = 2;
   head.MessageType = 5;
   head.UserDataRealSize = head.UserDataSize = sblen;
   rtn = sendpack(&head,sbuf,sblen);
   if (rtn<=0)
   {
		Close();
      sprintf(errmsg,"Send data error:%d",rtn);
      return(false);
   }
#elif defined DRTP_V3
   if (!DRTPSend(m_handle,destno,funcno,sbuf,sblen,2,false))
   {
      errmsg[0]='\0';
      DRTPGetLastError(m_handle,errmsg,255);
      if ('\0'==errmsg[0])
      {
         sprintf(errmsg,"Fail to send data(length=%d) to BCC(dno=%d,fno=%d)",sblen,destno,funcno);
      }
      // Added at 2006-12-30 12:02:53
      Close();
      //////////////////////////////////////////////////////////////////////////
      
      return(false);
   }
#else
   int errcode;   
   //TAG_DRTPHANDLE drtphandle;
   if (DrtpPostMessage(3,destno,funcno,sbuf,sblen,&errcode,errmsg,m_handle)==0)
   {
      Close();
      return(false);
   }
#endif
   m_lasttime = time(NULL);
   return true;
}

void CDrtpClient::Close()
{
#ifdef DRTP_V3
   if (m_handle!=NULL)
   {
      DRTPClose(m_handle);
      m_handle = NULL;
   }
#elif defined DRTP_V3X
	m_handle.Close();
#else
   if (m_handle>0)
   {
      DrtpClose(m_handle);
      m_handle = -1;
   }   
#endif
}

int CDrtpClient::Receive(char *rbuf, int rbsize, char *errmsg, int waittime)
{
#ifdef DRTP_V3
   int rtn;
   rtn = DRTPReceive(m_handle,rbuf,rbsize,waittime);
   if (rtn<=0)
   {
      errmsg[0]='\0';
      DRTPGetLastError(m_handle,errmsg,MAXERRMSGLENGTH-1);
      if ('\0'==errmsg[0])
      {
         if (rtn==0)
         {
            sprintf(errmsg,"Timeout (%d ms) to receive data from DRTP!",waittime);
         }
         else
         {
            strcpy(errmsg,"Failure to receive data from DRTP!");
         }
      }
   }
   else
   {
      m_lasttime = time(NULL);
   }
   return(rtn);
#elif defined DRTP_V3X
   int rtn;
   char buf[1024];
   unsigned int crc,crc1;
   SYS_HEAD *phead;
   char *pb;

	if (!m_handle.IsConnected())
	{
		strcpy(errmsg,"Not linked with DRTP yet.");
		return(-1);
	}
   phead = (SYS_HEAD *)buf;
   while (1)
   {
      rtn = m_handle.Recv((char *)phead,sizeof(SYS_HEAD),waittime);
      if (rtn<=0)
      {
         // =0: Timeout; <0:Link or socket error!
         if (rtn==0)
         {
            sprintf(errmsg,"Timeout (%d ms) to receive data from DRTP!",waittime);
         }
         else
         {
            sprintf(errmsg,"Failure to receive data from DRTP:%d",rtn);
         }
         return(rtn); 
      }
      if (rtn<(int)sizeof(SYS_HEAD))
      {
         sprintf(errmsg,"Invalid SYS_HEAD Received! sizeof(SYS_HEAD)%d>Len of recv.%d!",
            (int)sizeof(SYS_HEAD),rtn);
         return(-100);
      }
      // Use CRC check SYS_HEAD data?
      crc = phead->CRC;
      phead->CRC = 0;
      crc1 = CRC(phead,sizeof(SYS_HEAD));
      if (bByteReverse)
      {
         reverse(&crc,sizeof(crc));
      }
      if (crc1!=crc || phead->Ver!=2)
      {
         strcpy(buf,"Invalid SYS_HEAD, CRC checked error");
         return(-99);
      }
      phead->CRC = crc;
      if (bByteReverse)
      {
         // 属于非x86类CPU: 需要转换为本机可辨认的格式 big-endian 低地址存高位字节
         ReverseSysHead(phead);
      }
      if (rbsize<phead->UserDataSize)
      {
         // 属于接收缓冲不够，只有关闭本连接，清除连接中的数据，重新连接通讯平台
         // 往往有如下原因造成的：
         /*
         1. 接收缓冲长度不足；（属于程序错）
         2. 接收的请求数据不正确；
         3. 连接中的接收缓冲中数据不同步，需要reset本通讯平台连接；
         */
         sprintf(errmsg,"Size of Recv. Buffer(%d)<Lenght of Recv. Data(%d), Fail to recv.!",
            rbsize,phead->UserDataSize);
         return(-98);
      }
      if (phead->UserDataSize<=0)
      {
         // 应该属于内部交换数据：不属于应用数据
         rtn = 0;
      }
      else
      {
         rtn = m_handle.Recv((char *)rbuf,phead->UserDataSize,2000); // 要求在1秒钟内接收到后续包数据
         if (rtn<0)
         {
            return(rtn);
         }
         else if (rtn!=phead->UserDataSize)
         {
            sprintf(errmsg,"No enough pack data recv.(%d<%u)",
               rtn,phead->UserDataSize);
            return(-90);
         }
      }
      m_lasttime = time(NULL);
      switch (phead->MessageType)
      {
      case 10:
         phead->MessageType = 11;
         phead->UserDataRealSize = phead->UserDataSize = 0;
         sendpack(phead,NULL,0);
         break;
      case 5:  // 不应该为这个数
      case 6:  // 应该为6  2003-10-13 added
         //memcpy(&m_recvhead,phead,sizeof(SYS_HEAD));
         sprintf(errmsg,"Len of recv. data:%d",rtn);
         return(rtn);
      case 12:  // 错误通知消息：
         //"数据包路由路径太长"
         //"应用已注销"
         //"网络异常,目标地址不可到达"
         //"路由已注销"
         //"应用服务器未注册或目的网关无法到达"
         pb = (char *)rbuf;
			if (rtn>255)
				rtn = 255;
         pb[rtn] = '\0';
         strcpy(errmsg,pb);
         return(0);  // 无法抵达的请求
      }
   }

#else
	int bret;
	int len;
	TAG_DRTPHANDLE drtphandle;
	int errcode;
	if (waittime < 0)
	{
		bret=DrtpReadMessage(rbuf,rbsize,&len,m_handle,&drtphandle,&errcode,errmsg);
	}
	else
	{
		bret=DrtpReadMessage(rbuf,rbsize,&len,m_handle,&drtphandle,&errcode,errmsg,waittime);
	}
	if (bret!=0)
	{
      m_lasttime = time(NULL);
		return len;
	}
	else
	{
		if (errcode == ERROR_SOCKET)
		{
         Close();
         return -2;  // DRTP4专用的错误，连接被关闭，需要重新连接后使用
		}
		else
		{
			return 0;
		}
	}
#endif
}

#define DRTP_V42
bool CDrtpClient::Broad(int destno, int funcno, char *sbuf, int sblen, char *errmsg)
{
#ifdef DRTP_V3
   strcpy(errmsg,"DRTP3不能支持广播模式!");
#elif defined DRTP_V3X
	strcpy(errmsg,"DRTP3不能支持广播模式!");
#else
#ifdef DRTP_V42
   strcpy(errmsg,"DRTP42不能支持广播模式!");
#else
   int errcode;
   if (DrtpPostAllMessage(3,destno,funcno,sbuf,sblen,&errcode,errmsg,m_handle)!=0)
   {
      m_lasttime = time(NULL);
      return(true);
   }
#endif
#endif
   return(false);
}

