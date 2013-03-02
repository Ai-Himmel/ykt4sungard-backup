/* --------------------------------------------
 * 创建日期: 2008-06-30
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户转账
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
#include "transcode.h"
#include "acctrans.h"

static int doCard(TRANS& trans,CARDTRANSINFO& cti,T_t_card& tCard)
{

	int ret=0;

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else 
			return E_DB_CARD_R;
	}
	cti.cardtype=tCard.cardtype;
	cti.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return E_CARD_LOGOUT;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]=='1')
	{
		return E_CARDNO_FREEZE;
	}
	if(tCard.cardattr[CARDSTAT_TYPE_LOST]=='1')
	{
		return E_CARDNO_LOST;
	}
	//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,cti.cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,cti.cardphyid);
		return E_CARD_PHYNO_DIFFER;
	}
	//检查卡的有效期
	if(strcmp(tCard.expiredate,trans.transdate)<=0)
		return E_CARD_EXPIRED;
	return 0;
}

int F846336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	int transflag=0;
	char sysdate[9]="";
	char systime[7]="";
	char sMsg[256]="";
	char anonymflag[2]="";

	int cardno=0;
	int cardtype=0;
	int feetype=0;
	int cardflag=0;
	
	char cardphyid[9]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	CARDTRANSINFO& cti=pAccTrans->cti;
	
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	transflag=rPack->lvol3;
	char key[17]="";
	char pwd_plain[33]="";
	char pwd_crypt[33]="";
	strcpy(key,STATIC_SEED_KEY);
	des2src(pwd_plain,rPack->scust_limit);
	EncodePwd(key,pwd_plain,pwd_crypt, 0);
	
	if(transflag)
	{
		trans.transcode=TC_EACC2CARD;
	}
	else
	{
		trans.transcode=TC_CARD2EACC;
	}	

	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	
	T_t_cardtransdtl cardtransdtl;
	memset(&cardtransdtl,0,sizeof(cardtransdtl));

	getsysdate(cardtransdtl.transdate);
	getsystime(cardtransdtl.transtime);
	ret=getAccDate(cardtransdtl.accdate);
	if(ret)
		return ret;
	strcpy(cardtransdtl.acctime,cardtransdtl.transtime);
	cardtransdtl.termid=trans.termid;
	cardtransdtl.termseqno=trans.termseqno;
//	des2src(cardtransdtl.collectdate,rPack->sdate1);
//	des2src(cardtransdtl.collecttime,rPack->stime1);
	cardtransdtl.transcode=trans.transcode;
//	cardtransdtl.paytype=rPack->lvol9;
//	des2src(cardtransdtl.voucherno,rPack->scust_auth2);
	cardtransdtl.cardno=rPack->lvol0;
	cardtransdtl.purseno=PURSE_NO_ONE;
	cardtransdtl.cardcnt=rPack->lvol6+1;
	cardtransdtl.cardbefbal=D4U5(rPack->lvol7/100.0,2);
	cardtransdtl.amount=D4U5(rPack->damt0,2);
	
//	cardtransdtl.cardaftbal=rPack->lvol8;
//	cardtransdtl.siteno=rPack->lcert_code;
//	cardtransdtl.frontno=0;
	//des2src(cardtransdtl.devphyid,rPack->sname);
	//cardtransdtl.devseqno=rPack->lserial0;
	//des2src(cardtransdtl.bankcode,rPack->sbank_code);
	//des2src(cardtransdtl.bankcardno,rPack->scard0);
	//des2src(cardtransdtl.mobile,rPack->sphone2);
	des2src(cardtransdtl.opercode,rPack->semp);
	cardtransdtl.status[0]=DTLSTATUS_SUCCESS;
	cardtransdtl.revflag[0]='0';
	cardtransdtl.errcode=0;
//	des2src(cardtransdtl.remark,rPack->ssectypes);
	
	//检查客户
	trans.cardno=rPack->lvol0;	
	cti.cardno=rPack->lvol0;
	cti.purseno=PURSE_NO_ONE;
	cti.cardcnt=rPack->lvol6+1;
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
	//查询卡帐户
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
	//根据客户号查询电子钱包帐户
	T_t_account tNetAccount;	
	memset(&tNetAccount,0,sizeof(tNetAccount));
	ret=DB_t_account_read_by_custid_and_subjno(tCardAccount.custid,SUBJECT_ESAVING,&tNetAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_CARDACCOUNT_R;
	}
	if(tNetAccount.status[0]!=STATUS_NORMAL)
		return E_EACCNO_LOGOUT;
	strcpy(cti.cardaccno,tCardAccount.accno);
	
	pAccTrans->trans.feetype=tCard.feetype;
	strcpy(pAccTrans->trans.craccno,tCardAccount.accno);
	pAccTrans->trans.usecardflag=1;	
	pAccTrans->trans.custid=tCard.custid;
	//////////////////////////////
	pAccTrans->trans.inputamt=rPack->damt0;
	if(TC_CARD2EACC==trans.transcode)
	{
		//检查卡密码
		if(strcmp(tCardAccount.accpwd,pwd_crypt)!=0)
		{
			return E_CARDPWD;
		}
		if(pAccTrans->trans.inputamt>cti.cardbefbal)
			return E_CARD_BALANCE_SHORTAGE;
		strcpy(pAccTrans->trans.dbaccno,tCardAccount.accno);
		strcpy(pAccTrans->trans.craccno,tNetAccount.accno);		
	}
	else
	{
		//检查电子钱包密码
		if(strcmp(tNetAccount.accpwd,pwd_crypt)!=0)
		{
			return E_EACCPWD;
		}
		if(tNetAccount.stoppayflag[0]=='1')
			return E_EACC_STOPPAY;
		if(pAccTrans->trans.inputamt>tNetAccount.balance)
			return E_EACC_BALANCE_SHORTAGE;
		if(pAccTrans->trans.inputamt+cti.cardbefbal>=tCardAccount.cardmaxbal)
			return E_AMT_EXCEED_MAX;	
		strcpy(pAccTrans->trans.dbaccno,tNetAccount.accno);		
		strcpy(pAccTrans->trans.craccno,tCardAccount.accno);
	}
	pAccTrans->trans.feetype=0;
	pAccTrans->trans.usecardflag=1;	
	pAccTrans->trans.custid=tCard.custid;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;
	if(amtcmp(pAccTrans->trans.unusedamt,0)>0)
		return E_INPUT_AMT;
	if(amtcmp(pAccTrans->trans.unusedamt,0)<0)
		return E_AMT_LACK;
	cardtransdtl.cardaftbal=pAccTrans->trans.cardaftbal;
	ret=DB_t_cardtransdtl_add(&cardtransdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_CARDTRANSDTL_E;
	  else
	    return E_DB_CARDTRANSDTL_I;
	}		
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE0,
		F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=(int)(pAccTrans->trans.cardaftbal*100);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	char temp[128]="";
	sprintf(temp,"卡余额:%.2f",pAccTrans->trans.cardaftbal);
	pAccTrans->remark+=temp;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
