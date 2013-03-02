/* --------------------------------------------
 * 程序名称: F2401.sqc
 * 创建日期: 2009-08-8
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 内蒙财经圈存转账
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "bank_interface.h"


int F2401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int tradecode = rPack->lcert_code;

	switch(tradecode)
	{
		case TRADE_TRANS:													// 转账
			return Bank_Trans(handle,rPack,pRetCode,szMsg);			
			break;
			
		case TRADE_REVERSE:												// 冲正
			return Bank_Reverse(handle,rPack,pRetCode,szMsg);
			break;
		case BANK_QUERYBALA:
			return Bank_Querybala(handle,rPack,pRetCode,szMsg);				// 查询银行卡余额
			break;
		default:
			writelog(LOG_INFO,"This trade can't supplied,tradecode=[%d]!",tradecode);
			return E_TRANS_FUNC_NONSUPPORT;
	}

	return 0;
}

