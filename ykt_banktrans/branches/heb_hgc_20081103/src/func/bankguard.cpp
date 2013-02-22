#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include "shem.h"
#include "cpack.h"
//#include "fdsqc.h"
//#include "dbfunc.h"
#include "pubfunc.h"
//#include "pubdb.h"
#include "bupub.h"
#include "errdef.h"
#include "logfile.h"
#include "profile.h"
#include "bank.h"
#include "transinfo.h"
#include "yktclt.h"
//#include "bankdb.h"


extern int debug;
//ST_BUNIT g_BUnit;
/*
int DRTP_BRANCH=6000;
int BCC_BASEFUNCNO=9000;
int TIMEOUT=4;
char COMPACC_TIME[2+1]="06";
*/
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
	t_bank.default_bank_id=tf.ReadInt("COMMON","DEFAULT_BANKID",0);
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
			writelog(LOG_INFO,"BANKGUARD--BANKID=[%d], BANKCARDRAGNT=[%s], i=[%d], j=[%d]", t_bank.BankUnit[i].iBankID, t_bank.BankUnit[i].szBankCardRange[j], i, j);
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
/*
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
*/
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
	//�������е�Ȧ���豸��ǩ��״̬Ϊǩ��״̬
	//��֤���е��豸���ĵ�������pin/mac��Կ��ȷ
	//ret=DB_t_pif_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	//if(ret)

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
	if(!ykt_clt.SendRequest(240006, g_Bank.TIMEOUT*1000))
	{
		printf("----------��̨��������ʧ��----------\n");
		ykt_clt.GetReturnMsg(msg);
		writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	-1;
	}
	if(ykt_clt.GetReturnCode())
	{
		printf("---------��̨����ִ��ʧ��----------\n");
		ykt_clt.GetReturnMsg(msg);
		writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	-1;
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
//	T_t_tif_tradeserial  tradeserial; //��������ˮ������������

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
					//���̨����ǩ�������豸������
					ykt_clt.ResetHandler();
					if(!ykt_clt.SendRequest(240006, TIMEOUT*1000))
					{
						printf("----------��̨��������ʧ��----------\n");
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						shmdt(shm);
						shmctl(shmid,IPC_RMID,&buf);
						d_sem(semid);
						return 	-1;
					}
					if(ykt_clt.GetReturnCode())
					{
						printf("---------��̨����ִ��ʧ��----------\n");
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						shmdt(shm);
						shmctl(shmid,IPC_RMID,&buf);
						d_sem(semid);
						return 	-1;
					}

					shm[2]=1;
					writelog(LOG_INFO,"�������豸��");

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

			ret=Bank_CheckLine();
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
			writelog(LOG_ERR,"Start flush!");
			lastflush = now;
			//��ȡ��һ��������¼��״̬Ϊ��������ϴγ���ʱ������
			//RESERVE_1��Ϊ�յ���Ϊ�����ɹ�
			ykt_clt.ResetHandler();
			if(!ykt_clt.SendRequest(240004, g_Bank.TIMEOUT*1000))
			{
				ykt_clt.GetReturnMsg(msg);
				writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
			}
			else if(ykt_clt.GetReturnCode())
			{
				ykt_clt.GetReturnMsg(msg);
				writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
			}
			else
			{
				if(ykt_clt.HasMoreRecord())
				{
					ykt_clt.GetNextPackage();
					GET_PACK_STR(ykt_clt,"sdate0",strTemp);
					memcpy(inner_trans.TradeDate,strTemp,sizeof inner_trans.TradeDate);
					GET_PACK_STR(ykt_clt,"stime0",strTemp);
					memcpy(inner_trans.TradeTime,strTemp,sizeof inner_trans.TradeTime);
					GET_PACK_STR(ykt_clt,"sorder0",strTemp);
					memcpy(inner_trans.TransMoney,strTemp,sizeof inner_trans.TransMoney);
					GET_PACK_STR(ykt_clt,"sserial0",strTemp);
					memcpy(inner_trans.CardNo,strTemp,sizeof inner_trans.CardNo);
					GET_PACK_STR(ykt_clt,"scust_auth",strTemp);
					memcpy(inner_trans.BankCardNo,strTemp,sizeof inner_trans.BankCardNo);

					ykt_clt.GetIntFieldByName("lvol0",&inner_trans.RecvNo);
					ykt_clt.GetIntFieldByName("lvol1",&inner_trans.SendNo);
					ykt_clt.GetIntFieldByName("lvol2",&terminal_id);
					sprintf(inner_trans.TerminalId,"%d",terminal_id);
					writelog(LOG_ERR,"��ǰ��ˮ��=[%d], ������ˮ��=[%d], ����=[%s], ʱ��=[%s], ���׿���=[%d], ���п���=[%s], �ն˺�=[%d]", inner_trans.SendNo, inner_trans.RecvNo, inner_trans.TradeDate, inner_trans.TradeTime, atoi(inner_trans.CardNo), inner_trans.BankCardNo, terminal_id);
					ret = Bank_Undo(&inner_trans); 
					if(ret == 0)
					{
						writelog(LOG_ERR,"�������г�����¼�ɹ�[%ld]", inner_trans.SendNo);
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", inner_trans.SendNo);
						ykt_clt.SetIntFieldByName("lvol1", 1);

						if(!ykt_clt.SendRequest(240005, g_Bank.TIMEOUT*1000))
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"���ú�̨ȷ�ϳ�������ʧ��retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
						if(ykt_clt.GetReturnCode())
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"���ú�̨ȷ�ϳ�������ʧ��retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}

					}
					else
					{
						writelog(LOG_ERR,"�������г�����¼ʧ��[%ld]", inner_trans.SendNo);
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", inner_trans.SendNo);
						ykt_clt.SetIntFieldByName("lvol1", 0);

						if(!ykt_clt.SendRequest(240005, g_Bank.TIMEOUT*1000))
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"���ú�̨ȷ�ϳ�������ʧ��retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
						if(ykt_clt.GetReturnCode())
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"���ú�̨ȷ�ϳ�������ʧ��retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
					}

				}
				else
				{
					writelog(LOG_ERR,"Return package error,retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
				}
			}
		}

		// �����ж���, �����һ̨Ȧ���ʹ�ö�����п�, ���˵�ʱ���ղ�ͬʱ����ж���
		// a. �����ж˷��Ͷ�������
		// b. ��ȡ�ļ�·���Ļ��������Ͷ����ļ�����
		// c. ���Ͷ����ļ����ݸ�һ��ͨ��̨
		char buffer[256]="";
		int ho_OpCount=0;	
		double ho_Fee_Change=0;
		int ret=0;
		int file_flag = 0;			// ���ļ���ʶ, �����ǰ���ж����ļ��Ѿ��򿪱�ʶΪ1, δ�д򿪱�ʶΪ0
		now = time(0);
		if((now - lastcomp) > intcomp)
		{
			lastcomp=now;
			// Ѱ�ҵ�ǰ��������
			for(int ii = 0; ii < g_Bank.BankCount; ii++)
			{
//				writelog(LOG_ERR, "compare bank id=[%d], bank flag=[%d], compare_time=[%s], send_request_time=[%s], bank_count=[%d], bank_home=[%s], sendcompreq_flag=[%d], time=[%s], compare_count=[%d]", g_Bank.BankUnit[ii].iBankID, g_Bank.BankUnit[ii].compare_flag, g_Bank.BankUnit[ii].compare_time, g_Bank.BankUnit[ii].sendcompreq_time, g_Bank.BankCount, g_Bank.BankUnit[ii].comp_file_path, g_Bank.BankUnit[ii].sendcompreq_flag, getsystime(NULL), g_Bank.BankUnit[ii].compare_count);
				writelog(LOG_ERR, "compare bank id=[%d]", g_Bank.BankUnit[ii].iBankID);
				// ѡ���ź����н��ж���
				if (BANK_YNXH == g_Bank.BankUnit[ii].iBankID)
				{	
					if (g_Bank.BankUnit[ii].sendcompreq_flag) { goto L_COMP; }		// �Ѿ����͹��������Ҫ����
				}
				// ѡ����������н��ж���
				else if (BANK_HRBZH == g_Bank.BankUnit[ii].iBankID)
				{
					if (g_Bank.BankUnit[ii].sendcompreq_flag) { goto L_COMP; }		// �Ѿ����͹��������Ҫ����
				}
				// ѡ���������н��ж���
				else
				{
					writelog(LOG_ERR, "no other bank compare");
					continue;
				}
				
				// ��������ʱ���Ժ���Ҫ�޸Ķ��˱�ʶΪ0, ��֤�ڶ����������, �ź�5�����ж���
				if (memcmp(g_Bank.BankUnit[ii].compare_time,getsystime(NULL),2) < 0)
				{
					g_Bank.BankUnit[ii].compare_flag = 0;
					g_Bank.BankUnit[ii].sendcompreq_flag = 0;
					writelog(LOG_ERR,"modify compare file flag bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}
				// û�г�������ʱ��, �����Ѿ��������˾�Ҫ����, ������ж���
				else 
				{
					// ����Ѿ���������˵������򲻽��ж���
					if (1 == g_Bank.BankUnit[ii].compare_flag)
					{
						writelog(LOG_ERR,"already compare file bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
						goto L_RETU;
					}
				}

				// �ж�ϵͳʱ���Ƿ񵽴���5��, ������������, �����ź���Ҫ
				// ��������ģ�������źϽ��ж��˴���
				if ((0 == memcmp(g_Bank.BankUnit[ii].sendcompreq_time,getsystime(NULL),2)))
				{
					ret = Bank_GetRecvPacket(&inner_trans, &g_Bank.BankUnit[ii], &file_adjust);
					if (ret) 
					{
						writelog(LOG_ERR,"Send Request Compare File Failed");
						goto L_RETU;
					}
					g_Bank.BankUnit[ii].sendcompreq_flag = 1;		// �Ѿ����͹�����
				}
				else
				{
					writelog(LOG_ERR,"request time don't arrive, bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}

		L_COMP:				
				// �ж�ϵͳʱ���Ƿ񵽴�����5��30, �����������, �˴�����Ƚϵ�ʮ��λ, ��֤�ڴ�ʱ���ڳ���һ�ζ�������
				if (0 == memcmp(g_Bank.BankUnit[ii].compare_time,getsystime(NULL),4))
				{
					// ÿ�����еĶ����ļ������ݲ�һ��, ʹ��Bank_GetCompareFile���ĸ�������������
					// 1. Ч������ļ���ͨ�ô���
					ret = Bank_AdjustCompareFile(&inner_trans, &g_Bank.BankUnit[ii], NULL, &file_adjust, NULL);
					if (ret)
					{
						writelog(LOG_ERR, "Get Compare File Error", ret, msg);
						goto L_RETU;
					}
					
					do 
					{
						writelog(LOG_INFO,"comp_file_path=[%s]", file_adjust.file_path_name);
						// 2. �򿪶����ļ�, �����ж������ݴ���, ��Ϊ�����ļ����ݲ�һ��, �˴������б�ʶ�������� 
						if (!file_flag)
						{
							if ((fp = fopen(file_adjust.file_path_name, "rb")) == NULL)
							{
								writelog(LOG_ERR,"Open indirect file error,file=[%s]", g_Bank.BankUnit[ii].comp_file_path);
								goto L_RETU;
							}
						}
						
						file_flag = 1;			// ֻ���ļ����˲��ܹ�ȡ���е�����
						// 3. ��ȡ�����ļ�����, һ��һ��ȡ�����ļ�
						if (file_flag)
						{
							if (!feof(fp))
							{
								if (NULL == fgets((char *)(&compare_record), sizeof(BANK_COMPARE_RECODE), fp))	// ��ȡ�����ļ������ݼ�¼
								{
									writelog(LOG_ERR,"fgets error local_sn=[%s]", compare_record.LocalSn);
									break;	
								}
							}
						}
						// ����̨240007���ܷ��Ͷ��˽���, �����ж����ļ��������
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", 0);			// ���Ͷ��˼�¼��ʶ, �˱�ʶ������ȡ�����ļ���¼�е������Ƿ���ȫ���
						memcpy(buffer, compare_record.BankCard, sizeof(compare_record.BankCard));
						ykt_clt.SetStringFieldByName("scust_auth", buffer);
						memcpy(buffer, compare_record.BankSn, sizeof(compare_record.BankSn));
						ykt_clt.SetStringFieldByName("scust_auth2", buffer);
						memcpy(buffer, compare_record.GDCAccount, sizeof(compare_record.GDCAccount));
						ykt_clt.SetStringFieldByName("sorder0", buffer);
						memcpy(buffer, compare_record.LocalSn, sizeof(compare_record.LocalSn));
						ykt_clt.SetStringFieldByName("semp_no", buffer);
						memcpy(buffer, compare_record.TradeCode, sizeof(compare_record.TradeCode));
						ykt_clt.SetStringFieldByName("scust_type", buffer);
						memcpy(buffer, compare_record.TransMomoy, sizeof(compare_record.TransMomoy));
						ykt_clt.SetStringFieldByName("sorder1", buffer);
						ykt_clt.SetStringFieldByName("scard1", file_adjust.append_trade_info + 3);		// �ļ���
						writelog(LOG_ERR, "compare_flag=[%d], bank_card=[%20.20s], bank_sn=[%20.20s], card_id=[%10.10s], local_sn=[%8.8s], trade_code=[%2.2s], trans_money=[%9.9s]", g_Bank.BankUnit[ii].compare_flag, compare_record.BankCard, compare_record.BankSn, compare_record.GDCAccount, compare_record.LocalSn, compare_record.TradeCode, compare_record.TransMomoy);
						
						if (!ykt_clt.SendRequest(240007, g_Bank.TIMEOUT*1000))
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"retcode=[%d],msg=[%s],Do_Compare_file error",ykt_clt.GetReturnCode(),msg);
						}

						if (ykt_clt.GetReturnCode())
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
					}while(memcmp(&compare_record, &compare_src_file, 10) != 0);		// ȡ������¼��ʱ����˳�

					// 4.��ȡ�����ļ�����, �رն����ļ�
					if (file_flag)
					{
						if (fclose(fp))
						{
							writelog(LOG_ERR,"Close file error,file=[%s]", g_Bank.BankUnit[ii].comp_file_path);
							goto L_RETU;
						}
						file_flag = 0;
					}
					
					// 5.����������˽���
					ykt_clt.ResetHandler();
					ykt_clt.SetIntFieldByName("lvol0", 1);										// ���Ͷ��˼�¼��ʶ, �˱�ʶ������ȡ�����ļ���¼�е������Ƿ���ȫ���
					ykt_clt.SetStringFieldByName("scard1", file_adjust.append_trade_info + 3);  // ����Ҫ���ļ�����ʱ�䴫����Ӧ�÷�����
					if (!ykt_clt.SendRequest(240007, g_Bank.TIMEOUT*1000))
					{
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s],Do_Compare_file error",ykt_clt.GetReturnCode(),msg);
						goto L_RETU;
					}

					if (ykt_clt.GetReturnCode())
					{
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						goto L_RETU;
					}

					// �������, �ö��˱�ʶ��ʶ�Ѿ�����, �������ʶ, ��ʶ�����ٴη��Ͷ�������
					g_Bank.BankUnit[ii].compare_flag = 1;
					g_Bank.BankUnit[ii].sendcompreq_flag = 0;
					writelog(LOG_ERR,"Do_Compare_file complete Bankid=[%d], CompareFlag=[%d]", g_Bank.BankUnit[ii].iBankID, g_Bank.BankUnit[ii].compare_flag);
				}
				else 
				{
					writelog(LOG_ERR,"compare time don't arrive, bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}
				
				// 6.���ߵ�ǰ�����ļ�
//				rename("/home/bank/ynxh_ftp/BANK0420080427_bak.txt", "/home/bank/BANK0420080427_bak.txt");
			}
		}
		L_RETU:
		// ����
		sleep(5);//13938470950	
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
