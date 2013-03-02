/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通充值冲正
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
#include "busqc.h"
#include "acctrans.h"
static int doReverse(ST_PACK *rPack,char* oldaccdate,int oldtermid,int oldtermseqno)
{
	//查找操作员流水
	int ret=0;
	T_t_card tCard;
	
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.cardno=rPack->lvol0;
	
	T_t_cardtransdtl cardtransdtl;
	memset(&cardtransdtl,0,sizeof(cardtransdtl));
	ret=DB_t_cardtransdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&cardtransdtl);
	if(ret)
	{
	    if(DB_NOTFOUND==ret)
	        return E_DB_CARDTRANSDTL_N;
	    else
	        return E_DB_CARDTRANSDTL_R;
	}	
	if(trans.cardno!=cardtransdtl.cardno)
	{
		DB_t_cardtransdtl_free_lock_by_c0();
		return E_CARDNO_DIFFER;
	}
	if(cardtransdtl.transcode!=TC_POSSAVING&&
		cardtransdtl.transcode!=TC_CARDDEPOSIT&&
		cardtransdtl.transcode!=TC_CARDSAVINGREV)
	{
		DB_t_cardtransdtl_free_lock_by_c0();
		return E_TRANSCODE_NOT_SAVING;
	}
	if(cardtransdtl.revflag[0]=='1')
	{
		DB_t_cardtransdtl_free_lock_by_c0();

		memset(&tCard,0,sizeof(tCard));
		ret=DB_t_card_read_by_cardno(cardtransdtl.cardno,&tCard);
		if(ret)
		{
			writelog(LOG_ERR,"cardno[%d]",cardtransdtl.cardno);
			if(DB_NOTFOUND==ret)
				return E_DB_CARD_N;
			else 
				return E_DB_CARD_R;
		}		
		pAccTrans->remark="该交易已冲正";
		//strcpy(cardphyid,tCard.cardphyid);
		return 0;
	}
	cardtransdtl.revflag[0]='1';
	ret=DB_t_cardtransdtl_update_lock_by_c0(&cardtransdtl);
	if(ret)
	{
	    return E_DB_CARDTRANSDTL_U;
	}	
	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(cardtransdtl.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardtransdtl.cardno);
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_R;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return E_CARD_LOGOUT;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]=='1')
	{
		DB_t_card_free_lock_by_cur();
		return E_CARDNO_FREEZE;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_LOST]=='1')
	{
		DB_t_card_free_lock_by_cur();
		return E_CARDNO_LOST;
	}
//	strcpy(cardphyid,tCard.cardphyid);
	getfmtsysdatetime(tCard.lastsaved);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_U;
	}
	T_t_cardtransdtl cardtransdtlrev;
	memset(&cardtransdtlrev,0,sizeof(cardtransdtlrev));

	des2src(cardtransdtlrev.transdate,trans.transdate);
	des2src(cardtransdtlrev.transtime,trans.transtime);
	des2src(cardtransdtlrev.accdate,trans.accdate);
	strcpy(cardtransdtlrev.acctime,trans.acctime);
	cardtransdtlrev.termid=trans.termid;
	cardtransdtlrev.termseqno=trans.termseqno;
	cardtransdtlrev.custid=cardtransdtl.custid;	
	cardtransdtlrev.transcode=trans.transcode;
	cardtransdtlrev.paytype=0;
	cardtransdtlrev.cardno=cardtransdtl.cardno;
	cardtransdtlrev.purseno=cardtransdtl.purseno;
	cardtransdtlrev.cardcnt=rPack->lvol6+1;
	cardtransdtlrev.cardbefbal=rPack->lvol7/100.0;
	cardtransdtlrev.amount=cardtransdtl.amount;

	if(TC_CARDSAVINGREV==cardtransdtl.transcode)
		cardtransdtlrev.cardaftbal=cardtransdtlrev.cardbefbal+(cardtransdtl.cardbefbal-cardtransdtl.cardaftbal);
	else
		cardtransdtlrev.cardaftbal=cardtransdtlrev.cardbefbal-(cardtransdtl.cardaftbal-cardtransdtl.cardbefbal);	
	des2src(cardtransdtlrev.opercode,trans.opercode);
	cardtransdtlrev.status[0]=DTLSTATUS_SUCCESS;
	cardtransdtlrev.errcode=0;
	ret=DB_t_cardtransdtl_add(&cardtransdtlrev);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_CARDTRANSDTL_E;
	  else
	    return E_DB_CARDTRANSDTL_I;
	}		
	ret=pAccTrans->doReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;
	trans.cardaftbal=cardtransdtlrev.cardaftbal;
	return 0;
}
int F846316(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();

	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDSAVINGREV;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	ret=chk_oper_pwd(rPack->semp_no,rPack->scust_limit);
	if(ret)
		return ret;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);		

	char oldaccdate[9]="";
	des2src(oldaccdate,rPack->sdate3);
	int oldtermid=rPack->lwithdraw_flag;
	int oldtermseqno=rPack->lserial1;

	if(strlen(oldaccdate)<1)
		return E_INPUTNULL_ACCDATE;
	if(oldtermid<1)
		return E_INPUTNULL_TERMID;
	if(oldtermseqno<1)
		return E_INPUTNULL_TERMSEQNO;
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LSERIAL1,F_SSTATION0,F_VSMESS,0);	
	ret=doReverse(rPack,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		return ret;
	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=trans.cardaftbal*100;
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
