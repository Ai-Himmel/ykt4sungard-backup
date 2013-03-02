/* --------------------------------------------
 * 程序名称: F843360.sqC
 * 创建日期: 2007-11-02
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 充值操作员删除
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
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F843360(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=1;

	ret=DB_t_deposit_oper_del_by_oper_code(rPack->scust_auth);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_OPER_N;
		else
			*pRetCode=E_DB_DEPOSIT_OPER_D;
		goto L_RETU;
	}
	ret=DB_t_deposit_operpos_del_by_oper_code(rPack->scust_auth);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			*pRetCode=E_DB_DEPOSIT_OPERPOS_D;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
