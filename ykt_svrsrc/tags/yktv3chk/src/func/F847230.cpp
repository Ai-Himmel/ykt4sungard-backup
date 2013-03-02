/* --------------------------------------------
 * 程序名称: F847230
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡解挂
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
#include "busqc.h"
#include "acctrans.h"

int F847230(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char sysdate[9] = "";
	char systime[7] = "";
	char db_date[9] = "";
	char db_time[7] = "";
	char volume[13] = "";
	int auth_cardno = 0;
	T_t_authcard tAuthCard;
	T_t_operator tOper;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	double uni_no = 0.0;

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_AUTHCARDUNLOSS;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;

	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	auth_cardno = rPack->lvol0;
	if(auth_cardno <= 0)
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;
	}	
	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	ret = DB_t_authcard_read_by_cardno(auth_cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_AUTHCARD_NOT_EXISTS;
		else
			*pRetCode = E_DB_OPER_AUTHCARD_R;
		goto L_RETU;
	}

	if(tAuthCard.status[0]==STATUS_LOGOUT)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.cardno);
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}
	
	memset(&tOper,0,sizeof tOper);
	ret = DB_t_operator_read_by_opercode(tAuthCard.opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"operator does not exists, oper [%s]",tAuthCard.opercode);
			*pRetCode = E_DB_OPERATOR_N;
		}
		else
			*pRetCode = E_DB_OPERATOR_R;
		goto L_RETU;
	}
	if(tOper.status[0]==STATUS_LOGOUT)
	{
		writelog(LOG_ERR,"operator [%s] has been logout ",tAuthCard.opercode);
		*pRetCode = E_OPERLOGON_UNREG;
		goto L_RETU;
	}

	ret=chk_oper_pwd(tAuthCard.opercode,rPack->semp_pwd);
	if(ret)
	{
		writelog(LOG_ERR,"operator password error, operator [%s]",tAuthCard.opercode);
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_AUTH_OPER_NOT_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_AUTH_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	tAuthCard.cardstatus[CARDSTAT_TYPE_LOST]='0';
	strcpy(tAuthCard.lossdate,"");
	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.cardno);
		*pRetCode = E_DB_OPER_AUTHCARD_U;
		goto L_RETU;
	}
	// 插入黑名单表
	ret = InsertToBlkList(auth_cardno,DELETE_BLACKLIST);
	if(ret)
	{
		writelog(LOG_ERR,"insert into black list error, card id[%d]",auth_cardno);
		*pRetCode = ret;
		goto L_RETU;
	}
	
	// 生成流水
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_SSERIAL0,0);
	get_datetime_from_db(db_date,db_time);
	out_pack->lvol0 = auth_cardno;
	memcpy(volume,db_date+2,6);
	memcpy(volume+6,db_time,6);
	des2src(out_pack->sserial0,volume);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;		
}

