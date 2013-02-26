/* --------------------------------------------
* 程序名称: F847360.cpp
* 创建日期: 2008-07-11
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 哈尔滨工程大学用户查询
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
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "mypub.h"
#include "DllFun.h"
#include "logfile.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
extern ini_pack_para g_ini_para;

int F847360(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	char *result = NULL;
	char command[256] = "";
	char user_id[81] = "";
	char value_name[128] = "";

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	memcpy(user_id, in_pack->sall_name, sizeof(user_id) - 1);			// get user id

	SetCol(handle,0);
	SetCol(handle, F_SBANKNAME, F_SCUST_LIMIT, F_SCARD0, 0);
	
	strcat(command, RG_QUERYUSER_FLAG);
	strcat(command, RG_USER_ID);
	strcat(command, RG_SPLIT2);
	strcat(command, user_id);
	strcat(command, RG_SPLIT2);
	strcat(command, RG_END_MARK);

	result = fCommandTS(g_ini_para.user_id, g_ini_para.pwd, g_ini_para.ip, g_ini_para.port, command);
	
	error_code = GetRGRetData(result, RG_USER_ID, value_name);
	if (error_code)
	{
		error_code = E_NETCHARGE_NO_ACCOUNT;
		g_LogFile.WriteLogEx(1003, "用户名[%s]--IP地址[%s]--端口号[%d]--用户值[%s]--命令[%s]--errcode[%d]", g_ini_para.user_id, g_ini_para.ip, g_ini_para.port, value_name, command, error_code);
		goto L_RETU;
	}

	strncpy(out_pack->sbankname, value_name, sizeof(value_name) - 1);
	
	memset(value_name, 0, sizeof(value_name));
	error_code = GetRGRetData(result, RG_USER_IP, value_name);
	if (error_code || (0 == strlen(value_name)))
	{
		error_code = E_NETCHARGE_STOP_OUT_OF_DATE;
		g_LogFile.WriteLogEx(1003, "用户名[%s]--IP地址[%s]--端口号[%d]--用户值[%s]--命令[%s]--errcode[%d]", g_ini_para.user_id,g_ini_para.ip, g_ini_para.port, value_name, command, error_code);
		goto L_RETU;
	}
	strncpy(out_pack->scust_limit, value_name, sizeof(value_name) - 1);

	memset(value_name, 0, sizeof(value_name));
	error_code = GetRGRetData(result, RG_USER_NAME, value_name);
	if (error_code)
	{
		error_code = E_NETCHARGE_USER_NAME_NULL;
		g_LogFile.WriteLogEx(1003, "用户名[%s]--IP地址[%s]--端口号[%d]--用户值[%s]--命令[%s]--errcode[%d]", g_ini_para.user_id,g_ini_para.ip, g_ini_para.port, value_name, command, error_code);
		goto L_RETU;
	}
	
	g_LogFile.WriteLogEx(1003, "用户姓名[%s]", value_name, command);
	strncpy(out_pack->scard0, value_name, sizeof(value_name) - 1);

L_RETU:
	*pRetCode = error_code;
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif