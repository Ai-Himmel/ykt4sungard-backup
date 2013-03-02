/* --------------------------------------------
* 程序名称: F930121.c
* 创建日期: 2005-10-27
* 程序作者: 汤成
* 版本信息: 1.0.0.0
* 程序功能: 下传充值限额
* --------------------------------------------
* 修改日期:
* 修改人员:
* 修改描述:
* 版本信息:
* 备注信息:
* --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"

int F930124(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int device_id = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SDATE0,0);
	
	T_t_pif_device tDevice;
	memset(&tDevice,0,sizeof tDevice);
	if(in_pack->lvol0 == 0)
	{
		ret = get_devinfo_by_phyid(in_pack->sdate1,&tDevice);
		if(ret)
		{
			writelog(LOG_ERR,"read device info error,dev[%s]",in_pack->sdate0);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_DEVICE_N;
			else
				*pRetCode = E_DB_DEVICE_R;
			return -1;
		}
		device_id = tDevice.device_id;
	}
	else
		device_id = in_pack->lvol0;
	memset(&tDevice,0,sizeof tDevice);
	ret = DB_t_pif_device_read_by_device_id(device_id,&tDevice);
	if( tDevice.state_id >= DEVISTAT_LOGOUT )
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
		return -1;
	}
	if(strcmp(tDevice.devtype,"0201") != 0)
	{
		*pRetCode = E_DEVICE_TYPE_NOT_FIT;
		return -1;
	}
	out_pack->lvol0 = 1;
	out_pack->lvol1 = tDevice.maxtrade;
	des2src(out_pack->sdate0,"20500101");
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

