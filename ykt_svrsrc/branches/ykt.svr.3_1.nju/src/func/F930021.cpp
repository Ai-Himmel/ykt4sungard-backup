/* --------------------------------------------
 * 程序名称: F930021.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 下传设备档案信息
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

int F930021(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int cnt=0;
	int msgid=0;
   	T_t_msglist tMsgList;
	T_t_device	tDevice;
	T_t_device tPDev;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	memset(&tMsgList,0,sizeof(tMsgList));
	memset(&tDevice,0,sizeof(tDevice));
	memset(&tPDev,0,sizeof tPDev);


	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	ret=get_devinfo_by_phyid(in_pack->sdate0,&tDevice);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"get_devinfo_by_phyid err[%d]",ret);
		goto L_RETU;
	}

	if((ret = DB_t_device_read_by_deviceid(tDevice.fdeviceid,&tPDev)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DEV999_ID, tDevice.devphyid);
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_DEV999_NO,  tDevice.deviceno);
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DEVTYPE,tDevice.devtypecode);
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_DEVVERSION, tDevice.devverno);
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_CARDSTR, tDevice.cardphytype);
	AddXmlItemStr(tMsgList.reqdata,XML_KEY_VCARDSET, tDevice.cardset);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_PORTCOUNT, tDevice.svrportcnt);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_FDEVPHY_ID, tPDev.devphyid);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_PORTNO,tDevice.svrportno);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_status, tDevice.status);
	AddXmlItemInt(tMsgList.reqdata,XML_KEY_JOINMODE,tDevice.commtype);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_COMADD, tDevice.ip);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_PORT,  tDevice.portno);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_BAUDRATE, tDevice.baudrate);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_COMTYPE,tDevice.commtype);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_NOTVALIDITY, "091231000000");
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_VERNUM,tDevice.cardverno);
//	AddXmlItemInt(tMsgList.reqdata, XML_KEY_LASTTRASERNO, tDevice.lasttraserno);
//	AddXmlItemStr(tMsgList.reqdata, XML_KEY_LASTTRADATE, tDevice.lasttradate);
//	AddXmlItemInt(tMsgList.reqdata, XML_KEY_LASTSHUTSERNO, tDevice.lastshutserno);
//	AddXmlItemStr(tMsgList.reqdata, XML_KEY_LASTSHUTDATE, tDevice.lastshutdate);
	tMsgList.deviceid = tDevice.deviceid;
	tMsgList.funcno = 930021;
	tMsgList.msglevel = 3;
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





