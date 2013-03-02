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
//联机冲正,当日即时冲正
int OnlineTransRev(char *oldaccdate,int oldtermid,int oldtermseqno)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;

	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
	    if(DB_NOTFOUND==ret)
	        return E_DB_TRANSDTL_N;
	    else
	        return E_DB_TRANSDTL_R;
	}	
	if('1'==transdtl.revflag[0])
	{
		DB_t_transdtl_free_lock_by_c0();
		pAccTrans->remark="该交易已冲正";
		return 0;
	}	
	transdtl.revflag[0]='1';
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"UpdateTransdtlRevFlag ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	if(transdtl.cardcnt>0&&transdtl.cardno>0)
	{
		ret=UpdateCardBitmap(transdtl.cardno,transdtl.cardcnt,CARDBITMAPTYPE_RESET,0);
		if(ret)
			return ret;
	}
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
	trans.cardflag=1;
	trans.revflag=1;//冲正标志
	trans.cardbefbal=transdtl.cardaftbal;
	trans.cardaftbal=trans.cardbefbal;
	ret=pAccTrans->doTodayReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret; 
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.revflag[0]='0';
	strcpy(transdtl.accdate,pAccTrans->trans.accdate);
	strcpy(transdtl.acctime,pAccTrans->trans.acctime);
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
	return 0;
}
//冲账交易
int AccTransRev(char *oldaccdate,int oldtermid,int oldtermseqno)
{
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.revflag=1;//冲正标志

	char transdtlname[61]={0};
	int ret=GetTransdtlTableName(oldaccdate,transdtlname);
	if(ret)
	{
		writelog(LOG_ERR,"GetTransdtlTableName err");
		return ret;
	}
	T_t_transdtl transdtl;

	ret=ReadTransdtlData(transdtlname,oldaccdate,oldtermid,oldtermseqno,transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ReadTransdtlData transdtlname[%s],oldaccdate[%s],oldtermid[%d],oldtermseqno[%d]",transdtlname,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	if('1'==transdtl.revflag[0])
	{
//		DB_t_transdtl_free_lock_by_c0();
		pAccTrans->remark="该交易已冲正";
		return 0;
	}	
	ret=UpdateTransdtlRevFlag(transdtlname,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
	{
		writelog(LOG_ERR,"UpdateTransdtlRevFlag ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	if(transdtl.cardcnt>0&&transdtl.cardno>0)
	{
		ret=UpdateCardBitmap(transdtl.cardno,transdtl.cardcnt,CARDBITMAPTYPE_RESET,0);
		if(ret)
			return ret;
	}
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
	transdtl.revflag[0]='0';
	strcpy(transdtl.accdate,pAccTrans->trans.accdate);
	strcpy(transdtl.acctime,pAccTrans->trans.acctime);
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
	ret=pAccTrans->doHistoryReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
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
		ret=AccTransRev(oldaccdate,oldtermid,oldtermseqno);
		if(ret)
		{
			writelog(LOG_ERR,"acctransrev err ret=%d",ret);
			return ret;
		}
	}
	else
	{
		ret=OnlineTransRev(oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		{
			writelog(LOG_ERR,"acctransrev err ret=%d",ret);
		return ret;
		}
	}
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_STIME3,F_SEMP,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->stime3,pAccTrans->trans.acctime);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
