// DRTPRecvThread.cpp: implementation of the CDRTPRecvThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "cpack.h"
#include "drtp_di.h"
#include "DRTPRecvThread.h"
#include "sysgvars.h"
#include "MWThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRTPRecvThread::CDRTPRecvThread()
{
   iStep = DSRT_NOTSTART;
}

CDRTPRecvThread::~CDRTPRecvThread()
{
}

//////////////////////////////////////////////////////////////////////
// CDRTPRouter Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRTPRouter::CDRTPRouter()
{
   s_connect_time=0; // ���ӽ���ʱ��
   s_lasttime=0;   // �ϴη��ͳɹ���ʱ���
	s_connect_counts=0; // ���Ӵ���
	s_recv_count=0;
	s_recv_len=0;
	s_send_count=0;
	s_send_len=0; 
   

   c_connect_time=0; // ���ӽ���ʱ��
   c_lasttime=0;   // �ϴη��ͳɹ���ʱ���
	c_connect_counts=0; // ���Ӵ���
	c_recv_count=0;
	c_recv_len=0;
	c_send_count=0;
	c_send_len=0; 
}

CDRTPRouter::~CDRTPRouter()
{

}

bool CDRTPRouter::SvrToSendData(RECEIVEDATA *recvdata, char *rtnmsg)
{
   if (hSvr.IsOpenning())
   {
      if (hSvr.Send(&(recvdata->syshead),recvdata->buf,recvdata->len,rtnmsg))
      {
         s_lasttime = time(NULL);
         s_send_count++;
         s_send_len += recvdata->len;
#ifdef TESTINFO
         g_LogFile.WriteLogEx(120,"TESTINFO:(%ld)SVR��ͨѶƽ̨%d��������,����:%d--OK",s_lasttime,iID,recvdata->len);
#endif
         return(true);
      }
      else 
      {
         g_LogFile.WriteLogEx(1201,"(%ld)SVR��ͨѶƽ̨%d��������ʧ��,%s",time(NULL),iID,rtnmsg);
      }
   }
   else
   {
      g_LogFile.WriteLogEx(1202,"(%ld)SVR����ͨѶƽ̨%d�������ݵ�ʱ��,��������δ����!",time(NULL),iID);
   }
   return(false);
}

bool CDRTPRouter::SvrToSendData(SYS_HEAD *head, ST_CPACK *pack, ST_PACK *array, char *rtnmsg)
{
   RECEIVEDATA revdata;
   int len;
   revdata.SourceNo = iID;
   memcpy(&(revdata.syshead),head,sizeof(SYS_HEAD));
   if (EncodeBufArray(pack,array,(unsigned char *)(revdata.buf),&len,rtnmsg))
   {
      revdata.len = len;
      return(SvrToSendData(&revdata,rtnmsg));
   }
   else return(false);
}

int CDRTPRecvThread::Run()
{
   char szMsg[256];
   RECEIVEDATA recvdata;
   int rtn;
   iStep = DSRT_RUNNING;
   recvdata.SourceNo = pRouter->iID;
   while (g_Vars.g_bToExit==false)
   {
      if (pRouter->SvrToConnect(szMsg))
      {
         rtn = pRouter->SvrToReceive(&recvdata,szMsg,3000);
         if (rtn<0)
         {
            // ������
            g_LogFile.WriteLogEx(801,"Ӧ�ý��մ���(%d):%s",rtn,szMsg);
            pRouter->SvrToClose();
         }
         else if (rtn>0)
         {
            //recvdata.len = (unsigned int)rtn;
            recvdata.SourceNo = pRouter->iID;
            recvdata.syshead.CRC = inet_addr(pRouter->IP);
#ifdef TESTINFO
            g_LogFile.WriteLogEx(1010,"TESTINFO(%ld):ͨѶƽ̨%d���յ�����,����:%d",time(NULL),pRouter->iID,recvdata.len);  // 
#endif
            if (!g_MWThread.HaveAClientRequest(&recvdata,szMsg))
            {
               g_LogFile.WriteLogEx(1011,"TESTINFO:�ݽ���̨����ʧ�ܣ�����<%s>",szMsg);
            }
         }
      }
   }
   pRouter->SvrToClose();
   g_LogFile.WriteLogEx(100,"DRTPRecvThread[%d]�˳�!",pRouter->iID);
   iStep = DSRT_NOTSTART;
   return(0);
}

bool CDRTPRouter::SvrToConnect(char *rtnmsg)
{
   if (hSvr.IsOpenning()) return(true);
   mysleep(2000);  // �ȴ�2���ӣ������ڽ��з�����ӡ�����
   if (hSvr.Connect(IP,Port,2,tSFuncNos,rtnmsg))
   {
      s_connect_time = time(NULL);
      s_connect_counts++;
      g_LogFile.WriteLogEx(120,"(%ld)SVR��ͨѶƽ̨%d�ɹ��������ӣ�",s_connect_time,iID);
      return(true);
   }
   else
   {
      g_LogFile.WriteLogEx(1203,"(%ld)SVR��ͨѶƽ̨%d��������ʧ��:%s��",time(NULL),iID,rtnmsg);
      return(false);
   }
}

void CDRTPRouter::SvrToClose()
{
   if (hSvr.IsOpenning())
   {
      hSvr.Close();
   }
}

int CDRTPRouter::SvrToReceive(RECEIVEDATA *recvdata, char *rtnmsg, int wtimeout)
{
   int rtn;
   int len;
   len = sizeof(recvdata->buf);
   rtn = hSvr.Receive(&(recvdata->syshead),recvdata->buf,len,rtnmsg,256,wtimeout);
   if (rtn>0)
   {
      recvdata->len = rtn; //len;  // == rtn
      s_recv_count++;
      s_recv_len += recvdata->len;
   }
   return(rtn);
}

char * CDRTPRouter::GetRunTimeInformation(char *szbuf)
{
   char szsct[24];
   char szslt[24];
   char szcct[24];
   char szclt[24];
   if (s_connect_counts>0)
   {
      getfmttime(&s_connect_time,0,szsct);
      getfmttime(&s_lasttime,0,szslt);
   }
   else
   {
      strcpy(szsct,"--:--:--");
      strcpy(szslt,"--:--:--");
   }
   if (c_connect_counts>0)
   {
      getfmttime(&c_connect_time,0,szcct);
      getfmttime(&c_lasttime,0,szclt);
   }
   else
   {
      strcpy(szcct,"--:--:--");
      strcpy(szclt,"--:--:--");
   }
   sprintf(szbuf,
      "Router%d "
      "IP:%s "
      "Port:%u \n"
      "svr connect:%s "
      "sct=%s "
      "slt=%s "
      "scc=%u "
      "src=%u "
      "srl=%u "
      "ssc=%u "
      "ssl=%u \n"
      "cli connect:%s "
      "cct=%s "
      "clt=%s "
      "ccc=%u "
      "crc=%u "
      "crl=%u "
      "csc=%u "
      "csl=%u ",
      iID,
      IP,
      Port,
      hSvr.IsOpenning()?"Y":"N",
      szsct, // ���ӽ���ʱ��
      szslt,   // �ϴη��ͳɹ���ʱ���
	   s_connect_counts, // ���Ӵ���
	   s_recv_count,
	   s_recv_len,
	   s_send_count,
	   s_send_len, 
      hCli.IsOpenning()?"Y":"N",
      szcct, // ���ӽ���ʱ��
      szclt,   // �ϴη��ͳɹ���ʱ���
	   c_connect_counts, // ���Ӵ���
	   c_recv_count,
	   c_recv_len,
	   c_send_count,
	   c_send_len 
      );
   return(szbuf);
}

bool CDRTPRouter::CliToConnect(char *rtnmsg)
{
   if (hCli.IsOpenning())
      return(true);
   mysleep(2000);  // �ȴ�2���ӣ������ڽ��з�����ӡ�����
   if (hCli.Connect(IP,Port,rtnmsg))
   {
      c_connect_time = time(NULL);
      c_connect_counts++;
      g_LogFile.WriteLogEx(121,"(%ld)Cli��ͨѶƽ̨%d�ɹ��������ӣ�",c_connect_time,iID);
      return(true);
   }
   else
   {
      g_LogFile.WriteLogEx(1213,"(%ld)Cli��ͨѶƽ̨%d��������ʧ��:%s��",time(NULL),iID,rtnmsg);
      return(false);
   }
}

void CDRTPRouter::CliToClose()
{
   if (hCli.IsOpenning())
   {
      hCli.Close();
   }
}

int CDRTPRouter::CliToReceive(void *recvbuf, int &recvbufsize, char *rtnmsg, int wtime)
{
   int rtn;
   rtn = hCli.Receive(recvbuf,recvbufsize,rtnmsg,256,wtime);
   if (rtn>0)
   {
      c_recv_count++;
      c_recv_len += rtn;
   }
   return(rtn);
}

bool CDRTPRouter::CliToSendData(unsigned short branchno, unsigned short function, void *senddata, int datalen, char *rtnmsg)
{
   if (hCli.IsOpenning())
   {
      if (hCli.Send(branchno,function,senddata,datalen,rtnmsg,256,false))
      {
         c_lasttime = time(NULL);
         c_send_count++;
         c_send_len += datalen;
#ifdef TESTINFO
         g_LogFile.WriteLogEx(121,"TESTINFO:(%ld)Cli��ͨѶƽ̨%d��������,����:%d--OK",s_lasttime,iID,datalen);
#endif
         return(true);
      }
      else 
      {
         g_LogFile.WriteLogEx(1211,"(%ld)Cli��ͨѶƽ̨%d��������ʧ��,%s",time(NULL),iID,rtnmsg);
      }
   }
   else
   {
      g_LogFile.WriteLogEx(1212,"(%ld)Cli����ͨѶƽ̨%d�������ݵ�ʱ��,��������δ����!",time(NULL),iID);
   }
   return(false);
}
