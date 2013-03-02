#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include "shem.h"
#include "fdsqc.h"
#include "dbfunc.h"
#include "pubdb.h"
#include "errdef.h"
#include "logfile.h"
#include "profile.h"
#include "transinfo.h"
#include "bank.h"
#include "bankdb.h"


extern int debug;
ST_BUNIT g_BUnit;


#ifdef DEBUG
#define	TRACE	printf
#else
#define	TRACE	NULL
#endif

//#define writelog getpos(__FILE__,__LINE__),errlog


/**********************************************************************
 Added by hhd at 2004-09-16
**********************************************************************
 Updated by hhd at 2004-10-27
 Ϊ������ǩ�������ﵽ�����ڴ�Ĵ���
 ���ӹ����ڴ���ź���
 Ϊ�˷�ӳÿ���ն˵ĵ�ǰ����״̬���ڹ����ڴ�������һ��״̬��־
 �����ڴ�һ��1024���ֽڣ�����ʹ��ǰ26���ֽ�
 shm[0]:�����Ƿ���й�ǩ���ı�־�����Ϊ1���Ѿ�ǩ��������֪���Ƿ�ɹ�
 		������ҵ�񽫲��ܽ���ǩ������,���Ϊ����ֵ��ϵͳ������ǩ��
 shm[1]:����ǩ���Ƿ�ɹ��ı�־�����Ϊ1�����ʶǩ���ɹ�������16���ֽ�Ϊ
 		���������������ݣ�����ʹ��
 shm[2]:����ϵͳ����������־�������Ϊ1��ϵͳ���г�ʼ������(�����豸
 		ע������豸��״̬����ղ���),Ȼ��ϵͳ���ı�־��Ϊ1������BU����
 		�����������
 shm[10~25]:ǰ8���ֽ�Ϊ���ܵ�PIN��Կ����8���ֽ�Ϊ���ܵ�MAC��Կ

 ----------------
 Updated by lq at 2005-03-10
 ��ǩ����������ͨ�ż�⼯�е�������(bankguard)�д���ͨ�������ڴ�������ת��bu����
 Ϊ��������һ���ԣ���д�����ڴ���ͨ���ź�������ͬ��
 shm[3]:ͨ��״����־�����Ϊ1����ʾͨ���쳣��buӦ��ֱ�Ӿܾ�����
***********************************************************************/


void SQLDebugLog(int errorcode,char *fmt,...)
{
	va_list args;
	char msg[4096] = "";
	char body[3840] = "";

	va_start(args, fmt);
	vsprintf(body, fmt, args);
	va_end(args);

	sprintf(msg, "SQL ERROR[%d]-%s", errorcode, body);
	syslog(LOG_ERR, msg);

}

bool ReadIni(char *inifile)
{
   TIniFile tf;

   char szBuf[256];
   memset(&g_BUnit,0,sizeof(g_BUnit));
   if (!tf.Open(inifile))
   {
      writelog(LOG_ERR,"���ܴ������ļ�<%s>\n",inifile);
      return false;
   }


   tf.ReadString("DB","DB_NAME","test",g_BUnit.m_SqlDB.szDatabase,sizeof(g_BUnit.m_SqlDB.szDatabase)-1);
   tf.ReadString("DB","DB_USER","db2inst4",g_BUnit.m_SqlDB.szLogin,sizeof(g_BUnit.m_SqlDB.szLogin)-1);
   tf.ReadString("DB","DB_PASSWORD","db2inst4",g_BUnit.m_SqlDB.szPassword,sizeof(g_BUnit.m_SqlDB.szPassword)-1);

   tf.Close();
   return(true);
}

int	app_flag = 0;
#define APP_FLAG_DAEMON	0x0001
#define APP_FLAG_CONFIG	0x0002
#define APP_FLAG_DEBUG	0x0004
#define APP_FLAG_TERM	0x8000

void sig_handler(int signo)
{
	switch(signo)
	{
	case	SIGINT:
	case	SIGTERM:
		app_flag |= APP_FLAG_TERM;
		break;
	default:
		break;
	}
}

int main(int argc,char *argv[])
{
	int	_pid = 0;
	int 	ret=0;
	key_t 	key;
	int intping = 60;	// ping���м��
	int intflush = 60;	// �������
	int inttrans = 60;	//�������
	int intcomp = 10;	//����ʱ����
	struct 	shmid_ds buf;

	BANK_TRANS_REQUEST	bank_trans;

   	int opt;
   	extern int optind;
   	extern char *optarg;

	while ((opt = getopt(argc, argv, "bdvhi:p:f:")) != EOF)
	{
		switch(opt)
		{
		case 'v':
			printf("bank guard version 1.0.2.10\n");
			return 0;
		case 'b':
			app_flag |= APP_FLAG_DAEMON;
			break;
		case 'd':
			app_flag |= APP_FLAG_DEBUG;
			debug = 2;
			break;
		case 'i':
			app_flag |= APP_FLAG_CONFIG;
			ReadIni(optarg);
			break;
		case 'p':
			intping = atol(optarg);
			break;
		case 'f':
			intflush = atol(optarg);
			break;
		case '?':
		case 'h':
		default:
			printf("usage: %s -options \n", argv[0]);
			printf("\toptions:\n");
			printf("\t-b\t\trun as daemon\n");
			printf("\t-d\t\trun in debug mode, communication content will be printed to stdout\n");
			printf("\t-h\t\tshow this help message\n");
			printf("\t-i inifile\tassign config file\n");
			printf("\t-p ping_interval\tassign the interval between each ping\n");
			printf("\t-f flush_interval\tassign the interval between each database process\n");
			return 0;
		}
	}

 	// �����ź�
	signal(SIGPIPE, sig_handler);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGCHLD, sig_handler);

 	if((app_flag&APP_FLAG_CONFIG) == 0)
		ReadIni("trans.ini");

	if((app_flag&APP_FLAG_DAEMON)!= 0)
 	{
 		_pid=fork();
		if(_pid != 0)
			exit(0);
		else if(_pid< 0)
			exit(1);

		setsid();
		_pid=fork();
		if(_pid != 0)
			exit(0);
		else if(_pid< 0)
			exit(1);

		int i;
		for(i=3;i<20;++i)
			close(i);

		//umask(0);
 	}

    	openlog("bank",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL4);

	// ��ʼ�����ݿ����ӣ�
	SQLInitialize();
	ret = SQLConnectToServer();
	if (ret!=0)
	{
		writelog(LOG_ERR,"�������ݿ�ʧ��[%d]", ret);
		//printf("�������ݿ�ʧ��database %s, username %s, password %s, [%d]", g_BUnit.m_SqlDB.szDatabase,g_BUnit.m_SqlDB.szLogin,g_BUnit.m_SqlDB.szPassword, ret);
		printf("�������ݿ�ʧ��\n");
		return 	E_DB_DBCONN;
	}

   	//���������ڴ�
	key=ftok(".",0);
	shmid=shmget(key,SEGSIZE,IPC_CREAT|0666);
	if(-1==shmid)
	{
		writelog(LOG_ERR,"���������ڴ�ʧ��[%d]",shmid);
		printf("���������ڴ�ʧ��\n");
		return 	E_CREATE_SHARE_MEMORY;
	}
	shm=(char*)shmat(shmid,0,0);
	if((int)shm==-1)
	{
		writelog(LOG_ERR,"���ӹ����ڴ�ʧ��[%d]",shm);
		printf("���ӹ����ڴ�ʧ��\n");
		return 	E_JOIN_SHARE_MEMORY;
	}


	//������������豸ǩ�����ǰ�û�ǩ��
	semid=sem(key);
	if((int)semid==-1)
	{
		writelog(LOG_ERR,"�����ź���ʧ��[%d]",semid);
		printf("�����ź���ʧ��\n");
		return 	E_JOIN_SHARE_MEMORY;
	}

	p(semid);

	//��ʼ�������ڴ�
	memset(shm, 0, SEGSIZE);
	shm[0]=0;
	shm[1]=0;
	writelog(LOG_INFO,"�����ù����ڴ�");
	ret=DB_t_pif_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	//if(ret)
	if((ret!=0)&&(ret!=100))
	{
		writelog(LOG_ERR,"DB_t_pif_device_update_by_subsystem_type error,errcode=[%d]",ret);
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	ret;
	}

	shm[2]=1;
	writelog(LOG_ERR,"�������豸��");

	//�����˳�
	v(semid);

	//writelog(LOG_INFO,"���нӿڳ�ʼ����ɣ�bank_bu����������");
	//printf("���нӿڳ�ʼ�����\n");

	time_t	now = 0;
	time_t 	lastping = 0;		// �ϴ�ping����ʱ��
	time_t	lastflush = 0;		// �ϴδ������ʱ��
	time_t	lasttrans=0;		//�ϴ���ͼ���񻮲���ʱ��
	time_t	lastcomp=0;		//�ϴ���ͼ���ж��ʵ�ʱ��
	T_t_tif_tradeserial  tradeserial; //��������ˮ������������

	// ��������
	while(true)
	{
		if((app_flag&APP_FLAG_TERM) != 0)
		{
			writelog(LOG_INFO,"�յ���ֹ�źţ��˳�");
			break;
		}

		// ���������ͨ�����

		now = time(0);
		if((now - lastping) > intping)
		{

			lastping = now;
			if(shm[1] != 1)
			{
				//����ϵͳ��½���޸ĵ�½��־
				p(semid);

				writelog(LOG_INFO,"��ʼ��½����");
				printf("���ڵ�½����...\n");

				shm[0]=1;
				ret=Do_Login(&bank_trans);
				if(ret!=0)
				{
					writelog(LOG_ERR,"��½����ʧ��[%d]",ret);
					printf("----------��½����ʧ��----------\n");
				}
				else
				{
					writelog(LOG_INFO,"��½���гɹ�");
					printf("----------��½���гɹ�----------\n");
					shm[1]=1;
					shm[3]=0;
					memcpy(shm+10,bank_trans.BankCardPwd,sizeof(bank_trans.BankCardPwd));

					ret=call_240006();
					if((ret!=0)&&(ret!=100))
					{
						writelog(LOG_ERR,"Call 240006 error,errcode=[%d]",ret);
						shmdt(shm);
						shmctl(shmid,IPC_RMID,&buf);
						d_sem(semid);
						return 	ret;
					}

					shm[2]=1;
					writelog(LOG_INFO,"�������豸��");

					char buffer[100]="";
					int k=0;
					for(int i=0;i<16;i++)
					{
						k=bank_trans.BankCardPwd[i];
						sprintf(&buffer[2*i],"%02X",k);
					}
					writelog(LOG_INFO,"BankCardPwd=[%s]",buffer);
				}
				v(semid);
				continue;
			}

			ret=Do_CheckLine(&bank_trans);
			if(ret != 0)	// ret?
			{
				writelog(LOG_ERR,"�����е�ͨ�ſ����ж�[%d]",ret);
				p(semid);
				shm[1]=0;	// �õ�½��־��// �Ƿ��б�Ҫ���µ�½����
				shm[3]=1;	// ��ͨ�ű�־
				v(semid);
			}
			else if(shm[3] == 1)
			{
				writelog(LOG_ERR,"�����е�ͨ�Żָ�[%d]",ret);
				p(semid);
				shm[3]=0;	// ��ͨ�ű�־
				v(semid);
			}

		}

		//��������
		now = time(0);
		if((now - lastflush) > intflush)
		{
			lastflush = now;
			//��ȡ��һ��������¼��״̬Ϊ��������ϴγ���ʱ������
			//RESERVE_1��Ϊ�յ���Ϊ�����ɹ�
			ret = call_240004(&tradeserial);
			if( ret == 0)
			{
				ret = Do_DeTrans(&tradeserial,&bank_trans); 
				if(ret == 0)
				{
					// ���¸ó�����¼״̬������ʱ�䡢������
					// �������ж���ˮ��BankSn
					if(0!=strncmp(bank_trans.RetCode,RET_BANK_OK,2))
					{
						writelog(LOG_ERR,"����ʧ��,retcode=[%2.2s]",bank_trans.RetCode);
						ret=call_240005();
					}
					else
					{
						writelog(LOG_INFO,"����������¼�ɹ�[%ld]", tradeserial.serial_no);
						memcpy(tradeserial.reserve_1, bank_trans.BankSn, sizeof(bank_trans.BankSn));
						ret=call_240005();
					}
				}
				else
				{
					writelog(LOG_INFO,"����������¼ʧ��[%ld]", tradeserial.serial_no);
					ret=call_240005();
				}
			}
		}

		//�����ж���
		char buffer[20]="";
		int ho_OpCount=0;
		double ho_Fee_Change=0;
		int ret=0;
		now = time(0);
		if((now - lastcomp) > intcomp)
		{
			lastcomp=now;
			//�ж�ϵͳʱ���Ƿ񵽴���6��
			if(0==memcmp("06",getsystime(NULL),2))
			{
				ret=call_240007();
				if(ret)
				{
					writelog(LOG_ERR,"Do_Compare_file error[%d]", ret);
				}
				writelog(LOG_ERR,"Do_Compare_file complete");
			}
		}
		// ����
		sleep(5);//13938470950

	}

	p(semid);
	shm[3]=0;	// ��ͨ�ű�־
	v(semid);

	shmdt(shm);
	shmctl(shmid,IPC_RMID,&buf);
	d_sem(semid);

	SQLExit();
	writelog(LOG_INFO, "���������˳�");
	printf("���������˳�\n");
	return(0);
}
