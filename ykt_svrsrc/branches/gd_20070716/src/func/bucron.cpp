#include "stdafx.h"
#include <stdio.h>
#include "profile.h"
#include "slist.h"
#include "cpack.h"
#include "busqc.h"  // �����sqc������ص�ȫ�ֱ����ͺ�������
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "esqlc.h"
#include "dbfunc.h"
#include "ksbu.h"
//#include "BDFunc.inl"

ST_BUNIT g_BUnit;    // ����ֻ�е�һҵ����Ԫ
ST_SQLDB g_SqlDB;
CSvrLink *g_pSvrLink;  // ��ҵ��������ĵ�����
ST_PACK *g_pArrays;	//���ʱʹ��
CLogFile g_LogFile;   // ���Ƶ�SvrLink.cpp�У���Ϊϵͳ��Ҫ������

TBDefine g_XBDefines[1];  // �ھ���ĺ������岿�֣���BDFTest.cpp -> BDFunc.inl��

/* ****** Updated by CHENYH at 2005-11-5 14:51:49 ****** 
����������bupub.cpp���Ƶ������Ϊ�˲�ͬϵͳ�����Լ��Ļ������е���
*******************************************************/
// ������: WriteAppInfo
// ���  : ������ 2004-3-22 15:34:38
// ����  : BCC���һ�����Ӻõ�BU�����һ��ˢ�º�̨�������Ա�ҵ��ģ�鲿���ܹ�����ش���
//     ע�⣺�ú������ڿ�ܳ����ڽ��յ�BCC��WriteAppInfo��ʱ����õġ�
// ����  : int 
// ����  : int bccBaseFuncNo
// ����  : int bccID
int WriteAppInfo(int bccBaseFuncNo,int bccID)
{
   return(0);
}

int ERR_DEAL(char *msg,int retcode)
{
   return(g_pSvrLink->Err_Deal(msg,retcode));
}

/* ****** Updated by CHENYH at 2005-11-5 14:50:13 ****** 
����������bdefine.cpp����ȡ��������Ϊ���ø���ϵͳ���е����������ĵ��÷���
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
   g_LogFile.Open("bulog");  // �ó���Ľ��̺���Ϊ����BU��־�ļ����Ŀ¼

   memset(&g_BUnit,0,sizeof(g_BUnit));
   printf("Begin to read ini-file:%s...\n",inifile);
   if (!tf.Open(inifile))
   {
      sprintf(szBuf,"���ܴ������ļ�<%s>\n",inifile);
      DEBUG_RUNTIME_MSGOUT(szBuf);
      exit(-1000);
   }
   g_LogFile.RemoveOverdueLogFile(tf.ReadInt("COMMON","LOGOVERDUE",10));
   //g_BUnit.iBUnitGourpID = tf.ReadInt("COMMON","GID",1);
   tf.ReadString("COMMON","GID","",g_BUnit.szBUGroupID,sizeof(g_BUnit.szBUGroupID)-1);
   tf.ReadString("BCC","BCCSVR","127.0.0.1:6666",szBuf,sizeof(szBuf)-1);
   if (!tmpstr.FillStrings(szBuf,':') || tmpstr.GetCount()<2)
   {
      sprintf(szBuf,"�����ļ�<%s>��������[BCC] BCCSVR=???? ����! ��ʽΪ��BCCSVR=xxx.xxx.xxx.xxx:port\n",inifile);
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
		// �������ļ���ȡ
   tf.ReadString("DB2SVR","DATABASE","gmdata",g_SqlDB.szDatabase,sizeof(g_SqlDB.szDatabase)-1);
   tmpstr.trim(g_SqlDB.szDatabase);
   tf.ReadString("DB2SVR","LOGIN","sa",g_SqlDB.szLogin,sizeof(g_SqlDB.szLogin)-1);
   tmpstr.trim(g_SqlDB.szLogin);
   tf.ReadString("DB2SVR","PASSWORD","",g_SqlDB.szPassword,sizeof(g_SqlDB.szPassword)-1);
   tmpstr.trim(g_SqlDB.szPassword);
	}
	else if(strcmp("env",szBuf) == 0)
	{
		// �ӻ���������ȡ
		char* penv=NULL;
		if((penv = getenv("YKT_DBNAME")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ���");
			exit(-1001);
		}
		strcpy(g_SqlDB.szDatabase,penv);
		tmpstr.trim(g_SqlDB.szDatabase);
		if((penv = getenv("YKT_USER")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ������û���");
			exit(-1001);
		}
		strcpy(g_SqlDB.szLogin,penv);
		tmpstr.trim(g_SqlDB.szLogin);
   
		if((penv = getenv("YKT_PWD")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ���������");
			exit(-1001);
		}
		strcpy(g_SqlDB.szPassword,penv);
		tmpstr.trim(g_SqlDB.szPassword);
	}
	else
	{
		DEBUG_RUNTIME_MSGOUT("���ݿ����ӷ�ʽ���ô���\n");
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

   // ��ʼ�����ݿ����ӣ�
   SQLInitialize();
   if (SQLConnectToServer()!=0)
   {
      RAISE_RUNTIME_ERROR("���������������ݿ�����, ������ú����ݿ������!\n");
      return(-100);
   }
   // ��ʼ����BCC���ӣ�
   do 
   {
      rtn = g_pSvrLink->ToLink(&g_BUnit);
      if (rtn==1)
      {
         DEBUG_RUNTIME_MSGOUT("��ҵ���������(BCC)�����ӳɹ���\n");
         break;
      }
      else if (rtn==-100)
      {
         DEBUG_RUNTIME_MSGOUT("����ҵ���������(BCC)��δ��ʽ���������߼�������е�[SERVER]�����\n");
         mysleep(g_BUnit.iHBInterval);
      }
      else
      {
         // Ӧ�����ڹ��ϣ���Է�������BCC
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
            break;  // BCC exit (�����û��������ݿ����ӶϿ�����Ҫά��ϵͳ�������ֹ���BCC�˳�ͬʱҲ��ҪBU�˳�)
         if (SQLConnectToServer()!=0)
         {
            // SQL Link error:
            DEBUG_RUNTIME_MSGOUT("���������������ݿ�����, ������ú����ݿ������!\n");
         }
         else
         {
            DEBUG_RUNTIME_MSGOUT("�����ݿ����ӳɹ�!\n");
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
   �������Ժ�CheckLink()�������������Ի���Ϊ��BCC(WIN)+BU(WIN),BCC(LINUX)+BU(WIN),BCC(LINUX)+BU(LINUX)
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
   DEBUG_RUNTIME_MSGOUT("ҵ����ԪBUϵͳ�����˳�!\n");
   g_LogFile.Close();
   closelog();
   return(0);
}
