/* --------------------------------------------
 * 程序名称: F930018.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:采集现金充值流水（历史）
 * --------------------------------------------
 * 修改日期:2004-12-14
 * 修改人员:	闻剑
 * 修改描述: 修改业务逻辑
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_                    
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F930018(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
    T_t_tif_meslist tMesList;
	T_t_pif_device tDevice;

	memset(&tMesList,0,sizeof(tMesList));
	memset(&tDevice,0,sizeof tDevice);

	if(in_pack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if((ret = DB_t_pif_device_read_by_device_id(in_pack->lcert_code,&tDevice)))
	{
		*pRetCode = E_DB_DEVICE_N;
	}
	else
	{
		AddXmlItemInt(tMesList.incontent,XML_KEY_TIME, in_pack->lvol4);
		tMesList.devid = tDevice.device_id;
		tMesList.funid = 930018;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
		return 0;
	}
L_RETU:
	return  -1;		
}





