/* --------------------------------------------
* 程序名称: F847361.cpp
* 创建日期: 2008-07-11
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 哈尔滨工程大学用户转账
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
#include "ksbu.h"
#include "BasicMath.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
extern ini_pack_para g_ini_para;

int F847361(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	char *result = NULL;
	char command[256] = "";
	char user_id[81] = "";
	char value_name[128] = "";
	char trade_money[20] = "";

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	memcpy(user_id, in_pack->sall_name, sizeof(user_id) - 1);			// get user id
	sprintf(trade_money, "%.02lf", in_pack->damt1);						// get transfer money

	SetCol(handle,0);
	SetCol(handle, F_SBANKNAME, 0);

	strcat(command, RG_PAY_FLAG);
	strcat(command, RG_USER_ID);
	strcat(command, RG_SPLIT2);
	strcat(command, user_id);
	strcat(command, RG_SPLIT2);
	strcat(command, RG_SPLIT1);
	strcat(command, RG_FEE);
	strcat(command, RG_SPLIT2);
	strcat(command, trade_money);
	strcat(command, RG_SPLIT2);
	strcat(command, RG_END_MARK);

	result = fCommandTS(g_ini_para.user_id, g_ini_para.pwd, g_ini_para.ip, g_ini_para.port, command);

	error_code = GetRGRetData(result, RG_USER_ID, value_name);
	if (error_code)
	{
		error_code = E_NETCHARGE_NO_ACCOUNT;
		g_LogFile.WriteLogEx(1003, "用户名[%s]--密码[%s]--IP地址[%s]--端口号[%d]--用户值[%s]--命令[%s]--errcode[%d]", g_ini_para.user_id, g_ini_para.pwd, g_ini_para.ip, g_ini_para.port, value_name, command, error_code);
		goto L_RETU;
	}

	strncpy(out_pack->sbankname, value_name, sizeof(value_name) - 1);
L_RETU:
	*pRetCode = error_code;
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif