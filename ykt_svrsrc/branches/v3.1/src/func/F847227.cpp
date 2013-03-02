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
#include "busqc.h"
#include "acctrans.h"

int F847227(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_AUTHCARDCLOSE;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	T_t_authcard tAuthCard;

	memset(&tAuthCard,0,sizeof tAuthCard);

	trans.cardno = rPack->lvol0;
	if(trans.cardno <= 0)
	{
		return E_INPUT_CARDNO;
	}
	des2src(trans.cardphyid,rPack->sdate0);
	if(strlen(rPack->scust_limit) == 0)
	{
		return E_INPUT_OPER_NULL;
	}
	ret = DB_t_authcard_read_by_cardno(trans.cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_AUTHCARD;
		else
			return E_DB_AUTHCARD_R;
	}
	
	if(tAuthCard.status[0] == STATUS_DELETE)
	{
		writelog(LOG_ERR,"授权卡已经回收，不能重复卡号[%d]",trans.cardno);
		return E_AUTHCARD_LOGOUT;
	}

	if(strcmp(tAuthCard.cardphyid,trans.cardphyid))
	{
		writelog(LOG_ERR,"card id / phyid diff , card id[%d] db phyid[%s] input phyid[%s]"
			,tAuthCard.cardno,tAuthCard.cardphyid,trans.cardphyid);
		return E_INPUT_CARDPHYID;
	}
	tAuthCard.status[0] = STATUS_DELETE;
	getsysdate(tAuthCard.closedate);
	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update auth card status error , cardno[%d]", trans.cardno);
		return E_DB_AUTHCARD_U;
	}
	T_t_operator tOper;

	memset(&tOper,0,sizeof(tOper));
	ret = DB_t_operator_read_lock_by_c0_and_opercode(tAuthCard.opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_OPER;
		else
			return E_DB_OPERATOR_R;
	}
	tOper.cardno=0;
	ret=DB_t_operator_update_lock_by_c0(&tOper);
	if(ret)
	{
		return E_DB_OPERATOR_U;
	}
	/*
	int cardtype=0;
	ret=UseShowCardNoBack(trans.opercode,tAuthCard.showcardno);
	if(ret)
	{
		return ret;
	}
	if(cardtype!=CARDTYPE_AUTH)
	{	
		return E_CARDTYPE_NOT_AUTHCARD;
	}
	T_t_carddtl carddtl;
	memset(&carddtl,0,sizeof(carddtl));
	
	des2src(carddtl.accdate,pAccTrans->sysPara.sSettleDate);
	des2src(carddtl.acctime,trans.acctime);
	carddtl.termid=trans.termid;
	carddtl.termseqno=trans.termseqno;
	des2src(carddtl.opercode,trans.opercode);
	carddtl.cardtype=CARDTYPE_AUTH;
	carddtl.usetype=CARDUSETYPE_REUSE;
	carddtl.inoutflag=INOUTFLAG_IN;
	carddtl.transcnt=1;
	strcpy(carddtl.summary,"回收授权卡");	
	des2src(carddtl.cardphyid,tAuthCard.cardphyid);
	des2src(carddtl.showcardno,tAuthCard.showcardno);
	ret=DB_t_carddtl_add(&carddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.revflag[0]='0';
	transdtl.errcode=0;
	transdtl.custid=trans.custid;
	strcpy(transdtl.custname,trans.custname);
	strcpy(transdtl.transdate,trans.transdate);
	strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,pAccTrans->sysPara.sSettleDate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	des2src(transdtl.opercode,trans.opercode);
	transdtl.cardno=trans.cardno;
	des2src(transdtl.custname,tOper.opername);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	*/
	return 0;
}

