/* --------------------------------------------
 * 程序名称: F846331.cpp
 * 创建日期: 2008 8 21
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 电子帐户开户
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
#include "fdsqc.h"

static int doCustomer(int custid,T_t_cif_customer& tCustomer)
{
	int ret=0;
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(custid,&tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state==CUSTSTAT_LOGOUT)
	{
		DB_t_cif_customer_free_lock_cur();
		return E_CUSTOMER_LOGOUT;
	}
	if(tCustomer.eaccflag[0]=='1')
	{
		DB_t_cif_customer_free_lock_cur();
		return E_CUST_EACC_OPENED;
	}
//	tCustomer.useflag[0]='1';
	tCustomer.eaccflag[0]='1';
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_U;
	}
	return 0;
}

int F846331(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	double dUniqno=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char key[17]="";
//	char accpwd_plain[33]="";
	char accpwd_crypt[65]="";

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_cif_customer  tCustomer;
	T_t_aif_account	tAccount;
	T_t_tif_tradeserial  tradeserial;
	
	 memset(&tCustomer,0,sizeof(tCustomer));
	 memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	des2src(accpwd_crypt,rPack->snote2);	//密码
	if(!strlen(accpwd_crypt))
		return E_INPUTNULL_PWD;
	tCustomer.cut_id=rPack->lvol1;				//客户号
	if(tCustomer.cut_id<1)
		return E_INPUTNULL_CUSTID;
	ret=doCustomer(tCustomer.cut_id,tCustomer);
	if(ret)
		return ret;

//	strcpy(key,STATIC_SEED_KEY);
//	EncodePwd(key,accpwd_plain,accpwd_crypt, 0);

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);		//业务日期
	if(ret)
		return ret;
	
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCustomer.cut_id, ACCTYPE_PEREACC, &tAccount);
	if(ret)
	{
		if(DB_NOTFOUND!=ret)
			return E_DB_ACCOUNT_R;	
		ret = getNewActno(tAccount.account_id);												//获得最大帐号
		if (ret)
		{
			return ret;
		}
		des2src(tAccount.cut_name,tCustomer.cut_name);
		des2src(tAccount.stuemp_no,tCustomer.stuemp_no);
		des2src(tAccount.password,accpwd_crypt);
		des2src(tAccount.subno,SUBJECT_ESAVING);
		des2src(tAccount.open_date,logicdate);
		des2src(tAccount.open_time,systime);
		tAccount.act_type=ACCTYPE_PEREACC;
		tAccount.customer_id=tCustomer.cut_id;
		tAccount.current_state=ACCOUNTSTAT_REGIST;
		tAccount.stoppayflag[0]='0';        
		ret=DB_t_aif_account_add(&tAccount);
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
		if(tAccount.current_state!=ACCOUNTSTAT_LOGOUT)
			return E_CUST_EACC_OPENED;
		tAccount.current_state=ACCOUNTSTAT_REGIST;
		des2src(tAccount.password,accpwd_crypt);
		des2src(tAccount.open_date,logicdate);
		des2src(tAccount.open_time,systime);
		strcpy(tAccount.close_date,"");
		strcpy(tAccount.close_time,"");
		tAccount.stoppayflag[0]='0';        
		ret=DB_t_aif_account_update_by_account_id(tAccount.account_id,&tAccount);
		if(ret)
		{
			return E_DB_ACCOUNT_U;
		}
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo ret [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dUniqno);											//流水号
	tradeserial.other_seri_no = 0;														//上传端流水号
	tradeserial.serial_type = TXCODE_EACC_OPEN;											//交易代码；
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	des2src(tradeserial.oper_code , rPack->semp);										//操作员代码
	tradeserial.customer_id=tAccount.customer_id;											//客户号
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}		
	
	SetCol(handle,F_LVOL1,F_LSERIAL1,F_VSMESS,0);	
	out_pack->lvol1=tCustomer.cut_id;
	out_pack->lserial1=tradeserial.serial_no;
	sprintf(out_pack->vsmess,"开户成功,账号%s",tAccount.account_id);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}		
		
