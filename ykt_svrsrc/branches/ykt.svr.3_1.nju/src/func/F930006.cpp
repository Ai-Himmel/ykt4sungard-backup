/* --------------------------------------------
 * 程序名称: F930006.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 下传搭伙费比率
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

int F930006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	double dMaxFeeRatio=0;
	int iMaxFeeRatio=0;
	int iRow=0;
    	T_t_msglist tMsgList;
	T_t_feetype tFeeType;
	T_t_device tDevice;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	memset(&tMsgList,0,sizeof(tMsgList));
	memset(&tFeeType,0,sizeof(tFeeType));
	memset(&tDevice,0,sizeof tDevice);
//	memset(&tCuttypefee,0,sizeof(tCuttypefee));

	if(strlen( in_pack->sdate0)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	if((ret = get_devinfo_by_phyid( in_pack->sdate0,&tDevice)))
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tMsgList.deviceid = tDevice.deviceid;
	tMsgList.funcno = iRequest;
	tMsgList.msglevel = 1;
	///////////////////////////////////////////////////
	// 修改为读取
	ret=GetMaxShopFeeRate(dMaxFeeRatio);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	iMaxFeeRatio=(int)(dMaxFeeRatio*100);
	ret=DB_t_feetype_open_select_by_c1();
	if(ret)
	{
		*pRetCode=E_DB_FEETYPE_R;
		goto L_RETU;
	}
	while(1)
	{
		memset(&tFeeType,0,sizeof(tFeeType));
		memset(&tMsgList.reqdata,0,sizeof(tMsgList.reqdata));
		ret=DB_t_feetype_fetch_select_by_c1(&tFeeType);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(iRow)
					break;
				else
				{
					*pRetCode= E_DB_FEETYPE_N;
					goto L_RETU;
				}
			}
			else
			{
				*pRetCode= E_DB_FEETYPE_R;
				goto L_RETU;
			}
		}
		iRow++;
		AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDTYPE,tFeeType.feetype);	//卡类型
		if(strncmp(tFeeType.boardfeeflag,TYPE_YES,1)==0)
			AddXmlItemInt(tMsgList.reqdata, XML_KEY_FEE, iMaxFeeRatio);
		else
			AddXmlItemInt(tMsgList.reqdata, XML_KEY_FEE, 0);

		ret=AddMsgLst(&tMsgList);
		if(ret)
		{
			DB_t_feetype_close_select_by_c1();
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}

///////////////////////////////////////////////////////////////////
/*
	//AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDTYPE,in_pack->lvol5);	//卡类型
	//AddXmlItemInt(tMsgList.reqdata, XML_KEY_FEE, in_pack->lvol6);		//费率
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
*/
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return  -1;
}





