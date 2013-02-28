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
			return E_NOTEXIST_CUSTOMER;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.status[0]==STATUS_DELETE)
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
	des2src(tCustomer.lastsaved,CAccTrans::GetInst().hostdatetime);
	ret=DB_t_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CUSTOMER;
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

	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_EACCOPEN;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;

	char accpwd_crypt[65]="";
	char seedkey[65]="";
	char inpwd_plain[65]="";
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	memset(&aPack,0,sizeof(aPack));
	
	ResetNormalCPack(&aPack,0,1);		
	SetCol(handle,0);
	
	des2src(accpwd_crypt,rPack->snote2);
	if(!strlen(accpwd_crypt))
		return E_PWD_NULL;

	ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,accpwd_crypt,inpwd_plain);
	if(ret)
	{
		writelog(LOG_ERR,"oldpwd[%s]",accpwd_crypt);
		return E_PWD_DECRYPT;	//去帐户信息
	}
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
//	strcpy(key,STATIC_SEED_KEY);
//	EncodePwd(key,accpwd_plain,accpwd_crypt, 0);

	//先查找该客户是否存在电子钱包帐户，如果存在，直接修改状态.
//	创建账号
	T_t_netacc tEAccount;
	memset(&tEAccount,0,sizeof(tEAccount));

	ret=DB_t_netacc_read_by_custid(tCustomer.custid,&tEAccount);
	if(ret)
	{
		if(DB_NOTFOUND!=ret)
			return E_DB_ACCOUNT_R;	
		ret = GetNewNetAccno(tEAccount.accno);												//获得最大帐号
		if (ret)
		{
			return ret;
		}
		des2src(tEAccount.accname,tCustomer.custname);
		des2src(tEAccount.subjno,SUBJECT_ESAVING);
		des2src(tEAccount.accpwd,accpwd_crypt);
		tEAccount.custid=tCustomer.custid;
		tEAccount.status[0]=STATUS_NORMAL;
		getsysdate(tEAccount.lasttransdate);
		getsysdate(tEAccount.opendate);
		tEAccount.stoppayflag[0]='0';
//		tEAccount.acctype=ACCTYPE_EACC;		
		ret=DB_t_netacc_add(&tEAccount);
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
		if(tEAccount.status[0]!=STATUS_DELETE)
			return E_CUST_EACC_OPENED;
		tEAccount.stoppayflag[0]='0';		
		tEAccount.status[0]=STATUS_NORMAL;
		getsysdate(tEAccount.opendate);
		tEAccount.closedate[0]=0;
		ret=DB_t_netacc_update_by_accno(tEAccount.accno,&tEAccount);
		if(ret)
		{
			return E_DB_ACCOUNT_U;
		}
	}
	SetCol(handle,F_SDATE3,F_LWITHDRAW_FLAG,F_LSERIAL1,F_SEMP,F_VSMESS,0);	
	outPack->lvol1=tCustomer.custid;
	des2src(outPack->sdate3,ats.trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"客户[%s]电子钱包开户成功",tEAccount.accname);
	des2src(trans.remark,outPack->vsmess);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
