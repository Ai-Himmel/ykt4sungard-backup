// MWThread.cpp: implementation of the CMWThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cpack.h"
#include "mypub.h"
#include "MWThread.h"
#include "sysgvars.h"
#ifdef WIN32
#include "windows.h"
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
shm_pubctrl *g_pubctrl;
#endif

CMWThread g_MWThread;  // 一个运行实例


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMWThread::CMWThread()
{
}

CMWThread::~CMWThread()
{

}



int CMWThread::Run()
{
   RemoveForwardFiles(NULL,0);  // 全部清除全部各留下来的批数据文件
   // 启动BU连接的侦听线程。。。
   m_BUListen.CreateThread();
   // 启动ForwardThread。。。
   m_ForwardThread.CreateThread();
   // 启动各个通讯平台的连接接收线程。。。
   int i;
   for (i=0;i<nRouters;i++)
   {
      tRecvThreads[i].CreateThread();
   }
   if (m_bToPush)
   {
      for (i=0;i<nRouters;i++)
      {
         tPushThreads[i].CreateThread();
      }
   }
   unsigned int dwNoBUValidTick=0;
   unsigned int retcode;
   char retmsg[256];
   while (g_Vars.g_bToExit==false)
   {
//      SetDateTime();  由主线程完成。。。
      if (m_bToPush)
      {
         CheckPushDBF();         
      }
      if (rptimeout>0)
      {
         RemoveTimeoutRPack();
      }
      if (GetSuspendRPackCount()>0)
      {
         // 确认有需要处理的请求包：
         i = FindValidBULink(&retcode,retmsg);
         if (i>=0)
         {
            // 找到了空闲的BU连接单元：
            int ip;
            CReqPack rp;
            dwNoBUValidTick = 0;
            for (ip=0;ip<PRIORITIES;ip++)
            {
               if (GetRPackFromQueue(tRPackQueue+ip,rp,bRPQProcFIFO[ip]))
               {
                  tBULinks[i].SendRequestData(&(rp.rdata),rp.rtime);
                  break;  // 本BU已经提交了一个处理任务，不能再提交了。。。
               }
            }
         }
         else
         {
            if (dwNoBUValidTick==0)
               dwNoBUValidTick = GetTickCount();
            else if (nNoVBUWarnDelay>0 && GetTickCount()-dwNoBUValidTick>nNoVBUWarnDelay)
            {
               // 有0.5秒内都没有可处理的BU，那么就应该给客户端有个错误提示信息返回
               int ip;
               CReqPack rp;
               for (ip=PRIORITIES-1;ip>=0;ip--)
               {
                  if (GetRPackFromQueue(tRPackQueue+ip,rp,!bRPQProcFIFO[ip]))
                  {
                     NoValidBUReturn(&rp,retcode,retmsg);
                     break;
                  }
               }
            }
            // 都忙着，就让我休息一下，让别人用CPU，好早点完成任务：
            mysleep(freewait);
         }
      }
      else 
      {
         dwNoBUValidTick = 0;  // 清除以便等待一下再说。。。
         // 没有请求需要处理，让我休息一下，以便其他线程能够处理
         mysleep(freewait);
      }
   }
   //m_BUListen.Close();
   g_Vars.g_bToExit = true;
   DRTPUninitialize();
   mysleep(1000);
   RemoveForwardFiles(NULL,0);  // 全部清除
   return(0);
}






// 函数名: CMWThread::HaveAClientRequest
// 编程  : 陈永华 2004-2-17 14:57:29
// 描述  : 由DRTPRecvThread调用，该线程收到了一个客户请求数据包
// 返回  : bool 
// 参数  : RECEIVEDATA *recvdata
// 参数  : char *rtnmsg
bool CMWThread::HaveAClientRequest(RECEIVEDATA *recvdata, char *rtnmsg)
{
   ST_CPACK pack;
   CReqPack rpack;
   unsigned int retcode=10000;

   if (DecodeHead((unsigned char *)(recvdata->buf),recvdata->len,&(pack.head),rtnmsg))
   {
      if (NeedToSaveLog(pack.head.RequestType))
      {
         g_KSLog.WritePack(recvdata->buf,recvdata->len,"收到请求!");
      }
      if (pack.head.firstflag)
      {         
         int ipriority = GetPriority(&(pack.head));
         if (ipriority>0 && ipriority<=PRIORITIES)
         {
            memcpy(&(rpack.rdata),recvdata,sizeof(RECEIVEDATA));
            //rpack.rtime = GetTickCount(); 让PutRPackToQueue去填写
            PutRPackToQueue(&rpack,ipriority);
            return(true);
         }
         else
         {
            sprintf(rtnmsg,"系统暂不提供功能号为:%u的功能!",pack.head.RequestType);
            retcode = 9998;
         }
      }
      else if (pack.head.nextflag==0)
      {
         int bu;
         pack.head.hook.queuename[3]='\0';
         if (pack.head.hook.queuename[0]>='0')
         {
            bu = atoi(pack.head.hook.queuename);
            if (bu>=0 && bu<MAXBULINKS)
               tBULinks[bu].ToCancelProcess();
         }
         tRouters[recvdata->SourceNo].SvrToSendData(recvdata,rtnmsg);
         return(true);  // 这里就不返回结果给前端了，减少网络带宽的占用。。。
      }
      else
      {
         if (!m_ForwardThread.ProcessFRequest(recvdata,&(pack.head)))
         {
            m_ForwardThread.PutFRPackToQueue(recvdata,&(pack.head));
            return(true);
         }
         else return(true);
      }
   }
   else
   {
      retcode = 9999;
   }
   memset(pack.head.ParmBits,0,sizeof(pack.head.ParmBits));
   pack.head.retCode = retcode;
   pack.head.recCount = 1;
   //pack.head.firstflag = 1;
   pack.head.nextflag = 0;
   strcpy(pack.pack.vsmess,rtnmsg);
   SetParmBit(&(pack.head),F_VSMESS);
   int l=0;
   EncodeBuf(&pack,(unsigned char *)(recvdata->buf),&l,rtnmsg);
   recvdata->len = l;
   return(tRouters[recvdata->SourceNo].SvrToSendData(recvdata,rtnmsg));
}

int CMWThread::GetPriority(ST_PACKHEAD *phead)
{
   int i;
   i = FindBPFunction(phead->RequestType);
   if (i>=0)
   {
      i = g_BDefines[i].iPriority;
      if (i<0) i=0;
      else if (i>=PRIORITIES)
         i = PRIORITIES-1;
      return(i);
   }
   return(-1);
}

bool CMWThread::PutRPackToQueue(CReqPack *rpack, int iPriority)
{
   RPACKQUEUE *pRQ = tRPackQueue+iPriority-1;
   //CPMUTEX amutex(&(pRQ->m_mutex));
   rpack->rtime = GetTickCount();
   pRQ->m_mutex.Lock();
   pRQ->packs.push_back(*rpack);
   pRQ->m_mutex.UnLock();
   return(true);
}

bool CMWThread::GetRPackFromQueue(RPACKQUEUE *pRQ,CReqPack &rpack,bool bFIFO)
{
   //CPMUTEX amutex(&(pRQ->m_mutex));
   if (pRQ->packs.size()<=0) return(false);
   pRQ->m_mutex.Lock();
   if (bFIFO)
   {
      rpack = pRQ->packs.front();
      pRQ->packs.pop_front();
   }
   else
   {
      rpack = pRQ->packs.back();
      pRQ->packs.pop_back();
   }
   pRQ->m_mutex.UnLock();
   return(true);
}

//char szNoVaildBU[]="本处理中心可能没有启动有效的处理单元，不能提供服务，请与系统管理人员联系!";
int CMWThread::FindValidBULink(unsigned int *retcode,char *retmsg)
{
   int i;
   int nBUs=0;
   *retcode=0;
   for (i=0;i<MAXBULINKS;i++)
   {
      if (tBULinks[i].IsWaitReqStep())
      {
         return(i);
      }
      else 
      {
         if (tBULinks[i].iStep==BULS_REQPROC)
         {
            if (tBULinks[i].iErrorCode>0)
            {
               *retcode = tBULinks[i].iErrorCode;
               strcpy(retmsg,tBULinks[i].szErrorMsg);
            }
            nBUs++;
         }
      }
   }
   if (nBUs==0)
   {
      *retcode = 99999;
      //retmsg = szNoVaildBU;
      strcpy(retmsg,"本处理中心可能没有启动有效的处理单元，不能提供服务，请与系统管理人员联系!");
   }
   else if ((*retcode)==0)
   {
      *retcode = 99998;
      strcpy(retmsg,"本处理中心可能比较忙碌[没有空闲的处理单元]，请与系统管理人员联系!");
   }
   return(-1);   
}

bool CMWThread::Reset()
{
   int i;
   SetDateTime();
   m_pdbfdate = 0;
   nPushRecs = 0;

   DRTPInitialize(nRouters);

   for (i=0;i<MAXBULINKS;i++)
   {

/* ****** Updated by CHENYH at 2004-3-24 20:09:15 ****** 
      tBULinks[i].iID = i+1;
*/
      tBULinks[i].iID = i;

#ifdef WIN32
      memset(pi+i,0,sizeof(pi[0]));
#else
      pi[i]=0;   // as not started
#endif
   }
   for (i=0;i<MAXROUTERS;i++)
   {

/* ****** Updated by CHENYH at 2004-3-24 20:09:40 ****** 
      tRouters[i].iID = i+1;
      tPushThreads[i].m_index = i+1;
*/
      tRouters[i].iID = i;
      tPushThreads[i].m_index = i;

      tRecvThreads[i].pRouter = tRouters+i;
      tPushThreads[i].pRouter = tRouters+i;
   }
   return(m_BUListen.Initialize(g_Vars.iBULinkPort));
}

CBULinkThread * CMWThread::FindFreeBULink()
{
   int i;
   for (i=0;i<MAXBULINKS;i++)
   {
      if (tBULinks[i].IsFree())
      {
         iLastFreeBU = i;
         return(tBULinks+i);
      }
   }
   return(NULL);
}


int CMWThread::GetSuspendRPackCount()
{
   int i;
   int n=0;
   for (i=0;i<PRIORITIES;i++)
   {
      n += tRPackQueue[i].packs.size();
   }
   return(n);
}


// 函数名: CMWThread::RemoveTimeoutRPack
// 编程  : 陈永华 2004-2-18 10:26:06
// 描述  : 只有本线程调用，用于抛弃等待超时的请求包
// 返回  : int 被抛弃的请求包个数
int CMWThread::RemoveTimeoutRPack()
{
   int i;
   CReqPack rpack;
   int n=0;
   for (i=0;i<PRIORITIES;i++)
   {
      while (tRPackQueue[i].packs.size()>0)
      {
         rpack = tRPackQueue[i].packs.front();
         if (GetTickCount()-rpack.rtime>rptimeout)
         {
            tRPackQueue[i].m_mutex.Lock();
            tRPackQueue[i].packs.pop_front();  // 丢弃本被挂起的请求包
            tRPackQueue[i].m_mutex.UnLock();
            n++;
         }
         else break;  // 后面的都不会超时了
      }
   }
   return(n);
}


// 函数名: CMWThread::GetForwardData
// 编程  : 陈永华 2004-2-19 10:07:08
// 描述  : 从指定的后续文件中取打包后的数据
// 返回  : unsigned short 读取的数据长度 0:已经没有数据了；>0:成功
// 参数  : char *queuename IN 确认后续文件的队列名
// 参数  : int offset IN 偏移位置. <0:从queuename中取偏移位置
// 参数  : void *buf  OUT 存放的数据
// 参数  : char *eMsg OUT 错误信息
unsigned short CMWThread::GetForwardData(char *queuename, int offset, void *buf, char *eMsg)
{
   FILE *fp;
   char szfile[1024];
   unsigned short len;
   if (offset<0)
   {
/* ****** Updated by CHENYH at 2004-4-20 13:24:26 ****** 
      由于在HP小型机器会出现：Program terminated with signal 10, Bus error
      64位机器安腾上出现不正常赋值
*/
      //offset = *(int *)(queuename+29);
      memcpy(&offset,queuename+29,sizeof(offset));
      ////////////////////////////////////////////////////
   }
   sprintf(szfile,"%s%s.ksf",g_Vars.szForwardPath,queuename);
   fp = sh_fopen(szfile,"rb",SH_DENYNO);
   if (fp!=NULL)
   {
      if (fseek(fp,offset,SEEK_SET)==0)
      {
         if (fread(&len,sizeof(len),1,fp)==1)
         {
            if (len==0)
            {
               fclose(fp);
               strcpy(eMsg,"已经没有后续数据!");
               return(0xFFFF);
            }
            else if (fread(buf,1,len,fp)==len)
            {
               fclose(fp);
               return(len);
            }            
         }
      }
      fclose(fp);
      return(0);
   }
   strcpy(eMsg,"后续数据可能已经过期!");
   return(0xFFFF);
}

unsigned short CMWThread::GetForwardData(ST_PACKHEAD *phead, int offset, void *buf, char *eMsg)
{
   unsigned short len;
   len = GetForwardData(phead->hook.queuename,offset,buf,eMsg);
   if (len==0||len>=MAXDATASIZE)
   {
      ST_CPACK pack;
      memcpy(&(pack.head),phead,sizeof(pack.head));
      memset(&(pack.pack),0,sizeof(pack.pack));
      memset(&(pack.head.ParmBits),0,sizeof(pack.head.ParmBits));
      pack.head.nextflag = 0;
      pack.head.retCode = 9997;
      pack.head.recCount = 1;
      SetParmBit(&(pack.head),F_VSMESS);
      strcpy(pack.pack.vsmess,eMsg);
      int plen=0;
      EncodeBuf(&pack,(unsigned char *)buf,&plen,eMsg);
      len = plen;
   }
   return(len);
}

int CMWThread::ListBULinkStatus(char *outfile,int wmode)
{
   FILE *fp=NULL;
   char szmsg[1024];
   if (outfile!=NULL && outfile[0]!='\0')
   {
      if (wmode==0)
         fp = sh_fopen(outfile,"wt",SH_DENYRW);
      else
         fp = sh_fopen(outfile,"a+t",SH_DENYRW);
      if (fp!=NULL)
      {
         fprintf(fp,"--- BULinkThread Status at %d (TickCount=%u)---\n",g_Vars.g_iHhmmss,GetTickCount());
      }
   }
   int i;
   int rtn = 0;
   for (i=0;i<MAXBULINKS;i++)
   {
      if (tBULinks[i].iStep!=BULS_NOTSTART)
      {
         tBULinks[i].GetRunTimeInformation(szmsg);
         if (fp!=NULL)
            fprintf(fp,"%s\n",szmsg);
         else
            printf("%s\n",szmsg);
         rtn++;
      }
   }
   if (fp!=NULL)
   {
      fprintf(fp,"\n");
      fclose(fp);
   }
   return(rtn);
}

int CMWThread::ListRouterStatus(char *outfile, int wmode)
{
   FILE *fp=NULL;
   char szmsg[1024];
   if (outfile!=NULL && outfile[0]!='\0')
   {
      if (wmode==0)
         fp = sh_fopen(outfile,"wt",SH_DENYRW);
      else
         fp = sh_fopen(outfile,"a+t",SH_DENYRW);
      if (fp!=NULL)
      {
         fprintf(fp,"--- DRTPRouter Status at %d (TickCount=%u)---\n",g_Vars.g_iHhmmss,GetTickCount());
      }
   }
   int i;
   int rtn = 0;
   for (i=0;i<nRouters;i++)
   {
      tRouters[i].GetRunTimeInformation(szmsg);
      if (fp!=NULL)
         fprintf(fp,"%s\n",szmsg);
      else
         printf("%s\n",szmsg);
      rtn++;
   }

   if (fp!=NULL)
   {
      fprintf(fp,"\n");
      fclose(fp);
   }
   return(rtn);
}

int CMWThread::ListRPQStatus(char *outfile, int wmode)
{
   FILE *fp=NULL;
   char szmsg[1024];
   if (outfile!=NULL && outfile[0]!='\0')
   {
      if (wmode==0)
         fp = sh_fopen(outfile,"wt",SH_DENYRW);
      else
         fp = sh_fopen(outfile,"a+t",SH_DENYRW);
      if (fp!=NULL)
      {
         fprintf(fp,"--- ReqPackQueue Status at %d (TickCount=%u)---\n",g_Vars.g_iHhmmss,GetTickCount());
      }
   }
   int i;
   int rtn = 0;
   for (i=0;i<PRIORITIES;i++)
   {
      sprintf(szmsg,"ReqPackQueue%d size=%u",i+1,tRPackQueue[i].packs.size());
      if (fp!=NULL)
         fprintf(fp,"%s\n",szmsg);
      else
         printf("%s\n",szmsg);
      rtn++;
   }

   if (fp!=NULL)
   {
      fprintf(fp,"\n");
      fclose(fp);
   }
   return(rtn);
}

TField tPushFields[]=
{
   {"BUNIT",   'N',0,2,0,0},     // 本推送记录来自于哪个BU连接口，主要对PM_ANSWER （XCALL）有用
   {"SOURCENO",'N',0,2,0,0},     // 客户端注册接收的通讯平台（对应用服务器连接多通讯平台时有用）
   {"DESTNO",  'N',0,6,0,0},     // 客户端注册的目标通讯节点号
   {"FUNCNO",  'N',0,6,0,0},     // 客户端注册的功能号
   {"ACKFLAG", 'C',0,1,0,0},     // 是否需要确认或确认处理标志：0-无需确认,1-需确认,X-客户注销录出；2/3/4/5/6-已推送未确认(=发送trys+1)；A-已确认返回；C-因为后面的注销或登录而取消发送
   {"PATIME",  'N',0,6,0,0},     // 数据推送、确认返回的时间点hhmmss
   {"PACKDATA",'X',0,4096,0,0}   // 存放推送打包数据
};

bool CMWThread::CheckPushDBF()
{
   char sztemp[512];
   if (g_Vars.g_iToday!=m_pdbfdate)
   {
      sprintf(sztemp,"%s%d.dbf",
         g_Vars.szPushDbfPath,
         g_Vars.g_iToday
         );
      m_mutex.Lock();
      // 20040402 CYH Added next lines:
      m_pdbf.d4close();

      while (m_pdbf.d4use(sztemp)!=DBF_OK)
      {
         if (m_pdbf.d4create(sztemp,7,tPushFields)!=DBF_OK)
         {
            g_LogFile.WriteLogEx(10300,"创建推送数据库<%s>失败!",sztemp);
            m_mutex.UnLock();
            return(false);
         }
      }

      m_pdbfdate = g_Vars.g_iToday;
      nPushRecs = (int)(m_pdbf.d4reccount());
      m_mutex.UnLock();
   }
   return(true);
}

int CMWThread::AddPushRecord(int iBUnit,unsigned short sno, unsigned short dno, unsigned short fno, char pushmode, int acktime, void *pdata, int pdlen)
{
   int rtn;
   ST_PACKHEAD *phead;
   m_mutex.Lock();
   if (m_pdbf.d4used())
   {
      m_pdbf.f4b_int("BUNIT",iBUnit);
      m_pdbf.f4b_int("SOURCENO",sno);
      m_pdbf.f4b_int("DESTNO",dno);
      m_pdbf.f4b_int("FUNCNO",fno);
      m_pdbf.f4b_char("ACKFLAG",pushmode);
      m_pdbf.f4b_int("PATIME",acktime);
      if (pdlen>=(int)sizeof(ST_PACKHEAD))
      {
         phead = (ST_PACKHEAD *)pdata;
         // ****** Updated by CHENYH at 2004-3-31 17:40:42 ****** 
         //   根据QBIN要求，需要增加如下两行标记:
         sprintf(phead->hook.hostname,"%d",m_pdbfdate);
         phead->hook.queuetype = g_Vars.iThisID;

/* ****** Updated by CHENYH at 2004-3-31 17:57:11 ****** 
         // 下面2行可以不要，因为接收端已经兼容了：
         memcpy(phead->hook.queuename+20,"PUSHINFO",9);
         phead->hook.queuename[1]=pushmode;
*/

         sprintf(phead->hook.hostname+28,"PM%c",pushmode);

/* ****** Updated by CHENYH at 2004-4-2 12:45:42 ****** 
         为了提高速度作的优化
         phead->hook.UserID = (m_pdbf.d4reccount()+1)*100+m_pdbfdate%100; // 开始修改发送数据中的标示码
*/
         phead->hook.UserID = (nPushRecs+1)*100+m_pdbfdate%100; // 开始修改发送数据中的标示码


         /* ****** Updated by CHENYH at 2004-5-2 11:35:48 ****** 
         userdata作为批次号
         // 2004-4-30: CYH Added next line:
         // 为了符合CPACK标准定义，作为推送方，也就是客户请求方，外部处理后，唯一不会改变的是hook.userdata:
         phead->userdata = phead->hook.UserID;
         */

         // 由于字节顺序，为了让对方接收到后，正常读取数据：
         if (htons(1)==1)
         {
            Reverse((unsigned char *)(&(phead->hook.UserID)),sizeof(phead->hook.UserID));
            // 2004-4-30: 为了能够彻底兼容各类字节序的平台而加如下一行：
            Reverse((unsigned char *)(&(phead->hook.queuetype)),sizeof(phead->hook.queuetype));
         }
      }
      m_pdbf.f4b_binary("PACKDATA",pdata,pdlen);
      m_pdbf.d4append();
/* ****** Updated by CHENYH at 2004-4-2 12:51:21 ****** 
      为了提高速度作的优化
      rtn = nPushRecs = (int)(m_pdbf.d4reccount());
*/
      rtn = nPushRecs = (int)(m_pdbf.d4recno());
   }
   else 
      rtn = -1;
   m_mutex.UnLock();
   return(rtn);
}

#ifndef WIN32
#include "dirent.h"
#endif



int CMWThread::RemoveForwardFiles(char *ksfile, int timeout)
{
   int nfs=0;
   char szfile[1024];
   char fname[256];
#ifdef WIN32
   struct _finddata_t fd;
   int dh;
   if (ksfile==NULL||ksfile[0]=='\0'||ksfile[0]=='*')
   {
      sprintf(szfile,"%s*.ksf",g_Vars.szForwardPath);
      fname[0]='\0';
   }
   else 
   {
      sprintf(szfile,"%s%s.ksf",g_Vars.szForwardPath,ksfile);
      sprintf(fname,"%s.ksf",ksfile);
   }
   dh = _findfirst(szfile,&fd);
   if (dh==-1) return(0);
   do
   {
      if (fname[0]=='\0'||strstr(fd.name,fname)!=NULL)
      {
         sprintf(szfile,"%s%s",g_Vars.szForwardPath,fd.name);
         if (timeout<=0 || getlastaccesstime(szfile)+timeout<time(NULL))
         {
            remove(szfile);
            nfs++;
         }
      }
   } while (_findnext(dh,&fd)!=-1);
   _findclose(dh);
#else
   DIR *dp;
   struct dirent *dirp;
   dp = opendir(g_Vars.szForwardPath);
   if (dp==NULL) return(0);
   if (ksfile==NULL||ksfile[0]=='\0'||ksfile[0]=='*')
   {
      sprintf(szfile,"%s*.ksf",g_Vars.szForwardPath);
      fname[0]='\0';
   }
   else 
   {
      sprintf(szfile,"%s%s.ksf",g_Vars.szForwardPath,ksfile);
      sprintf(fname,"%s.ksf",ksfile);
   }
   while ((dirp=readdir(dp))!=NULL)
   {
      if (strstr(dirp->d_name,".ksf")!=NULL && 
         (fname[0]=='\0'||strstr(dirp->d_name,fname)!=NULL))
      {
         sprintf(szfile,"%s%s",g_Vars.szForwardPath,dirp->d_name);
         // 说明为批数据文件，且匹配ksfile模式
         if (timeout<=0 || getlastaccesstime(szfile)+timeout<time(NULL))
         {
            remove(szfile);
            nfs++;
         }
      }
   }
   closedir(dp);
#endif
   return(nfs);
}


// 函数名: CMWThread::CheckStartupBU
// 编程  : 陈永华 2004-3-3 20:41:45
// 描述  : 被主线程调用，在需要监控BU启动状态时候，监控并启动相关的BU进程
// 返回  : int 被作用的BU进程编号，<0表示正常，没有需要作用的BU进程
int CMWThread::CheckStartupBU()
{
   int i;
   if (nBUnits<=0||szBUProg[0]=='\0') 
   {
      mysleep(100);
      return(-1);
   }
#ifdef WIN32
   HANDLE hs[MAXBULINKS];
   DWORD rtn,n;
   n = 0;
   for (i=0;i<nBUnits;i++)
   {
      if (pi[i].hProcess!=NULL)
      {
         hs[n++]=pi[i].hProcess;
      }
      else break;
   }
   if (n>0)
   {
      // 看一下已经被启动的BU是否正常运行着：
      rtn = WaitForMultipleObjects(n,hs,FALSE,100);
      if (g_Vars.g_bToExit) 
         return(-2);
      if (rtn>=WAIT_OBJECT_0 && rtn<WAIT_OBJECT_0+n)
      {
         i = rtn-WAIT_OBJECT_0;
         TerminateProcess(pi[i].hProcess,0);
         CloseHandle(pi[i].hProcess);
         CloseHandle(pi[i].hThread);
         pi[i].hProcess = NULL;
         pi[i].hThread = NULL;
      }
      else if (n>=nBUnits)
      {
         // 表示一切都被启动，并且不需要再启动BU了：
         return(-2);
      }
   }
   // 启动第i个BU：
   STARTUPINFO si;
   //char szBUPath[1024];
   memset(&si,0,sizeof(si));
   si.cb = sizeof(si);
   memset(pi+i,0,sizeof(pi[0]));
   //szBUPath[0]='\0';
   //strcpy(szBUPath,".\\bunit");
   //UpdateCheckPath(szBUPath,"bunit");  // 就运行在当前目录下的bunit子目录：
   if (!CreateProcess(
      NULL,   // use szBUProg as command line to startup
      szBUProg,
      NULL,   // If lpProcessAttributes is NULL, the handle cannot be inherited
      NULL,   // If lpThreadAttributes is NULL, the handle cannot be inherited
      FALSE,  // If the parameter is FALSE, the handles are not inherited.
      CREATE_NO_WINDOW, // This flag is valid only when starting a console application. If set, the console application is run without a console window. 
      NULL,   //  Use parent's environment block. 
      szBUPath,  // ./bunit
      &si,
      &pi[i]
      ))
   {
      memset(pi+i,0,sizeof(pi[0]));
   }
   else
      mysleep(500);
   return(i);
#else
   for (i=0;i<nBUnits;i++)
   {
      if (pi[i]!=0)
      {

         int status;
         if (waitpid(pi[i],&status,WNOHANG)!=0)  // 适用于SVr4,POSIX.1和BSD系统
         {
            // 该子进程pi[i]退出，或指定的子进程pi[i]不存在或不是发出调用进程的子进程
            break;
         }
      }
      else break;
   }
   if (i>=nBUnits)
   {
      // 表示一切都被启动，并且不需要再启动BU了：
      mysleep(100);  // 休息一下，不要急着返回
      return(-2);
   }
   // 否则，重新启动该子进程:
   pi[i]=0;

   pid_t pid;
   pid=fork();
   if (pid==0)
   {
      execl(szBUProg,szBUProg,NULL);
      /* 如果exec函数返回，表明没有正常执行命令，打印错误信息*/
      perror(szBUProg);
      exit(-1);
   }
   else if (pid>0)
   {
      pi[i] = pid;
   }
   //mysleep(100);
   return(-2); // 目前还没有比较好的想法，在非WINDOWS下作监控启动子进程。
#endif
}

int CMWThread::NoValidBUReturn(CReqPack *prp, int retcode, char *retmsg)
{
   ST_CPACK pack;
   char szmsg[256];
   int len;
   DecodeBuf((unsigned char *)prp->rdata.buf,prp->rdata.len,&pack,szmsg);
   pack.head.retCode = retcode;
   memset(pack.head.ParmBits,0,sizeof(pack.head.ParmBits));
   pack.head.firstflag = 1;
   pack.head.nextflag = 0;
   DAddFieldC((&pack),F_VSMESS,vsmess,retmsg);
   EncodeBuf(&pack,(unsigned char *)prp->rdata.buf,&len,szmsg);
   prp->rdata.len = len;
   return(tRouters[prp->rdata.SourceNo].SvrToSendData(&(prp->rdata),szmsg));
}
