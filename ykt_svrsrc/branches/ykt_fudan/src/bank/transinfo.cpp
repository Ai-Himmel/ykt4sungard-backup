/* ----------------------------------------------------------
 * 程序名称：transinfo.h
 * 创建日期：2004-09-09 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：银行转帐各种交易函数实现
 * ----------------------------------------------------------
 * 修改日期: 2005-03-10
 * 修改人员: 林钦
 * 修改描述: 将与银行通信部分移到bank.h，以与bu代码分离，供bankguard调用
 *           此处只保留pos请求处理（包含银行接口调用）
 * 版本信息：1.0.1.1
 * ----------------------------------------------------------*/
#include <stdlib.h>
#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "errdef.h"
#include "mypub.h"
#include "tcp.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "account.h"
#include "bank.h"


#ifndef	DEBUG
	#define	DEBUG
#endif
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);



//查询转帐流水
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no)
{
	int ret=0;
	T_t_tif_tradeserial  tradeserial;
	INNER_TRANS_REQUEST from_pos;
	double unique=0;
	memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//清空流水结构体
	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pnode,sizeof(from_pos));
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);			//流水号
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.serial_no=int(unique);
	tradeserial.serial_type=TRADE_INNER_DETRANS;			//交易代码
	tradeserial.serial_state=SERISTAT_NONEEDDEBT;			//流水状态
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//交易日期
		memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//交易时间
	}
	//memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//交易日期
	//memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//交易时间
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));//采集日期
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));//采集时间
	tradeserial.maindevice_id=GetTransferSystemId();				//子系统号码
	tradeserial.device_id=atoi(from_pos.TerminalId);			//终端ID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100;			//转帐金额
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));	//银行卡号－－－－更港添加数据库字段
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;				//外部系统标识，此处为区分多个银行--- 农业银行为1
	tradeserial.condition_id=SELF_TRANS;						//自动/自助转帐标识
	strcpy(tradeserial.oper_code,"system");						//操作员代码
	tradeserial.other_seri_no=other_serial_no;					//原始流水号
	tradeserial.tmark=0;									//用来记录冲正发送次数？

	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_ERR,"detrans ok");
	return	0;


}

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//工作站标识
	IA->iDevId=p->device_id;						//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;					//交易码
	strcpy(IA->sTxDate,p->operate_date);			//交易日期
	strcpy(IA->sTxTime,p->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,p->oper_code);			//操作员
	strcpy(IA->sChkOper,p->reserve_1);			//复核操作员

	IA->iUseCardFlag=IS_YES;						//卡交易
	IA->iTxCnt=p->trade_count;					//交易次数
	IA->dInCardBala=p->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}

//POS登陆	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode)
{
	//double unique=0;
	int ret=0;
	INNER_TRANS_REQUEST  from_pos;


	//银行未签到成功，POS不能登陆授予密钥
	if(!BANK_LOGIN)
	{
		writelog(LOG_ERR,"System not login to bank,pos login forbidden!shm[1]=[%d]",shm[1]);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NETERR);
		return	E_TRANS_BANK_NETERR;
	}

	memcpy(&from_pos,pNode,sizeof(from_pos));
	T_t_tif_tradeserial  	tradeserial;		//卡操作流水表 	tradeserial;
	T_t_pif_device 		t_pif_device;
	T_t_pif_cur_syspara 	t_syspara;


	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&t_pif_device,0,sizeof(t_pif_device));
	memset(&t_syspara,0,sizeof(t_syspara));

	ret=DB_t_pif_cur_syspara_read_by_id(2006, &t_syspara);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	ret=DB_t_pif_device_read_lock_by_cur_and_device_id(atoi(from_pos.TerminalId),&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	t_pif_device.state_id=DEVISTAT_ONLINE;		//更改设备注册表状态为在线状态
	ret=DB_t_pif_device_update_lock_by_cur(&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_update_lock_by_cur error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

    	ret=db_commit();
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	//填充应答包－－－pNode
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	memcpy(pNode->BankCardNewPwd,t_syspara.value,sizeof(pNode->BankCardNewPwd));
	writelog(LOG_INFO,"device login dev[%d] shm=[%s],pNode->bankcardpwd[%s]",t_pif_device.device_id,shm,pNode->BankCardPwd);
	return 0;
}


//查询校园卡余额
//暂时该功能取消，终端通过读写卡取得余额
int Pos_QuerySchool(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	//T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}


	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	//根据卡号和钱包号，返回帐号
	ret=GetActnoByCardIdAndPurseId(account_id,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId err,CardNo=[%s],Notecase=[%s]",from_pos.CardNo,from_pos.Notecase);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	ret=DB_t_aif_account_read_by_account_id(account_id, &account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	//填充应答包
	memset(pNode,0,sizeof(from_pos));
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	//printf("卡余额= [%f]\n",account.cur_freebala);
	sprintf(pNode->AccountMoney,"%f",account.cur_freebala);
	writelog(LOG_INFO,"query school card balance succeed!");

	return 0;

}

//查询银行卡余额
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	double unique=0;
//	char buffer[1024]="";


	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	struct SockNode SockNode;

	memset(&SockNode,0,sizeof(SockNode));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));

	memcpy(&from_pos,pNode,sizeof(from_pos));


	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}


	//组织银行包
	//写交易代码
	memcpy( BankReqPak.TradeCode,TRADE_BANK_QUERY, BANK_TRADE_CODE_LEN);
	//写交易日期和交易时间
	ret=get_datetime_from_db(BankReqPak.TradeDate,BankReqPak.TradeTime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
		memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	}
	//memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	//memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//写银行卡号字段
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//写银行卡号字段
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);
	//写银行卡密码字段
	//通过16进制格式传输，再解密
	hex2dec(from_pos.BankCardPwd, (unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));
	#ifdef DEBUG
		char buffer[100]="";
		int k=0;
		for(int i=0;i<16;i++)
		{
			k=(unsigned char)BankReqPak.BankCardPwd[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		writelog(LOG_INFO,"BankCardNo=[%s],BankCardPwd=[%s]",BankReqPak.BankCardNo,buffer);
		writelog(LOG_INFO,"BankCardNo=[%s],fromCardPwd=[%s]",BankReqPak.BankCardNo,from_pos.BankCardPwd);
	#endif

	//写校园端流水号
	sprintf(BankReqPak.CustSn,"%-8f",unique);
	//写院校代码
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	BankReqPak.AutoFlag='0';
	//写校验mac码
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);

	//memcpy(SockNode.Buf,&BankReqPak,sizeof(BankReqPak));
	TRACE_BANK_TRANS(&BankReqPak,"send query bank package");

	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}


	TRACE_BANK_TRANS(&BankAnsPak,"receivce query bank package");

	//农行暂时未校验该mac,所以暂时屏蔽掉
	/*
	ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	//更改数据库流水日志,包括填写一些额外字段以及填写银行返回信息等－－－－暂时屏蔽没作
	/*
	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(int(unique), &tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"read from t_tif_tradeserial table error,error code=[%d]",ret);
		sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		db_rollback();
		return 	E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//通讯或密钥错
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}

	//填充应答包
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->Balance,BankAnsPak.Balance,sizeof(pNode->Balance));
	writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%s]",BankAnsPak.Balance);
	return 0;

}

//修改校园卡密码
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
//	double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
//	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	Strncpy_t(account_pwd, from_pos.AccountNewPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);
	memcpy(card.password,pwd,sizeof(card.password));
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_update_lock_by_cur error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}
	//填充应答包

	memset(pNode,0,sizeof(from_pos));
	writelog(LOG_INFO,"Change school card password succeed!");
	return 0;

}

//挂失校园卡

int Pos_LostCard(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	char enddate[10 + 1] = "";
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));

	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}

	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	ret=get_tradecard_no_by_stupid(from_pos.CardNo,&card_id);			//卡标识
	if(ret)
	{
		if(100==ret)
		{
			writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d]",ret);
			return E_TRANS_SCHACC_NOEXIT;
		}
		if(-811==ret)
		{
			writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
			return E_TRANS_SCHCARD_TWICE;
		}
		writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//writelog(LOG_INFO,"card_id=[%d]",*pCardid);


	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	Cut_id = card.cosumer_id;														//客户号
	des2src(Operator,"system");												//操作员号
	maindevice_id = GetTransferSystemId();											//上传工作站标识
	device_id = atoi(from_pos.TerminalId);										//采集设备标识

	//判断卡密码是否正确
	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		return E_TRANS_SCHCARD_PWDERR;
	}
	/*
	//	检查客户信息，判断是否可以挂失
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetCardState error,errcode=[%d],card_id=[%d]",ret,card_id);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	//	修改卡状态为挂失
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_TRUE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	插入卡挂失有效期限表
	/*
	ret=GetLostCardValiddate(sysdate,enddate);											//获得挂失有效期限
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetLostCardValiddate=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.card_id = card_id;													//卡号
	des2src(cardlossinfo.begin_date,sysdate);											//起始日期
	des2src(cardlossinfo.end_date,enddate);											//截至日期
	des2src(cardlossinfo.operate_date,sysdate);										//操作日期
	des2src(cardlossinfo.operate_time,systime);										//操作时间
	cardlossinfo.state_id=STATE_VALID;												//有效
	ret = DB_t_pif_cardlossinfo_add(&cardlossinfo);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_add=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//如果该卡号被冻结,则挂失时对黑名单不处理
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(card.card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_card_id_and_is_ad error,errcode=[%d],card_id=[%d]",ret,card.card_id);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		ret=InsertToBlkList(card.card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList error,errcode=[%d],card_id=[%d]",ret,card.card_id);
			return E_TRANS_UNKNOW_ERROR;
		}

		//广播黑名单
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card.card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"AddMsgLst=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

	}


	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//发生日期
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//采集日期
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//采集时间
	des2src(tradeserial.enteract_date,logicdate);							//处理日期
	des2src(tradeserial.enteract_time,tradeserial.operate_time);							//处理时间
	tradeserial.serial_no = (int)dUniqno;									//流水号
	tradeserial.serial_type = TXCODE_CARD_LOSS;							//挂失
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;						//流水状态
	tradeserial.maindevice_id = GetTransferSystemId();						//上传工作站标识
	tradeserial.device_id = atoi(from_pos.TerminalId);						//采集设备标识
	tradeserial.card_id = card_id;										//交易卡号
	tradeserial.customer_id=Cut_id;										//客户号
	des2src(tradeserial.oper_code,Operator);
	tradeserial.other_seri_no=from_pos.SendNo;

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	return 0;
}

int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode)
{

	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	//char enddate[10 + 1] = "";
	//int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}

	Cut_id = card.cosumer_id;													//客户号
	des2src(Operator,"system");												//操作员号
	//maindevice_id = GetTransferSystemId();										//上传工作站标识
	//device_id = atoi(from_pos.TerminalId);										//采集设备标识

	//des2src(sysdate,from_pos.TradeDate);
	//des2src(systime,from_pos.TradeTime);

	//des2src(black_sheet.operate_date,sysdate);
	//des2src(black_sheet.operate_time,systime);

	//des2src(hi_enddate,sysdate);
	//des2src(hi_endtime,systime);

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHCARD_FREEZE;
	//	return E_TRANS_SCHCARD_UNLOSTING;
	}
	//去掉重复解挂的限制，允许正常状态下解挂，并下发名单
	//如果挂失状态，判断是否存在非挂失的另外的一张卡
	//如果是，不允许解挂
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		ret=IsExistNoLostCardByCustomId(Cut_id);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			return E_TRANS_SCHCARD_TWICE;
		}
	}
	//修改挂失表状态为无效
	/*
	ret=DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id(card.card_id,STATE_VALID,&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id error,card_id=[%d],errcode=[%d]",card.card_id,ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.state_id=STATE_INVALID;
	des2src(cardlossinfo.end_date,sysdate);
	ret=DB_t_pif_cardlossinfo_update_lock_by_cur1(&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_update_lock_by_cur1 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//状态作为黑名单的有效状态,不作为卡状态
		//修改原来的黑名单的状态标志为无效
		//	插入黑名单表
		black_sheet.card_id = card.card_id;
		black_sheet.is_ad = DELETE_BLACKLIST;
		des2src(black_sheet.operate_date,sysdate);
		des2src(black_sheet.operate_time,systime);
		memcpy(black_sheet.volume,sysdate+2,6);
		memcpy(black_sheet.volume+6,systime,6);
		strcpy(black_sheet.validdate,VALIDDATE);
		black_sheet.state_id = STATE_VALID;
		ret = DB_t_tif_black_sheet_add(&black_sheet);
		if (ret)
		{
			writelog(LOG_ERR,"DB_t_tif_black_sheet_add error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		//广播黑名单
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,black_sheet.card_id);
		AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, black_sheet.volume);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,black_sheet.is_ad);	//增删标志

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"AddMsgLst error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//	修改卡状态为解挂状态
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_FALSE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//发生日期
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);				//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.serial_no = (int)dUniqno;													//流水号
	tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;								//解挂
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;										//流水状态
	tradeserial.maindevice_id = GetTransferSystemId();									//上传工作站标识
	tradeserial.device_id = atoi(from_pos.TerminalId);										//采集设备标识
	tradeserial.card_id = card.card_id;														//交易卡号
	tradeserial.customer_id = Cut_id;
	des2src(tradeserial.oper_code, "system");
	//	插入卡操作流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	return 0;
}

//POS转帐
int Pos_Transfer(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_tif_tradeserial  tradeserial_bak;
	T_t_pif_card		card;
	InAcc	IA;

	memset(&tradeserial_bak,0,sizeof(tradeserial_bak));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	//判断是否处于日终结算状态
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}

	//转账不允许转小数金额
	if(0!=memcmp(from_pos.TransMoney+7,"00",2))
	{
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",atol(from_pos.TransMoney)/100.00);
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}

	//开始填充流水数据
	//流水号
    alarm(3);
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
    alarm(0);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
    
	tradeserial.serial_no=int(unique);
	//纪录流水号，作为冲正使用
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=from_pos.SendNo;	//上传端流水号
	tradeserial.serial_type=TRADE_INNER_TRANS;	//交易代码
	tradeserial.serial_state=SERISTAT_NODEBT;	//流水状态
	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.in_balance=double(atoi(from_pos.AccountMoney)/100.00);	//入卡金额
	tradeserial.out_balance=tradeserial.in_balance;						//出卡金额
	tradeserial.trade_count=from_pos.RecvNo+1;							//当前卡中交易次数

	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//采集日期
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//采集时间
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//入帐日期
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//入帐时间
	tradeserial.maindevice_id=GetTransferSystemId();	//子系统号码
	tradeserial.device_id=atoi(from_pos.TerminalId);	//终端ID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100.00;	//转帐金额
	//银行卡号－－－－更港添加数据库字段
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;	//外部系统标识，此处为区分多个银行--- 农业银行为1
	tradeserial.condition_id=SELF_TRANS;	//自动/自助转帐标识
	//tradeserial.out_account_id=;
	//tradeserial.in_account_id=;
	tradeserial.customer_id=card.cosumer_id;
	strncpy(tradeserial.oper_code,"system",sizeof(tradeserial.oper_code));	//操作员代码
	//结束填充流水数据
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//把流水结构备份起来，作为测试入帐后的数据
	//防止重复运算搭伙费
	memcpy(&tradeserial_bak,&tradeserial,sizeof(tradeserial_bak));

	double trade_fee=0;
	double board_fee=0;
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_aif_account	tAccount;		//帐户表
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;

	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));

	//判断转帐金额是否超出钱包最大限额
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	//读取客户收费类别字段
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		/*
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
		*/
	}
	DB_t_cif_customer_free_lock_cur();
	//填写入账结构,问问闻剑
	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
/*
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;

*/
	//结束--是否process也要修改

	ret=process(&IA,&tradeserial_bak);
	if(ret)
	{
		writelog(LOG_ERR,"test process err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}
	//如果测试成功仍然回滚
	ret=db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_rollback err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}

	//组织银行包
	memcpy(BankReqPak.TradeCode,TRADE_BANK_TRANS, BANK_TRADE_CODE_LEN);	//写交易代码
	memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//由于银行给的接口中的校园卡账号字段只有10个长度
	//所以这里在校园卡账号字段上填写校园卡卡号
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(from_pos.CardNo));
	/*
	//写校园卡帐号
	ret=GetActnoByCardIdAndPurseId(BankReqPak.CustAccountNo,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId error,CardNo=[%s],Notecase=[%d]",from_pos.CardNo,from_pos.Notecase);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//写银行卡号字段
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);	//写银行卡号字段
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));	//写商户号字段
	sprintf(BankReqPak.TransMoney,"%-9s",from_pos.TransMoney);	//写转帐金额字段
	//通过16进制传输，然后解密
	hex2dec(from_pos.BankCardPwd,(unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));	//写银行卡密码字段
	sprintf(BankReqPak.CustSn,"%-d",tradeserial.serial_no);	//写校园端流水号
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);	//写院校代码
	BankReqPak.AutoFlag='0';	//写自动自助标志
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);//写校验mac码

	TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
	if(ret)
	{
		if(E_TRANS_BANK_NOANSWER==ret)							//如果银行没有返回包，进行冲正处理
		{
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;
			}
			writelog(LOG_INFO,"This trade have detrans!");
			return E_TRANS_BANK_NOANSWER;
		}
		else
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
			return ret;
		}
	}

	TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	//校验mac，判断银行接收包是否正确
	//ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	ret=0;
	if(ret)
	{
			writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;
			}
			ret=db_commit();
			if(ret)
			{
				writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
			//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
			return	E_TRANS_BANK_RECVERR;
	}

	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//银行卡挂失
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//银行卡状态错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//银行卡金额不足
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//银行未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//银行密码错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//通讯或密钥错
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//其他未知错误
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}
	//进行入帐操作
	//trade_fee=0;
	//board_fee=0;

	//填写入账结构,问问闻剑
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		ret=DelTrans(&from_pos, temp_serial_no);
		if(ret)
		{
			writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
			//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
			return E_TRANS_UNKNOW_ERROR;
		}
		return	E_TRANS_UNKNOW_ERROR;
	}
	char sMsg[255]="";
	char sDebugMsg[255]="";
	sprintf(sDebugMsg,"流水号:%d ",IA.iSerialNo);
	double trans_amt=0.0;
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_BANK_TRANSFER:
				trans_amt=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(sDebugMsg,sMsg);
		}
	}
    	sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);
	//double tmp_fee=0;
	//tmp_fee=tradeserial.out_balance;

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(tradeserial.serial_no,&tradeserial_bak);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//tradeserial.out_balance=tmp_fee;
	tradeserial.serial_state=SERISTAT_DEBT;
	//tradeserial.out_balance=tradeserial.in_balance+tradeserial.trade_fee;
	//tradeserial.boardfee=board_fee;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_tif_tradeserial_free_lock_cur();
	writelog(LOG_ERR,"ou error,error code=[%d]",ret);
	sprintf(pNode->TransMoney,"%f",trans_amt);
	sprintf(pNode->ExtraMoney,"%f",tradeserial.boardfee);
	pNode->RecvNo=tradeserial.serial_no;
	pNode->MngFeeFlag='1';
	writelog(LOG_INFO,"transfer succeed!");
	return 0;
}
//POS缴费
int Pos_Fee(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Pay fee function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//增加对应关系
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Add realation function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//删除对应关系
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Delete relation function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//查询校园卡转帐流水
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID *handle,int *pRetCode,char *szMsg)
{

	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	int cnt=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account account;
	T_t_pif_card card;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	ret=DB_t_tif_tradeserial_open_select_by_cur3_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
	if(ret)
	{
			db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
	}
	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	while(1)
	{
		ret=DB_t_tif_tradeserial_fetch_select_by_cur3(&tradeserial);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial table!");
						break;
					}
				else		break;
			}
			else
				return   E_TRANS_UNKNOW_ERROR;
		}
		cnt++;

		memcpy(from_pos.TradeDate,tradeserial.operate_date,sizeof(from_pos.TradeDate));
		memcpy(from_pos.TradeTime,tradeserial.operate_time,sizeof(from_pos.TradeTime));
		sprintf(from_pos.CardNo,"%d",tradeserial.card_id);
		memcpy(from_pos.BankCardNo,tradeserial.b_act_id,sizeof(from_pos.BankCardNo));
		sprintf(from_pos.TransMoney,"%d",int(tradeserial.trade_fee)*100);
		if(tradeserial.serial_state!=2)
		{
			sprintf(from_pos.RetCode,"%s","失败");
		}
		else sprintf(from_pos.RetCode,"%s","成功");

		//开始返回应答包
		Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
		Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
		Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
		Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
		out_pack->lvol0=from_pos.SendNo;
		out_pack->lvol1=from_pos.RecvNo;
		memcpy(out_pack->sdate0,from_pos.TradeDate,sizeof(from_pos.TradeDate));
		memcpy(out_pack->stime0,from_pos.TradeTime,sizeof(from_pos.TradeTime));
		memcpy(out_pack->sdate1,from_pos.BankDate,sizeof(from_pos.BankDate));
		memcpy(out_pack->stime1,from_pos.BankTime,sizeof(from_pos.BankTime));
		Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
		Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
		Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
		out_pack->lvol2=from_pos.Notecase;
		Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
		sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
		Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
		Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
		Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
		Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
		Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));
//	printf("LINE:%d\n",__LINE__);

		PutRow(handle,out_pack,pRetCode,szMsg);
		if(cnt>=10)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			break;
		}
	}
//	printf("LINE:%d\n",__LINE__);


	T_t_tif_tradeserial_his tradeserial_his;
	memset(&tradeserial_his,0,sizeof(tradeserial_his));

	if(cnt<10)
	{
		ret=DB_t_tif_tradeserial_his_open_select_by_cur1_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
		if(ret)
		{
				db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
		}
	//	printf("LINE:%d\n",__LINE__);

		while(1)
		{
			ret=DB_t_tif_tradeserial_his_fetch_select_by_cur1(&tradeserial_his);
			if(ret)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				if(ret==DB_NOTFOUND)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial_his table!");
					break;
				}
				else
					return   E_TRANS_UNKNOW_ERROR;
			}
			cnt++;

			memcpy(from_pos.TradeDate,tradeserial_his.operate_date,sizeof(from_pos.TradeDate));
			memcpy(from_pos.TradeTime,tradeserial_his.operate_time,sizeof(from_pos.TradeTime));
			sprintf(from_pos.CardNo,"%d",tradeserial_his.card_id);
			memcpy(from_pos.BankCardNo,tradeserial_his.b_act_id,sizeof(from_pos.BankCardNo));
			sprintf(from_pos.TransMoney,"%d",int(tradeserial_his.trade_fee)*100);
			if(tradeserial_his.serial_state!=2)
			{
				sprintf(from_pos.RetCode,"%s","失败");
			}
			else sprintf(from_pos.RetCode,"%s","成功");

			//开始返回应答包
			Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
			Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
			Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
			Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
			out_pack->lvol0=from_pos.SendNo;
			out_pack->lvol1=from_pos.RecvNo;
			Strncpy_t(out_pack->sdate0,from_pos.TradeDate,sizeof(out_pack->sdate0));
			Strncpy_t(out_pack->stime0,from_pos.TradeTime,sizeof(out_pack->stime0));
			Strncpy_t(out_pack->sdate1,from_pos.BankDate,sizeof(out_pack->sdate1));
			Strncpy_t(out_pack->stime1,from_pos.BankTime,sizeof(out_pack->stime1));
			Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
			Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
			Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
			out_pack->lvol2=from_pos.Notecase;
			Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
			sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
			Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
			Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
			Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
			Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
			Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));

			PutRow(handle,out_pack,pRetCode,szMsg);
			if(cnt>=10)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				break;
			}

		}
	}


	writelog(LOG_INFO,"query trans record succeed!");
	return 0;
}
//圈存机写卡失败冲正(实际并不冲正，只是改写卡状态)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode)
{

	int ret = 0;
	int card_id = 0;
	char logicdate[11]="";
	int serial_no=0;
	T_t_pif_card  card;
	T_t_tif_tradeserial tradeserial;

	INNER_TRANS_REQUEST from_pos;

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"GetLogicDate err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	serial_no=from_pos.RecvNo;
	ret=DB_t_tif_tradeserial_read_by_serial_no(serial_no,&tradeserial);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_tif_tradeserial_read_by_serial_no err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//修改原卡状态为发卡写卡失败状态
	card_id = tradeserial.card_id;

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_read_lock_by_cur_and_card_id err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	memset(card.comments,0,sizeof(card.comments));
	AddXmlItemStr(card.comments, XML_KEY_OPERATEDATE,logicdate);
	AddXmlItemInt(card.comments,XML_KEY_SERIALNO,serial_no);
	AddXmlItemInt(card.comments,XML_KEY_TRADECODE,TRADE_INNER_TRANS);

	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_update_lock_by_cur err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	writelog(LOG_INFO,"update card status succeed!");

	return 0;

}
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

