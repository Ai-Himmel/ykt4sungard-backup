/* --------------------------------------------
 * 创建日期: 2008 8 21
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


int F846337(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;

	char key[17]="";
	char in_oldpwd_plain[9]="";
	char db_oldpwd_plain[9]="";
	char oldpwd[65]="";
	char newpwd[65]="";
	char seedkey[33]="";
	des2src(oldpwd,rPack->snote);
	if(!strlen(oldpwd))
		return E_INPUTNULL_PWD;
	des2src(newpwd,rPack->snote2);
	if(!strlen(newpwd))
		return E_INPUTNULL_PWD;
	//取帐户信息
	ret=GetParameter(2006,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,oldpwd,in_oldpwd_plain);
	if(ret)
		return E_EACCPWD;
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		DB_t_aif_account_free_lock_cur();
		return E_EACCNO_LOGOUT;
	}
	ret=decrypt_elec_card_pwd(0,seedkey,tAccount.password,db_oldpwd_plain);
	if(ret)
	{
		writelog(LOG_ERR,"crypt ret[%d]:in_pwd[%s]db_pwd[%s],plain:in_pwd[%s]db_pwd[%s]",ret,oldpwd,tAccount.password,in_oldpwd_plain,db_oldpwd_plain);		
		return E_PWD_DECRYPT;
	}
	if(strcmp(in_oldpwd_plain,db_oldpwd_plain)!=0)
	{
		writelog(LOG_ERR,"crypt:in_pwd[%s]db_pwd[%s],plain:in_pwd[%s]db_pwd[%s]",oldpwd,tAccount.password,in_oldpwd_plain,db_oldpwd_plain);
		DB_t_aif_account_free_lock_cur();
		return E_EACCPWD;
	}
	des2src(tAccount.password,newpwd);
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_U;
	}

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
		return ret;
	
	double dUniqno= 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		return ret;
	}
	
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.serial_type = TXCODE_EACC_MODPW;								//修改密码
	tradeserial.serial_no = D2I(dUniqno);										//流水号
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//流水状态
	tradeserial.card_id = tAccount.card_id;											//交易卡号
	tradeserial.customer_id=tAccount.customer_id;									//客户号
	des2src(tradeserial.oper_code,rPack->semp);						//操作员

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return  E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	
	SetCol(handle,F_LSERIAL1,F_VSMESS,0);	
	outPack->lserial1=tradeserial.serial_no;

	sprintf(outPack->vsmess,"%s的密码修改成功",tAccount.cut_name);
	PutRow(handle,outPack,pRetCode,szMsg);

	return 0;
}

