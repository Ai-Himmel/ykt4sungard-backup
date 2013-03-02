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
//	TRANS& trans=pAccTrans->trans;
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
	if('1'==cardtransdtl.revflag[0])
	{
		DB_t_cardtransdtl_free_lock_by_c0();
		pAccTrans->remark="该交易已冲正";
		return 0;
	}
	cardtransdtl.revflag[0]='1';
	ret=DB_t_cardtransdtl_update_lock_by_c0(&cardtransdtl);
	if(ret)
	{
	    return E_DB_CARDTRANSDTL_U;
	}	
	if('1'==authrightflag)
	{
		cardtransdtl.revflag[0]='0';
		des2src(cardtransdtl.accdate,pAccTrans->trans.accdate);
		des2src(cardtransdtl.acctime,pAccTrans->trans.acctime);
	    cardtransdtl.transcode= pAccTrans->trans.transcode;
	    cardtransdtl.termid = pAccTrans->trans.termid;
		cardtransdtl.termseqno = pAccTrans->trans.termseqno;
		des2src(cardtransdtl.opercode,pAccTrans->trans.opercode);
		ret=DB_t_cardtransdtl_add(&cardtransdtl);
		if(ret)
		{
			if(DB_REPEAT==ret)
				return E_DB_CARDTRANSDTL_E;
			else
				return E_DB_CARDTRANSDTL_I;
		}
	}
	ret=pAccTrans->doReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;	
	return 0;
}
int F846315(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
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

	if('1'==authrightflag)
	{
		ret=chk_oper_pwd(rPack->semp_no,rPack->scust_limit);
		if(ret)
			return ret;
	}
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_TRANSREV;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;	
	ret=doReverse(authrightflag,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		return ret;
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
