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
	TRANS& trans=pAccTrans->trans;

	//des2src(pAccTrans->trans.opercode,rPack->semp);
	trans.termid=rPack->lcert_code;
	
	int transflag=rPack->lvol3;
	if(transflag)
	{
		trans.transcode=TC_EACC2CARD;
	}
	else
	{
		trans.transcode=TC_CARD2EACC;
	}
	
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			

	char pwd_crypt[33]="";
	des2src(pwd_crypt,rPack->scust_limit); // 卡密码
	
	trans.cardflag=1;
	trans.usecardflag=1;	
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

	T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));
	
	get_random(tRefno.mac);
	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,trans.sysdatetime);
	des2src(tRefno.accdate,trans.accdate);
	tRefno.termid = trans.termid;
	tRefno.termseqno = trans.termseqno;
	tRefno.status = RS_SUCC;
	
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}

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
	
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;
	strcpy(trans.cardaccno,tCardAccount.accno);
	strcpy(trans.eaccno,tNetAccount.accno); 

	if(TC_CARD2EACC==trans.transcode)
	{
		//检查卡密码
		if(strcmp(tCard.cardpwd,pwd_crypt)!=0)
		{
			return E_CARDPWD;
		}

		if(amtcmp(trans.inputamt,trans.cardbefbal)>0)
			return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
	}
	else
	{
		char inpwd_crypt[65]="";
		des2src(inpwd_crypt,rPack->snote2); //检查电子钱包密码
		if(!strlen(inpwd_crypt))
			return E_EACCPWD;

		if(strcmp(inpwd_crypt,tNetAccount.paypwd)!=0)
			return E_EACCPWD;
		
		//if(tNetAccount.stoppayflag[0]=='1')
		//	return ERRINFO(E_EACC_STOPPAY,tNetAccount.accno);

		if(amtcmp(trans.inputamt,tNetAccount.balance)>0)
			return ERRINFO(E_EACC_BALANCE_SHORTAGE,trans.inputamt-tNetAccount.balance);

		double CardMaxBal=0;
		ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
		if(ret)
			return ret;
		if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
			return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);	
	}
	trans.feetype=0;
	trans.usecardflag=1;
	trans.custid=tCard.custid;
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.refno,tRefno.refno); // 交易参考号
	des2src(transdtl.transdate,trans.accdate);
	des2src(transdtl.transtime,trans.acctime);
	des2src(transdtl.coldate,trans.accdate);
	des2src(transdtl.coltime,trans.acctime);	
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	des2src(transdtl.custname,tNetAccount.accname);
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
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.amount=trans.inputamt;
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

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);	
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE0,F_SPHONE3,F_SADDR,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
	
	strcpy(outPack->sphone3,tRefno.refno);
	strcpy(outPack->saddr,tRefno.mac);			
	outPack->lvol0=tCard.cardno;
	outPack->lvol8=D4U5(trans.cardaftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	char temp[128]="";
	if(TC_EACC2CARD==trans.transcode)
	{
		sprintf(temp,"电子账户向卡转账 %.2f 元成功，电子账户余额:%.2f 卡余额:%.2f",
		trans.inputamt,
		trans.draccaftbal,
		trans.cardaftbal);
	}
	else
	{
		sprintf(temp,"卡向电子账户转账 %.2f 元成功，电子账户余额:%.2f 卡余额:%.2f",
		trans.inputamt,
		trans.craccaftbal,
		trans.cardaftbal);
	}

	pAccTrans->remark+=temp;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	des2src(trans.remark,outPack->vsmess);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
