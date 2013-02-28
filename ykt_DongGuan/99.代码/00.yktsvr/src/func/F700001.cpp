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
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

int F700001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int cardno=0;
	T_t_account  tAccount;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tAccount,0,sizeof(tAccount));
	ResetNormalCPack(&aPack,0,1);

	cardno=rPack->lvol3;
	if(cardno<1)
	{
		return ERRINFO(E_NOTEXIST_CARDNO,cardno);
	}
	SetCol(handle,0);
 	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,0);

	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));
	ret=DB_t_card_read_by_cardno(cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,cardno);
		else 
			return E_DB_CARD_R;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,cardno);
	}	
	ret=DB_t_account_read_by_accno(tCard.accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDACCNO,tCard.accno);
		else
			return E_DB_ACCOUNT_R;
	}
	out_pack->damt0=D4U5(tAccount.balance,2);
	out_pack->damt1=D4U5(tAccount.availbal,2);
	out_pack->damt2=D4U5(tAccount.frozebal,2);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
