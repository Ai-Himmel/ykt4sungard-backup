/* --------------------------------------------
 * 程序名称: F849005.cpp
 * 创建日期: 2007-07-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 联机充值签到
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
#include "dbfunc_foo.h"
#include "fdsqc.h"



int F849005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	int device_id=0;
	char sDevPhyid[31]="";
	char sdevice_id[31]="";
	char current_date[9] = "";

	
	T_t_pif_oper_authcard auth_card;
	T_t_pif_operator oper;
	T_t_deposit_oper   tDepositOper;
	T_t_deposit_operpos tDepositOperpos;


	getsysdate(current_date);
	memset(&auth_card,0,sizeof auth_card);
	memset(&oper,0,sizeof oper);
	memset(&tDepositOper,0,sizeof tDepositOper);
	memset(&tDepositOperpos,0,sizeof tDepositOperpos);
	writelog(LOG_INFO,"充值操作员签到,操作员卡号%d,设备%s",rPack->lvol5,rPack->sdate1);
	ret = DB_t_pif_oper_authcard_read_by_card_id(rPack->lvol5,&auth_card);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_OPER_AUTHCARD_N;
		else
		 	*pRetCode = E_DB_OPER_AUTHCARD_R;
		 goto L_RETU;
	}
	if(strcmp(auth_card.card_phyid,rPack->sdate0))
	{
		*pRetCode = E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}

	if(auth_card.status != AUTHCARD_STATUS_NORMAL)
	{
		*pRetCode = E_AUTHCARD_IS_LOSS;
		goto L_RETU;
	}
	// 判断授权卡权限
	if((auth_card.privilege & AUTHCARD_PRV_ADDPOS) == 0)
	{
		*pRetCode = E_AUTHCARD_IS_LOSS;
		goto L_RETU;
	}
	// 判断有效期
	if(strcmp(auth_card.expired_date,current_date) < 0)
	{
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}
	ret = DB_t_pif_operator_read_by_oper_code(auth_card.oper_code,&oper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_OPER_NOT_EXIST;
		else
			*pRetCode = E_DB_OPERATOR_R;
		goto L_RETU;
	}
	//writelog(LOG_DEBUG,"operator[%s],status[%s]",oper.oper_code,oper.status);
	if(strcmp(oper.status,OPERATOR_UNREG) == 0)
	{
		*pRetCode = E_OPERLOGON_UNREG;
		goto L_RETU;
	}
	ret=DB_t_deposit_oper_read_by_oper_code(auth_card.oper_code,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_OPER_R;
		else
			*pRetCode=E_DB_DEPOSIT_OPER_N;
		goto L_RETU;
	}
	if(tDepositOper.status[0]!='1')
	{
		*pRetCode=E_DEPOSIT_OPER_STOP;
		goto L_RETU;
	}
	if(tDepositOper.usedevlimit_flag[0]=='1')
	{
		ret=GetDevIdByDevPhyId(&device_id,rPack->sdate1);
		if (ret)
		{
			writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] device_id[%d]devphy999_id[%s]",ret,device_id,rPack->sdate1);
			*pRetCode=ret;
			goto L_RETU;
		}
		sprintf(sdevice_id,"%d",device_id);
		ret=DB_t_deposit_operpos_read_by_oper_code_and_device_id(tDepositOper.oper_code, sdevice_id,&tDepositOperpos);
		if(ret)
		{
			writelog(LOG_ERR,"t_deposit_operpos_read_by_oper_code_and_device_id ret[%d]oper_code[%s] sdevice_id[%s]devphy999_id[%s]",ret,tDepositOper.oper_code, sdevice_id,sDevPhyid);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_OPER_NO_RIGHT_FOR_DEVICE;
			else
				*pRetCode=E_DB_DEPOSIT_OPERPOS_R;
			goto L_RETU;
		}
	}
	
	return 0;
L_RETU:
	return -1;
}
