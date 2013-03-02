/* --------------------------------------------
 * 程序名称: F841613.cpp
 * 创建日期: 2008-03-03
 * 程序作者: auto creat by wen jian
 * 版本信息: 1.0.0.0
 * 程序功能: 导入客户信息删除
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

int F841613(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	char    	stuemp_no[30+1]="";           	//学号或员工号

	int    ret=0;
	char sqlcmd[512]="";

	des2src(stuemp_no,rPack->scert_no);
	if(!strlen(stuemp_no))
	{
		*pRetCode= E_INPUT_STUEMP_NO;
		goto L_RETU;
	}
	sprintf(sqlcmd,"delete ykt_cur.t_customertmp where  stuemp_no='%s' ",stuemp_no);
	ret=DynamicStmtExecute(sqlcmd);
	if(ret)
	{
		writelog(LOG_ERR,"sql:[%s]",sqlcmd);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_DB_CUSTOMER_TMP_N;
		else
			*pRetCode= E_DB_CUSTOMER_TMP_D;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
