/* --------------------------------------------
 * 程序名称: F841602.sqc
 * 创建日期: Sep 29 2004
 * 程序作者: auto creat by wen jian
 * 版本信息: 1.0.0.0
 * 程序功能: 客户信息删除
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

int F841602(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int	cut_id=0;                     	//客户号
	T_t_cif_customer  tCustomer;

	cut_id=atol(rPack->sholder_ac_no);
	
	ret=DB_t_cif_customer_read_by_cut_id(cut_id, &tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode=E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	if('1'==tCustomer.use_flag[0])
	{
		*pRetCode=E_CUSTOMER_IN_USE;
		goto L_RETU;
	}
	ret=DB_t_cif_customer_del_by_cut_id(cut_id);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode=E_DB_CUSTOMER_D;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
