#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include "profile.h"
#include "slist.h"
#include "cpack.h"
#include "fdsqc.h"  // �����sqc������ص�ȫ�ֱ����ͺ�������
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"

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
static void sig_alarm_handler(int signum)
{
}

#endif



ST_BUNIT g_BUnit;    // ����ֻ�е�һҵ����Ԫ
ST_SQLDB *pSqlDB;
CSvrLink g_SvrLink;  // ��ҵ��������ĵ�����
int iThisProcID;     // ��ҵ����Ԫ��ID��ʶ����Ӧ�÷���ܹ����䣬ҵ����ģ�������Ϊ������ϵͳ��Ψһ������OutErrorFile��Ϊ�ļ�����¼���������� 
CLogFile g_LogFile;
char iDefaultAnswerMode=AM_AUTO;   // ��ϵͳȱʡ��Ӧ��ģʽ������������ϵͳ���Եı�������趨

bool ReadIni(char *inifile)
{
	TIniFile tf;
	CSList tmpstr;

	char szBuf[256];
	char * penv = NULL;
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

	tf.ReadString("DB2SVR","NAME","gmserver",g_BUnit.m_SqlDB.szServer,sizeof(g_BUnit.m_SqlDB.szServer)-1);
	tmpstr.trim(g_BUnit.m_SqlDB.szServer);

	memset(szBuf,0,sizeof szBuf);
	tf.ReadString("DB2SVR","AUTH_TYPE","config",szBuf,sizeof(szBuf)-1);
	if(strcmp("config",szBuf) == 0)
	{
		// �������ļ���ȡ
		tf.ReadString("DB2SVR","DATABASE","gmdata",g_BUnit.m_SqlDB.szDatabase,sizeof(g_BUnit.m_SqlDB.szDatabase)-1);
		tmpstr.trim(g_BUnit.m_SqlDB.szDatabase);
		tf.ReadString("DB2SVR","LOGIN","sa",g_BUnit.m_SqlDB.szLogin,sizeof(g_BUnit.m_SqlDB.szLogin)-1);
		tmpstr.trim(g_BUnit.m_SqlDB.szLogin);
		tf.ReadString("DB2SVR","PASSWORD","",g_BUnit.m_SqlDB.szPassword,sizeof(g_BUnit.m_SqlDB.szPassword)-1);
		tmpstr.trim(g_BUnit.m_SqlDB.szPassword);
	}
	else if(strcmp("env",szBuf) == 0)
	{
		// �ӻ���������ȡ
		if((penv = getenv("YKT_DBNAME")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ���");
			exit(-1001);
		}
		strcpy(g_BUnit.m_SqlDB.szDatabase,penv);
		tmpstr.trim(g_BUnit.m_SqlDB.szDatabase);
		if((penv = getenv("YKT_USER")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ������û���");
			exit(-1001);
		}
		strcpy(g_BUnit.m_SqlDB.szLogin,penv);
		tmpstr.trim(g_BUnit.m_SqlDB.szLogin);

		if((penv = getenv("YKT_PWD")) == NULL)
		{
			DEBUG_RUNTIME_MSGOUT("�޷�ȡ�����ݿ���������");
			exit(-1001);
		}
		strcpy(g_BUnit.m_SqlDB.szPassword,penv);
		tmpstr.trim(g_BUnit.m_SqlDB.szPassword);
	}
	else
	{
		DEBUG_RUNTIME_MSGOUT("���ݿ����ӷ�ʽ���ô���\n");
		exit(-1001);
	}
	tf.Close();
	return(true);   
}



int main(int argc,char *argv[])
{
	int rtn;
	pSqlDB = &(g_BUnit.m_SqlDB); // ���ⲿ�����飬��Ҫ����DEBUGSQLERROR(msg)
	g_BUnit.pSvrLink = &g_SvrLink;
	g_LogFile.SetFlushDelay(0);
	g_LogFile.Open("bulog");
	openlog("yktbase",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL0);
	memset(pSqlDB,0,sizeof(ST_SQLDB));
	//puts("Before Reading ini...");
	if (argc<2)
		ReadIni("fdsvrall.ini");
	else
		ReadIni(argv[1]);
	DEBUG_RUNTIME_MSGOUT("�������ļ�end");
	ResetBPFunctions();
	if (argc>2)
	{
		ListBPFunctions(argv[2]);
	}

	pSqlDB->bConnected = 0;   

	// ��ʼ�����ݿ����ӣ�
	SQLInitialize();
	if (SQLConnectToServer()!=0)
	{
		DEBUG_RUNTIME_MSGOUT("���������������ݿ�����, ������ú����ݿ������!\n");
		g_LogFile.Close();
		closelog();
		return(-100);
	}
#ifndef WIN32
	struct sigaction sigact;
	memset(&sigact,0,sizeof sigact);
	sigact.sa_handler = sig_alarm_handler;

	sigaction(SIGALRM,&sigact,NULL);
#endif
	// ��ʼ����BCC���ӣ�
	DEBUG_RUNTIME_MSGOUT("�������ݿ�ɹ�!\n");
	do 
	{
		rtn = g_SvrLink.ToLink(&g_BUnit);
		if (rtn==1)
		{
			puts("��ҵ���������(BCC)�����ӳɹ���\n");
			break;
		}
		else if (rtn==-100)
		{
			DEBUG_RUNTIME_MSGOUT("����ҵ���������(BCC)��δ��ʽ���������߼�������е�[SERVER]�����\n");
			puts("sleep waiting for connect  BCC!");
			mysleep(g_BUnit.iHBInterval);
		}
		else
		{
			g_LogFile.Close();
			closelog();
			return(rtn);
		}
	} while (1);
	setnoblockgetch();

	while (g_SvrLink.LinkOK())
	{
		/*
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
		   printf("Enter command to select:\n");
		   break;
		   case 'x':
		   case 'X':
		   g_SvrLink.bExit = true;
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
		   */
		TestSQLConnect();
		if (pSqlDB->bConnected==0)
		{
			mysleep(1000);
			if (!g_SvrLink.CheckLink()) 
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
			g_SvrLink.Processing(&g_BUnit);
		if (g_SvrLink.bExit) break;
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
	g_SvrLink.Close();
	closelog();
	SQLExit();
	DEBUG_RUNTIME_MSGOUT("ҵ����ԪBUϵͳ�����˳�!\n");
	g_LogFile.Close();
	return(0);
}




/* ****** Updated by CHENYH at 2004-3-10 22:17:31 ****** 
// ������: SetCol
// ���  : ������ 2004-2-8 23:26:38
// ����  : ����CPACK����λͼ�����Ѿ���PutRow��������ݼ�¼�����ϴ����ݴ�����͸�ԭ�����
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : void *handle �� ��ʱ�Ͷ�Ӧ�� TRUSERID *, �ڱ�ϵͳû�����壬��Ϊ���̵߳�Ե��
// ����  : ...  �� F_XXXXX ���������ֶ��б��� 0��ʾ��������handle��Ϊ0�������λͼ��������λͼ
*/
int SetCol(TRUSERID *handle,...)
{
	va_list ap;
	int arg;
	ST_PACKHEAD head;
	memset(&head,0,sizeof(head));
	va_start(ap, handle);
	while ((arg = va_arg(ap, int)) != 0)
	{
		SetParmBit( &head, arg);
	}
	va_end(ap);
	return(g_SvrLink.SetCol(handle,head.ParmBits));
}



// ������: PutRowData
// ���  : ������ 2004-2-8 23:30:07
// ����  : �������CPACK����������һ��ST_PACK�����¼��ʵ�ʶ�֮ǰ��SetCol������ֶ���Ч��û�ж������Ч
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : ST_PACK *pdata  �� ���ӵ�ST_PACK�������
int PutRowData(ST_PACK *pdata)
{
	return(g_SvrLink.PutRowData(pdata));
}


// ������: AnswerData
// ���  : ������ 2004-2-8 23:32:42
// ����  : ��ruserid�Ŀͻ��ˣ�������SetCol��PutRowData���õ�Ӧ�𷵻ص�����
// ����  : int 
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg)
{
	return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,0));
}


// ������: AnswerDataPart
// ���  : ������ 2004-2-12 12:12:09
// ����  : ��AnswerData���ƣ���������֪ͨ�ͻ��ˣ����и�������ݷ���
//         �����ڽ��д��������ݷ��أ�������������ͬ����Ϊ�˲��ÿͻ��˳�ʱ��ȴ�
//         �ȷ��Ͳ������ݡ�
// ����  : int 
// ����  : TRUSERID *ruserid
// ����  : int retcode
// ����  : char *szmsg
int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg)
{
	return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,1));
}

// ������: AnswerDataEx
// ���  : ������ 2004-2-8 23:37:00
// ����  : ��ruserid�Ŀͻ��ˣ�����apack��pArrays���Ӧ�𷵻ص�����
// ����  : int 
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : ST_CPACK *apack  Ӧ������ͷ���ױ���
// ����  : ST_PACK *pArrays �������ݱ��壬��apack->head.RetCount<=1ʱ����Ч ������дΪNULL
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg)
{
	return(g_SvrLink.AnswerDataEx(ruserid,apack,pArrays,retcode,szmsg));
}

// ������: PushData
// ���  : ������ 2004-2-8 23:43:01
// ����  : ��һ����Ϊ����ʽע���Ŀ��㣬��������
// ����  : int 
// ����  : int sourceno  ��������ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    �������ݵ�Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ը�Ŀ���Ự���κ�
// ����  : ST_CPACK *ppack  ���͵����ݰ���ppack->head.RetCount<=1�����������ݲ��ܳ���1�������¼
// ����  : char pushmode  ����ģʽ�������������PM_xxx
// ����  : int acktime   ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime)
{
	return(g_SvrLink.PushData(sourceno,destno,funcno,batchno,ppack,pushmode,acktime));
}



/* ****** Updated by CHENYH at 2004-3-10 23:27:14 ****** 
// ������: PushRow
// ���  : ������ 2004-3-5 15:12:18
// ����  : ��һ����Ϊ����ʽע���Ŀ��㣬��������
// ����  : int 
// ����  : int sourceno ��������ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno   �������ݵ�Ŀ��ͨѶƽ̨���
// ����  : int funcno   Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : ST_PACK *pack ���͵����ݰ��壬ʵ�ʵ�����λͼ��SetCol����
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int batchno   ��Ը�Ŀ���Ự���κ�
// ����  : int acktime   ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushRow(int sourceno,int destno,int funcno,ST_PACK *pack,char pushmode,int batchno,int acktime)
{
return(g_SvrLink.PushRow(sourceno,destno,funcno,pack,pushmode,batchno,acktime));
}

*/

// ������: ExtCall
// ���  : ������ 2004-3-6 17:47:14
// ����  : ������һ������㷢������Ҫ��Է�����Ӧ�𷵻أ������ܳ������ڲ�ͬϵͳ֮��ĶԽӣ���Ҫ��������Χϵͳ����
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����
// ����  : int sourceno  ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ŀ���Ự���κ� (���ȷ����Ը�Ŀ��㣬����������������ģʽ�������ֱ����дΪ0)
// ����  : int acktime   ���������Чʱ�䣬�����
// ����  : ST_CPACK *rpack  ���������
// ����  : ST_CPACK *apack  Ŀ���Ӧ������ݷ���
// ����  : ST_PACK *pArrays Ӧ�����ݺ���������
int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays)
{
	return(g_SvrLink.ExtCall(sourceno,destno,funcno,batchno,acktime,rpack,apack,pArrays));
}



// ������: ExtCallNext
// ���  : ������ 2004-3-8 17:31:47
// ����  : �ڵ���ExtCall֮�󣬷��ֶԷ��������ݻ�û��ȡ���������ñ����ܻ�ȡ��������
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����-3:�Ѿ�ȡ���˺�������
// ����  : int acktime
// ����  : ST_CPACK *apack
// ����  : ST_PACK *pArrays
int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays)
{
	return(g_SvrLink.ExtCallNext(acktime,apack,pArrays));
}


// ������: PushDataEx
// ���  : ������ 2004-2-9 0:10:53
// ����  : ��pushdests�������Ϊ����ʽע��Ŀ�����������
// ����  : int 
// ����  : TPUSHDEST *pushdests �����Ŀ����б�
// ����  : int pdcount  Ŀ���ĸ���
// ����  : ST_CPACK *ppack ���͵Ĳ�����һ����¼�����ݰ�
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int acktime  ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime)
{
	return(g_SvrLink.PushDataEx(pushdests,pdcount,ppack,pushmode,acktime));
}



/* ****** Updated by CHENYH at 2004-3-10 23:27:31 ****** 
// ������: PushRowEx
// ���  : ������ 2004-3-5 17:50:56
// ����  : ��pushdests�������Ϊ����ʽע��Ŀ����������� �������Զ������˰�ͷ����ҵ����벿��ֻ�ܿ��ư��壩
// ����  : int 
// ����  : TPUSHDEST *pushdests �����Ŀ����б�
// ����  : int pdcount  Ŀ���ĸ���
// ����  : ST_PACK *pack ���͵�һ����¼��ʵ�ʵ�����λͼ��SetCol����
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int batchno   ��Ը���Ŀ���Ự�����κ� �������ͬ�����κţ�ע����Ҫ�޸ģ�
// ����  : int acktime  ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushRowEx(TPUSHDEST *pushdests,int pdcount,ST_PACK *pack,char pushmode,int batchno,int acktime)
{
return(g_SvrLink.PushRowEx(pushdests,pdcount,pack,pushmode,batchno,acktime));
}
*/

// ������: PutRow
// ���  : ������ 2004-2-20 10:03:04
// ����  : һ�������PutRowData �� AnswerData, ���ǲ������Ϸ��� ��Ϊ������а汾���ݣ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : ST_PACK *pdata
// ����  : int *pRetCode
// ����  : char *rtnMsg
int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg)
{
	return(g_SvrLink.PutRow(handle,pdata,*pRetCode,rtnMsg));
}



// ������: ERR_DEAL
// ���  : ������ 2004-2-22 16:39:51
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ��Ϊ���뼯�н��׼��ݣ�
// ����  : int SendMsg������Ϣ
// ����  : char *msg
// ����  : int retcode
int ERR_DEAL(char *msg,int retcode)
{
	return(g_SvrLink.Err_Deal(msg,retcode));
}


// ������: Error_Deal
// ���  : ������ 2004-2-22 16:43:34
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ ������ϵͳʹ�ñ��������ԭ����ERR_DEAL
//         �ϲ���ԭ����Ҫ��sprintf����omsg
// ����  : int SendMsg������Ϣ
// ����  : int retcode
// ����  : char *omsg  OUT
// ����  : char *pFormat IN
// ����  : ... IN
int Error_Deal(int retcode,char *omsg,char *pFormat,...)
{
	va_list pArg;
	va_start(pArg,pFormat);
	vsprintf(omsg,pFormat,pArg);
	va_end(pArg);
	return(ERR_DEAL(omsg,retcode));
}


// ������: SQLDebugLog
// ���  : ������ 2004-3-4 17:45:16
// ����  : ר��Ϊ��SQCʹ�ã���C��ʹ�õģ���¼��Ϣ��LOG��־��
// ����  : void 
// ����  : int errorcode
// ����  : char *pFormat
// ����  : ...
void SQLDebugLog(int errorcode,char *pFormat,...)
{
	char omsg[1024];
	va_list pArg;
	va_start(pArg,pFormat);
	vsprintf(omsg,pFormat,pArg);
	va_end(pArg);
	g_LogFile.WriteLogEx(errorcode,"%s",omsg);   
}


// ������: CheckProcCancel
// ���  : ������ 2004-3-10 15:44:20
// ����  : ����Ƿ񱾴�������ǰ̨�Ƿ�Ҫ��ֹͣ��ע�⣺�������Ҫ����������Ƿ��и�ֹͣ������ᵼ�µ�1���룬��ʹ�ô���Ч�ʽ���
// ����  : int 1:��ʾǰ̨��Ҫ��ֹͣ�����0:û��
int CheckProcCancel()
{
	if (g_SvrLink.CheckProcCancel())
		return(1);
	else 
		return(0);
}

// ������: SetAnswerMode
// ���  : ������ 2004-3-10 18:48:18
// ����  : ����Ӧ��ģʽ����AM_xxxx�Ķ���
// ����  : int 
// ����  : char iAnswerMode ��AM_xxxx�Ķ���
int SetAnswerMode(char iAnswerMode)
{
	return(g_SvrLink.SetAnswerMode(iAnswerMode));
}


// ������: BCCMsgLogOut
// ���  : ������ 2004-3-10 19:31:25
// ����  : ��BCC���������BU���ı���־��Ϣ
// ����  : int 
// ����  : int logid ������־��ID��
// ����  : char *pFormat ���ı���־�ĸ�ʽ����
// ����  : ... ����pFormat������������
int BCCMsgLogOut(int logid,char *pFormat,...)
{
	char omsg[1024];
	va_list pArg;
	va_start(pArg,pFormat);
	vsprintf(omsg,pFormat,pArg);
	va_end(pArg);
	return(g_SvrLink.BCCLogOut(LT_MSG,logid,strlen(omsg),omsg));
}


// ������: ResetNormalCPack
// ���  : ������ 2004-3-11 20:30:59
// ����  : ���ݱ�ҵ�������������һ��CPACK��ͷ��λͼ�����ݶ��������
// ����  : void 
// ����  : ST_CPACK *pack
void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount)
{
	g_SvrLink.ResetNormalCPack(pack,nextflag,recCount);
}


// ������: SetMaxRow
// ���  : ������ 2004-3-22 11:41:26
// ����  : ���ñ��ι��ܴ���ʱ��ÿ��Ӧ������ص�����¼����ֻ�Ա��ι��ܴ�����Ч
// ����  : int 
// ����  : int maxrows
int SetMaxRow(int maxrows)
{
	return(g_SvrLink.SetMaxRow(maxrows));
}


// ������: SetBUError
// ���  : ������ 2004-3-22 11:42:37
// ����  : ���ñ�BU������Ϣ�������ṩ��ǰ�˳���
// ����  : int 
// ����  : int errcode
// ����  : char *pFormat
// ����  : ...
int SetBUError(int errcode,char *pFormat,...)
{
	char omsg[1024];
	va_list pArg;
	va_start(pArg,pFormat);
	vsprintf(omsg,pFormat,pArg);
	va_end(pArg);
	return(g_SvrLink.SetBUError(errcode,omsg));   
}


// ������: SetAnswerTimeout
// ���  : ������ 2004-3-22 12:49:02
// ����  : �趨��ҵ��ÿ��Ӧ����ĳ�ʱʱ�䣬�Ժ���ƣ���������������ʱ������Ĵ���
// ����  : int 
// ����  : unsigned int atimeout  ָ���ĳ�ʱʱ�䣨�Ժ���ƣ�
int SetAnswerTimeout(unsigned int atimeout)
{
	return(g_SvrLink.SetAnswerTimeout(atimeout));
}

// ������: WriteAppInfo
// ���  : ������ 2004-3-22 15:34:38
// ����  : BCC���һ�����Ӻõ�BU�����һ��ˢ�º�̨�������Ա�ҵ��ģ�鲿���ܹ�����ش���
// ����  : int 
// ����  : int bccBaseFuncNo
// ����  : int bccID
int WriteAppInfo(int bccBaseFuncNo,int bccID)
{
	// ������Ҫ����ҵ�����Ͳ�ͬ����Ӧ����

	return(0);
}



// ������: ResetAnswerData
// ���  : ������ 2004-3-24 22:16:17
// ����  : ��������Ѿ��ύ��Ӧ�����ݣ�����������ִ��һ������������Ϊ����������Retry
// ����  : int 
int ResetAnswerData()
{
	return(g_SvrLink.ResetAnswerData());
}


// ������: CopyAnswerHead
// ���  : ������ 2004-4-15 9:24:20
// ����  : ���ύ�����󷽵�Ӧ������ݰ�ͷ���Ƶ�ָ����phead��
// ����  : void 
// ����  : ST_PACKHEAD *phead �����ư�ͷ�Ļ���
void CopyAnswerHead(ST_PACKHEAD *phead)
{
	g_SvrLink.CopyAnswerHead(phead);
}
