/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户销户
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

static int doAccount(TRANS& trans,char *cardaccno)
{
	int ret=0;
	T_t_account tCardAccount;

	memset(&tCardAccount,0,sizeof(tCardAccount));

	ret=DB_t_account_read_lock_by_c0_and_accno(cardaccno,&tCardAccount);
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
	if(amtcmp(tCardAccount.balance,0)!=0)
	{
		writelog(LOG_ERR,"balance[%d]",tCardAccount.balance);
		DB_t_account_free_lock_by_c0();
		return E_CARDACC_BALANCE_NOZERO;
	}
	tCardAccount.status[0]=STATUS_LOGOUT;
	strcpy(tCardAccount.closedate,trans.transdate);
	ret=DB_t_account_update_lock_by_c0(&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_ACCOUNT_U;

	}
	return 0;
}
static int doCustomer(int custid,T_t_customer& tCustomer)
{
	int ret=0;
	ret=DB_t_customer_read_lock_by_cur_and_custid(custid,&tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.status[0]!=STATUS_NORMAL)
		return E_CUSTOMER_LOGOUT;
	tCustomer.eaccflag[0]='0';
	getfmtsysdatetime(tCustomer.lastsaved);
	ret=DB_t_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_U;
	}
	return 0;
}

int F846332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";


	int custid=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

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
	pAccTrans->trans.transcode=TC_EACCCLOSE;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;

	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	//去帐户信息
	T_t_account tCardAccount;	
	memset(&tCardAccount,0,sizeof(tCardAccount));
	ret=DB_t_account_read_by_accno(accno,&tCardAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_CARDACCOUNT_R;
	}
	if(tCardAccount.status[0]!=STATUS_NORMAL)
	{
		return E_CARDACC_LOGOUT;
	}	
	char key[17]="";
	char accpwd_plain[33]="";
	char accpwd_crypt[33]="";
	strcpy(key,STATIC_SEED_KEY);
	des2src(accpwd_plain,rPack->scust_limit);
	EncodePwd(key,accpwd_plain,accpwd_crypt, 0);
	if(strcmp(tCardAccount.accpwd,accpwd_crypt)!=0)
		return E_EACCPWD;
		//检查客户
	T_t_customer tCustomer;
	memset(&tCustomer,0,sizeof(tCustomer));
	ret=doCustomer(tCardAccount.custid,tCustomer);
	if(ret)
		return ret;
	//	创建账号
	pAccTrans->trans.custid=tCardAccount.custid;
	strcpy(pAccTrans->trans.dbaccno,tCardAccount.accno);
	pAccTrans->trans.inputamt=tCardAccount.balance;
	ret=pAccTrans->doMainTrans();
	if(ret)
		return ret;	
	//注销帐户
	ret=doAccount(trans,accno);
	if(ret)
		return ret;
	SetCol(handle,F_LVOL0,F_LVOL8,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	strcpy(outPack->vsmess,"销户成功");
	strcat(outPack->vsmess,pAccTrans->remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

