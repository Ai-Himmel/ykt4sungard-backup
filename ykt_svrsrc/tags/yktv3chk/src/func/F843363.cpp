/* --------------------------------------------
 * 程序名称: F843363.sqC
 * 创建日期: 2007-11-02
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 充值操作员设备删除
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

int F843363(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	ret=pAccTrans->initOperDtl(rPack->semp);	
	if(ret)
		return ret;
	pAccTrans->trans.transcode=MAKETRANSCODEDEL(TCM_DEPOSITOPERPOS);
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	if(ret)
		return ret;
	ret=pAccTrans->addOperDtl();
	if(ret)
		return ret;	

	int deviceid=atoi(rPack->vsvarstr1);
	ret=DB_t_depositoperpos_del_by_opercode_and_deviceid(rPack->scust_auth,deviceid);
	if(ret)
	{
		writelog(LOG_ERR,"oper[%s]device_id[%d]",rPack->scust_auth,deviceid);
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPERPOS_N;
		else
			return E_DB_DEPOSITOPERPOS_D;
	}
	return 0;
}
