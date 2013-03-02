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
	
	trans.revflag=1;//冲正标志

	char transdtlname[61]={0};
	ret=GetTransdtlTableName(oldaccdate,transdtlname);
	if(ret)
	{
		writelog(LOG_ERR,"GetTransdtlTableName err");
		return ret;
	}
	T_t_transdtl transdtl;
	
	ret=ReadTransdtlData(transdtlname,oldaccdate,oldtermid,oldtermseqno,transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ReadTransdtlData transdtlname[%s]oldaccdate[%s]oldtermid[%d]oldtermseqno[%d]",transdtlname,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	if('1'==transdtl.revflag[0])
	{
		return E_TRANS_REVERSED;
	}	
	if(strlen(transdtl.opercode))
	{
		if(strcmp(transdtl.opercode,pAccTrans->trans.opercode)!=0)
		{
			return ERRINFO(E_REVOPER,transdtl.opercode);
		}
	}
	if(trans.cardno!=transdtl.cardno)
	{
		return E_CARDNO_DIFFER;
	}
	if(transdtl.transcode!=TC_POSDEPOSIT&&
		transdtl.transcode!=TC_POSDEPOSITREV&&
		transdtl.transcode!=TC_SHOPPOSDEPOSIT&&
		transdtl.transcode!=TC_SHOPPOSDEPOSITREV&&
		transdtl.transcode!=TC_CARDDEPOSIT&&
		transdtl.transcode!=TC_CARDDEPOSITREV)
	{
		return E_TRANSCODE_NOT_SAVING;
	}
	ret=UpdateTransdtlRevFlag(transdtlname,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
	{
		writelog(LOG_ERR,"UpdateTransdtlRevFlag ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_by_cardno(transdtl.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",transdtl.cardno);
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_R;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
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
//	ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_INCREV,0);
//	if(ret)
//		return ret;
	T_t_transdtl transdtlrev;
	memset(&transdtlrev,0,sizeof(transdtlrev));

	des2src(transdtlrev.transdate,trans.transdate);
	des2src(transdtlrev.transtime,trans.transtime);
	des2src(transdtlrev.accdate,trans.accdate);
	strcpy(transdtlrev.acctime,trans.acctime);
	transdtlrev.termid=trans.termid;
	transdtlrev.termseqno=trans.termseqno;
	transdtlrev.transcode=trans.transcode;
	transdtlrev.paytype=0;
	transdtlrev.cardno=transdtl.cardno;
	transdtlrev.purseno=transdtl.purseno;
	transdtlrev.transflag=TF_PAY;
	transdtlrev.cardcnt=trans.paycnt;
	transdtlrev.cardbefbal=trans.cardbefbal;
	transdtlrev.amount = -transdtl.amount;
	transdtlrev.managefee= -transdtl.managefee;
	transdtlrev.custid=transdtl.custid;
    transdtlrev.showcardno=transdtl.showcardno;
	des2src(transdtlrev.custname,transdtl.custname);
	des2src(transdtlrev.stuempno,transdtl.stuempno);
	des2src(transdtlrev.opercode,transdtl.opercode);
	transdtlrev.cardaftbal=transdtlrev.cardbefbal-(transdtl.cardaftbal-transdtl.cardbefbal);	
	if(amtcmp(transdtlrev.cardaftbal,0)<0)
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
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
	trans.cardflag=1;
	strcpy(trans.cardaccno,tCard.accno);
	ret=pAccTrans->doHistoryReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
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
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_STIME3,F_SEMP,F_LSERIAL1,F_SSTATION0,F_VSMESS,0);	
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardno=rPack->lvol0;
	trans.paycnt= rPack->lvol6+1;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
	ret=doReverse(oldaccdate,oldtermid,oldtermseqno);
	if(ret)
		return ret;
	
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->stime3,pAccTrans->trans.acctime);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	sprintf(outPack->vsmess,"冲正金额%.2lf 卡余额%.2lf元",pAccTrans->trans.transamt,pAccTrans->trans.cardaftbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
