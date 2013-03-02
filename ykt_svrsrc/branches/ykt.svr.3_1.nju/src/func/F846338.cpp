/* --------------------------------------------
 * 创建日期: 2008-07-10
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户密码重置
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

int CheckIdno(char *idtype,char *idno,int custid)
{
	//核对证件
	T_t_customer customer;
	memset(&customer,0,sizeof(customer));
	int ret=DB_t_customer_read_by_custid(custid,&customer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CUSTOMER;
		else
			return E_DB_CUSTOMER_R;
	}
	if(strlen(customer.idno))
	{
		if(strlen(customer.idtype))
		{
			if(customer.idtype[0]!=idtype[0])
				return E_DIFF_IDTYPE;
		}
		if(strcmp(customer.idno,idno)!=0)
		{
			return E_DIFF_IDNO;
		}
	}
	return 0;
}
int F846338(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	des2src(pAccTrans->trans.opercode,rPack->semp);
	pAccTrans->trans.transcode=TC_EACCPWDRESET;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=pAccTrans->trans;
	char idtype[2]="";
	char idno[61]="";
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);

	char newpwd_crypt[65]="";
	char inpwd_plain[65]="";
	char seedkey[65]="";
	des2src(newpwd_crypt,rPack->snote2);
	if(!strlen(newpwd_crypt))
		 return E_PWD_NULL;
	ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,newpwd_crypt,inpwd_plain);
	if(ret)
	{
		writelog(LOG_ERR,"oldpwd[%s]",newpwd_crypt);
		return E_PWD_DECRYPT;	//去帐户信息
	}
	
	des2src(idtype,rPack->smarket_code2);
	des2src(idno,rPack->semail2);
	des2src(trans.eaccno,rPack->sbank_acc);
	if(!strlen(trans.eaccno))
		return E_INPUTNULL_ACCNO;

	//取帐户信息
	T_t_netacc eaccount;	
	memset(&eaccount,0,sizeof(eaccount));
	ret=DB_t_netacc_read_lock_by_c0_and_accno(trans.eaccno,&eaccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	if(eaccount.status[0]!=STATUS_NORMAL)
	{
		DB_t_netacc_free_lock_by_c0();
		return E_EACCNO_LOGOUT;
	}
	ret=CheckIdno(idtype,idno,eaccount.custid);
	if(ret)
	{
		DB_t_netacc_free_lock_by_c0();
		return ret;
	}
	des2src(eaccount.accpwd,newpwd_crypt);
	ret=DB_t_netacc_update_lock_by_c0(&eaccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else 
			return E_DB_ACCOUNT_U;
	}
	SetCol(handle,F_SDATE3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);	
	des2src(outPack->sdate3,pAccTrans->trans.accdate);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	sprintf(outPack->vsmess,"客户[%s]的电子账户密码重置成功",eaccount.accname);
	des2src(trans.remark,outPack->vsmess);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

