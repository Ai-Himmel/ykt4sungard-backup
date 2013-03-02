/* --------------------------------------------
 * 创建日期: 2009-08-10
 * 程序作者:
 * 版本信息: 3.0.0.0
 * 程序功能: 水控转账
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
#include "dbfunc_foo.h"
#include "busqc.h"
#include "acctrans.h"
#include "payment.h"

int F850010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	pAccTrans->trans.transcode=TC_WATERTRANS;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.termid=rPack->lwithdraw_flag;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));
    ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL8,F_SDATE0,F_SPHONE3,F_SADDR,F_LVOL5,F_LVOL9,F_LSAFE_LEVEL,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
	des2src(trans.refno,rPack->sphone3);		//发送方凭证号

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
			return ERRINFO(E_DB_REFNO_N,trans.refno);
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
	if(RS_SUCC==tRefno.status)
	{
		T_t_transdtl transdtl;

		memset(&transdtl,0,sizeof(transdtl));
		ret=DB_t_transdtl_read_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_NOTEXIST_TRANSDTL;
			else
				return E_DB_TRANSDTL_R;
		}
		outPack->lvol0=transdtl.cardno;
		outPack->lvol5=D4U5(transdtl.amount*100.0,0);
		outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
		outPack->lsafe_level=atoi(transdtl.extdata);
		des2src(outPack->sdate3,transdtl.accdate);
		des2src(outPack->semp,transdtl.opercode);
		outPack->lwithdraw_flag=transdtl.termid;
		outPack->lserial1=transdtl.termseqno;
		des2src(outPack->sphone3,tRefno.refno);
		PutRow(handle,outPack,pRetCode,szMsg);
		return 0;
	}
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.cardno=rPack->lvol0;	
	trans.purseno=PURSE_NO_ONE;
	trans.paycnt=rPack->lvol6+1;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal;
	des2src(trans.cardphyid,rPack->sstation1);
	trans.inputamt= D4U5(rPack->lvol5/100.0);	
	trans.unusedamt = trans.inputamt;
	double waterbefbal = rPack->lsafe_level/100.0;
	double wateraftbal = waterbefbal+trans.inputamt;
	
	if((rPack->lvol5<100)||(rPack->lvol5%100!=0))
	{
		ERRTIP("转账金额必须以元为单位");
		return E_COMMON_ERR;
	}
	if(amtcmp(trans.inputamt,trans.cardbefbal)>0)
	{
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
	}
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_TWO,CardMaxBal);
	if(ret)
		return ret;
	if(amtcmp(wateraftbal,CardMaxBal)>0)
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);

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
	int paycode=rPack->lcert_code;
	CPaymentBase *payment;
	payment = CPaymentBase::find_payment(paycode);
	if(NULL == payment)
	{
		return E_TRANS_FUNC_NONSUPPORT;
	}
	ret = payment->init(handle,&aPack,rPack);
	if(ret)
	{
		writelog(LOG_ERR,"trade[%d],ret[%d]",paycode,ret);		
		return	ret;
	}
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;

	pAccTrans->SetSummary(payment->payment_.summary);
	
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	des2src(transdtl.refno,trans.refno);
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
//	transdtl.paytype=trans.fundtype;
//	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.transflag= TF_PAY;
	transdtl.cardcnt=trans.paycnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.custid=trans.custid;
	transdtl.exttype=paycode;
	sprintf(transdtl.extdata,"%.2lf",wateraftbal);	//小钱包充值后余额
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.showcardno=atol(trans.showcardno);
	GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	tRefno.status=RS_SUCC;
	strcpy(tRefno.accdate,transdtl.accdate);
	tRefno.termid=transdtl.termid;
	tRefno.termseqno=transdtl.termseqno;
	des2src(tRefno.lastsaved,trans.sysdatetime);
	ret=DB_t_refno_update_by_refno(tRefno.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_U;
	}
	outPack->lvol0=tCard.cardno;
	outPack->lvol5=rPack->lvol5;
	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
	outPack->lsafe_level=D4U5(wateraftbal*100,0);
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->stime3,pAccTrans->trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
