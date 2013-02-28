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
#include "transfunc.h"
#include "interfacefunc.h"
#include "payment.h"

int F850010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	ats.trans.transcode=TC_WATERTRANS;
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.termid=rPack->lwithdraw_flag;
	ret=ats.InitTrans();
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
	T_t_pursetype  pursetype;

	memset(&pursetype,0,sizeof(pursetype));

	pursetype.pursetype=rPack->lbank_acc_type;
	if(pursetype.pursetype<1)
	{
		ERRTIP("请输入小钱包类型");
		return E_COMMON_ERR;
	}
	ret=DB_t_pursetype_read_by_pursetype(pursetype.pursetype,&pursetype);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{	
			ERRTIP("钱包类型[%d]不存在",pursetype.pursetype);
			return E_COMMON_ERR;
		}
		else
			return E_DB_PURSETYPE_R;
	}
	if(!pursetype.enableflag)
	{
		ERRTIP("钱包类型[%d]未启用",pursetype.pursetype);
		return E_COMMON_ERR;
	}
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.cardno=rPack->lvol0;	
	trans.calccardbalflag=1;
	trans.transflag=TF_PAY;
	ats.SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
	trans.aftpaycnt++;
	des2src(trans.cardphyid,rPack->sstation1);
	trans.inputamt= D4U5(rPack->lvol5/100.0);	
	trans.transamt=trans.inputamt;
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
	if(amtcmp(wateraftbal,pursetype.pursemaxbal)>0)
		return ERRINFO(E_AMT_EXCEED_MAX,pursetype.pursemaxbal);
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));

	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	
	ret=ats.CheckAcc(&tCard,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"检查状态失败");
		return ret;
	}	
	T_t_cardbalance  cardbalance;

	memset(&cardbalance,0,sizeof(cardbalance));
	ret=DB_t_cardbalance_read_lock_by_c0_and_accno_and_pursetype(tAccount.accno,pursetype.pursetype,&cardbalance);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			des2src(cardbalance.accno,tAccount.accno);
			cardbalance.pursetype=pursetype.pursetype;
			cardbalance.cardno=trans.cardno;
			cardbalance.balance=wateraftbal;
			cardbalance.cardbal=cardbalance.balance;
			//cardbalance.dpscnt=rPack->lvol3;
			des2src(cardbalance.transdate,trans.transdate);
			des2src(cardbalance.transtime,trans.transtime);
			cardbalance.accumdpsamt = cardbalance.balance;
			ret=DB_t_cardbalance_add(&cardbalance);
			if(ret)
			{
				return E_DB_CARDBALANCE_I;
			}
		}
		else
		{
			return E_DB_CARDBALANCE_R;
		}
	}
	else
	{
		cardbalance.cardbal=D4U5(cardbalance.cardbal+trans.inputamt);
		cardbalance.balance=D4U5(cardbalance.balance+trans.inputamt);
		cardbalance.accumdpsamt = D4U5(cardbalance.accumdpsamt+trans.inputamt);
		des2src(cardbalance.transdate,trans.transdate);
		des2src(cardbalance.transtime,trans.transtime);
//			cardbalance.dpscnt=rPack->lvol3+1;
		ret=DB_t_cardbalance_update_lock_by_c0(&cardbalance);
		if(ret)
		{
			return E_DB_CARDBALANCE_U;
		}
	}
	if(pursetype.onlineflag)
	{
		//联机水控充值
		ats.trans.transcode=TC_WATERDEPOSIT;
		ats.trans.transtype=TRANSTYPE_WATERDEPOSIT;
		ret=ats.DoTransByTransType();
		if(ret)
			return ret;	
		ret=ats.doTransEnd();
		if(ret)
			return ret;
	}
	else
	{
		if(pursetype.shopid<1)
		{
			ERRTIP("钱包类型[%d]没有设置对应的水控商户",pursetype.pursetype);
			return E_COMMON_ERR;
		}
		//否则脱机水控
		int shoptype=0;
		char shopstatus[2]={0};
		ret=ShopAccReadbyShopid(pursetype.shopid,trans.shopaccno,&shoptype,shopstatus);
		if(ret)
		{
			writelog(LOG_ERR,"shopid[%d]",pursetype.shopid);
			return ret;
		}
		if(shopstatus[0]!=STATUS_NORMAL)
			return ERRIF_SHOP_CLOSE;
		if(shoptype!=SHOPTYPE_COSUMESHOP)
			return ERRIF_SHOP_TYPE;
		ats.trans.transtype=TRANSTYPE_WATERTRANS;
		ret=ats.DoTransByTransType();
		if(ret)
			return ret;	
		ret=ats.doTransEnd();
		if(ret)
			return ret;
	}
	ret=UpdateCardBitmap(trans.cardno,trans.aftpaycnt,CARDBITMAPTYPE_SYS_ONLINE);
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
	transdtl.cardcnt=trans.aftpaycnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.cardaftbal=trans.cardaftbal;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.custid=trans.custid;
	des2src(transdtl.custname,trans.custname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
    des2src(transdtl.showcardno,trans.showcardno);
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
	T_t_pursetransdtl pursetransdtl;
	memset(&pursetransdtl,0,sizeof(pursetransdtl));
	des2src(pursetransdtl.refno,transdtl.refno);
	des2src(pursetransdtl.transdate,transdtl.transdate);
	des2src(pursetransdtl.transtime,transdtl.transtime);
	strcpy(pursetransdtl.accdate,transdtl.accdate);
	strcpy(pursetransdtl.acctime,transdtl.acctime);
	pursetransdtl.termid=transdtl.termid;
	pursetransdtl.termseqno=transdtl.termseqno;
	pursetransdtl.transcode=transdtl.transcode;
	pursetransdtl.cardno=transdtl.cardno;
	pursetransdtl.pursetype=pursetype.pursetype;
	pursetransdtl.transflag= TF_DPS;
	pursetransdtl.cardcnt=cardbalance.dpscnt;
	pursetransdtl.cardbefbal=waterbefbal;
	pursetransdtl.cardaftbal=wateraftbal;
	pursetransdtl.amount=transdtl.amount;
	pursetransdtl.custid=transdtl.custid;
	des2src(pursetransdtl.custname,transdtl.custname);
	des2src(pursetransdtl.opercode,transdtl.opercode);
	pursetransdtl.status[0]=transdtl.status[0];
	des2src(pursetransdtl.showcardno,trans.showcardno);
	des2src(pursetransdtl.stuempno,transdtl.stuempno);
	ret=DB_t_pursetransdtl_add(&pursetransdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_PURSETRANSDTL_E;
	  else
		return E_DB_PURSETRANSDTL_I;
	}		
	outPack->lvol0=tCard.cardno;
	outPack->lvol5=rPack->lvol5;
	outPack->lvol8=D4U5(ats.trans.cardaftbal*100,0);
	outPack->lsafe_level=D4U5(wateraftbal*100,0);
	des2src(outPack->sdate3,ats.trans.accdate);
	des2src(outPack->stime3,ats.trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);
    sprintf(trans.remark,"%s卡余额%.2lf元",ats.remark.c_str(),ats.trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
