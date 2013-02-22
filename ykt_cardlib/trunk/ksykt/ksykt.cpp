#include "..\include\ksykt.h"
#include "..\include\yktclt.h"
#include "ksykt_def.h"
#include "..\include\carddll_def.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>

#define MAX_DEVICE_COUNT 30

#define DEV_FLAG_LOGIN 0x01

#define FUNC_ENROLL 849001
#define FUNC_QUERY_USER_INFO 849002
#define FUNC_LOST_CARD 847318
#define FUNC_CONSUME 847316
#define FUNC_CONSUME_CONFIRM 847317
#define FUNC_READ_CARD 847173
#define FUNC_READ_CUST_INFO 841605
#define FUNC_READ_ACCOUNT 847170
#define FUNC_READ_DICT 820502

/*
对应卡状态
*/
// 正常
#define ACC_FLAG_OK 0
// 
#define ACC_FLAG_SET 1
#define ACC_FLAG_LOGOUT 2

typedef struct{
	int device_id;	// 设备ID
	int sys_id;		// 子系统号
	unsigned short term_no;	// 终端机号
	ULONG maxjnl;		// 终端流水号
	int purse_no;		// 终端交易钱包号
	int day_trade_limit; // 日交易累计限额
	int trade_limit_per_cnt; // 单次交易限额
	int flag;				// 标志
	char oper_code[11];		// 操作员
}conn_dev_conf_t;

typedef struct {
	int device_count;
	conn_dev_conf_t devices[MAX_DEVICE_COUNT];
}sys_devices_t;

DCLR_DLLFUNC(int,encrypt_des,(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result));
DCLR_DLLFUNC(int,dencrypt_des,(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result));

// CardDll 相关函数
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(Load_WorkKey);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(ReadSerial);
DEF_DLLFUNC(SMT_ReadPacketInfo);
DEF_DLLFUNC(ReadCardNO);
DEF_DLLFUNC(SMT_PacketSetMoney);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(SMT_GetPacketInfo);
DEF_DLLFUNC(encrypt_des);
DEF_DLLFUNC(dencrypt_des);

// 设备列表
static sys_devices_t g_devices;
// 主功能号
static int g_main_func = 7000;
// 串口是否打开
static int g_com_open = 0;

static char g_workkey[33] = "";

static HINSTANCE g_carddll_module = NULL;
static HINSTANCE g_des_module = NULL;

static int do_load_carddll()
{
	if((g_carddll_module=LoadLibrary("carddll"))!=NULL)
	{
		return -1;
	}
	LOAD_DLLFUNC(g_carddll_module,ConnectMF);
	LOAD_DLLFUNC(g_carddll_module,CloseMF);
	LOAD_DLLFUNC(g_carddll_module,Load_WorkKey);
	LOAD_DLLFUNC(g_carddll_module,ReadCardInfo);
	LOAD_DLLFUNC(g_carddll_module,ReadSerial);
	LOAD_DLLFUNC(g_carddll_module,SMT_ReadPacketInfo);
	LOAD_DLLFUNC(g_carddll_module,ReadCardNO);
	LOAD_DLLFUNC(g_carddll_module,SMT_PacketSetMoney);
	LOAD_DLLFUNC(g_carddll_module,ControlBuzzer);
	LOAD_DLLFUNC(g_carddll_module,SMT_GetPacketInfo);

	if((g_des_module=LoadLibrary("desdll"))!=NULL)
	{
		return -1;
	}
	LOAD_DLLFUNC(g_des_module,encrypt_des);
	LOAD_DLLFUNC(g_des_module,dencrypt_des);
	return 0;
}

static bool do_sys_init()
{
	memset(&g_devices,0,sizeof g_devices);
	g_com_open = 0;
	memset(g_workkey,0,sizeof g_workkey);
	if(do_load_carddll())
		return false;
	return true;
}

static void do_get_date_time(char date_str[9],char time_str[7])
{
	SYSTEMTIME st;
	memset(&st,0,sizeof st);
	GetLocalTime(&st);
	sprintf(date_str,"%04u%02u%02u",st.wYear,st.wMonth,st.wDay);
	sprintf(time_str,"%02u%02u%02u",st.wHour,st.wMinute,st.wSecond);
}

static double d4u5(double in_data,int precision=2)
{
	/*
	int k;
	double tmp;
	tmp = in_data * pow(10,precision);
	tmp += 0.5;
	k = (int)tmp;
	return (k/pow(10,precision));
	*/
	char format_str[20] = "";
	char value_str[40] = "";
	sprintf(format_str,"%%20.%df",precision);
	sprintf(value_str,format_str,in_data);
	return atof(value_str);
}

static bool g_sys_init = do_sys_init();

#define TEST_SYS_INIT do { \
	if(!g_sys_init) return ERR_TA_NOT_INIT; }while(0)

#define TEST_COM_OPEN do { \
	if(!g_com_open) return ERR_TA_CARDREADER; }while(0)

#define src2des(d,s) do { \
	strncpy((char*)(d),(const char*)(s),sizeof(d)-1);}while(0)

#define GET_PACK_STR(c,p,v) do {\
	c.GetStringFieldByName(p,v,sizeof(v)-1);}while(0)

static int do_find_dev_by_termno(int termno)
{
	int i;
	for(i = 0;i < g_devices.device_count;i++)
	{
		if(g_devices.devices[i].term_no == termno)
		{
			return i;
		}
	}
	return -1;
}

static int do_find_dev_by_devid(int devid)
{
	int i;
	for(i = 0;i < g_devices.device_count;i++)
	{
		if(g_devices.devices[i].device_id == devid)
		{
			return i;
		}
	}
	return -1;	
}


static int do_convert_card_phyno(const unsigned char *phyno,unsigned int *dec_no)
{
	unsigned char reverse_phyno[9];
	int i;
	unsigned int no;
	for (i = 0;i < 2;i++)
	{
		memcpy(reverse_phyno+(3-i)*2,phyno+i*2,2);
	}
	reverse_phyno[8] = '\0';
	no = strtoul((const char*)reverse_phyno,NULL,16);
	if(no > 0)
	{
		*dec_no = no;
		return 0;
	}
	return -1;
}

static int do_convert_card_dec_phyno(unsigned int dec_no,unsigned char *phyno)
{
	char reverse_phyno[9] = "";
	sprintf(reverse_phyno,"%08X",dec_no);
	return 0;
}

static void do_card_state_to_flag(char state_id[5],char flag[16],char enableid)
{
	if(state_id[0] == '2')
		flag[1] = ACC_FLAG_LOGOUT;
	if(state_id[1] == '1')
		flag[2] = ACC_FLAG_SET;
	if(state_id[2] == '1' )
		flag[3] = ACC_FLAG_SET;
	flag[7] = ACC_FLAG_SET;
	flag[9] = (enableid == '2') ? ACC_FLAG_SET : ACC_FLAG_OK; 
}

// 检查
static bool do_check_file_exists(const char *FileName)
{
	FILE *fp;
	if((fp = fopen(FileName,"r"))==NULL)
	{
		return false;
	}
	fclose(fp);
	return true;
}

BOOL CALLAPI Is_Init_OK()
{
	return (g_sys_init) ? TRUE : FALSE;
}

BOOL CALLAPI TA_Init(char *IP , short port , unsigned short SysCode,
					 unsigned short TerminalNo, bool *ProxyOffline, ULONG *MaxJnl)
{
	int ret_code,idx;
	KS_YKT_Clt clt;
	if(!g_sys_init)
		return FALSE;

	if(!KS_YKT_Clt::Initialize(IP,port,g_main_func))
		return FALSE;
	
	idx = do_find_dev_by_termno(TerminalNo);	
	clt.SetIntFieldByName("lcert_code",SysCode);
	clt.SetIntFieldByName("lvol0",TerminalNo);
	if(!clt.SendRequest(FUNC_ENROLL,1000))
	{
		return FALSE;
	}
	ret_code = clt.GetReturnCode();
	if(!ret_code)
	{
		return FALSE;
	}
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
#if 0
		if(idx == -1)
		{
			if(g_devices.device_count >= MAX_DEVICE_COUNT)
				return FALSE;
			idx = g_devices.device_count++;
		}
#else
		idx = 0;
		g_devices.device_count = 1;
#endif
		
		clt.GetIntFieldByName("lvol0",&(g_devices.devices[idx].device_id));
		clt.GetIntFieldByName("lvol1",(int*)&(g_devices.devices[idx].maxjnl));
		GET_PACK_STR(clt,"scust_limit",g_workkey);
		clt.GetIntFieldByName("lvol2",&(g_devices.devices[idx].purse_no));
		clt.GetIntFieldByName("lvol3",&(g_devices.devices[idx].trade_limit_per_cnt));
		clt.GetIntFieldByName("lvol4",&(g_devices.devices[idx].day_trade_limit));
		g_devices.devices[idx].term_no = TerminalNo;
		g_devices.devices[idx].sys_id = SysCode;
		g_devices.devices[idx].flag = DEV_FLAG_LOGIN;
		src2des(g_devices.devices[idx].oper_code,"system");
		*MaxJnl = g_devices.devices[idx].maxjnl;
		*ProxyOffline = false;
		if(Load_WorkKey(g_workkey))
		{
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

int CALLAPI TA_CRInit(char CardReaderType,int port,long Baud_Rate)
{
	TEST_SYS_INIT;
	if(g_com_open)
	{
		return ERR_OK;
	}
	int ret;
	if(CardReaderType == 0)
	{
		ret = ConnectMF(100,Baud_Rate);
	}
	else
	{
		ret = ConnectMF(port+1,Baud_Rate);
	}
	if(!ret)
		return ERR_OK;
	return ERR_FAIL;
}

BOOL CALLAPI TA_CRClose(void)
{
	if(g_com_open)
	{
		g_com_open = 1;
		if(CloseMF())
			return FALSE;
		return TRUE;
	}
	return TRUE;
}

int CALLAPI TA_FastGetCardNo(unsigned int *CardNo)
{
	TEST_COM_OPEN;
	int ret;
	unsigned char serial_no[8];
	ret = ReadSerial(serial_no);
	if(ret)
		return ERR_TA_READCARD;

	ret = do_convert_card_phyno(serial_no,CardNo);
	if(ret)
		return ERR_TA_READCARD;
	return ERR_OK;
}

int CALLAPI TA_ReadCardSimple(AccountMsg * pAccMsg)
{
	TEST_COM_OPEN;
	int ret;
	TPublishCard card;
	memset(&card,0,sizeof card);
	
	ret = ReadCardInfo(&card);
	if(ret)
	{
		return ERR_TA_READCARD;
	}
	int cardid = atoi((char*)card.CardNo);
	if(cardid <= 0)
		return ERR_TA_READCARD;
	// TODO : 物理卡号格式
	ret = TA_FastGetCardNo(&(pAccMsg->CardNo));
	if(ret != ERR_OK)
		return ret;
	
	src2des(pAccMsg->Name,card.ucName);
	pAccMsg->Balance = card.Money;
	src2des(pAccMsg->SexNo,card.ucSexNo);
	src2des(pAccMsg->StudentCode,card.ucCardNo);
	src2des(pAccMsg->IDNo,card.ucCertificateNo);
	src2des(pAccMsg->ExpireDate,card.DeadLineDate+2);
	src2des(pAccMsg->Password,card.ucPwd);
	src2des(pAccMsg->DeptCode,card.ucDepartmentNo);
	pAccMsg->IsOpenInSys = 1;
	return ERR_OK;
}

static int do_read_card_from_db(AccountMsg *pAccMsg)
{
	char card_phyno[9] = "";
	AccountMsg acc;
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol1",pAccMsg->AccountNo);
	do_convert_card_dec_phyno(pAccMsg->CardNo,(unsigned char*)card_phyno);
	clt.SetStringFieldByName("sdate0",card_phyno);
	if(!clt.SendRequest(FUNC_QUERY_USER_INFO))
	{
		return ERR_COMM_FAIL;
	}
	if(clt.GetReturnCode())
	{
		return ERR_FAIL;
	}

	memset(&acc,0,sizeof acc);
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		double bala_amt = 0.0;
		char invalid_date[9] = "";
		char state_id[5] = "";
		char id_status[2] = "";
		int card_id;
		
		GET_PACK_STR(clt,"semail",acc.Name);
		GET_PACK_STR(clt,"smarket_code",acc.SexNo);
		GET_PACK_STR(clt,"scust_no",acc.DeptCode);
		clt.GetIntFieldByName("lvol1",(int*)&(acc.AccountNo));
		clt.GetDoubleFieldByName("damt0",&bala_amt);
		acc.Balance = (int)d4u5(bala_amt*100,0);
		GET_PACK_STR(clt,"scust_auth2",acc.StudentCode);
		GET_PACK_STR(clt,"sroom_no",acc.PID);
		GET_PACK_STR(clt,"sdate0",card_phyno);
		clt.GetIntFieldByName("lvol6",&card_id);
		if(card_id > 0)
		{
			if(strlen(card_phyno) != 8)
				return -1;
		}
		else
			return -1;
		do_convert_card_phyno((const unsigned char*)card_phyno,&(acc.CardNo));
		GET_PACK_STR(clt,"scust_no2",invalid_date);
		strcpy(acc.ExpireDate,invalid_date+2);
		GET_PACK_STR(clt,"sdate2",state_id);
		GET_PACK_STR(clt,"sstatus1",id_status);
		do_card_state_to_flag(state_id,acc.Flag,id_status[0]);
		*pAccMsg = acc;
		return 0;
	}
	return -1;
}

int CALLAPI TA_CheckWL (unsigned int AccountNo , unsigned int CardNo , bool CheckID=true)
{
	TEST_SYS_INIT;
	int ret;
	AccountMsg acc;
	char serial_no[9] = "";
	if(AccountNo <= 0)
		return ERR_TA_CARDNO;
	acc.AccountNo = AccountNo;
	acc.CardNo = CardNo;
	memset(&acc,0,sizeof acc);
	ret = do_read_card_from_db(&acc);
	if(acc.Flag[2] == 1)
		return ERR_TA_LOST_CARD;
	if(acc.Flag[3] == 1)
		return ERR_TA_FREEZE_CARD;
	return ret;
}

int CALLAPI TA_ReadCard(AccountMsg *pAccMsg,bool CheckID=true ,bool CheckSub= false)
{
	AccountMsg acc;
	int ret;
	memset(&acc,0,sizeof acc);
	ret = TA_ReadCardSimple(&acc);
	if(ret)
	{
		return ret;
	}
	ret= do_read_card_from_db(&acc);
	if(ret)
	{
		return ERR_FAIL;
	}
	memcpy(pAccMsg,&acc,sizeof acc);
	return ERR_OK;
}

int CALLAPI TA_Consume(CardConsume *pCardCons, bool IsVerfy, short TimeOut=10)
{
	TEST_COM_OPEN;
	int ret,term_idx;
	int card_id;
	int trade_serial = 0;
	double trade_amt,out_amt;
	int trade_money,out_money;
	char now_date[9] = "";
	char now_time[7] = "";
	char last_trade_date[9] = "";
	char card_serial_no[9] = "";
	//AccountMsg acc;
	MONEY_PACK_INFO purse_info;
	
	TimeOut = (TimeOut > 0 && TimeOut < 30) ? TimeOut : 10;
	TimeOut *= 1000;

	if(pCardCons->TranAmt >= 0)
	{
		return ERR_TA_TRANAMT;
	}

	term_idx = do_find_dev_by_termno(pCardCons->TerminalNo);
	if(term_idx<0)
	{
		return ERR_TRN_STATION;
	}

	if((pCardCons->TranAmt*-1) >= g_devices.devices[term_idx].trade_limit_per_cnt)
	{
		if(strlen(pCardCons->PassWord) == 0)
		{
			return ERR_TA_EXCEED_QUOTA;
		}
	}
	if(pCardCons->TranJnl < g_devices.devices[term_idx].maxjnl)
	{
		return ERR_TA_PARA;
	}
	ret = ReadCardNO(&card_id);
	if(ret)
	{
		return ERR_TA_READCARD;
	}
	ret = ReadSerial((unsigned char*)card_serial_no);
	if(ret)
	{
		return ERR_TA_READCARD;
	}
	memset(&purse_info,0,sizeof purse_info);
	ret = SMT_GetPacketInfo(g_devices.devices[term_idx].purse_no,&purse_info);
	if(ret)
	{
		return ERR_TA_READCARD;
	}
	if(purse_info.bala + pCardCons->TranAmt < 0)
	{
		return ERR_TA_TRANAMT;
	}
	// 比较日期
	do_get_date_time(now_date,now_time);
	sprintf(last_trade_date,"20%02d%02d%02d",purse_info.date/10000%100
		,purse_info.date/100%100,purse_info.date%100);
	if(strcmp(last_trade_date,now_date) == 0)
	{
		if(purse_info.daybala - pCardCons->TranAmt > g_devices.devices[term_idx].day_trade_limit)
		{
			if(strlen(pCardCons->PassWord) == 0)
			{
				return ERR_TA_EXCEED_QUOTA;
			}
		}
	}
	
	KS_YKT_Clt clt;
	// 请求交易
	clt.SetIntFieldByName("lcert_code",827111);
	// 交易卡号
	clt.SetIntFieldByName("lvol0",card_id);
	// 卡使用次数
	clt.SetIntFieldByName("lvol1",purse_info.time_cnt);
	// 钱包号
	clt.SetIntFieldByName("lvol2",g_devices.devices[term_idx].purse_no);
	// 子系统号
	clt.SetIntFieldByName("lvol3",g_devices.devices[term_idx].sys_id);
	// 设备ID
	clt.SetIntFieldByName("lvol4",g_devices.devices[term_idx].device_id);
	// 终端流水号
	clt.SetIntFieldByName("lvol5",pCardCons->TranJnl);
	// 入卡值
	clt.SetDoubleFieldByName("damt0",purse_info.bala/100.0);
	// 交易金额
	clt.SetDoubleFieldByName("damt1",(pCardCons->TranAmt * -1)/100.0);
	// 操作员
	clt.SetStringFieldByName("scust_no",g_devices.devices[term_idx].oper_code);
	// 密码
	clt.SetStringFieldByName("semp_pwd",pCardCons->PassWord);
	// 物理卡号
	clt.SetStringFieldByName("sdate1",card_serial_no);
	// 交易日期
	clt.SetStringFieldByName("sdate0",now_date);
	clt.SetStringFieldByName("stime0",now_time);
	// 摘要
	clt.SetStringFieldByName("vsmess",pCardCons->Abstract);

	if(!clt.SendRequest(FUNC_CONSUME,TimeOut))
	{
		ret = ERR_FAIL;
	}
	pCardCons->RetCode = clt.GetReturnCode();
	if(ret)
		return ret;
	if(pCardCons->RetCode)
		return ERR_FAIL;
	if(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		clt.GetIntFieldByName("lvol0",&trade_serial);
		clt.GetDoubleFieldByName("damt0",&out_amt);
		clt.GetDoubleFieldByName("damt1",&trade_amt);
		out_money = (int)d4u5(out_amt*100.0);
		trade_money = (int)d4u5(trade_amt*100.0);
		
		int curr_card_id;
		ret = ReadCardNO(&curr_card_id);
		if(ret)
			return ERR_TA_READCARD;
		int retries = 3;
		while(retries-->0)
		{
			if(curr_card_id != card_id)
				return ERR_TA_NOT_SAMECARD;
			ret = SMT_PacketSetMoney(g_devices.devices[term_idx].purse_no,out_money);
			if(!ret)
				break;
		}
		if(ret)
			return ERR_TA_WRITECARD;	
		clt.ResetHandler();
		// 请求交易
		clt.SetIntFieldByName("lcert_code",827111);
		// 交易卡号
		clt.SetIntFieldByName("lvol0",card_id);
		// 卡使用次数
		clt.SetIntFieldByName("lvol1",purse_info.time_cnt);
		// 钱包号
		clt.SetIntFieldByName("lvol2",g_devices.devices[term_idx].purse_no);
		// 子系统号
		clt.SetIntFieldByName("lvol3",g_devices.devices[term_idx].sys_id);
		// 设备ID
		clt.SetIntFieldByName("lvol4",g_devices.devices[term_idx].device_id);
		// 终端流水号
		clt.SetIntFieldByName("lvol5",pCardCons->TranJnl);
		// 入卡值
		clt.SetDoubleFieldByName("damt0",purse_info.bala/100.0);
		// 交易金额
		clt.SetDoubleFieldByName("damt1",(pCardCons->TranAmt * -1)/100.0);
		// 操作员
		clt.SetStringFieldByName("scust_no",g_devices.devices[term_idx].oper_code);
		// 密码
		clt.SetStringFieldByName("semp_pwd",pCardCons->PassWord);
		// 后台流水号
		clt.SetIntFieldByName("lvol6",trade_serial);
		if(clt.SendRequest(FUNC_CONSUME_CONFIRM))
		{
			pCardCons->TranAmt = trade_money;
			return ERR_OK;
		}
		pCardCons->RetCode = clt.GetReturnCode();
	}
	return ERR_FAIL;
	
}
// 精确查询客户信息
int CALLAPI TA_InqAcc(AccountMsg * pAccMsg, short TimeOut = 10)
{
	TEST_SYS_INIT;
	AccountMsg ret_acc,acc;
	int ret;
	char card_phyno[9] = "";
	TimeOut = (TimeOut > 0 && TimeOut <= 60) ?  TimeOut : 10;
	TimeOut *= 1000;
	KS_YKT_Clt clt;
	
	if(pAccMsg->AccountNo <= 0 && pAccMsg->CardNo <= 0)
	{
		return ERR_TA_PARA;
	}
	
	
	clt.SetIntFieldByName("lvol1",pAccMsg->AccountNo);
	do_convert_card_dec_phyno(pAccMsg->CardNo,(unsigned char*)card_phyno);
	clt.SetStringFieldByName("sdate0",card_phyno);
	clt.SetStringFieldByName("scust_auth2",pAccMsg->StudentCode);
	clt.SetStringFieldByName("scert_no",pAccMsg->IDCard);
	if(!clt.SendRequest(FUNC_QUERY_USER_INFO))
	{
		return ERR_COMM_FAIL;
	}
	if(clt.GetReturnCode())
	{
		return ERR_FAIL;
	}
	ret = ERR_FAIL;
	memset(&ret_acc,0,sizeof ret_acc);
	while(clt.HasMoreRecord())
	{
		clt.GetNextPackage();
		double bala_amt = 0.0;
		char invalid_date[9] = "";
		char state_id[5] = "";
		char id_status[2] = "";
		int card_id;
		memset(&acc,0,sizeof acc);
		GET_PACK_STR(clt,"semail",acc.Name);
		GET_PACK_STR(clt,"smarket_code",acc.SexNo);
		GET_PACK_STR(clt,"scust_no",acc.DeptCode);
		clt.GetIntFieldByName("lvol1",(int*)&(acc.AccountNo));
		clt.GetDoubleFieldByName("damt0",&bala_amt);
		acc.Balance = (int)d4u5(bala_amt*100,0);
		GET_PACK_STR(clt,"scust_auth2",acc.StudentCode);
		GET_PACK_STR(clt,"sroom_no",acc.PID);
		GET_PACK_STR(clt,"sdate0",card_phyno);
		clt.GetIntFieldByName("lvol6",&card_id);
		if(card_id > 0)
		{
			if(strlen(card_phyno) != 8)
				continue;
		}
		else
			continue;
		do_convert_card_phyno((const unsigned char*)card_phyno,&(acc.CardNo));
		GET_PACK_STR(clt,"scust_no2",invalid_date);
		strcpy(acc.ExpireDate,invalid_date+2);
		GET_PACK_STR(clt,"sdate2",state_id);
		GET_PACK_STR(clt,"sstatus1",id_status);
		do_card_state_to_flag(state_id,acc.Flag,id_status[0]);
		if(ret_acc.AccountNo == 0)
			ret_acc = acc;
		else if(ret_acc.AccountNo == acc.AccountNo)
		{
			if(state_id[1] == '0' && state_id[2] == '0'
				&& state_id[0] == '1')
			{
				ret_acc = acc;
			}
		}
		else
			break;
	}
	if(ret_acc.AccountNo > 0)
	{
		*pAccMsg = ret_acc;
		ret = ERR_OK;
	}
	return ret;
}
// 模糊查询信息 
int CALLAPI TA_HazyInqAcc(AccountMsg *pAccMsg, int *RecNum , char *FileName
						  ,short TimeOut = 10)
{
	if(FileName == NULL)
		return ERR_TA_PARA;
	TimeOut = (TimeOut > 0 && TimeOut <= 80) ? TimeOut : 30;
	TimeOut *= 1000;
	int rec_cnt = 0;
	FILE *fp;
	int ret;
	
	if(do_check_file_exists(FileName))
	{
		// 删除文件
		if(unlink(FileName) == -1)
			return ERR_DEL_FAIL;
	}
	if((fp = fopen(FileName,"wb+"))== NULL)
	{
		return ERR_REFUSE;
	}
	ret = ERR_COMM_FAIL;
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("semail",pAccMsg->Name);
	clt.SetStringFieldByName("scust_no",pAccMsg->DeptCode);
	clt.SetStringFieldByName("smarket_code",pAccMsg->SexNo);
	clt.SetStringFieldByName("scust_auth2",pAccMsg->StudentCode);
	if (clt.SendRequest(FUNC_QUERY_USER_INFO,TimeOut))
	{
		HazyInqAccMsg acc;
		ret = ERR_OK;
		while(clt.HasMoreRecord())
		{
			clt.GetNextPackage();
			double bala_amt = 0.0;
			char invalid_date[9] = "";
			char state_id[5] = "";
			char id_status[2] = "";
			char card_phyno[9] = "";
			int card_id;
			memset(&acc,0,sizeof acc);
			GET_PACK_STR(clt,"semail",acc.Name);
			GET_PACK_STR(clt,"smarket_code",acc.SexNo);
			GET_PACK_STR(clt,"scust_no",acc.DeptCode);
			clt.GetIntFieldByName("lvol1",(int*)&(acc.AccountNo));
			clt.GetDoubleFieldByName("damt0",&bala_amt);
			acc.Balance = (int)d4u5(bala_amt*100,0);
			GET_PACK_STR(clt,"scust_auth2",acc.StudentCode);
			GET_PACK_STR(clt,"sroom_no",acc.PID);
			GET_PACK_STR(clt,"sdate0",card_phyno);
			clt.GetIntFieldByName("lvol6",&card_id);
			if(card_id > 0)
			{
				if(strlen(card_phyno) != 8)
					continue;
			}
			else
				continue;
			do_convert_card_phyno((const unsigned char*)card_phyno,&(acc.CardNo));
			GET_PACK_STR(clt,"scust_no2",invalid_date);
			strcpy(acc.ExpireDate,invalid_date+2);
			GET_PACK_STR(clt,"sdate2",state_id);
			GET_PACK_STR(clt,"sstatus1",id_status);
			do_card_state_to_flag(state_id,acc.Flag,id_status[0]);
			// 写入文件
			if(fwrite(&acc,sizeof(acc),1,fp) < 1)
			{
				ret = ERR_REFUSE;
				break;
			}
			rec_cnt++;
		}
	}
	if(fp)
	{
		fclose(fp);
	}
	*RecNum = rec_cnt;
	return ret;
}

int CALLAPI TA_DownControlFile(short timeOut=10)
{
	return ERR_OK;
}

BOOL CALLAPI TA_ExtractConFile(const int readrec , const char * fn)
{
	int ret,rec_cnt;
	int dict_no = -1;
	void *pdata;
	int data_len;
	FILE *fp;
	if(fn == NULL)
		return FALSE;
	if(do_check_file_exists(fn))
	{
		if(unlink(fn) == -1)
			return FALSE;	
	}
	KS_YKT_Clt clt;
	switch(readrec)
	{
	case OFFSET_T_DEPARTMENT:	/* 部门组织表 */
		dict_no = -22;
		break;
	case OFFSET_T_PID:			/* 身份代码表 */
		break;
	case OFFSET_T_IDTYPE:		/* 证件类型表 */
		dict_no = 87;
		break;
	case OFFSET_T_PEOPLE:		/* 民族表 */
		dict_no = 2001;
		break;
	case OFFSET_T_NATION:		/* 国籍表 */
		dict_no = 89;
		break;
	case OFFSET_T_ZZMM:			/* 政治面貌 */
		break;
	case OFFSET_T_AREA:			/* 校/厂区代码表 */
		dict_no = -27;
		break;
	case OFFSET_T_SS_YUAN:		/* 宿舍（苑/栋 */
	case OFFSET_T_WHCD:			/* 文化程度 */
	case OFFSET_T_CARDTYPE:     /* 卡样管理表 */
	case OFFSET_T_JSZC:			/* 技术职称 */
	case OFFSET_T_XZZW:			/* 行政职务 */
	case OFFSET_SCHOOLCODE:		/* 0:学校代码SchoolCode*/
	case OFFSET_SUBJECT:		/* 1:日报字典Subject*/
	case OFFSET_FEE:			/* 2:操作费用设定表fee*/
	case OFFSET_CONFIGINFO:		/* 3:各种代码字典ConfigInfo*/
	case OFFSET_BRANCH:			/* 4:商户部门表branch*/
	case OFFSET_CSZD:			/* 5:系统参数cszd*/
	case OFFSET_TRCD:			/* 6:事件代码表trcd*/
	case OFFSET_MESSAGE:		/* 7:系统信息表message*/
	default:
		return FALSE;
	}
	if(dict_no == -1)
		return FALSE;
	
	clt.SetIntFieldByName("lcert_code",dict_no);
	clt.SetStringFieldByName("scust_auth",g_devices.devices[0].oper_code);
	if(!clt.SendRequest(FUNC_READ_DICT,20000))
	{
		return FALSE; 
	}

	if((fp = fopen(fn,"wb+")) == NULL)
		return FALSE;
	rec_cnt = 0;
	ret = TRUE;
	while(clt.HasMoreRecord())
	{
		t_idtype idtype;
		t_department dept;
		t_people people;
		t_nation nation;
		t_area area;

		int ret_dict_no;
		char dict_value[31] = "";
		char dict_caption[41] = "";

		clt.GetNextPackage();
		clt.GetIntFieldByName("lcert_code",&ret_dict_no);
		GET_PACK_STR(clt,"sname",dict_value);
		GET_PACK_STR(clt,"sall_name",dict_caption);
		switch(readrec)
		{
		case OFFSET_T_DEPARTMENT:	/* 部门组织表 */
			memset(&dept,0,sizeof dept);
			src2des(dept.area_code,dict_value);
			src2des(dept.dept_name,dict_caption);
			src2des(dept.dept_easycode,dept.area_code);
			dict_no = -22;
			pdata = &dept;
			data_len = sizeof(dept);
			break;
		case OFFSET_T_IDTYPE:		/* 证件类型表 */
			dict_no = 87;
			memset(&idtype,0,sizeof idtype);
			src2des(idtype.idtype_code,dict_value);
			src2des(idtype.idtype_name,dict_caption);
			src2des(idtype.idtype_easycode,idtype.idtype_code);
			pdata = &idtype;
			data_len = sizeof(idtype);
			break;
		case OFFSET_T_PEOPLE:		/* 民族表 */
			dict_no = 2001;
			memset(&people,0,sizeof people);
			src2des(people.people_code,dict_value);
			src2des(people.people_name,dict_caption);
			src2des(people.people_easycode,people.people_code);
			pdata = &people;
			data_len = sizeof(people);
			break;
		case OFFSET_T_NATION:		/* 国籍表 */
			dict_no = 89;
			memset(&nation,0,sizeof nation);
			src2des(nation.nation_code,dict_value);
			src2des(nation.nation_name,dict_caption);
			src2des(nation.nation_easycode,nation.nation_code);
			pdata = &nation;
			data_len = sizeof(nation);
			break;

		case OFFSET_T_AREA:			/* 校/厂区代码表 */
			dict_no = -27;
			memset(&area,0,sizeof area);
			src2des(area.area_code,dict_value);
			src2des(area.area_name,dict_caption);
			src2des(area.area_easycode,area.area_code);
			pdata = &area;
			data_len = sizeof(area);
			break;
		case OFFSET_T_PID:			/* 身份代码表 */
		case OFFSET_T_ZZMM:			/* 政治面貌 */
		case OFFSET_T_SS_YUAN:		/* 宿舍（苑/栋 */
		case OFFSET_T_WHCD:			/* 文化程度 */
		case OFFSET_T_CARDTYPE:     /* 卡样管理表 */
		case OFFSET_T_JSZC:			/* 技术职称 */
		case OFFSET_T_XZZW:			/* 行政职务 */
		case OFFSET_SCHOOLCODE:		/* 0:学校代码SchoolCode*/
		case OFFSET_SUBJECT:		/* 1:日报字典Subject*/
		case OFFSET_FEE:			/* 2:操作费用设定表fee*/
		case OFFSET_CONFIGINFO:		/* 3:各种代码字典ConfigInfo*/
		case OFFSET_BRANCH:			/* 4:商户部门表branch*/
		case OFFSET_CSZD:			/* 5:系统参数cszd*/
		case OFFSET_TRCD:			/* 6:事件代码表trcd*/
		case OFFSET_MESSAGE:		/* 7:系统信息表message*/
		default:
			ret = FALSE;
			break;
		}
		if(fwrite(pdata,data_len,1,fp) != 1)
		{
			ret = FALSE;
			break;
		}
	}
	if(fp)
	{
		fclose(fp);
	}
	return ret;
}

int CALLAPI TA_CardLost(CardOperating *pCardOper, short TimeOut = 10)
{
	TEST_SYS_INIT;
	if(pCardOper->AccountNo <= 0)
		return ERR_TA_PARA;
	if(strlen(pCardOper->inqPassword) <= 0)
		return ERR_TA_PARA;
	KS_YKT_Clt clt;
	clt.SetIntFieldByName("lvol0",pCardOper->AccountNo);
	clt.SetIntFieldByName("lvol1",0);
	clt.SetIntFieldByName("lvol2",0);
	clt.SetStringFieldByName("semp_pwd",pCardOper->inqPassword);
	clt.SetStringFieldByName("sstatus0","1");
	clt.SetStringFieldByName("scust_limit",g_devices.devices[0].oper_code);
	clt.SetIntFieldByName("lvol6",g_devices.devices[0].device_id);
	clt.SetIntFieldByName("lvol7",g_devices.devices[0].device_id);
	if(clt.SendRequest(FUNC_LOST_CARD))
	{
		return ERR_OK;
	}
	pCardOper->RetCode = clt.GetReturnCode();
	return ERR_FAIL;
}

int CALLAPI TA_CRBeep(unsigned int BeepMSecond)
{
	ControlBuzzer();
	return ERR_OK;
}

short CALLAPI TA_DesEncrypt(const void *InBuf, long InLen, void *OutBuf, void *pKey)
{
	int ret,out_len;
	unsigned char *pin = (unsigned char*)InBuf;
	unsigned char *pout = (unsigned char*)OutBuf;
	unsigned char temp[8];
	int offset=0;
	out_len = 0;
	for(;offset < InLen;offset += 8)
	{
		if(InLen - offset < 8)
		{
			// 需要增补
			int pad_len = 8 - (InLen-offset);
			memcpy(temp,pin+offset,InLen-offset);
			memset(temp+8-pad_len,pad_len,pad_len);
			ret = encrypt_des((unsigned char*)pKey,8,temp,8,pout+offset);
		}
		else
			ret = encrypt_des((unsigned char*)pKey,8,pin+offset,8,pout+offset);
		if(!ret)
			return -1;
		out_len += 8;
	}
	return out_len;
}

void CALLAPI TA_DesDecrypt(const void *InBuf, long InLen, void *OutBuf, void *pKey)
{
	unsigned char *pin = (unsigned char*)InBuf;
	unsigned char *pout = (unsigned char*)OutBuf;
	int ret,offset;
	if(InLen % 8 != 0)
		return;

	for (offset = 0;offset < InLen;offset += 8)
	{
		ret = dencrypt_des((unsigned char*)pKey,8,pin+offset,8,pout+offset);
		if(ret)
			return;
	}
}

int CALLAPI TA_Refund (CardConsume *pCardCons, short TimeOut=10)
{
	return ERR_FAIL;
}

int CALLAPI TA_CardOpen(CardOperating *pCardOper, short TimeOut = 10)
{
	return ERR_OK;
}
int CALLAPI TA_CardClose(CardOperating *pCardOper, short TimeOut = 10)
{
	return ERR_OK;
}
int CALLAPI TA_PermitID(CardOperating *pCardOper, short TimeOut=10)
{
	return ERR_OK;
}
int CALLAPI TA_ProhibitID(CardOperating *pCardOper, short TimeOut=10)
{
	return ERR_OK;
}

int CALLAPI TA_InqTranFlow(InqTranFlow *pInqTranFlow, short TimeOut = 10)
{
	return ERR_FAIL;
}
int CALLAPI TA_HazyInqAccEx(AccountMsg *pAccMsg, int *RecNum , char *FileName,short TimeOut = 10)
{
	return ERR_FAIL;
}
int CALLAPI TA_InqAccEx(AccountMsgEx * pAccMsg, short TimeOut = 10)
{
	return ERR_FAIL;
}
int CALLAPI TA_InqAccByDeptClass(char *DeptCode,char *InYear,int *RecNum , char *FileName , short TimeOut=10)
{
	return ERR_FAIL;
}
int CALLAPI TA_InqAccByPIDInYear(char *PID,char *InYear,int *RecNum , char *FileName , short TimeOut=10)
{
	return ERR_FAIL;
}
int  CALLAPI TA_DownPhotoFile(char * IDNo ,char *PhotoFn,short Timeout=10)
{
	return ERR_FAIL;
}
int CALLAPI TA_UpLoadFile(char *fn , short timeOut=10)
{
	return ERR_FAIL;
}
int CALLAPI TA_DownLoadFile(char *fn , short timeOut=5)
{
	return ERR_FAIL;
}
