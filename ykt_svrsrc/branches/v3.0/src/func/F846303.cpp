/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通销户
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
static int doAccount(TRANS& trans)
{
	int ret=0;
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c0_and_accno(trans.cardaccno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,trans.cardaccno);
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
		return ERRINFO(E_CARDACC_BALANCE_NOZERO,tCardAccount.balance);
	}
	if(amtcmp(tCardAccount.foregift,0)!=0)
	{
		writelog(LOG_ERR,"foregift[%.2lf]",tCardAccount.foregift);
		DB_t_account_free_lock_by_c0();
		return ERRINFO(E_CARDACC_FOREGIFT_NOZERO,tCardAccount.foregift);
	}
	tCardAccount.status[0]=STATUS_DELETE;
	tCardAccount.lastcardbal=0;
	tCardAccount.frozebal=0;
	tCardAccount.subsidybal=0;
	tCardAccount.availbal=0;
	strcpy(tCardAccount.closedate,trans.transdate);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tCardAccount.accno);
		else 
			return E_DB_ACCOUNT_U;
	}
	return 0;
}
//有卡退卡
static int CardCloseWithCard()
{
	//检查卡
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;

	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
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
	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
	{
		DB_t_card_free_lock_by_cur();
	//	writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,trans.cardphyid);
		return ERRINFO(E_CARD_PHYNO_DIFFER,trans.cardphyid,tCard.cardphyid);
	}
	ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
	tCard.status[0]=STATUS_DELETE;
	strcpy(tCard.closedate,trans.transdate);
	getfmtsysdatetime(tCard.lastsaved);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,tCard.cardno);
		else 
			return E_DB_CARD_U;
	}
	trans.cardtype=tCard.cardtype;
	trans.custid=tCard.custid;
	trans.feetype=tCard.feetype;
	des2src(trans.showcardno,tCard.showcardno);
	
	T_t_customer tCustomer;

	memset(&tCustomer,0,sizeof(tCustomer));
	if(trans.custid>0)
	{
		ret=DB_t_customer_read_lock_by_cur_and_custid(trans.custid,&tCustomer);
		if(ret)
		{		
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,trans.custid);
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.holdcardcnt)
		{		
			tCustomer.holdcardcnt--;
		}	
		getfmtsysdatetime(tCustomer.lastsaved);
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,trans.custid);
			else
				return E_DB_CUSTOMER_U;
		}
		des2src(trans.custname,tCustomer.custname);
		des2src(trans.stuempno,tCustomer.stuempno);
	}
	////添加卡版本号记录
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.sysdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,trans.stuempno);
	cardver.cardvertype=CARDVERTYPE_CARDCLOSE;
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
	//回收卡
	T_t_cardtype tCardType;

	memset(&tCardType,0,sizeof(tCardType));
		
	ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardType);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDTYPE,tCard.cardtype);
		else
			return E_DB_CARDTYPE_R;
	}
	if(tCardType.reuseable[0]=='1')
	{
		if(pAccTrans->sysPara.bEnableCardMgr)
		{
			ret=UseShowCardNoBack(trans.opercode,tCard.showcardno);
			if(ret)
				return ret;
			T_t_carddtl carddtl;
			memset(&carddtl,0,sizeof(carddtl));
			
			des2src(carddtl.accdate,pAccTrans->trans.sysdate);
			des2src(carddtl.acctime,trans.systime);
			carddtl.termid=trans.termid;
			carddtl.termseqno=trans.termseqno;
			des2src(carddtl.opercode,trans.opercode);
			carddtl.cardtype=tCard.cardtype;
			carddtl.usetype=CARDUSETYPE_REUSE;
			carddtl.inoutflag=INOUTFLAG_IN;
			carddtl.transcnt=1;
			strcpy(carddtl.summary,"销户回收卡");	
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
	}
	//读取帐户信息
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tCard.accno);
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
	if(trans.cardsubsidyno<tCardAccount.lastsubsidyno)
	{
		ERRTIP("该卡补助批次号不能小于上次卡补助批次号");
		return E_CARDSUBSIDYNO;
	}
	//检查补助信息
	double subsidyamt=0;
	int maxsubsidyno=0;
	ret =GetSubsidy(trans.cardno,trans.cardsubsidyno,1,subsidyamt,maxsubsidyno);
	if(ret)
	{
		writelog(LOG_ERR,"DoGetSubsidy ret=[%d]",ret);
		return ret;
	}
	double cardbal=D4U5(trans.cardbefbal+subsidyamt);
	double availbal=D4U5(tCardAccount.subsidybal+tCardAccount.availbal);
	strcpy(trans.cardaccno,tCardAccount.accno);
	//押金处理
	double returncashamt=0;
	if(tCardAccount.foregift>0)
	{
		returncashamt=tCardAccount.foregift;
		trans.inputamt=tCardAccount.foregift;
		trans.transamt=tCardAccount.foregift;
		trans.fundtype=0;//0表示从帐户扣
		//退押金
		pAccTrans->trans.transtype=TRANSTYPE_RETURNFOREGIFT;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret;	
		ret=pAccTrans->doTransEnd();
		if(ret)
			return ret;
	}
	//判断卡余额是否大于账户余额
	if(amtcmp(cardbal,availbal)>0)
	{
		if(amtcmp(cardbal - availbal,pAccTrans->sysPara.dAutoRenewAccMaxAmt)>0)
		{
			return ERRINFO(E_CARDBAL_EXCEPTION,cardbal,availbal);
		}		
//		if(amtcmp(trans.cardbefbal,tCardAccount.availbal)!=0)
	//	{			
		trans.inputamt=D4U5(cardbal-availbal);
		trans.transamt=trans.inputamt;
		trans.fundtype=0;//0表示从帐户扣
		//营业外支出
		pAccTrans->trans.transtype=TRANSTYPE_LESS_CARDBAL;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret; 
		ret=pAccTrans->doTransEnd();
		if(ret)
			return ret;
//		}
//		else
//		{
			//如果卡本身余额等于账户余额,则按照卡余额退款
//			cardbal=tCardAccount.balance;
//		}
	}
	else if(amtcmp(cardbal,availbal)<0)
	{
		//营业外收入
		
//		if(amtcmp(trans.cardbefbal,tCardAccount.availbal)!=0)
//		{			
		trans.inputamt=D4U5(availbal-cardbal);
		trans.transamt=trans.inputamt;
		trans.fundtype=0;//0表示从帐户扣
		//营业外支
		pAccTrans->trans.transtype=TRANSTYPE_MORE_CARDBALINCOME;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret; 
		ret=pAccTrans->doTransEnd();
		if(ret)
			return ret;
//		}
	}
	//下面退款按账户金额来退
	returncashamt= D4U5(returncashamt+cardbal+tCardAccount.frozebal);
	trans.inputamt=cardbal+tCardAccount.frozebal;//按卡余额来退款
	trans.feetype=tCard.feetype;
	trans.fundtype=0;
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;	
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	returncashamt=D4U5(returncashamt-trans.totalfeeamt);
	sprintf(trans.remark,"销户成功,%s,总共应退现金%.2lf元",pAccTrans->remark.c_str(),returncashamt);
	return 0;
}
//无卡退卡
static int CardCloseWithoutCard()
{
	//检查卡
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	int ReturnForgift=0;
	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else 
			return E_DB_CARD_R;
	}
	trans.cardtype=tCard.cardtype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("请先解冻后再销户");
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.badflag[0])
	{
		if((CARDBADFLAG_CARDBAL==tCard.badtype[0])||(CARDBADFLAG_ACCBAL==tCard.badtype[0]))
		{
			DB_t_card_free_lock_by_cur();
			ERRTIP("该卡余额错误,请使用坏卡修复功能处理,不可以直接退卡");
			return E_CARD_BAD_AND_NEED_UPDATE;
		}
	}
	//无卡只有挂失或卡物理损坏的情况下才可以退卡
	if(tCard.lossflag[0]!='1'&&
		tCard.badflag[0]!='1')
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("该卡状态正常,请先放卡再销户!");
		return E_COMMON_ERR;
	}
	if(tCard.badflag[0]=='1')
	{
		//检查卡是否到了销卡的时间
		/*
		T_t_badcardbook badcardbook;
		memset(&badcardbook,0,sizeof(badcardbook));
		ret=DB_t_badcardbook_read_by_cardno(trans.cardno,&badcardbook);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();
			if(DB_NOTFOUND==ret)
				return E_DB_BADCARDBOOK_N;
			else
				return E_DB_BADCARDBOOK_R;
		}
		*/
		char enddate[9]="";
		ret=calcEndDate(tCard.baddate,pAccTrans->sysPara.iPosdtlMaxDayCnt,enddate);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();		
			return ret;
		}
		if(strncmp(enddate,pAccTrans->trans.transdate,8)>0)
		{
			DB_t_card_free_lock_by_cur();		
			return ERRINFO(E_BADCARD_RECORDDATE_NOTREACH,enddate);
		}
		if(tCard.badtype[0]!=CARDBADFLAG_MANMADE)
			ReturnForgift=1;
	}	
	else if('1'==tCard.lossflag[0])
	{
		char enddate[9]="";
		ret=calcEndDate(tCard.lossdate,pAccTrans->sysPara.iPosdtlMaxDayCnt,enddate);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();		
			return ret;
		}
		if(strncmp(enddate,pAccTrans->trans.transdate,8)>0)
		{
			DB_t_card_free_lock_by_cur();		
			return ERRINFO(E_CARDLOSSDATE_NOREACH,enddate);
		}
	}	
	tCard.status[0]=STATUS_DELETE;
	ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();		
		return ret;
	}
	strcpy(tCard.closedate,trans.transdate);
	getfmtsysdatetime(tCard.lastsaved);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,tCard.cardno);
		else 
			return E_DB_CARD_U;
	}
	trans.custid=tCard.custid;
	trans.feetype=tCard.feetype;
	des2src(trans.showcardno,tCard.showcardno);
	
	T_t_customer tCustomer;

	memset(&tCustomer,0,sizeof(tCustomer));
	if(tCard.custid>0)
	{
		ret=DB_t_customer_read_lock_by_cur_and_custid(trans.custid,&tCustomer);
		if(ret)
		{		
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,trans.custid);
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.holdcardcnt)
		{		
			tCustomer.holdcardcnt--;
		}	
		getfmtsysdatetime(tCustomer.lastsaved);
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_CUSTOMER,trans.custid);
			else
				return E_DB_CUSTOMER_U;
		}
		des2src(trans.custname,tCustomer.custname);
		des2src(trans.stuempno,tCustomer.stuempno);
	}
	////添加卡版本号记录
	T_t_cardver cardver;

	memset(&cardver,0,sizeof(cardver));
	cardver.cardno=tCard.cardno;
	des2src(cardver.accdate,pAccTrans->trans.sysdate);
	cardver.termid=trans.termid;
	cardver.termseqno=trans.termseqno;
	cardver.cardno=tCard.cardno;
	cardver.status[0]=STATUS_NORMAL;	
	des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,trans.stuempno);
	cardver.cardvertype=CARDVERTYPE_CARDCLOSE;
	des2src(cardver.cardverno,tCard.cardverno);
	ret=DB_t_cardver_add(&cardver);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDVER_E;
		else
			return E_DB_CARDVER_I;
	}
//检查补助信息
	//double cardbal=D4U5(trans.cardbefbal+subsidyamt);
	//读取帐户信息
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tCard.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
	}
	double subsidyamt=0;
	int maxsubsidyno=0;
	
	ret =GetSubsidy(trans.cardno,tCardAccount.subsidyno,trans.cardflag,subsidyamt,maxsubsidyno);
	if(ret)
	{
		writelog(LOG_ERR,"DoGetSubsidy ret=[%d]",ret);
		return ret;
	}
	strcpy(trans.cardaccno,tCardAccount.accno);
	//押金处理
	double returncashamt=0;
	if(tCardAccount.foregift>0)
	{
		trans.inputamt=tCardAccount.foregift;
		trans.transamt=tCardAccount.foregift;
		trans.fundtype=0;//0表示从帐户扣
		//退押金
			//退押金
		if(ReturnForgift)
		{
			pAccTrans->trans.transtype=TRANSTYPE_RETURNFOREGIFT;
			returncashamt=tCardAccount.foregift;
		}
		else
		{
			pAccTrans->trans.transtype=TRANSTYPE_FOREGIFT2COSTFEE;
		}
		ret=pAccTrans->DoTransByTransType();
		if(ret)
		ret=pAccTrans->doTransEnd();
		if(ret)
			return ret;
	}
	double ReturnCardBal=0;
	if(amtcmp(tCardAccount.availbal,tCardAccount.lastcardbal)<=0)
		ReturnCardBal=D4U5(tCardAccount.availbal+tCardAccount.subsidybal);
	else
		ReturnCardBal=D4U5(tCardAccount.lastcardbal+tCardAccount.subsidybal);

	if(amtcmp(tCardAccount.balance,ReturnCardBal)>0)
	{
		//走长款处理
		trans.transamt=D4U5(tCardAccount.balance-ReturnCardBal);
		trans.inputamt=trans.transamt;
		trans.fundtype=0;
		pAccTrans->trans.transtype=TRANSTYPE_MORE_CARDBALINCOME;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret;
		if(pAccTrans->trans.unusedamt>0)
			return E_INPUT_AMT;
		if(pAccTrans->trans.unusedamt<0)
			return E_AMT_LACK;
	}
	//下面退款按账户金额来退
	returncashamt= D4U5(returncashamt+ReturnCardBal);
	trans.inputamt=ReturnCardBal;
	trans.feetype=tCard.feetype;
	trans.fundtype=0;
	ret=pAccTrans->doTrans();
	if(ret)
		return ret; 
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	returncashamt=D4U5(returncashamt-trans.totalfeeamt);
	sprintf(trans.remark,"销户成功 %s 总共应退现金%.2lf元",pAccTrans->remark.c_str(),returncashamt);
	return 0;
}

int F846303(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
//	ret=pAccTrans->checkCfgUpdate();
//	if(ret)
//		return ret;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_CARDCLOSE;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);	
	SetCol(handle,0);

	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

		//检查客户
	trans.cardflag=rPack->lvol4;//有无卡标志
	trans.cardno=rPack->lvol0;	
	trans.purseno=PURSE_NO_ONE;
	if(trans.cardflag)
	{
		trans.cardcnt=rPack->lvol6+1;
		trans.cardbefbal=rPack->lvol8/100.0;
		trans.cardaftbal=trans.cardbefbal;		
		trans.cardsubsidyno=rPack->lvol10;
		des2src(trans.cardphyid,rPack->sstation0);
		ret=CardCloseWithCard();
		if(ret)
			return ret;
	}	
	else
	{
		ret=CardCloseWithoutCard();
		if(ret)
			return ret;
	}
	//注销帐户
	ret=doAccount(trans);
	if(ret)
		return ret;
	//删除卡库不平表该卡的记录
	ret=DelCardAccDiffByCardno(trans.cardno);
	if(ret)
		return ret;
	strcpy(transdtl.transdate,trans.transdate);
	strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.transcode=trans.transcode;
	des2src(transdtl.opercode,trans.opercode);
	transdtl.purseno=PURSE_NO_ONE;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.revflag[0]='0';
	transdtl.errcode=0;
	transdtl.cardno=trans.cardno;
	transdtl.cardcnt=trans.cardcnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=0;
	transdtl.custid=trans.custid;	
    transdtl.showcardno=atol(trans.showcardno);
	des2src(transdtl.custname,trans.custname);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=trans.cardno;
	outPack->lvol8=0;
	des2src(outPack->sdate3,pAccTrans->trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
