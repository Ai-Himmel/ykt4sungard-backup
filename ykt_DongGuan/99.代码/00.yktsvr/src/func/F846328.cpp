/* ----------------------------------------------------------
 * 创建日期：2010-03-22
 * 程序作者：闻剑
 * 版本信息：3.0.0.0
 * 程序功能：卡卡转账
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
#include "tcp.h"

static int TestTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	trans.transcode=TC_CARD2CARD;
	des2src(trans.opercode,rPack->semp);
	trans.termid=rPack->lwithdraw_flag;
	ret=ats.InitTrans();
	if(ret)
		return ret;	
	if(rPack->lvol0<1)
	{
		ERRTIP("请输入付款方卡号");
		return E_COMMON_ERR;
	}
	if(rPack->lvol2<1)
	{
		ERRTIP("请输入收款方卡号");
		return E_COMMON_ERR;
	}
	if(rPack->lvol1<0)
	{
		ERRTIP("请输入转账金额");
		return E_COMMON_ERR;
	}
	T_t_card tInCard;
	memset(&tInCard,0,sizeof(tInCard));

	T_t_account tInAccount;
	memset(&tInAccount,0,sizeof(tInAccount));

	ats.trans.cardno=rPack->lvol2;
	ret=ats.CheckAcc(&tInCard,&tInAccount);
	if(ret)
	{
		char sErrMsg[256];
		strcpy(sErrMsg,"收款方卡账户状态错误:");
		strcat(sErrMsg,ats.GetErrTip().c_str());
		ERRTIP(sErrMsg);
		return ret;
	}
	T_t_card  tOutCard;
	memset(&tOutCard,0,sizeof(tOutCard));

	T_t_account tOutAccount;
	memset(&tOutAccount,0,sizeof(tOutAccount));

	ats.trans.cardno=rPack->lvol0;

	ret=ats.CheckAcc(&tOutCard,&tOutAccount);
	if(ret)
	{
		char sErrMsg[256];
		strcpy(sErrMsg,"付款方卡账户状态错误:");
		strcat(sErrMsg,ats.GetErrTip().c_str());
		ERRTIP(sErrMsg);
		return ret;
	}
	double dInCardAftBal=(rPack->lvol1+rPack->lsafe_level)/100.0;
	trans.cardflag=0;
	trans.usecardflag=0;	
	trans.purseno=PURSE_NO_ONE;
	trans.paycnt=rPack->lvol6+1;
	des2src(trans.cardphyid,rPack->sstation1);

	trans.inputamt= D4U5(rPack->lvol1/100.0);	
	trans.unusedamt = trans.inputamt;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal - trans.inputamt;
	if(amtcmp(trans.inputamt,trans.cardbefbal)>0)
	{
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
	}	
	//检查收款方账户余额是否超过最大值
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
		return ret;
	if(amtcmp(dInCardAftBal,CardMaxBal)>=0)
	{
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
	}
		// 保持第三方账号
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	transdtl.exttype = 0;
	sprintf(transdtl.voucherno,"%d",tInCard.cardno);
	transdtl.exttype=EXTTYPE_OPPSNO;
	GetStuempnoByCustid(tInCard.custid,transdtl.extdata);
	sprintf(transdtl.remark,"向(%s)转入",tInAccount.accname);
	ret = ats.GenTransdtl(&transdtl,DTLSTATUS_INIT);
	if(ret)
	{
		writelog(LOG_ERR,"GenTransdtl ret=%d",ret);
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		return ret;
	}	
	//trans.cardaftbal=trans.cardbefbal;
	strcpy(ats.trans.draccno,tOutAccount.accno);
	strcpy(ats.trans.craccno,tInAccount.accno);
	ret=ats.doTrans();
	if(ret)
	{
		writelog(LOG_ERR,"doTrans err=%d",ret);
		return ret;
	}
	ret=ats.doTransEnd();
	if(ret)
	{
		writelog(LOG_ERR,"doTransEnd err=%d",ret);
		return ret;
	}
	if(amtcmp(trans.cardaftbal,transdtl.cardaftbal)!=0)
	{
		ERRTIP("卡余额计算有误");
		return E_COMMON_ERR;
	}
	ret=db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_rollback err");
		return ret;
	}
	// 输出参数
	outPack->lvol0=tOutCard.cardno;
	outPack->lvol1=D4U5(trans.inputamt*100,0);
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lvol2=tInCard.cardno;
	outPack->lsafe_level2=D4U5(dInCardAftBal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);	
    des2src(outPack->saddr,trans.cardpwd);	//mac
    sprintf(trans.remark,"%s卡余额%.2lf元",ats.remark.c_str(),ats.trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

static int NormalTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);

	if(rPack->lvol0<1)
	{
		ERRTIP("请输入付款方卡号");
		return E_COMMON_ERR;
	}
	if(rPack->lvol2<1)
	{
		ERRTIP("请输入收款方卡号");
		return E_COMMON_ERR;
	}
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
	ret=DB_t_transdtl_read_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_TRANSDTL;
		else
			return E_DB_TRANSDTL_R;
	}
	if(RS_SUCC==tRefno.status)
	{
		outPack->lvol0=transdtl.cardno;
		outPack->lvol1=D4U5(transdtl.amount*100,0);
		outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
		outPack->lsafe_level2=rPack->lsafe_level+D4U5(transdtl.amount*100,0);
		des2src(outPack->sdate3,transdtl.transdate);
		des2src(outPack->stime3,transdtl.transtime);
		des2src(outPack->semp,transdtl.opercode);
		outPack->lwithdraw_flag=transdtl.termid;
		outPack->lserial1=transdtl.termseqno;
		des2src(outPack->sphone3,transdtl.refno);	
		PutRow(handle,outPack,pRetCode,szMsg);
		return 0;
	}
	int cardno=atoi(transdtl.voucherno);
	if(rPack->lvol2!=cardno)
	{
		ERRTIP("收款方卡号错误");
		return E_COMMON_ERR;
	}
	if(transdtl.status[0]!=DTLSTATUS_INIT)
	{
		ERRTIP("交易流水表状态错误");
		return E_COMMON_ERR;
	}
	des2src(trans.opercode,transdtl.opercode);
	trans.termid=transdtl.termid;
	trans.termseqno=transdtl.termseqno;
	trans.cardflag=0;
	trans.usecardflag=0;	
	trans.transcode=transdtl.transcode;
	trans.cardno=transdtl.cardno;	
	trans.purseno=transdtl.purseno;
	trans.paycnt=transdtl.cardcnt;
	trans.cardbefbal=transdtl.cardbefbal;
	trans.cardaftbal=transdtl.cardaftbal;
	trans.inputamt= transdtl.amount;	
	trans.unusedamt = trans.inputamt;
	
	T_t_card tOutCard;
	memset(&tOutCard,0,sizeof(tOutCard));

	T_t_card tInCard;
	memset(&tInCard,0,sizeof(tInCard));

	ret=DB_t_card_read_by_cardno(trans.cardno,&tOutCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else
			return E_DB_CARD_R;
	}
	ret=DB_t_card_read_by_cardno(rPack->lvol2,&tInCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,rPack->lvol2);
		else
			return E_DB_CARD_R;
	}
	trans.feetype=tOutCard.feetype;
	trans.custid=tOutCard.custid;
//	trans.cardaftbal=trans.cardbefbal;
	strcpy(ats.trans.draccno,tOutCard.accno);
	strcpy(ats.trans.craccno,tInCard.accno);
	
	ret=ats.doTrans();
	if(ret)
		return ret;
	ret=ats.doTransEnd();
	if(ret)
		return ret;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_update_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_U;
	}
	tRefno.status=RS_SUCC;
	des2src(tRefno.lastsaved,trans.sysdatetime);
	ret=DB_t_refno_update_by_refno(tRefno.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_U;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//记录转入卡的卡交易流水	
	ats.Reset();
	trans.termid=transdtl.termid;
	trans.dpscnt=rPack->lvol3+1;
	trans.cardbefbal=rPack->lsafe_level/100.0;
	trans.cardaftbal=(rPack->lvol1+rPack->lsafe_level)/100.0;
	trans.cardno=atoi(transdtl.voucherno);
	if(trans.cardno!=rPack->lvol2)
	{
		ERRTIP("收款卡号不符");
		return E_COMMON_ERR;
	}
	ret=GetCustBaseInfoByCustID(tInCard.custid,trans.custname,trans.stuempno,trans.remark);
	if(ret)
		return ret;
	ret=ats.GetTermSeqno();
	if(ret)
	{
		return ret;
	}
	T_t_transdtl transdtl2;
	memset(&transdtl2,0,sizeof(transdtl2));
	des2src(transdtl2.refno,transdtl.refno);
	des2src(transdtl2.transdate,transdtl.transdate);
	des2src(transdtl2.transtime,transdtl.transtime);
	strcpy(transdtl2.accdate,transdtl.accdate);
	strcpy(transdtl2.acctime,transdtl.acctime);
	transdtl2.termid=trans.termid;
	transdtl2.termseqno=trans.termseqno;
	transdtl2.transcode=transdtl.transcode;
	sprintf(transdtl2.voucherno,"%d",transdtl.cardno);
	transdtl2.cardno=trans.cardno;
	transdtl2.purseno=trans.purseno;
	transdtl2.transflag =TF_DPS;
	transdtl2.cardcnt=trans.dpscnt;
	transdtl2.cardbefbal=trans.cardbefbal;
	transdtl2.cardaftbal=trans.cardaftbal;
	transdtl2.amount= transdtl.amount;
	transdtl2.managefee=0;
	transdtl2.custid=tInCard.custid;
	des2src(transdtl2.custname,trans.custname);
	des2src(transdtl2.opercode,trans.opercode);
	transdtl2.status[0]=DTLSTATUS_SUCCESS;
	des2src(transdtl2.showcardno,tInCard.showcardno);
	des2src(transdtl2.stuempno,trans.stuempno);
	transdtl2.exttype=EXTTYPE_OPPSNO;	
	des2src(transdtl2.extdata,transdtl.stuempno);
	sprintf(transdtl2.remark,"由(%s)转出",transdtl.custname);
	ret=DB_t_transdtl_add(&transdtl2);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_TRANSDTL_E;
	  else
		return E_DB_TRANSDTL_I;
	}		
	T_t_account OutAccount;
	memset(&OutAccount,0,sizeof(OutAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(tOutCard.accno,&OutAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tOutCard.accno);
		else
			return E_DB_ACCOUNT_R;
	}
	OutAccount.paycnt=transdtl.cardcnt;
	OutAccount.cardbal=transdtl.cardaftbal;
	strcpy(OutAccount.transtime,trans.transtime);
	ret=DB_t_account_update_lock_by_c0(&OutAccount);
	if(ret)
	{
		writelog(LOG_ERR,"更新付款方账户表错误ret=%d",ret);
		return E_DB_ACCOUNT_U;
	}

	T_t_account InAccount;
	memset(&InAccount,0,sizeof(InAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(tInCard.accno,&InAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tInCard.accno);
		else
			return E_DB_ACCOUNT_R;
	}
	InAccount.dpscnt=transdtl2.cardcnt;
	InAccount.cardbal=transdtl2.cardaftbal;
	strcpy(InAccount.transtime,trans.transtime);
	ret=DB_t_account_update_lock_by_c0(&InAccount);
	if(ret)
	{
		writelog(LOG_ERR,"更新收款方账户表错误ret=%d",ret);
		return E_DB_ACCOUNT_U;
	}
	outPack->lvol0=transdtl.cardno;
	outPack->lvol2=transdtl2.cardno;
	outPack->lvol1=D4U5(transdtl.amount*100,0);
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);	
	outPack->lsafe_level2=D4U5(transdtl2.cardaftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=transdtl.termid;
	outPack->lserial1=transdtl.termseqno;
	des2src(outPack->sphone3,transdtl.refno);
	des2src(outPack->vsmess,trans.remark);
	
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
//写卡异常处理
static int WriteCardExcept(ST_PACK *rPack)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
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
	T_t_transdtl transdtl;

	memset(&transdtl,0,sizeof(transdtl));

	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_U;
	}
	if(transdtl.status[0]!=DTLSTATUS_SUCCESS)
		transdtl.status[0]=DTLSTATUS_FAIL;
	transdtl.errcode = 2;
	strcpy(transdtl.remark,"中途拔卡,写卡失败");
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		return E_DB_TRANSDTL_U;
	}
	return 0;
}
int F846328(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
		case 3://写卡失败
			ret=WriteCardExcept(rPack);
			break;
		default:
			ERRTIP("交易标志错误");
			return E_COMMON_ERR;
	}
	return ret;
}

