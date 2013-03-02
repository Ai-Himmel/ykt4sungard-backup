/* --------------------------------------------
 * 程序名称: F930029.cpp
 * 创建日期: 2007-10-15
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  收集洗衣机冲正流水
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
	if(strcmp(p->tx_date,"20000000") != 0)
	{
		ret=IsInvalidDateTime(p->tx_date,"YYYYMMDD");
		if(ret)
		{
			return E_999_DATE;						//上传流水交易日期有误
		}
	}
	else
		getsysdate(p->tx_date);
	if(strcmp(p->tx_time,"000000") != 0)
	{
		ret=IsInvalidDateTime(p->tx_time,"HHMMSS");
		if(ret)
		{
			return E_999_TIME;							//上传流水交易时间有误
		}
	}
	else
		getsystime(p->tx_time);
	// &&(p->tx_mark!=0xF0)
	
	if((p->tx_mark!=0XFA))
	{
		return 	p->tx_mark+E_999_0X00;			//把返回码置为交易标记
	}
	if(p->in_bala - p->amount != p->out_bala)
	{
		return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
	}
	return 0;
}

int SaveWaterRcvdtl_250(ST_PACK *rPack)
{
	int ret=0;
	T_t_tif_rcvdtl_water tRcvdtlwater;
	memset(&tRcvdtlwater,0,sizeof tRcvdtlwater);
	
	tRcvdtlwater.serial_no= rPack->lvol4;							//上传端流水号
	tRcvdtlwater.tx_mark=rPack->lvol12;							//999交易标记
	tRcvdtlwater.sys_id  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(tRcvdtlwater.device_id, rPack->sdate1);				//物理设备ID
	des2src(tRcvdtlwater.inpower_no,rPack->stx_pwd);				//终端设备授权号
	tRcvdtlwater.comu_ver=rPack->lbank_acc_type;					//通信版本号
	int ver = tRcvdtlwater.comu_ver / 10;
	if( 0x81 == tRcvdtlwater.comu_ver || 0x81 == ver )
	{
//	tRcvdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
		tRcvdtlwater.fee_code = rPack->lbank_acc_type2;				// 将启动原因保存到收费科目中
	}
	else
	{
		tRcvdtlwater.fee_code = 0;
	}
	des2src(tRcvdtlwater.crc,rPack->sbank_code2);				//CRC校验

	//tRcvdtl.man_fee = rPack->lvol11;						//
	tRcvdtlwater.card_no= rPack->lvol5;							//交易卡号
	//tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号
	tRcvdtlwater.purse_no = 0;
	tRcvdtlwater.in_bala= rPack->lvol9;							//入卡金额
	tRcvdtlwater.out_bala = rPack->lvol10;						//出卡金额
	tRcvdtlwater.amount = rPack->lvol8;							//本次消费金额
	if(tRcvdtlwater.amount>0)
		tRcvdtlwater.amount = -tRcvdtlwater.amount;
	tRcvdtlwater.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	tRcvdtlwater.tx_code = 930031;								//交易代码
 	snprintf(tRcvdtlwater.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tRcvdtlwater.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsystimestamp(tRcvdtlwater.col_timestamp);
	ret=check(&tRcvdtlwater);
	if(ret)
	{
		tRcvdtlwater.err_code=ret;
		if(tRcvdtlwater.tx_mark==240 || tRcvdtlwater.tx_mark==2)
		{
			tRcvdtlwater.status[0]='1';							//中途拔卡交易
			// 标记为中途拔卡
			tRcvdtlwater.tx_mark = 2;
		}
		else
		{
			tRcvdtlwater.status[0]='5';								//无效交易
			strncpy(tRcvdtlwater.deal_date,tRcvdtlwater.col_timestamp,8);
			strncpy(tRcvdtlwater.deal_time,tRcvdtlwater.col_timestamp+8,6);
		}
	}
	else
		tRcvdtlwater.status[0]='1';
	ret = DB_t_tif_rcvdtl_water_add(&tRcvdtlwater);
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",tRcvdtlwater.serial_no,tRcvdtlwater.card_no,tRcvdtlwater.device_id,tRcvdtlwater.tx_date,tRcvdtlwater.tx_time);
		if(DB_REPEAT==ret)
			return 0;
		return E_DB_TRADESERIAL_I;
	}
	return 0;
}
int F950029(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_tif_rcvdtl tRcvdtl;
	T_t_pif_device tDevice;

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
	memset(&tDevice,0,sizeof tDevice);

	ret = DB_t_pif_device_read_by_devphy999_id(rPack->sdate1, &tDevice);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			*pRetCode = E_DB_DEVICE_R;
			goto L_RETU;
		}			
	}
	else
	{
		if(memcmp(tDevice.devtype,"0244",4) ==0				// 水控设备
			||memcmp(tDevice.devtype,"0245",4) ==0)
			return SaveWaterRcvdtl_250(rPack);			
	}

	tRcvdtl.serial_no= rPack->lvol4;							//上传端流水号
	tRcvdtl.tx_mark=rPack->lvol12;							//999交易标记
	tRcvdtl.sys_id  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(tRcvdtl.device_id, rPack->sdate1);				//物理设备ID
	des2src(tRcvdtl.inpower_no,rPack->stx_pwd);				//终端设备授权号
	tRcvdtl.comu_ver=rPack->lbank_acc_type;					//通信版本号
	int ver = tRcvdtl.comu_ver / 10;
	if( 0x81 == tRcvdtl.comu_ver || 0x81 == ver )
	{
//	tRcvdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
		tRcvdtl.fee_code = rPack->lbank_acc_type2;				// 将启动原因保存到收费科目中
	}
	else
	{
		tRcvdtl.fee_code = 0;
	}
	des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRC校验

	//tRcvdtl.man_fee = rPack->lvol11;						//
	tRcvdtl.card_no= rPack->lvol5;							//交易卡号
	//tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号
	tRcvdtl.purse_no = 0;
	tRcvdtl.in_bala= rPack->lvol9;							//入卡金额
	tRcvdtl.out_bala = rPack->lvol10;						//出卡金额
	tRcvdtl.amount = rPack->lvol8;							//本次消费金额
	if(tRcvdtl.amount>0)
		tRcvdtl.amount = -tRcvdtl.amount;
	tRcvdtl.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	tRcvdtl.tx_code = 930031;								//交易代码
 	snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsystimestamp(tRcvdtl.col_timestamp);
	ret=check(&tRcvdtl);
	if(ret)
	{
		tRcvdtl.err_code=ret;
		if(tRcvdtl.tx_mark==240 || tRcvdtl.tx_mark==2)
		{
			tRcvdtl.status[0]='6';							//中途拔卡交易
			// 标记为中途拔卡
			tRcvdtl.tx_mark = 2;
		}
		else
		{
			tRcvdtl.status[0]='5';								//无效交易
			strncpy(tRcvdtl.deal_date,tRcvdtl.col_timestamp,8);
			strncpy(tRcvdtl.deal_time,tRcvdtl.col_timestamp+8,6);
		}
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
	return -1;
}

