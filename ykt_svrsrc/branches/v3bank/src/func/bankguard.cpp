#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include "shem.h"
#include "cpack.h"
#include "pubfunc.h"
#include "bupub.h"
#include "errdef.h"
#include "logfile.h"
#include "profile.h"
#include "bank.h"
#include "transinfo.h"
#include "yktclt.h"


int debug;
ST_BANK_CONFIG g_Bank;

#ifdef DEBUG
#define	TRACE	printf
#else
#define	TRACE	NULL
#endif

#define GET_PACK_STR(c,p,v) do {c.GetStringFieldByName(p,v,sizeof(v)-1); }while(0)


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
	tf.ReadString("COMMON","SENDCOMPREQ_TIME","05",t_bank.SENDCOMPREQ_TIME,sizeof(t_bank.SENDCOMPREQ_TIME)-1);
	t_bank.AUTH_MODE=tf.ReadInt("COMMON","AUTH_MODE",1);
	t_bank.LOGIN_MODE=tf.ReadInt("COMMON","LOGIN_MODE",1);
	t_bank.LOG_MODE=tf.ReadInt("COMMON","LOG_MODE",1);
	tf.ReadString("COMMON","SERV_TIME","060000-235959",t_bank.SERV_TIME,sizeof(t_bank.SERV_TIME)-1);
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
		tf.ReadString(bank_unit,"BANK_ACCOUNT_NO","2011",t_bank.BankUnit[i].szBankAccountNO,sizeof(t_bank.BankUnit[i].szBankAccountNO)-1);	// ����Ƕ������, �˴���Ҫ��дһ��ͨ�������˻�
		tf.ReadString(bank_unit,"BANK_CARD_RANGE","",szBuf,sizeof(szBuf)-1);
		tf.ReadString(bank_unit,"COMPARE_TIME","06",t_bank.BankUnit[i].compare_time, sizeof(t_bank.BankUnit[i].compare_time) - 1);
		tf.ReadString(bank_unit,"SENDCOMPREQ_TIME","05",t_bank.BankUnit[i].sendcompreq_time,sizeof(t_bank.BankUnit[i].sendcompreq_time) - 1);
		tf.ReadString(bank_unit,"COMP_FILE_PATH","/home",t_bank.BankUnit[i].comp_file_path,sizeof(t_bank.BankUnit[i].comp_file_path) - 1);
		pch = strtok (szBuf,",");
		while (pch != NULL)
		{
			des2src(t_bank.BankUnit[i].szBankCardRange[j], pch);
			pch = strtok (NULL, ",");
			j++;
			if(j>=MAX_RANGE) 
				break;
		}
	}
	memcpy(p_bankini,&t_bank,sizeof(t_bank));
	tf.Close();
	return 0;   
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
	FILE *fp = NULL;
	int	_pid = 0;
	int 	ret=0;
	key_t 	key;
	int intping = 60;	// ping���м��
	int intflush = 10;	// �������
	int inttrans = 60;	//�������
	int intcomp = 10;	//����ʱ����
	char strTemp[256]="";
	struct 	shmid_ds buf;
	int terminal_id=0;
	int send_flag = 0;			// ���������ʶ, �е����в���Ҫ���������ʶ, �е���Ҫ(�ź���Ҫ, ũ�в���Ҫ)
	int send_count = 0;			// ���Ͷ�������Ĵ���, ����һ������Ͳ��������ٷ�������, ���Ƿ���ʧ��
	
	//BANK_TRANS_REQUEST	bank_trans;
	INNER_TRANS_REQUEST  inner_trans;
	BANK_COMPARE_FILE compare_file, compare_src_file;				// �����ļ�����
	BANK_COMPARE_RECODE compare_record;			// �����ļ���¼����
	BANK_FILE_ADJUST file_adjust;				// �����ļ�����Ч��������ֶ�
	memset(&compare_file, 0, sizeof(compare_file));
	memset(&compare_src_file, 0, sizeof(compare_src_file));
	memset(&compare_record, 0, sizeof(compare_record));
	memset(&file_adjust, 0, sizeof(file_adjust));
	
   	int opt;
   	extern int optind;
   	extern char *optarg;

	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));



	memset(&inner_trans,0,sizeof inner_trans);
	
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
			ReadIni_bank(&g_Bank);
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
		ReadIni_bank(&g_Bank);

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

	//���������ڴ�
	key=ftok("bankguard",9);

	//key=ftok(".",0);
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

	if(!KS_YKT_Clt::Initialize(g_Bank.DRTP_IP, g_Bank.DRTP_PORT, g_Bank.BCC_BASEFUNCNO))
	{
		printf("----------��ʼ��ͨѶƽ̨ʧ��----------\n");
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	-1;
	}
	KS_YKT_Clt ykt_clt;
	char msg[256]="";
	ykt_clt.ResetHandler();

	//shm[2]=1;

	//�����˳�
	v(semid);

	time_t	now = 0;
	time_t 	lastping = 0;		// �ϴ�ping����ʱ��
	time_t	lastflush = 0;		// �ϴδ������ʱ��
	time_t	lasttrans=0;		//�ϴ���ͼ���񻮲���ʱ��
	time_t	lastcomp=0;		//�ϴ���ͼ���ж��ʵ�ʱ��

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
			//�ж�ϵͳʱ���Ƿ񵽴���5���
			/*
			if(0==memcmp("0530",getsystime(NULL),4))
			{
				shm[1]= 0;				// ���ù����ڴ棬Ҫ�����µ�¼
			}
			
			if(shm[1] != 1)
			{
				p(semid);	//����ϵͳ��½���޸ĵ�½��־
				writelog(LOG_INFO,"��ʼ��½����");
				printf("���ڵ�½����...\n");
				shm[0]=1;
				ret=Bank_SignIn(&inner_trans);
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
					memcpy(shm+10,inner_trans.BankCardPwd,sizeof(inner_trans.BankCardPwd));
					shm[2]=1;

					char buffer[100]="";
					int k=0;
					for(int i=0;i<16;i++)
					{
						k=inner_trans.BankCardPwd[i];
						sprintf(&buffer[2*i],"%02X",k);
					}
					writelog(LOG_INFO,"BankCardPwd=[%s]",buffer);
				}
				v(semid);
				continue;
			}
			*/
		}
		sleep(30);
	}


	p(semid);
	shm[3]=0;	// ��ͨ�ű�־
	v(semid);

	shmdt(shm);
	shmctl(shmid,IPC_RMID,&buf);
	d_sem(semid);
	
	writelog(LOG_INFO, "���������˳�");
	printf("���������˳�\n");
	return(0);
}
