/* --------------------------------------------
 * 程序名称: F930034.sqc
 * 创建日期: 20050306
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  采集现金充值流水
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

static int check(T_t_tif_rcvdtl *p)
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
	if((p->tx_mark!=0XFA)&&(p->tx_mark!=0xFE))
	{
		return 	p->tx_mark+E_999_0X00;			//把返回码置为交易标记
	}
	if(0XFA==p->tx_mark)
	{
		if(p->out_bala<=p->in_bala)
		{
			return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
		}
		if(p->amount<=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	else
	{
		if(p->out_bala>=p->in_bala)
		{
			return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
		}
		if(p->amount>=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	return 0;
}
int F930034(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_tif_rcvdtl tRcvdtl;

	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&tRcvdtl,0,sizeof(tRcvdtl));

	tRcvdtl.serial_no= rPack->lvol4;							//上传端流水号
	tRcvdtl.tx_mark=rPack->lvol12;							//999交易标记
	tRcvdtl.sys_id  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(tRcvdtl.device_id, rPack->sdate1);				//物理设备ID
	des2src(tRcvdtl.inpower_no,rPack->stx_pwd);				//终端设备授权号
//	tRcvdtl.comu_ver=rPack->lbank_acc_type;				//通信版本号
//	tRcvdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
	des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRC校验

	tRcvdtl.card_no= rPack->lvol5;							//交易卡号
	tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号
	tRcvdtl.in_bala= rPack->lvol9;							//入卡金额
	tRcvdtl.out_bala = rPack->lvol10;						//出卡金额
	tRcvdtl.amount = rPack->lvol8;							//本次消费金额
	tRcvdtl.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	tRcvdtl.tx_code = 930034;								//交易代码
 	snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsystimestamp(tRcvdtl.col_timestamp);
	ret=check(&tRcvdtl);
	if(ret)
	{
		tRcvdtl.status[0]='5';								//无效交易
		tRcvdtl.run_reason=ret;
		strncpy(tRcvdtl.deal_date,tRcvdtl.col_timestamp,8);
		strncpy(tRcvdtl.deal_time,tRcvdtl.col_timestamp+8,6);
	}
	else
		tRcvdtl.status[0]='1';
	g_dbchkerr=0;
	ret = DB_t_tif_rcvdtl_add(&tRcvdtl);
	if (ret)
	{
		g_dbchkerr=1;
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",tRcvdtl.serial_no,tRcvdtl.card_no,tRcvdtl.device_id,tRcvdtl.tx_date,tRcvdtl.tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	g_dbchkerr=1;
	return 0;
L_RETU:
	//回滚事务
	return -1;
}
