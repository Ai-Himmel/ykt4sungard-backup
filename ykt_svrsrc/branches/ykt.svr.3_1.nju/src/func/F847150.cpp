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
#include "acctrans.h"
#include "busqc.h"


int F847150(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret =0;
	char accno[21]="";
	char accflag=0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_SBANKNAME,0);
	des2src(accno,rPack->sbank_acc);
	if(strlen(accno)<10)
	{
		accflag=ACCFLAG_INNER;
	}
	else
	{
		if('1'==accno[0])
			accflag=ACCFLAG_CARD;
		else if('2'==accno[0])
			accflag=ACCFLAG_SHOP;
		else if('3'==accno[0])
			accflag=ACCFLAG_EACC;
		else
		{
			return ERRINFO(E_NOTEXIST_ACCNO,accno);
		}
	}
	switch(accflag)
	{
		case ACCFLAG_CARD:
		{
			T_t_account  tAccount;
			memset(&tAccount,0,sizeof(tAccount));
			ret=DB_t_account_read_by_accno(accno, &tAccount);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					return ERRINFO(E_NOTEXIST_CARDACCNO,accno);
				else
					return E_DB_ACCOUNT_R;
			}
			strcpy(out_pack->sbankname,tAccount.accname);
		}
		break;
		case ACCFLAG_SHOP:
		{
			T_t_shopacc  tShopAcc;
			memset(&tShopAcc,0,sizeof(tShopAcc));
			ret=DB_t_shopacc_read_by_accno(accno, &tShopAcc);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					return ERRINFO(E_NOTEXIST_SHOPACCNO,accno);
				else
					return E_DB_ACCOUNT_R;
			}
			strcpy(out_pack->sbankname,tShopAcc.accname);
		}
		break;
		case ACCFLAG_EACC:
		{
			T_t_netacc  tNetAcc;
			memset(&tNetAcc,0,sizeof(tNetAcc));
			ret=DB_t_netacc_read_by_accno(accno, &tNetAcc);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					return ERRINFO(E_NOTEXIST_EACCNO,accno);
				else
					return E_DB_ACCOUNT_R;
			}
			strcpy(out_pack->sbankname,tNetAcc.accname);
		}
		break;
		case ACCFLAG_INNER:
		{
			T_t_inneracc  tInnerAcc;
			memset(&tInnerAcc,0,sizeof(tInnerAcc));
			ret=DB_t_inneracc_read_by_accno(accno, &tInnerAcc);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					return ERRINFO(E_NOTEXIST_INNERACCNO,accno);
				else
					return E_DB_ACCOUNT_R;
			}
			strcpy(out_pack->sbankname,tInnerAcc.accname);
		}
		break;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

