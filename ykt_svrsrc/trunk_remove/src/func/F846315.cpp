/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通交易冲正
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
static int doReverse(char authrightflag,char* oldaccdate,int oldtermid,int oldtermseqno)
{
	//查找操作员流水
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.revflag=1;//冲正标志
	T_t_transdtl OrgiTransdtl;
	T_t_transdtl transdtl;
	memset(&OrgiTransdtl,0,sizeof(OrgiTransdtl));
	ret=DB_v_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&OrgiTransdtl);
	if(ret)
	{
	    if(DB_NOTFOUND==ret)
	        return E_DB_TRANSDTL_N;
	    else
	        return E_DB_TRANSDTL_R;
	}	
	if('1'==OrgiTransdtl.revflag[0])
	{
		DB_v_transdtl_free_lock_by_c0();
		pAccTrans->remark="该交易已冲正";
		return 0;
	}
	OrgiTransdtl.revflag[0]='1';
	ret=DB_v_transdtl_update_lock_by_c0(&OrgiTransdtl);
	if(ret)
	{
	    return E_DB_TRANSDTL_U;
	}	
	if(OrgiTransdtl.cardcnt>0&&OrgiTransdtl.cardno>0)
	{
		ret=UpdateCardBitmap(OrgiTransdtl.cardno,OrgiTransdtl.cardcnt,CARDBITMAPTYPE_RESET,0);
		if(ret)
			return ret;
	}
	memcpy(&transdtl,&OrgiTransdtl,sizeof(transdtl));
	if(strlen(transdtl.opercode))
	{
		if(strcmp(transdtl.opercode,pAccTrans->trans.opercode)!=0)
		{
			return ERRINFO(E_REVOPER,transdtl.opercode);
		}
	}
	else
	{
		des2src(transdtl.opercode,trans.opercode);
	}

	if('1'!=authrightflag)
	{
		transdtl.cardaftbal=OrgiTransdtl.cardbefbal;
		transdtl.cardbefbal=OrgiTransdtl.cardaftbal;
		pAccTrans->trans.cardflag=1;
	}
	transdtl.revflag[0]='0';
	strcpy(transdtl.accdate,pAccTrans->trans.sysdate);
	strcpy(transdtl.acctime,pAccTrans->trans.systime);
	des2src(transdtl.transdate,pAccTrans->trans.transdate);
	des2src(transdtl.transtime,pAccTrans->trans.transtime);
    transdtl.transcode= pAccTrans->trans.transcode;
    transdtl.termid = pAccTrans->trans.termid;
	transdtl.termseqno = pAccTrans->trans.termseqno;
	transdtl.amount = -transdtl.amount;
	transdtl.managefee = -transdtl.managefee;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_TRANSDTL_E;
		else
			return E_DB_TRANSDTL_I;
	}
	if(transdtl.cardno)
	{
		T_t_card card;
		memset(&card,0,sizeof(card));
		ret=DB_t_card_read_by_cardno(transdtl.cardno,&card);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CARDNO,transdtl.cardno);
			else
				return E_DB_CARD_R;
		}
		strcpy(pAccTrans->trans.cardaccno,card.accno);
	}
	ret=pAccTrans->doReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;	
	return 0;
}
int F846315(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	if(strlen(pAccTrans->trans.opercode)<1)
	{
		pAccTrans->trans.termid=rPack->lwithdraw_flag;
	}
	pAccTrans->trans.transcode=TC_TRANSREV;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
//	TRANS& trans=pAccTrans->trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);		

	char oldaccdate[9]="";
	des2src(oldaccdate,rPack->sdate3);
	int oldtermid=rPack->lwithdraw_flag;
	int oldtermseqno=rPack->lserial1;
	
	char authrightflag=rPack->sstatus2[0];

	if(strlen(oldaccdate)<1)
		return E_INPUTNULL_ACCDATE;
	if(oldtermid<1)
		return E_INPUTNULL_TERMID;
	if(oldtermseqno<1)
		return E_INPUTNULL_TERMSEQNO;

	des2src(pAccTrans->trans.chkopercode,rPack->semp_no);
	if('1'==authrightflag)
	{
		ret=chk_oper_pwd(pAccTrans->trans.chkopercode,rPack->scust_limit);
		if(ret)
			return ret;
	}
	ret=doReverse(authrightflag,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		return ret;
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
