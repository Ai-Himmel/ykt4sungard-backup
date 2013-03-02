/* --------------------------------------------
 * 程序名称: F847123.c
 * 创建日期: 2005-07-28
 * 程序作者: 闻剑
 * 版本信息:
 * 程序功能: 新生换卡
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
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

int F847123(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_id=0;
	char sSeedKey[17] = "";							//种子密钥
	char sPwd[7] = "";							//卡密码
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double dSerialno=0;
	T_t_pif_card tCard;
	T_t_cif_customer tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account  tAccount;
	T_t_tif_tradeserial tTradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tTradeserial,0,sizeof(tTradeserial));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL10,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,0);

	card_id=rPack->lvol0;
	if(card_id<1)
	{
		*pRetCode=E_INPUT_CARDNO;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//判断卡状态是否为写卡未成功状态
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(card_id!=tCard.card_id)
	{
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if('3'!=tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARDNO_LOGOUT;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_LOST])
			*pRetCode=E_CARDNO_LOST;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
			*pRetCode=E_CARDNO_FREEZE;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_WFAIL])
			*pRetCode=E_CARDNO_WFAIL;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode=E_OLDCARDINFO_NOSAVE;
		goto L_RETU;
	}
	trim(rPack->sbank_acc);
	trim(rPack->scust_no);
	trim(rPack->sdate0);
	if(strlen(rPack->scust_no))
	{
		ret=IsExistShowCardNo(rPack->scust_no);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	if(strcmp(tCard.physical_no,rPack->sbank_acc)!=0)
	{
		ret=IsExistCardByPhyCardNo(rPack->sbank_acc);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=ret;
		goto L_RETU;
	}

	// add by tc
	// 在这里我们要记录旧卡的物理卡号
	ret = InsertToCutUpdList(tCard.card_id,CUTUPD_CH_OLDCARD,tCard.physical_no);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = ret;
		goto L_RETU;
	}
	des2src(tCard.physical_no, rPack->sbank_acc);		//物理卡号
	des2src(tCard.showid,rPack->scust_no);				//显示卡号
	des2src(tCard.end_time,rPack->sdate0);				//到期日期

	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	// add by tc 
	// 在这里记录新卡的物理卡号
	ret = InsertToCutUpdList(tCard.card_id,CUTUPD_CH_NEWCARD,tCard.physical_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	memcpy(sSeedKey,STATIC_SEED_KEY,16);			//读种子密钥
	EncodePwd(sSeedKey,sPwd,tCard.password,1);		//卡密码

	//注销帐户
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_ACTNO_NOT_EXIST;
		else
			*pRetCode= E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	if(tAccount.consume_count<1)
	{
		*pRetCode=E_CARD_TXCNT;
		goto L_RETU;
	}
	if(amtcmp(tAccount.card_balance,0)<0)
	{
		*pRetCode=E_CARD_BALA;
		goto L_RETU;
	}
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//得到收费类别
	if(tCustomer.fee_type<1)
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
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
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
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//获得流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no = D2I(dSerialno);					//流水号
	tTradeserial.other_seri_no = 0;							//上传端流水号
	tTradeserial.serial_type = 847123;						//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
	tTradeserial.serial_state = SERISTAT_DEBT;				//流水状态
	des2src(tTradeserial.operate_date,sysdate);				//发生日期
	des2src(tTradeserial.operate_time,systime);				//发生时间
	des2src(tTradeserial.collect_date,sysdate);				//采集日期
	des2src(tTradeserial.collect_time,systime);				//采集时间
	des2src(tTradeserial.enteract_date,logicdate);				//处理日期
	des2src(tTradeserial.enteract_time,systime);				//处理时间
	des2src(tTradeserial.oper_code , rPack->scust_limit);
	tTradeserial.maindevice_id = rPack->lvol6;				//上传工作站标识
	tTradeserial.device_id = rPack->lvol7;					//采集设备标识
	tTradeserial.card_id = tCard.card_id;						//卡号
	des2src(tTradeserial.showid,tCard.showid);				//显示卡号
	tTradeserial.purse_id = PURSE_NO_ONE;					//钱包号
	tTradeserial.customer_id = tCard.cosumer_id;				//客户标识

	//插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	out_pack->lvol0 = card_id;									//交易卡号
	out_pack->lvol1 = tCustomer.cut_type;						//客户类别
	out_pack->lvol5 = tCustomer.fee_type;						//收费类别
	des2src(out_pack->scust_no,tCard.showid);					//显示卡号
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//部门号
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//学号
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//身份证号
	des2src(out_pack->sname,tCustomer.cut_name);				//客户姓名
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//图书证号
	des2src(out_pack->sstatus0,tCustomer.sex);					//性别
	des2src(out_pack->sopen_emp,sPwd);						//卡密码
	des2src(out_pack->sdate0,tCard.end_time);					//有效截至日期

	out_pack->damt2=D4U5(tAccount.card_balance,2);			//卡余额
	out_pack->lvol10=tAccount.consume_count;					//消费次数
	out_pack->lserial1=tTradeserial.serial_no;						//流水号

	sprintf(out_pack->vsmess,"流水号:%d 卡号:%d 学工号:%s 姓名:%s 卡余额:%.2lf元",tTradeserial.serial_no,card_id,tCustomer.stuemp_no,tCustomer.cut_name,tAccount.card_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
	// add by 汤成 2005-8-8
	// 增加向名单表写入记录
	/*
	ret = InsertToBlkList(card_id,CHCARD_BLACKLIST);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	*/
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
