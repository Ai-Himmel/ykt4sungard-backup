/* --------------------------------------------
 * 程序名称: F950006.c
 * 创建日期: 2006-8-12
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 下载系统参数
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "pubfunc.h"
#include "dbfunc_foo.h"

int F950006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	char buf[256] = "";
	int sysid = rPack->lcert_code;
	ret = CheckGatewayDynKey(sysid,rPack->scust_limit);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret = GetParameter(rPack->lvol0,buf);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCARD0,0);
	des2src(out_pack->scard0,buf);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

