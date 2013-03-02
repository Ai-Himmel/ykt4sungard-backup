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
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"

static int check(T_t_door_txdtl *p)
{
	int ret=0;
	if(strlen(p->crc)==0)
	{
		return E_999_CRC;							//上传流水CRC校验错误
	}
	ret=IsInvalidDateTime(p->tx_date,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							//上传流水交易日期有误
	}
	ret=IsInvalidDateTime(p->tx_time,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							//上传流水交易时间有误
	}
	/*
	if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			//把返回码置为交易标记
	}
	*/
	return 0;
}

static int SaveDoorJSBSerial(T_t_attend_txdtl* tTxdtl)
{
	int ret = 0;

	g_dbchkerr=0;
	ret = DB_t_attend_txdtl_add(tTxdtl);
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]phycardid[%s]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",
			tTxdtl->serial_no,tTxdtl->phycard_no,tTxdtl->card_no,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOOR_TXDTL_I;
	}
	return ret;
}
int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	//T_t_attend_txdtl tTxdtl;
	T_t_door_txdtl tTxdtl;
	T_t_pif_device tDevice;
	T_t_pif_card tCard;
	if(strlen(rPack->sdate0) != 8)
	{
		*pRetCode = E_DEVPHYID_NULL;
		goto L_RETU;
	}

	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&tTxdtl,0,sizeof(tTxdtl));
	memset(&tDevice,0,sizeof tDevice);

	/*

	tTxdtl.serial_no= rPack->lvol3;						//上传端流水号
	tTxdtl.sys_id  = rPack->lcert_code;					//上传工作站标识(前置机注册号)
//		tTxdtl.mode_code=rPack->lvol6;					//模式代码
	tTxdtl.card_no= rPack->lvol7;						//交易卡号
//		tTxdtl.use_type= rPack->lvol8;						//考勤类型
//		tTxdtl.inductor_no= rPack->lvol9;					//感应头标记
//		tTxdtl.work_mark=rPack->lvol10;					//上下班标志
	tTxdtl.tx_mark=rPack->lvol11;						//999交易标志
	des2src(tTxdtl.device_id, rPack->sdate0);			//物理设备ID
	des2src(tTxdtl.tx_date,rPack->sdate1);				//发生日期(格式化输入的日期)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRC校验
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
//		ret=check(&tTxdtl);
//		if(ret)
//		{
//			tTxdtl.status[0]='5';							//无效交易
//			//tTxdtl.err_code=ret;
//			writelog(LOG_DEBUG,"无效流水device_id[%d]serial_no[%d]",tTxdtl.device_id,tTxdtl.serial_no);
//			return ret;
//		}
//		else
//			tTxdtl.status[0]='1';
	ret = SaveDoorJSBSerial(&tTxdtl);
	*/
	tTxdtl.serial_no= rPack->lvol3;						//上传端流水号
	tTxdtl.sys_id  = rPack->lcert_code;					//上传工作站标识(前置机注册号)
//		tTxdtl.mode_code=rPack->lvol6;					//模式代码
	tTxdtl.card_no= rPack->lvol7;						//交易卡号
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_pif_card_read_by_card_id(tTxdtl.card_no,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			// 卡号不存在
		}
		else
		{
			*pRetCode = E_DB_CARD_R;
			goto L_RETU;
		}
	}
//		tTxdtl.use_type= rPack->lvol8;						//考勤类型
//		tTxdtl.inductor_no= rPack->lvol9;					//感应头标记
//		tTxdtl.work_mark=rPack->lvol10;					//上下班标志
	tTxdtl.cust_id = tCard.cosumer_id; //客户号
	tTxdtl.tx_mark=rPack->lvol11;						//999交易标志
	//des2src(tTxdtl.device_id, rPack->sdate0);			//物理设备ID
	ret = get_devinfo_by_phyid(rPack->sdate0,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			// 设备不存在
			writelog(LOG_ERR,"采集计时宝流水,设备不存在或已注销[%s]"
			,rPack->sdate0);
			return 0;
		}
		else
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	tTxdtl.device_id = tDevice.device_id;
	des2src(tTxdtl.tx_date,rPack->sdate1);				//发生日期(格式化输入的日期)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRC校验
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
	ret = SaveKQSerial(&tTxdtl);
	if(ret)
	{
		writelog(LOG_ERR,"插入考勤流水表失败,errcode[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
