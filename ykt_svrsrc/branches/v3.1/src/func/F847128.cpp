/* --------------------------------------------
 * 程序名称: F847128.c
 * 创建日期: 2011-05-11
 * 程序作者: xlh
 * 版本信息: 1.0.0.0
 * 程序功能: 小钱包冲正
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
#include "interfacefunc.h"
#include "busqc.h"
int F847128(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char transdate[12]="";
	char devphyid[30]="";
	int devseqno=0;
	int cardno=0;
	int deviceid=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_MANUALDRCR;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	//水控消费
	T_t_purseposdtl purseposdtl;
	memset(&purseposdtl,0,sizeof purseposdtl);
	T_t_shop shop;
	memset(&shop,0,sizeof shop);
	T_t_account  account; 
	memset(&account,0,sizeof account);
	ResetNormalCPack(&aPack,0,1);
	des2src(transdate,rPack->sdate0);
	deviceid=rPack->lwithdraw_flag;
	devseqno=rPack->lserial1;
	cardno=rPack->lvol0;
	trans.inputamt=rPack->damt0;
	trans.unusedamt = trans.inputamt;
	trans.transamt=trans.inputamt;
	if(amtcmp(trans.inputamt,0)==0)
	{
		return E_INPUT_AMT_NULL;
	}	
	ret=DB_t_purseposdtl_read_lock_by_c1_and_transdate_and_termid_and_devseqno_and_cardno(transdate,deviceid,devseqno,cardno,&purseposdtl);
		if (ret)
		{
			if(DB_NOTFOUND==ret)
		           E_DB_PURSEPOSDTL_N;
		                else
		           return E_DB_PURSEPOSDTL_R;
		}
		if(!trans.cardaccno)
		{
				
		ret=GetShopidByDevphyid(purseposdtl.devphyid,purseposdtl.transdate,purseposdtl.transtime,deviceid,purseposdtl.shopid);
		if(ret)
			{
			  return ret;
			}
			}
		ret=DB_t_shop_read_by_shopid(purseposdtl.shopid,&shop);   
		if(ret)
			{
				writelog(LOG_ERR,"DB_t_shop_read_by_shop_id ret[%d],shopid[%d]",ret,rPack->lserial0);
				if(DB_NOTFOUND==ret)
				{
					return E_NOTEXIST_SHOPACCNO;
				}
				else
				return E_DB_SHOP_R;
			}
		ret=DB_t_account_read_by_cardno(cardno,&account);
		if (rPack->lvol1)
		{
			ret=DB_t_account_read_by_cardno(rPack->lvol1,&account);
			if(ret)
			{
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_R;
			}			
		 }
	des2src(trans.draccno,shop.accno);
	des2src(trans.craccno,account.accno);
	des2src(trans.chkopercode,rPack->semp_no);
	pAccTrans->trans.fundtype=0;
	pAccTrans->trans.transtype=TRANSTYPE_MANDRCR;
	ret=pAccTrans->DoTransByTransType();
	if(ret)
		return ret;	
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
		des2src(purseposdtl.status,"4");
	ret=DB_t_purseposdtl_update_lock_by_c1(&purseposdtl);
	if(ret)
		return ret;
	 DB_t_purseposdtl_free_lock_by_c1();
	sprintf(trans.remark,"交易金额%.2lf,借方账户[%s]余额%.2lf,贷方账户[%s]余额%.2lf",trans.totaltransamt,trans.draccname,trans.draccaftbal,trans.craccname,trans.craccaftbal);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lvol1=rPack->lvol1;
	outPack->lvol0=cardno;      //卡号
	outPack->lvol2=trans.transamt*100;//交易金额
	sprintf(outPack->vsmess,"%s 借方账户[%s]贷方帐户[%s]",pAccTrans->remark.c_str(),pAccTrans->trans.draccname,trans.craccname);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

