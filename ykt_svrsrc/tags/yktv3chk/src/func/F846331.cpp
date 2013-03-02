/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通网络电子钱包开户
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
	if(tCustomer.status[0]==STATUS_LOGOUT)
	{
		DB_t_customer_free_lock_cur();
		return E_CUSTOMER_LOGOUT;
	}
	if(tCustomer.eaccflag[0]=='1')
	{
		DB_t_customer_free_lock_cur();
		return E_CUST_EACC_OPENED;
	}
	tCustomer.useflag[0]='1';
	tCustomer.eaccflag[0]='1';
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
static int doAccBook(TRANS& trans)
{

	return 0;
}
int F846331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret=0;
	char accpwd_plain[33]="";
	char accpwd_crypt[33]="";
	
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
	pAccTrans->trans.transcode=TC_EACCOPEN;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	
	des2src(accpwd_plain,rPack->scust_limit);


	//检查客户
	T_t_customer tCustomer;
	
	memset(&tCustomer,0,sizeof(tCustomer));
	tCustomer.custid=rPack->lvol1;
	if(!tCustomer.custid)
		return E_INPUTNULL_CUSTID;	
	ret=doCustomer(tCustomer.custid,tCustomer);
	if(ret)
		return ret;

	char key[17]="";
//	get_init_passwd_by_man_id(tCustomer.idno,accpwd);
	strcpy(key,STATIC_SEED_KEY);
	EncodePwd(key,accpwd_plain,accpwd_crypt, 0);

	//先查找该客户是否存在电子钱包帐户，如果存在，直接修改状态.
//	创建账号
	T_t_account tCardaccount;
	memset(&tCardaccount,0,sizeof(tCardaccount));

	ret=DB_t_account_read_by_custid_and_subjno(tCardaccount.custid,SUBJECT_ESAVING,&tCardaccount);
	if(ret)
	{
		if(DB_NOTFOUND!=ret)
			return E_DB_ACCOUNT_R;	
		ret = getNewActno(tCardaccount.accno);												//获得最大帐号
		if (ret)
		{
			return ret;
		}
		des2src(tCardaccount.accname,tCustomer.custname);
		des2src(tCardaccount.subjno,SUBJECT_ESAVING);
		des2src(tCardaccount.accpwd,accpwd_crypt);
		tCardaccount.custid=tCustomer.custid;
		tCardaccount.status[0]=STATUS_NORMAL;
		getsysdate(tCardaccount.lasttransdate);
		getsysdate(tCardaccount.opendate);
		tCardaccount.acctype=ACCTYPE_EACC;		
		ret=DB_t_account_add(&tCardaccount);
		if(ret)
		{
			if(DB_REPEAT==ret)
				return E_DB_ACCOUNT_E;
			else
				return E_DB_ACCOUNT_I;
		}	
	}
	else
	{
		if(tCardaccount.status[0]!=STATUS_LOGOUT)
			return E_CUST_EACC_OPENED;
		tCardaccount.status[0]=STATUS_NORMAL;
		ret=DB_t_account_update_by_accno(tCardaccount.accno,&tCardaccount);
		if(ret)
		{
			return E_DB_ACCOUNT_U;
		}
	}

	SetCol(handle,F_SDATE3,F_LWITHDRAW_FLAG,F_LSERIAL1,F_SEMP,F_VSMESS,0);	
	outPack->lvol1=tCustomer.custid;
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"开户成功,账号%s",tCardaccount.accno);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
