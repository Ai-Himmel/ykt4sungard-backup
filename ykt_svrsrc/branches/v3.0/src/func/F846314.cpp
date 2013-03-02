/* --------------------------------------------
 * 创建日期: 2008-06-30
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通支取
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

static int doCard(TRANS& trans,T_t_card& tCard)
{
	int ret=0;

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDNO;
		else 
			return E_DB_CARD_R;
	}
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.lockflag[0])
	{
		ERRTIP("请将该卡注销");
		return ERRINFO(E_CARDNO_LOCKED,trans.cardno);
	}
	if('1'==tCard.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==tCard.badflag[0])
	{
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,trans.cardphyid);
		return E_CARD_PHYNO_DIFFER;
	}
	//检查卡的有效期
	if(strcmp(tCard.expiredate,trans.transdate)<=0)
		return E_CARD_EXPIRED;
	return 0;
}

int F846314(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
//	ret=pAccTrans->checkCfgUpdate();
//	if(ret)
//		return ret;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_CARDDRAW;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.cardno=rPack->lvol0;	
	trans.purseno=PURSE_NO_ONE;
	trans.cardcnt=rPack->lvol6+1;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
//	trans.fundtype=PAYTYPE_CASH;
	des2src(trans.cardphyid,rPack->sstation0);
	trans.inputamt=rPack->damt0;	
	if(amtcmp(trans.inputamt,trans.cardbefbal)>0)
	{
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal-trans.inputamt);
	}
	T_t_card tCard;
	
	memset(&tCard,0,sizeof(tCard));
	ret=doCard(trans,tCard);
	if(ret)
	{
		return ret;
	}
	ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_DEC,0);
	if(ret)
		return ret;
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_cardno_and_purseno(trans.cardno,trans.purseno,&tCardAccount);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]purseno[%d]",trans.cardno,trans.purseno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_CARDNO_PURSENO_NOACCNO,trans.cardno,trans.purseno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	if(tCardAccount.lastcardcnt>trans.cardcnt)
	{
		return ERRINFO(E_CARDCNT_LT_LASTCARDCNT,trans.cardcnt,tCardAccount.lastcardcnt);
	}
	strcpy(trans.cardaccno,tCardAccount.accno);
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;
	strcpy(trans.draccno,tCardAccount.accno);
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
//	transdtl.paytype=trans.fundtype;
//	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.cardcnt=trans.cardcnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.custid=tCardAccount.custid;
	des2src(transdtl.custname,tCardAccount.accname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.showcardno=atol(tCard.showcardno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE0,
		F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
