/* --------------------------------------------
 * 程序名称: F930103.c
 * 创建日期: 2005-09-05
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:下传计时宝设备参数
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
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

int F930103(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
       T_t_tif_meslist tMesList;
	T_t_pif_device tDevice;
	memset(&tDevice,0,sizeof tDevice);

	memset(&tMesList,0,sizeof(tMesList));

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	AddXmlItemStr(tMesList.incontent,XML_KEY_DEV999_ID,in_pack->sdate0);
	AddXmlItemInt(tMesList.incontent,XML_KEY_WORKMODE, in_pack->lvol3);
	AddXmlItemInt(tMesList.incontent,XML_KEY_LOCK1_TIME, in_pack->lvol5);
	AddXmlItemInt(tMesList.incontent,XML_KEY_LOCK2_TIME, in_pack->lvol6);
	AddXmlItemStr(tMesList.incontent,XML_KEY_IS_ALLEYWAY, in_pack->sstatus0);
	AddXmlItemStr(tMesList.incontent,XML_KEY_IS_SAVE, in_pack->sstatus1);
	AddXmlItemStr(tMesList.incontent,XML_KEY_IS_LCD, in_pack->sstatus2);
	AddXmlItemStr(tMesList.incontent,XML_KEY_SYSPWD, in_pack->semp_pwd);
	AddXmlItemInt(tMesList.incontent,XML_KEY_BAUDRATE, 0);
	AddXmlItemInt(tMesList.incontent,XML_KEY_CARDSTR, 100);
	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMesList.devid = tDevice.device_id;
	tMesList.funid = iRequest;
	tMesList.level =1;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	return 0;
L_RETU:
	return  -1;
}
