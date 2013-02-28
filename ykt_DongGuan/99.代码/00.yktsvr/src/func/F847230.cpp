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
#include "busqc.h"
#include "acctrans.h"

int F847230(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_AUTHCARDUNLOSS;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);

		
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_SSERIAL0,0);

	trans.cardno= rPack->lvol0;
	if(trans.cardno<= 0)
	{
		return  E_INPUT_CARDNO;
	}	
	if(strlen(rPack->scust_limit) == 0)
	{
		return  E_INPUT_OPER_NULL;
	}
	T_t_authcard tAuthCard;
	memset(&tAuthCard,0,sizeof(tAuthCard));
	ret = DB_t_authcard_read_by_cardno(trans.cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return  E_NOTEXIST_AUTHCARD;
		else
			return  E_DB_AUTHCARD_R;
	}

	if(tAuthCard.status[0]==STATUS_DELETE)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.cardno);
		return  E_AUTHCARD_LOGOUT;
	}
	if(tAuthCard.lossflag[0]=='0')
	{
		return E_AUTHCARD_NOLOST;
	}
	
	T_t_operator tOper;
	memset(&tOper,0,sizeof tOper);
	ret = DB_t_operator_read_by_opercode(tAuthCard.opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"operator does not exists, oper [%s]",tAuthCard.opercode);
			return  E_DB_OPERATOR_N;
		}
		else
			return  E_DB_OPERATOR_R;
	}
	sprintf(trans.remark,"操作员[%s]授权卡卡号[%d]解挂",tAuthCard.opercode,tAuthCard.cardno);
	if(tOper.status[0]==STATUS_DELETE)
	{
		writelog(LOG_ERR,"operator [%s] has been logout ",tAuthCard.opercode);
		return  E_OPERLOGON_UNREG;
	}

	ret=chk_oper_pwd(tAuthCard.opercode,rPack->semp_pwd);
	if(ret)
	{
		writelog(LOG_ERR,"operator password error, operator [%s]",tAuthCard.opercode);
		if(E_NOTEXIST_OPER==ret)
			return E_NOTEXIST_AUTHOPER;
		else if(E_OPERPWD==ret)
			return E_AUTH_OPER_PWD;
		else
			return ret;
	}
	tAuthCard.lossflag[0]='0';
	strcpy(tAuthCard.lossdate,"");
	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.cardno);
		return  E_DB_AUTHCARD_U;
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
	cardver.cardvertype=CARDVERTYPE_CARDUNLOSS;
	cardver.adddelflag=ADDDELFLAG_DEL;
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
	outPack->lvol0=tAuthCard.cardno;
	des2src(outPack->sserial0,cardver.cardverno);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

