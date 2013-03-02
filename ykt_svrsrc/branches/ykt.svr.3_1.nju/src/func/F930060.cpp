/* --------------------------------------------
 * 程序名称: F930009.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:强制设备签退
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
#include "busqc.h"

int F930055(TRUSERID * handle, int iRequest, ST_PACK * rPack, int *iRetCode, char *szMsg);

int F930060(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int cnt=0;
	int msgid=0;
     	T_t_msglist tMsgList;
	T_t_device tDevice;
	memset(&tDevice,0,sizeof tDevice);

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	memset(&tMsgList,0,sizeof(tMsgList));

	tMsgList.deviceid=in_pack->lcert_code;
	if(tMsgList.deviceid==0)
	{
		return E_NOTEXIST_DEVICE;
	}
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_SUBSIDYONOFF, in_pack->lvol4);
	tMsgList.funcno = 930060;
	tMsgList.msglevel = 2;
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=tMsgList.funcno)
		return 0;	
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		*pRetCode=E_DB_COMMIT;
		goto  L_RETU;
	}
	msgid=tMsgList.msgid;
	des2src(out_pack->sdate0,in_pack->sdate0);
	for(cnt=0;(cnt<10)&&(tMsgList.errcode!=0);cnt++)
	{
		sleep(1);
		memset(&tMsgList,0,sizeof(tMsgList));
		ret=DB_t_msglist_read_by_msgid(msgid, &tMsgList);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_msglist_read_by_msgid err[%d]",ret);
			*pRetCode=E_DB_MSGLIST_R;
			goto L_RETU;
		}
	}
	switch(tMsgList.errcode)
	{
		case 0:		//成功
			des2src(out_pack->vsvarstr0,"成功");
			ret=F930055( handle,iRequest, in_pack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"设备签退成功,但F930055 更新签退状态失败");
				goto L_RETU;
			}
			break;
		case 9999:		//交易未处理
			des2src(out_pack->vsvarstr0,"前置机无应答");
			break;
		default:			//交易已经处理,但结果是失败
			des2src(out_pack->vsvarstr0,tMsgList.errmsg);				
			break;
	}	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return  -1;	
}





