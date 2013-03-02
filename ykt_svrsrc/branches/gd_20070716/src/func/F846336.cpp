/* --------------------------------------------
 * 创建日期: 2008 8 21
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户转账
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

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
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

int F846336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int transflag=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";

	int cardno=0;

	InAcc	IA;
	char sMaxBalance[20]="";
	double dMaxCardBalance = 0;
	double dMaxEACCBalance = 0;
	T_t_tif_tradeserial  tradeserial;
	T_t_cif_customer tCustomer;
	T_t_pif_card tCard;
	T_t_aif_account tCardAccount;
	T_t_aif_account tEAcc;

	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tCard,0,sizeof(tCard));
	memset(&tCardAccount,0,sizeof(tCardAccount));
	memset(&tEAcc,0,sizeof(tEAcc));
	
	char cardphyid[9]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	transflag=rPack->lvol3;		
//	char key[17]="";
//	char pwd_plain[33]="";
//	char pwd_crypt[65]="";
//	strcpy(key,STATIC_SEED_KEY);
//	des2src(pwd_crypt,rPack->snote2);
//	EncodePwd(key,pwd_plain,pwd_crypt, 0);

	getsysdate(sysdate);
	getsystime(systime);
	
	cardno=rPack->lvol0;		//卡号

	//检查卡号
	ret=DB_t_pif_card_read_by_card_id(cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_R;
	}

	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}
	
	//比较卡物理ID是否相同
	if(strcmp(tCard.physical_no,rPack->sstation0)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.physical_no,rPack->sstation0);
		return E_CARD_PHYNO_DIFFER;
	}
	//检查卡的有效期
	if(strncmp(tCard.end_time,sysdate,6)<=0)
		return E_CARD_EXPIRE;
	//检查卡对应的账户
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(cardno, PURSE_NO_ONE,&tCardAccount);
	if (ret)
	{
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return  E_DB_ACCOUNT_R;
	}
	if(tCardAccount.current_state!=1)
		return E_ACTNO_LOGOUT;

	//检查客户表,电子钱包是否开通
	ret = DB_t_cif_customer_read_by_cut_id(tCardAccount.customer_id, &tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state==CUSTSTAT_LOGOUT)
		return E_CUSTOMER_LOGOUT;
	
	if(tCustomer.eaccflag[0]=='0')
		return E_EACCNO_LOGOUT;

	//检查电子账户
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCustomer.cut_id, ACCTYPE_PEREACC, &tEAcc);
	if (ret)
	{
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return  E_DB_ACCOUNT_R;
	}
	if(tEAcc.current_state!=1)
		return E_ACTNO_LOGOUT;

	tradeserial.trade_fee = rPack->damt0;					//充值金额
	char inpwd_crypt[65]="";
	char seedkey[33]="";
	char inpwd_plain[65]="";
	char dbpwd_plain[65]="";
	if(transflag)		//电子钱包到卡转帐
	{
		tradeserial.serial_type = TXCODE_EACC2CARD;
		ret=GetParameter(2006,seedkey);
		if(ret)
			return ret;
		des2src(inpwd_crypt,rPack->snote2);
		if(!strlen(inpwd_crypt))
			return E_INPUTNULL_PWD;
		
		ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
		if(ret)
			return E_EACCPWD;
		ret=decrypt_elec_card_pwd(0,seedkey,tEAcc.password,dbpwd_plain);
		if(ret)
			return E_PWD_DECRYPT;
		if(strcmp(inpwd_plain,dbpwd_plain)!=0)
			return E_EACCPWD;
		if(tEAcc.stoppayflag[0] == '1')
			return E_EACC_STOPPAY;
		if(amtcmp(tEAcc.cur_freebala , rPack->damt0) <0)   //金额不足
			return E_EACC_BALANCE_SHORTAGE;
		ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxBalance);
		if(ret)
			return ret;
		dMaxCardBalance=atof(sMaxBalance);
		if(amtcmp(tCardAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
			return E_AMT_EXCEED_MAX;

//		tradeserial.in_balance=rPack->damt1;			//卡上余额
//		tradeserial.trade_count=rPack->lvol6+1;		//交易次数
		
	}
	else
	{
		tradeserial.serial_type = TXCODE_CARD2EACC;

		strcpy(seedkey,STATIC_SEED_KEY);
		des2src(inpwd_plain,rPack->scust_limit2);
		EncodePwd(seedkey,inpwd_plain,inpwd_crypt,0);
		if(strcmp(tCardAccount.password,inpwd_crypt)!=0)
			return E_CARD_PWD_DIFFER;
		if(amtcmp(tCardAccount.cur_freebala , rPack->damt0) <0)   //金额不足
			return E_EACC_BALANCE_SHORTAGE;
			
		ret=GetParameter(GLOBE_MAXEACCBALANCE,sMaxBalance);
		if(ret)
			return ret;
		dMaxEACCBalance=atof(sMaxBalance);
		if(amtcmp(tEAcc.cur_bala+tradeserial.trade_fee,dMaxEACCBalance)>0)
			return E_AMT_EXCEED_MAX;
		
//		tradeserial.in_balance=tEAcc.cur_freebala;
//		tradeserial.trade_count=tEAcc.consume_count+1;		//交易次数

	}

	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
		return ret;
	
	double dSerialNo = 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dSerialNo);											//流水号
	tradeserial.other_seri_no = 0;															//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code, rPack->sname);
	tradeserial.customer_id = tCustomer.cut_id;
	tradeserial.sys_id = 0;																//外部系统标识
	tradeserial.in_balance=rPack->lvol7/100.0;
	tradeserial.trade_count=rPack->lvol6+1;		//交易次数
	des2src(IA.sArrInActno[0],tCardAccount.account_id);						//卡帐户
	des2src(IA.sArrInActno[5],tEAcc.account_id);						//电子钱包帐户
	IA.iCardNo=tEAcc.card_id;

	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}	
	if(TXCODE_CARD2EACC==tradeserial.serial_type)
		sprintf(outPack->vsmess,"卡转电子钱包:转帐前卡余额%.2lf元,转账金额%.2lf,当前卡余额%.2lf元",tradeserial.in_balance,tradeserial.trade_fee,tradeserial.out_balance);
	else
		sprintf(outPack->vsmess,"电子钱包转卡:转帐前卡余额%.2lf元,转账金额%.2lf,当前卡余额%.2lf元",tradeserial.in_balance,tradeserial.trade_fee,tradeserial.out_balance);
	writelog(LOG_DEBUG,outPack->vsmess);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	if(amtcmp(tradeserial.out_balance,0)<0)
		return E_ENTER_ACCOUNT;

	SetCol(handle,F_DAMT2,F_LSERIAL1,F_VSMESS,0);		

	outPack->damt2=tradeserial.out_balance;		//出卡值
	outPack->lserial1=tradeserial.serial_no;			//流水号
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
