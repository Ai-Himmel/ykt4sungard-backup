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
static int doReverse(char* oldaccdate,int oldtermid,int oldtermseqno)
{
	//查找操作员流水
	int ret=0;
	T_t_card tCard;
	
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	
	T_v_transdtl vTransdtl;
	memset(&vTransdtl,0,sizeof(vTransdtl));
	ret=DB_v_transdtl_read_by_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&vTransdtl);
	if(ret)
	{
	    if(DB_NOTFOUND==ret)
	        return E_DB_TRANSDTL_N;
	    else
	        return E_DB_TRANSDTL_R;
	}	
	if(strlen(vTransdtl.opercode))
	{
		if(strcmp(vTransdtl.opercode,pAccTrans->trans.opercode)!=0)
		{
			return ERRINFO(E_REVOPER,vTransdtl.opercode);
		}
	}
	if(trans.cardno!=vTransdtl.cardno)
	{
		return E_CARDNO_DIFFER;
	}
	if(vTransdtl.transcode!=TC_POSDEPOSIT&&
		vTransdtl.transcode!=TC_POSDEPOSITREV&&
		vTransdtl.transcode!=TC_SHOPPOSDEPOSIT&&
		vTransdtl.transcode!=TC_SHOPPOSDEPOSITREV&&
		vTransdtl.transcode!=TC_CARDDEPOSIT&&
		vTransdtl.transcode!=TC_CARDDEPOSITREV)
	{
		return E_TRANSCODE_NOT_SAVING;
	}
	if(vTransdtl.revflag[0]=='1')
	{
		/*
		memset(&tCard,0,sizeof(tCard));
		ret=DB_t_card_read_by_cardno(vTransdtl.cardno,&tCard);
		if(ret)
		{
			writelog(LOG_ERR,"cardno[%d]",vTransdtl.cardno);
			if(DB_NOTFOUND==ret)
				return E_DB_CARD_N;
			else 
				return E_DB_CARD_R;
		}
		*/
		pAccTrans->remark="该交易已冲正";
		//strcpy(cardphyid,tCard.cardphyid);
		return E_TRANS_REVERSED;
	}
	ret=UpdateTransdtlRevFlag(oldaccdate,oldtermid,oldtermseqno);
	if(ret)
	{
		writelog(LOG_ERR,"UpdateTransdtlRevFlag ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(vTransdtl.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",vTransdtl.cardno);
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_R;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==tCard.badflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
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
	ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_INCREV,0);
	if(ret)
		return ret;
	T_t_transdtl transdtlrev;
	memset(&transdtlrev,0,sizeof(transdtlrev));

	des2src(transdtlrev.transdate,trans.transdate);
	des2src(transdtlrev.transtime,trans.transtime);
	des2src(transdtlrev.accdate,pAccTrans->trans.sysdate);
	strcpy(transdtlrev.acctime,trans.systime);
	transdtlrev.termid=trans.termid;
	transdtlrev.termseqno=trans.termseqno;
	transdtlrev.transcode=trans.transcode;
	transdtlrev.paytype=0;
	transdtlrev.cardno=vTransdtl.cardno;
	transdtlrev.purseno=vTransdtl.purseno;
	transdtlrev.cardcnt=trans.cardcnt;
	transdtlrev.cardbefbal=trans.cardbefbal;
	transdtlrev.amount = -vTransdtl.amount;
	transdtlrev.managefee= -vTransdtl.managefee;
	transdtlrev.custid=vTransdtl.custid;
    transdtlrev.showcardno=vTransdtl.showcardno;
	des2src(transdtlrev.custname,vTransdtl.custname);
	des2src(transdtlrev.opercode,vTransdtl.opercode);
	transdtlrev.cardaftbal=transdtlrev.cardbefbal-(vTransdtl.cardaftbal-vTransdtl.cardbefbal);	
	if(amtcmp(transdtlrev.cardaftbal,0)<0)
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,transdtlrev.cardaftbal);
	transdtlrev.status[0]=DTLSTATUS_SUCCESS;
	transdtlrev.errcode=0;
	ret=DB_t_transdtl_add(&transdtlrev);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	strcpy(trans.cardaccno,tCard.accno);
	ret=pAccTrans->doReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;
	trans.cardaftbal=transdtlrev.cardaftbal;
	trans.transamt=transdtlrev.amount;
	return 0;
}
int F846316(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_CARDDEPOSITREV;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;
	des2src(trans.chkopercode,rPack->semp_no);

	ret=chk_oper_pwd(trans.chkopercode,rPack->scust_limit);
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
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardno=rPack->lvol0;
	trans.cardcnt= rPack->lvol6+1;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
	ret=doReverse(oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		return ret;
	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	sprintf(outPack->vsmess,"冲正金额%.2lf 卡余额%.2lf元",pAccTrans->trans.transamt,pAccTrans->trans.cardaftbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
