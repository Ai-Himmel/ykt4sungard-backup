/* --------------------------------------------
 * 程序名称: F930118.c
 * 创建日期: 2005-09-02
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:广播下传门禁白名单
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
#include "busqc.h"

int F930118(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
       T_t_msglist tMsgList;
	T_t_device tDevice;
	memset(&tDevice,0,sizeof tDevice);

	memset(&tMsgList,0,sizeof(tMsgList));

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_CARDID,in_pack->lvol3);
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_VERNUM,in_pack->sserial0);

	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMsgList.deviceid = tDevice.deviceid;
	tMsgList.funcno = iRequest;
	tMsgList.msglevel =1;
	ret=AddMsgLst(&tMsgList);
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





