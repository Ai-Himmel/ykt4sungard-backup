/* --------------------------------------------
 * 创建日期: 2008 8 21
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户取款
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "account.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
	//根据卡号和钱包号得到消费者账号(借方)
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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//联机交易
//	IA->iTxCnt=p->trade_count;					//交易次数
//	IA->dInCardBala=p->in_balance;				//入卡值
//	IA->dOutCardBala=-1;							//出卡值
	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
//	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}

int F846334(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";

	InAcc IA;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_cif_customer tCustomer;
	
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	des2src(accno,rPack->sbank_acc);		//账户
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	
	if(amtcmp(rPack->damt0,0)<=0)		//取款金额
		return E_INPUT_AMT;

	//取帐户信息
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",accno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}	
	double accbefbal=tAccount.cur_bala;
	char seedkey[33]="";
	char inpwd_crypt[65]="";
	char inpwd_plain[65]="";
	char dbpwd_plain[65]="";
	des2src(inpwd_crypt,rPack->snote2);
	if(!strlen(inpwd_crypt))
		return E_INPUTNULL_PWD;
	ret=GetParameter(2006,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
	if(ret)
		return E_EACCPWD;
	ret=decrypt_elec_card_pwd(0,seedkey,tAccount.password,dbpwd_plain);
	if(ret)
		return E_PWD_DECRYPT;
	writelog(LOG_ERR,"input pwd[%s],db pwd[%s]",inpwd_plain,dbpwd_plain);
	if(strcmp(inpwd_plain,dbpwd_plain)!=0)
		return E_EACCPWD;
	if(tAccount.stoppayflag[0]=='1')
		return E_EACC_STOPPAY;	
	if(amtcmp(tAccount.cur_freebala,rPack->damt0)<0)
	{
		writelog(LOG_ERR,"eAcc balance[%lf] amount[%lf]",tAccount.cur_freebala,rPack->damt0);
		return E_BALANCE_SHORTAGE;
	}	
	//检查客户
	ret=DB_t_cif_customer_read_by_cut_id(tAccount.customer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tAccount.customer_id);
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state != CUSTSTAT_REGIST)
	{
		return E_CUSTOMER_LOGOUT;
	}
	tradeserial.trade_fee = rPack->damt0;					//取款金额

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
		return ret;
	
	IA.iArrInFeeSwitch[1]=1;

	double dSerialNo = 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  	//获得流水号
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}

	tradeserial.serial_no = D2I(dSerialNo);						//流水号
	tradeserial.other_seri_no = 0;							//上传端流水号
	tradeserial.serial_type = TXCODE_EACC_CASH_DEPOSIT;		//交易代码
	tradeserial.serial_state = SERISTAT_DEBT;					//流水状态
	des2src(tradeserial.operate_date,sysdate);				//发生日期
	des2src(tradeserial.operate_time,systime);				//发生时间
	des2src(tradeserial.collect_date,sysdate);					//采集日期
	des2src(tradeserial.collect_time,systime);					//采集时间
	des2src(tradeserial.enteract_date,logicdate);				//处理日期
	des2src(tradeserial.enteract_time,systime);				//处理时间
	tradeserial.card_id = tAccount.card_id;						//卡号
	tradeserial.customer_id = tAccount.customer_id;					//客户标识
	//tradeserial.in_balance=tAccount.cur_freebala;					//入卡值
	//tradeserial.trade_count=tAccount.consume_count+1;				//交易次数
	des2src(tradeserial.oper_code , rPack->semp);		//操作员代码
	tradeserial.sys_id = 0;									//外部系统标识

	IA.iCardNo=tAccount.card_id;
//	IA.iFeeType=tCustomer.fee_type;
	strcpy(IA.sArrInActno[5],tAccount.account_id);		//账号
	IA.dArrInAmt[0]=tradeserial.trade_fee;					
/*
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;
*/
	//	调用入账子模块
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",accno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	sprintf(outPack->vsmess,"取款前帐户余额%.2lf元,取款金额%.2lf,当前帐户余额:%.2lf元",accbefbal,tradeserial.trade_fee,tAccount.cur_bala);
	writelog(LOG_DEBUG,outPack->vsmess);
	//	插入卡操作流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_VSMESS,0);	
	outPack->lserial1=tradeserial.serial_no;								//流水号
	outPack->damt2 = tAccount.cur_bala;
	PutRow(handle,outPack,pRetCode,szMsg);

	return 0;
}

