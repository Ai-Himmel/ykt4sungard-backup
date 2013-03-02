/* --------------------------------------------
 * 程序名称: F847224.sqc
 * 创建日期: 2006-9-30
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  上大账务商户消费结算商户余额查询
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"


static int do_calc_shop_balance(int shop_id,double * balance)
{
	int ret;
	double free_bala = 0;
	int rows;
	T_v_cif_shop_tree shop_node;
	T_t_aif_account account;
	T_t_cif_shop shop;

	ret = DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(shop_id);
	if(ret)
	{
		writelog(LOG_ERR,"查询商户信息失败[%d]",ret);
		if(DB_NOTFOUND == 0)
			return E_SHOP_HAVE_SUB_NODE;
		else
			return E_DB_SHOP_R;
	}
	rows = 0;
	while(1)
	{
		memset(&shop_node,0,sizeof shop_node);
		ret = DB_v_cif_shop_tree_fetch_select_by_c1(&shop_node);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				else
					return E_FAN_SHOP_HAS_NO_LEAF;
			}
			return E_DB_SHOP_R;
		}
		rows++;
		memset(&shop,0,sizeof shop);
		ret = DB_t_cif_shop_read_by_shop_id(shop_node.leaf_id,&shop);
		if(ret)
		{
			DB_v_cif_shop_tree_close_select_by_c1();
			if(DB_NOTFOUND == ret)
				return E_DB_SHOP_N;
			else
				return E_DB_SHOP_R;
		}
		memset(&account,0,sizeof account);
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(
			shop.cut_id,ACCTYPE_SHOPMAIN,&account);
		if(ret)
		{
			DB_v_cif_shop_tree_close_select_by_c1();
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		free_bala += account.last_bala;
	}
	*balance = free_bala;
	return 0;
}

int F847224(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_cif_shop shop;
	int shop_id;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	writelog(LOG_DEBUG,"操作员[%s]",rPack->scard0);
	shop_id = atoi(rPack->sbank_acc);
	if(shop_id <= 0)
	{
		*pRetCode = E_SHOP_ACTNO_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		writelog(LOG_DEBUG,"检查操作员密码错误[%s]",rPack->scard0);
		*pRetCode = ret;
		goto L_RETU;
	}

	shop_id = strtoul(rPack->sbank_acc,NULL,10);
	memset(&shop,0,sizeof shop);
	ret =DB_t_cif_shop_read_by_shop_id(shop_id,&shop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_SHOP_N;
		else
			*pRetCode =  E_DB_SHOP_R;
		goto L_RETU;
	}

	if(strcmp(shop.is_indep,TYPE_YES))
	{
		*pRetCode = E_FAN_SHOP_NOT_INDEP;
		goto L_RETU;
	}
	
	SetCol(handle,0);
	SetCol(handle,F_DAMT1,0);

	ret = do_calc_shop_balance(shop.shop_id,&(out_pack->damt1));
	if(ret)
	{
		writelog(LOG_DEBUG,"计算商户余额错误shopid[%d]",shop.shop_id);
		*pRetCode = ret;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
L_RETU:
	return -1;
}