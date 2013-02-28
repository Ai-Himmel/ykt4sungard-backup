/* --------------------------------------------
 * 程序名称: F847122.c
 * 创建日期: 2005-07-28
 * 程序作者: 闻剑
 * 版本信息:
 * 程序功能:新生换卡保存卡信息
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

int F847122(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int cardno=0;
	T_t_card tCard;
	T_t_aif_account  tAccount;

	memset(&tCard,0,sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));

	cardno=rPack->lvol0;
	if(cardno<1)
	{
		*pRetCode=E_INPUT_CARDNO;
		goto L_RETU;
	}
	if(rPack->lvol10<1)
	{
		*pRetCode=E_INPUT_CARD_TXCNT;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt0,0)<0)
	{
		*pRetCode=E_INPUT_CARD_BALA;
		goto L_RETU;
	}
	//判断卡状态是否为写卡未成功状态
	ret=DB_t_card_read_lock_by_c0_and_cardno(cardno, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(cardno!=tCard.cardno)
	{
		writelog(LOG_ERR,"cardno[%d] db cardno[%d]",cardno,tCard.cardno);
		DB_t_card_free_lock_by_c0();
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.cardattr,CARDSTAT_REG,4)!=0)
	{
		DB_t_card_free_lock_by_c0();

		if('2'==tCard.cardattr[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARD_CLOSE;
		else if('3'==tCard.cardattr[CARDSTAT_TYPE_REG])
			return 0;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_LOST])
			*pRetCode=E_CARD_LOST;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_FREEZE])
			*pRetCode=E_CARD_FREEZE;
		else if(STATE_TRUE==tCard.cardattr[CARDSTAT_TYPE_WFAIL])
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	trim(rPack->sbank_acc);
	if(strcmp(tCard.cardphyid,rPack->sbank_acc)!=0)
	{
		DB_t_card_free_lock_by_c0();
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,rPack->sbank_acc);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	tCard.cardattr[CARDSTAT_TYPE_REG]='3';
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_card_free_lock_by_c0();
	//注销帐户
	ret=DB_t_aif_account_read_lock_by_cur4_and_cardno_and_purseno(cardno,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_lock_by_cur4_and_cardno_and_purseno ret[%d]cardno[%d]",ret,cardno);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	tAccount.consume_count=rPack->lvol10;
	tAccount.card_balance=rPack->damt0;
	ret=DB_t_aif_account_update_lock_by_cur4(&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur4 ret[%d]account_id[%s]",ret,tAccount.account_id);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_cur4();
	return 0;
L_RETU:
	return -1;
}
