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

static int doCard(T_t_card& tCard)
{

	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();	
	TRANS& trans=pAccTrans->trans;

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDNO;
		else 
			return E_DB_CARD_R;
	}
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
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
	if('1'==tCard.lockflag[0])
	{
		return ERRINFO(E_CARDNO_LOCKED,trans.cardno);
	}	
	//比较卡物理ID是否相同
	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,trans.cardphyid);
		return E_CARD_PHYNO_DIFFER;
	}
	//检查卡的有效期
	if(strcmp(tCard.expiredate,trans.transdate)<=0)
		return E_CARD_EXPIRED;
	return 0;
}

int F846336(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	int transflag=rPack->lvol3;;
	if(transflag)
	{
		pAccTrans->trans.transcode=TC_EACC2CARD;
	}
	else
	{
		pAccTrans->trans.transcode=TC_CARD2EACC;
	}	
	
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	char key[17]="";
	char pwd_plain[33]="";
	char pwd_crypt[33]="";
	strcpy(key,STATIC_SEED_KEY);
	des2src(pwd_plain,rPack->scust_limit);
	EncodePwd(key,pwd_plain,pwd_crypt, 0);
	
	trans.cardflag=1;
	pAccTrans->trans.usecardflag=1;	
	trans.cardno=rPack->lvol0;
	trans.purseno=PURSE_NO_ONE;
	trans.dpscnt=rPack->lvol5+1;
	trans.paycnt=rPack->lvol6+1;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
	trans.inputamt=D4U5(rPack->damt0,2);
	trans.unusedamt = trans.inputamt;
	
//	transdtl.cardaftbal=rPack->lvol8;
//	transdtl.siteno=rPack->lcert_code;
//	transdtl.frontno=0;
	//des2src(transdtl.devphyid,rPack->sname);
	//transdtl.devseqno=rPack->lserial0;
	//des2src(transdtl.bankcode,rPack->sbank_code);
	//des2src(transdtl.bankcardno,rPack->scard0);
	//des2src(transdtl.mobile,rPack->sphone2);
//	des2src(transdtl.remark,rPack->ssectypes);
	
	//检查客户
	des2src(trans.cardphyid,rPack->sstation0);
	T_t_card tCard;
	
	memset(&tCard,0,sizeof(tCard));
	ret=doCard(tCard);
	if(ret)
	{
		return ret;
	}
	//查询卡帐户
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
	//根据客户号查询电子钱包帐户
	T_t_netacc tNetAccount;	
	memset(&tNetAccount,0,sizeof(tNetAccount));
	ret=DB_t_netacc_read_by_custid(tCardAccount.custid,&tNetAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_EACCNO,tCardAccount.custid);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tNetAccount.status[0]!=STATUS_NORMAL)
		return ERRINFO(E_EACCNO_LOGOUT,tNetAccount.accno);
	strcpy(trans.cardaccno,tCardAccount.accno);
	
	pAccTrans->trans.feetype=tCard.feetype;
	pAccTrans->trans.custid=tCard.custid;
	strcpy(pAccTrans->trans.cardaccno,tCardAccount.accno);
	strcpy(pAccTrans->trans.eaccno,tNetAccount.accno); 	
	if(TC_CARD2EACC==trans.transcode)
	{
		//检查卡密码
		if(strcmp(tCard.cardpwd,pwd_crypt)!=0)
		{
			return E_CARDPWD;
		}
		if(amtcmp(pAccTrans->trans.inputamt,trans.cardbefbal)>0)
			return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
		strcpy(pAccTrans->trans.draccno,tCardAccount.accno);
		strcpy(pAccTrans->trans.craccno,tNetAccount.accno);		
	}
	else
	{
		char inpwd_crypt[65]="";
		char seedkey[33]="";
		char inpwd_plain[65]="";
		char dbpwd_plain[65]="";
		//检查电子钱包密码
		des2src(inpwd_crypt,rPack->snote2);
		if(!strlen(inpwd_crypt))
			return E_PWD_NULL;
		ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,seedkey);
		if(ret)
			return ret;
		ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
		if(ret)
			return E_EACCPWD;
		ret=decrypt_elec_card_pwd(0,seedkey,tNetAccount.accpwd,dbpwd_plain);
		if(ret)
			return E_PWD_DECRYPT;
		if(strcmp(inpwd_plain,dbpwd_plain)!=0)
			return E_EACCPWD;

		if(tNetAccount.stoppayflag[0]=='1')
			return ERRINFO(E_EACC_STOPPAY,tNetAccount.accno);
		if(amtcmp(pAccTrans->trans.inputamt,tNetAccount.balance)>0)
			return ERRINFO(E_EACC_BALANCE_SHORTAGE,pAccTrans->trans.inputamt-tNetAccount.balance);
	
		double CardMaxBal=0;
		ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
		if(ret)
			return ret;
		if(amtcmp(pAccTrans->trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
			return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);	
		strcpy(pAccTrans->trans.draccno,tNetAccount.accno);		
		strcpy(pAccTrans->trans.craccno,tCardAccount.accno);
	}
	pAccTrans->trans.feetype=0;
	pAccTrans->trans.usecardflag=1;	
	pAccTrans->trans.custid=tCard.custid;
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.accdate);
	des2src(transdtl.transtime,trans.acctime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	if(TC_EACC2CARD==trans.transcode)
	{
		transdtl.transflag=TF_DPS;
		transdtl.cardcnt = trans.dpscnt;
	}
	else
	{
		transdtl.transflag=TF_PAY;
		transdtl.cardcnt = trans.paycnt;
	}
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=pAccTrans->trans.cardaftbal;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.totalfeeamt;
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.revflag[0]='0';
	des2src(transdtl.showcardno,tCard.showcardno);
	transdtl.custid=tCard.custid;
	GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE0,
		F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	char temp[128]="";
	sprintf(temp,"卡余额:%.2f",pAccTrans->trans.cardaftbal);
	pAccTrans->remark+=temp;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	des2src(trans.remark,outPack->vsmess);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
