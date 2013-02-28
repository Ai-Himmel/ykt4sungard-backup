/* --------------------------------------------
 * 程序名称: F847229
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡挂失
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

int F847229(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_AUTHCARDLOSS;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;
	int auth_cardno = 0;
	T_t_authcard tAuthCard;

	memset(&tAuthCard,0,sizeof tAuthCard);

	auth_cardno = rPack->lvol0;
	if(auth_cardno <= 0)
	{
		return E_INPUT_CARDNO;
	}

	
	if(strlen(rPack->scust_limit) == 0)
	{
		return E_INPUT_OPER_NULL;
	}
	
	ret = DB_t_authcard_read_by_cardno(auth_cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_AUTHCARD;
		else
			return E_DB_AUTHCARD_R;
	}
	sprintf(trans.remark,"操作员[%s]授权卡卡号[%d]挂失",tAuthCard.opercode,tAuthCard.cardno);

	if(tAuthCard.status[0]==STATUS_DELETE)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.cardno);
		return E_AUTHCARD_LOGOUT;
	}
	if(tAuthCard.lossflag[0]=='1')
	{
		return E_AUTHCARD_IS_LOSS;
	}
	T_t_operator tOper;
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

	tAuthCard.lossflag[0]='1';
	getsysdate(tAuthCard.lossdate);
	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.cardno);
		return E_DB_AUTHCARD_U;
	}
	// 插入黑名单表
	T_t_cardver cardver;
	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tAuthCard.cardno;
	des2src(cardver.accdate,ats.trans.accdate);
	cardver.termid=ats.trans.termid;
	cardver.termseqno=ats.trans.termseqno;
	cardver.cardno=tAuthCard.cardno;
	des2src(cardver.cardphyid,tAuthCard.cardphyid);
	cardver.cardvertype=CARDVERTYPE_CARDLOSS;
    cardver.adddelflag=ADDDELFLAG_ADD;
	cardver.status[0]=STATUS_NORMAL;
	
	ret=getCardVerNo(cardver.cardverno);
	if(ret)
		return ret;
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	return 0;
}

