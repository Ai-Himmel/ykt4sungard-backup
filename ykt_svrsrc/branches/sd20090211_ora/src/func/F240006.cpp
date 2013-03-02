/* --------------------------------------------
 * 程序名称: F240006.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 前置机后台签到,每次登录银行后,
 			需要重新向后台签到.后台便于将设备签退,保证设备重新更换密钥
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



int F240006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	
	ret=DB_t_pif_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	if(ret)
	{
		*pRetCode=E_DB_DEVICE_U;
		writelog(LOG_ERR,"更新设备状态失败,errcode=[%d]",ret);
		goto L_RETU;
	}

	return 0;
L_RETU:
	return ret;
}


