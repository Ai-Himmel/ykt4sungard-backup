#include "stdafx.h"
#include <stdio.h>
#include <syslog.h>
#include "profile.h"
#include "slist.h"
#include "cpack.h"
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "ksbu.h"
#include "BDFunc.inl"

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
//#include "transinfo.h"
#include "shem.h"

char g_szVerNo[61];
ST_BUNIT g_BUnit;    // 这里只有单一业务处理单元
CSvrLink *g_pSvrLink;  // 与业务调度中心的连接
ST_PACK *g_pArrays;	//多包时使用
CLogFile g_LogFile;   // 被移到SvrLink.cpp中，作为系统必要的属性

extern TBDefine g_XBDefines[];  // 在具体的函数定义部分，如BDFTest.cpp -> BDFunc.inl中


/* ****** Updated by CHENYH at 2005-11-5 14:51:49 ****** 
将本函数从bupub.cpp中移到这里，是为了不同系统根据自己的环境进行调整
*******************************************************/
// 函数名: WriteAppInfo
// 编程  : 陈永华 2004-3-22 15:34:38
// 描述  : BCC向第一个连接好的BU发起的一个刷新后台的请求，以便业务模块部分能够作相关处理
//     注意：该函数属于框架程序在接收到BCC的WriteAppInfo的时候调用的。
// 返回  : int 
// 参数  : int bccBaseFuncNo
// 参数  : int bccID
int WriteAppInfo(int bccBaseFuncNo,int bccID)
{
   // 这里需要各个业务类型不同作相应处理：

   // 当需要采用动态注册功能的时候，这里可以进行本BU组向BCC注册功能的处理
   TBDefine *pBDefine;
   for (pBDefine=g_XBDefines;pBDefine->RequestType!=0;pBDefine++)
   {
      g_pSvrLink->UpdateRegFunction(pBDefine->RequestType,pBDefine->szRTName,pBDefine->szProgrammer,pBDefine->iPriority,pBDefine->bStoped);
   }

   return(0);
}

int ERR_DEAL(char *msg,int retcode)
{
   return(g_pSvrLink->Err_Deal(msg,retcode));
}

/* ****** Updated by CHENYH at 2005-11-5 14:50:13 ****** 
将本函数从bdefine.cpp中提取到这里是为了让各个系统自行调整本函数的调用方法
*******************************************************/
#if 0
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
   int rtn;
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif
   APPFUNC pFunc = g_XBDefines[fno].pFunc;

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
   rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
#ifdef _DEBUG1
	cm2.Checkpoint();
	if (cm3.Difference(cm1, cm2))
   {
      BCCMsgLogOut(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
      g_LogFile.WriteLogEx(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
		cm3.DumpStatistics();
   }
#endif 
   
   return(rtn);
}
#endif
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
   int r=0;
   int rtn=0;
   int sendtype=0;
   char sRetMsg[256]="";
   APPFUNC pFunc = g_XBDefines[fno].pFunc;
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
	*iRetCode=0;
	*szMsg=0;
	g_pArrays=pArrays;
	//判断是否是结帐时刻,如果是则等待处理
	sendtype=rpack->head.RequestType;
	rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
#ifdef _DEBUG1
	cm2.Checkpoint();
	if (cm3.Difference(cm1, cm2))
	{
	      BCCMsgLogOut(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
	      g_LogFile.WriteLogEx(14444,"在执行功能号:%u时候，经检查，内存出现错误!",rpack->head.RequestType);
			cm3.DumpStatistics();
	}
#endif 
	if(rtn)
	{
		*iRetCode=rtn;
		ERR_DEAL(szMsg,*iRetCode);
	}
	//writelog(LOG_INFO,"%s:bu[%02d][%d]  End",getdbtimestamp(NULL),g_pSvrLink->iThisProcID,rpack->head.RequestType);
   	return(rtn);
}



#ifdef WIN32
#include <conio.h>

void setnoblockgetch()
{
}

int mygetch()
{
   if (kbhit())
      return(getch());
   else return(0);
}
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void setnoblockgetch()
{
   int oldstatus;
   oldstatus = fcntl(0,F_GETFL);
   fcntl(0,F_SETFL,oldstatus|O_NDELAY);
}

int mygetch()
{
   int rtn;
   char kbuf[2];
   rtn = read(0,kbuf,1);
   if (rtn<=0) return(0);
   else return(kbuf[0]);
}
#endif


bool ReadIni(char *inifile)
{
   TIniFile tf;
   CSList tmpstr;

   char szBuf[256];
   g_LogFile.Open("bulog");  // 用程序的进程号作为各个BU日志文件存放目录

   memset(&g_BUnit,0,sizeof(g_BUnit));
   printf("Begin to read ini-file:%s...\n",inifile);
   if (!tf.Open(inifile))
   {
      sprintf(szBuf,"不能打开配置文件<%s>\n",inifile);
      //DEBUG_RUNTIME_MSGOUT(szBuf);
      exit(-1000);
   }
   g_LogFile.RemoveOverdueLogFile(tf.ReadInt("COMMON","LOGOVERDUE",10));
   //g_BUnit.iBUnitGourpID = tf.ReadInt("COMMON","GID",1);
   tf.ReadString("COMMON","GID","",g_BUnit.szBUGroupID,sizeof(g_BUnit.szBUGroupID)-1);
   tf.ReadString("BCC","BCCSVR","127.0.0.1:6666",szBuf,sizeof(szBuf)-1);
   if (!tmpstr.FillStrings(szBuf,':') || tmpstr.GetCount()<2)
   {
      sprintf(szBuf,"配置文件<%s>的配置项[BCC] BCCSVR=???? 错误! 格式为：BCCSVR=xxx.xxx.xxx.xxx:port\n",inifile);
      //DEBUG_RUNTIME_MSGOUT(szBuf);
      exit(-1000);
   }
   strncpy(g_BUnit.szSvrIP,tmpstr.GetAt(0),sizeof(g_BUnit.szSvrIP)-1);
   g_BUnit.iSvrPort = atoi(tmpstr.GetAt(1));
   g_BUnit.iHBInterval = tf.ReadInt("BCC","HEARTBEAT",5000);
   if (g_BUnit.iHBInterval<100)
      g_BUnit.iHBInterval = 100;
   tf.Close();
   return(true);   
}
int main(int argc,char *argv[])
{
   int rtn;
   openlog("yktbank",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL3);
   g_pSvrLink = BUPubInitialize(g_XBDefines,CallBDFunc,WriteAppInfo,&g_LogFile);
   SetLogShowLevel(0);   
   if (argc<2)
      ReadIni("ksbu.ini");
   else
      ReadIni(argv[1]);

   ResetBPFunctions();
   if (argc>2)
   {
      ListBPFunctions(argv[2]);
   }

   // 初始化与BCC连接：
   do 
   {
      rtn = g_pSvrLink->ToLink(&g_BUnit);
      if (rtn==1)
      {
         //DEBUG_RUNTIME_MSGOUT("与业务调度中心(BCC)的连接成功！\n");
         break;
      }
      else if (rtn==-100)
      {
         //DEBUG_RUNTIME_MSGOUT("估计业务调度中心(BCC)尚未正式启动，或者检查配置中的[SERVER]项参数\n");
         //mysleep(g_BUnit.iHBInterval);
	sleep(10);
      }
      else
      {
         // 应该属于故障，或对方并不是BCC
         return(rtn);
      }
   } while (1);
#ifdef WIN32
   setnoblockgetch();
#endif

	key_t key;
	struct shmid_ds buf;


// Update by lq at 2005-03-10
// 将创建共享内存和设备签到移到bankguard中去
// 必须先运行bankguard此处操作才能完成

	key=ftok("bankguard",9);
	shmid=shmget(key,SEGSIZE,0666);
	if(-1==shmid)
	{
		printf("errno=%s\n",strerror(errno));
		return 	100021;	
	}
	shm=(char*)shmat(shmid,0,0);
	if((int)shm==-1)
	{
		return 	100515;	
	}
	semid=semget(key,1,0);
	if(semid==-1)
	{
		return 100515;
	}
	
   while (g_pSvrLink->LinkOK())
   {
#ifdef WIN32
      switch (mygetch())
      {
      case '?':
      case 'h':
      case 'H':
         printf("\nCommand List:\n");
         printf("\t ? or h: display this Help informations!\n");
         printf("\t x: To eXit this business unit.\n");
         printf("\t d: Display functions status.\n");
         printf("\t l: List functions status into <function.lst>.\n");
         printf("Enter command to select:");
         break;
      case 'x':
      case 'X':
         g_pSvrLink->bExit = true;
         continue;
         break;
      case 'd':
      case 'D':
         ListBPFunctions(NULL);
         break;
      case 'l':
      case 'L':
         ListBPFunctions("function.lst");
         break;
      }
#endif
      g_pSvrLink->Processing(&g_BUnit);
      if (g_pSvrLink->bExit) break;
   }
   g_pSvrLink->Close();
   //SQLExit();
   //DEBUG_RUNTIME_MSGOUT("业务处理单元BU系统正常退出!\n");
   g_LogFile.Close();
   closelog();
   return(0);
}
