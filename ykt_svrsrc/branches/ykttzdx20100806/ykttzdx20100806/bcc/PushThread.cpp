// PushThread.cpp: implementation of the CPushThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "sysgvars.h"
#include "mypub.h"
#include "comstru.h"
#include "DRTPRecvThread.h"
#include "PushThread.h"
#include "MWThread.h"


//#define PM2_RETRY  //推送模式2也需要重复发送的情况下

//////////////////////////////////////////////////////////////////////
// CDestStatus Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDestStatus::CDestStatus()
{

}

CDestStatus::~CDestStatus()
{

}

CDestStatus::CDestStatus(const CDestStatus &ds)
{
   batchno = ds.batchno;
   iDestNo = ds.iDestNo;
   iFuncNo = ds.iFuncNo;
   unAckRecord = ds.unAckRecord;
   iSourceNo = ds.iSourceNo;
   tSendTime = ds.tSendTime;
   tSendTime0 = ds.tSendTime0;
}

//////////////////////////////////////////////////////////////////////
// CPushRecord Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPushRecord::CPushRecord()
{

}

CPushRecord::~CPushRecord()
{

}

CPushRecord::CPushRecord(const CPushRecord &pr)
{
   bunit = pr.bunit;
   ackflag = pr.ackflag;
   destno = pr.destno;
   funcno = pr.funcno;
   patime = pr.patime;
   recno = pr.recno;
   valid_at = pr.valid_at;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPushThread::CPushThread()
{
   m_pdbfdate = 0;
   lastrecord = 0;
   vdeststatus.clear();
   vprecords.clear();
}

CPushThread::~CPushThread()
{
   m_pdbf.d4close();
   vdeststatus.clear();
   vprecords.clear();
}



int CPushThread::Run()
{
   VPUSHDEST::iterator vpd;
   VPUSHRECORD::iterator ppr,dpr;
   ST_PACKHEAD *phead;
   int pdlen;  // packdata(buf)中的数据长度
   int routerid;  // 处理记录的通讯平台编号
   CPushRecord pushrec;  // 推送记录的状态数据
   CDestStatus deststatus; // 目标点的状态数据
   int rtn;

   g_LogFile.WriteLogEx(40,"通讯平台%d（%s:%u）的推送线程正常启动!",m_index,pRouter->IP,pRouter->Port);
   while (1)
   {
      if (g_Vars.g_bToExit) 
         break;
      if (pRouter->CliToConnect(szMsg))
      {
         // 客户连接正常，做正常工作：
         // 1. 检查推送数据库打开的状态：
         if (m_pdbfdate!=g_MWThread.m_pdbfdate)
         {
            mysleep(1000); // 日期切换时，延时1秒
            sprintf(pdata,"%s%d.dbf",
               g_Vars.szPushDbfPath ,
               g_MWThread.m_pdbfdate
               );
            if (m_pdbf.d4use(pdata)==DBF_OK)
            {
               m_pdbfdate = g_MWThread.m_pdbfdate;
               lastrecord = 0;
               vprecords.clear();
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  vpd->unAckRecord = 0;  // 清除待发送确认标志，重新开始新的推送处理
               }

            } // if (m_pdbf.d4use(...)
         } // if (m_pdbfdate!=g_MWThread.m_pdbfdate)

         // 2. 检查是否有新的推送记录
         if (m_pdbf.d4used())
         {
            phead = (ST_PACKHEAD *)pdata;
            while (lastrecord<g_MWThread.nPushRecs)
            {
               m_pdbf.d4go(lastrecord+1);
               if (ReadPushRecord(&pushrec,routerid,pdata,pdlen)<=0) 
                  break;
               lastrecord++;
               deststatus.iDestNo = pushrec.destno;
               deststatus.iFuncNo = pushrec.funcno;
               deststatus.iSourceNo = routerid;
               deststatus.unAckRecord = 0;
               pushrec.patime = deststatus.tSendTime0 = time(NULL);
               deststatus.tSendTime = 0;
               if (pdlen>=(int)sizeof(ST_PACKHEAD))
                  deststatus.batchno = phead->userdata; // 目标点的批次号
               else
                  deststatus.batchno = 0;
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  if (vpd->iDestNo==deststatus.iDestNo
                     && vpd->iFuncNo==deststatus.iFuncNo)
                  {
                     break;
                  }
               }
               if (vpd==vdeststatus.end())
               {
                  vdeststatus.push_back(deststatus);
               }
               else
               {
                  // 检查因为注销或更改了发送的Router号，而取消发送或确认的任务：
                  if (pushrec.ackflag=='X'   // 目标点下线了
                     || vpd->batchno != deststatus.batchno //因目标点重新登录，不同批次
                     || vpd->iSourceNo!=routerid) // 登记的目标点使用routerid变更了
                  {
                     // 表示本目标点已经注销，或因为重新登录，修改了发送的Router号
                     if (vpd->unAckRecord>0 
                        && vpd->iSourceNo==m_index)  // 别的连接就不管了
                     {
                        // 表示有已发送但有待确认的记录，则将所有与本目标点相关的记录，都标注已经不再需要确认了
                        // 则将相关的vprecords[x].ackflag = 'C';
                        for (ppr=vprecords.begin();ppr!=vprecords.end();ppr++)
                        {
                           if ((int)ppr->recno>=lastrecord) 
                              break;  // 应该不会出现这种情况的
                           if (ppr->destno==pushrec.destno
                              && ppr->funcno==pushrec.funcno
                              && ((ppr->ackflag>'0'&& ppr->ackflag<='9')
                                 || (ppr->ackflag>='a'&&ppr->ackflag<='z')
                                 ))
                           {
                              // 本记录为本目标点，并且属于推送后需要确认的
                              ppr->ackflag = 'C';
                              ppr->patime = time(NULL);
                              SetPushDbfRecord(ppr->recno,'C');  // 是否需要从vprecords中删除？
                           }
                        } // for 检查待发送或确认的记录中的同目标点的记录                        
                     }
                     vpd->batchno = deststatus.batchno;  // 更改为最新的批次号
                     vpd->unAckRecord = 0;  // 表示合法的待发送或确认的记录都完全没有了
                  } // 检查因为注销或更改了发送的Router号，而取消发送或确认的任务：
                  vpd->iSourceNo = routerid;
               }
               // 检查是否需要发送本任务：
               if (routerid==m_index)
               {
#ifdef TESTINFO
                  g_LogFile.WriteLogEx(400,"TESTINFO:%d(%s:%u)的推送线程读到需要推送任务，记录号:%u!",
                     m_index,pRouter->IP,pRouter->Port,pushrec.recno);
#endif
                  switch (pushrec.ackflag)
                  {
                  case '0':
                     // 以通讯平台客户方式，直接推送出去了
                     //钱彬，20031211，日志中显示返回值
                     rtn = PushDataInClient(&pushrec,pdlen);
                     if (rtn)
                     {
                        SetPushDbfRecord(pushrec.recno,'F'); // 表示发送失败了
                        // 如果推送0类消息失败，是否还需要继续发送，比如因为通讯平台故障???
                        g_LogFile.WriteLogEx(4001,"推送消息类0[%d]失败：%s,%d",pushrec.recno,szMsg,rtn);
                        // 如果需要在恢复后继续推送
                     }
                     else
                     {
                        SetPushDbfRecord(pushrec.recno,'O');
                        g_LogFile.WriteLogEx(4000,"成功推送了消息类0[%d]，本记录不用确认！",pushrec.recno);
                        // 如果需要在恢复后继续推送
                        // break;  //而不要后面的break了
                     }
                     break;
                  case '1':
                  case '2':
                  // 是否需要对以下两种作处理？ － 这种情况往往是由于BCC的重新启动，这里又读取进来了
                  case 'a':  // 已经发送但正在等待确认，但由于BCC的重新启动，这里又读取进来了
                  case 'b':
                     // 入推送记录表：
                     if (pushrec.ackflag>='a')
                     {
                        if (pushrec.valid_at<=0)
                           pushrec.ackflag = pushrec.ackflag-'a'+'1';
                     }

                     pushrec.patime = time(NULL);  // 读取时间作为判断有效期的起始时间

/* ****** Updated by CHENYH at 2004-4-2 14:11:40 ****** 
                     // 为了有效时间点的控制*/
                     if (pushrec.valid_at>0)
                     {
                        pushrec.valid_at += pushrec.patime;
                     }
                     else pushrec.valid_at = 0;
/* ****** End of Updated by CHENYH at 2004-4-2 14:11:50 ****** */

                     if (pdlen>=(int)sizeof(ST_PACKHEAD) && pushrec.ackflag>'0' && pushrec.ackflag<'3')
                     {
                        vprecords.push_back(pushrec);
                     }
                     break;
                  }  // switch (pushrec.ackflag)
               }
               // else 不是本router需要发送的记录，不管它！
            }  // while (lastrecord<g_MWThread.nPushRecs)            
         } // if (m_pdbf.d4used())
         // 开始正式扫描、推送那些读入的消息：
         for (ppr=vprecords.begin();ppr!=vprecords.end()&&pRouter->CliToConnect(szMsg);ppr++)
         {
            if (ppr->ackflag>='a' && ppr->ackflag<='b' && ppr->patime+g_MWThread.m_patime>time(NULL)) 
               continue;  // 已经作过推送了，暂时不需要推送
#ifndef PM2_RETRY
            if (ppr->ackflag=='b' && ppr->valid_at>0)
               continue;   // '2'类请求并且有时效设定的 不需要重新发送
#endif

            // ****** Added by CHENYH at 2004-4-30 9:03:49 ****** 
            if (ppr->ackflag>='A' && ppr->ackflag<='Z')
               continue;   // 这些都不属于需要推送的消息，就跳过去，在后面删除

            pushrec = *ppr;

/* ****** Updated by CHENYH at 2004-2-26 17:16:30 ****** 
          交由PushDataInClient(...) 判断了
            for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
            {
               if (vpd->iDestNo==ppr->destno && vpd->iFuncNo==ppr->funcno)
                  break;
            }
            if (vpd!=vdeststatus.end() && vpd->unAckRecord==0)
            {
*/
            // 本记录作为该目标点的剩下推送记录的第一条，需要发送
            rtn = PushDataInClient(&pushrec);
            if (rtn!=0)
            {
               //钱彬，20031211，加入返回值显示
               if (rtn<0)
                  g_LogFile.WriteLogEx(5001,"推送消息%c[%d]失败：%s,%d",pushrec.ackflag,pushrec.recno,szMsg,rtn);
            }
            else
            {
               g_LogFile.WriteLogEx(5000,"推送消息%c[%d]成功!",pushrec.ackflag,pushrec.recno);
               switch (pushrec.ackflag)
               {
               case '0':  // 应该不会有这种情况的
                  SetPushDbfRecord(pushrec.recno,'O');
                  ppr->ackflag = 'O';
                  break;
               case '1':
                  SetPushDbfRecord(pushrec.recno,'a');
                  ppr->ackflag = 'a';                  
                  break;
               case '2':
                  SetPushDbfRecord(pushrec.recno,'b');
                  ppr->ackflag = 'b';
                  break;
               }
               ppr->patime = time(NULL); 
            } // 成功推送，可能需要确认等
         } // for (ppr=vprecords.begin();ppr!=vprecords.end()&&pRouter->CliToConnect();ppr++)
         while (ReadAckData());  // 从连接处读取确认数据

         // 从vprecords中删除完成或取消的任务
         for (ppr=vprecords.begin();ppr!=vprecords.end();)
         {
            if (ppr->valid_at>0 && time(NULL)>ppr->valid_at)
            {
               SetPushDbfRecord(ppr->recno,'V');
               ppr->ackflag = 'V'; // 标注为已经超期的推送任务，该任务被取消
               for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
               {
                  if (vpd->unAckRecord==ppr->recno)
                  {
                     vpd->unAckRecord = 0;
                     break;
                  }
               }
            }
            if (ppr->ackflag>='A'&& ppr->ackflag<='Z')
            {
               dpr = ppr; 
               ppr++;
               vprecords.erase(dpr);
            }
            else ppr++;
         } //  从vprecords中删除完成或取消的任务       
      } // if (pRouter->CliToConnect(szMsg))      
   } // while (1)
   g_LogFile.WriteLogEx(45,"通讯平台%d的推送线程正常退出!",m_index);
   return(0);
}

int CPushThread::ReadPushRecord(CPushRecord *pData, int &routerid, char *packdata, int &pdlen)
{
   pdlen = 0;
   pData->recno = m_pdbf.d4recno();
   if (pData->recno>0)
   {
      /* ****** Updated by CHENYH at 2003-10-15 22:24:57 ****** 
      {"BUNIT",   'N',0,2,0,0},     // 本推送记录来自于哪个BU连接口，主要对PM_ANSWER （XCALL）有用
      {"SOURCENO",'N',0,2,0,0}, // 客户端注册接收的通讯平台（对应用服务器连接多通讯平台时有用）
      {"DESTNO",'N',0,6,0,0},   // 客户端注册的目标通讯节点号
      {"FUNCNO",'N',0,6,0,0},   // 客户端注册的功能号
      {"ACKFLAG",'C',0,1,0,0},  // 是否需要确认或确认处理标志：
         0-无需确认,1-需确认,X-客户注销录出；2/3/4/5/6-已推送未确认(=发送trys+1)；A-已确认返回；C-因为后面的注销或登录更改而取消发送或确认
      {"PATIME",'N',0,6,0,0},   // 数据推送后指定的需要确认返回的有效时间（秒计），在回写的时候则为发送或确认回来的时间点hhmmss
      {"PACKDATA",'X',0,4096,0,0}  // 存放推送打包数据
      */
      pData->bunit = m_pdbf.f4int("BUNIT");
      pData->ackflag = m_pdbf.f4char("ACKFLAG");
      pData->destno = (unsigned short)m_pdbf.f4int("DESTNO");
      pData->funcno = (unsigned short)m_pdbf.f4int("FUNCNO");
      pData->valid_at = m_pdbf.f4int("PATIME");
      routerid = m_pdbf.f4int("SOURCENO");      
      if (routerid==m_index && (pData->ackflag>='0'&&pData->ackflag<='9')
         ||(pData->ackflag>='a'&&pData->ackflag<='z'))
      {
         pdlen = m_pdbf.f4binary("PACKDATA",packdata,MAXDATASIZE);
      }
   }
   return(pData->recno);
}



bool CPushThread::SetPushDbfRecord(unsigned int recno, char ackflag)
{
   //char tmstr[40];
   if (recno<=0 || m_pdbf.d4used()==false)
      return(false);
   if (m_pdbf.d4go(recno)==DBF_OK)
   {
      m_pdbf.f4b_char("ACKFLAG",ackflag);
      if (ackflag>='A' && ackflag<='Z')
         m_pdbf.f4b_int("PATIME",g_Vars.g_iHhmmss);  
      m_pdbf.d4putrec();
      return(true);
   }
   return(false);
}

int CPushThread::PushDataInClient(CPushRecord *pPR, int pdlen)
{
   ST_PACKHEAD *phead;
   CPushRecord prec;
   int routerid;
   VPUSHDEST::iterator vpd;
   bool bChkDest;

   if (!(pRouter->CliToConnect(szMsg)))
   {
      strcpy(szMsg,"没有与通讯平台建立客户方式的连接！不能推送！");
      return(-1);
   }
#ifdef PM2_RETRY
   if (pPR->ackflag!='0')
      bChkDest = true;
   else
      bChkDest = false;
#else
   switch (pPR->ackflag)
   {
   case '1':
   case 'a':
      bChkDest = true;
      break;
   default:  //'0','2','b' etc.
      bChkDest = false;
      break;
   }
#endif
   if (bChkDest)
   {
      for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++)
      {
         if (vpd->iDestNo==pPR->destno
            && vpd->iFuncNo==pPR->funcno)
         {
            break;
         }
      }
/* ****** Updated by CHENYH at 2004-2-26 12:23:25 ****** 
      if (vpd==vdeststatus.end())
      {
      }
*/
      if (vpd->unAckRecord>0 && vpd->unAckRecord<pPR->recno)
      {
         // 已经有推送消息需要确认，为了保证顺序发送，本记录就暂不发送了，等到前面数据都发送后，轮到它再发送
         strcpy(szMsg,"针对该目标点，已经有数据需要发送后确认！");
         return(1);
      }
   }
   if (pdlen<=0)
   {
      if (!(m_pdbf.d4used()))
      {
         strcpy(szMsg,"推送记录库没有成功打开！不能推送！");
         return(-2);
      }
      // 到推送记录库中读取相应的推送数据：
      if (m_pdbf.d4go(pPR->recno)!=DBF_OK)
      {
         sprintf(szMsg,"不能定位推送记录库的记录%d！不能推送！",pPR->recno);
         return(-3);
      }
      if (pdlen<=0)
      {
         if (ReadPushRecord(&prec,routerid,pdata,pdlen)<=0)
         {
            sprintf(szMsg,"不能读取推送记录库的记录%d！不能推送！",pPR->recno);
            return(-4);
         }
      }
   }
   if (pdlen<(int)sizeof(ST_PACKHEAD))
   {
      sprintf(szMsg,"推送数据长度(%d)不足(<%d  sizeof(ST_PACKHEAD))，取消推送!",pdlen,sizeof(ST_PACKHEAD));
      return(-5);
   }
   
   phead = (ST_PACKHEAD *)pdata;
   if (bChkDest)
   {
      vpd->unAckRecord = pPR->recno;
      vpd->iSourceNo = m_index;
      vpd->batchno = phead->userdata;
      vpd->tSendTime = time(NULL);
   }

#ifdef _DEBUG
   g_KSLog.WriteLog(0,"(%u)BU%dR%u向(%u:%u)推送数据%u-L%d",
      GetTickCount(),
      pPR->bunit,
      pPR->recno,
      pPR->destno,
      pPR->funcno,
      phead->RequestType,
      pdlen
      );
#endif

   // 真正开始推送：
   //pPR->patime = time(NULL); // 做了一次推送，但是否成功要看后续的处理
   if (pRouter->CliToSendData(pPR->destno,pPR->funcno,pdata,pdlen,szMsg))
   {
      return(0);
   }
   else
   {
      // 推送数据到sourceno通讯平台失败
      pRouter->CliToClose();
      return(-6);
   }
}

bool CPushThread::ReadAckData()
{
   int rtn,acklen;
   unsigned int recno;
   ST_PACKHEAD *phead;
   VPUSHDEST::iterator vpd;
   VPUSHRECORD::iterator ppr;
   
   
   if (!(pRouter->CliToConnect(szMsg)))
   {
      return false;
   }
   acklen = MAXDATASIZE;
   rtn = pRouter->CliToReceive(pdata,acklen,szMsg,10);
   if (rtn<0)
   {
      g_LogFile.WriteLogEx(3001,"CliToReceive接收错误%d:%s!",
         rtn,szMsg);
      pRouter->CliToClose();
      return false;
   }
   if (rtn==0)
   {
      return false;  // 在指定时间里没有收到数据
   }
   if (rtn<(int)sizeof(ST_PACKHEAD))
   {
      // 本系统中通讯数据必须符合ST_PACK协议，所以数据包至少有ST_PACKHEAD长度：
      g_KSLog.WriteLog(0,"DEBUGINFO:接收包数据长度%d<%u sizeof(ST_PACKHEAD)！",
         rtn,sizeof(ST_PACKHEAD));
      return false;
   }
   phead = (ST_PACKHEAD *)pdata;

   // 由于字节顺序，为了正常读取数据：
   Reverse((unsigned char *)(&(phead->hook.UserID)),sizeof(phead->hook.UserID));
   if ((int)(phead->hook.UserID%100)!=m_pdbfdate%100)
   {
      g_KSLog.WriteLog(0,"DEBUGINFO:在日切时候，属于正常情况，包中日期%d!=当前推送库日期%d!",
         phead->hook.UserID%100,m_pdbfdate%100);
      return true;
   }
   recno = (phead->hook.UserID/100);


   /* ****** Updated by CHENYH at 2004-5-2 11:34:29 ****** 
   userdata已经作为批次号使用了，不能再使用了
   if ((int)(phead->userdata%100)!=(m_pdbfdate%100))
   {
      g_KSLog.WriteLog(0,"DEBUGINFO:在日切时候，属于正常情况，包中日期%d!=当前推送库日期%d!",
         phead->userdata%100,m_pdbfdate%100);
      return true;      
   }
   recno = (phead->userdata/100);
   */

   for (ppr=vprecords.begin();ppr!=vprecords.end();ppr++)
   {
      if (ppr->recno==recno)
      {
#ifdef _DEBUG
         // 找到了对应的推送消息：
         g_KSLog.WriteLog(0,"(%u)收到一个确认ID号为%u的确认信息，对应记录号%d的推送记录!",
            GetTickCount(),
            phead->hook.UserID,
            recno);
#endif
         switch (ppr->ackflag)
         {
         case 'a': // '1'->'a'
            ppr->ackflag = 'A';
            break;
         case 'b':
            ppr->ackflag = 'B';
            // 将确认返回的数据，转发给对应BULink的BUNIT，作为外调的返回，当然需要在合理的处理时间内
            // if (ppr->patime+ppr->valid_at>=time(NULL)) 在这里不作判断，由Run中间去处理，从待确认的推送中删除
            {
               if (ppr->bunit>=0 && ppr->bunit<MAXBULINKS)
                  g_MWThread.tBULinks[ppr->bunit].ExtCallReturn(acklen,pdata);
            }
            break;
         default:
            g_KSLog.WriteLog(0,"LOGIC ERROR: 怎么会出现没有作推送(ackflag=%c)就有确认数据回来的情况呢? recno=%d",
               ppr->ackflag,recno);
            break;
         }
         SetPushDbfRecord(recno,ppr->ackflag);
         for (vpd=vdeststatus.begin();vpd!=vdeststatus.end();vpd++) 
         {
            if (vpd->unAckRecord==recno)
            {
               vpd->unAckRecord = 0;
               break; 
            }
         }
         return true;
      }
   }
   // 收到一个不能在推送任务表中的确认记录
   g_KSLog.WriteLog(0,"LOGIC ERROR:收到一个确认ID号为%u的确认信息，但是不能找到推送任务表中对应记录号%d的推送记录!",
      phead->hook.UserID,
      recno);
   //SetPushDbfRecord(recno,'A');
   return true;
}
