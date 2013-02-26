/* --------------------------------------------
* 程序名称: F847355.cpp
* 创建日期: 2007-09-10
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 海事大学电控转账测试连接数据库
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
#include "pubfunc.h"
#include "mypub.h"
#include "bupub.h"
#include "logfile.h"
#include "DllFun.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

int F847355(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	float elec_price = 0.0;
	bool conncet_flag = false;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	out_pack->damt0 = elec_price = CNectDB(true);

	if (elec_price >= -0.01 && elec_price <= 0.01)	// 如果为0表示执行失败, 单价最低为分
	{
		error_code = DLLFUN_ERR_GET_ELEC_PRICE;
		g_LogFile.WriteLogEx(1001, "数据库连接出错--[%d]", error_code);
		goto L_RETU;	
	}
	
	if (GetDBStatus() != 1)
	{
		error_code = DLLFUN_ERR_CONNECT_ELEC;
		g_LogFile.WriteLogEx(1001, "获得数据库状态出错--[%d]", error_code);
		goto L_RETU;
	}

L_RETU:
	out_pack->lvol10 = *pRetCode = error_code;
	out_pack->damt1 = CNectDB(false);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif