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
#include "busqc.h"
#include "acctrans.h"


int F843360(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=1;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=MAKETRANSCODEDEL(TCM_DEPOSITOPER);	
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;	

	ret=DB_t_depositoper_del_by_opercode(rPack->scust_auth);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPER_N;
		else
			return E_DB_DEPOSITOPER_D;
	}
	ret=DB_t_depositoperpos_del_by_opercode(rPack->scust_auth);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_DEPOSITOPERPOS_D;
	}
	return 0;
}
