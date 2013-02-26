/* --------------------------------------------
* 程序名称: F847307.cpp
* 创建日期: 2007-5-11
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 网络收费帐户查询(包含第三方对接)
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
#include "bupub.h"
#include "ComFunNetCharge.h"

#ifdef __cplusplus
extern "C" {
#endif

int F847307(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szStuEmpNo[21] = "";
	char szAccSerOutOfDate[9] = "";
	double dRemainBalance = 0.0;
	double dOweBalanece = 0.0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL11, 0);
	
	memcpy(szStuEmpNo, in_pack->scust_auth, sizeof(szStuEmpNo) - 1);
//	ret = GetAccoutInfo(in_pack->scust_auth, &(out_pack->damt0), &(out_pack->damt1), out_pack->sphone);
	out_pack->lvol11 = GetAccoutInfo(szStuEmpNo, &dRemainBalance);
//	if (ret)
//		out_pack->lvol11 = ret;				// L_LVOL11作为返回码查看
//	else
//		out_pack->lvol11 = 999;
	
	out_pack->damt0 = dRemainBalance;
//	out_pack->damt1 = dOweBalanece;

//	memcpy(szAccSerOutOfDate, out_pack->sphone, sizeof(szAccSerOutOfDate) - 1);
	
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif