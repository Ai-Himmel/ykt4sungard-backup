/* --------------------------------------------
 * 创建日期: 2008-05-29
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员签退
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
#include "acctrans.h"
#include "busqc.h"

int F820352(TRUSERID * handle, int iRequest, ST_PACK * in_pack, int *pRetCode, char *szMsg)
{

	int ret=0;
	T_t_operator tOperator;

	memset(&tOperator,0,sizeof(tOperator));
	ret=DB_t_operator_read_by_opercode(in_pack->scust_no,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_OPER;
		else
			return E_DB_OPERATOR_R;
	}
	tOperator.loginflag[0]='0';
	des2src(tOperator.logouttime,CAccTrans::getInstance()->trans.sysdatetime);
	ret=DB_t_operator_update_by_opercode(tOperator.opercode,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			return E_NOTEXIST_OPER;
		}
		else
		{
			return E_DB_OPERATOR_U;
		}
	}
	return 0;
}
