/* --------------------------------------------
* 程序名称: F851003.cpp
* 创建日期: 2009-12-16
* 程序作者: 汤成
* 版本信息: 1.0.0.0
* 程序功能: 空中充值帐户支付冲正(包含第三方对接)
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
#include "gdctpub.h"

#ifdef __cplusplus
extern "C" {
#endif

int F851003(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
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
	SetCol(handle,F_LSAFE_LEVEL,F_VSMESS, F_SCUST_LIMIT, F_SBANK_CODE,F_SBANK_ACC,
		F_SCUSTTYPES,F_LVOL1,F_SPHONE3,F_VSVARSTR0, 0);

	strcpy(out_pack->sphone3,"200910101");
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 1;
}

#ifdef __cplusplus
}
#endif