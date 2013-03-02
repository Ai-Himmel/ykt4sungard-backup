/* --------------------------------------------
 * 创建日期: 2008-05-28
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 客户类别删除
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

int F843374(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int cuttype=rPack->lvol0;
	T_t_cuttype tCuttype;

	memset(&tCuttype,0,sizeof(tCuttype));
	if(cuttype<1)
	{
		*pRetCode=E_CUTTYPE_NOT_EXIST;
		goto L_RETU;
	}
	ret=DB_t_cuttype_read_by_cuttype(cuttype,&tCuttype);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_CUTTYPEFEE_N;
		else
			*pRetCode=E_DB_CUTTYPEFEE_R;
		goto L_RETU;
	}
	if(tCuttype.useflag[0]=='1')
	{
		*pRetCode=E_CUTTYPE_IN_USE;
		goto L_RETU;
	}
	ret=DB_t_cuttype_del_by_cuttype(cuttype);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_CUTTYPEFEE_N;
		else
			*pRetCode=E_DB_CUTTYPEFEE_D;
		goto L_RETU;

	}
	return 0;
L_RETU:
	return -1;
}
