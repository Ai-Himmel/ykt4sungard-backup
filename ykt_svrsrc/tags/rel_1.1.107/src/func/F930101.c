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

static int SaveDoorJSBSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;


	g_dbchkerr=0;
	ret = DB_t_door_txdtl_add(tTxdtl);
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",
			tTxdtl->serial_no,tTxdtl->card_no,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOOR_TXDTL_I;
	}
	return ret;
}

static int UpdateConferSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;
	int confid = 0;
	T_t_pif_card tCard;
	char sign[1] = "";
	memset(&tCard,0,sizeof(tCard));
	if(tTxdtl->tx_mark != (E_999_0x99 - E_999_BASE))
	{
		writelog(LOG_DEBUG,"不正确的刷卡，卡号[%d]标志[%d]"
			,tTxdtl->card_no,tTxdtl->tx_mark);
		return 0;
	}
	ret = DB_t_pif_card_read_by_card_id(tTxdtl->card_no,&tCard);
	if(ret)
		return ret;
	ret = GetConferenceIDByDev(tTxdtl,&confid,sign);
	if(ret)
	{
		// 如果没有查找会议
		/*
		if(E_DB_CONFDEV_N == ret)
			return 0;
		return ret;
		*/
		writelog(LOG_ERR,"无法找到会议,设备[%d][%s : %s]"
			,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		return 0;
	}
	ret = SaveConferenceSerial(tTxdtl,confid,tCard.cosumer_id,sign[0]);
	if(ret)
	{
		writelog(LOG_DEBUG,"返回码[%d]卡号[%d],客户号[%d]会议号[%d]",
			ret,tTxdtl->card_no,tCard.cosumer_id,confid);
		// 没有对应的记录，删除掉
		if(E_DB_CONFATTLST_N == ret)
			return 0;
	}
	return ret;
}

//增加插入考勤流水表记录功能
//added by hhd at 2006-06-27
static int InsertKQSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;
	int confid = 0;
	T_t_pif_card tCard;
	memset(&tCard,0,sizeof(tCard));
	/*
	ret = DB_t_pif_card_read_by_card_id(tTxdtl->card_no,&tCard);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_pif_card_read_by_card_id error,errcode=[%d]",ret);
		return ret;
	}
	*/
	ret = SaveKQSerial(tTxdtl);
	if(ret)
	{
		writelog(LOG_DEBUG,"SaveKQSerial error,errcode=[%d]",ret);
		return ret;
	}
	return 0;
}

int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	T_t_door_txdtl tTxdtl;
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

	tTxdtl.serial_no= rPack->lvol3;						//上传端流水号
	tTxdtl.sys_id  = rPack->lcert_code;					//上传工作站标识(前置机注册号)
	tTxdtl.mode_code=rPack->lvol6;					//模式代码
	tTxdtl.card_no= rPack->lvol7;						//交易卡号
	tTxdtl.use_type= rPack->lvol8;						//考勤类型
	tTxdtl.inductor_no= rPack->lvol9;					//感应头标记
	tTxdtl.work_mark=rPack->lvol10;					//上下班标志
	tTxdtl.tx_mark=rPack->lvol11;						//999交易标志
	des2src(tTxdtl.device_id, rPack->sdate0);			//物理设备ID
 	des2src(tTxdtl.tx_date,rPack->sdate1);				//发生日期(格式化输入的日期)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRC校验
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
	ret=check(&tTxdtl);
	if(ret)
	{
//		tTxdtl.status[0]='5';								//无效交易
//		tTxdtl.err_code=ret;
		writelog(LOG_DEBUG,"无效流水[%s][%d]",tTxdtl.device_id,tTxdtl.serial_no);
		return ret;
	}
	else
		tTxdtl.status[0]='1';
	ret = GetDevUsageByDevId(tTxdtl.device_id,&dev_usage);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	switch(dev_usage)
	{
		case DU_JSB_CONFRENCE:
			ret = SaveDoorJSBSerial(&tTxdtl);
			if(ret)
			{
				writelog(LOG_ERR,"保存计时宝流水失败,errcode[%d]",ret);
				break;
			}
			ret = UpdateConferSerial(&tTxdtl);
			break;
		case DU_JSB_ATTENDANCE:
			ret = InsertKQSerial(&tTxdtl);
			if(ret)
			{
				writelog(LOG_ERR,"插入考勤流水表失败,errcode[%d]",ret);
				break;
			}
		default:
			ret = SaveDoorJSBSerial(&tTxdtl);
			break;
	}
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
