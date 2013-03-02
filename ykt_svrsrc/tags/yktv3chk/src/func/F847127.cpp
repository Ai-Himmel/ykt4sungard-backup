/* --------------------------------------------
 * 程序名称: F847127.c
 * 创建日期: 2005-11-18
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 手工借-手工贷
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"

int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char dbaccno[21]="";
	char craccno[21]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	if(amtcmp(rPack->damt0,0)==0)
	{
		return E_INPUT_AMT_NULL;
	}
	des2src(dbaccno,rPack->sbank_acc);
	des2src(craccno,rPack->sbank_acc2);
	
	if(!strlen(dbaccno))
		return E_NO_DBACCNO;
	if(!strlen(craccno))
		return E_NO_CRACCNO;
	if(strcmp(dbaccno,craccno)==0)
	{
		return E_INPUT_2ACTNO_EQ;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(rPack->scust_limit)==0)
	{
		return E_INPUT_OPER_NULL;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		return E_INPUT_OPER_NULL;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper1[%s]oper2[%s]",rPack->scust_limit,rPack->scust_limit2);
		return E_INPUT_2OPER_EQ;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			return E_INPUT_OPER_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			return E_INPUT_OPER_PWD;
		else
			return ret;
	}

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->scust_limit);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_MANUALDRCR;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	//去帐户信息
	T_t_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_account_read_by_accno(dbaccno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else 
			return E_DB_CARDACCOUNT_R;
	}
	if(tAccount.status[0]!=STATUS_NORMAL)
	{
		return E_EACCNO_LOGOUT;
	}
	//	创建账号
	pAccTrans->trans.custid=tAccount.custid;
	strcpy(pAccTrans->trans.craccno,dbaccno);
	strcpy(pAccTrans->trans.craccno,craccno);
	pAccTrans->trans.inputamt=rPack->damt0;
	if(!pAccTrans->trans.inputamt)
		return E_INPUT_AMT_NULL;
	pAccTrans->trans.fundtype=0;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;	
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

