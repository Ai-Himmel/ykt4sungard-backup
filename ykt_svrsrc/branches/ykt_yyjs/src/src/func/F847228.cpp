/* --------------------------------------------
 * 程序名称: F847228
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡更新
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

int F847228(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char sysdate[9] = "";
	char systime[7] = "";
	int auth_card_id = 0;
	T_t_pif_oper_authcard tAuthCard;
	T_t_tif_tradeserial tSerial;
	T_t_pif_operator tOper;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	double uni_no = 0.0;


	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&tSerial,0,sizeof tSerial);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	auth_card_id = rPack->lvol0;
	if(auth_card_id <= 0)
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;
	}

	
	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	if(IsInvalidDateTime(rPack->sdate0,"YYYYMMDD"))
	{
		*pRetCode = E_INPUT_DATE;
		goto L_RETU;
	}
	
	ret = DB_t_pif_oper_authcard_read_by_card_id(auth_card_id,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_AUTHCARD_NOT_EXISTS;
		else
			*pRetCode = E_DB_OPER_AUTHCARD_R;
		goto L_RETU;
	}

	if(tAuthCard.status == AUTHCARD_STATUS_CANCEL)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.card_id);
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}
	else if(tAuthCard.status == AUTHCARD_STATUS_LOSS)
	{
		writelog(LOG_ERR,"auth card is loss , card id [%d]",tAuthCard.card_id);
		*pRetCode = E_AUTHCARD_IS_LOSS;
		goto L_RETU;
	}

	memset(&tOper,0,sizeof tOper);
	ret = DB_t_pif_operator_read_by_oper_code(tAuthCard.oper_code,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"operator does not exists, oper [%s]",tAuthCard.oper_code);
			*pRetCode = E_DB_OPERATOR_N;
		}
		else
			*pRetCode = E_DB_OPERATOR_R;
		goto L_RETU;
	}
	if(strcmp(tOper.status,OPERATOR_LOGOUT) == 0)
	{
		writelog(LOG_ERR,"operator [%s] has been logout ",tAuthCard.oper_code);
		*pRetCode = E_OPERLOGON_UNREG;
		goto L_RETU;
	}
	des2src(tAuthCard.expired_date,rPack->sdate0);
	tAuthCard.privilege = rPack->lvol1;

	ret = DB_t_pif_oper_authcard_update_by_card_id(tAuthCard.card_id,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.card_id);
		*pRetCode = E_DB_OPER_AUTHCARD_U;
		goto L_RETU;
	}
	
	// 生成流水
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&uni_no);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tSerial.serial_no = D2I(uni_no);

	getsysdate(sysdate);
	getsystime(systime);

	tSerial.card_id = tAuthCard.card_id;
	tSerial.serial_state = SERISTAT_NONEEDDEBT;
	tSerial.serial_type = TXCODE_MODIFY_AUTHCARD;
	des2src(tSerial.operate_date,sysdate);
	des2src(tSerial.operate_time,systime);
	des2src(tSerial.enteract_date,sysdate);
	des2src(tSerial.enteract_time,systime);
	des2src(tSerial.collect_date,sysdate);
	des2src(tSerial.collect_time,systime);
	des2src(tSerial.oper_code,rPack->scust_limit);
	
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			writelog(LOG_ERR,"记录流水表失败!");
			*pRetCode = E_DB_TRADESERIAL_E;
		}
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"更新授权卡成功，操作员[%s]交易卡号[%d]流水号[%d]"
		,tAuthCard.oper_code,tAuthCard.card_id,tSerial.serial_no);

	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SDATE0,F_SCUST_LIMIT,0);
	out_pack->lvol0 = tAuthCard.card_id;
	des2src(out_pack->sdate0,tAuthCard.expired_date);
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->scust_limit,tAuthCard.oper_code);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;		
}
