/* --------------------------------------------
 * 程序名称: F847133.c
 * 创建日期: 2010-7-26
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 已下发补助信息修改
 (发错客户的补助，在补助还未领取前可以修改为另一个客户)
 * --------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

int F847133(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	double dSerialNo = 0;
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";

	T_t_tif_tradeserial  tradeserial;
	T_t_tif_subsidy  	tSubsidy;
	T_t_cif_customer   tCustomer;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tSubsidy,0,sizeof(tSubsidy));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof tCustomer);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);					//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if (strlen(rPack->semp) == 0)			// 操作员
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if (strlen(rPack->scust_no2) == 0)			// 复核操作员
	{
		*pRetCode = E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if (strcmp(rPack->semp, rPack->scust_no2) == 0)
	{
		writelog(LOG_ERR, "oper[%s]auth_oper[%s]", rPack->semp, rPack->scust_no2);
		*pRetCode = E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret = chk_oper_pwd(rPack->scust_no2, rPack->semp_pwd);			// 复核操作员密码
	if (ret)
	{
		if (E_OPER_NOT_EXIST == ret)
			*pRetCode = E_AUTH_OPER_NOT_EXIST;
		else if (E_PASSWORD_WRONG == ret)
			*pRetCode = E_AUTH_OPER_PWD;
		else
			*pRetCode = ret;
		goto L_RETU;
	}
	
	if(strlen(rPack->scust_limit2)<1)								//补助批次号
	{
		*pRetCode=E_INPUT_SUBSIDY;
		goto L_RETU;
	}

	if(rPack->lvol0 < 0)											// 客户号,发错补助的客户
	{
		*pRetCode = E_CUSTOMER_NOT_EXIST;
		goto L_RETU;
	}
	if(rPack->lvol1 < 0)											// 正确补助的客户号
	{
		*pRetCode = E_CUSTOMER_NOT_EXIST;
		goto L_RETU;
	}

	ret = DB_t_cif_customer_read_by_cut_id(rPack->lvol1 , &tCustomer);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ret = DB_t_tif_subsidy_read_lock_by_c3_and_subsidy_no_and_cust_no_and_status(rPack->scust_limit2, rPack->lvol0, "2", &tSubsidy);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode =  E_DB_SUBSIDY_N;
		else
			*pRetCode =  E_DB_SUBSIDY_R;
		goto L_RETU;
	}

	tSubsidy.cust_no = rPack->lvol1;							// 修改成正确的客户号
	ret=DB_t_tif_subsidy_update_lock_by_c3(&tSubsidy);
	if(ret)
	{
		DB_t_tif_subsidy_free_lock_by_c3();
		if(DB_NOTFOUND==ret)
			*pRetCode = E_USER_NO_SUBSIDY;
		else
			*pRetCode = E_DB_SUBSIDY_U;
		goto L_RETU;
	}
	DB_t_tif_subsidy_free_lock_by_c3();	
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = (int)dSerialNo;											//流水号
	tradeserial.serial_type = TXCODE_MOD_SUBSIDY;
	tradeserial.serial_state = SERISTAT_NODEBT;				//流水状态
	des2src(tradeserial.operate_date,sysdate);			//发生日期
	des2src(tradeserial.operate_time,systime);			//发生时间
	des2src(tradeserial.collect_date,sysdate);				//采集日期
	des2src(tradeserial.collect_time,systime);				//采集时间
	des2src(tradeserial.enteract_date,logicdate);			//处理日期
	des2src(tradeserial.enteract_time,systime);			//处理时间
	tradeserial.maindevice_id = rPack->lvol6;				//上传工作站标识
	tradeserial.device_id = rPack->lvol7;					//采集设备标识
	tradeserial.customer_id = rPack->lvol1;
	tradeserial.run_reason = rPack->lvol0;					// 原客户号
	des2src(tradeserial.oper_code , rPack->semp);		//操作员代码
	des2src(tradeserial.reserve_1,rPack->scust_no2);		// 复核操作员
	
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	des2src(out_pack->vsmess, "补助信息客户号修改成功");
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
