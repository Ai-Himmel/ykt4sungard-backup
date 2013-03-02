/* --------------------------------------------
 * 程序名称: F847175.sqc
 * 创建日期: 2008-09-03
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 查询,交押金,冲正,退押金
 * --------------------------------------------
 * 修改日期: 
 * 修改人员: 
 * 修改描述: 
 * 版本信息: 
 * 备注信息: 
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
#include "fdsqc.h"
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
	if(strlen(p->oper_code))
		strcpy(IA->sMdeOper,p->oper_code);			//操作员
	else
		strcpy(IA->sMdeOper,"system");
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

static int check_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//查询押金
{
	int ret = 0;
	T_t_pif_card tCard;
	T_t_cif_customer tCustomer;
	T_t_tif_libdeposit tLibdeposit;

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tLibdeposit,0,sizeof(tLibdeposit));

	int card_id = rPack->lvol0;		//卡号
	writelog(LOG_DEBUG,"卡号[%d]*******************",card_id);
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			return E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			return E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			return E_CARDNO_WFAIL;
	}
	
		
	if(tCard.type_id == CT_NORMAL)			//正式卡,防止发错卡,继续判断
		ret = -1;
	
	ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		if(ret ==DB_NOTFOUND)
			return E_DB_CUSTOMER_N;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state != CUSTSTAT_REGIST)		//客户已经注销
		return E_CUSTOMER_LOGOUT;
	
	writelog(LOG_DEBUG,"客户号[%d]*******************",tCustomer.cut_id);
	if(tCustomer.cut_type != 20 && tCustomer.cut_type != 26)				///////////////修改为培训学员
		ret = -1;
	else
	{
		ret = DB_t_tif_libdeposit_read_by_customer_id(tCustomer.cut_id, &tLibdeposit);
		if(ret)
		{
			if(ret == DB_NOTFOUND)			//未找到,需交押金
				ret = 1;			
			else
				return E_DB_LIBDEPOSIT_R;
		}
		else
		{
			if(tLibdeposit.fee_flag[0] !='1')	// 未交押金
				ret = 1;
			else 
				ret = 0;		
		}
	}

	writelog(LOG_DEBUG,"ret [%d]*******************",ret);
	if(ret == -1)		//非培训学员
		out_pack->lvol0 = -1;
	
	else if(ret == 0)		//培训学员,已交过押金
		out_pack->lvol0  = 0;
	
	else if(ret == 1)				//培训学员,需交押金
		out_pack->lvol0 = 1;

	return 0;
}

static int handin_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//上交押金
{
	int ret = 0,depflag = 0;
	int card_id = 0;
	double deposit_fee = 0;
	char deposit_para[20] = "";
	char logicdate[9] = "";
	char sysdate[9] ="";
	char systime[7] = "";
	double dSerialNo = 0;
	InAcc	IA;
	
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = check_deposit(rPack,out_pack);
	if(ret)
		return ret;
	
	writelog(LOG_DEBUG,"ret [%d]*******************",ret);

	depflag = out_pack->lvol0;
//	if(depflag != 1)			//不需要交押金,直接返回
//		return 1;
	if(depflag == -1)
		return -1;			//不需要交押金
	if(depflag == 0)
		return 1;			//已经交过押金

	ret = GetParameter(GLOBAL_LIB_DEPOSIT, deposit_para);
	if(ret)
		return ret;
	deposit_fee = atof(deposit_para);
	writelog(LOG_DEBUG,"deposit_fee [%f]*******************",deposit_fee);

//	rPack->damt1 = rPack->lvol8/100;		//分转换为元
	if(amtcmp(rPack->damt1,deposit_fee) < 0)		//卡片上金额小于押金金额
		return E_AMT_LACK;
	
	card_id = rPack->lvol0;		//卡号
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	if(tAccount.act_type != ACCOUNTSTAT_REGIST)
		return E_ACTNO_LOGOUT;
	if(amtcmp(tAccount.cur_freebala,deposit_fee) < 0)
		return E_BALANCE_SHORTAGE;
	
	writelog(LOG_DEBUG,"name [%s]*******************",tAccount.cut_name);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
		return ret;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	
	tradeserial.trade_fee = deposit_fee;		//交易金额
	tradeserial.serial_type = TXCODE_LIBDEPOSIT_HANDIN;
	tradeserial.in_balance=rPack->damt1;		//卡片上金额
	tradeserial.trade_count=rPack->lvol10+1;		//交易次数
	tradeserial.serial_no = D2I(dSerialNo);											//流水号
	tradeserial.other_seri_no = 0;															//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code, "system");
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//外部系统标识
	tradeserial.card_id = card_id;
	
	des2src(IA.sArrInActno[0],tAccount.account_id);						//商户帐户
	IA.iCardNo=tAccount.card_id;
	writelog(LOG_DEBUG,"acc_id [%s]*******************",IA.sArrInActno[0]);
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	sprintf(out_pack->vsmess,"扣押金前可用余额:%.2lf元,当前可用余额:%.2lf元",tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
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
	
	tLibdeposit.customer_id = tAccount.customer_id;
	tLibdeposit.deposit_fee = deposit_fee;
	tLibdeposit.fee_flag[0] = '1';
	des2src(tLibdeposit.cut_name,tAccount.cut_name);
	des2src(tLibdeposit.oper_date,logicdate);
	des2src(tLibdeposit.oper_time,systime);	
	ret = DB_t_tif_libdeposit_add(&tLibdeposit);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id,&tLibdeposit);
			if(ret)
				return E_DB_LIBDEPOSIT_U;
		}
		else
			return E_DB_LIBDEPOSIT_I;
	}
	out_pack->damt1 = deposit_fee;		//交易金额
	out_pack->damt2 = tradeserial.out_balance;		//出卡值
	out_pack->lvol4 = D2I(deposit_fee*100);
	out_pack->lvol5 = D2I(tradeserial.out_balance*100);
	out_pack->lserial0 = tradeserial.serial_no;	//流水号
	return 0;
}

static int do_enteract(T_t_tif_tradeserial *reverse_serial,T_t_tif_tradeserial *tradeserial,InAcc *IA)
{
	int ret;
	double new_serial;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&new_serial);
	if(ret)
	{
		writelog(LOG_ERR,"生成交易流水号错误");

		return ret;
	}
	tradeserial->serial_no = D2I(new_serial);
	tradeserial->serial_state = SERISTAT_DEBT;
	tradeserial->in_balance = reverse_serial->out_balance;
	tradeserial->out_balance = reverse_serial->in_balance;
	tradeserial->trade_fee = -reverse_serial->trade_fee;
	getsysdate(tradeserial->operate_date);
	getsystime(tradeserial->operate_time);
	des2src(tradeserial->enteract_time,tradeserial->operate_time);

	// 交易金额
	IA->dArrInAmt[0] = tradeserial->trade_fee;
	// 冲正标志
	IA->iTxFlag = ACC_TYPE_RUSH;
	writelog(LOG_DEBUG,"冲正交易金额 [%f]*******************",IA->dArrInAmt[0]);
	ret = process(IA,tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process account ret[%d]",ret);
		return ret;
	}
	
	if(amtcmp(tradeserial->out_balance,0)<0)
		return E_ENTER_ACCOUNT;
	
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	// 记录水流水号
	reverse_serial->reviseserial_no = tradeserial->serial_no;
	
	return 0;
}

static int backoff(ST_PACK *rPack,ST_PACK *out_pack)				//写卡失败冲正
{
	int ret = 0;
	InAcc	IA;
	int serial_no = rPack->lserial0;		//流水号
	int card_id = rPack->lvol0;		//卡号
	
	T_t_tif_tradeserial  tradeserial,reverse_serial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&reverse_serial,0,sizeof(reverse_serial));

	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}

	des2src(IA.sArrInActno[0],tAccount.account_id);						
	IA.iCardNo=tAccount.card_id;
	writelog(LOG_DEBUG,"acc_id [%s]*******************",IA.sArrInActno[0]);

	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(serial_no, &reverse_serial);
	if(ret)
	{
		writelog(LOG_ERR,"read serial error,serialno[%d]",serial_no);
		// 无对应流水,就返回冲正成功
		if(DB_NOTFOUND == ret)
			return 0;
		return E_DB_TRADESERIAL_R;
	}

	if(reverse_serial.serial_state != SERISTAT_DEBT)
	{
		writelog(LOG_ERR,"交易流水已被冲正,不能再次冲正,serial[%d]logicdate[%s]",
				 reverse_serial.serial_no,reverse_serial.enteract_date);
		ret = 0;
	}
	else
	{
		memcpy(&tradeserial,&reverse_serial,sizeof(tradeserial));
		ret = do_enteract(&reverse_serial,&tradeserial,&IA);
		if(!ret)
		{
			// 流水状态标志成 已冲正
			reverse_serial.serial_state = SERISTAT_RUSH;
			ret = DB_t_tif_tradeserial_update_lock_by_cur(&reverse_serial);
			if(ret)
			{
				writelog(LOG_ERR,"更新被冲正流水失败,ret[%d]",ret);
				ret = E_DB_TRADESERIAL_U;
			}
		}		
	}
	DB_t_tif_tradeserial_free_lock_cur();
	if(ret)
		return ret;
	
	ret = DB_t_tif_libdeposit_read_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_LIBDEPOSIT_N;
		return E_DB_LIBDEPOSIT_R;
	}
	if(tLibdeposit.fee_flag[0] == '0')
		tLibdeposit.fee_flag[0] = '1';
	else
		tLibdeposit.fee_flag[0] = '0';
	ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_U;
	out_pack->damt2 = tradeserial.out_balance;		//出卡值
	out_pack->lserial0 = tradeserial.serial_no;	//流水号
	return 0;
}

static int handback_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//退还押金
{
	int ret = 0,depflag = 0;
	int card_id = 0;
	double deposit_fee = 0;
	char logicdate[9] = "";
	char sysdate[9] ="";
	char systime[7] = "";
	double dSerialNo = 0;
	InAcc	IA;
	
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = check_deposit(rPack,out_pack);
	if(ret)
		return ret;
	
	depflag = out_pack->lvol0;
//	if(depflag != 0)			//不需要退押金,直接返回
//		return 1;
	if(depflag == -1)
		return -1;			//不需要退押金
	if(depflag == 1)
		return 1;			//未交过押金
	
	card_id = rPack->lvol0;		//卡号
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	if(tAccount.act_type != ACCOUNTSTAT_REGIST)
		return E_ACTNO_LOGOUT;
	if(amtcmp(tAccount.cur_freebala,deposit_fee) < 0)
		return E_BALANCE_SHORTAGE;

	ret = DB_t_tif_libdeposit_read_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_R;
	deposit_fee = tLibdeposit.deposit_fee;
	
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
		return ret;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
//	rPack->damt1 = rPack->lvol8/100;	
	tradeserial.trade_fee = deposit_fee;		//交易金额
	tradeserial.serial_type = TXCODE_LIBDEPOSIT_HANDOFF;
	tradeserial.in_balance=rPack->damt1;		//卡片上金额
	tradeserial.trade_count=rPack->lvol10+1;		//交易次数
	tradeserial.serial_no = D2I(dSerialNo);											//流水号
	tradeserial.other_seri_no = 0;															//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code, "system");
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//外部系统标识
	tradeserial.card_id = card_id;
	
	des2src(IA.sArrInActno[0],tAccount.account_id);						//商户帐户
	IA.iCardNo=tAccount.card_id;

	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	sprintf(out_pack->vsmess,"退押金前可用余额:%.2lf元,当前可用余额:%.2lf元",tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
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
	
	
	tLibdeposit.fee_flag[0] = '0';	
	ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id,&tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_U;
		
	out_pack->damt1 = deposit_fee;		//交易金额
	out_pack->damt2 = tradeserial.out_balance;		//出卡值
	out_pack->lvol4 = D2I(deposit_fee*100);
	out_pack->lvol5 = D2I(tradeserial.out_balance*100);
	out_pack->lserial0 = tradeserial.serial_no;	//流水号
	return 0;
}

int F847175(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	int transcode = rPack->lvol3;		//交易码
	rPack->damt1=D4U5(rPack->lvol8/100.0, 2);		// 入卡值，前端传入分
	switch(transcode)
	{
		case 10:						
			ret = check_deposit(rPack,out_pack);
			break;
		case 11:
			ret = handin_deposit(rPack,out_pack);
			break;
		case 12:
			ret = backoff(rPack,out_pack);
			break;
		case 13:
			ret = handback_deposit(rPack,out_pack);
			break;
		default :
			ret =-1;
	}

	if(ret)
		return ret;
	
	SetCol(handle,0);
 	SetCol(handle,F_LVOL0,F_LVOL4,F_LVOL5,F_DAMT1,F_DAMT2,F_LSERIAL0,F_VSMESS,0);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
}
