/* --------------------------------------------
 * 程序名称: F843354.cpp
 * 创建日期: 2004 10 28
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 充值商户信息修改
 * --------------------------------------------
 * 修改日期: 
 * 修改人员: 
 * 修改描述: 
 * 版本信息: 
 * 备注信息: 
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
#include "fdsqc.h"


int F843354(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int    ret=0;
	int shop_id=0;
	T_t_deposit_shop	tDepositShop;
	T_t_aif_account     tAccount;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tDepositShop,0,sizeof(tDepositShop));	
	memset(&tAccount,0,sizeof(tAccount));	
	ResetNormalCPack(&aPack,0,1);

	shop_id=rPack->lvol0;
	
	ret=DB_t_deposit_shop_read_lock_by_cur_and_shop_id(shop_id,&tDepositShop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_SHOP_N;
		else
			*pRetCode=E_DB_DEPOSIT_SHOP_U;
		goto L_RETU;
	}
	if(tDepositShop.status[0]=='2')
	{
		DB_t_deposit_shop_free_lock_by_cur();
		*pRetCode=E_SHOP_ACTNO_NOT_EXIST;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt0,0)>0)
		tDepositShop.deposit_ratio=rPack->damt0/100.0;
	if(strlen(rPack->vsvarstr0))
	{
		des2src(tDepositShop.shop_name,rPack->vsvarstr0);
	}
	if(strlen(rPack->vsvarstr0))
	{
		des2src(tDepositShop.shop_man_name,rPack->sall_name);	
	}
	if(rPack->lvol1>0)
		tDepositShop.id_type=rPack->lvol1;
	if(strlen(rPack->snote))
	{
		des2src(tDepositShop.id_no,rPack->snote);	
	}
	ret=DB_t_deposit_shop_update_lock_by_cur(&tDepositShop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_SHOP_N;
		else
			*pRetCode=E_DB_DEPOSIT_SHOP_U;
		goto L_RETU;
	}	
	DB_t_deposit_shop_free_lock_by_cur();
	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(tDepositShop.account_id, &tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	des2src(tAccount.cut_name,tDepositShop.shop_name);
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		*pRetCode=E_DB_ACCOUNT_U;
		goto L_RETU;
	}
	DB_t_aif_account_free_lock_cur();
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	strcpy(out_pack->vsmess,"更新信息成功");
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
