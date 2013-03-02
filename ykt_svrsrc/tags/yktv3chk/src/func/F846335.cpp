/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户止付、解付
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

int F846335(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";
	char stoppayflag[2]="";

	int custid=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_EACCDRAW;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	
	des2src(stoppayflag,rPack->sstatus1);
	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;

	//去帐户信息
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_lock_by_c0_and_accno(accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_account_free_lock_by_c0();
		return E_EACCNO_LOGOUT;
	}
	if(stoppayflag[0]=='1')
	{
		if(tCardAccount.stoppayflag[0]=='1')
		{			
			DB_t_account_free_lock_by_c0();
			return E_EACC_STOPPAY;
		}
		pAccTrans->trans.transcode=TC_EACCSTOPPAY;
	}
	else
	{
		if(tCardAccount.stoppayflag[0]=='0')
		{
			DB_t_account_free_lock_by_c0();
			return E_EACC_NO_STOPPAY;
		}
		pAccTrans->trans.transcode=TC_EACCUNSTOPPAY;
	}
	tCardAccount.stoppayflag[0]=stoppayflag[0];
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_CARDACCDTL_U;
	}
	SetCol(handle,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,"交易成功");
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

