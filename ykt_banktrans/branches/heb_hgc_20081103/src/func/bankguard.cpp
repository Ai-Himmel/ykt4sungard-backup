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

 ----------------
 Updated by lq at 2005-03-10
 将签到、冲正、通信监测集中到本程序(bankguard)中处理，通过共享内存与银行转账bu交互
 为保持数据一致性，读写共享内存区通过信号量进行同步
 shm[3]:通信状况标志：如果为1，表示通信异常，bu应该直接拒绝请求
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
		tf.ReadString(bank_unit,"BANK_ACCOUNT_NO","2011",t_bank.BankUnit[i].szBankAccountNO,sizeof(t_bank.BankUnit[i].szBankAccountNO)-1);	// 如果是多家银行, 此处需要填写一卡通的银行账户
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
	int intping = 60;	// ping银行间隔
	int intflush = 10;	// 冲正间隔
	int inttrans = 60;	//划拨间隔
	int intcomp = 10;	//对帐时间间隔
	char strTemp[256]="";
	struct 	shmid_ds buf;
	int terminal_id=0;
	int send_flag = 0;			// 发送请求标识, 有的银行不需要发送请求标识, 有的需要(信合需要, 农行不需要)
	int send_count = 0;			// 发送对账请求的次数, 超过一次请求就不允许了再发请求了, 除非发送失败
	
	//BANK_TRANS_REQUEST	bank_trans;
	INNER_TRANS_REQUEST  inner_trans;
	BANK_COMPARE_FILE compare_file, compare_src_file;				// 对账文件描述
	BANK_COMPARE_RECODE compare_record;			// 对账文件记录描述
	BANK_FILE_ADJUST file_adjust;				// 对账文件所需效验的数据字段
	memset(&compare_file, 0, sizeof(compare_file));
	memset(&compare_src_file, 0, sizeof(compare_src_file));
	memset(&compare_record, 0, sizeof(compare_record));
	memset(&file_adjust, 0, sizeof(file_adjust));
	
   	int opt;
   	extern int optind;
   	extern char *optarg;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// 设置发送包

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

 	// 屏蔽信号
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
	// 初始化数据库连接：
	SQLInitialize();
	ret = SQLConnectToServer();
	if (ret!=0)
	{
		writelog(LOG_ERR,"连接数据库失败[%d]", ret);
		//printf("连接数据库失败database %s, username %s, password %s, [%d]", g_BUnit.m_SqlDB.szDatabase,g_BUnit.m_SqlDB.szLogin,g_BUnit.m_SqlDB.szPassword, ret);
		printf("连接数据库失败\n");
		return 	E_DB_DBCONN;
	}
*/
	//创建共享内存
	key=ftok(".",0);
	shmid=shmget(key,SEGSIZE,IPC_CREAT|0666);
	if(-1==shmid)
	{
		writelog(LOG_ERR,"创建共享内存失败[%d]",shmid);
		printf("创建共享内存失败\n");
		return 	E_CREATE_SHARE_MEMORY;
	}
	shm=(char*)shmat(shmid,0,0);
	if((int)shm==-1)
	{
		writelog(LOG_ERR,"连接共享内存失败[%d]",shm);
		printf("连接共享内存失败\n");
		return 	E_JOIN_SHARE_MEMORY;
	}


	//枷锁进行清除设备签到表和前置机签到
	semid=sem(key);
	if((int)semid==-1)
	{
		writelog(LOG_ERR,"创建信号量失败[%d]",semid);
		printf("创建信号量失败\n");
		return 	E_JOIN_SHARE_MEMORY;
	}

	p(semid);

	//初始化共享内存
	memset(shm, 0, SEGSIZE);
	shm[0]=0;
	shm[1]=0;
	writelog(LOG_INFO,"已重置共享内存");
	//清理所有的圈存设备的签到状态为签出状态
	//保证所有的设备所的到的银行pin/mac密钥正确
	//ret=DB_t_pif_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	//if(ret)

	if(!KS_YKT_Clt::Initialize(g_Bank.DRTP_IP, g_Bank.DRTP_PORT, g_Bank.BCC_BASEFUNCNO))
	{
		printf("----------初始化通讯平台失败----------\n");
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
		printf("----------后台发送请求失败----------\n");
		ykt_clt.GetReturnMsg(msg);
		writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	-1;
	}
	if(ykt_clt.GetReturnCode())
	{
		printf("---------后台功能执行失败----------\n");
		ykt_clt.GetReturnMsg(msg);
		writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
		shmdt(shm);
		shmctl(shmid,IPC_RMID,&buf);
		d_sem(semid);
		return 	-1;
	}
	shm[2]=1;
	writelog(LOG_ERR,"已清理设备表");

	//枷锁退出
	v(semid);

	//writelog(LOG_INFO,"银行接口初始化完成，bank_bu可以启动了");
	//printf("银行接口初始化完成\n");

	time_t	now = 0;
	time_t 	lastping = 0;		// 上次ping银行时间
	time_t	lastflush = 0;		// 上次处理冲正时间
	time_t	lasttrans=0;		//上次试图帐务划拨的时间
	time_t	lastcomp=0;		//上次试图银行对帐的时间
//	T_t_tif_tradeserial  tradeserial; //卡操作流水表，用做冲正用

	// 进入运行
	while(true)
	{
		if((app_flag&APP_FLAG_TERM) != 0)
		{
			writelog(LOG_INFO,"收到终止信号，退出");
			break;
		}

		// 监测与银行通信情况
		now = time(0);
		if((now - lastping) > intping)
		{
			lastping = now;
			if(shm[1] != 1)
			{
				p(semid);	//进行系统登陆，修改登陆标志
				writelog(LOG_INFO,"开始登陆银行");
				printf("正在登陆银行...\n");
				shm[0]=1;
				ret=Bank_SignIn(&inner_trans);
				if(ret!=0)
				{
					writelog(LOG_ERR,"登陆银行失败[%d]",ret);
					printf("----------登陆银行失败----------\n");
				}
				else
				{
					writelog(LOG_INFO,"登陆银行成功");
					printf("----------登陆银行成功----------\n");
					shm[1]=1;
					shm[3]=0;
					memcpy(shm+10,inner_trans.BankCardPwd,sizeof(inner_trans.BankCardPwd));
					//向后台发起签出所有设备的请求
					ykt_clt.ResetHandler();
					if(!ykt_clt.SendRequest(240006, TIMEOUT*1000))
					{
						printf("----------后台发送请求失败----------\n");
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						shmdt(shm);
						shmctl(shmid,IPC_RMID,&buf);
						d_sem(semid);
						return 	-1;
					}
					if(ykt_clt.GetReturnCode())
					{
						printf("---------后台功能执行失败----------\n");
						ykt_clt.GetReturnMsg(msg);
						writelog(LOG_ERR,"retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						shmdt(shm);
						shmctl(shmid,IPC_RMID,&buf);
						d_sem(semid);
						return 	-1;
					}

					shm[2]=1;
					writelog(LOG_INFO,"已清理设备表");

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
				writelog(LOG_ERR,"与银行的通信可能中断[%d]",ret);
				p(semid);
				shm[1]=0;	// 置登陆标志，// 是否有必要重新登陆？？
				shm[3]=1;	// 置通信标志
				v(semid);
			}
			else if(shm[3] == 1)
			{
				writelog(LOG_ERR,"与银行的通信恢复[%d]",ret);
				p(semid);
				shm[3]=0;	// 置通信标志
				v(semid);
			}

		}

		//补发冲正
		now = time(0);
		if((now - lastflush) > intflush)
		{
			writelog(LOG_ERR,"Start flush!");
			lastflush = now;
			//获取下一个冲正记录：状态为需冲正且上次冲正时间最早
			//RESERVE_1不为空的视为冲正成功
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
					writelog(LOG_ERR,"当前流水号=[%d], 冲正流水号=[%d], 日期=[%s], 时间=[%s], 交易卡号=[%d], 银行卡号=[%s], 终端号=[%d]", inner_trans.SendNo, inner_trans.RecvNo, inner_trans.TradeDate, inner_trans.TradeTime, atoi(inner_trans.CardNo), inner_trans.BankCardNo, terminal_id);
					ret = Bank_Undo(&inner_trans); 
					if(ret == 0)
					{
						writelog(LOG_ERR,"发送银行冲正记录成功[%ld]", inner_trans.SendNo);
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", inner_trans.SendNo);
						ykt_clt.SetIntFieldByName("lvol1", 1);

						if(!ykt_clt.SendRequest(240005, g_Bank.TIMEOUT*1000))
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"调用后台确认冲正功能失败retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
						if(ykt_clt.GetReturnCode())
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"调用后台确认冲正功能失败retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}

					}
					else
					{
						writelog(LOG_ERR,"发送银行冲正记录失败[%ld]", inner_trans.SendNo);
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", inner_trans.SendNo);
						ykt_clt.SetIntFieldByName("lvol1", 0);

						if(!ykt_clt.SendRequest(240005, g_Bank.TIMEOUT*1000))
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"调用后台确认冲正功能失败retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
						if(ykt_clt.GetReturnCode())
						{
							ykt_clt.GetReturnMsg(msg);
							writelog(LOG_ERR,"调用后台确认冲正功能失败retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
						}
					}

				}
				else
				{
					writelog(LOG_ERR,"Return package error,retcode=[%d],msg=[%s]",ykt_clt.GetReturnCode(),msg);
				}
			}
		}

		// 做银行对帐, 如果是一台圈存机使用多家银行卡, 对账的时候按照不同时间进行对账
		// a. 往银行端发送对账请求
		// b. 获取文件路径的环境变量和对账文件数据
		// c. 发送对账文件数据给一卡通后台
		char buffer[256]="";
		int ho_OpCount=0;	
		double ho_Fee_Change=0;
		int ret=0;
		int file_flag = 0;			// 打开文件标识, 如果当前银行对账文件已经打开标识为1, 未有打开标识为0
		now = time(0);
		if((now - lastcomp) > intcomp)
		{
			lastcomp=now;
			// 寻找当前对账银行
			for(int ii = 0; ii < g_Bank.BankCount; ii++)
			{
//				writelog(LOG_ERR, "compare bank id=[%d], bank flag=[%d], compare_time=[%s], send_request_time=[%s], bank_count=[%d], bank_home=[%s], sendcompreq_flag=[%d], time=[%s], compare_count=[%d]", g_Bank.BankUnit[ii].iBankID, g_Bank.BankUnit[ii].compare_flag, g_Bank.BankUnit[ii].compare_time, g_Bank.BankUnit[ii].sendcompreq_time, g_Bank.BankCount, g_Bank.BankUnit[ii].comp_file_path, g_Bank.BankUnit[ii].sendcompreq_flag, getsystime(NULL), g_Bank.BankUnit[ii].compare_count);
				writelog(LOG_ERR, "compare bank id=[%d]", g_Bank.BankUnit[ii].iBankID);
				// 选择信合银行进行对账
				if (BANK_YNXH == g_Bank.BankUnit[ii].iBankID)
				{	
					if (g_Bank.BankUnit[ii].sendcompreq_flag) { goto L_COMP; }		// 已经发送过请求就需要对账
				}
				// 选择哈尔滨中行进行对账
				else if (BANK_HRBZH == g_Bank.BankUnit[ii].iBankID)
				{
					if (g_Bank.BankUnit[ii].sendcompreq_flag) { goto L_COMP; }		// 已经发送过请求就需要对账
				}
				// 选择其他银行进行对账
				else
				{
					writelog(LOG_ERR, "no other bank compare");
					continue;
				}
				
				// 超过对账时间以后需要修改对账标识为0, 保证第二天继续对账, 信合5点半进行对账
				if (memcmp(g_Bank.BankUnit[ii].compare_time,getsystime(NULL),2) < 0)
				{
					g_Bank.BankUnit[ii].compare_flag = 0;
					g_Bank.BankUnit[ii].sendcompreq_flag = 0;
					writelog(LOG_ERR,"modify compare file flag bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}
				// 没有超过对账时间, 但是已经对完账了就要跳出, 否则进行对账
				else 
				{
					// 如果已经参与过对账的银行则不进行对账
					if (1 == g_Bank.BankUnit[ii].compare_flag)
					{
						writelog(LOG_ERR,"already compare file bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
						goto L_RETU;
					}
				}

				// 判断系统时间是否到达早5点, 到达则发送请求, 云南信合需要
				// 其他银行模仿云南信合进行对账处理
				if ((0 == memcmp(g_Bank.BankUnit[ii].sendcompreq_time,getsystime(NULL),2)))
				{
					ret = Bank_GetRecvPacket(&inner_trans, &g_Bank.BankUnit[ii], &file_adjust);
					if (ret) 
					{
						writelog(LOG_ERR,"Send Request Compare File Failed");
						goto L_RETU;
					}
					g_Bank.BankUnit[ii].sendcompreq_flag = 1;		// 已经发送过请求
				}
				else
				{
					writelog(LOG_ERR,"request time don't arrive, bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}

		L_COMP:				
				// 判断系统时间是否到达早上5点30, 到达则发起对账, 此处计算比较到十分位, 保证在此时间内出现一次对账请求
				if (0 == memcmp(g_Bank.BankUnit[ii].compare_time,getsystime(NULL),4))
				{
					// 每个银行的对账文件的内容不一样, 使用Bank_GetCompareFile第四个参数进行描述
					// 1. 效验对账文件的通用处理
					ret = Bank_AdjustCompareFile(&inner_trans, &g_Bank.BankUnit[ii], NULL, &file_adjust, NULL);
					if (ret)
					{
						writelog(LOG_ERR, "Get Compare File Error", ret, msg);
						goto L_RETU;
					}
					
					do 
					{
						writelog(LOG_INFO,"comp_file_path=[%s]", file_adjust.file_path_name);
						// 2. 打开对账文件, 并进行对账数据处理, 因为对账文件内容不一样, 此处用银行标识进行区分 
						if (!file_flag)
						{
							if ((fp = fopen(file_adjust.file_path_name, "rb")) == NULL)
							{
								writelog(LOG_ERR,"Open indirect file error,file=[%s]", g_Bank.BankUnit[ii].comp_file_path);
								goto L_RETU;
							}
						}
						
						file_flag = 1;			// 只有文件打开了才能够取其中的数据
						// 3. 获取对账文件数据, 一条一条取数据文件
						if (file_flag)
						{
							if (!feof(fp))
							{
								if (NULL == fgets((char *)(&compare_record), sizeof(BANK_COMPARE_RECODE), fp))	// 获取对账文件的数据记录
								{
									writelog(LOG_ERR,"fgets error local_sn=[%s]", compare_record.LocalSn);
									break;	
								}
							}
						}
						// 往后台240007功能发送对账交易, 将银行对账文件数据入库
						ykt_clt.ResetHandler();
						ykt_clt.SetIntFieldByName("lvol0", 0);			// 发送对账记录标识, 此标识描述获取对账文件记录中的数据是否完全入库
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
						ykt_clt.SetStringFieldByName("scard1", file_adjust.append_trade_info + 3);		// 文件名
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
					}while(memcmp(&compare_record, &compare_src_file, 10) != 0);		// 取不到记录的时候就退出

					// 4.读取对帐文件结束, 关闭对账文件
					if (file_flag)
					{
						if (fclose(fp))
						{
							writelog(LOG_ERR,"Close file error,file=[%s]", g_Bank.BankUnit[ii].comp_file_path);
							goto L_RETU;
						}
						file_flag = 0;
					}
					
					// 5.真正发起对账交易
					ykt_clt.ResetHandler();
					ykt_clt.SetIntFieldByName("lvol0", 1);										// 发送对账记录标识, 此标识描述获取对账文件记录中的数据是否完全入库
					ykt_clt.SetStringFieldByName("scard1", file_adjust.append_trade_info + 3);  // 这里要把文件名的时间传到主应用服务上
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

					// 对账完成, 置对账标识标识已经对账, 置请求标识, 标识不用再次发送对账请求
					g_Bank.BankUnit[ii].compare_flag = 1;
					g_Bank.BankUnit[ii].sendcompreq_flag = 0;
					writelog(LOG_ERR,"Do_Compare_file complete Bankid=[%d], CompareFlag=[%d]", g_Bank.BankUnit[ii].iBankID, g_Bank.BankUnit[ii].compare_flag);
				}
				else 
				{
					writelog(LOG_ERR,"compare time don't arrive, bankid=[%d]", g_Bank.BankUnit[ii].iBankID);
					goto L_RETU;
				}
				
				// 6.移走当前对账文件
//				rename("/home/bank/ynxh_ftp/BANK0420080427_bak.txt", "/home/bank/BANK0420080427_bak.txt");
			}
		}
		L_RETU:
		// 休眠
		sleep(5);//13938470950	
	}

	p(semid);
	shm[3]=0;	// 置通信标志
	v(semid);

	shmdt(shm);
	shmctl(shmid,IPC_RMID,&buf);
	d_sem(semid);
	
	writelog(LOG_INFO, "程序正常退出");
	printf("程序正常退出\n");
	return(0);
}
