#include "stdafx.h"
#include <stdio.h>
#include "profile.h"
#include "slist.h"
#include "cpack.h"
#include "busqc.h"  // 与各个sqc程序相关的全局变量和函数定义
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "esqlc.h"
#include "dbfunc.h"
#include "ksbu.h"
//#include "BDFunc.inl"

ST_BUNIT g_BUnit;    // 这里只有单一业务处理单元
ST_SQLDB g_SqlDB;
CSvrLink *g_pSvrLink;  // 与业务调度中心的连接
ST_PACK *g_pArrays;	//多包时使用
CLogFile g_LogFile;   // 被移到SvrLink.cpp中，作为系统必要的属性

TBDefine g_XBDefines[1];  // 在具体的函数定义部分，如BDFTest.cpp -> BDFunc.inl中

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
   return(0);
}

int ERR_DEAL(char *msg,int retcode)
{
   return(g_pSvrLink->Err_Deal(msg,retcode));
}

/* ****** Updated by CHENYH at 2005-11-5 14:50:13 ****** 
将本函数从bdefine.cpp中提取到这里是为了让各个系统自行调整本函数的调用方法
*******************************************************/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg)
{
	return 0;
}
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
      DEBUG_RUNTIME_MSGOUT(szBuf);
      exit(-1000);
   }
   g_LogFile.RemoveOverdueLogFile(tf.ReadInt("COMMON","LOGOVERDUE",10));
   //g_BUnit.iBUnitGourpID = tf.ReadInt("COMMON","GID",1);
   tf.ReadString("COMMON","GID","",g_BUnit.szBUGroupID,sizeof(g_BUnit.szBUGroupID)-1);
   tf.ReadString("BCC","BCCSVR","127.0.0.1:6666",szBuf,sizeof(szBuf)-1);
   if (!tmpstr.FillStrings(szBuf,':') || tmpstr.GetCount()<2)
   {
      sprintf(szBuf,"配置文件<%s>的配置项[BCC] BCCSVR=???? 错误! 格式为：BCCSVR=xxx.xxx.xxx.xxx:port\n",inifile);
      DEBUG_RUNTIME_MSGOUT(szBuf);
      exit(-1000);
   }
   strncpy(g_BUnit.szSvrIP,tmpstr.GetAt(0),sizeof(g_BUnit.szSvrIP)-1);
   g_BUnit.iSvrPort = atoi(tmpstr.GetAt(1));
   g_BUnit.iHBInterval = tf.ReadInt("BCC","HEARTBEAT",5000);
   if (g_BUnit.iHBInterval<100)
      g_BUnit.iHBInterval = 100;


/* ****** Updated by CHENYH at 2005-9-28 12:14:22 ****** 

   tf.ReadString("SQLSVR","NAME","gmserver",g_BUnit.m_SqlDB.szServer,sizeof(g_BUnit.m_SqlDB.szServer)-1);
   tmpstr.trim(g_BUnit.m_SqlDB.szServer);
   tf.ReadString("SQLSVR","DATABASE","gmdata",g_BUnit.m_SqlDB.szDatabase,sizeof(g_BUnit.m_SqlDB.szDatabase)-1);
   tmpstr.trim(g_BUnit.m_SqlDB.szDatabase);
   tf.ReadString("SQLSVR","LOGIN","sa",g_BUnit.m_SqlDB.szLogin,sizeof(g_BUnit.m_SqlDB.szLogin)-1);
   tmpstr.trim(g_BUnit.m_SqlDB.szLogin);
   tf.ReadString("SQLSVR","PASSWORD","",g_BUnit.m_SqlDB.szPassword,sizeof(g_BUnit.m_SqlDB.szPassword)-1);
   tmpstr.trim(g_BUnit.m_SqlDB.szPassword);
*******************************************************/
   tf.ReadString("DB2SVR","NAME","gmserver",g_SqlDB.szServer,sizeof(g_SqlDB.szServer)-1);
   tmpstr.trim(g_SqlDB.szServer);

	memset(szBuf,0,sizeof szBuf);
	tf.ReadString("DB2SVR","AUTH_TYPE","config",szBuf,sizeof(szBuf)-1);
	if(strcmp("config",szBuf) == 0)
	{
		// 从配置文件读取
   tf.ReadString("DB2SVR","DATABASE","gmdata",g_SqlDB.szDatabase,sizeof(g_SqlDB.szDatabase)-1);
   tmpstr.trim(g_SqlDB.szDatabase);
   tf.ReadString("DB2SVR","LOGIN","sa",g_SqlDB.szLogin,sizeof(g_SqlDB.szLogin)-1);
   tmpstr.trim(g_SqlDB.szLogin);
   tf.ReadString("DB2SVR","PASSWORD","",g_SqlDB.szPassword,sizeof(g_SqlDB.szPassword)-1);
   tmpstr.trim(g_SqlDB.szPassword);
	}
	else if(strcmp("env",szBuf) == 0)
	{
		// 从环境变量读取
		char* penv=NULL;
		if((penv = getenv("YKT_DBNAME")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("无法取得数据库名");
			exit(-1001);
		}
		strcpy(g_SqlDB.szDatabase,penv);
		tmpstr.trim(g_SqlDB.szDatabase);
		if((penv = getenv("YKT_USER")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("无法取得数据库连接用户名");
			exit(-1001);
		}
		strcpy(g_SqlDB.szLogin,penv);
		tmpstr.trim(g_SqlDB.szLogin);
   
		if((penv = getenv("YKT_PWD")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("无法取得数据库连接密码");
			exit(-1001);
		}
		strcpy(g_SqlDB.szPassword,penv);
		tmpstr.trim(g_SqlDB.szPassword);
	}
	else
	{
		DEBUG_RUNTIME_MSGOUT("数据库连接方式配置错误\n");
		exit(-1001);
	}
   tf.Close();
   return(true);   
}
int F847321(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int DoCronTask()
{
    int retcode=0;
    char sMsg[256]="";
    F847321(NULL,847321,NULL,&retcode,sMsg);
    sleep(60*60);
    return 0;
}

int main(int argc,char *argv[])
{
   int rtn;
   openlog("bucron",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL3);
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

   // 初始化数据库连接：
   SQLInitialize();
   if (SQLConnectToServer()!=0)
   {
      RAISE_RUNTIME_ERROR("不能正常建立数据库连接, 检查配置和数据库服务器!\n");
      return(-100);
   }
   // 初始化与BCC连接：
   do 
   {
      rtn = g_pSvrLink->ToLink(&g_BUnit);
      if (rtn==1)
      {
         DEBUG_RUNTIME_MSGOUT("与业务调度中心(BCC)的连接成功！\n");
         break;
      }
      else if (rtn==-100)
      {
         DEBUG_RUNTIME_MSGOUT("估计业务调度中心(BCC)尚未正式启动，或者检查配置中的[SERVER]项参数\n");
         mysleep(g_BUnit.iHBInterval);
      }
      else
      {
         // 应该属于故障，或对方并不是BCC
         return(rtn);
      }
   } while (1);

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
      if (!SQLIsConnectOK())
      {
         mysleep(1000);
         if (!g_pSvrLink->CheckLink()) 
            break;  // BCC exit (可能用户发现数据库连接断开，需要维护系统，导致手工将BCC退出同时也需要BU退出)
         if (SQLConnectToServer()!=0)
         {
            // SQL Link error:
            DEBUG_RUNTIME_MSGOUT("不能正常建立数据库连接, 检查配置和数据库服务器!\n");
         }
         else
         {
            DEBUG_RUNTIME_MSGOUT("与数据库连接成功!\n");
         }
         continue;
      }
      else 
      {
	  DoCronTask();
      }         
      if (g_pSvrLink->bExit) break;
   }


/* ****** Updated by CHENYH at 2004-4-14 11:07:19 ****** 
   经过测试后，CheckLink()工作正常，测试环境为：BCC(WIN)+BU(WIN),BCC(LINUX)+BU(WIN),BCC(LINUX)+BU(LINUX)
   while (1)
   {
      mysleep(1000);
      if (!g_SvrLink.CheckLink())
      {
         printf("TEST CHECK LINK return <false>!\n");
         break;
      }
   }
*/
   g_pSvrLink->Close();
   SQLExit();
   DEBUG_RUNTIME_MSGOUT("业务处理单元BU系统正常退出!\n");
   g_LogFile.Close();
   closelog();
   return(0);
}
