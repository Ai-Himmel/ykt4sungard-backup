/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户密码修改
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

int F846337(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_EACCPWDUPD;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;
	
	des2src(stoppayflag,rPack->sstatus1);
	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;

	char key[17]="";
	char pwd_plain[33]="";
	char newpwd_plain[33]="";
	char pwd_crypt[33]="";
	char newpwd_crypt[33]="";
	strcpy(key,STATIC_SEED_KEY);
	des2src(pwd_plain,rPack->scust_limit);
	EncodePwd(key,pwd_plain,pwd_crypt, 0);
	des2src(newpwd_plain,rPack->scust_limit2);
	EncodePwd(key,newpwd_plain,newpwd_crypt,0);
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
	if(strcmp(tCardAccount.accpwd,pwd_crypt)!=0)
		return E_EACCPWD;
	
	des2src(tCardAccount.accpwd,newpwd_crypt);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_U;
	}
	SetCol(handle,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
//	des2src(outPack->sdate3,trans.accdate);
//	des2src(outPack->semp,trans.opercode);
//	outPack->lwithdraw_flag=trans.termid;
//	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"%s的密码修改成功",tCardAccount.accname);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

