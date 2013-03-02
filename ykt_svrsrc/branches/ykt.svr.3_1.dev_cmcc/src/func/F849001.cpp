/* --------------------------------------------
 * 程序名称: F849001.cpp
 * 创建日期: 2007-07-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 读卡器消费-终端登陆
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

#define ID_TERM_NO 0xFF
#define ID_TERM_NO2 0xFFFF

int F849001(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int dev_id;
	int termno;
	T_t_device tDevice;
	T_t_subsystem tSubsystem;
	int ret;
	char temp[128] = "";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	
	termno = in_pack->lvol0;//机号
	if(termno != ID_TERM_NO && termno != ID_TERM_NO2)
	{
		ret = find_device_by_sys_termno(in_pack->lcert_code,termno,&dev_id);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	else
	{
		memset(&tSubsystem,0,sizeof tSubsystem);
		ret = DB_t_subsystem_read_by_sysid(in_pack->lcert_code,&tSubsystem);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_SUBSYSTEM_N;
			else
				*pRetCode = E_DB_SUBSYSTEM_N;
			goto L_RETU;
		}
	}

	ResetNormalCPack(&aPack,1,0);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SCUST_LIMIT,F_LVOL2,F_LVOL3,F_LVOL4,F_LVOL5,0);

	ret = GetSysParaVal(GLOBE_999_DEVAUTHKEY,temp);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	des2src(out_pack->scust_limit,temp);
	
	ret = GetSysParaVal(GLOBE_DEV_DAY_TRADE_LIMIT,temp);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	out_pack->lvol4 = atoi(temp);
	ret = GetSysParaVal(GLOBE_DEV_ONCE_TRADE_LIMIT,temp);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	out_pack->lvol3 = atoi(temp);
	out_pack->lvol2 = PURSE_NO_ONE + 1;
	out_pack->lvol0 = dev_id;
	
	if(termno != ID_TERM_NO && termno != ID_TERM_NO2)
	{
		memset(&tDevice,0,sizeof tDevice);
		ret = DB_t_device_read_lock_by_c0_and_deviceid(dev_id,&tDevice);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_DEVICE_N;
			else
				*pRetCode = E_DB_DEVICE_R;
			goto L_RETU;
		}
		if(strcmp(tDevice.devtypecode,DEVITYPE_CONSUME_TERM))
		{
			DB_t_device_free_lock_by_c0();
			*pRetCode = E_DB_DEVICE_N;
			goto L_RETU;
		}
		if(tDevice.lastseqno == 0)
			out_pack->lvol1 = 1;
		else
			out_pack->lvol1 = tDevice.lastseqno;
		out_pack->lvol5 = 1;
	}
	else
	{
		out_pack->lvol1 = 0;
		out_pack->lvol5 = 0;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	DB_t_device_free_lock_by_c0();
	return 0;
L_RETU:
	return -1;
}

