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
static int doReverse(char* oldaccdate,int oldtermid,int oldtermseqno,char *cardpwd,char *cardphyid)
{
	//查找操作员流水
	int ret=0;
	T_t_card tCard;
	
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
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
		strcpy(cardphyid,tCard.cardphyid);
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
	if(strcmp(tCard.cardpwd,cardpwd)!=0)
	{
		DB_t_card_free_lock_by_cur();
		return E_CARDPWD;
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
	tCard.status[0]=STATUS_LOGOUT;
	strcpy(cardphyid,tCard.cardphyid);
	strcpy(tCard.closedate,trans.transdate);
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
	//检查客户
	if(tCard.custid)
	{
		T_t_customer tCustomer;
		
		memset(&tCustomer,0,sizeof(tCustomer));
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
		strcpy(tCustomer.lastsaved,tCard.lastsaved);
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
	//回收卡
	T_t_cardbook tCardBook;

	memset(&tCardBook,0,sizeof(tCardBook));
	ret=getCardBookRecordNo(tCardBook.recordno);
	if(ret)
		return ret;
	tCardBook.cardtype=tCard.cardtype;
	strcpy(tCardBook.curno,tCard.showcardno);
	strcpy(tCardBook.startno,tCard.showcardno);
	strcpy(tCardBook.endno,tCard.showcardno);	
	tCardBook.usedcnt=0;
	tCardBook.unusedcnt=1;
	tCardBook.status[0]=STATUS_NORMAL;
	getfmtsysdatetime(tCardBook.lastsaved);
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

	des2src(tCarddtl.accdate,trans.accdate);
	tCarddtl.termid=trans.termid;
	tCarddtl.termseqno=trans.termseqno;
	tCarddtl.cardtype=tCard.cardtype;
	des2src(tCarddtl.showcardno,tCard.showcardno);
	des2src(tCarddtl.cardphyid,tCard.cardphyid);
	tCarddtl.cardusetype[0]=CARDUSETYPE_REUSE;
	des2src(tCarddtl.opercode,trans.opercode);
	ret=DB_t_carddtl_add(&tCarddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
	//删除卡交易位图数据
	ret=DB_t_cardbitmap_del_by_cardno(tCard.cardno);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);		
		return E_DB_CARDBITMAP_D;
	}	
	////添加卡版本号记录
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,trans.accdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	des2src(cardver.cardphyid,tCard.cardphyid);
	cardver.cardvertype=CARDVERTYPE_CARDCLOSE;
	
	ret=addCardVerNo(cardver);
	if(ret)
		return ret;
	ret=pAccTrans->doReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;
	//注销帐户
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c1_and_cardno_and_purseno(cardtransdtl.cardno,cardtransdtl.purseno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_CARDACCOUNT_N;
		else
			return E_DB_CARDACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c1();
		return E_CARDACC_LOGOUT;
	}
	if(tCardAccount.balance!=0)
	{
		writelog(LOG_ERR,"balance[%d]",tCardAccount.balance);
		DB_t_account_free_lock_by_c1();
		return E_CARDACC_BALANCE_NOZERO;
	}
	if(tCardAccount.foregift!=0)
	{
		writelog(LOG_ERR,"foregift[%d]",tCardAccount.foregift);
		DB_t_account_free_lock_by_c1();
		return E_CARDACC_FOREGIFT_NOZERO;
	}
	tCardAccount.status[0]=STATUS_LOGOUT;
	strcpy(tCardAccount.closedate,trans.transdate);
	ret=DB_t_account_update_lock_by_c1(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_CARDACCDTL_U;

	}
	return 0;
}
int F846302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char key[17]="";
	char cardpwd[33]="";
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CARDOPENREV;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	
	strcpy(key,STATIC_SEED_KEY);
	
	if(!strlen(rPack->scust_limit))
	{
		return E_CARDPWD;
	}
	EncodePwd(key,rPack->scust_limit,cardpwd, 0);

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
	ret=doReverse(oldaccdate,oldtermid,oldtermseqno,cardpwd,outPack->sstation0);
	if(ret)
		return ret;
	outPack->lvol0=pAccTrans->trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,pAccTrans->trans.opercode);
	outPack->lserial1=pAccTrans->trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
