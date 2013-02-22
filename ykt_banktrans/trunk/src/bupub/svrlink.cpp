/********************************************************************
	created:	2004/03/22
	created:	22:3:2004   10:13
	filename: 	E:\proj\goldmem\gmsvrall\SvrLink.cpp
	file path:	E:\proj\goldmem\gmsvrall
	file base:	SvrLink
	file ext:	cpp
	author:		CHENYH
	
	purpose:	

   Version:   20040322 - ������SetBUError, SetMaxRow 
               �Լ��ð汾������淶BU��BCC�İ汾���
              
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
char iDefaultAnswerMode=AM_AUTO;   // ��ϵͳȱʡ��Ӧ��ģʽ������������ϵͳ���Եı�������趨
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

// ������: CSvrLink::SetTRUserID
// ���  : ������ 2005-8-2 11:25:04
// ����  : ���ø���Ӧ�����ݽ��շ�����ʾ����PutRow�����ݶ�Ҫ���͸�ָ����
// ����  : int 
// ����  : TRUSERID *ruserid : ָ����Ӧ�����ݽ��շ�
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
}

CSvrLink::~CSvrLink()
{

}


// ������: CSvrLink::ToLink
// ���  : ������ 2004-2-11 12:14:25
// ����  : 
// ����  : int 
// ����  : ST_BUNIT *pBUnit
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
   iGRFrame = 10;  // ���¿�ʼ�Ļ�ȡ�����֡�ţ�ע�������ӳ��ڣ�������BCC��ͬ���Է�ֹ��ͬ��
   linksock.Close();
   rp.bu1 = 1;
   strncpy(rp.szBUGroupID,pBUnit->szBUGroupID,sizeof(rp.szBUGroupID)-1);
   rp.iDefaultAM = iDefaultAnswerMode;
   rp.iBUVersion = htonl(BU_VERSION);  // BU�İ汾����
   /* ****** Updated by CHENYH at 2005-9-1 20:35:12 ****** */
#ifdef WIN32
   rp.dwProcID = GetCurrentProcessId();
#else
   rp.dwProcID = getpid();
#endif
   /********************************************************/

   if (linksock.ConnectTcp(pBUnit->szSvrIP,pBUnit->iSvrPort))
   {
      for (i=0;i<5;i++)
      {
         rtn = SendMsg(MT_LINKBEGIN,sizeof(rp),&rp); 
         if (rtn!=0)
         {
            sprintf(buf,"���������������ݵ�ʱ��ʧ�ܣ�SendMsg()=%d���˿�ʧ�ܺ�Ϊ%d\n",rtn,linksock.GetLastError(NULL,0));
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
               // ����ν�����ת���ˣ����������ظ��ģ������Ҫ���������Ҳ�����᷵�ظ�BCC��
               iThisProcID = ntohl(pap->bu_number);
               bccBFuncNo = ntohl(pap->basefuncno);
               bccID = ntohl(pap->bccid);
               if (strlen(pap->szmsg)>0)
               {
                  g_pLogFile->WriteLogEx(1000,"BU%d-BCC Warning:%s",iThisProcID,pap->szmsg);
               }
               return(1);  // �ɹ����ӣ����Կ�ʼ������
            }
         }
         else if (rtn!=0)
         {
            sprintf(buf,"����������������ȷ�ϵ�ʱ��ʧ�ܣ�RecvMsg()=%d���˿�ʧ�ܺ�Ϊ%d\n",rtn,linksock.GetLastError(NULL,0));
            DEBUG_RUNTIME_MSGOUT(buf);
            return(rtn);  // ����ʱ��ʧ��
         }
      }
      linksock.Close();
      DEBUG_RUNTIME_MSGOUT("����5����������û��Ӧ�𷵻�!\n");
      return(0);
   }
   return(-100);
}

MSGBUF *CSvrLink::GetRecvMsg()
{
   return((MSGBUF *)buf);
}


// ������: CSvrLink::RecvMsg
// ���  : ������ 2004-2-10 22:40:18
// ����  : ����MSGЭ���������
// ����  : int >0:���յ��������ݰ���0:��ʱ��-1:���Է������رգ�-10:�����nDesignedSize<=0��-11:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-2:��Ϊ��·��������رգ�-3:�ڽ������ݵ�ʱ�򣬳�������ر�
// ����  : int timeout
int CSvrLink::RecvMsg(int timeout)
{
   MSGBUF *pMsgBuf=(MSGBUF *)buf;
   MSGHEAD *phead = (MSGHEAD *)buf;
   int rtn;
   bool bReverse;
   rtn = linksock.Recv(buf,sizeof(MSGHEAD),timeout);
   if (rtn!=sizeof(MSGHEAD))
      return(rtn);  // ����ʱ�������ʱ
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
      // ���ڲ�������MSG���رն˿ڣ��������ӡ�����
      // ������������ͬ����ͨ���������ӽ���ͬ��������
      DEBUG_RUNTIME_MSGOUT("���ڲ�������MSG������������ͬ�����رն˿ڣ���������\n");
      linksock.Close();
      return(-11);
   }
   if (phead->len>0)
   {
      rtn = linksock.Recv(pMsgBuf->data,phead->len,5000);  // һֱ�ȴ������յ��������ݣ��������5���ӳ�ʱ
      if (rtn!=phead->len)
      {
         linksock.Close();
         return(rtn); // ����ʱ�������ʱ
      }
   }
   m_lastrcvtick = GetTickCount();
   return(phead->len+sizeof(MSGHEAD));
}


// ������: CSvrLink::SendMsg
// ���  : ������ 2004-2-10 21:08:11
// ����  : ��MSG��ʽ������Ϣ���ݸ���������
// ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
// ����  : short msgtype ��IN ���͵���Ϣ����
// ����  : unsigned short msglen ��IN ��Ϣ�����ݳ���
// ����  : void *MSGBUF �� IN ��Ϣ���ݻ���
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
      // ����ʱ���˿������⣬�������ر�
      return(rtn);   
   }
   else if (rtn==0)
   {
      // ��Ӧ�ó����������
      DEBUG_RUNTIME_MSGOUT("������Ϣʱ���ֱ����Դ�CTcpSocket.Send���ó���==0�ķ���!\n");
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
      // ���ӳ��������ˣ���BCC�ر���
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
         (*pWriteAppInfo)(bccBFuncNo,bccID);   // ������ܳ��򲿷�
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
      /* ****** Updated by CHENYH at 2005-10-24 14:29:13 ****** */
      // ��BU��CheckLink()����MT_TESTLINK��������ʱ��BCC��BU����һ���������Ӧ��
      // ��BU��CheckLink()�����ʱ��Ӧ����tc2_tc1(GetTickCount(),m_lastrcvtick)��pBUnit->iHBInterval��2���Ƚ�
      // BCC��BU�ڲ��ȶ������£���·�Ƿ������ġ�
      case MT_TESTLINK:
         goto GETNEXTMSG;  // ������Ϊ��BU��BCC����MT_TESTLINK�������ʱ��BCC��BU���������Ӧ��
         break;
      /*******************************************************/
      default:
         break;
      }
   }
   return(rtn);
}

#define PRIORITIES 3

// ���  : ������ 2005-9-6 11:16:09
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
   head.recCount = 0;  // �Ա���׷�Ӽ�¼��ʱ�򣬽�λͼ���͸�BCC
   for (i=n=0;i<sizeof(head.ParmBits);i++)
   {
      if (parmbits[i])
      {
         head.ParmBits[i] |= parmbits[i];  // �ϲ�λͼ
         n++;
      }
   }
   if (n==0)
   {
      // �������λͼģʽ��Ҳ�͵�ͬ����Ķ���
      // head.retCode = 0;
      memset(head.ParmBits,0,sizeof(head.ParmBits));
   }
   return(n);
/* ****** Updated by CHENYH at 2004-3-10 22:32:19 ****** 
   �����µ�SetCol����������BU�ˣ������������
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
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // ���ṩ�������ݼ�¼��λͼ
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




// ������: CSvrLink::PutRow
// ���  : ������ 2004-2-20 11:49:12
// ����  : Ϊ���뼯�н��׼��ݣ�׼���ĺ���
// ����  : int 
// ����  : TRUSERID *handle
// ����  : ST_PACK *pdata
// ����  : int retcode
// ����  : char *rtnMsg
int CSvrLink::PutRow(TRUSERID *handle, ST_PACK *pdata, int retcode, char *rtnMsg)
{
//   return(PutRowData(pdata));
   unsigned char buf[MAXDATASIZE];
   unsigned short len;
   RP_PUTROW *ppr = (RP_PUTROW *)buf;
   char szMsg[256];

///* ****** Updated by CHENYH at 2004-3-11 20:00:03 ****** 
   // ���ˣ����Ǳ����������Ա�δ�����ܵ���չ��2004-3-11 20:04:42 Ŀǰʵ����û���ô���
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
   ������ҵ��ģ��ȥ�����Ƿ�rtnMsg���ظ��ͻ��ˣ����ﲻ��������
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
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // ���ṩ�������ݼ�¼��λͼ
      head.recCount = 0;      
   }
   head.recCount++;
   int elen;
   EncodeRow(&head,pdata,buf+len,&elen,szMsg);
   len += elen;
   return(SendMsg(MT_PUTROW,len,buf));
}


// ������: CSvrLink::DataDone
// ���  : ������ 2004-2-22 13:35:51
// ����  : 
// ����  : int 
int CSvrLink::DataDone(int retcode,char *szMsg)
{
   char buf[MAXMSG];
   RP_DATADONE *pad=(RP_DATADONE *)buf;
#ifdef TESTINFO
   sprintf(buf,"���ܺ�(%u)������(%d):%s",iLastReqType,retcode,szMsg);
   DEBUG_RUNTIME_MSGOUT(buf);
#endif
   /* ****** Updated by CHENYH at 2006-2-9 17:26:16 ****** 
   ���н��׼�ʹû�м�¼Ҳ��Ҫ��Ӧ��λͼ
   *******************************************************/
   if (head.recCount<=0)
   {
      SendMsg(MT_SETCOL,sizeof(head.ParmBits),head.ParmBits); // ���ṩ�������ݼ�¼��λͼ
      head.recCount = 0;      
   }
   /******************************************************/

   pad->iLastReqType = htonl(iLastReqType);
   pad->n_retcode = htonl(retcode);
   strcpy(pad->szmsg,szMsg);
   return(SendMsg(MT_DATADONE,sizeof(RP_DATADONE)+strlen(szMsg),buf));
}

//#define COM_JZJY   // �����Ҫ�뼯�н��׼��ݣ���û����ʽ����AnswerData���������ݣ���Ҫ�������DataDone�����ͽ���������

// ������: CSvrLink::Err_Deal
// ���  : ������ 2004-2-22 16:36:05
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ��Ϊ���뼯�н��׼��ݣ�
// ����  : int SendMsg������Ϣ
// ����  : char *emsg
// ����  : int retcode
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
   rtn = AnswerData(&user,retcode,emsg,0);  // �������к������ݷ����ˣ�ֻ��һ�������¼(emsgӦ������ֵ��)
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
      acktime = 5;  // ȱʡΪ5�����ڵõ�Ӧ�𣬷�����Ϊʧ�ܴ��������Է�ֹҵ�񲿷ֵ��ô���������BUNIT����ʧ�ܻ����
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
            // ��Ӧ�����ݷ��أ�
            alen = pmb->head.len;
            memcpy(abuf,pmb->data,alen);
            DecodeHead((unsigned char *)abuf,alen,&(xcdata.ahead),szmsg);
            // Ϊ����ȷ��ȡ������ܵĺ������������BCC�ܹ�֧�ֲ��ж�Ӧ�÷������ܹ����������
            if (xcdata.ahead.hook.queuename[0]>='0' && xcdata.ahead.hook.queuename[0]<='9'
               && xcdata.ahead.hook.queuetype>0)
            {
               // ����KSBCCģʽ��XPACKЭ�飺
               xcdata.fno = xcdata.ahead.hook.queuetype;
               // �����ܹ�����Ŀ���ת�����������
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
            DEBUG_RUNTIME_MSGOUT("ExtCall�м��յ��˷�MT_PUSHDATAӦ��������ڳ������!");
            rtn = 0; // ������ȡ���ݣ��Ա���յ���ȷ��MT_PUSHDATAӦ���
         }
      }
      else if (rtn==0)
      {
         return(-2);  // �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������acktime+1����û�н��յ�Ӧ������  
      }
   }
   return(-1); // ��������ͨѶ����Ĵ���
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
      acktime = 5;  // ȱʡΪ5�����ڵõ�Ӧ�𣬷�����Ϊʧ�ܴ��������Է�ֹҵ�񲿷ֵ��ô���������BUNIT����ʧ�ܻ����
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
            // ��Ӧ�����ݷ��أ�
            rtn = 0;
            DecodeBufWithArray((unsigned char *)pmb->data,pmb->head.len,apack,pArrays,&rtn,szmsg);
            memcpy(&xcdata.ahead,&(apack->head),sizeof(ST_PACKHEAD));
            //////////////////////////////////////////////////////////////////////////
            // ��ΪKSMBCC��ʱ��2005-9-11 18:40:49
            if (pmb->head.len>=rtn+sizeof(TPUSHDESTN))
            {
               // �µ�KSMBCC��ExtCallģʽ��2005-9-11 14:11:25
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
            DEBUG_RUNTIME_MSGOUT("ExtCall�м��յ��˷�MT_PUSHDATAӦ��������ڳ������!");
            rtn = 0; // ������ȡ���ݣ��Ա���յ���ȷ��MT_PUSHDATAӦ���
         }
      }
      else if (rtn==0)
      {
         return(-2);  // �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������acktime+1����û�н��յ�Ӧ������  
      }
   }
   return(-1); // ��������ͨѶ����Ĵ���
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
      return(-3); // ��ʾ�Ѿ�ȡ���˺������ݣ�����Ҫ����ȡ�ˣ�
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
      return(-3); // ��ʾ�Ѿ�ȡ���˺������ݣ�����Ҫ����ȡ�ˣ�
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


// ������: CSvrLink::ResetAnswerData
// ���  : ������ 2004-3-24 21:43:47
// ����  : ��������Ѿ��ύ��Ӧ�����ݣ�������Ϊ�����������ִ�е�ʱ����Ҫ������
// ����  : int 
int CSvrLink::ResetAnswerData()
{
   head.recCount = 0;
   return(SendMsg(MT_RESETANSWER,0,NULL));
}

bool CSvrLink::CheckLink()
{
   //return(linksock.CheckDataArrived(0)>=0);
   // ����һ�����԰�������ȥ��BCC����Ϊ����ʶ��İ���������������
   return(SendMsg(MT_TESTLINK,0,NULL)>=0);
}




// ������: CSvrLink::SMOpenBlock
// ���  : ������ 2005-7-4 15:52:14
// ����  : �������һ�����������ڴ��
// ����  : int 
//          >=0: �ɹ������ظù����ڴ�ľ���ţ�
//          -1: �����ڴ�飨������Ѿ�������
//          -2: �Ѿ���Ҫ�Ĺ����ڴ�鳤���Ѿ�������BCC�޶���
//          -3: Ҫ��ĳ��ȳ����Ѿ�����Ĺ����ڴ泤��
//          -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
//          <100: ���ڸ������-101:���Է������رգ�-110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-102:��Ϊ��·��������رգ�-103:�ڽ������ݵ�ʱ�򣬳�������ر�
// ����  : char *name : �����ڴ������
// ����  : unsigned int length: �����ڴ��ĳ���
int CSvrLink::SMOpenBlock(char *name, unsigned int length)
{
   unsigned char sbuf[MAXMSG];
   RP_SMOPEN *pob;
   int rtn;
   pob = (RP_SMOPEN *)sbuf;
   memcpy(pob->name,name,sizeof(pob->name));
   pob->length = htonl(length);
   rtn = SendMsg(MT_SMOPEN,sizeof(RP_SMOPEN),sbuf);
   if (rtn<0) rtn -= 1000;  // �������ش��󣬶Ͽ�����BCC�����ӣ��˳�
   while (rtn==0)
   {
      // ���͹������Ϣ�ɹ���
      rtn = RecvMsg(1000);  // 1����Ӧ�ø��н����
      if (rtn>0)
      {
         // �յ������
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMOPEN)
         {
            // �յ��ļ�Ϊ�����ص�ֵ��
            /* ****** Updated by CHENYH at 2006-7-5 16:24:46 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            //>=0: �ɹ������ظù����ڴ�ľ���ţ�
            //-1: �����ڴ�飨������Ѿ�������
            //-2: �Ѿ���Ҫ�Ĺ����ڴ�鳤���Ѿ�������BCC�޶���
            //-3: Ҫ��ĳ��ȳ����Ѿ�����Ĺ����ڴ泤��            
            return(rtn);
         }
         else rtn = 0; // �����ȴ��Է���Ӧ��
      }
      else if (rtn==0)
      {
         // �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
         rtn = -20;
      }
      else
      {
         // ������
         rtn -= 100;
      }      
   }
   return(rtn);
}


// ������: CSvrLink::SMWrite
// ���  : ������ 2005-7-4 20:13:07
// ����  : д�ֲ���ȫ�����ݵ�ָ���Ĺ����ڴ��
// ����  : int -2/-1000:�����ڴ������� 
//             -1:�ڴ�ռ�û�з��䣻 
//              0:д��λ��offset�����Ѿ�����Ŀռ�  
//             >0:д�����ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
//             -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
//             <-100: ���ڸ������
//             -101:���Է������رգ�
//             -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
//             -102:��Ϊ��·��������رգ�
//             -103:�ڽ������ݵ�ʱ�򣬳�������ر�
//             -1001: ���ȹ�����ÿ�εĳ���length<=8180
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
// ����  : void *wdata��[IN] д���ǵ����ݿ�
// ����  : unsigned int offset��[IN] ���ݴ���ڹ����ڴ���ƫ��λ��
// ����  : unsigned int length��[IN] ���ݿ鳤�ȣ�ע��<8180
// ����  : bool bWLock: [IN] �Ƿ���Ҫ����д
int CSvrLink::SMWrite(int smh, void *wdata, unsigned int offset, unsigned int length, bool bWLock)
{
   unsigned char sbuf[MAXMSG];
   RP_SMWRITE *pwr;
   int rtn;
   if (smh<0)
      return(-1000); // �����ڴ�������󣬲μ�SMOpenBlock
   pwr = (RP_SMWRITE *)sbuf;
   if (length>MAXMSG-sizeof(RP_SMWRITE))
      return(-1001); // ���ȹ�����ÿ�εĳ���length<=8180
   pwr->handle = htonl(smh);
   pwr->offset = htonl(offset);
   pwr->length = htonl(length);
   pwr->lock = bWLock?1:0;
   memcpy(sbuf+sizeof(RP_SMWRITE),wdata,length);
   rtn = SendMsg(MT_SMWRITE,sizeof(RP_SMWRITE)+length,sbuf);
   if (rtn<0) rtn -= 1000;  // �������ش��󣬶Ͽ�����BCC�����ӣ��˳�
   while (rtn==0)
   {
      // ����д�����ڴ����Ϣ�ɹ���
      rtn = RecvMsg(1000);  // 1����Ӧ�ø��н����
      if (rtn>0)
      {
         // �յ������
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMWRITE)
         {
            // �յ��ļ�Ϊ�����ص�ֵ��
            /* ****** Updated by CHENYH at 2006-7-5 16:26:32 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            // ����  : int -2:�����ڴ������� 
            //             -1:�ڴ�ռ�û�з��䣻 
            //              0:д��λ��offset�����Ѿ�����Ŀռ�  
            //             >0:д�����ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
            return(rtn);
         }
         else rtn = 0; // �����ȴ��Է���Ӧ��
      }
      else if (rtn==0)
      {
         // �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
         rtn = -20;
      }
      else
      {
         // ������
         rtn -= 100;
      }      
   }
   return(rtn);
}


// ������: CSvrLink::SMRead
// ���  : ������ 2005-7-6 10:21:43
// ����  : ��ָ�������ڴ�ռ��ж�ȡ�ֲ���ȫ��������
// ����  : int -2/-1000:�����ڴ������� 
//             -1:�ڴ�ռ�û�з��䣻 
//              0:��ȡλ��offset�����Ѿ�����Ŀռ�  
//             >0:��ȡ���ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
//             -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
//             <-100: ���ڸ������
//             -101:���Է������رգ�
//             -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
//             -102:��Ϊ��·��������رգ�
//             -103:�ڽ������ݵ�ʱ�򣬳�������ر�
//             -1001: ���ȹ�����ÿ�εĳ���length<=8180
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
// ����  : void *rbuf��[OUT] ��ȡ���ݻ���
// ����  : unsigned int offset��[IN] ��ȡ���ݴ���ڹ����ڴ���ƫ��λ��
// ����  : unsigned int rblen��[IN] ��ȡ���ݿ鳤�ȣ�ע��<8180
// ����  : bool bRLock: [IN] �Ƿ���Ҫ������
int CSvrLink::SMRead(int smh, void *rbuf, unsigned int offset, unsigned int rblen, bool bRLock)
{
   unsigned char sbuf[MAXMSG];
   RP_SMWRITE *pwr;  // ����Ҳ��ʹ��д�ṹ�������ݽ���
   int rtn;
   if (smh<0)
      return(-1000); // �����ڴ�������󣬲μ�SMOpenBlock
   pwr = (RP_SMWRITE *)sbuf;
   if (rblen>MAXMSG-sizeof(RP_SMWRITE))
      return(-1001); // ���ȹ�����ÿ�εĳ���length<=8180
   pwr->handle = htonl(smh);
   pwr->offset = htonl(offset);
   pwr->length = htonl(rblen);
   pwr->lock = bRLock?1:0;
   rtn = SendMsg(MT_SMREAD,sizeof(RP_SMWRITE),sbuf);
   if (rtn<0) rtn -= 1000;  // �������ش��󣬶Ͽ�����BCC�����ӣ��˳�
   while (rtn==0)
   {
      // ���Ͷ������ڴ����Ϣ�ɹ���
      rtn = RecvMsg(1000);  // 1����Ӧ�ø��н����
      if (rtn>0)
      {
         // �յ������
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMREAD)
         {
            // �յ��ļ�Ϊ�����ص�ֵ��
            /* ****** Updated by CHENYH at 2006-7-5 16:27:38 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            // ����  : int -2:�����ڴ������� 
            //             -1:�ڴ�ռ�û�з��䣻 
            //              0:��ȡλ��offset�����Ѿ�����Ŀռ�  
            //             >0:��ȡ���ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
            if (rtn>0)
            {
               memcpy(rbuf,pmb->data+sizeof(int),rtn);
            }
            return(rtn);
         }
         else rtn = 0; // �����ȴ��Է���Ӧ��
      }
      else if (rtn==0)
      {
         // �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
         rtn = -20;
      }
      else
      {
         // ������
         rtn -= 100;
      }      
   }
   return(rtn);
}


// ������: CSvrLink::SMInterlockedAdd
// ���  : ������ 2005-7-6 11:08:58
// ����  : �ڹ����ڴ����ָ����λ����Ϊ�������ж�ռ�ӷ�����
// ����  : int ���ض�ռ�ӷ�������ֵ��
//          Ϊ0x80000000����������ϵͳ���������
//          Ϊ0x80000001����������ڲ�������
//          ���������������Ϊ�ж�
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
// ����  : unsigned int offset��[IN] ���ݵ�ƫ��λ��
// ����  : int increment��[IN] ��������
int CSvrLink::SMInterlockedAdd(int smh, unsigned int offset, int increment)
{
   unsigned char sbuf[MAXMSG];
   RP_SMINTADD *pia;
   int rtn;
   if (smh<0)
      return(SMIA_BADP); // �����ڴ�������󣬲μ�SMOpenBlock
   pia = (RP_SMINTADD *)sbuf;
   pia->handle = htonl(smh);
   pia->offset = htonl(offset);
   pia->increment = htonl(increment);
   rtn = SendMsg(MT_SMINTADD,sizeof(RP_SMINTADD),sbuf);
   if (rtn<0) rtn = SMIA_ERR;
   while (rtn==0)
   {
      // ���ͳɹ���
      rtn = RecvMsg(1000);  // 1����Ӧ�ø��н����
      if (rtn>0)
      {
         // �յ������
         MSGBUF *pmb = GetRecvMsg();
         if (pmb->head.msgtype==MT_SMINTADD)
         {
            // �յ��ļ�Ϊ�����ص�ֵ��
            /* ****** Updated by CHENYH at 2006-7-5 16:27:38 ****** 
            rtn = ntohl(*(int *)pmb->data); 
            *******************************************************/
            memcpy(&rtn,pmb->data,sizeof(rtn));
            rtn = ntohl(rtn);
            
            return(rtn);
         }
         else rtn = 0; // �����ȴ��Է���Ӧ��
      }
      else break;
   }
   return(SMIA_ERR);
}


// ������: CSvrLink::SMLock
// ���  : ������ 2005-7-6 16:07:57
// ����  : ��ָ���Ĺ����ڴ����б�BUռ�ü���������ģʽ��ֱ���ɹ���ʧ��
// ����  : int -2/-1000:�����ڴ������� 
//             1: �����ɹ�
//             <-100: ���ڸ������
//                -101:���Է������رգ�
//                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
//                -102:��Ϊ��·��������رգ�
//                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
//                -1001: ���ȹ�����ÿ�εĳ���length<=8180
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
int CSvrLink::SMLock(int smh)
{
   return(SMLockCmd(smh,MT_SMLOCK));
}


// ������: CSvrLink::SMTryLock
// ���  : ������ 2005-7-6 20:25:17
// ����  : ���Ŷ�ָ�����ڴ����м���������������������
// ����  : int -2/-1000:�����ڴ������� 
//             0: ������������������Դ������BU������
//             1: �����ɹ�
//             <-100: ���ڸ������
//                -101:���Է������رգ�
//                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
//                -102:��Ϊ��·��������رգ�
//                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
//                -1001: ���ȹ�����ÿ�εĳ���length<=8180
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
int CSvrLink::SMTryLock(int smh)
{
   return(SMLockCmd(smh,MT_SMTRYLOCK));
}


// ������: CSvrLink::SMUnlock
// ���  : ������ 2005-7-6 20:28:47
// ����  : �Ա�BU�����Ĺ����ڴ�����
// ����  : int -2/-1000:�����ڴ������� 
//             1: �����ɹ�
//             <-100: ���ڸ������
//                -101:���Է������رգ�
//                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
//                -102:��Ϊ��·��������رգ�
//                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
//                -1001: ���ȹ�����ÿ�εĳ���length<=8180
// ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
//          ע������ĿǰΪ������ϵͳ�ȶ����ǣ�Ŀǰһ��BUͬʱֻ�ܶ�һ��
//             �����ڴ����м����������һ����ͼ������ʱ��
//             �����Ѿ��������Ļ��������ͷ�
int CSvrLink::SMUnlock(int smh)
{
   return(SMLockCmd(smh,MT_SMUNLOCK));
}


// ������: CSvrLink::SMLockCmd
// ���  : ������ 2005-7-6 14:58:52
// ����  : �����Ϊ�˼ӽ����������ڲ����ã����򻯳���
// ����  : int 
// ����  : int smh
// ����  : int lockmode
int CSvrLink::SMLockCmd(int smh, short lockmode)
{
   int rtn;
   if (smh<0)
      return(-1000); // �����ڴ�������󣬲μ�SMOpenBlock
   smh = htonl(smh);
   rtn = SendMsg(lockmode,sizeof(smh),&smh);
   if (rtn<0) rtn -= 1000;  // �������ش��󣬶Ͽ�����BCC�����ӣ��˳�
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
         else rtn = 0; // ����
      }
      else if (rtn==0)
      {
         // �������������ȴ�
      }
      else 
      {
         // ����ʱ�������
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
   Ϊ���ܹ�Ϊ����ҵ����ģ�������㹻�Ķ�ջ�ռ䣬���������ö�̬����ռ䷽ʽ����
   ST_PACK pArrays[MAXROW]={0};   // 819200 / ��VC��ȱʡ��stack�ռ䱾��Ҳ��1M (1048576)
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
         iLastReqType = head.RequestType;
         iAnswerMode = iDefaultAnswerMode;
         eMsg[0]='\0';
         iLastRetCode = 0;
         rtn = (*pProcess)(&ruserid,rdata,rdlen,&iLastRetCode,eMsg);
         DataDone(iLastRetCode,eMsg);
         return(rtn);
      }
   }

   // 2006-3-23 0:56:40 ���ö�̬���䣬����ռ�ö�ջ�ռ�
   pArrays = (ST_PACK *)malloc(((CXPack *)GetDefaultXPack())->GetPackLength()*MAXROW);
   if (DecodeBufWithArray((unsigned char *)rdata,rdlen,&rpack,pArrays,&recs,szMsg)>0)
   {
      int fno;
      ASSERT(rpack.head.firstflag==1);  // ֻ���װ��ύ�����ġ�������
      memcpy(&reqhead,&(rpack.head),sizeof(ST_PACKHEAD));  // �������ͷ��¼���� 2005-9-21 17:35:06

      memcpy(&head,&(rpack.head),sizeof(head));
      
      memset(head.ParmBits,0,sizeof(head.ParmBits));  // �������λͼ���
      
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
         // �����Ҫͳ�ƹ��ܴ�����������������ϡ�����
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
         sprintf(szMsg,"BCC�ύ������<%u>�ڱ�ҵ��Ԫ��û�ж�Ӧ�Ĵ�����!",
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
            // ��Ӧ�����ݷ��أ�
            rtn = 0;
            DecodeBufWithArray((unsigned char *)pmb->data,pmb->head.len,apack,pArrays,&rtn,szmsg);
            //memset(&xcdata,0,sizeof(xcdata));  // ���
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
            DEBUG_RUNTIME_MSGOUT("IntCall�м��յ��˷�MT_INTCALLӦ��������ڳ������!");
            rtn = 0; // ������ȡ���ݣ��Ա���յ���ȷ��MT_INTCALLӦ���
         }
      }
      else if (rtn==0)
      {
         return(-2);  // �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
      }
   }
   return(-1); // ��������ͨѶ����Ĵ���
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

// ���������ַ�ʽ��飬��Ϊ��һBCC������BU�ύ������ô�������ݾͻᱻflush��
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

