/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通回收卡
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

static int doCard(TRANS& trans,CARDTRANSINFO& cti,T_t_card& tCard)
{

	int ret=0;

	ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_R;
	}
	cti.cardtype=tCard.cardtype;
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
	if(tCard.custid>0)
	{
		DB_t_card_free_lock_by_cur();
		return E_CARDRETURN_CARD_HAVE_CUST;
	}
		//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,cti.cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,cti.cardphyid);
		DB_t_card_free_lock_by_cur();
		return E_CARD_PHYNO_DIFFER;
	}
	//回收卡
	T_t_cardtype tCardType;

	memset(&tCardType,0,sizeof(tCardType));
		
	ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardType);
	if(tCardType.anonymflag[0]!='1')
	{
		DB_t_card_free_lock_by_cur();
		return	E_CARDTYPE_CANNOT_REUSE;
	}
	if(tCardType.validdays<1)
	{
		DB_t_card_free_lock_by_cur();		
		return E_NOSET_CARDTYPE_VALIDDAYS;
	}
	ret=calcEndDate(trans.transdate,tCardType.validdays,tCard.expiredate);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();		
		return ret;
	}
	char cardpwd[33]="";
	char key[17]="";
	get_init_passwd_by_man_id("",cardpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,cardpwd,tCard.cardpwd, 0);
	memset(tCard.cardattr,'0',sizeof(tCard.cardattr));
	getfmtsysdatetime(tCard.lastsaved);

	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_CARD_N;
		else 
			return E_DB_CARD_U;
	}
	//用来输出卡密码
	strcpy(tCard.cardpwd,cardpwd);
	
	//添加卡片回收明细记录
	T_t_carddtl tCarddtl;
	
	memset(&tCarddtl,0,sizeof(tCarddtl));
	/////////////////////////////////rPack2TableStuct////////////////////////
	des2src(tCarddtl.accdate,trans.accdate);
	tCarddtl.termid=trans.termid;
	tCarddtl.termseqno=trans.termseqno;
	tCarddtl.cardtype=tCard.cardtype;
	des2src(tCarddtl.showcardno,tCard.showcardno);
	des2src(tCarddtl.cardphyid,tCard.cardphyid);
	tCarddtl.cardusetype[0]=CARDUSETYPE_RETURNCARD;
	des2src(tCarddtl.opercode,trans.opercode);
	ret=DB_t_carddtl_add(&tCarddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
	return 0;
}
static int doAccount(TRANS& trans,char *cardaccno)
{
	int ret=0;
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c0_and_accno(cardaccno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_LOGOUT;
	}
	if(tCardAccount.balance!=0)
	{
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_BALANCE_NOZERO;
	}
	tCardAccount.lastcardcnt=0;
	strcpy(tCardAccount.lasttransdate,trans.transdate);
	tCardAccount.availbal=0;
	tCardAccount.frozebal=0;
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_U;
	}
	return 0;
}

int F846310(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char sMsg[256]="";
	char anonymflag[2]="";

	int cardno=0;
	int cardtype=0;
	int feetype=0;
	int cardflag=0;
	int returnForgiftFlag=0;
	
	char cardphyid[9]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	CARDTRANSINFO cti;
	
	memset(&cti,0,sizeof(cti));
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

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
	pAccTrans->trans.transcode=TC_CARDRETURN;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;

	//检查客户
	trans.cardno=rPack->lvol0;	
	cti.cardno=rPack->lvol0;
	cti.purseno=PURSE_NO_ONE;
	cti.cardcnt=rPack->lvol6;
	cti.cardbefbal=rPack->lvol7/100.0;
	des2src(cti.cardphyid,rPack->sstation0);
	cti.cardflag=1;
	
	T_t_card tCard;
	
	memset(&tCard,0,sizeof(tCard));
	ret=doCard(trans,cti,tCard);
	if(ret)
	{
		return ret;
	}
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_cardno_and_purseno(cti.cardno,cti.purseno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_CARDACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return E_CARDACC_LOGOUT;
	}
	//检查最后交易日期是否超过挂失补办日期,防止流水未上传
	char expiredate[9]="";
	char sDays[10]="";
	ret=getParaVal(GLOBE_RENEWCARDDATE,sDays);
	if(ret)
		return ret;
	int days=atoi(sDays);
	
	ret=calcEndDate(tCardAccount.lasttransdate,days,expiredate);
	if(ret)
		return ret;
	getsysdate(sysdate);
	if(strcmp(sysdate,expiredate)<0)
	{
		return E_CARDLASTDATE_NOREACH;
	}
	strcpy(cti.cardaccno,tCardAccount.accno);
	memcpy(&pAccTrans->cti,&cti,sizeof(cti));
	pAccTrans->trans.feetype=tCard.feetype;
	strcpy(pAccTrans->trans.dbaccno,tCardAccount.accno);
	pAccTrans->trans.inputamt=tCardAccount.balance;
	pAccTrans->trans.transamt=tCardAccount.balance;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;	
	//修改帐户
	ret=doAccount(trans,tCardAccount.accno);
	if(ret)
		return ret;
	T_t_cardtransdtl cardtransdtl;
	memset(&cardtransdtl,0,sizeof(cardtransdtl));

	strcpy(cardtransdtl.transdate,trans.transdate);
	strcpy(cardtransdtl.transtime,trans.transtime);
	strcpy(cardtransdtl.accdate,trans.accdate);
	strcpy(cardtransdtl.acctime,trans.acctime);
	cardtransdtl.termid=trans.termid;
	cardtransdtl.termseqno=trans.termseqno;
//	des2src(cardtransdtl.collectdate,rPack->sdate1);
//	des2src(cardtransdtl.collecttime,rPack->stime1);
	cardtransdtl.transcode=trans.transcode;
//	cardtransdtl.paytype=rPack->lvol9;
//	des2src(cardtransdtl.voucherno,rPack->scust_auth2);
	cardtransdtl.purseno=PURSE_NO_ONE;
	cardtransdtl.cardcnt=cti.cardcnt;
	cardtransdtl.cardbefbal=cti.cardbefbal;
	cardtransdtl.amount=tCardAccount.balance;
	cardtransdtl.cardaftbal=trans.cardaftbal;
////	cardtransdtl.frontno=0;
	//des2src(cardtransdtl.devphyid,rPack->sname);
	//cardtransdtl.devseqno=rPack->lserial0;
	//des2src(cardtransdtl.bankcode,rPack->sbank_code);
	//des2src(cardtransdtl.bankcardno,rPack->scard0);
	//des2src(cardtransdtl.mobile,rPack->sphone2);
	des2src(cardtransdtl.opercode,trans.opercode);
	cardtransdtl.status[0]=DTLSTATUS_SUCCESS;
	cardtransdtl.revflag[0]='0';
	cardtransdtl.errcode=0;

	SetCol(handle,F_LVOL0,F_LVOL8,F_LVOL5,F_LVOL6,F_SDATE0,
		F_SDATE3,F_STX_PWD,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=tCard.cardno;
	outPack->lvol5=tCard.feetype;
	outPack->lvol6=1;
	outPack->lvol8=0;
	des2src(outPack->sdate0,tCard.expiredate);
	des2src(outPack->stx_pwd,tCard.cardpwd);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;	
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
