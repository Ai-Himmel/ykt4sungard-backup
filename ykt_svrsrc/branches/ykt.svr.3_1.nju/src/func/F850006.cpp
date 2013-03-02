/* ----------------------------------------------------------
 * 创建日期：2009-08-18
 * 程序作者：闻剑
 * 版本信息：3.0.0.0
 * 程序功能：水控钱包互转(广州大学城)
 * ----------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "pubdb.h"
#include "busqc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "acctrans.h"
#include "payment.h"

int F850006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	if(rPack->lbank_acc_type==1)
		pAccTrans->trans.transcode=TC_WATERJD2XT;
	else
		pAccTrans->trans.transcode=TC_WATERXT2JD;
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.termid=rPack->lwithdraw_flag;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			

	trans.cardno= rPack->lvol0;
	if(pAccTrans->trans.cardno<1)
	{
		return E_INPUTNULL_CARDNO;
	}
	des2src(trans.cardphyid,rPack->sstation1);

	
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));
	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	
	ret=pAccTrans->CheckAcc(&tCard,&tAccount);
	if(ret)
	{
		writelog(LOG_INFO,"检查卡状态失败");
		return ret;
	}
	ret=check_card_pwd_by_card(trans.cardno,rPack->stx_pwd);
	if(ret)
		return ret;

	double waterbefbal = rPack->lsafe_level/100.0;

	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	transdtl.transcode=trans.transcode;
	transdtl.cardno=trans.cardno;
//	transdtl.purseno=PURSE_NO_TWO;
//	transdtl.transflag= TF_PAY;
//	transdtl.cardcnt=trans.paycnt;
//	transdtl.cardbefbal=waterbefbal;
//	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.custid=tCard.custid;
//	transdtl.exttype= exttype_
	sprintf(transdtl.extdata,"%.2lf",waterbefbal);
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	des2src(transdtl.showcardno,tCard.showcardno);
	if(transdtl.custid)
	{	
		ret=GetStuempnoByCustid(transdtl.custid,trans.stuempno);
		if(ret)
			return ret;
	}
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"accdate[%s]termid[%d]termseqno[%d]",transdtl.accdate,transdtl.termid,transdtl.termseqno);
	 	 if(DB_REPEAT==ret)
			return E_DB_TRANSDTL_E;
	  	else
			return E_DB_TRANSDTL_I;
	}		
	return 0;
}

