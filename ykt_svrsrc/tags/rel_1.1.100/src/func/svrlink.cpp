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
              
*********************************************************************/
// SvrLink.cpp: implementation of the CSvrLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "svrlink.h"
#include "comstru.h"
#include "bdefine.h"
#include "logfile.h"

extern CLogFile g_LogFile;

#define MAXROW 100

void reverse(void *data,int len)
{
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;

   ASSERT(len<=16);

   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
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

CSvrLink::CSvrLink()
{
   bExit = false;
   iLastReqType = 0;
   iLastRetCode = 0;
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
   linksock.Close();
   rp.bu1 = 1;
   strncpy(rp.szBUGroupID,pBUnit->szBUGroupID,sizeof(rp.szBUGroupID)-1);
   rp.iDefaultAM = iDefaultAnswerMode;
   rp.iBUVersion = htonl(BU_VERSION);  // BU的版本编码
   if (linksock.ConnectTcp(pBUnit->szSvrIP,pBUnit->iSvrPort))
   {
      for (i=0;i<5;i++)
      {
         rtn = SendMsg(MT_LINKBEGIN,sizeof(rp),&rp); 
         if (rtn!=0)
         {
            sprintf(buf,"发送连接请求数据的时候失败，SendMsg()=%d，端口失败号为%d\n",rtn,linksock.GetLastError(NULL,0));
            DEBUG_RUNTIME_MSGOUT(buf);
            return(rtn);
         }
         rtn = RecvMsg(pBUnit->iHBInterval);
         if (rtn>0 && rtn>=(int)(sizeof(MSGHEAD)))
         {
            pmb = GetRecvMsg();
            if (pmb->head.msgtype==MT_LINKBEGIN && pmb->head.len>=sizeof(AP_LINKBEGIN))
            {
               pap = (AP_LINKBEGIN *)(pmb->data);
               svr_hs1 = pap->bc1;
               // 无所谓字序的转换了，反正不会重复的，如果需要，这个参数也多数会返回给BCC的
               iThisProcID = ntohl(pap->bu_number);
               bccBFuncNo = ntohl(pap->basefuncno);
               bccID = ntohl(pap->bccid);
               if (strlen(pap->szmsg)>0)
               {
                  g_LogFile.WriteLogEx(1000,"BU%d-BCC Warning:%s",iThisProcID,pap->szmsg);
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
      linksock.Close();
      DEBUG_RUNTIME_MSGOUT("做了5次连接请求都没有应答返回!\n");
      return(0);
   }
   return(-100);
}

MSGBUF *CSvrLink::GetRecvMsg()
{
   return((MSGBUF *)buf);
}


// 函数名: CSvrLink::RecvMsg
// 编程  : 陈永华 2004-2-10 22:40:18
// 描述  : 按照MSG协议接收数据
// 返回  : int >0:接收到正常数据包；0:超时；-1:被对方正常关闭；-10:输入的nDesignedSize<=0；-11:对方非标准MSG协议口或数据不同步；-2:因为链路错误而被关闭；-3:在接收数据的时候，出错而被关闭
// 参数  : int timeout
int CSvrLink::RecvMsg(int timeout)
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


// 函数名: CSvrLink::SendMsg
// 编程  : 陈永华 2004-2-10 21:08:11
// 描述  : 以MSG格式发送消息数据给调度中心
// 返回  : int =0:发送成功；<0:发送时候端口出现问题，端口被关闭；-100:出现设计上的错误，需要核查程序
// 参数  : short msgtype ：IN 发送的消息类型
// 参数  : unsigned short msglen ：IN 消息体数据长度
// 参数  : void *MSGBUF ： IN 消息数据缓存
int CSvrLink::SendMsg(short msgtype, unsigned short msglen, void *MSGBUF)
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

bool CSvrLink::LinkOK()
{
   return(!linksock.IsFree());
}

void CSvrLink::Close()
{
   linksock.Close();
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
         WriteAppInfo(bccBFuncNo,bccID);   // 在主框架程序部分
         break;
      case MT_GETREQ:
         // OK,have new request to process
         if (pmb->head.len>=sizeof(AP_REQUEST)+sizeof(ST_PACKHEAD))
         {
            AP_REQUEST *prp = (AP_REQUEST *)(pmb->data);
            if (prp->iGRFrame==iGRFrame)
            {
               CallBPFunction(pmb);
               iGRFrame++;
            }
         }
         break;
      default:
         break;
      }
   }
   return(rtn);
}

int CSvrLink::CallBPFunction(MSGBUF *pmb)
{
   AP_REQUEST *preq;
   ST_CPACK rpack;
   // 20040409: QBIN希望能够处理多记录的请求
   ST_PACK pArrays[MAXROW];
   int recs;

   char szMsg[256];
   preq = (AP_REQUEST *)(pmb->data);
   ruserid.SourceNo = ntohs(preq->SourceNo); 
   memcpy(&(ruserid.syshead),&(preq->syshead),sizeof(ruserid.syshead));
   //memcpy(&head,pmb->data+sizeof(AP_REQUEST),sizeof(head));  // 将原始请求的头截获下来，字序按照实际打包字序格式
                       // 这里留个底，也就不用转换字序了

   if (DecodeBufWithArray((unsigned char *)(pmb->data+sizeof(AP_REQUEST)),
      pmb->head.len-sizeof(AP_REQUEST),
      &rpack,pArrays,&recs,szMsg))
   {
      int fno;
      ASSERT(rpack.head.firstflag==1);  // 只有首包提交下来的。。。。
      fno = FindBPFunction(rpack.head.RequestType);
      if (fno>=0 && g_BDefines[fno].pFunc!=NULL)
      {
         int rtn;
         unsigned int t1=GetTickCount();
         memcpy(&head,&(rpack.head),sizeof(head));
      
         memset(head.ParmBits,0,sizeof(head.ParmBits));  // 将结果集位图清空

         head.recCount = 0;  // Reset the recCount

         iLastReqType = rpack.head.RequestType;
         iAnswerMode = iDefaultAnswerMode;
         
         // OK,have found the process function:
#ifdef TESTINFO
         sprintf(szMsg,"Begin to call req%u <%s>!",
            rpack.head.RequestType,
            g_BDefines[fno].szRTName);
         DEBUG_RUNTIME_MSGOUT(szMsg);
#endif
         eMsg[0]='\0';
         iLastRetCode = 0;
/* ****** Updated by CHENYH at 2004-2-21 12:23:30 ****** 
         rtn = g_BDefines[fno].pFunc(
            &ruserid,
            &(rpack.pack),
            &retcode,
            szMsg
            );
*/
         rtn = CallBDFunc(fno,&ruserid,&rpack,pArrays,&iLastRetCode,eMsg);
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
         return(rtn);
      }
      else
      {
         iLastReqType = 0;
         iLastRetCode = 0;
         sprintf(szMsg,"BCC提交的请求<%u>在本业务单元中没有对应的处理定义!",
            rpack.head.RequestType);
         DEBUG_RUNTIME_MSGOUT(szMsg);
         return(-2);
      }
   }
   else
   {
      DEBUG_RUNTIME_MSGOUT(szMsg);
      return(-1);
   }
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
   pad->SourceNo = htons(ruserid->SourceNo);
   memcpy(&(pad->syshead),&(ruserid->syshead),sizeof(pad->syshead));
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

   pad->SourceNo = htons(ruserid->SourceNo);
   memcpy(&(pad->syshead),&(ruserid->syshead),sizeof(pad->syshead));

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

int CSvrLink::PushData(int sourceno, int destno, int funcno, int batchno, ST_CPACK *ppack, char pushmode, int acktime)
{
   TPUSHDEST dest;
   dest.SourceNo = sourceno;
   dest.DestNo = destno;
   dest.FuncNo = funcno;
   dest.BatchNo = batchno;
   return(PushDataEx(&dest,1,ppack,pushmode,acktime));
}

int CSvrLink::PushDataEx(TPUSHDEST *pushdests, int pdcount, ST_CPACK *ppack, char pushmode, int acktime)
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
   if (ppack->head.recCount>1)
   {
      ppack->head.recCount = 1;
   }
   EncodeBuf(ppack,sbuf+len,&i,szmsg);
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
   ppr->SourceNo = htons(handle->SourceNo);
   memcpy(&(ppr->syshead),&(handle->syshead),sizeof(ppr->syshead));

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
   head.recCount = 0;
   memset(head.ParmBits,0,sizeof(head.ParmBits));
   SetParmBit(&head,F_VSMESS);   
   iLastRetCode = retcode;
   strcpy(eMsg,emsg);
   ST_PACK pack;
   strcpy(pack.vsmess,emsg);
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
            if (apack->head.hook.queuetype>0)
               xcdata.fno = apack->head.hook.queuetype;
            else if (atoi(apack->head.hook.hostname)>0)
               xcdata.fno = atoi(apack->head.hook.hostname);
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
   memset(&(pack->pack),0,sizeof(pack->pack));
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
   return(SendMsg(0x20FF,0,NULL)>=0);
}

//DEL void CSvrLink::GetAnswerHead(ST_PACKHEAD *phead)
//DEL {
//DEL    memcpy(phead,&head,sizeof(head));
//DEL }

void CSvrLink::CopyAnswerHead(ST_PACKHEAD *phead)
{
   memcpy(phead,&head,sizeof(head));   
}
