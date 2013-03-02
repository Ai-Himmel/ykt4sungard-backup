/* --------------------------------------------
 * 程序名称: F849004.c
 * 创建日期: 2006-7-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 绑定商户
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

int F849004(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int tx_code = 0;
	T_t_tradecode_shop tTradecodeShop;
	T_t_cif_shop tShop;

	memset(&tShop,0,sizeof tShop);
	memset(&tTradecodeShop,0,sizeof tTradecodeShop);

	tx_code = in_pack->lvol0;
	
	ret = DB_t_cif_shop_read_by_shop_id(in_pack->lvol1,&tShop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_SHOP_N;
		else
			*pRetCode = E_DB_SHOP_R;
		goto L_RETU;
	}

	if(strncmp(tShop.is_leaf,TYPE_YES,1)!=0)
	{
		*pRetCode = E_SHOP_ACTNO_NOT_EXIST;
		goto L_RETU;
	}

	ret = DB_t_tradecode_shop_read_lock_by_c1_and_trade_code(tx_code,&tTradecodeShop);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			*pRetCode = E_DB_TRADECODE_SHOP_R;
			goto L_RETU;
		}
		tTradecodeShop.trade_code = tx_code;
		tTradecodeShop.shop_id = tShop.shop_id;
		ret = DB_t_tradecode_shop_add(&tTradecodeShop);
		if(ret)
		{
			*pRetCode = E_DB_TRADECODE_SHOP_I;
			goto L_RETU;
		}
	}
	else
	{
		tTradecodeShop.shop_id = tShop.shop_id;
		ret = DB_t_tradecode_shop_update_lock_by_c1_and_trade_code(&tTradecodeShop);
		if(ret)
		{
			*pRetCode = E_DB_TRADECODE_SHOP_U;
			goto L_RETU;
		}
		DB_t_tradecode_shop_free_lock_by_c1();
	}
	return 0;
L_RETU:
	return -1;
}

