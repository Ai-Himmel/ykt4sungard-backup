/* --------------------------------------------
 * 程序名称: F847227
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡回收
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

int F847227(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char sysdate[9] = "";
	char systime[7] = "";
	char auth_card_phyid[9] = "";
	int auth_card_id = 0;
	T_t_pif_oper_authcard tAuthCard;
	T_t_tif_tradeserial tSerial;
	double uni_no = 0.0;

	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&tSerial,0,sizeof tSerial);

	auth_card_id = rPack->lvol0;
	if(auth_card_id <= 0)
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;
	}

	des2src(auth_card_phyid,rPack->sdate0);
	
	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
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
		writelog(LOG_ERR,"授权卡已经回收，不能重复卡号[%d]",auth_card_id);
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}

	if(strcmp(tAuthCard.card_phyid,auth_card_phyid))
	{
		writelog(LOG_ERR,"card id / phyid diff , card id[%d] db phyid[%s] input phyid[%s]"
			,auth_card_id,tAuthCard.card_phyid,auth_card_phyid);
		*pRetCode = E_INPUT_CARDPHYID;
		goto L_RETU;
	}

	tAuthCard.status = AUTHCARD_STATUS_CANCEL;
	ret = DB_t_pif_oper_authcard_update_by_card_id(tAuthCard.card_id,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update auth card status error , card id[%d]", auth_card_id);
		*pRetCode = E_DB_OPER_AUTHCARD_U;
		goto L_RETU;
	}

	// 插入黑名单表
	ret = InsertToBlkList(auth_card_id,ADD_BLACKLIST);
	if(ret)
	{
		writelog(LOG_ERR,"insert into black list error, card id[%d]",auth_card_id);
		*pRetCode = ret;
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
	tSerial.serial_type = TXCODE_CANCEL_AUTHCARD;
	des2src(tSerial.operate_date,sysdate);
	des2src(tSerial.operate_time,systime);
	des2src(tSerial.enteract_date,sysdate);
	des2src(tSerial.enteract_time,systime);
	des2src(tSerial.collect_date,sysdate);
	des2src(tSerial.collect_time,systime);
	des2src(tSerial.oper_code,rPack->scust_limit);
	if(rPack->lvol1)
	{
		strcpy(tSerial.reserve_1,"无卡回收");
	}
	
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
	writelog(LOG_DEBUG,"回收授权卡成功，操作员[%s]交易卡号[%d]流水号[%d]"
		,tAuthCard.oper_code,tAuthCard.card_id,tSerial.serial_no);

	return 0;
L_RETU:
	return -1;		
}

