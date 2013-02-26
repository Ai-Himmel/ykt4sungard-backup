/* --------------------------------------------
* 程序名称: F847352.cpp
* 创建日期: 2007-08-27
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 公安专科水控转账金额传送
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

#ifdef _DEBUG
	extern CLogFile g_LogFile;	
	int count1 = 0;
#endif

int F847352(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	
	Save_Info save_info;
	memset(&save_info, 0, sizeof(save_info));

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	if (1 == in_pack->lvol3)
	{
		if (error_code = InitDB())
			error_code = DLLFUN_ERR_TRANSFER_THIRD_PART_FAIL;
		
		*pRetCode = error_code;
		PutRow(handle, out_pack, pRetCode, szMsg);
		return error_code;
	}

	save_info.cut_id = in_pack->lvol0;
	save_info.save_Money = in_pack->lvol1;
	save_info.save_type = in_pack->lvol2;

	SaveInfo(&save_info, &error_code);

#ifdef _DEBUG
	g_LogFile.WriteLogEx(1001, "客户号[%d]--转帐金额[%d]--转账类型[%d]--错误码[%d]--序号[%d]", 
	save_info.cut_id, save_info.save_Money, save_info.save_type, error_code, ++count1);
#endif
	if (error_code != 0)
		error_code = DLLFUN_ERR_TRANSFER_FAIL;
	
	*pRetCode = error_code;
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
	//	return 0;
}

#ifdef __cplusplus
}
#endif