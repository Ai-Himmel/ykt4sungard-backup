/* --------------------------------------------
 * 程序名称: F847150.c
 * 创建日期: 2005-11-22
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 帐户名查询
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
#include "busqc.h"


int F847150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret =0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_SBANKNAME,0);
	if(!strlen(rPack->sbank_acc))
	{
		return E_INPUT_ACTNO_NULL;
	}
	T_t_account  tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_account_read_by_accno(rPack->sbank_acc, &tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	strcpy(out_pack->sbankname,tAccount.accname);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

