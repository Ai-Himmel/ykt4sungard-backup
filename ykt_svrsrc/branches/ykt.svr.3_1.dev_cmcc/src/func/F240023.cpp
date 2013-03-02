/* --------------------------------------------
 * 程序名称: F240023.sqc
 * 创建日期: 2009-8-25
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 对账查询
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "accchkquery.h"

int F240023(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int accchktype = rPack->lsafe_level2;				// 对账类别	
	T_t_cfgaccchk cfgaccchk;
	memset(&cfgaccchk,0,sizeof cfgaccchk);
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,
		F_SDATE3,F_SALL_NAME,F_SNAME2,F_SPHONE,F_SHOLDER_AC_NO,0);

	ret = DB_t_cfgaccchk_read_by_accchktype(accchktype,&cfgaccchk);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_CFGACCCHK_N;
		else
			return E_DB_CFGACCCHK_R;
	}
	switch(accchktype)
	{
		case BANK_ACCCHK_TYPE:											// 圈存对账结果查询
			return  bankaccchkquery(handle,rPack,out_pack,pRetCode,szMsg);

		case MOBILE_ACCCHK_TYPE:											// 移动对账查询
			return mobileaccchkquery(handle,rPack,out_pack,pRetCode,szMsg);
			
		default:
			return E_TRANS_FUNC_NONSUPPORT;
	}
	return 0;
}

