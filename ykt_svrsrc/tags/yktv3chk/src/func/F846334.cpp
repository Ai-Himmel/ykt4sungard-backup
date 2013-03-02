/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户取款
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

int F846334(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";

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

	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	//去帐户信息
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(accno,&tCardAccount);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",accno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_CARDACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return E_EACCNO_LOGOUT;
	}	
	char key[17]="";
	char accpwd_plain[33]="";
	char accpwd_crypt[33]="";
	strcpy(key,STATIC_SEED_KEY);
	des2src(accpwd_plain,rPack->scust_limit);
	EncodePwd(key,accpwd_plain,accpwd_crypt, 0);
	if(strcmp(tCardAccount.accpwd,accpwd_crypt)!=0)
		return E_EACCPWD;
	if(tCardAccount.stoppayflag[0]=='1')
		return E_EACC_STOPPAY;
	pAccTrans->trans.inputamt=rPack->damt0;
	if(!pAccTrans->trans.inputamt)
		return E_INPUT_AMT_NULL;
	if(pAccTrans->trans.inputamt>tCardAccount.balance)
		return E_BALANCE_SHORTAGE;
	//	创建账号
	pAccTrans->trans.custid=tCardAccount.custid;
	strcpy(pAccTrans->trans.dbaccno,accno);
	pAccTrans->trans.fundtype=0;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;	
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"%s %s 帐户余额:%.2f元",tCardAccount.accname,pAccTrans->remark.c_str(),pAccTrans->trans.dbaccbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

