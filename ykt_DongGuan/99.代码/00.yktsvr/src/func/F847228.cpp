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
#include "busqc.h"
#include "acctrans.h"

int F847228(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_AUTHCARDUPD;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;
	int auth_cardno = 0;
	T_t_authcard tAuthCard;
	T_t_operator tOper;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	double uni_no = 0.0;
	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	auth_cardno = rPack->lvol0;
	if(auth_cardno <= 0)
	{
		return E_INPUT_CARDNO;
	}
	if(strlen(rPack->scust_limit) == 0)
	{
		return E_INPUT_OPER_NULL;
	}

	if(IsInvalidDateTime(rPack->sdate0,"YYYYMMDD"))
	{
		return E_INPUT_DATE;
	}
	
	ret = DB_t_authcard_read_by_cardno(auth_cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_AUTHCARD;
		else
			return E_DB_AUTHCARD_R;
	}

	if(tAuthCard.status[0] == STATUS_DELETE)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.cardno);
		return E_AUTHCARD_LOGOUT;
	}
	if(tAuthCard.lossflag[0]== '1')
	{
		writelog(LOG_ERR,"auth card is loss , card id [%d]",tAuthCard.cardno);
		return E_AUTHCARD_IS_LOSS;
	}

	memset(&tOper,0,sizeof tOper);
	ret = DB_t_operator_read_by_opercode(tAuthCard.opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"operator does not exists, oper [%s]",tAuthCard.opercode);
			return E_DB_OPERATOR_N;
		}
		else
			return E_DB_OPERATOR_R;
	}
	if(tOper.status[0]==STATUS_DELETE)
	{
		writelog(LOG_ERR,"operator [%s] has been logout ",tAuthCard.opercode);
		return E_OPERLOGON_UNREG;
	}
	des2src(tAuthCard.expiredate,rPack->sdate0);
	tAuthCard.privilege = rPack->lvol1;

	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.cardno);
		return E_DB_AUTHCARD_U;
	}
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SDATE0,F_SCUST_LIMIT,0);
	out_pack->lvol0 = tAuthCard.cardno;
	des2src(out_pack->sdate0,tAuthCard.expiredate);
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->scust_limit,tAuthCard.opercode);
	sprintf(trans.remark,"操作员[%s]授权卡卡号[%d]更新",tAuthCard.opercode,tAuthCard.cardno);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
