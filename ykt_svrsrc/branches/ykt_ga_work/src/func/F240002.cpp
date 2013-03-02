/* --------------------------------------------
 * 程序名称: F240002.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台模拟入账交易
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

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	ret=	F240001(handle,iRequest,rPack,pRetCode,szMsg);
	db_rollback();
	if(ret)
	{
		return -1;
	}
	return 0;
}

