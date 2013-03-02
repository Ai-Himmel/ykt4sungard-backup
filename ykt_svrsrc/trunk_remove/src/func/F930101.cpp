/* --------------------------------------------
 * 程序名称: F930101.sqc
 * 创建日期: 2005-08-22
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 收集门禁流水
 * --------------------------------------------
 * 修改日期: 2006-06-27
 * 修改人员:	韩海东
 * 修改描述:	增加考勤流水收集功能
 * 版本信息:	1.0.0.1
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

//static int check(T_t_doordtl *p)
//{
//	int ret=0;
//	if(strlen(p->crc)==0)
//	{
//		return E_999_CRC;							//上传流水CRC校验错误
//	}
//	ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
//	if(ret)
//	{
//		return E_999_DATE;							//上传流水交易日期有误
//	}
//	ret=IsInvalidDateTime(p->transtime,"HHMMSS");
//	if(ret)
//	{
//		return E_999_TIME;							//上传流水交易时间有误
//	}
//	/*
//	if((p->transmark!=0X99)&&(p->transmark!=0xFE)	)
//	{
//		return 	p->transmark+E_999_0X00;			//把返回码置为交易标记
//	}
//	*/
//	return 0;
//}

//static int SaveDoorJSBSerial(T_t_attenddtl* attenddtl)
//{
//	int ret = 0;
//
//	g_dbchkerr=0;
//	ret = DB_t_attenddtl_add(attenddtl);
//	g_dbchkerr=1;
//	if (ret)
//	{
//		writelog(LOG_DEBUG,"serial_no[%d]phycardid[%s]cardno[%d]deviceid[%s]transdate[%s]transtime[%s]",
//			attenddtl->devseqno,attenddtl->cardphyid,attenddtl->cardno,attenddtl->deviceid,attenddtl->transdate,attenddtl->transtime);
//		if(DB_REPEAT==ret)
//			return 0;
//		else
//			return E_DB_DOOR_TXDTL_I;
//	}
//	return ret;
//}
int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	T_t_doordtl tTxdtl;
	T_t_card tCard;
	if(!strlen(rPack->sdate0))
	{
		return E_DEVPHYID_NULL;
	}
	memset(&tTxdtl,0,sizeof(tTxdtl));

	tTxdtl.devseqno= rPack->lvol3;						//上传端流水号
	tTxdtl.sysid  = rPack->lcert_code;					//上传工作站标识(前置机注册号)
//		tTxdtl.mode_code=rPack->lvol6;					//模式代码
	tTxdtl.cardno= rPack->lvol7;						//交易卡号
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_card_read_by_cardno(tTxdtl.cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_CARD_R;
	}
	tTxdtl.custid = tCard.custid; //客户号
	tTxdtl.transmark=rPack->lvol11;						//999交易标志
	ret=GetDevIdByDevPhyId(&tTxdtl.deviceid,rPack->sdate0);
	if(ret)
	{
			writelog(LOG_ERR,"采集计时宝流水,设备不存在或已注销[%s]",rPack->sdate0);
//			return ret;
	}
	des2src(tTxdtl.transdate,rPack->sdate1);				//发生日期(格式化输入的日期)
//	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRC校验
	des2src(tTxdtl.transtime,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsysdate(tTxdtl.coldate);
	getsystime(tTxdtl.coltime);
	ret=DB_t_doordtl_add(&tTxdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOORDTL_I;
	}
	return 0;
}
