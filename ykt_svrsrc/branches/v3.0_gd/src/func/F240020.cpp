/* --------------------------------------------
 * 程序名称: F240020.cpp
 * 创建日期: 2009-08-07
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台记录流水
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int F240010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F240011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F240020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";
	
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->trans.transcode=TC_BANKTRANS;
	TRANS& trans=pAccTrans->trans;
	trans.termid=rPack->lcert_code;
	
	trans.inputamt = rPack->lvol5/100.0;
	trans.unusedamt=trans.inputamt;
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.cardbefbal=rPack->lvol6/100.00;
	trans.dpscnt=rPack->lvol1+1;	//充值次数
	trans.cardaftbal=trans.cardbefbal;
	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额必须是整数");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	if(rPack->lvol5<1)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额不能为0");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	T_t_account		tAccount;		//帐户表
	T_t_card		card;
		
	memset(&tAccount,0,sizeof(tAccount));
	memset(&card,0,sizeof(card));

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_AUTH,F_SNAME,F_SNAME2,F_LSERIAL0,F_STX_PWD,F_LVOL5,F_LVOL6,0);


	/*判断设备是否登陆 */
	if(0!=device_login_yes_or_no(trans.termid))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	// 校验绑定关系	
	// cardno : lvol0
	// bankno : sphone
	ret = F240011(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
		return ret;

	ret=DB_t_card_read_by_cardno(rPack->lvol0,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_card_read_by_cardno error,errcode=[%d],cardno=[%d]",ret,rPack->lvol0);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,rPack->lvol0);
		else
			return E_DB_CARD_R;
	}
	if(card.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,card.cardno);
	}	
	strcpy(key,STATIC_SEED_KEY);
	des2src(account_pwd, rPack->semp_pwd);
	EncodePwd(key,account_pwd,pwd, 0);

	//判断卡密码是否正确
	if(0!=strncmp(pwd,card.cardpwd,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.cardpwd);
		return E_TRANS_SCHCARD_PWDERR;
	}
	/*
	char buffer[16]="";
	//判断是否处于日终结算状态
 	ret=GetSysParaVal(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}
	*/
	
	trans.cardno=rPack->lvol0;
	ret=pAccTrans->CheckAcc(&card,&tAccount);
	if(ret)
		return ret;
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
		return ret;
	if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);

	trans.feetype=card.feetype;
	trans.cardtype=card.cardtype;
	trans.custid=card.custid;
	if(tAccount.lastdpscnt>trans.dpscnt)
	{
		return ERRINFO(E_CARDCNT_LT_LASTCARDCNT,trans.dpscnt,tAccount.lastdpscnt);
	}

	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			

	
	//取流水号
	ret=pAccTrans->GetTermSeqno();
	if(ret)
	{
		writelog(LOG_ERR,"GetTermSeqno error,error code=[%d]",ret);
		return ret;
	}

	T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));
	
	get_random(tRefno.mac);

	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,trans.sysdatetime);
	des2src(tRefno.accdate,trans.transdate);
	tRefno.termid = trans.termid;
	tRefno.termseqno = trans.termseqno;
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}
	
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.transflag = TF_DPS;
	transdtl.cardcnt=trans.dpscnt;
	transdtl.cardbefbal=trans.cardbefbal;
    transdtl.amount=trans.inputamt;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.custid=tAccount.custid;
	//transdtl.sysid= rPack->lvol2;
	transdtl.exttype=EXTTYPE_BANKCARD;
	des2src(transdtl.extdata,rPack->sphone);		// 银行卡号
	des2src(transdtl.custname,tAccount.accname);
	transdtl.showcardno=atof(card.showcardno);
	transdtl.status[0]=DTLSTATUS_INIT;
	des2src(transdtl.refno,tRefno.refno);
	GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}	
//	des2src(out_pack->scust_auth,bankcard.bankcardno);					// 银行卡号
	des2src(out_pack->sname,transdtl.stuempno);							// 学工号
	des2src(out_pack->sname2,transdtl.refno);							// 交易参考号
	des2src(out_pack->stx_pwd,tRefno.mac);								// 随机数
	out_pack->lserial0=trans.termseqno;									// 终端流水号
	out_pack->lvol5 = D2I(trans.inputamt*100);									// 交易金额 (分)
	out_pack->lvol6 = D2I(trans.cardbefbal*100);									// 入卡值(分)

	writelog(LOG_INFO,"bankcardno[%s],stuempno[%s],refno[%s],termseqno[%d],inputamt[%d],befbal[%d]",rPack->sphone,
		out_pack->sname,out_pack->sname2,out_pack->lserial0,out_pack->lvol5,out_pack->lvol6);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


