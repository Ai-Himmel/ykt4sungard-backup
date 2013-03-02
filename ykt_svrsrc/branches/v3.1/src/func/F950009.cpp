/* --------------------------------------------
 * 程序名称: F950009.sqC
 * 创建日期: 2007-1224
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 获取系统当前最大黑名单版本号
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "dbfunc_foo.h"


int F950009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);
	char maxvol[21] = {0};
	int ret=GetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,maxvol);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal ret[%d]",ret);
		return ERRIF_DATABASE_QRY;
	}
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_LIMIT,0);
	des2src(out_pack->scust_limit,maxvol);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

