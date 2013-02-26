/********************************************************************
	created:	2004/03/22
	created:	22:3:2004   10:13
	filename: 	E:\proj\goldmem\gmsvrall\SvrLink.cpp
	file path:	E:\proj\goldmem\gmsvrall
	file base:	SvrLink
	file ext:	cpp
	author:		CHENYH
	
	purpose:	

   Version:   20040322 - 增加了SetBUError, SetMaxRow 
               以及用版本编号来规范BU与BCC的版本检查
              
              2008-12-15 21:50:05 在TESTLINK消息接收的地方，增加了GETREQ消息的检查，
              否则，将会导致消息不同步，将有用的GETREQ(BCC提供给BU的请求处理，给丢弃了)
*********************************************************************/
// SvrLink.cpp: implementation of the CSvrLink class.
//
//////////////////////////////////////////////////////////////////////
#ifndef BUPUBLIB
#define BUPUBLIB
#endif
#include "stdafx.h"
#include "mypub.h"
#include "svrlink.h"
#include "comstru.h"
#include "bdefine.h"
#include "logfile.h"
#include "XPack.h"

CLogFile *g_pLogFile;
char iDefaultAnswerMode=AM_AUTO;   // 本系统缺省的应答模式，本参数根据系统各自的编程特性设定
//int iThisProcID;


#define MAXROW 100

void reverse(void *data,int len)
{
/* ****** Updated by CHENYH at 2005-10-29 1:59:52 ****** 
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;

   ASSERT(len<=16);

   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
   }
*******************************************************/
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

void ResetMsgHead(MSGHEAD *phead,short msgtype,unsigned short msglen)
{
   phead->msgid = LMSGID;
   phead->msgtype = msgtype;
   phead->len = msglen;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 函数名: CSvrLink::SetTRUserID
// 编程  : 陈永华 2005-8-2 11:25:04
// 描述  : 设置更改应答数据接收方，表示后续PutRow等数据都要发送给指定方
// 返回  : int 
// 参数  : TRUSERID *ruserid : 指定的应答数据接收方
int CSvrLink::SetTRUserID(TRUSERID *ruserid)
{
   unsigned char sbuf[MAXMSG];
   RP_ANSDATAEXH *pad;
   pad = (RP_ANSDATAEXH *)sbuf;
   pad->SourceNo = htons(ruserid->SourceNo);
   memcpy(&(pad->syshead),&(ruserid->syshead),sizeof(pad->syshead));
   return(SendMsg(MT_SETUSERID,sizeof(RP_ANSDATAEXH),sbuf));
}


CSvrLink::CSvrLink()
{
   bExit = false;
   iLastReqType = 0;
   iLastRetCode = 0;
#ifndef NOIPCS
   m_pMsgQueue=NULL; // 2007-11-22 10:08:10 使用IPC消息交换数据
#endif
}

CSvrLink::~CSvrLink()
{

}


// 函数名: CSvrLink::ToLink
// 编程  : 陈永华 2004-2-11 12:14:25
// 描述  : 
// 返回  : int 
// 参数  : ST_BUNIT *pBUnit
int CSvrLink::ToLink(ST_BUNIT *pBUnit)
{
   int i;
   int rtn;
   RP_LINKBEGIN rp;
   AP_LINKBEGIN *pap;
   MSGBUF *pmb;

   memset(&head,0,sizeof(head));
   iLastReqType = 0;
   iLastRetCode = 0;
   iGRFrame = 10;  // 重新开始的获取请求的帧号，注意在连接初期，必须与BCC不同，以防止不同步
   Close();
   rp.bu1 = 1;
   memcpy(rp.szBUGroupID,pBUnit->szBUGroupID,sizeof(rp.szBUGroupID));
   rp.iDefaultAM = iDefaultAnswerMode;
   rp.iBUVersion = htonl(BU_VERSION);  // BU的版本编码
   /* ****** Updated by CHENYH at 2005-9-1 20:35:12 ****** */
#ifdef WIN32
   rp.dwProcID = GetCurrentProcessId();
#else
   rp.dwProcID = getpid();
#endif

   // 2007-11-22 16:14:24 Added by CHENYH
   rp.bUseMQ = 0;
#ifndef NOIPCS
   if (g_MQFactory.GetMQ(0)!=NULL)
      rp.bUseMQ = 1;  // to use MQ
#endif
   /********************************************************/

   if (linksock.ConnectTcp(pBUnit->szSvrIP,pBUnit->iSvrPort))
   {
      for (i=0;i<5;i++)
      {
         rtn = SendMsgT(MT_LINKBEGIN,sizeof(rp),&rp); 
         if (rtn!=0)
         {
            sprintf(buf,"发送连接请求数据的时候失败，SendMsg()=%d，端口失败号为%d\n",rtn,linksock.GetLastError(NULL,0));
            DEBUG_RUNTIME_MSGOUT(buf);
            return(rtn);
         }
         rtn = RecvMsgT(pBUnit->iHBInterval);
         if (rtn>=(int)(sizeof(MSGHEAD)))
         {
            pmb = GetRecvMsg();
            if (pmb->head.msgtype==MT_LINKBEGIN && pmb->head.len>=sizeof(AP_LINKBEGIN))
            {
               pap = (AP_LINKBEGIN *)(pmb->data);
               svr_hs1 = pap->bc1;
               // 无所谓字序的转换了，反正不会重复的，如果需要，这个参数也多数会返回给BCC的
               iThisProcID = ntohl(pap->bu_number);
#ifndef NOIPCS
               if (rp.bUseMQ!=0)
               {
                  m_pMsgQueue = g_MQFactory.GetMQ(iThisProcID);
                  if (m_pMsgQueue==NULL||!m_pMsgQueue->Open(OM_OPEN,1))
                  {
                     g_pLogFile->WriteLogEx(11225,"Fail to open BU-MQ:%d",iThisProcID);
                     return(-100);
                  }
               }
#endif
               bccBFuncNo = ntohl(pap->basefuncno);
               bccID = ntohl(pap->bccid);
               if (strlen(pap->szmsg)>0)
               {
                  g_pLogFile->WriteLogEx(1000,"BU%d-BCC Warning:%s",iThisProcID,pap->szmsg);
               }
               return(1);  // 成功连接，可以开始处理了
            }
         }
         else if (rtn!=0)
         {
            sprintf(buf,"接收连接请求数据确认的时候失败，RecvMsg()=%d，端口失败号为%d\n",rtn,linksock.GetLastError(NULL,0));
            DEBUG_RUNTIME_MSGOUT(buf);
            return(rtn);  // 接收时候失败
         }
      }
      Close();
      DEBUG_RUNTIME_MSGOUT("做了5次连接请求都没有应答返回!\n");
      return(0);
   }
   return(-100);
}

MSGBUF *CSvrLink::GetRecvMsg()
{
   return((MSGBUF *)buf);
}


int CSvrLink::RecvMsgT(int timeout)
{
   MSGBUF *pMsgBuf=(MSGBUF *)buf;
   MSGHEAD *phead = (MSGHEAD *)buf;
   int rtn;
   rtn = linksock.Recv(buf,sizeof(MSGHEAD),timeout);
   if (rtn!=sizeof(MSGHEAD))
      return(rtn);  // 接收时候出错，或超时
   if (phead->msgid==RMSGID)
   {
      reverse(&(phead->msgid),sizeof(phead->msgid));
      reverse(&(phead->msgtype),sizeof(phead->msgtype));
      reverse(&(phead->len),sizeof(phead->len));
   }
   if (phead->msgid!=LMSGID || phead->len>MAXMSG)
   {
      // 属于不正常的MSG，关闭端口，重新连接。。。
      // 或者数据流不同步，通过重新连接进行同步。。。
      DEBUG_RUNTIME_MSGOUT("属于不正常的MSG或者数据流不同步，关闭端口，重新连接\n");
      Close();
      return(-11);
   }
   if (phead->len>0)
   {
      rtn = linksock.Recv(pMsgBuf->data,phead->len,5000);  // 一直等待到接收到后续数据，或出错，或5秒钟超时
      if (rtn!=phead->len)
      {
         Close();
         return(rtn); // 接收时候出错，或超时
      }
   }
   //m_lastrcvtick = GetTickCount();
   return(phead->len+sizeof(MSGHEAD));  
}

int CSvrLink::RecvMsgQ(int timeout)
{
#ifdef NOIPCS
   return(-1);
#else
   if (m_pMsgQueue==NULL || !(m_pMsgQueue->IsOpened()))
      return(-1);
   return(m_pMsgQueue->Recv(buf,sizeof(buf),timeout,0));      
#endif   
}

// 函数名: CSvrLink::RecvMsg
// 编程  : 陈永华 2004-2-10 22:40:18
// 描述  : 按照MSG协议接收数据
// 返回  : int >0:接收到正常数据包；0:超时；-1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；-3:在接收数据的时候，出错而被关闭
// 参数  : int timeout
int CSvrLink::RecvMsg(int timeout)
{
   int rtn;
#ifdef NOIPCS
   rtn = RecvMsgT(timeout);
#else
   if (m_pMsgQueue!=NULL && m_pMsgQueue->IsOpened())
   {
      rtn = RecvMsgQ(timeout);
      if (rtn==0)
      {
         rtn = RecvMsgT(0); // check the socket status.
      }
   }
   else 
      rtn = RecvMsgT(timeout);
#endif
   if (rtn<0)
   {
      Close();
   }
   else if (rtn>=sizeof(MSGHEAD))
   {
      m_lastrcvtick = GetTickCount();
   }
   return(rtn);
}


int CSvrLink::SendMsgT(short msgtype, unsigned short msglen, void *msgbuf)
{
   int rtn;
   MSGHEAD *phead;
   char xbuf[MAXMSG+sizeof(MSGHEAD)];
   
   phead = (MSGHEAD *)xbuf;
   ResetMsgHead(phead,msgtype,msglen);
   if (msglen>0)
   {
      memcpy(xbuf+sizeof(MSGHEAD),msgbuf,msglen);
   }
   rtn = linksock.Send(xbuf,sizeof(MSGHEAD)+msglen);
   if (rtn<0)
   {
      // 发送时，端口有问题，包括被关闭
      return(rtn);   
   }
   else if (rtn==0)
   {
      // 不应该出现这种情况
      DEBUG_RUNTIME_MSGOUT("发送消息时出现编码性错，CTcpSocket.Send不该出现==0的返回!\n");
      return(-100);
   }
   return(0);
}

int CSvrLink::SendMsgQ(short msgtype, unsigned short msglen, void *msgbuf)
{
#ifdef NOIPCS
   return(-1);
#else
   MSGHEAD *phead;
   char xbuf[MAXMSG+sizeof(MSGHEAD)];
   MSGBUF *pMsgBuf=(MSGBUF *)xbuf;
   if (m_pMsgQueue==NULL || !(m_pMsgQueue->IsOpened()))
      return(-1);
   
   phead = (MSGHEAD *)xbuf;
   ResetMsgHead(phead,msgtype,msglen);
   if (msglen>0)
   {
      memcpy(pMsgBuf->data,msgbuf,msglen);
   }
   return(m_pMsgQueue->Send(xbuf,sizeof(MSGHEAD)+msglen,0));   
#endif   
}

// 函数名: CSvrLink::SendMsg
// 编程  : 陈永华 2004-2-10 21:08:11
// 描述  : 以MSG格式发送消息数据给调度中心
// 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
// 参数  : short msgtype ：IN 发送的消息类型
// 参数  : unsigned short msglen ：IN 消息体数据长度
// 参数  : void *msbuf ： IN 消息数据缓存
int CSvrLink::SendMsg(short msgtype, unsigned short msglen, void *msgbuf)
{
   int rtn;
#ifdef NOIPCS
   rtn = SendMsgT(msgtype,msglen,msgbuf);
#else
   if (m_pMsgQueue!=NULL && m_pMsgQueue->IsOpened())
   {
      rtn = SendMsgQ(msgtype,msglen,msgbuf);
   }
   else
   {
      rtn = SendMsgT(msgtype,msglen,msgbuf);
   }
#endif
   if (rtn<0)
   {
      Close();
      return(rtn);
   }
   return(0);
}

bool CSvrLink::LinkOK()
{
   return(!linksock.IsFree());
}

void CSvrLink::Close()
{
   linksock.Close();
#ifndef NOIPCS
   if (m_pMsgQueue!=NULL)
      m_pMsgQueue->Close(); // 2007-11-22 10:08:10 使用IPC消息交换数据
#endif
}

int CSvrLink::Processing(ST_BUNIT *pBUnit)
{
   int rtn;
   MSGBUF *pmb;
   RP_REQUEST rp;

   if (linksock.IsFree())
      return(0);
   rp.iGRFrame = iGRFrame;
   rp.iLastReqType = htonl(iLastReqType);
   rp.iLastRetCode = htonl(iLastRetCode);
   rtn = SendMsg(MT_GETREQ,sizeof(rp),&rp);
   if (rtn!=0)
   {
      // 连接出现问题了：或被BCC关闭了
      return(-1);
   }
GETNEXTMSG:
   rtn = RecvMsg(pBUnit->iHBInterval);
   if (rtn>=(int)(sizeof(MSGHEAD)))
   {
      pmb = GetRecvMsg();
      switch (pmb->head.msgtype)
      {
      case MT_LINKBEGIN:
         // Update some variables:
         if (pmb->head.len>=sizeof(AP_LINKBEGIN))
         {
            AP_LINKBEGIN *pap;
            pap = (AP_LINKBEGIN *)(pmb->data);
            svr_hs1 = pap->bc1;
            iThisProcID = ntohl(pap->bu_number);
         }
         break;
      case EXITMSGTYPE:
         Close();
         bExit = true;
         break;
      case WRITEAPPINFO:
         (*pWriteAppInfo)(bccBFuncNo,bccID);   // 在主框架程序部分
         break;
      case MT_GETREQ:
         // OK,have new request to process
         if (pmb->head.len>=sizeof(AP_REQUEST))
         {
            AP_REQUEST *prp = (AP_REQUEST *)(pmb->data);
            if (prp->iGRFrame==iGRFrame)
            {
               CallBPFunction(pmb);
               iGRFrame++;
            }
         }
         break;
      /* ****** Updated by CHENYH at 2005-10-24 14:29:13 ****** */
      // 当BU用CheckLink()发送MT_TESTLINK心跳检查的时候，BCC给BU反馈一个心跳检查应答，
      // 当BU用CheckLink()命令的时候，应该用tc2_tc1(GetTickCount(),m_lastrcvtick)与pBUnit->iHBInterval×2来比较
      // BCC与BU在不稳定网络下，链路是否正常的。
      case MT_TESTLINK:
         goto GETNEXTMSG;  // 仅仅作为当BU给BCC发送MT_TESTLINK心跳检查时候，BCC给BU的心跳检查应答
         break;
      /*******************************************************/
      default:
         break;
      }
   }
   return(rtn);
}

#define PRIORITIES 3

// 编程  : 陈永华 2005-9-6 11:16:09
int CSvrLink::UpdateRegFunction(unsigned int reqtype, char *rtname, char *programmer, int priority, bool bstop)
{
   RP_REGFUNC prf;
   prf.reqtype = htonl(reqtype);
   Strncpy(prf.rtname,rtname,sizeof(prf.rtname));
   Strncpy(prf.programmer,programmer,sizeof(prf.programmer));
   if (priority>PRIORITIES) 
      priority = PRIORITIES;
   else if (priority<1)
      priority = 1;
   prf.priority = htonl(priority);
   prf.bStop = bstop;
   return(SendMsg(MT_REGFUNC,sizeof(RP_REGFUNC),&prf));
}

int CSvrLink::SetCol(TRUSERID *puserid, unsigned char *parmbits)
{
   int n;
   unsigned int i;
   head.recCount = 0;  // 以便在追加记录的时候，将位图发送给BCC
   for (i=n=0;i<sizeof(head.ParmBits);i++)
   {
      if (parmbits[i])
      {
         head.ParmBits[i] |= parmbits[i];  // 合并位图
         n++;
      }
   }
   if (n==0)
   {
      // 属于清空位图模式，也就等同下面的动作
      // head.retCode = 0;
      memset(head.ParmBits,0,sizeof(head.ParmBits));
   }
   return(n);
/* ****** Updated by CHENYH at 2004-3-10 22:32:19 ****** 
   采用新的SetCol规则，尤其在BU端，可以连续多个
   //return(SendMsg(MT_SETCOL,sizeof(head.ParmBits),parmbits));
*/
}

int CSvrLink::PutRowData(ST_PACK *pdata)
{
   unsigned char buf[MAXDATASIZE];
   char szMsg[256];
   int len;
   if (head.recCount<=0)
   {
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // 先提供后续数据记录的位图
      head.recCount = 0;
   }
   head.recCount++;
   EncodeRow(&head,pdata,buf,&len,szMsg);
   return(SendMsg(MT_PUTROWDATA,(unsigned short)len,buf));   
}


int CSvrLink::AnswerData(TRUSERID *ruserid, int retcode, char *szmsg,unsigned char nextflag)
{
   char buf[MAXMSG];
   RP_ANSDATA *pad=(RP_ANSDATA *)buf;
   unsigned short len;
   if (ruserid==NULL)
   {
      pad->SourceNo = htons(0xFFFF);
   }
   else
   {
      pad->SourceNo = htons(ruserid->SourceNo);
      memcpy(&(pad->syshead),&(ruserid->syshead),sizeof(pad->syshead));
   }
   pad->nextflag = nextflag;
   pad->n_retcode = htonl(retcode);
   len = sizeof(RP_ANSDATA);
   pad->szmsg[0]='\0';
/* ****** Updated by CHENYH at 2004-3-11 16:15:14 ****** 
   if (szmsg==NULL || szmsg[0]=='\0')
   {
      pad->szmsg[0]='\0';
   }
   else
   {
      len += strlen(szmsg);
      strcpy(pad->szmsg,szmsg);
      SetParmBit(&head,F_VSMESS);  // ????
   }
*/
   return(SendMsg(MT_ANSDATA,len,pad));
}

int CSvrLink::AnswerDataEx(TRUSERID *ruserid, ST_CPACK *apack, ST_PACK *pArrays, int retcode, char *szmsg)
{
   unsigned char sbuf[MAXMSG];
   RP_ANSDATAEXH *pad;
   unsigned char *buf;
   int len;
   char szMsg[256];
   pad = (RP_ANSDATAEXH *)sbuf;
   buf = sbuf+sizeof(RP_ANSDATAEXH);

/* ****** Updated by CHENYH at 2004-3-11 20:43:59 ****** 
   if (szmsg!=NULL && szmsg[0]!='\0')
   {
      SetParmBit(&(apack->head),F_VSMESS);
      strcpy(apack->pack.vsmess,szmsg);
   }
*/
   apack->head.retCode = retcode;
   if (ruserid==NULL)
   {
      pad->SourceNo = htons(0xFFFF);
   }
   else
   {
      pad->SourceNo = htons(ruserid->SourceNo);
      memcpy(&(pad->syshead),&(ruserid->syshead),sizeof(pad->syshead));
   }

   if (apack->head.recCount<1)
   {
      len = sizeof(ST_PACKHEAD);
      ModifyHead(&(apack->head),buf);
   }
   else if (apack->head.recCount==1||pArrays==NULL)
   {
      apack->head.recCount = 1;
      EncodeBuf(apack,buf,&len,szMsg);
   }
   else 
   {
      EncodeBufArray(apack,pArrays,buf,&len,szMsg);
   }
   len += sizeof(RP_ANSDATAEXH);
   return(SendMsg(MT_ANSDATAEX,(unsigned int)len,sbuf));
}

int CSvrLink::PushData(int sourceno, int destno, int funcno, int batchno, char pushmode, int acktime, void *pdata, int pdlen)
{
   TPUSHDEST dest;
   dest.SourceNo = sourceno;
   dest.DestNo = destno;
   dest.FuncNo = funcno;
   dest.BatchNo = batchno;
   return(PushDataEx(&dest,1,pdata,pdlen,pushmode,acktime));
}


int CSvrLink::PushData(int sourceno, int destno, int funcno, int batchno, ST_CPACK *ppack, char pushmode, int acktime,ST_PACK *pArray)
{
   TPUSHDEST dest;
   dest.SourceNo = sourceno;
   dest.DestNo = destno;
   dest.FuncNo = funcno;
   dest.BatchNo = batchno;
   return(PushDataEx(&dest,1,ppack,pushmode,acktime,pArray));
}


int CSvrLink::PushDataEx(TPUSHDEST *pushdests, int pdcount, void *pdata, int pdlen, char pushmode, int acktime)
{
   int i;
   unsigned char sbuf[MAXMSG];
   RP_PUSHDATAH *ph;
   TPUSHDESTN *pd;
   unsigned short len;
   ASSERT(pdcount>0);
   ph = (RP_PUSHDATAH *)sbuf;
   ph->pushmode = pushmode;
   ph->acktime = htonl(acktime);
   ph->dcount = htons(pdcount);
   len = sizeof(RP_PUSHDATAH);
   pd = (TPUSHDESTN *)(sbuf+len);
   for (i=0;i<pdcount;i++)
   {
      pd[i].SourceNo = htons(pushdests[i].SourceNo);
      pd[i].DestNo = htons(pushdests[i].DestNo);
      pd[i].FuncNo = htons(pushdests[i].FuncNo);
      pd[i].BatchNo = htonl(pushdests[i].BatchNo);
      len += sizeof(TPUSHDESTN);
   }
   memcpy(sbuf+len,pdata,pdlen); len += pdlen;
   return(SendMsg(MT_PUSHDATA,len,sbuf));
}


int CSvrLink::PushDataEx(TPUSHDEST *pushdests, int pdcount, ST_CPACK *ppack, char pushmode, int acktime,ST_PACK *pArray)
{
   int i;
   unsigned char sbuf[MAXMSG];
   RP_PUSHDATAH *ph;
   TPUSHDESTN *pd;
   unsigned short len;
   char szmsg[256];
   ASSERT(pdcount>0);
   ph = (RP_PUSHDATAH *)sbuf;
   ph->pushmode = pushmode;
   ph->acktime = htonl(acktime);
   ph->dcount = htons(pdcount);
   len = sizeof(RP_PUSHDATAH);
   pd = (TPUSHDESTN *)(sbuf+len);
   for (i=0;i<pdcount;i++)
   {
      pd[i].SourceNo = htons(pushdests[i].SourceNo);
      pd[i].DestNo = htons(pushdests[i].DestNo);
      pd[i].FuncNo = htons(pushdests[i].FuncNo);
      pd[i].BatchNo = htonl(pushdests[i].BatchNo);
      len += sizeof(TPUSHDESTN);
   }
   if (ppack->head.recCount>1 && pArray==NULL)
   {
      ppack->head.recCount = 1;
   }
   EncodeBufArray(ppack,pArray,sbuf+len,&i,szmsg);
   len += i;
   return(SendMsg(MT_PUSHDATA,len,sbuf));
}




// 函数名: CSvrLink::PutRow
// 编程  : 陈永华 2004-2-20 11:49:12
// 描述  : 为了与集中交易兼容，准备的函数
// 返回  : int 
// 参数  : TRUSERID *handle
// 参数  : ST_PACK *pdata
// 参数  : int retcode
// 参数  : char *rtnMsg
int CSvrLink::PutRow(TRUSERID *handle, ST_PACK *pdata, int retcode, char *rtnMsg)
{
//   return(PutRowData(pdata));
   unsigned char buf[MAXDATASIZE];
   unsigned short len;
   RP_PUTROW *ppr = (RP_PUTROW *)buf;
   char szMsg[256];

///* ****** Updated by CHENYH at 2004-3-11 20:00:03 ****** 
   // 算了，还是保留下来，以便未来可能的扩展，2004-3-11 20:04:42 目前实际是没有用处的
   if (handle==NULL)
   {
      ppr->SourceNo = 0xFFFF;
   }
   else
   {
      ppr->SourceNo = htons(handle->SourceNo);
      memcpy(&(ppr->syshead),&(handle->syshead),sizeof(ppr->syshead));
   }

   ppr->n_retcode = htonl(retcode);
   len = sizeof(RP_PUTROW);

/* ****** Updated by CHENYH at 2004-3-11 20:05:46 ****** 
   还是让业务模块去控制是否将rtnMsg返回给客户端，这里不作处理了
   if (rtnMsg!=NULL && rtnMsg[0]!='\0')
   {
      rtnMsg[sizeof(pdata->vsmess)-1]='\0';
      strcpy(pdata->vsmess,rtnMsg);
      //SetParmBit(&head,F_VSMESS);
   }
*/
   head.retCode = retcode;
   if (head.recCount<=0)
   {
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // 先提供后续数据记录的位图
      head.recCount = 0;      
   }
   head.recCount++;
   int elen;
   EncodeRow(&head,pdata,buf+len,&elen,szMsg);
   len += elen;
   return(SendMsg(MT_PUTROW,len,buf));
}


// 函数名: CSvrLink::DataDone
// 编程  : 陈永华 2004-2-22 13:35:51
// 描述  : 
// 返回  : int 
int CSvrLink::DataDone(int retcode,char *szMsg)
{
   char buf[MAXMSG];
   RP_DATADONE *pad=(RP_DATADONE *)buf;
#ifdef TESTINFO
   sprintf(buf,"功能号(%u)处理结果(%d):%s",iLastReqType,retcode,szMsg);
   DEBUG_RUNTIME_MSGOUT(buf);
#endif
   /* ****** Updated by CHENYH at 2006-2-9 17:26:16 ****** 
   集中交易即使没有记录也需要相应的位图
   *******************************************************/
   if (head.recCount<=0)
   {
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // 先提供后续数据记录的位图
      head.recCount = 0;      
   }
   /******************************************************/

   pad->iLastReqType = htonl(iLastReqType);
   pad->n_retcode = htonl(retcode);
   strcpy(pad->szmsg,szMsg);
   return(SendMsg(MT_DATADONE,sizeof(RP_DATADONE)+strlen(szMsg),buf));
}

//#define COM_JZJY   // 如果需要与集中交易兼容，即没有显式调用AnswerData等其他数据，需要在最后由DataDone来发送结果给请求端

// 函数名: CSvrLink::Err_Deal
// 编程  : 陈永华 2004-2-22 16:36:05
// 描述  : 清除原来准备的应答信息，并且在运行时跟踪文件中记录（错误）信息（为了与集中交易兼容）
// 返回  : int SendMsg返回信息
// 参数  : char *emsg
// 参数  : int retcode
int CSvrLink::Err_Deal(char *emsg, int retcode)
{

/* ****** Updated by CHENYH at 2004-3-12 13:49:50 ****** 
   unsigned char pb[PARMBYTES];
   int rtn;
   memset(pb,0,sizeof(pb));
   rtn = SetCol(NULL,pb);
*/
   CXPack *pXPack = (CXPack *)GetDefaultXPack();
   head.recCount = 0;
   memset(head.ParmBits,0,sizeof(head.ParmBits));
   //SetParmBit(&head,F_VSMESS);   
   iLastRetCode = retcode;
   strcpy(eMsg,emsg);
   ST_PACK pack;
   pXPack->AddField(&pack,"vsmess",emsg,&head);
   //strcpy(pack.vsmess,emsg);
   return(PutRow(&ruserid,&pack,retcode,emsg));
/* ****** Updated by CHENYH at 2004-3-12 13:46:02 ****** 
   rtn = AnswerData(&user,retcode,emsg,0);  // 不容许有后续数据返回了，只有一条结果记录(emsg应该是有值的)
   return(rtn);
*/
}

int CSvrLink::PushRow(int sourceno, int destno, int funcno, ST_PACK *pack, char pushmode, int batchno, int acktime)
{
   TPUSHDEST dest;
   dest.SourceNo = sourceno;
   dest.DestNo = destno;
   dest.FuncNo = funcno;
   dest.BatchNo = batchno;
   return(PushRowEx(&dest,1,pack,pushmode,batchno,acktime));
}

int CSvrLink::PushRowEx(TPUSHDEST *pushdests, int pdcount, ST_PACK *pack, char pushmode, int batchno, int acktime)
{
   int i;
   unsigned char sbuf[MAXMSG];
   RP_PUSHDATAH *ph;
   TPUSHDESTN *pd;
   unsigned short len;
   char szmsg[256];
   ST_PACKHEAD phead;
   ASSERT(pdcount>0);
   ph = (RP_PUSHDATAH *)sbuf;
   ph->pushmode = pushmode;
   ph->acktime = htonl(acktime);
   ph->dcount = htons(pdcount);
   len = sizeof(RP_PUSHDATAH);
   pd = (TPUSHDESTN *)(sbuf+len);
   for (i=0;i<pdcount;i++)
   {
      pd[i].SourceNo = htons(pushdests[i].SourceNo);
      pd[i].DestNo = htons(pushdests[i].DestNo);
      pd[i].FuncNo = htons(pushdests[i].FuncNo);
      pd[i].BatchNo = htonl(pushdests[i].BatchNo);
      len += sizeof(TPUSHDESTN);
   }
   memcpy(&phead,&head,sizeof(phead));
   //phead.userdata = (unsigned int)batchno;
   phead.recCount = 1;
   ModifyHead(&phead,sbuf+len);
   len += sizeof(phead);
   EncodeRow(&phead,pack,sbuf+len,&i,szmsg);
   len += i;
   return(SendMsg(MT_PUSHDATA,len,sbuf));   
}


int CSvrLink::ExtCall(int sourceno, int destno, int funcno, int batchno, int acktime, void *rdata, int rdlen, char *abuf, int &alen)
{
   int rtn;
   char szmsg[256];
   ST_PACKHEAD phead;
   xcdata.sno = sourceno;
   xcdata.dno = destno;
   xcdata.fno = funcno;
   xcdata.bno = batchno;

   DecodeHead((unsigned char *)rdata,rdlen,&phead,szmsg);
   phead.userdata = batchno;
   ModifyHead(&phead,(unsigned char *)rdata);

   if (acktime<=0)
   {
      acktime = 5;  // 缺省为5秒钟内得到应答，否则作为失败处理。。。以防止业务部分调用错误导致整个BUNIT处理失败或挂起
   }
   rtn = PushData(sourceno,destno,funcno,batchno,PM_ANSWER,acktime,rdata,rdlen);
   while (rtn==0)
   {
      rtn = RecvMsg(acktime*1000+1000);
      if (rtn>0)
      {
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_PUSHDATA)
         {
            // 有应答数据返回：
            alen = pmb->head.len;
            memcpy(abuf,pmb->data,alen);
            DecodeHead((unsigned char *)abuf,alen,&(xcdata.ahead),szmsg);
            // 为了正确提取外调功能的后续包（尤其对BCC能够支持并行多应用服务器架构），则采用
            if (xcdata.ahead.hook.queuename[0]>='0' && xcdata.ahead.hook.queuename[0]<='9'
               && xcdata.ahead.hook.queuetype>0)
            {
               // 属于KSBCC模式的XPACK协议：
               xcdata.fno = xcdata.ahead.hook.queuetype;
               // 包括能够处理被目标点转发后处理的请求
               if (0==xcdata.ahead.hook.hostname[0])
               {
                  int dno = atoi(xcdata.ahead.hook.hostname+1);
                  if (dno>0)
                  {
                     xcdata.dno = dno;
                  }
               }
               // m_bBCCADP:  2006-3-17 17:14:21
               else if (0!=xcdata.ahead.hook.hostname[10])
               {
                  int dno = atoi(xcdata.ahead.hook.hostname+10);
                  if (dno>0)
                  {
                     xcdata.dno = dno;
                  }
               }
               //////////////////////////////////////////////////////////////////////////
               
            }
            return(rtn);
         }
         else
         {
            DEBUG_RUNTIME_MSGOUT("ExtCall中间收到了非MT_PUSHDATA应答包，属于程序错误!");
            rtn = 0; // 继续读取数据，以便接收到正确的MT_PUSHDATA应答包
         }
      }
      else if (rtn==0)
      {
         return(-2);  // 等待应答数据超时，即自从向外发送了请求后，在acktime+1秒内没有接收到应答数据  
      }
   }
   return(-1); // 其他各种通讯方面的错误
}


int CSvrLink::ExtCall(int sourceno, int destno, int funcno, int batchno, int acktime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays)
{
   int rtn;
   char szmsg[256];
   xcdata.sno = sourceno;
   xcdata.dno = destno;
   xcdata.fno = funcno;
   xcdata.bno = batchno;

   rpack->head.userdata = batchno;
   if (acktime<=0)
   {
      acktime = 5;  // 缺省为5秒钟内得到应答，否则作为失败处理。。。以防止业务部分调用错误导致整个BUNIT处理失败或挂起
   }
   rtn = PushData(sourceno,destno,funcno,batchno,rpack,PM_ANSWER,acktime);
   while (rtn==0)
   {
      rtn = RecvMsg(acktime*1000+1000);
      if (rtn>0)
      {
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_PUSHDATA)
         {
            // 有应答数据返回：
            rtn = 0;
            DecodeBufWithArray((unsigned char *)pmb->data,pmb->head.len,apack,pArrays,&rtn,szmsg);
            memcpy(&xcdata.ahead,&(apack->head),sizeof(ST_PACKHEAD));
            //////////////////////////////////////////////////////////////////////////
            // 当为KSMBCC的时候：2005-9-11 18:40:49
            if (pmb->head.len>=rtn+sizeof(TPUSHDESTN))
            {
               // 新的KSMBCC的ExtCall模式：2005-9-11 14:11:25
               TPUSHDESTN *pd = (TPUSHDESTN *)(pmb->data+rtn);
               xcdata.sno = ntohs(pd->SourceNo);
               xcdata.dno = ntohs(pd->DestNo);
               xcdata.fno = ntohs(pd->FuncNo);
            }
            //////////////////////////////////////////////////////////////////////////

            if (apack->head.hook.queuetype>0)
            {
               xcdata.fno = apack->head.hook.queuetype;
            }            
            /* ****** Updated by CHENYH at 2005-9-11 18:39:15 ****** 
            else if (atoi(apack->head.hook.hostname)>0)
               xcdata.fno = atoi(apack->head.hook.hostname);
            *******************************************************/
            return(rtn);
         }
         else
         {
            DEBUG_RUNTIME_MSGOUT("ExtCall中间收到了非MT_PUSHDATA应答包，属于程序错误!");
            rtn = 0; // 继续读取数据，以便接收到正确的MT_PUSHDATA应答包
         }
      }
      else if (rtn==0)
      {
         return(-2);  // 等待应答数据超时，即自从向外发送了请求后，在acktime+1秒内没有接收到应答数据  
      }
   }
   return(-1); // 其他各种通讯方面的错误
}


int CSvrLink::ExtCallNext(int acktime, char *abuf, int &alen)
{
   ST_CPACK rpack;
   memcpy(&(rpack.head),&(xcdata.ahead),sizeof(ST_PACKHEAD));
   rpack.head.recCount = 0;
   rpack.head.firstflag = 0;
   alen = ModifyHead(&(rpack.head),(unsigned char *)abuf);
   if (xcdata.ahead.nextflag==0)
   {
      return(-3); // 表示已经取完了后续数据，不需要再提取了；
   }
   return(ExtCall(xcdata.sno,xcdata.dno,xcdata.fno,xcdata.bno,acktime,abuf,alen,abuf,alen));
}

int CSvrLink::ExtCallNext(int acktime, ST_CPACK *apack, ST_PACK *pArrays)
{
   //int rtn;
   if (xcdata.ahead.nextflag==0)
   {
      memcpy(&apack->head,&xcdata.ahead,sizeof(ST_PACKHEAD));
      apack->head.recCount = 0;
      return(-3); // 表示已经取完了后续数据，不需要再提取了；
   }
   ST_CPACK rpack;
   memcpy(&rpack.head,&xcdata.ahead,sizeof(ST_PACKHEAD));
   rpack.head.recCount = 0;
   rpack.head.retCode = 0;
   rpack.head.firstflag = 0;
   rpack.head.nextflag = 1;
   return(ExtCall(xcdata.sno,xcdata.dno,xcdata.fno,xcdata.bno,acktime,&rpack,apack,pArrays));
}

bool CSvrLink::CheckProcCancel()
{
   int rtn;
   MSGBUF *pmb;
   unsigned char *rframe;
   rtn = RecvMsg(0);
   if (rtn>=(int)(sizeof(MSGHEAD)))
   {
      pmb = GetRecvMsg();
      if (pmb->head.msgtype==MT_CMDCANCEL)
      {
         rframe = (unsigned char *)pmb->data;
         if (rframe[0]==iGRFrame)
            return(true);
      }      
   }
   return(false);   
}

int CSvrLink::SetAnswerMode(char iAMode)
{
   iAnswerMode = iAMode;
   return(SendMsg(MT_SETAMODE,sizeof(iAnswerMode),&iAnswerMode));
}



int CSvrLink::BCCLogOut(char logtype, int logid, int textlen, char *text, int datalen, void *data)
{
   unsigned char sbuf[MAXMSG];
   RP_BCCLOG *pbl = (RP_BCCLOG *)sbuf;
   unsigned short len;
   pbl->logtype = logtype;
   pbl->logid = htonl(logid);
   pbl->textlen = htons(textlen);
   memcpy(pbl->logtext,text,textlen+1);
   len = sizeof(RP_BCCLOG)+textlen;
   if (datalen>0)
   {
      memcpy(sbuf+len,data,datalen);
      len += datalen;
   }   
   return(SendMsg(MT_BCCLOG,len,sbuf));
}

void CSvrLink::ResetNormalCPack(ST_CPACK *pack, unsigned char nextflag, int recCount)
{
   memcpy(&(pack->head),&head,sizeof(head));
   pack->head.firstflag = 1;
   pack->head.nextflag = nextflag;
   pack->head.recCount = recCount;
   memset(pack->head.ParmBits,0,sizeof(pack->head.ParmBits));
   pack->head.retCode = 0;
   //CXPack *pXPack = (CXPack *)GetDefaultXPack();
   memset(&(pack->pack),0,((CXPack *)GetDefaultXPack())->GetPackLength());  
   //memset(&(pack->pack),0,sizeof(pack->pack));
}

int CSvrLink::SetMaxRow(int maxrows)
{
   maxrows = htonl(maxrows);
   return(SendMsg(MT_SETMAXROWS,sizeof(maxrows),&maxrows));
}

int CSvrLink::SetBUError(int errcode, char *szErrMsg)
{
   unsigned char sbuf[MAXMSG];
   RP_SETERROR *pse = (RP_SETERROR *)sbuf;
   unsigned short len;
   len = strlen(szErrMsg);
   pse->iErrorCode = htonl(errcode);
   if (len>255)
      len = 255;
   Strncpy(pse->szmsg,szErrMsg,len+1);
   return(SendMsg(MT_SETERROR,sizeof(RP_SETERROR)+len,sbuf));
}

int CSvrLink::SetAnswerTimeout(unsigned int atimeout)
{
   atimeout = htonl(atimeout);
   return(SendMsg(MT_SETTIMEOUT,sizeof(atimeout),&atimeout));
}


// 函数名: CSvrLink::ResetAnswerData
// 编程  : 陈永华 2004-3-24 21:43:47
// 描述  : 重置清除已经提交的应答数据，比如因为死锁造成重新执行的时候需要本功能
// 返回  : int 
int CSvrLink::ResetAnswerData()
{
   head.recCount = 0;
   return(SendMsg(MT_RESETANSWER,0,NULL));
}

bool CSvrLink::CheckLink()
{
   //return(linksock.CheckDataArrived(0)>=0);
   // 发送一个测试包数据上去，BCC则作为不能识别的包丢弃，不作处理
/* ****** Updated by CHENYH at 2008-7-15 11:10:13 ****** 
   return(SendMsg(MT_TESTLINK,0,NULL)>=0);
   // 为了能够在发送测试包的方式来检测连接是否正常
*/
   if (SendMsg(MT_TESTLINK,0,NULL)<0)
      return(false);
   if (RecvMsg(1000)>=(int)(sizeof(MSGHEAD)))
   {
      /* ****** Added by CHENYH at 2008-12-15 21:46:28 ****** 
      由于万一由于框架中调用了这个TESTLINK消息，导致这里收到的正好是GETREQ的请求处理包
      如果不处理，那么就完蛋了，BCC又不能因为这个而重复发送原来的GETREQ，存在风险的 */
      MSGBUF *pmb;
      pmb = GetRecvMsg();
      if (pmb->head.msgtype==MT_GETREQ)
      {
         // OK,have new request to process
         if (pmb->head.len>=sizeof(AP_REQUEST))
         {
            AP_REQUEST *prp = (AP_REQUEST *)(pmb->data);
            if (prp->iGRFrame==iGRFrame)
            {
               CallBPFunction(pmb);
               iGRFrame++;
            }
         }
      }
      /***************************************************/

      return(true);
   }
   return(false);
}




// 函数名: CSvrLink::SMOpenBlock
// 编程  : 陈永华 2005-7-4 15:52:14
// 描述  : 创建或打开一个命名共享内存块
// 返回  : int 
//          >=0: 成功，返回该共享内存的句柄号；
//          -1: 共享内存块（句柄）已经用完了
//          -2: 已经需要的共享内存块长度已经超过了BCC限定了
//          -3: 要求的长度超过已经分配的共享内存长度
//          -20: 等待超时，BCC没有能够在1秒之内响应
//          <100: 属于各类错误，-101:被对方正常关闭；-110/-111:对方非标准MSG协议口或数据不同步；-102:因为链路错误而被关闭；-103:在接收数据的时候，出错而被关闭
// 参数  : char *name : 共享内存块命名
// 参数  : unsigned int length: 共享内存块的长度
int CSvrLink::SMOpenBlock(char *name, unsigned int length)
{
   unsigned char sbuf[MAXMSG];
   RP_SMOPEN *pob;
   int rtn;
   pob = (RP_SMOPEN *)sbuf;
   memcpy(pob->name,name,sizeof(pob->name));
   pob->length = htonl(length);
   rtn = SendMsg(MT_SMOPEN,sizeof(RP_SMOPEN),sbuf);
   if (rtn<0) rtn -= 1000;  // 属于严重错误，断开了与BCC的连接，退出
   while (rtn==0)
   {
      // 发送共享打开消息成功：
      rtn = RecvMsg(1000);  // 1秒内应该该有结果了
      if (rtn>0)
      {
         // 收到结果：
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMOPEN)
         {
            // 收到的即为处理返回的值：
            /* ****** Updated by CHENYH at 2006-7-5 16:24:46 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            //>=0: 成功，返回该共享内存的句柄号；
            //-1: 共享内存块（句柄）已经用完了
            //-2: 已经需要的共享内存块长度已经超过了BCC限定了
            //-3: 要求的长度超过已经分配的共享内存长度            
            return(rtn);
         }
         else rtn = 0; // 继续等待对方的应答
      }
      else if (rtn==0)
      {
         // 等待超时，BCC没有能够在1秒之内响应
         rtn = -20;
      }
      else
      {
         // 出错了
         rtn -= 100;
      }      
   }
   return(rtn);
}


// 函数名: CSvrLink::SMWrite
// 编程  : 陈永华 2005-7-4 20:13:07
// 描述  : 写局部或全部数据到指定的共享内存块
// 返回  : int -2/-1000:共享内存句柄错误； 
//             -1:内存空间没有分配； 
//              0:写入位置offset超过已经分配的空间  
//             >0:写入数据长度（如果该值<指定的值，即即为结束）
//             -20: 等待超时，BCC没有能够在1秒之内响应
//             <-100: 属于各类错误：
//             -101:被对方正常关闭；
//             -110/-111:对方非标准MSG协议口或数据不同步；
//             -102:因为链路错误而被关闭；
//             -103:在接收数据的时候，出错而被关闭
//             -1001: 长度过长，每次的长度length<=8180
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
// 参数  : void *wdata：[IN] 写覆盖的数据块
// 参数  : unsigned int offset：[IN] 数据存放在共享内存块的偏移位置
// 参数  : unsigned int length：[IN] 数据块长度，注意<8180
// 参数  : bool bWLock: [IN] 是否需要加锁写
int CSvrLink::SMWrite(int smh, void *wdata, unsigned int offset, unsigned int length, bool bWLock)
{
   unsigned char sbuf[MAXMSG];
   RP_SMWRITE *pwr;
   int rtn;
   if (smh<0)
      return(-1000); // 共享内存块句柄错误，参见SMOpenBlock
   pwr = (RP_SMWRITE *)sbuf;
   if (length>MAXMSG-sizeof(RP_SMWRITE))
      return(-1001); // 长度过长，每次的长度length<=8180
   pwr->handle = htonl(smh);
   pwr->offset = htonl(offset);
   pwr->length = htonl(length);
   pwr->lock = bWLock?1:0;
   memcpy(sbuf+sizeof(RP_SMWRITE),wdata,length);
   rtn = SendMsg(MT_SMWRITE,sizeof(RP_SMWRITE)+length,sbuf);
   if (rtn<0) rtn -= 1000;  // 属于严重错误，断开了与BCC的连接，退出
   while (rtn==0)
   {
      // 发送写共享内存块消息成功：
      rtn = RecvMsg(1000);  // 1秒内应该该有结果了
      if (rtn>0)
      {
         // 收到结果：
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMWRITE)
         {
            // 收到的即为处理返回的值：
            /* ****** Updated by CHENYH at 2006-7-5 16:26:32 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            // 返回  : int -2:共享内存句柄错误； 
            //             -1:内存空间没有分配； 
            //              0:写入位置offset超过已经分配的空间  
            //             >0:写入数据长度（如果该值<指定的值，即即为结束）
            return(rtn);
         }
         else rtn = 0; // 继续等待对方的应答
      }
      else if (rtn==0)
      {
         // 等待超时，BCC没有能够在1秒之内响应
         rtn = -20;
      }
      else
      {
         // 出错了
         rtn -= 100;
      }      
   }
   return(rtn);
}


// 函数名: CSvrLink::SMRead
// 编程  : 陈永华 2005-7-6 10:21:43
// 描述  : 从指定共享内存空间中读取局部或全部的数据
// 返回  : int -2/-1000:共享内存句柄错误； 
//             -1:内存空间没有分配； 
//              0:读取位置offset超过已经分配的空间  
//             >0:读取数据长度（如果该值<指定的值，即即为结束）
//             -20: 等待超时，BCC没有能够在1秒之内响应
//             <-100: 属于各类错误：
//             -101:被对方正常关闭；
//             -110/-111:对方非标准MSG协议口或数据不同步；
//             -102:因为链路错误而被关闭；
//             -103:在接收数据的时候，出错而被关闭
//             -1001: 长度过长，每次的长度length<=8180
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
// 参数  : void *rbuf：[OUT] 读取数据缓存
// 参数  : unsigned int offset：[IN] 读取数据存放在共享内存块的偏移位置
// 参数  : unsigned int rblen：[IN] 读取数据块长度，注意<8180
// 参数  : bool bRLock: [IN] 是否需要加锁读
int CSvrLink::SMRead(int smh, void *rbuf, unsigned int offset, unsigned int rblen, bool bRLock)
{
   unsigned char sbuf[MAXMSG];
   RP_SMWRITE *pwr;  // 这里也是使用写结构进行数据交换
   int rtn;
   if (smh<0)
      return(-1000); // 共享内存块句柄错误，参见SMOpenBlock
   pwr = (RP_SMWRITE *)sbuf;
   if (rblen>MAXMSG-sizeof(RP_SMWRITE))
      return(-1001); // 长度过长，每次的长度length<=8180
   pwr->handle = htonl(smh);
   pwr->offset = htonl(offset);
   pwr->length = htonl(rblen);
   pwr->lock = bRLock?1:0;
   rtn = SendMsg(MT_SMREAD,sizeof(RP_SMWRITE),sbuf);
   if (rtn<0) rtn -= 1000;  // 属于严重错误，断开了与BCC的连接，退出
   while (rtn==0)
   {
      // 发送读共享内存块消息成功：
      rtn = RecvMsg(1000);  // 1秒内应该该有结果了
      if (rtn>0)
      {
         // 收到结果：
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMREAD)
         {
            // 收到的即为处理返回的值：
            /* ****** Updated by CHENYH at 2006-7-5 16:27:38 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            // 返回  : int -2:共享内存句柄错误； 
            //             -1:内存空间没有分配； 
            //              0:读取位置offset超过已经分配的空间  
            //             >0:读取数据长度（如果该值<指定的值，即即为结束）
            if (rtn>0)
            {
               memcpy(rbuf,pmb->data+sizeof(int),rtn);
            }
            return(rtn);
         }
         else rtn = 0; // 继续等待对方的应答
      }
      else if (rtn==0)
      {
         // 等待超时，BCC没有能够在1秒之内响应
         rtn = -20;
      }
      else
      {
         // 出错了
         rtn -= 100;
      }      
   }
   return(rtn);
}


// 函数名: CSvrLink::SMInterlockedAdd
// 编程  : 陈永华 2005-7-6 11:08:58
// 描述  : 在共享内存块中指定的位置作为整数进行独占加法运算
// 返回  : int 返回独占加法运算后的值。
//          为0x80000000，可能属于系统或参数错误；
//          为0x80000001，则可能属于参数错误；
//          但不建议用这个作为判断
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
// 参数  : unsigned int offset：[IN] 数据的偏移位置
// 参数  : int increment：[IN] 增量参数
int CSvrLink::SMInterlockedAdd(int smh, unsigned int offset, int increment)
{
   unsigned char sbuf[MAXMSG];
   RP_SMINTADD *pia;
   int rtn;
   if (smh<0)
      return(SMIA_BADP); // 共享内存块句柄错误，参见SMOpenBlock
   pia = (RP_SMINTADD *)sbuf;
   pia->handle = htonl(smh);
   pia->offset = htonl(offset);
   pia->increment = htonl(increment);
   rtn = SendMsg(MT_SMINTADD,sizeof(RP_SMINTADD),sbuf);
   if (rtn<0) rtn = SMIA_ERR;
   while (rtn==0)
   {
      // 发送成功：
      rtn = RecvMsg(1000);  // 1秒内应该该有结果了
      if (rtn>0)
      {
         // 收到结果：
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMINTADD)
         {
            // 收到的即为处理返回的值：
            /* ****** Updated by CHENYH at 2006-7-5 16:27:38 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            
            return(rtn);
         }
         else rtn = 0; // 继续等待对方的应答
      }
      else break;
   }
   return(SMIA_ERR);
}


// 函数名: CSvrLink::SMLock
// 编程  : 陈永华 2005-7-6 16:07:57
// 描述  : 对指定的共享内存块进行本BU占用加锁，阻塞模式，直到成功或失败
// 返回  : int -2/-1000:共享内存句柄错误； 
//             1: 加锁成功
//             <-100: 属于各类错误：
//                -101:被对方正常关闭；
//                -110/-111:对方非标准MSG协议口或数据不同步；
//                -102:因为链路错误而被关闭；
//                -103:在接收数据的时候，出错而被关闭
//                -1001: 长度过长，每次的长度length<=8180
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
int CSvrLink::SMLock(int smh)
{
   return(SMLockCmd(smh,MT_SMLOCK));
}


// 函数名: CSvrLink::SMTryLock
// 编程  : 陈永华 2005-7-6 20:25:17
// 描述  : 试着对指定的内存块进行加锁，不阻塞，立即返回
// 返回  : int -2/-1000:共享内存句柄错误； 
//             0: 不能立即加锁，该资源被其他BU加锁着
//             1: 加锁成功
//             <-100: 属于各类错误：
//                -101:被对方正常关闭；
//                -110/-111:对方非标准MSG协议口或数据不同步；
//                -102:因为链路错误而被关闭；
//                -103:在接收数据的时候，出错而被关闭
//                -1001: 长度过长，每次的长度length<=8180
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
int CSvrLink::SMTryLock(int smh)
{
   return(SMLockCmd(smh,MT_SMTRYLOCK));
}


// 函数名: CSvrLink::SMUnlock
// 编程  : 陈永华 2005-7-6 20:28:47
// 描述  : 对本BU加锁的共享内存块解锁
// 返回  : int -2/-1000:共享内存句柄错误； 
//             1: 解锁成功
//             <-100: 属于各类错误：
//                -101:被对方正常关闭；
//                -110/-111:对方非标准MSG协议口或数据不同步；
//                -102:因为链路错误而被关闭；
//                -103:在接收数据的时候，出错而被关闭
//                -1001: 长度过长，每次的长度length<=8180
// 参数  : int smh：[IN] 共享内存块句柄，参见SMOpenBlock返回
//          注：由于目前为了整个系统稳定考虑，目前一个BU同时只能对一个
//             共享内存块进行加锁，如果对一个试图加锁的时候，
//             另外已经被加锁的会立即被释放
int CSvrLink::SMUnlock(int smh)
{
   return(SMLockCmd(smh,MT_SMUNLOCK));
}


// 函数名: CSvrLink::SMLockCmd
// 编程  : 陈永华 2005-7-6 14:58:52
// 描述  : 这仅仅为了加解锁的命令内部调用，来简化程序
// 返回  : int 
// 参数  : int smh
// 参数  : int lockmode
int CSvrLink::SMLockCmd(int smh, short lockmode)
{
   int rtn;
   if (smh<0)
      return(-1000); // 共享内存块句柄错误，参见SMOpenBlock
   smh = htonl(smh);
   rtn = SendMsg(lockmode,sizeof(smh),&smh);
   if (rtn<0) rtn -= 1000;  // 属于严重错误，断开了与BCC的连接，退出
   while (rtn==0)
   {
      rtn = RecvMsg(1000);
      if (rtn>0)
      {
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==lockmode)
         {
            /* ****** Updated by CHENYH at 2006-7-5 16:27:38 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            
            return(rtn);
         }
         else rtn = 0; // 继续
      }
      else if (rtn==0)
      {
         // 继续，比如锁等待
      }
      else 
      {
         // 接收时候出错了
         rtn -= 100;
      }
   }
   return(rtn);
}

int CSvrLink::CallBPFunction(MSGBUF *pmb)
{
   AP_REQUEST *preq;
   ST_CPACK rpack={0};
   /* ****** Updated by CHENYH at 2006-3-23 0:37:37 ****** 
   为了能够为具体业务处理模块留出足够的堆栈空间，因此这里采用动态分配空间方式分配
   ST_PACK pArrays[MAXROW]={0};   // 819200 / 在VC下缺省的stack空间本来也就1M (1048576)
   *******************************************************/
   ST_PACK *pArrays; 
   int recs;
   int rtn;
   char szMsg[256];
   char *rdata = pmb->data+sizeof(AP_REQUEST);
   int rdlen = pmb->head.len-sizeof(AP_REQUEST);
   preq = (AP_REQUEST *)(pmb->data);
   ruserid.SourceNo = ntohs(preq->SourceNo); 
   memcpy(&(ruserid.syshead),&(preq->syshead),sizeof(ruserid.syshead));

   if (pProcess!=NULL)
   {
      if (DecodeHead((unsigned char *)rdata,rdlen,&head,szMsg)==sizeof(ST_PACKHEAD))
      {
         memcpy(&reqhead,&head,sizeof(ST_PACKHEAD)); 

         memset(head.ParmBits,0,sizeof(head.ParmBits));  // 将结果集位图清空      
         head.recCount = 0;  // Reset the recCount

         iLastReqType = head.RequestType;
         iAnswerMode = iDefaultAnswerMode;
         eMsg[0]='\0';
         iLastRetCode = 0;
         rtn = (*pProcess)(&ruserid,rdata,rdlen,&iLastRetCode,eMsg);
         DataDone(iLastRetCode,eMsg);
         return(rtn);
      }
   }

   // 2006-3-23 0:56:40 采用动态分配，以少占用堆栈空间
   pArrays = (ST_PACK *)malloc(((CXPack *)GetDefaultXPack())->GetPackLength()*MAXROW);
   if (DecodeBufWithArray((unsigned char *)rdata,rdlen,&rpack,pArrays,&recs,szMsg)>0)
   {
      int fno;
      ASSERT(rpack.head.firstflag==1);  // 只有首包提交下来的。。。。
      memcpy(&reqhead,&(rpack.head),sizeof(ST_PACKHEAD));  // 将请求包头记录下来 2005-9-21 17:35:06

      memcpy(&head,&(rpack.head),sizeof(head));
      
      memset(head.ParmBits,0,sizeof(head.ParmBits));  // 将结果集位图清空
      
      head.recCount = 0;  // Reset the recCount
      
      iLastReqType = rpack.head.RequestType;
      iAnswerMode = iDefaultAnswerMode;
      
      eMsg[0]='\0';
      iLastRetCode = 0;
      
      fno = FindBPFunction(rpack.head.RequestType);
      if (fno>=0 && g_BDefines[fno].pFunc!=NULL)
      {
         unsigned int t1=GetTickCount();
         
         // OK,have found the process function:
#ifdef TESTINFO
         sprintf(szMsg,"Begin to call REQ%u <%s>!",
            rpack.head.RequestType,
            g_BDefines[fno].szRTName);
         DEBUG_RUNTIME_MSGOUT(szMsg);
#endif
         rtn = (*pCallBDFunc)(fno,&ruserid,&rpack,pArrays,&iLastRetCode,eMsg);
         // 如果需要统计功能处理能力，在这里加上。。。
         t1 = tc2_tc1(GetTickCount(),t1);
         DataDone(iLastRetCode,eMsg);
         if (iLastRetCode==0)
         {
            g_BDefines[fno].nSuccess++;
            g_BDefines[fno].dTakentime += t1;
            if (g_BDefines[fno].nSuccess==1)
            {
               g_BDefines[fno].nTt_max = g_BDefines[fno].nTt_min = t1;
            }
            else
            {
               if (g_BDefines[fno].nTt_max<t1)
                  g_BDefines[fno].nTt_max=t1;
               if (g_BDefines[fno].nTt_min>t1)
                  g_BDefines[fno].nTt_min = t1;
            }
         }
         else
            g_BDefines[fno].nFail++;
         //return(rtn);
      }
      else
      {
         iLastReqType = 0;
         iLastRetCode = 0;
         sprintf(szMsg,"BCC提交的请求<%u>在本业务单元中没有对应的处理定义!",
            rpack.head.RequestType);
         DEBUG_RUNTIME_MSGOUT(szMsg);
         rtn = -2;
      }
   }
   else 
   {
      DEBUG_RUNTIME_MSGOUT(szMsg);
      rtn = -1;
   }
   free(pArrays);
   return(rtn);
}



int CSvrLink::IntCall(char *szBUGroupID, int waittime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays)
{
   int rtn;
   unsigned short len;
   unsigned char sbuf[MAXMSG];
   char szmsg[256]={0};
   RP_INTCALLH *pic = (RP_INTCALLH *)sbuf;
   pic->waittime = htonl(waittime);
   strncpy(pic->szBUGroupID,szBUGroupID,MAXBUGRPID);
   if (rpack->head.recCount>1)
   {
      rpack->head.recCount = 1;
   }
   EncodeBuf(rpack,sbuf+sizeof(RP_INTCALLH),&rtn,szmsg);
   len = rtn+sizeof(RP_INTCALLH);
   rtn=SendMsg(MT_INTCALL,len,sbuf);
   while (rtn==0)
   {
      rtn = RecvMsg(waittime*1000+1000);
      if (rtn>0)
      {
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_PUSHDATA)
         {
            // 有应答数据返回：
            rtn = 0;
            DecodeBufWithArray((unsigned char *)pmb->data,pmb->head.len,apack,pArrays,&rtn,szmsg);
            //memset(&xcdata,0,sizeof(xcdata));  // 清空
            memcpy(&(xcdata.ahead),&(apack->head),sizeof(ST_PACKHEAD));
            if (pmb->head.len>=rtn+sizeof(TPUSHDESTN))
            {
               TPUSHDESTN *pd = (TPUSHDESTN *)(pmb->data+rtn);
               xcdata.sno = ntohs(pd->SourceNo);
               xcdata.dno = ntohs(pd->DestNo);
               xcdata.fno = ntohs(pd->FuncNo);
            }
            return(rtn);
         }
         else
         {
            DEBUG_RUNTIME_MSGOUT("IntCall中间收到了非MT_INTCALL应答包，属于程序错误!");
            rtn = 0; // 继续读取数据，以便接收到正确的MT_INTCALL应答包
         }
      }
      else if (rtn==0)
      {
         return(-2);  // 等待应答数据超时，即自从向外发送了请求后，在waittime+1秒内没有接收到应答数据  
      }
   }
   return(-1); // 其他各种通讯方面的错误
}

int CSvrLink::IntCallNext(int waittime, ST_CPACK *apack, ST_PACK *pArrays)
{
   if (xcdata.ahead.nextflag==0)
   {
      memcpy(&apack->head,&(xcdata.ahead),sizeof(ST_PACKHEAD));
      apack->head.recCount = 0;
      return(-3);
   }
   ST_CPACK rpack;
   memcpy(&(rpack.head),&(xcdata.ahead),sizeof(ST_PACKHEAD));
   rpack.head.recCount = 0;
   rpack.head.retCode = 0;
   rpack.head.firstflag = 0;
   rpack.head.nextflag = 1;
   return(IntCall("",waittime,&rpack,apack,pArrays));
}

int CSvrLink::RACall(int acktime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays)
{
   return(ExtCall(INTSOURCENO,0xFFFF,0,0,acktime,rpack,apack,pArrays));
}

int CSvrLink::RACallNext(int acktime, ST_CPACK *apack, ST_PACK *pArrays)
{
   return(ExtCallNext(acktime,apack,pArrays));
}

int CSvrLink::IntTransfer(char *szBUGroupID, ST_CPACK *rpack, ST_PACK *pArrays)
{
   int rtn;
   unsigned short len;
   unsigned char sbuf[MAXMSG]={0};
   char szmsg[256]={0};
   RP_INTTRANSFER *pit = (RP_INTTRANSFER *)sbuf;
   strncpy(pit->szBUGroupID,szBUGroupID,MAXBUGRPID);
   if (rpack!=NULL)
   {
      if (rpack->head.recCount>1 && pArrays==NULL)
      {
         rpack->head.recCount = 1;
      }
      EncodeBufArray(rpack,pArrays,sbuf+sizeof(RP_INTTRANSFER),&rtn,szmsg);
      len = rtn+sizeof(RP_INTTRANSFER);
   }
   else
   {
      len = sizeof(RP_INTTRANSFER);
   }
   return(SendMsg(MT_INTTRANSFER,len,sbuf));
}

int CSvrLink::ExtTransfer(unsigned short destno, unsigned short funcno, ST_CPACK *rpack, ST_PACK *pArrays)
{
   int rtn;
   unsigned short len;
   unsigned char sbuf[MAXMSG]={0};
   char szmsg[256]={0};
   RP_EXTTRANSFER *pxt = (RP_EXTTRANSFER *)sbuf;
   pxt->DestNo = htons(destno);
   pxt->FuncNo = htons(funcno);
   if (rpack!=NULL)
   {
      if (rpack->head.recCount>1 && pArrays==NULL)
      {
         rpack->head.recCount = 1;
      }
      EncodeBufArray(rpack,pArrays,sbuf+sizeof(RP_EXTTRANSFER),&rtn,szmsg);
      len = rtn+sizeof(RP_EXTTRANSFER);
   }
   else
   {
      len = sizeof(RP_EXTTRANSFER);
   }
   return(SendMsg(MT_EXTTRANSFER,len,sbuf));
}

int CSvrLink::RATransfer(ST_CPACK *rpack, ST_PACK *pArrays)
{
   return(ExtTransfer(0xFFFF,0,rpack,pArrays));
}



void CSvrLink::GetAnswerHead(ST_PACKHEAD *phead)
{
   memcpy(phead,&head,sizeof(ST_PACKHEAD));
}

void CSvrLink::GetRequestHead(ST_PACKHEAD *phead)
{
   memcpy(phead,&reqhead,sizeof(ST_PACKHEAD));
}

int CSvrLink::Error_Deal(int retcode, char *omsg, char *pFormat, ...)
{
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(Err_Deal(omsg,retcode));
}

int CSvrLink::BCCMsgLogOut(int logid, char *pFormat, ...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(BCCLogOut(LT_MSG,logid,strlen(omsg),omsg));
}

int CSvrLink::SetCol(TRUSERID *handle, ...)
{
	va_list ap;
	int arg;
   ST_PACKHEAD head;
   memset(&head,0,sizeof(head));
	va_start(ap, handle);

   while ((arg=va_arg(ap,int))>=0)
	{
		SetParmBit( &head, arg);
	}
	va_end(ap);
   return(SetCol(handle,head.ParmBits));
}

// 不能用这种方式检查，因为万一BCC正在向BU提交请求，那么请求数据就会被flush掉
//DEL bool CSvrLink::CheckLinkEx()
//DEL {
//DEL    int rtn;
//DEL    rtn = SendMsg(MT_TESTLINKEX,0,NULL);
//DEL    if (rtn>=0)
//DEL    {
//DEL       rtn = RecvMsg(1000);
//DEL       if (rtn>0)
//DEL       {
//DEL          return(GetRecvMsg()->head.msgtype==MT_TESTLINKEX);
//DEL       }
//DEL    }
//DEL    return(false);
//DEL }


MSGBUF * CSvrLink::CheckBCCMsg(int timeout)
{
   int rtn = RecvMsg(timeout);
   if (rtn>=(int)(sizeof(MSGHEAD)))
   {
      return(GetRecvMsg());
   }
   return(NULL);
}
