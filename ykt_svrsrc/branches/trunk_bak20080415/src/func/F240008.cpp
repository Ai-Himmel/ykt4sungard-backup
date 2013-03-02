/* --------------------------------------------
 * 程序名称: F240008.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存终端设备向后台签到,返回读卡密钥
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"



int F240008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_pif_device 		t_pif_device;
	T_t_pif_cur_syspara 	t_syspara;
	T_t_pif_subsystem 		t_pif_subsystem;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCARD0,0);

	memset(&t_pif_device,0,sizeof(t_pif_device));
	memset(&t_syspara,0,sizeof(t_syspara));
	memset(&t_pif_subsystem,0,sizeof t_pif_subsystem);

	ret=DB_t_pif_cur_syspara_read_by_id(GLOBLE_SYSPARA_STATIC_KEY, &t_syspara);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		*pRetCode=E_DB_SYSPARA_R;
		goto L_RETU;
	}

	ret=DB_t_pif_device_read_lock_by_cur_and_device_id(atoi(rPack->sorder2),&t_pif_device);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
			*pRetCode=E_DB_DEVASSET_N;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
			*pRetCode=E_DB_DEVICE_R;
		}
		goto L_RETU;
	}
	//增加判断该设备是否为圈存设备
	ret=DB_t_pif_subsystem_read_by_system_id(t_pif_device.subsystem_id,&t_pif_subsystem);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_subsystem_read_by_system_id error,error code=[%d]",ret);
		*pRetCode=E_DB_SUBSYSTEM_R;
		goto L_RETU;
	}
	if(t_pif_subsystem.system_type!=SUBSYSTYPE_KEEP)
	{
		writelog(LOG_ERR,"t_pif_subsystem.system_type error,t_pif_subsystem.system_type=[%d]",t_pif_subsystem.system_type);
		*pRetCode=E_DB_SUBSYSTEM_U;
		goto L_RETU;
	}
	t_pif_device.state_id=DEVISTAT_ONLINE;		//更改设备注册表状态为在线状态
	ret=DB_t_pif_device_update_lock_by_cur(&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_update_lock_by_cur error,error code=[%d]",ret);
		*pRetCode=E_DB_DEVICE_U;
		goto L_RETU;
	}
	des2src(out_pack->scard0,t_syspara.value);

	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
L_RETU:
	return ret;
}


