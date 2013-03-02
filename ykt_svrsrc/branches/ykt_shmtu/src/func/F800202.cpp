/* --------------------------------------------
 * 程序名称: F847128.c
 * 创建日期: 2009-6-17
 * 程序作者: 
 * 版本信息: 1.0.0.0
 * 程序功能: 考试报名补缴费
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"


/*
交易卡号		lvol0
交易日期		sdate0
交易日期		stime0
商户账户		sstation1
入卡值			damt0
交易金额		damt1
交易次数		lvol1	
设备号			lvol3
*/

int F800202(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	//int i=0;
	int ret =0;
	int card_id= 0;
	char logicdate[11]="";										//业务日期
	char systime[9]="";
	char pre_time[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	double dUniqno = 0;
	char sMsg[256]="";
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_DAMT1,F_DAMT2,F_VSMESS,0);

	T_t_tif_tradeserial tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);
	
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	getsystime(systime);

	T_t_pif_card tCard;
	memset(&tCard,0,sizeof(tCard));

	card_id=rPack->lvol0;
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
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

	T_t_aif_account account;
	memset(&account,0,sizeof(account));
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,0,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read t_aif_account err[%d]cardid[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
		{
			return E_ACTNO_NOT_EXIST;
		}
		else
			return E_DB_ACCOUNT_R;
	}
	
	T_t_cif_customer tCustomer;
	memset(&tCustomer,0,sizeof tCustomer);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}

	T_t_pif_spefee tSpeFee;
	memset(&tSpeFee,0,sizeof tSpeFee);
	//得到收费类别
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
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}						
	tradeserial.serial_no = D2I(dUniqno);			//流水号
	
	tradeserial.serial_type = 847233;
	des2src(tradeserial.operate_date,rPack->sdate0);
	GetPreTime(rPack->stime0, 1, pre_time);
	des2src(tradeserial.operate_time,pre_time);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//采集日期
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//采集时间
	des2src(tradeserial.enteract_date,logicdate);							//处理日期
	des2src(tradeserial.enteract_time,systime);							//处理时间
	tradeserial.purse_id = PURSE_NO_ONE;					//钱包号
	tradeserial.serial_state = SERISTAT_DEBT;								//流水状态
	tradeserial.maindevice_id = 0;						//上传工作站标识
	tradeserial.device_id = rPack->lvol3;										//采集设备标识
	tradeserial.card_id = card_id;										//交易卡号
	tradeserial.customer_id=tCard.cosumer_id;								//客户号
	des2src(tradeserial.oper_code,"web");
	tradeserial.trade_count=rPack->lvol1;			//交易次数
	tradeserial.in_balance=rPack->damt0;			//入卡值
	tradeserial.trade_fee=rPack->damt1;				//交易金额
	tradeserial.out_balance=tradeserial.in_balance -tradeserial.trade_fee ;			//出卡值
	strcpy(tradeserial.reserve_2,"考试报名补缴费");

	des2src(IA.sArrInActno[0],account.account_id);			//借方账号(个人)
	des2src(IA.sArrInActno[1],rPack->sstation1);				//贷方账号
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	IA.iMainDevId=tradeserial.maindevice_id;				//工作站标识
	IA.iDevId=tradeserial.device_id;						//设备ID
	IA.iSerialNo=tradeserial.serial_no;					//流水号
	IA.iTradeNo=tradeserial.serial_type;					//交易码
	strcpy(IA.sTxDate,tradeserial.operate_date);			//交易日期
	strcpy(IA.sTxTime,tradeserial.operate_time);			//交易时间
	strcpy(IA.sTxCollectDate,tradeserial.collect_date);		//采集日期
	strcpy(IA.sTxCollectTime,tradeserial.collect_time);		//采集时间
	strcpy(IA.sTxAccDate,tradeserial.enteract_date);		//记账日期
	strcpy(IA.sTxAccTime,tradeserial.enteract_time);		//记账时间
	strcpy(IA.sMdeOper,tradeserial.oper_code);			//操作员

	IA.iUseCardFlag=USE_CARD_TYPE_OFFLINE;		//联机交易
	IA.iTxCnt=tradeserial.trade_count;					//交易次数
	IA.dInCardBala=tradeserial.in_balance;				//入卡值
	IA.dOutCardBala=-1;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	out_pack->damt0=tradeserial.out_balance;	//出卡值
	out_pack->damt1=tradeserial.trade_fee;		//交易金额	
	out_pack->damt2=tradeserial.in_balance;		//交易金额	
	out_pack->lvol0 = tradeserial.serial_no;		//流水号	
	sprintf(sMsg,"卡号:%d,交易金额:%.2f,交易前卡余额:%.2lf元, 卡当前余额:%.2lf元",card_id,tradeserial.trade_fee,tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}

	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

