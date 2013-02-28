/* --------------------------------------------
 * 程序名称: F240007.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 响应前置机的请求,根据银行对帐文件进行对帐
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



int F240007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
/*
	ret=DB_t_device_update_by_subsystem_type(SUBSYSTYPE_KEEP,SUBSYSSTAT_OFFLINE);
	if(ret)
	{
		*pRetCode=E_DB_DEVICE_U;
		writelog(LOG_ERR,"更新设备状态失败,errcode=[%d]",ret);
		goto L_RETU;
	}
*/
	return 0;
}


