/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能:充值商户存款
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

int F843351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;	
	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
		return ret;
	des2src(trans.opercode,rPack->semp);	
	trans.transcode=TC_SHOPSAVING;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;
	char accno[21]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);

	trans.shopid=rPack->lvol0;
	double depositamt=rPack->damt0;
	
	if(trans.shopid<1||amtcmp(depositamt,0)<=0)
	{
		return E_INPUT_DATA_INVAILD;
	}
	T_t_shop shop;

	memset(&shop,0,sizeof(shop));
	ret=DB_t_shop_read_lock_by_c0_and_shopid(trans.shopid,&shop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_SHOP_N;
		else
			return E_DB_SHOP_R;
	}
	if(shop.status[0]=='2')
	{
		DB_t_shop_free_lock_by_c0();
		return ERRINFO(E_SHOP_LOGOUT,shop.shopid);
	}
	double discount_amt=D4U5(depositamt*shop.depositagio);
	shop.depositamt+=depositamt;
	shop.depositcnt++;
	shop.discountamt+=discount_amt;
	ret=DB_t_shop_update_lock_by_c0(&shop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_SHOP_N;
		else
			return E_DB_SHOP_U;
	}	
	//检查客户
	//去帐户信息
	T_t_shopacc tShopAccount;	
	memset(&tShopAccount,0,sizeof(tShopAccount));
	ret=DB_t_shopacc_read_by_accno(shop.accno,&tShopAccount);
	if(ret)
	{
		writelog(LOG_ERR,"shopid[%d]",trans.shopid);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_SHOPACCNO,shop.accno);
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tShopAccount.status[0]!=STATUS_NORMAL)
	{
		return E_SHOPACC_LOGOUT;
	}
	pAccTrans->trans.custid=0;
	strcpy(trans.shopaccno,tShopAccount.accno);
	strcpy(trans.craccno,tShopAccount.accno);
	trans.inputamt=depositamt;
	trans.transamt=trans.inputamt;
	trans.fundtype=rPack->lvol9;
	des2src(trans.voucherno,rPack->scust_auth2);
	trans.transtype=TRANSTYPE_DEPOSITSHOPSAV;
	ret=pAccTrans->DoTransByTransType();
	if(ret)
		return ret; 	
	if(amtcmp(discount_amt,0)>0)
	{
		strcpy(pAccTrans->trans.craccno,tShopAccount.accno);
		trans.inputamt=discount_amt;
		trans.fundtype=0;
		trans.transamt=trans.inputamt;
		trans.transtype=TRANSTYPE_DEPOSITSHOPSAVDISCNT;
		ret=pAccTrans->DoTransByTransType();
		if(ret)
			return ret; 	
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));

	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.sysdate);
	strcpy(transdtl.acctime,trans.systime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=rPack->lvol9;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	des2src(transdtl.voucherno,trans.voucherno);
	des2src(transdtl.custname,shop.shopname);
	des2src(transdtl.opercode,trans.opercode);
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}
	sprintf(trans.remark,"商户[%s]存入%.2lf元提成金额%.2lf余额%.2lf",tShopAccount.accname,depositamt,discount_amt,trans.craccaftbal);
	SetCol(handle,F_SDATE3,F_LWITHDRAW_FLAG,F_LSERIAL1,F_SORDER0,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL0,F_VSVARSTR0,F_VSMESS,0);
	des2src(outPack->sdate3,trans.sysdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	outPack->damt0=depositamt;
	outPack->damt1=discount_amt;
	outPack->damt2=pAccTrans->trans.craccaftbal;
	outPack->lvol0=shop.shopid;
	des2src(outPack->vsvarstr0,shop.shopname);
	des2src(outPack->sorder0,trans.transdate);
	
	sprintf(outPack->vsmess,"%s %s 帐户余额%.2f元",tShopAccount.accname,pAccTrans->remark.c_str(),pAccTrans->trans.craccaftbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
