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
#include "acctrans.h"
#include "busqc.h"



int F240008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_device 		device;
	T_t_syspara 	t_syspara;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCARD0,0);

	memset(&device,0,sizeof(device));
	memset(&t_syspara,0,sizeof(t_syspara));

	ret=DB_t_syspara_read_by_paraid(GLOBLE_SYSPARA_STATIC_KEY, &t_syspara);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_device_read_lock_by_cur_and_deviceid error,error code=[%d]",ret);
		if(DB_NOTFOUND==ret)
			return E_DB_SYSPARA_N;
		else
			return E_DB_SYSPARA_R;
	}

	ret=DB_t_device_read_lock_by_c0_and_deviceid(atoi(rPack->sorder2),&device);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			writelog(LOG_ERR,"DB_t_device_read_lock_by_cur_and_deviceid error,error code=[%d]",ret);
			return E_NOTEXIST_DEVICE;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_device_read_lock_by_cur_and_deviceid error,error code=[%d]",ret);
			return E_DB_DEVICE_R;
		}
	}
	device.runstatus[0]=DEVRUNSTATUS_ONLINE;		//更改设备注册表状态为在线状态
	ret=DB_t_device_update_lock_by_c0(&device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_device_update_lock_by_cur error,error code=[%d]",ret);
		return E_DB_DEVICE_U;
	}
	des2src(out_pack->scard0,t_syspara.paraval);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
}


