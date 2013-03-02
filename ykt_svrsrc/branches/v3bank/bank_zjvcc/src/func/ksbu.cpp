#include "stdafx.h"
#include <stdio.h>
#include "profile.h"
#include "slist.h"
#include "cpack.h"
//#include "busqc.h"  // 与各个sqc程序相关的全局变量和函数定义
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
//#include "pubdb.h"
//#include "esqlc.h"
//#include "dbfunc.h"
#include "mypub.h"
#include "ksbu.h"
#include "bupub.h"
#include "BDFunc.inl"
/******************************
add by hhd at 2004-9-16 15:22
******************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
//#include "transinfo.h"
#include "shem.h"
#include "bank.h"

ST_BUNIT g_BUnit;    // 这里只有单一业务处理单元
ST_SQLDB g_SqlDB;
CSvrLink *g_pSvrLink;  // 与业务调度中心的连接
ST_PACK *g_pArrays;	//多包时使用
CLogFile g_LogFile;   // 被移到SvrLink.cpp中，作为系统必要的属性
extern TBDefine g_XBDefines[];  // 在具体的函数定义部分，如BDFTest.cpp -> BDFunc.inl中
ST_BANK_CONFIG g_Bank;

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
   char param[101]="";
#ifdef _DEBUG1
CMemoryState cm1, cm2, cm3;
#endif
   APPFUNC pFunc = g_XBDefines[fno].pFunc;

#ifdef _DEBUG1
	cm1.Checkpoint();
#endif
	*iRetCode=0;
	*szMsg=0;
	g_pArrays=pArrays;

	rtn = (*pFunc)(handle,rpack->head.RequestType,&rpack->pack,iRetCode,szMsg);
	if(rtn)
	{
	   	//char sErrMsg[101]="";
		//char sRetMsg[256]="";
		//if(*szMsg)
		//	snprintf(sRetMsg,256," %s",szMsg);
		//r=get_errcode_msg(*iRetCode, sErrMsg);
		//db_rollback();
		//snprintf(szMsg,256,"%s%s\n%s",sErrMsg,sRetMsg,g_sqlmsg);
		if(0==*iRetCode)
			*iRetCode=rtn;
		writelog(LOG_ERR,"Func[%d]ecode[%d]msg[%s]",rpack->head.RequestType,*iRetCode,szMsg);
		ERR_DEAL(szMsg,*iRetCode);
		/*
		if(r)
		{
			AnswerData(handle,*iRetCode,szMsg);
			db_disconnect();
			writelog(LOG_ERR,"数据库错误,系统退出");
			exit(1);
		}
		*/
	}
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
		/*
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
		*/
	}
	else
	{
		DEBUG_RUNTIME_MSGOUT("数据库连接方式配置错误\n");
		exit(-1001);
	}
   tf.Close();
   return(true);   
}

int ReadIni_bank(ST_BANK_CONFIG *p_bankini)
{
	TIniFile tf;
	ST_BANK_CONFIG t_bank;
	char szBuf[256];
	char bank_unit[10]="";
	char * pch;
	int j=0;
	
	memset(&t_bank,0,sizeof t_bank);
	if (!tf.Open(TRANS_INI_FILE))
	{
		writelog(LOG_ERR,"Cann't open ini file,file's name=[%s]",TRANS_INI_FILE);
		return -1;
	}
	t_bank.BankCount=tf.ReadInt("COMMON","BANK_UNIT",1);
	t_bank.BCC_BASEFUNCNO=tf.ReadInt("COMMON","BCC_BASEFUNCNO",9000);
	t_bank.DRTP_BRANCH=tf.ReadInt("COMMON","DRTP_BRANCH",7000);
	t_bank.TIMEOUT=tf.ReadInt("COMMON","TIMEOUT",5);
	t_bank.DRTP_PORT=tf.ReadInt("COMMON","DRTP_PORT",4000);
	tf.ReadString("COMMON","DRTP_IP","127.0.0.1",t_bank.DRTP_IP,sizeof(t_bank.DRTP_IP)-1);
	tf.ReadString("COMMON","COMPACC_TIME","06",t_bank.COMPACC_TIME,sizeof(t_bank.COMPACC_TIME)-1);
	t_bank.AUTH_MODE=tf.ReadInt("COMMON","AUTH_MODE",1);
	t_bank.LOGIN_MODE=tf.ReadInt("COMMON","LOGIN_MODE",1);
	t_bank.LOG_MODE=tf.ReadInt("COMMON","LOG_MODE",1);
	tf.ReadString("COMMON","SERV_TIME","010000-235959",t_bank.SERV_TIME,sizeof(t_bank.SERV_TIME)-1);
	t_bank.trans_money=tf.ReadInt("COMMON","TRANS_MONEY",100000);
	for(int i=0;i<t_bank.BankCount;i++)
	{
		j=0;
		sprintf(bank_unit,"BANK%d",i+1);
		tf.ReadString(bank_unit,"BANK_IP","26.136.2.9",t_bank.BankUnit[i].szBankIP,sizeof(t_bank.BankUnit[i].szBankIP)-1);
		t_bank.BankUnit[i].iBankID= tf.ReadInt(bank_unit,"BANK_ID",1);
		t_bank.BankUnit[i].iBankPort= tf.ReadInt(bank_unit,"BANK_PORT",5301);
		t_bank.BankUnit[i].iBankTimeout= tf.ReadInt(bank_unit,"BANK_DELAY_TIME",5000);
		t_bank.BankUnit[i].iAuthMode= tf.ReadInt(bank_unit,"AUTH_MODE",1);
		t_bank.BankUnit[i].compare_flag= tf.ReadInt(bank_unit,"COMPARE_FLAG",1);
		t_bank.BankUnit[i].sendcompreq_flag= tf.ReadInt(bank_unit,"SENDCOMPREQ_FLAG",0);
		t_bank.BankUnit[i].compare_count= tf.ReadInt(bank_unit,"COMPARE_COUNT",0);
		tf.ReadString(bank_unit,"BANK_ACCOUNT_NO","2011",t_bank.BankUnit[i].szBankAccountNO,sizeof(t_bank.BankUnit[i].szBankAccountNO)-1);	// 如果是多家银行, 此处需要填写一卡通的银行账户
		tf.ReadString(bank_unit,"BANK_CARD_RANGE","",szBuf,sizeof(szBuf)-1);
		tf.ReadString(bank_unit,"COMPARE_TIME","06",t_bank.BankUnit[i].compare_time,sizeof(t_bank.BankUnit[i].compare_time) - 1);
		tf.ReadString(bank_unit,"SENDCOMPREQ_TIME","05",t_bank.BankUnit[i].sendcompreq_time,sizeof(t_bank.BankUnit[i].sendcompreq_time) - 1);
		tf.ReadString(bank_unit,"COMP_FILE_PATH","/home",t_bank.BankUnit[i].comp_file_path,sizeof(t_bank.BankUnit[i].comp_file_path) - 1);
		//writelog(LOG_INFO,"COMP_FILE_PATH=[%s], BANK_CARD_RANGE=[%s], BANK_ACCOUNT_NO=[%s]", t_bank.BankUnit[i].comp_file_path, szBuf, t_bank.BankUnit[i].szBankAccountNO);
		pch = strtok (szBuf,",");
		while (pch != NULL)
		{
			des2src(t_bank.BankUnit[i].szBankCardRange[j], pch);
			pch = strtok (NULL, ",");
			//writelog(LOG_INFO,"BANKID=[%d], BANKCARDRAGNT=[%s], i=[%d], j=[%d]", t_bank.BankUnit[i].iBankID, t_bank.BankUnit[i].szBankCardRange[j], i, j);
			j++;
			if(j>=MAX_RANGE) 
				break;
		}
	}
	memcpy(p_bankini,&t_bank,sizeof(t_bank));
	tf.Close();
	return 0;   
}

void handler_alarm(int signum)
{
	// empty
}
int main(int argc,char *argv[])
{
	int rtn;
	int ret=0;
	openlog("yktbank",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL3);
	g_pSvrLink = BUPubInitialize(g_XBDefines,CallBDFunc,WriteAppInfo,&g_LogFile);
	SetLogShowLevel(0);
	if (argc<2)      ReadIni("ksbu.ini");
	else		     ReadIni(argv[1]);

	struct sigaction act,oldact;
	act.sa_handler = handler_alarm;
	if(-1==sigaction(SIGALRM,&act,&oldact))
	{
		writelog(LOG_ERR,"sigaction error,errcode=[%d]",-1);
		return -1;
	}


	ret=ReadIni_bank(&g_Bank);
	if(ret)
	{
		writelog(LOG_ERR,"ReadIni_bank error,errcode=[%d]",ret);
		return -1;
	}

	ResetBPFunctions();
	if (argc>2)
	{
	  ListBPFunctions(argv[2]);
	}

	// 初始化数据库连接：
	/*
	SQLInitialize();
	if (SQLConnectToServer()!=0)
	{
	  RAISE_RUNTIME_ERROR("不能正常建立数据库连接, 检查配置和数据库服务器!\n");
	  return(-100);
	}
	*/
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
			  DEBUG_RUNTIME_MSGOUT("未知错误\n");
			 return(rtn);
		}
	} while (1);
#ifdef WIN32
   setnoblockgetch();
#endif

/**********************************************************************
 Added by hhd at 2004-09-16
 为了增加签到处理，达到共享内存的处理
 增加共享内存和信号量
 共享内存一共1024个字节，其中使用前18个字节
 shm[0]:代表是否进行过签到的标志，如果为1，已经签过到但不知道是否成功
 		，后续业务将不能进行签到处理,如果为其他值，系统将进行签到
 shm[1]:代表签到是否成功的标志，如果为1，则标识签到成功，后续16个字节为
 		银行正常返回数据，可以使用
 shm[2~17]:前8个字节为加密的PIN密钥，后8个字节为加密的MAC密钥
***********************************************************************/
/**********************************************************************
 Update by hhd at 2004-10-27
 为了增加签到处理，达到共享内存的处理
 增加共享内存和信号量
 为了反映每个终端的当前工作状态，在共享内存中设置一个状态标志
 共享内存一共1024个字节，其中使用前26个字节
 shm[0]:代表是否进行过签到的标志，如果为1，已经签过到但不知道是否成功
 		，后续业务将不能进行签到处理,如果为其他值，系统将进行签到
 shm[1]:代表签到是否成功的标志，如果为1，则标识签到成功，后续16个字节为
 		银行正常返回数据，可以使用
 shm[2]:代表系统重新启动标志，如果不为1，系统进行初始化操作(进行设备
 		注册表中设备的状态的清空操作),然后系统将改标志置为1，其他BU启动
 		跳过该项操作
 shm[10~25]:前8个字节为加密的PIN密钥，后8个字节为加密的MAC密钥
***********************************************************************/
/*
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
		DEBUG_RUNTIME_MSGOUT("获取共享内存失败，请确保bankguard已经启动\n");
		return 	E_CREATE_SHARE_MEMORY;	
	}
	shm=(char*)shmat(shmid,0,0);
	if((int)shm==-1)
	{
		DEBUG_RUNTIME_MSGOUT("映射共享内存失败");
		return 	E_JOIN_SHARE_MEMORY;	
	}
	semid=semget(key,1,0);
	if(semid==-1)
	{
		DEBUG_RUNTIME_MSGOUT("获取共享锁id失败");
		return E_JOIN_SHARE_MEMORY;
	}
	*/
// Added by hhd end here
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
     // if (!SQLIsConnectOK())
     if(0)
      {
         mysleep(1000);
         if (!g_pSvrLink->CheckLink()) 
            break;  // BCC exit (可能用户发现数据库连接断开，需要维护系统，导致手工将BCC退出同时也需要BU退出)
         //if (SQLConnectToServer()!=0)
	if(0)
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
  	//DEBUG_RUNTIME_MSGOUT("处理bu业务!\n");
         g_pSvrLink->Processing(&g_BUnit);
      }
      //if (g_pSvrLink->bExit) break;
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
/*
	shmdt(shm);
	shmctl(shmid,IPC_RMID,&buf);
	d_sem(semid);
*/
	g_pSvrLink->Close();
	// SQLExit();
	DEBUG_RUNTIME_MSGOUT("业务处理单元BU系统正常退出!\n");
	g_LogFile.Close();
	closelog();
	return(0);
}




