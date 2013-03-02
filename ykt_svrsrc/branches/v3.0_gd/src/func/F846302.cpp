/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通开户冲正
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
static int doReverse(char* oldaccdate,int oldtermid,int oldtermseqno,char *cardphyid)
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
		writelog(LOG_ERR,"ReadTransdtlData transdtlname[%s],oldaccdate[%s],oldtermid[%d],oldtermseqno[%d]",transdtlname,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}	
	if('1'==transdtl.revflag[0])
	{
		memset(&tCard,0,sizeof(tCard));
		ret=DB_t_card_read_by_cardno(transdtl.cardno,&tCard);
		if(ret)
		{
			writelog(LOG_ERR,"cardno[%d]",transdtl.cardno);
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CARDNO,tCard.cardno);
			else 
				return E_DB_CARD_R;
		}		
		pAccTrans->remark="该交易已冲正";
		strcpy(cardphyid,tCard.cardphyid);
		return 0;
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
	ret=UpdateTransdtlRevFlag(transdtlname,oldaccdate,oldtermid,oldtermseqno);
	if(ret)
	{
		writelog(LOG_ERR,"UpdateTransdtlRevFlag ret[%d] transdtlname[%s]accdate[%s]termid[%d]termseqno[%d]",ret,transdtlname,oldaccdate,oldtermid,oldtermseqno);
		return ret;
	}
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.transcode=TC_CARDOPENREV;
	transdtl.cardcnt=trans.paycnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=0;
	transdtl.amount=-transdtl.amount;
	if(amtcmp(trans.cardbefbal,0)>0)
	{	
		transdtl.transflag=TF_PAY;
		transdtl.cardcnt=trans.paycnt;
	}
	transdtl.managefee=-transdtl.managefee;
	transdtl.revflag[0]=0;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_TRANSDTL_E;
		else
			return E_DB_TRANSDTL_I;
	}
	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(transdtl.cardno,&tCard);
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
	ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
	tCard.status[0]=STATUS_DELETE;
	strcpy(cardphyid,tCard.cardphyid);
	strcpy(tCard.closedate,trans.transdate);
	des2src(tCard.lastsaved,trans.sysdatetime);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_U;
	}	
	T_t_customer tCustomer;
	
	memset(&tCustomer,0,sizeof(tCustomer));
	//检查客户
	if(tCard.custid)
	{
		ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid,&tCustomer);
		if(ret)
		{
			writelog(LOG_ERR,"custid[%d]",tCard.custid);
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else 
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.status[0]!=STATUS_NORMAL)

		{
			DB_t_customer_free_lock_cur();
			return E_CUSTOMER_LOGOUT;		
		}
		tCustomer.holdcardcnt--;
		des2src(tCustomer.lastsaved,trans.sysdatetime);
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			writelog(LOG_ERR,"custid[%d]",tCard.custid);
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else 
				return E_DB_CUSTOMER_U;
		}
	}
	////添加卡版本号记录
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,tCustomer.stuempno);
	cardver.cardvertype=CARDVERTYPE_CARDCLOSE;	
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		writelog(LOG_ERR,"cardverno[%s]",cardver.cardverno);
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	if(pAccTrans->sysPara.bEnableCardMgr)
	{
		ret=UseShowCardNoRev(tCard.showcardno);
		if(ret)
			return ret;
		trans.cardno=tCard.cardno;
		T_t_carddtl carddtl;
		memset(&carddtl,0,sizeof(carddtl));
		
		des2src(carddtl.accdate,trans.accdate);
		des2src(carddtl.acctime,trans.acctime);
		carddtl.termid=trans.termid;
		carddtl.termseqno=trans.termseqno;
		des2src(carddtl.opercode,trans.opercode);
		carddtl.cardtype=tCard.cardtype;
		carddtl.usetype=CARDUSETYPE_GET;
		carddtl.inoutflag=INOUTFLAG_IN;
		carddtl.transcnt=1;
		strcpy(carddtl.summary,"发卡冲正");	
		des2src(carddtl.cardphyid,tCard.cardphyid);
		des2src(carddtl.showcardno,tCard.showcardno);
		ret=DB_t_carddtl_add(&carddtl);
		if(ret)
		{
			if(DB_REPEAT==ret)
				return E_DB_CARDDTL_E;
			else
				return E_DB_CARDDTL_I;
		}	
	}
	/*
	//回收卡
	T_t_cardbook tCardBook;

	memset(&tCardBook,0,sizeof(tCardBook));
	ret=getCardBookRecordNo(tCardBook.recordno);
	if(ret)
		return ret;
	tCardBook.cardtype=tCard.cardtype;
//	strcpy(tCardBook.curno,tCard.showcardno);
//	strcpy(tCardBook.startno,tCard.showcardno);
//	strcpy(tCardBook.endno,tCard.showcardno);	
////	tCardBook.usedcnt=0;
//	tCardBook.unusedcnt=1;
	tCardBook.status[0]=STATUS_NORMAL;
	strcpy(tCardBook.opercode,trans.opercode);
	ret=DB_t_cardbook_add(&tCardBook);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDBOOK_E;
		else
			return E_DB_CARDBOOK_I;
	}
	//添加卡片回收明细记录
	T_t_carddtl tCarddtl;
	
	memset(&tCarddtl,0,sizeof(tCarddtl));

	des2src(tCarddtl.accdate,pAccTrans->sysPara.sSettleDate);
	tCarddtl.termid=trans.termid;
	tCarddtl.termseqno=trans.termseqno;
	tCarddtl.cardtype=tCard.cardtype;
	des2src(tCarddtl.showcardno,tCard.showcardno);
	des2src(tCarddtl.cardphyid,tCard.cardphyid);
	tCarddtl.cardusetype=CARDUSETYPE_REUSE;
	des2src(tCarddtl.opercode,trans.opercode);
	ret=DB_t_carddtl_add(&tCarddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
	*/
	//删除卡交易位图数据
	/*
	ret=DB_t_cardbitmap_del_by_cardno(tCard.cardno);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);		
		return E_DB_CARDBITMAP_D;
	}
	*/
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		writelog(LOG_ERR,"transdtl.cardno[%d],transdtl.purseno[%d]",transdtl.cardno,transdtl.purseno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return E_CARDACC_LOGOUT;
	}
	des2src(trans.cardaccno,tCardAccount.accno);
	ret=pAccTrans->doHistoryReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
	{
		if(E_DB_ACCDTL_N!=ret)
		return ret;
	}
	//注销帐户

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c0_and_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		writelog(LOG_ERR,"transdtl.cardno[%d],transdtl.purseno[%d]",transdtl.cardno,transdtl.purseno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_LOGOUT;
	}
	if(amtcmp(tCardAccount.balance,0)!=0)
	{
		writelog(LOG_ERR,"balance[%.2lf]",tCardAccount.balance);
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_BALANCE_NOZERO;
	}
	if(amtcmp(tCardAccount.foregift,0)!=0)
	{
		writelog(LOG_ERR,"foregift[%.2lf]",tCardAccount.foregift);
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_FOREGIFT_NOZERO;
	}
	tCardAccount.status[0]=STATUS_DELETE;
	strcpy(tCardAccount.closedate,trans.transdate);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_ACCOUNT_U;

	}
	return 0;
}
int F846302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
//	ret=pAccTrans->checkCfgUpdate();
//	if(ret)
//		return ret;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_CARDOPENREV;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;
	char authrightflag=rPack->sstatus2[0];
	des2src(trans.chkopercode,rPack->semp_no);
	if('1'==authrightflag)
	{
		ret=chk_oper_pwd(trans.chkopercode,rPack->scust_limit);
		if(ret)
			return ret;
	}
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
		

	char oldaccdate[9]="";
	des2src(oldaccdate,rPack->sdate3);
	int oldtermid=rPack->lwithdraw_flag;
	int oldtermseqno=rPack->lserial1;
	trans.dpscnt=rPack->lvol5;
	trans.paycnt=rPack->lvol6;
	trans.cardbefbal=rPack->lvol7;
	des2src(trans.cardphyid,rPack->sstation1);
	if(trans.dpscnt>1||trans.paycnt>0)
		return E_CARD_USED;
	if(strlen(oldaccdate)<1)
		return E_INPUTNULL_ACCDATE;
	if(oldtermid<1)
		return E_INPUTNULL_TERMID;
	if(oldtermseqno<1)
		return E_INPUTNULL_TERMSEQNO;
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LSERIAL1,F_SSTATION0,F_VSMESS,F_STIME3,0);	
	ret=doReverse(oldaccdate,oldtermid,oldtermseqno,outPack->sstation0);
	if(ret)
		return ret;
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->stime3,pAccTrans->trans.acctime);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,"开户冲正成功");
	strcat(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
