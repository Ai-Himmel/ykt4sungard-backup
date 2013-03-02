/* --------------------------------------------
 * 程序名称: F930105.c
 * 创建日期: 2005-09-02
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:下传计时宝时间段
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
#include "dbfunc_foo.h"

int F930105(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	T_t_device tDevice;
	memset(&tDevice,0,sizeof tDevice);
	
	T_t_msglist tMsgList;
	memset(&tMsgList,0,sizeof(tMsgList));

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	if(in_pack->lvol3<1||in_pack->lvol3>8)
	{
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}

	if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	tMsgList.deviceid = tDevice.deviceid;
	ret = process930105(tDevice.deviceid,in_pack->lvol3);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	AddXmlItemInt(tMsgList.reqdata,XML_KEY_WEEKNO,in_pack->lvol3);			//星期
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_OUTNUM,in_pack->lvol5);			//记录数
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME1,in_pack->saddr);		//时间段1
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME2,in_pack->saddr2);		//时间段2
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME3,in_pack->sall_name);	//时间段3
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME4,in_pack->snote);		//时间段4
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME5,in_pack->snote2);		//时间段5
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME6,in_pack->scert_addr);	//时间段6
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME7,in_pack->sbankname);	//时间段7
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DOORTIME8,in_pack->sbankname2);	//时间段8
	//FIXME
	//需要查询时间段表下传
	//FIXME
	//tMsgList.funcno = iRequest;
	tMsgList.funcno=930105;
	tMsgList.pfuncno = 930105;
	tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
	// 重试10次
	tMsgList.maxsendcnt = 10;

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





