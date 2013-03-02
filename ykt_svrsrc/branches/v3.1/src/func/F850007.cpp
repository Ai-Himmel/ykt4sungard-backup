/* ----------------------------------------------------------
 * 创建日期：2010-09-26
 * 程序作者：闻剑
 * 版本信息：3.0.0.0
 * 程序功能：自助充值
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "errdef.h"
#include "pubdb.h"
#include "busqc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "acctrans.h"
#include "transfunc.h"
#include "interfacefunc.h"

static int TestTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char termno[13]={0};
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.transcode=TC_CARDAUTODEPOSIT;
	des2src(trans.opercode,rPack->semp);
	des2src(termno,rPack->sserial0);
	ret=GetDeviceidByDevphyid(termno,&(trans.termid));
	if(ret)
	{
		writelog(LOG_ERR,"termno[%s]",termno);
		return ret;
	}
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;	
	
	trans.cardno=rPack->lvol0;
	if(trans.cardno<1)
	{
		return E_INPUTNULL_CARDNO;
	}
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.purseno=PURSE_NO_ONE;
	trans.dpscnt=rPack->lvol5+1;
	des2src(trans.cardphyid,rPack->sstation1);

	trans.inputamt= D4U5(rPack->lvol1/100.0);	
	trans.unusedamt = trans.inputamt;
	trans.cardbefbal=rPack->lvol7/100.0;
//	trans.cardaftbal=trans.cardbefbal + trans.inputamt;	
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));

	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	
	ret=pAccTrans->CheckAcc(&tCard,&tAccount);
	if(ret)
	{
		writelog(LOG_INFO,"检查状态失败");
		return ret;
	}
	if(amtcmp(tAccount.balance-trans.cardbefbal,MAXAMT_CARDGTACC)>0)
	{
		writelog(LOG_ERR,"卡余额[%.2lf]错误",trans.cardbefbal);
		return ERRIF_CARDBAL_EXCEPT;
	}
	trans.custid=tCard.custid;
	if(trans.custid>0)
	{
		ret=GetCustBaseInfoByCustID(trans.custid,trans.custname,trans.stuempno,NULL);
		if(ret)
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

	des2src(transdtl.opercode,trans.opercode);
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
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.stuempno,trans.stuempno);
	des2src(transdtl.showcardno,tCard.showcardno);
	transdtl.status[0]=DTLSTATUS_INIT;
	des2src(transdtl.refno,tRefno.refno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}	
	outPack->lvol0=tCard.cardno;
	outPack->lvol1=D4U5(trans.inputamt*100,0);
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,tRefno.refno);	
    des2src(outPack->saddr,tRefno.mac);	//mac
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);			
	return 0;
}

static int NormalTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);

	des2src(trans.refno,rPack->sphone3);		//交易参考号
	if(strlen(trans.refno)!=14)
	{
		 ERRTIP("交易参考号错误");
		 return E_COMMON_ERR;
	}
	T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));

	ret=DB_t_refno_read_by_refno(trans.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(tRefno.mac,rPack->saddr,8)!=0)
	{
		ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}
	if(RS_FAIL==tRefno.status)
	{
		ERRTIP("交易已失败");
		return E_COMMON_ERR;
	}
	T_t_transdtl transdtl;	
	memset(&transdtl,0,sizeof(transdtl));
	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_TRANSDTL;
		else
			return E_DB_TRANSDTL_R;
	}
	if(RS_SUCC==tRefno.status)
	{
		DB_t_transdtl_free_lock_by_c0();
		outPack->lvol0=transdtl.cardno;
		outPack->lvol1=D4U5(transdtl.amount*100,0);
		outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
		des2src(outPack->sdate3,transdtl.transdate);
		des2src(outPack->stime3,transdtl.transtime);
		des2src(outPack->semp,transdtl.opercode);
		outPack->lwithdraw_flag=transdtl.termid;
		outPack->lserial1=transdtl.termseqno;
		des2src(outPack->sphone3,transdtl.refno);	
		des2src(outPack->saddr,tRefno.mac);
		PutRow(handle,outPack,pRetCode,szMsg);
		return 0;
	}
	if(transdtl.status[0]!=DTLSTATUS_INIT)
	{
		DB_t_transdtl_free_lock_by_c0();
		ERRTIP("交易流水表状态错误");
		return E_COMMON_ERR;
	}
	des2src(trans.opercode,transdtl.opercode);
	des2src(trans.cardphyid,rPack->sstation1);
	des2src(trans.stuempno,transdtl.stuempno);
	trans.termid=transdtl.termid;
	trans.termseqno=transdtl.termseqno;
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.transcode=transdtl.transcode;
	trans.cardno=transdtl.cardno;	
	trans.purseno=transdtl.purseno;
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.purseno=PURSE_NO_ONE;
	pAccTrans->SetCardCntAndCardBal(rPack->lvol5,0,rPack->lvol7);
	trans.aftdpscnt++;
	trans.inputamt= D4U5(rPack->lvol1/100.0);	
	trans.unusedamt = trans.inputamt;

	if(amtcmp(trans.inputamt,1000)>0)
	{
		DB_t_transdtl_free_lock_by_c0();
		ERRTIP("单次充值金额超过限制");
		return E_COMMON_ERR;
	}
	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else
			return E_DB_CARD_R;
	}
	strcpy(trans.cardaccno,tCard.accno);
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;
	trans.fundtype =1;//现金
	ret=pAccTrans->doTrans();
	if(ret)
	{	
		DB_t_transdtl_free_lock_by_c0();
		return ret;
	}
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		return ret;	
	}
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.amount=trans.inputamt;
	transdtl.cardaftbal=trans.cardaftbal;
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_U;
	}
	tRefno.status=RS_SUCC;
	strcpy(tRefno.lastsaved,trans.sysdatetime);
	ret=DB_t_refno_update_by_refno(tRefno.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_U;
	}
	ret=SaveCardTransInfo();
	if(ret)
	{
		writelog(LOG_ERR,"SaveCardTransInfo ret=%d",ret);
	}
	outPack->lvol0=tCard.cardno;
	outPack->lvol1=D4U5(trans.inputamt*100,0);
	outPack->lvol8=D4U5(trans.cardaftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);
	des2src(outPack->saddr,tRefno.mac);
	sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
	des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);			
	return 0;
}
int F850007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	//支付交易
	switch(rPack->lbank_acc_type)
	{
			//试入账
		case 1:
			ret=TestTrans(handle,rPack,pRetCode,szMsg);
			break;
			//正式入账
		case 2:
			ret=NormalTrans(handle,rPack,pRetCode,szMsg);
			break;
	}
	return ret;
}

