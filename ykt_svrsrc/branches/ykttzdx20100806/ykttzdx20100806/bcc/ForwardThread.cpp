// ForwardThread.cpp: implementation of the CForwardThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "sysgvars.h"
#include "ForwardThread.h"
#include "MWThread.h"

//////////////////////////////////////////////////////////////////////
// CReqPack Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReqPack::CReqPack()
{

}

CReqPack::~CReqPack()
{

}

CReqPack::CReqPack(const CReqPack &rpack)
{
   memcpy(&rdata,&(rpack.rdata),sizeof(rdata));
   rtime = rpack.rtime;
}

//////////////////////////////////////////////////////////////////////
// CFReqPack Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFReqPack::CFReqPack()
{

}

CFReqPack::~CFReqPack()
{

}

CFReqPack::CFReqPack(const CFReqPack &rpack)
{
   // 对于内部的RECEIVEDATA 中的buf因为有head就不需要了。。。
   rdata.SourceNo = rpack.rdata.SourceNo;
   memcpy(&(rdata.syshead),&(rpack.rdata.syshead),sizeof(rdata.syshead));
   rtime = rpack.rtime;
   memcpy(&head,&(rpack.head),sizeof(head));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CForwardThread::CForwardThread()
{

}

CForwardThread::~CForwardThread()
{

}

int CForwardThread::Run()
{
   RPLIST::iterator prq,prn;
   RECEIVEDATA *recvdata;
   bool bToCheckTimeout;
   ST_PACKHEAD *phead;
   unsigned int atimeout;
   while (1)
   {
      if (g_Vars.g_bToExit)
         break;
      bToCheckTimeout = (g_MWThread.rptimeout>0);
      for (prn=tFRQueue.packs.begin();prn!=tFRQueue.packs.end();)
      {
         prq = prn;
         prn++;
         if (bToCheckTimeout)
         {
            if (GetTickCount()-prq->rtime>g_MWThread.rptimeout)
            {
               phead = &(prq->head);
               if (NeedToSaveLog(phead->RequestType))
               {
                  g_KSLog.WritePack(prq->rdata.buf,prq->rdata.len,"取后续请求因为超时，被强制取消!");
               }

               tFRQueue.m_mutex.Lock();
               tFRQueue.packs.pop_front();  // 删除了这个过时的请求了
               tFRQueue.m_mutex.UnLock();               
            }
            else
               bToCheckTimeout = false;  // 后面就没有需要检查了
         }
         if (!bToCheckTimeout)
         {
            recvdata = &(prq->rdata);
            phead = &(prq->head);

            /* ****** Updated by CHENYH at 2004-4-20 13:24:26 ****** 
                  由于在HP小型机器会出现：Program terminated with signal 10, Bus error
                  64位机器安腾上出现不正常赋值
            */
            //atimeout = ntohl(*(unsigned int *)(phead->hook.hostname+20));
            memcpy(&atimeout,phead->hook.hostname+20,sizeof(atimeout));
            atimeout = ntohl(atimeout);
            if (atimeout<=0)
            {
               atimeout = 30000;
            }
            if (ProcessFRequest(recvdata,phead,(GetTickCount()-prq->rtime>atimeout)))
            {
               tFRQueue.m_mutex.Lock();
               tFRQueue.packs.erase(prq);
               tFRQueue.m_mutex.UnLock();
            }
         }
      }
      mysleep(500);
   }
   g_LogFile.WriteLogEx(101,"ForwardThread Exit!");
   return(0);
}

bool CForwardThread::PutFRPackToQueue(RECEIVEDATA *recvdata,ST_PACKHEAD *phead)
{
   CFReqPack rpack;
   rpack.rtime = GetTickCount();
   memcpy(&rpack.rdata,recvdata,sizeof(rpack.rdata));
   memcpy(&rpack.head,phead,sizeof(ST_PACKHEAD));
   tFRQueue.m_mutex.Lock();
   tFRQueue.packs.push_back(rpack);
   tFRQueue.m_mutex.UnLock();
   return(true);
}


bool CForwardThread::ProcessFRequest(RECEIVEDATA *recvdata,ST_PACKHEAD *phead,bool bTimeOut)
{
   char rtnmsg[256];
   ST_PACKHEAD *ohead;
   int rtn;
   bool brtn;
   rtn = g_MWThread.GetForwardData(phead->hook.queuename,-1,(unsigned char *)(recvdata->buf),rtnmsg);
   if (rtn<=0 && bTimeOut)
   {
      strcpy(rtnmsg,"系统处理超时，后续数据没有能够及时返回!");
      rtn = MAXDATASIZE+1;
   }
   if (rtn>=MAXDATASIZE)
   {
      ST_CPACK pack;
      memcpy(&pack.head,phead,sizeof(ST_PACKHEAD));
      pack.head.nextflag = 0;
      pack.head.recCount = 1;
      memset(pack.head.ParmBits,0,sizeof(pack.head.ParmBits));
      SetParmBit(&pack.head,F_VSMESS);
      strcpy(pack.pack.vsmess,rtnmsg);
      pack.head.retCode = 9997;
      EncodeBuf(&pack,(unsigned char *)recvdata->buf,&rtn,rtnmsg);
      recvdata->len = (unsigned short)rtn;
   }
   if (rtn>0)
   {
      recvdata->len = (unsigned short)rtn;
      ohead = (ST_PACKHEAD *)(recvdata->buf);
      /* ****** Updated by CHENYH at 2004-3-1 10:43:10 ****** 
      前台要求保证返回的userdata就是其指定的userdata，特别增加如下代码：
      */
      ohead->userdata = phead->userdata;
      brtn = (g_MWThread.tRouters[recvdata->SourceNo].SvrToSendData(recvdata,rtnmsg));
      if (NeedToSaveLog(phead->RequestType))
      {
         char msg[1024];
         sprintf(msg,"取后续数据成功返回(%s)",rtnmsg);
         g_KSLog.WritePack(recvdata->buf,recvdata->len,msg);
      }
      return(brtn);
   }
   return(false);
}

