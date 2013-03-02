/* --------------------------------------------
 * 程序名称: F930065.sqc
 * 创建日期: 20051008
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 采集LPORT补助名单
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

int F930065(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	/*
	int ret = 0;
	int cnt=0;
	int mesid=0;
     	T_t_tif_meslist tMesList;
	T_t_pif_device	tDevice;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);

	if(strlen(in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	memset(&tDevice,0,sizeof tDevice);
	ret = DB_t_pif_device_read_by_devphy999_id(in_pack->sdate0,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_DEVICE_N;
		}
		*pRetCode = E_DB_DEVICE_R;
		goto L_RETU;
	}
	// 检查设备是不是LPORT
	if(strncmp(tDevice.devtype,"5301",4))
	{
		*pRetCode = E_DEVICE_TYPE_NOT_FIT;
		goto L_RETU;
	}
	memset(&tMesList,0,sizeof(tMesList));
	
	AddXmlItemStr(tMesList.incontent,XML_KEY_DEV999_NO,in_pack->sdate0);
	AddXmlItemInt(tMesList.incontent,XML_KEY_CARDID,in_pack->lvol5);
	
	tMesList.funid = 930065;
	tMesList.level = 3;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=tMesList.funid)
		return 0;	
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		*pRetCode=E_DB_COMMIT;
		goto  L_RETU;
	}
	mesid=tMesList.mesid;
	des2src(out_pack->sdate0,in_pack->sdate0);
	for(cnt=0;(cnt<10)&&(tMesList.ecode!=0);cnt++)
	{
		sleep(1);
		memset(&tMesList,0,sizeof(tMesList));
		ret=DB_t_tif_meslist_read_by_mesid(mesid, &tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_meslist_read_by_mesid err[%d]",ret);
			*pRetCode=E_DB_MESLIST_R;
			goto L_RETU;
		}
	}
	switch(tMesList.ecode)
	{
		case 0:		//成功
			des2src(out_pack->vsvarstr0,"成功");
			break;
		case 9999:		//交易未处理
			des2src(out_pack->vsvarstr0,"前置机无应答");
			break;
		default:			//交易已经处理,但结果是失败
			des2src(out_pack->vsvarstr0,tMesList.emsg);				
			break;
	}	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
*/
	return  -1;		
}
