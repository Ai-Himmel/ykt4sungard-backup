/* --------------------------------------------
 * 创建日期: 2008 8 21
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户充值
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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//联机交易
	IA->iTxCnt=0;					//交易次数
	IA->dInCardBala=0;				//入卡值
	IA->dOutCardBala=0;							//出卡值

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

int F846333(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	char accno[21]="";

	int	type=0;
	InAcc	IA;
	char sMaxEAccBalance[20]="";
	double dMaxEAccBalance = 0;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_cif_customer tCustomer;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);

	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	des2src(accno,rPack->sbank_acc); //账号
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	
	if(amtcmp(rPack->damt0,0)<=0)   //充值金额
		return E_INPUT_AMT;
		
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	//检查账户
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}
	
	double accbefbal=tAccount.cur_bala;
	
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
	
	tradeserial.trade_fee = rPack->damt0;					//充值金额
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
		return ret;
//
	ret=GetParameter(GLOBE_MAXEACCBALANCE,sMaxEAccBalance);
	if(ret)
		return ret;
	dMaxEAccBalance=atof(sMaxEAccBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxEAccBalance)>0)
		return E_AMT_EXCEED_MAX;
	
	type=rPack->lvol9;										//交易类型
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(type)
	{
		case TYPE_CASH:	//现金
			IA.iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//支票
			IA.iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//经费本
			IA.iArrInFeeSwitch[3]=1;
			break;
		default:
			return E_INPUT_DEPOSIT_TYPE;
	}

	double dSerialNo = 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dSerialNo);											//流水号
	tradeserial.other_seri_no = 0;															//上传端流水号
	tradeserial.serial_type = TXCODE_EACC_SAVING_CASH;
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tCustomer.cut_id;
//	tradeserial.in_balance=tAccount.cur_freebala;
//tradeserial.trade_count=tAccount.consume_count+1;		//交易次数
	tradeserial.sys_id = 0;																//外部系统标识
	switch(type)
	{
		case TYPE_CASH:		//现金
			break;
 		case TYPE_BILL:		//支票
		case TYPE_FUNDBOOK:	//经费本
		case TYPE_OTHER:	//其他
 			tSavdtl.amount=rPack->damt0;				//发生额
				break;
			des2src(tSavdtl.bill_no,rPack->sphone);		//票据号码
			if(strlen(tSavdtl.bill_no)<1)
				return E_INPUT_BILLNO;
			
			tSavdtl.card_no=tAccount.card_id;	//卡号
			des2src(tSavdtl.oper_no,rPack->semp);	//操作员
			tSavdtl.seqno=tradeserial.serial_no;			//流水号
			des2src(tSavdtl.tx_date,sysdate);			//发生日期
			des2src(tSavdtl.tx_time,systime);			//发生时间
			tSavdtl.cnt=1;								//票据数量
			tSavdtl.bill_type=type;						//票据类型
			tSavdtl.tx_code=tradeserial.serial_type;		//交易码
			ret=DB_t_tif_savdtl_add(&tSavdtl);
			if(ret)
			{
				if(DB_REPEAT==ret)
					return E_DB_SAVDTL_E;
				else
					return E_DB_SAVDTL_I;
			}
			break;
		default:
			return E_TXCODE_NOT_EXIST;
	}
	
	des2src(IA.sArrInActno[5],tAccount.account_id);						//帐户
//	writelog(LOG_ERR,"account_id[%s]",IA.sArrInActno[5]);
//	IA.iCardNo=tAccount.card_id;
//	IA.iFeeType=tCustomer.fee_type;
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
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	
	sprintf(outPack->vsmess,"充值前帐户余额%.2lf元,充值金额%.2lf,当前帐户余额:%.2lf元",accbefbal,tradeserial.trade_fee,tAccount.cur_bala);
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
	SetCol(handle,F_DAMT2,F_LSERIAL1,F_VSMESS,0);		

	outPack->damt2=tAccount.cur_bala;		//出卡值
	outPack->lserial1=tradeserial.serial_no;			//流水号
	PutRow(handle,outPack,pRetCode,szMsg);

	return 0;

}

