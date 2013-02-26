/* --------------------------------------------
* 程序名称: F847308.cpp
* 创建日期: 2007-5-14
* 程序作者: 李翔
* 版本信息: 1.0.0.0
* 程序功能: 网络收费帐户转账(包含第三方对接)
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

int F847308(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szStuEmpNo[21] = "";
	double dRemainBalance = 0.0;
	double dTransferBalance = in_pack->damt0; 
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_LVOL3, F_LVOL11, 0);

	out_pack->lvol11 = NetChargeTrans(in_pack->scust_auth, &dRemainBalance, &dTransferBalance,in_pack->scusttypes);
//	if (ret)
//		out_pack->lvol11 = ret;				// L_LVOL11作为返回码查看
//	else
//		out_pack->lvol11 = 0;
	
	out_pack->damt0 = dRemainBalance;		// 网络收费剩余余额
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif