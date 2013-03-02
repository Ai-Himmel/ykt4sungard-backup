/* --------------------------------------------
* 程序名称: F930121.c
* 创建日期: 2005-10-27
* 程序作者: 汤成
* 版本信息: 1.0.0.0
* 程序功能:下传门禁名单与版本
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
#include "busqc.h"
#include "dbfunc_foo.h"

int F930121(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int deviceid=0;
	ret = GetDevIdByDevPhyId(&deviceid,in_pack->sdate0);
	if(ret)
	{
		writelog(LOG_ERR,"read device info error,dev[%s]",in_pack->sdate0);
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_DEVICE_N;
		else
			*pRetCode = E_DB_DEVICE_R;
		return -1;
	}

	ret = process930121(in_pack->lvol3,in_pack->lvol5,in_pack->sserial0,deviceid,0);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	return 0;
}

