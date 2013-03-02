/* --------------------------------------------
 * 程序名称: F843358.sqC
 * 创建日期: 2007-11-02
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 充值操作员添加
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

int F843358(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_deposit_oper tDepositOper;

	memset(&tDepositOper,0,sizeof(tDepositOper));

	//添加操作员
	des2src(tDepositOper.oper_code,rPack->scust_auth);
	tDepositOper.max_amt=rPack->damt0*100;
	tDepositOper.status[0]='1';
	des2src(tDepositOper.usedevlimit_flag,rPack->sstatus2);
	des2src(tDepositOper.shopoper_flag,rPack->sstatus3);	
	getsysdate(tDepositOper.open_date);
	getdatetime(tDepositOper.last_saved);
	ret=DB_t_deposit_oper_add(&tDepositOper);
	if(ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode=E_DB_DEPOSIT_OPER_E;
		else	
			*pRetCode=E_DB_DEPOSIT_OPER_I;
		goto L_RETU;
	}

	return 0;
L_RETU:
	return -1;
}
