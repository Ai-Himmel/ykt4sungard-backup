/* --------------------------------------------
 * 程序名称: F700001.sqc
 * 创建日期: 2005-05-16
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 电话查询余额
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

int F700001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_no=0;
	T_t_aif_account  tAccount;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tAccount,0,sizeof(tAccount));
	ResetNormalCPack(&aPack,0,1);

	card_no=rPack->lvol3;
	if(card_no<1)
	{
		*pRetCode=E_CARDNO_NOT_EXIST;
		goto L_RETU;
	}
	SetCol(handle,0);
 	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,0);
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_no, 0,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"card_no[%d]",card_no);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_NOT_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	out_pack->damt0=D4U5(tAccount.cur_bala,2);
	out_pack->damt1=D4U5(tAccount.cur_freebala,2);
	out_pack->damt2=D4U5(tAccount.cur_frozebala,2);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
