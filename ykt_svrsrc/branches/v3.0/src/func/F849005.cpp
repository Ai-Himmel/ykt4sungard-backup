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
#include "busqc.h"



int F849005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	int device_id=0;
	char sDevPhyid[31]="";
	char current_date[9] = "";

	
	T_t_authcard auth_card;
	T_t_operator oper;
	T_t_depositoper   tDepositOper;
	T_t_depositoperpos tDepositOperpos;


	getsysdate(current_date);
	memset(&auth_card,0,sizeof auth_card);
	memset(&oper,0,sizeof oper);
	memset(&tDepositOper,0,sizeof tDepositOper);
	memset(&tDepositOperpos,0,sizeof tDepositOperpos);
	writelog(LOG_INFO,"充值操作员签到,操作员卡号%d,设备%s",rPack->lvol5,rPack->sdate1);
	ret = DB_t_authcard_read_by_cardno(rPack->lvol5,&auth_card);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_AUTHCARD_N;
		else
		 	return E_DB_AUTHCARD_R;
	}
	/*
	if(strcmp(auth_card.cardphyid,rPack->sdate0))
	{
		return E_CARD_PHYNO_DIFFER;
	}
	*/
	if(auth_card.status[0]!=STATUS_NORMAL)
		return E_AUTHCARD_LOGOUT;
	if(auth_card.lossflag[0] == '1')
	{
		return E_AUTHCARD_IS_LOSS;
	}
	// 判断授权卡权限
//	if((auth_card.privilege & AUTHCARD_PRV_ADDPOS) == 0)
//	{
//		*pRetCode = E_AUTHCARD_IS_LOSS;
//		goto L_RETU;
//	}
	// 判断有效期
	if(strcmp(auth_card.expiredate,current_date) < 0)
	{
		return E_AUTHCARD_LOGOUT;
	}
	ret = DB_t_operator_read_by_opercode(auth_card.opercode,&oper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_OPER;
		else
			return E_DB_OPERATOR_R;
	}
	ret=DB_t_depositoper_read_by_opercode(auth_card.opercode,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPER_R;
		else
			return E_DB_DEPOSITOPER_N;
	}
	if(tDepositOper.status[0]!=STATUS_NORMAL)
	{
		return E_DEPOSITOPER_STOP;
	}
	if(tDepositOper.devlimitflag[0]=='1')
	{
		ret=GetDevIdByDevPhyId(&device_id,rPack->sphone3);
		if (ret)
		{
			writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] device_id[%d]devphy999_id[%s]",ret,device_id,rPack->sdate1);
			return ret;
		}
		ret=DB_t_depositoperpos_read_by_opercode_and_deviceid(tDepositOper.opercode, device_id,&tDepositOperpos);
		if(ret)
		{
			writelog(LOG_ERR,"t_deposit_operpos_read_by_oper_code_and_device_id ret[%d]oper_code[%s] device_id[%d]devphy999_id[%s]",ret,tDepositOper.opercode, device_id,sDevPhyid);
			if(DB_NOTFOUND==ret)
				return E_OPER_NO_RIGHT_FOR_DEVICE;
			else
				return E_DB_DEPOSITOPERPOS_R;
		}
	}	
	return 0;
}
