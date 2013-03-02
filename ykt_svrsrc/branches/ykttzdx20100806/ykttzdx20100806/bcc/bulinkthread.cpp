// bulinkthread.cpp: implementation of the CBULinkThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "comstru.h"
#include "mypub.h"
#include "tcp.h"
#include "sysgvars.h"
#include "bulinkthread.h"
#include "MWThread.h"
#include "drtp_di.h"   // reverse(...)
#include "KSLog.h"



void ResetMsgHead(MSGHEAD *phead,short msgtype,unsigned short msglen)
{
   phead->msgid = LMSGID;
   phead->msgtype = msgtype;
   phead->len = msglen;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define MAXROW      100

CBULinkThread::CBULinkThread()
{
   iStep = BULS_NOTSTART;
   iqueueno = 1;
   memset(szBUGroupID,0,sizeof(szBUGroupID));
   iLinkTime = 0;
   iLastSendTime = 0;
   iBURFrame = 0;
   iLastReqType = 0;
   SourceNo = 0;
   ad_ksfseg = 0;
   ad_dklen = 0;
   maxrows = MAXROW;
   memset(&head,0,sizeof(head));
}

CBULinkThread::~CBULinkThread()
{

}



bool CBULinkThread::IsFree()
{
   return(linksock.IsFree());
}

void CBULinkThread::ToLink()
{
   // BU Link to the BCC:
   if (iStep==BULS_NOTSTART)
   {
      //linksock.Close();
      iStep = BULS_NOTREADY;
      CreateThread();
   }
   iStep = BULS_TOLINK;
}



int CBULinkThread::Run()
{
   while (g_Vars.g_bToExit==false)
   {
      switch (iStep)
      {
      case BULS_NOTREADY:
         mysleep(100);
         break;
      case BULS_TOLINK:
         if (LinkWithBU())
         {
            g_LogFile.WriteLogEx(200,"BULink(%d)建立了正常的连接，开始正式工作!",iID);
            iStep = BULS_LINKOK;
         }
         else
         {
            iStep = BULS_NOTREADY;
         }
         break;
      case BULS_LINKOK:
      case BULS_WAITREQ:
      case BULS_REQPROC:
         Recv_Processing();
         break;
      default:
         linksock.Close();
//         iStep = BULS_NOTREADY;
         break;
      }
      if (linksock.IsFree() && iStep!=BULS_NOTREADY)
      {
         g_LogFile.WriteLogEx(200,"本BULink(%d)停止工作!",iID);
         iStep = BULS_NOTREADY;
      }
   }
   linksock.Close();
   g_LogFile.WriteLogEx(100,"BULinkThread[%d]退出!",iID);
   iStep = BULS_NOTSTART;
   return(0);
}

bool CBULinkThread::LinkWithBU()
{
   MSGBUF *pmb;

   memset(&head,0,sizeof(head));
   iLastReqType = 0;
   memset(LastRData,0,sizeof(AP_REQUEST));  // 清除上次发送的数据包标记，尤其使得其中的iGRFrame=0
   iBURFrame = 0;

   while (g_Vars.g_bToExit==false)
   {
      int rtn;
      rtn = RecvMsg(1000);
      if (rtn>0 && rtn>=(int)sizeof(MSGHEAD))
      {
         pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_LINKBEGIN && pmb->head.len>=sizeof(RP_LINKBEGIN))
         {
            if (AnswerLinkBegin(pmb))
            {
               return(true);
            }
            else break;
         }
      }
      else break;  // recv error or timeout ... 不正常的连接
   }
   linksock.Close();
   iStep = BULS_NOTREADY;
   return(false);
}


// 函数名: CBULinkThread::RecvMsg
// 编程  : 陈永华 2004-2-15 22:22:51
// 描述  : 按照MSG协议接收数据
// 返回  : int >0:接收到正常数据包；0:超时；-1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；-3:在接收数据的时候，出错而被关闭
// 参数  : int timeout
int CBULinkThread::RecvMsg(int timeout)
{
   MSGBUF *pMsgBuf=(MSGBUF *)buf;
   MSGHEAD *phead = (MSGHEAD *)buf;
   int rtn;
   bool bReverse;
   rtn = linksock.Recv(buf,sizeof(MSGHEAD),timeout);
   if (rtn!=sizeof(MSGHEAD))
      return(rtn);  // 接收时候出错，或超时
   if (phead->msgid==RMSGID)
   {
      bReverse = true;
      reverse(&(phead->msgid),sizeof(phead->msgid));
      reverse(&(phead->msgtype),sizeof(phead->msgtype));
      reverse(&(phead->len),sizeof(phead->len));
   }
   else
      bReverse = false;
   if (phead->msgid!=LMSGID || phead->len>MAXMSG)
   {
      // 属于不正常的MSG，关闭端口，重新连接。。。
      // 或者数据流不同步，通过重新连接进行同步。。。
      DEBUG_RUNTIME_MSGOUT("属于不正常的MSG或者数据流不同步，关闭端口，重新连接\n");
      linksock.Close();
      return(-11);
   }
   if (phead->len>0)
   {
      rtn = linksock.Recv(pMsgBuf->data,phead->len,5000);  // 一直等待到接收到后续数据，或出错，或5秒钟超时
      if (rtn!=phead->len)
      {
         linksock.Close();
         return(rtn); // 接收时候出错，或超时
      }
   }
   return(phead->len+sizeof(MSGHEAD));
}


// 函数名: CBULinkThread::SendMsg
// 编程  : 陈永华 2004-2-15 22:28:06
// 描述  : 以MSG格式发送消息数据给调度中心
// 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
// 参数  : short msgtype ：IN 发送的消息类型
// 参数  : unsigned short msglen ：IN 消息体数据长度
// 参数  : void *MSGBUF ： IN 消息数据缓存
int CBULinkThread::SendMsg(short msgtype, unsigned short msglen, void *MSGBUF)
{
   int rtn;
   MSGHEAD *phead;
   char buf[MAXMSG+sizeof(MSGHEAD)];

   phead = (MSGHEAD *)buf;
   ResetMsgHead(phead,msgtype,msglen);
   if (msglen>0)
   {
      memcpy(buf+sizeof(MSGHEAD),MSGBUF,msglen);
   }
   rtn = linksock.Send(buf,sizeof(MSGHEAD)+msglen);
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

MSGBUF * CBULinkThread::GetRecvMsg()
{
   return((MSGBUF *)buf);
}

bool CBULinkThread::IsWaitReqStep()
{
   if (linksock.IsFree()==false
      && iStep==BULS_WAITREQ)
      return(true);
   else
      return(false);
}

int CBULinkThread::Recv_Processing()
{
   int rtn;
   MSGBUF *pmb;

/* ****** Updated by CHENYH at 2004-4-5 13:48:56 ****** 
   由于类似BULogOut等函数的特殊使用，可能会导致数据超界，特别扩展其长度到
   8K，并且其实例也就是几个BU连接，不会大量消耗内存
   char szmsg[256];
*/
   char szmsg[8192];
   
   rtn = RecvMsg(1000);
   if (rtn>0 && rtn>=(int)sizeof(MSGHEAD))
   {
      pmb = GetRecvMsg();
      switch (pmb->head.msgtype)
      {
      case MT_LINKBEGIN:
         if (pmb->head.len>=sizeof(RP_LINKBEGIN))
         {
            ASSERT(iStep==BULS_NOTREADY||iStep==BULS_TOLINK||iStep==BULS_LINKOK);
            if (AnswerLinkBegin(pmb))
            {
               iStep = BULS_LINKOK;
            }
         }
         else
         {
            sprintf(szmsg,"BULINK PERROR:MT_LINKBEGIN msg_len(%u)<sizeof(RP_LINKBEGIN)(%u)",
               pmb->head.len,
               sizeof(RP_LINKBEGIN));
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         break;
      case MT_GETREQ:
         if (g_MWThread.bToWriteAppInfo)
         {
            g_MWThread.bToWriteAppInfo = false;
            SendMsg(WRITEAPPINFO,0,NULL);
         }
         else if (pmb->head.len>=sizeof(RP_REQUEST))
         {
            GetReq(pmb->head.len,pmb->data,szmsg);
         }
         else
         {
            sprintf(szmsg,"BULINK PERROR:MT_GETREQ msg_len(%u)<sizeof(RP_REQUEST)(%u)",
               pmb->head.len,sizeof(RP_REQUEST));
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         break;
      case MT_SETAMODE:
         if (pmb->head.len>0)
         {
            SetAMode(pmb->data);
         }
         //iAnswerMode = pmb->data[0];
         break;
      case MT_SETCOL:
         if (pmb->head.len>=sizeof(head.ParmBits))
         {
            SetCol(pmb->data);
         }
         else
         {
            sprintf(szmsg,"BULINK PERROR:MT_SETCOL msg_len(%u)<sizeof(head.ParmBits)(%u)",
               pmb->head.len,sizeof(head.ParmBits));
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         if (iStep!=BULS_REQPROC)
         {
            DEBUG_RUNTIME_MSGOUT("BUERROR:可能BU与BCC不协调，在收到MT_SETCOL的时候，BCC还没有发送请求数据?");
         }
         break;
      case MT_PUTROWDATA:
         if (iStep!=BULS_REQPROC)
         {
            DEBUG_RUNTIME_MSGOUT("BUERROR:可能BU与BCC不协调，在收到MT_PUTROWDATA的时候，BCC还没有发送请求数据?");
         }
         if (ad_dklen<0||ad_ksfseg<0)
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_PUTROWDATA的时候，BCC还没有收到MT_SETCOL?功能号(%u)",iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         if (pmb->head.len<=0)
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_PUTROWDATA的时候，ROWDATA长度为0，功能号(%u)",iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         else
         {
            PutRowData(pmb->head.len,pmb->data);
         }
         break;
      case MT_ANSDATA:
         if (iStep!=BULS_REQPROC)
         {
            DEBUG_RUNTIME_MSGOUT("BUERROR:可能BU与BCC不协调，在收到MT_ANSDATA的时候，BCC还没有发送请求数据?");
         }
         if (ad_dklen<0||ad_ksfseg<0)
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_ANSDATA的时候，BCC还没有收到MT_SETCOL?功能号(%u)",iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         if (pmb->head.len<sizeof(RP_ANSDATA))
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_ANSDATA的时候，数据长度(%u)<sizeof(RP_ANSDATA)(%u)，功能号(%u)",
               pmb->head.len,sizeof(RP_ANSDATA),iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         else
         {
            AnswerData(pmb->head.len,pmb->data,szmsg);
         }
         break;
      case MT_ANSDATAEX:
         if (pmb->head.len>sizeof(RP_ANSDATAEXH))
         {
            AnswerDataEx(pmb->head.len,pmb->data,szmsg);
         }
         else
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_ANSDATAEX的时候，数据长度(%u)<=sizeof(RP_ANSDATAEXH)(%u)，功能号(%u)",
               pmb->head.len,sizeof(RP_ANSDATAEXH),iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         break;
      case MT_PUSHDATA:
         if (pmb->head.len>=sizeof(RP_PUSHDATAH)+sizeof(TPUSHDESTN))
         {
            PushData(pmb->head.len,pmb->data,szmsg);
         }
         else
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_PUSHDATA的时候，数据长度(%u)<sizeof(RP_PUSHDATAH)+sizeof(TPUSHDESTN)(%u)，功能号(%u)",
               pmb->head.len,sizeof(RP_PUSHDATAH)+sizeof(TPUSHDESTN),iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         break;
      case MT_PUTROW:
         if (iStep!=BULS_REQPROC)
         {
            DEBUG_RUNTIME_MSGOUT("BUERROR:可能BU与BCC不协调，在收到MT_PUTROW的时候，BCC还没有发送请求数据?");
         }
         if (ad_dklen<0||ad_ksfseg<0)
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_PUTROW的时候，BCC还没有收到MT_SETCOL?功能号(%u)",iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);
         }
         if (pmb->head.len<sizeof(RP_PUTROW))
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_PUTROW的时候，数据长度(%u)<sizeof(RP_PUTROW)，功能号(%u)",
               pmb->head.len,iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         else
         {
            PutRow(pmb->head.len,pmb->data,szmsg);
         }
         break;
      case MT_DATADONE:
         if (iStep!=BULS_REQPROC)
         {
            DEBUG_RUNTIME_MSGOUT("BUERROR:可能BU与BCC不协调，在收到MT_DATADONE的时候，BCC还没有发送请求数据?");
         }
         if (pmb->head.len<sizeof(RP_DATADONE))
         {
            sprintf(szmsg,"BUERROR:BU与BCC不协调，在收到MT_DATADONE的时候，数据长度(%d)<sizeof(RP_DATADONE)，功能号(%u)",
               pmb->head.len,iLastReqType);
            DEBUG_RUNTIME_MSGOUT(szmsg);            
         }
         else
         {
            DataDone(pmb->head.len,pmb->data,szmsg);
         }
         break;
      case MT_BCCLOG:
         if (pmb->head.len>=sizeof(RP_BCCLOG))
         {
            BULogOut(pmb->head.len,pmb->data,szmsg);
         }
         break;
      case MT_SETMAXROWS:
         if (pmb->head.len>=sizeof(int))
         {
            int rows = ntohl(*(int *)pmb->data);
            if (rows>0 && rows<=MAXROW)
            {
               maxrows = rows;
            }
         }
         break;
      case MT_RESETANSWER:
         ResetAnswerData();
         break;
      case MT_SETERROR:
         if (pmb->head.len>=sizeof(RP_SETERROR))
         {
            SetBUError(pmb->head.len,(RP_SETERROR *)pmb->data,szmsg);
         }
         break;
      case MT_SETTIMEOUT:  // 20040322: CYH
         if (pmb->head.len>=sizeof(unsigned int))
         {
            memcpy(head.hook.hostname+20,pmb->data,sizeof(unsigned int));
         }
         break;
      default:
         break;
      }
   }
   return(0);
}

bool CBULinkThread::AnswerLinkBegin(MSGBUF *pmb)
{
   char sbuf[MAXMSG];
   RP_LINKBEGIN *prp;
   AP_LINKBEGIN *ap = (AP_LINKBEGIN *)sbuf;
   prp = (RP_LINKBEGIN *)(pmb->data);
   bu1 = prp->bu1;
   strncpy(szBUGroupID,prp->szBUGroupID,sizeof(szBUGroupID)-1);
   iDefaultAM = prp->iDefaultAM;
   iBUVersion = ntohl(prp->iBUVersion);
   ap->bc1 = 1;
   ap->bu_number = htonl(iID);

// ****** Added by CHENYH at 2004-3-22 14:13:42 ****** 
   ap->basefuncno = htonl(g_Vars.iBaseFuncNo);
   ap->bccid = htonl(g_Vars.iThisID);

   if (iBUVersion==BU_VERSION)
   {
      ap->szmsg[0]='\0';
   }
   else
   {
      sprintf(ap->szmsg,"BCC版本(%d)与BU版本(%d)不同，可能部分功能不正常!",BU_VERSION,iBUVersion);
   }
   if (SendMsg(MT_LINKBEGIN,sizeof(AP_LINKBEGIN)+strlen(ap->szmsg),sbuf)==0)
   {
      // OK
      iStep = BULS_LINKOK;
      iLinkTime = time(NULL);
      iBURFrame = 0;
      iLastReqType = 0;
      memset(LastRData,0,sizeof(AP_REQUEST));
      return(true);
   }
   else return(false);   // send error ...

}

void CBULinkThread::LastRequestOver(RP_REQUEST *prp)
{
   // 统计处理信息：
   int i = FindBPFunction(prp->iLastReqType);
   char szmsg[256];
   if (prp->iLastReqType!=iLastReqType)
   {
      sprintf(szmsg,"BULinkThread Error:BCC记录的上次请求号(%u)<>BU发送过来的请求号(%u)",
         iLastReqType,prp->iLastReqType);
      DEBUG_RUNTIME_MSGOUT(szmsg);
   }
   if (i>=0)
   {
      if (prp->iLastRetCode==0)
      {
         unsigned int dt=GetTickCount()-iLastSendTime;
         g_BDefines[i].nSuccess++;
         g_BDefines[i].dTakentime += dt;
         if (dt>g_BDefines[i].nTt_max)
            g_BDefines[i].nTt_max = dt;
         if (g_BDefines[i].nSuccess==1||dt<g_BDefines[i].nTt_min)
            g_BDefines[i].nTt_min = dt;
      }
      else
      {
         g_BDefines[i].nFail++;
      }
   }
}

int CBULinkThread::SendRequestData(RECEIVEDATA *rdata,unsigned int rtime)
{
   // 这里没有用一个互斥变量来控制BULinkThread和外部提交线程之间发送和重新发送请求包的，可能会出现连续两次发送情况
   int len;
   AP_REQUEST *pap = (AP_REQUEST *)LastRData;
   char eMsg[256];
   m_mutex.Lock();
   // 记录请求方的ID数据：
   SourceNo = rdata->SourceNo;
   memcpy(&(syshead),&(rdata->syshead),sizeof(SYS_HEAD));

   // 将请求方的ID数据转交给BU
   pap->SourceNo = htons(rdata->SourceNo);
   memcpy(&(pap->syshead),&(rdata->syshead),sizeof(SYS_HEAD));
   pap->len = htons(rdata->len);
   memcpy(LastRData+sizeof(AP_REQUEST),rdata->buf,rdata->len);
   len = rdata->len;
   DecodeHead((unsigned char *)rdata->buf,len,&head,eMsg);
   if (head.retCode>0 && head.retCode<MAXROW)
      maxrows = head.retCode;
   else
      maxrows = MAXROW;
   
   iLastReqType = head.RequestType;  // 用于后面的功能统计

   head.recCount = 0;
   head.firstflag = 1;
   head.nextflag = 0;
   head.hook.queuetype = g_Vars.iBaseFuncNo+g_Vars.iThisID;  // 需要前台在后续发送数据的时候，使用本标记的通讯功能号
   memset(head.hook.hostname,0,sizeof(head.hook.hostname));
   sprintf(head.hook.hostname,"%d",g_Vars.iBaseFuncNo+g_Vars.iThisID);
   memset(head.hook.queuename,0,sizeof(head.hook.queuename));
   //sprintf(head.hook.queuename,"%02d%03d%u",g_Vars.iThisID,iID,iqueueno++);
   sprintf(head.hook.queuename,"%03d%u",iID,iqueueno++);

   memset(head.ParmBits,0,sizeof(head.ParmBits));
   iAnswerMode = iDefaultAM;  // 恢复到缺省的AnswerMode状态
   bHaveSent = false;

   ad_ksfseg = -1;
   ad_dklen = -1;
   iLastSendTime = rtime; //GetTickCount();  // 用于后面的功能统计
   pap->iGRFrame = iBURFrame;
   len += sizeof(AP_REQUEST);
   iStep = BULS_REQPROC;
   int rtn = SendMsg(MT_GETREQ,len,LastRData);
   m_mutex.UnLock();

   // 为了减少锁时间，就移到外面：
   if (NeedToSaveLog(head.RequestType))
   {
      sprintf(eMsg,"(%u)BU%d接收请求(%u)",GetTickCount(),iID,head.RequestType);
      g_KSLog.WritePack(rdata->buf,rdata->len,eMsg);
   }
   return(rtn);
}



void CBULinkThread::SetCol(void *parmbits)
{
   head.nextflag = 1;  // 说明应该有新的数据过来
   if (ad_dklen>0)
   {
      // 因为位图更改，导致不同的结果集：
      FlushToKSF(1);
   }
   else if (ad_dklen<0)
   {
      ad_dklen = 0;
      ad_ksfseg = 0;
   }
   head.recCount = 0;
   //head.retCode = 0;
   memcpy(head.ParmBits,parmbits,sizeof(head.ParmBits));
}

#define MAXDATALEN 8000
int CBULinkThread::PutRowData(unsigned short len, char *prowdata)
{
   if (ad_dklen<0)
      ad_dklen = 0;
   if (ad_ksfseg<0)
      ad_ksfseg = 0;
   if (len>0)
   {
      if ((int)(ad_dklen+len)>=(int)(MAXDATALEN-sizeof(ST_PACKHEAD))||head.recCount>=maxrows)
      {
         FlushToKSF();
      }
      memcpy(rowedata+ad_dklen,prowdata,len);
      ad_dklen+=len;
      head.recCount++;
/* ****** Updated by CHENYH at 2004-3-24 13:53:48 ****** 
      if (head.recCount>=maxrows)
      {
         // 这是为了能够及时将结果返回给前台，尤其在处理maxrows=1的情况下
         FlushToKSF(); 
      }
*/
   }
   return(ad_ksfseg+ad_dklen);
}

int CBULinkThread::FlushToKSF(unsigned char nextflag)
{
   FILE *fp;
   unsigned short len;
   char szfile[1024];
   //int *poffset = (int *)(head.hook.queuename+29);
   char *poffset = head.hook.queuename+29;
   len = sizeof(ST_PACKHEAD)+ad_dklen;
   sprintf(szfile,"%s%s.ksf",g_Vars.szForwardPath,head.hook.queuename);
   if (ad_ksfseg<=0)
   {
      fp = sh_fopen(szfile,"w+b",SH_DENYNO);
   }
   else 
   {
      fp = sh_fopen(szfile,"r+b",SH_DENYNO);
   }
   if (fp!=NULL)
   {
      fseek(fp,ad_ksfseg,SEEK_SET);
      fwrite(&len,sizeof(len),1,fp);
      ad_ksfseg += sizeof(len)+sizeof(ST_PACKHEAD)+ad_dklen;

/* ****** Updated by CHENYH at 2004-4-20 13:24:26 ****** 
      由于在HP小型机器会出现：Program terminated with signal 10, Bus error
      64位机器安腾上出现不正常赋值
      *poffset = ad_ksfseg;
*/
      memcpy(poffset,&ad_ksfseg,sizeof(ad_ksfseg));  // 给为内存复制，而不采用直接赋值
      //////////////////////////////////////////////////////////////////////////////

      //head.firstflag = 0;
      head.nextflag = nextflag;
      ModifyHead(&head,(unsigned char *)szfile);
      fwrite(szfile,sizeof(ST_PACKHEAD),1,fp);
      if (ad_dklen>0)
         fwrite(rowedata,ad_dklen,1,fp);
      if (nextflag==0)
      {
         // Add EOF Mark at end of file:
         len = 0;
         fwrite(&len,sizeof(len),1,fp);
      }
      fclose(fp);
   }
   ad_dklen = 0;
   head.firstflag = 0;
   head.recCount = 0;
   if (iAnswerMode==AM_AUTO && !bHaveSent)
   {
      RECEIVEDATA recvdata;
      recvdata.SourceNo = SourceNo;
      memcpy(&(recvdata.syshead),&syshead,sizeof(syshead));
      recvdata.len = g_MWThread.GetForwardData(&head,0,recvdata.buf,szfile);
      g_MWThread.tRouters[SourceNo].SvrToSendData(&recvdata,szfile);

      if (NeedToSaveLog(head.RequestType))
      {
         sprintf(szfile,"(%u)BU%d发送应答数据(%u):",GetTickCount(),iID,head.RequestType);
         g_KSLog.WritePack(recvdata.buf,recvdata.len,szfile);
      }

      bHaveSent = true;
   }
   return(ad_ksfseg);
}

bool CBULinkThread::AnswerData(unsigned short len, char *rdata,char *eMsg)
{
   RP_ANSDATA *rad = (RP_ANSDATA *)rdata;
   if (len<sizeof(RP_ANSDATA))
      return(false);
   head.retCode = ntohl(rad->n_retcode);

/* ****** Updated by CHENYH at 2004-3-11 17:50:05 ****** 
   不将rad->szmsg中的数据设置到包体中，这个要求BU的业务代码自行去控制
   同时也为了提高处理速度：

   if (rad->szmsg[0]!='\0')
   {
      if (head.recCount>0)
      {
         // 由于vsmess更改，需要重新编码：
         ST_PACK array[MAXROW];
         int i,l;
         l = 0;
         for (i=0;i<head.recCount;i++)
         {
            l += DecodeAPack(rowedata+l,ad_dklen-l,&head,array+i,eMsg);
            if (l>ad_dklen)
            {
               sprintf(eMsg,"BUERROR:EncodeRow in PutRow Error: l(%d)>ad_dklen(%d)",l,ad_dklen);
               DEBUG_RUNTIME_MSGOUT(eMsg);
            }
         }
         SetParmBit(&head,F_VSMESS);
         ad_dklen = 0;
         for (i=0;i<head.recCount;i++)
         {
            EncodeRow(&head,array+i,(unsigned char *)rowedata+ad_dklen,&l,eMsg);
            ad_dklen += l;
         }
      }
      else 
      {
         ST_PACK pack;
         int l=0;
         memset(head.ParmBits,0,sizeof(head.ParmBits));
         memset(&pack,0,sizeof(pack));
         strncpy(pack.vsmess,rad->szmsg,255);
         SetParmBit(&head,F_VSMESS);
         head.recCount = 1;
         EncodeRow(&head,&pack,(unsigned char *)rowedata,&l,eMsg);
         ad_dklen = l;
      }
   }
*/
   RECEIVEDATA recvdata;
   recvdata.SourceNo = ntohs(rad->SourceNo);
   if (recvdata.SourceNo==0xFFFF)
   {
      recvdata.SourceNo = SourceNo;
      memcpy(&(recvdata.syshead),&syshead,sizeof(recvdata.syshead));
   }
   else
      memcpy(&(recvdata.syshead),&(rad->syshead),sizeof(recvdata.syshead));
   if (recvdata.SourceNo>=g_MWThread.nRouters)
   {
      sprintf(eMsg,"PERROR:ANSWERDATA指定的router号(%u)错误,改由第一个router发送!",
         recvdata.SourceNo);
      DEBUG_RUNTIME_MSGOUT(eMsg);
      recvdata.SourceNo = 0;
   }
   head.nextflag = rad->nextflag;
   if (ad_ksfseg>0||rad->nextflag!=0)
   {
      // 首包已经记录到Forward文件中了，或者后面还有数据包，那么我就只好将最后这一段写到文件中，
      // 再从文件中读取出来,进行发送。。。。
      FlushToKSF(rad->nextflag);
      // 从FSK中取首包数据进行发送...
      recvdata.len = g_MWThread.GetForwardData(&head,0,recvdata.buf,eMsg);
   }
   else
   {
      // 直接将缓存中的数据发送给前台...
      ModifyHead(&head,(unsigned char *)recvdata.buf);
      if (ad_dklen>0)
      {
         memcpy(recvdata.buf+sizeof(ST_PACKHEAD),rowedata,ad_dklen);
      }
      else
      {
         ad_dklen = 0;
      }
      recvdata.len = sizeof(ST_PACKHEAD)+ad_dklen;
      ad_dklen = 0;
      head.firstflag = 0;
      head.recCount = 0;      
   }
   if (SourceNo==recvdata.SourceNo && memcmp(&(recvdata.syshead),&syshead,sizeof(syshead))==0)
   {
      if (bHaveSent) 
         return(0);  // 针对本目标点不用再发送首包数据了，可能在FlushToKSF的时候就已经发送过数据了
      bHaveSent = true;
   }

   
   // ****** Updated by CHENYH at 2004-3-16 16:56:40 ****** 
   // 为了记录应答数据到日志中
   if (NeedToSaveLog(head.RequestType))
   {
      sprintf(eMsg,"BU%d发送应答数据(%u):",iID,head.RequestType);
      g_KSLog.WritePack(recvdata.buf,recvdata.len,eMsg);
   }
   
   return(g_MWThread.tRouters[recvdata.SourceNo].SvrToSendData(&recvdata,eMsg));
}

bool CBULinkThread::AnswerDataEx(unsigned short len, char *rdata,char *eMsg)
{
   RP_ANSDATAEXH *rad = (RP_ANSDATAEXH *)rdata;
   RECEIVEDATA recvdata;
   recvdata.SourceNo = ntohs(rad->SourceNo);
   if (recvdata.SourceNo>=g_MWThread.nRouters)
   {
      sprintf(eMsg,"PERROR:ANSWERDATAEXH指定的router号(%u)错误,改由第一个router发送!",
         recvdata.SourceNo);
      DEBUG_RUNTIME_MSGOUT(eMsg);
      recvdata.SourceNo = 0;
   }
   memcpy(&(recvdata.syshead),&(rad->syshead),sizeof(recvdata.syshead));
   recvdata.len = len-sizeof(RP_ANSDATAEXH);
   memcpy(recvdata.buf,rdata+sizeof(RP_ANSDATAEXH),recvdata.len);
   return(g_MWThread.tRouters[recvdata.SourceNo].SvrToSendData(&recvdata,eMsg));   
}

bool CBULinkThread::PushData(unsigned short len, char *rdata, char *eMsg)
{
   RP_PUSHDATAH *pdh;
   TPUSHDESTN *pdests;
   char *pdata;
   pdh = (RP_PUSHDATAH *)rdata;
   pdh->acktime = ntohl(pdh->acktime);
   pdh->dcount = ntohs(pdh->dcount);
   pdata = rdata+sizeof(RP_PUSHDATAH);
   pdests = (TPUSHDESTN *)pdata;
   pdata = pdata+sizeof(TPUSHDESTN)*pdh->dcount;
   if (len<sizeof(RP_PUSHDATAH)+sizeof(TPUSHDESTN)*pdh->dcount) 
   {
      sprintf(eMsg,"PERROR:MT_PUSHDATA收到的数据长度[%u]<sizeof(RP_PUSHDATAH)[%u]+sizeof(TPUSHDESTN)[%u]*pdh->dcount[%u]",
         len,sizeof(RP_PUSHDATAH),sizeof(TPUSHDESTN),pdh->dcount);
      return(false);
   }
   len -= sizeof(RP_PUSHDATAH)+sizeof(TPUSHDESTN)*pdh->dcount;
   ST_PACKHEAD *phead = (ST_PACKHEAD *)pdata;
   if (len>=sizeof(ST_PACKHEAD))
   {
      sprintf(phead->hook.hostname+28,"PM%c",pdh->pushmode);
   }
   // 分析执行具体的推送指令：
   int i;
   for (i=0;i<pdh->dcount;i++)
   {
      pdests[i].SourceNo = ntohs(pdests[i].SourceNo);
      pdests[i].DestNo = ntohs(pdests[i].DestNo);
      pdests[i].FuncNo = ntohs(pdests[i].FuncNo);
      pdests[i].BatchNo = ntohl(pdests[i].BatchNo);
      phead->userdata = pdests[i].BatchNo;
      if (NeedToSaveLog(head.RequestType))
      {
         sprintf(eMsg,"(%u)BU%d请求推送%u-%c:",GetTickCount(),iID,phead->RequestType,pdh->pushmode);
/* ****** Updated by CHENYH at 2004-4-2 15:15:54 ****** 
         sprintf(eMsg,"BU%d处理(%u)中需要向[sno%d,dno%d,fno%d]推送(%c)数据:",
            iID,head.RequestType,
            pdests[i].SourceNo,
            pdests[i].DestNo,
            pdests[i].FuncNo,
            pdh->pushmode
            );
*/
         g_KSLog.WritePack(pdata,len,eMsg);
      }
      int rtn;
      rtn = g_MWThread.AddPushRecord(iID,pdests[i].SourceNo,pdests[i].DestNo,pdests[i].FuncNo,
         pdh->pushmode,pdh->acktime,pdata,len);
#ifdef _DEBUG
      g_KSLog.WriteLog(0,"(%u)BU%d写入推送%u-%c到R%d",
         GetTickCount(),
         iID,
         phead->RequestType,
         pdh->pushmode,
         rtn);
#endif
   }
   return(true);
}



bool CBULinkThread::PutRow(unsigned short len, char *rdata, char *eMsg)
{
   RP_PUTROW *ppr = (RP_PUTROW *)(rdata);
   head.retCode = ntohl(ppr->n_retcode);
/* ****** Updated by CHENYH at 2004-3-11 16:19:46 ****** 
   注意，这里不关心属于那个客户端的数据
   SourceNo = ntohs(ppr->SourceNo);
   memcpy(&syshead,&(ppr->syshead),sizeof(syshead));
*/
   if (len>sizeof(RP_PUTROW))
   {
      PutRowData(len-sizeof(RP_PUTROW),rdata+sizeof(RP_PUTROW));
      return(true);
   }
   else
      return(false);
}

char * CBULinkThread::GetRunTimeInformation(char *szbuf)
{
   char sztmp[40];
   switch (iStep)
   {
   case BULS_NOTSTART:  // 本线程尚未启动，需要启动然后才能正常工作
      sprintf(szbuf,"%02d(%5s) QNO%-5u",
         iID,
         "NOTSTART",
         iqueueno
         );
      break;
   case BULS_NOTREADY:  // BU 尚未连接上来
      sprintf(szbuf,"%02d(%5s) QNO%-5u",
         iID,
         "NOTREADY",
         iqueueno
         );
      break;
   case BULS_TOLINK:    // 物理连接成功，但是还需要交换连接初始化
      sprintf(szbuf,"%02d(%5s) QNO%-5u",
         iID,
         "TOLINK",
         iqueueno
         );
      break;
   case BULS_LINKOK:    // 与BU连接上来，但还没有要求
      sprintf(szbuf,"%02d(%5s) QNO%-5u GID(%-11s) LT[%8s] LF%3d LRT%-7u LST%-10u ",
         iID,
         "LINKOK",
         iqueueno,
         szBUGroupID,
         getfmttime(&iLinkTime,0,sztmp),
         iBURFrame,
         iLastReqType,
         iLastSendTime
         );
      break;
   case BULS_WAITREQ:   // BU已经发出等待接收请求处理
      sprintf(szbuf,"%02d(%5s) QNO%-5u GID(%-11s) LT[%8s] LF%3d LRT%-7u LST%-10u ",
         iID,
         "WAITREQ",
         iqueueno,
         szBUGroupID,
         getfmttime(&iLinkTime,0,sztmp),
         iBURFrame,
         iLastReqType,
         iLastSendTime
         );
      break;
   case BULS_REQPROC:   // 与之连接的BU正在处理请求，在提交了请求后，没有收到BU发出等待REQPACK的请求
      sprintf(szbuf,"%02d(%5s) QNO%-5u GID(%-11s) LT[%8s] LF%3d LRT%-7u LST%-10u "
         "RNO%d MaxRows%-3d FSeg%d DLen%d ",
         iID,
         "REQPROC",
         iqueueno,
         szBUGroupID,
         getfmttime(&iLinkTime,0,sztmp),
         iBURFrame,
         iLastReqType,
         iLastSendTime,

         SourceNo,
         maxrows,
         ad_ksfseg,
         ad_dklen
         );
      ShowPackHead(szbuf+strlen(szbuf),&head);
      break;
   default:
      sprintf(szbuf,"%02d(%5d) QNO%-5u GID(%-11s) LT[%8s] LF%3d LRT%-7u LST%-10u "
         "RNO%d MaxRows%-3d FSeg%d DLen%d ",
         iID,
         iStep,
         iqueueno,
         szBUGroupID,
         getfmttime(&iLinkTime,0,sztmp),
         iBURFrame,
         iLastReqType,
         iLastSendTime,

         SourceNo,
         maxrows,
         ad_ksfseg,
         ad_dklen
         );
      ShowPackHead(szbuf+strlen(szbuf),&head);
      break;
   }
   return(szbuf);
}

int CBULinkThread::GetReq(unsigned short len, char *rdata, char *szmsg)
{
   RP_REQUEST *prp = (RP_REQUEST *)rdata;
   //AP_REQUEST *pap = (AP_REQUEST *)LastRData;
   prp->iLastReqType = ntohl(prp->iLastReqType);
   prp->iLastRetCode = ntohl(prp->iLastRetCode);

   iErrorCode = 0;   // 清除原来标注的BU错误

   m_mutex.Lock();
/* ****** Updated by CHENYH at 2004-2-27 17:13:25 ****** 
   if (iLastReqType>0 && prp->iGRFrame==nextframe)
   {
      // 上次请求提交给了本BU，可以统计请求处理时间。。。
      LastRequestOver(prp);
      iLastReqType = 0;
   }
*/
   if (prp->iGRFrame!=iBURFrame)
   {
      iLastSendTime = 0;
      iBURFrame = prp->iGRFrame;
      iStep = BULS_WAITREQ;
   }

/* ****** Updated by CHENYH at 2004-2-23 21:55:26 ****** 
   这里基于如果连接正常，则原来发送的请求包一定是可靠递达的，不用再次发送了
   else if (iStep==BULS_REQPROC)
   {
      if (prp->iGRFrame==iBURFrame)
         ResendRequestData();  // Resend data ... is really need?
      else
      {
         sprintf(szmsg,"CBULinkThread Design Error:iStep==BULS_REQPROC(%d) prp->iGRFrame(%u)!=pap->iGRFrame(%u) iBURFrame(%u)",
            iStep,prp->iGRFrame,pap->iGRFrame,iBURFrame);
         DEBUG_RUNTIME_MSGOUT(szmsg);
      }
   }
*/
   m_mutex.UnLock();
   return(iStep);
}

int CBULinkThread::ResendRequestData()
{
   unsigned short len;
   AP_REQUEST *pap = (AP_REQUEST *)LastRData;
   len = ntohs(pap->len)+sizeof(AP_REQUEST);
   int rtn = SendMsg(MT_GETREQ,len,LastRData);
   iStep = BULS_REQPROC;
   return(rtn);
}

//#define COM_JZJY   // 如果需要与集中交易兼容，即没有显式调用AnswerData等其他数据，需要在最后由DataDone来发送结果给请求端
bool CBULinkThread::DataDone(unsigned short len, char *rdata, char *eMsg)
{
   RP_DATADONE *rdd = (RP_DATADONE *)rdata;
   int i;
   head.nextflag = 0;  // 打上结束标志
   head.retCode = ntohl(rdd->n_retcode);
   if (iAnswerMode==AM_AUTO)
   {
      if (bHaveSent)
      {
         if (ad_ksfseg>0 && ad_dklen>0)
         {
            FlushToKSF(0);
         }
      }
      else
      {
         char buf[1024];
         RP_ANSDATA *rad = (RP_ANSDATA *)buf;
         rad->SourceNo = 0xFFFF; // 明确指明用缺省请求方的
         rad->n_retcode = rdd->n_retcode;
         rad->nextflag = 0;
         rdd->szmsg[255]='\0';
         strcpy(rad->szmsg,rdd->szmsg);
         AnswerData(sizeof(RP_ANSDATA)+strlen(rdd->szmsg),buf,eMsg);
      }
   }
   else
   {
      if (ad_ksfseg>0)
      {
         // 在后续数据文件中，增加结束标记
         FlushToKSF(0);
      }
   }
   rdd->iLastReqType = ntohl(rdd->iLastReqType);
   rdd->n_retcode = ntohl(rdd->n_retcode);
   if (rdd->iLastReqType!=iLastReqType)
   {
      sprintf(eMsg,"BULinkThread Error:BCC记录的上次请求号(%u)<>BU发送过来的请求号(%u)",
         iLastReqType,rdd->iLastReqType);
      DEBUG_RUNTIME_MSGOUT(eMsg);
   }
   i = FindBPFunction(iLastReqType);
   if (i>=0)
   {
      if (rdd->n_retcode==0)
      {
         unsigned int dt=GetTickCount()-iLastSendTime;
         g_BDefines[i].nSuccess++;
         g_BDefines[i].dTakentime += dt;
         if (dt>g_BDefines[i].nTt_max)
            g_BDefines[i].nTt_max = dt;
         if (g_BDefines[i].nSuccess==1||dt<g_BDefines[i].nTt_min)
            g_BDefines[i].nTt_min = dt;
      }
      else
      {
         g_BDefines[i].nFail++;         
      }
   }
   return(true);
}

int CBULinkThread::ExtCallReturn(int dlen, void *rtndata)
{
   if (NeedToSaveLog(head.RequestType))
   {
      char eMsg[256];
      sprintf(eMsg,"(%u)BU%d接收到ExtCall返回(%u)",GetTickCount(),iID,head.RequestType);
      g_KSLog.WritePack(rtndata,dlen,eMsg);
   }
   return(SendMsg(MT_PUSHDATA,dlen,rtndata));
}

int CBULinkThread::ToCancelProcess()
{
   if (iStep==BULS_REQPROC)
      return(SendMsg(MT_CMDCANCEL,sizeof(iBURFrame),&iBURFrame));
   else 
      return(0);  // BU已经处理完毕或处于其他状态，不必停止了
}

void CBULinkThread::SetAMode(char *pAMode)
{
   iAnswerMode = pAMode[0];
}


// 函数名: CBULinkThread::BULogOut
// 编程  : 陈永华 2004-3-11 21:20:59
// 描述  : 本连接对应的BU发出一个要求记录日志的请求
// 返回  : bool 
// 参数  : unsigned short len
// 参数  : char *rdata
// 参数  : char *eMsg
bool CBULinkThread::BULogOut(unsigned short len, char *rdata, char *eMsg)
{
   RP_BCCLOG *pbl = (RP_BCCLOG *)rdata;
   pbl->logid = ntohl(pbl->logid);
   pbl->textlen = ntohs(pbl->textlen);
   if (pbl->logtype==LT_MSG && pbl->logid>=g_MWThread.bumsgshowlevel)
   {
      printf("BU%dLog:%c-%d<%s> dlen%d\n",
         iID,pbl->logtype,pbl->logid,pbl->logtext,len-sizeof(RP_BCCLOG)-pbl->textlen
         );
   }
   // 记录到BULOG文件中：
   switch (pbl->logtype)
   {
   case LT_MSG:
      g_LogFile.WriteLogEx(88,"BU%d:%c-%d<%s>",
         iID,pbl->logtype,pbl->logid,pbl->logtext
         );
      break;
   case LT_CPACK:
      sprintf(eMsg,"BU%d:%c-%d<%s> dlen%d",
         iID,pbl->logtype,pbl->logid,pbl->logtext,len-sizeof(RP_BCCLOG)-pbl->textlen
         );
      g_KSLog.WritePack(pbl->logtext+pbl->textlen+1,len-sizeof(RP_BCCLOG)-pbl->textlen,eMsg);
      break;
   case LT_UDATA:
      g_KSLog.WriteData(rdata,len);
      break;
   }
   return(true);
}

bool CBULinkThread::SetBUError(unsigned short len, RP_SETERROR *prp, char *eMsg)
{
   iErrorCode = ntohl(prp->iErrorCode);
   if (len>=sizeof(RP_SETERROR))
   {
      len -= sizeof(RP_SETERROR);
      if (len>=sizeof(szErrorMsg))
         len = sizeof(szErrorMsg)-1;
      Strncpy(szErrorMsg,prp->szmsg,len+1);
      return(true);
   }
   else return(false);
}

bool CBULinkThread::ResetAnswerData()
{
   head.recCount = 0;
   ad_dklen = 0;
   head.firstflag = 1;
   ad_ksfseg = 0;
   return(true);
}
