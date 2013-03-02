#if 0
int F843351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int shop_id=0;
	double deposit_amt=0;
	double discount_amt=0;
	double dUniqno=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_deposit_shop	shop;
	T_t_aif_account	tAccount;
	T_t_tif_tradeserial  tradeserial;
	InAcc	IA;
	
	memset(&shop,0,sizeof(shop));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));

	ResetNormalCPack(&aPack,0,1);
	getsysdate(sysdate);
	getsystime(systime);

	shop_id=rPack->lvol0;
	deposit_amt=rPack->damt0;
	
	if(shop_id<1||amtcmp(deposit_amt,0)<0)
	{
		return E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	ret=GetLogicDate(logicdate);		//业务日期
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=DB_t_deposit_shop_read_lock_by_cur_and_shop_id(shop_id,&shop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSIT_SHOP_N;
		else
			return E_DB_DEPOSIT_SHOP_R;
		goto L_RETU;
	}
	if(shop.status[0]=='2')
	{
		DB_t_deposit_shop_free_lock_by_cur();
		return E_SHOP_CLOSE;
		goto L_RETU;
	}
	discount_amt=deposit_amt*shop.deposit_ratio;
	shop.deposit_total_amt+=deposit_amt;
	shop.deposit_total_cnt++;
	shop.discount_total_amt+=discount_amt;
	ret=DB_t_deposit_shop_update_lock_by_cur(&shop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSIT_SHOP_N;
		else
			return E_DB_DEPOSIT_SHOP_U;
		goto L_RETU;
	}	
	dUniqno=0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	des2src(tradeserial.oper_code,rPack->semp);							//操作员号
	tradeserial.maindevice_id=rPack->lvol10;										//工作站
	tradeserial.serial_no = D2I(dUniqno);											//流水号
	tradeserial.other_seri_no = 0;												//上传端流水号
	tradeserial.serial_type = TXCODE_DEPOSIT_SHOP_DEPOSIT;						//交易代码；备注：发卡+充值 用一个交易码，即847101； 发卡（不充值）另用一个交易码，即新的发卡程序文件名，从而区分发卡充值与发卡不充值的卡操作信息。
	tradeserial.serial_state = SERISTAT_DEBT;										//流水状态
	des2src(tradeserial.operate_date,sysdate);									//发生日期
	des2src(tradeserial.operate_time,systime);									//发生时间
	des2src(tradeserial.collect_date,sysdate);										//采集日期
	des2src(tradeserial.collect_time,systime);										//采集时间
	des2src(tradeserial.enteract_date,logicdate);									//处理日期
	des2src(tradeserial.enteract_time,systime);									//处理时间
	tradeserial.maindevice_id = rPack->lvol6;										//上传工作站标识
	tradeserial.device_id = rPack->lvol7;											//采集设备标识
	tradeserial.trade_fee=deposit_amt;
//		tradeserial.customer_id=tAccount.customer_id;											//客户号
	des2src(IA.sArrInActno[4],shop.account_id);							//帐户
	IA.iCardNo=0;
	IA.iFeeType=0;
	IA.dArrInAmt[0]=deposit_amt;
	IA.dArrInAmt[1]=discount_amt;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
		goto L_RETU;
	}
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}		

	ret=DB_t_aif_account_read_by_account_id( shop.account_id,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"ret[%d]account_id[%s]",ret,shop.account_id);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_SORDER0,F_SEMP,F_LSERIAL1,F_LVOL0,F_DAMT0,F_DAMT1,F_DAMT2,F_VSMESS,0);
	des2src(out_pack->sorder0,sysdate);
	des2src(out_pack->semp,tradeserial.oper_code);
	out_pack->lvol0=shop.shop_id;
	out_pack->lserial1=tradeserial.serial_no;
	out_pack->damt0=deposit_amt;
	out_pack->damt1=discount_amt;
	out_pack->damt2=tAccount.cur_bala;
	sprintf(out_pack->vsmess,"流水号%d,存款金额:%.2lf,提成金额%.2lf元,商户余额%.2lf元",tradeserial.serial_no,deposit_amt,discount_amt,tAccount.cur_bala);
	writelog(LOG_INFO,out_pack->vsmess);		
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
#endif
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

static int doAccount(TRANS& trans,char *cardaccno)
{
	int ret=0;
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c0_and_accno(cardaccno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_CARDACCOUNT_N;
		else
			return E_DB_CARDACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_LOGOUT;
	}
	if(tCardAccount.balance!=0)
	{
		writelog(LOG_ERR,"balance[%d]",tCardAccount.balance);
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_BALANCE_NOZERO;
	}
	if(tCardAccount.foregift!=0)
	{
		writelog(LOG_ERR,"foregift[%d]",tCardAccount.foregift);
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_FOREGIFT_NOZERO;
	}
	tCardAccount.status[0]=STATUS_LOGOUT;
	strcpy(tCardAccount.closedate,trans.transdate);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_CARDACCDTL_U;

	}
	return 0;
}
int F843351(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";

	int custid=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;	
	pAccTrans->clear();
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_SHOPSAVING;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	int shop_id=rPack->lvol0;
	int deposit_amt=rPack->damt0;
	
	if(shop_id<1||deposit_amt<=0)
	{
		return E_INPUT_DATA_INVAILD;
	}
	T_t_shop shop;

	memset(&shop,0,sizeof(shop));
	ret=DB_t_shop_read_lock_by_c0_and_shopid(shop_id,&shop);
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
		return E_SHOPACC_LOGOUT;
	}
	int discount_amt=deposit_amt*shop.depositagio;
	shop.depositamt+=deposit_amt;
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
	T_t_account tShopAccount;	
	memset(&tShopAccount,0,sizeof(tShopAccount));
	ret=DB_t_account_read_by_accno(shop.accno,&tShopAccount);
	if(ret)
	{
		writelog(LOG_ERR,"shop_id[%d]",shop_id);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_SHOPACCNO;
		else 
			return E_DB_SHOPACCOUNT_R;
	}
	if(tShopAccount.status[0]!=STATUS_NORMAL)
	{
		return E_SHOPACC_LOGOUT;
	}
	//	创建账号
	pAccTrans->trans.custid=0;
	strcpy(pAccTrans->trans.craccno,tShopAccount.accno);
	pAccTrans->trans.inputamt=rPack->damt0;
	if(!pAccTrans->trans.inputamt)
		return E_INPUT_AMT_NULL;
	pAccTrans->trans.fundtype=1;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;	
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"%s %s 帐户余额:%.2f元",tShopAccount.accname,pAccTrans->remark.c_str(),pAccTrans->trans.craccbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}


