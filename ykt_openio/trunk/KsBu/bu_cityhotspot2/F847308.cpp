/* --------------------------------------------
* 程序名称: 
* 创建日期: 2009-3-4
* 程序作者: 王彦兵
* 版本信息: 1.0.0.0
* 程序功能: 网络收费帐户转账(包含第三方对接)
* --------------------------------------------
* 修改日期:
* 修改人员:
* 修改描述:
* 版本信息:
* 备注信息:
* --------------------------------------------*/

#include "netfeetrans.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
int F847308(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	if (strncmp(in_pack->sroom_no,"009",3) != 0)
	{
		g_LogFile.WriteLogEx(1004,"请求码[%s]错误",in_pack->sroom_no);
		return -1;
	}
	g_LogFile.WriteLogEx(1004,"学号[%s],密码[%s],请求码[%s],金额[%f],交易时间[%s]",in_pack->scust_auth,in_pack->sserial1,
		in_pack->sroom_no,in_pack->damt1,in_pack->scust_auth2);
	return netfee_trans(handle,iRequest,in_pack,pRetCode,szMsg);
}

#ifdef __cplusplus
}
#endif