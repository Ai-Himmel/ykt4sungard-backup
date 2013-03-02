/* --------------------------------------------
 * 程序名称: F950031.sqc
 * 创建日期: 2006-8-12
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  汇多收集消费流水入账
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
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
	if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			//把返回码置为交易标记
	}
	if(p->in_bala- p->out_bala!=p->amount)
	{
		return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
	}
	if(0X99==p->tx_mark)
	{
		if(p->amount<=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	else
	{
		//冲正交易,发生额为负数
		if(p->amount>=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	return 0;
}

int F950031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int in_balance = 0;
	int out_balance = 0;
	int man_fee = 0;
	int trade_fee = 0;
	T_t_tif_rcvdtl tRcvdtl;

	memset(&tRcvdtl,0,sizeof(tRcvdtl));

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

	in_balance = rPack->lvol9;								//入卡金额
	out_balance = rPack->lvol10;							//出卡金额
	man_fee = rPack->lvol1;								//为负数
	trade_fee = rPack->lvol8;								//本次消费金额

	tRcvdtl.in_bala = in_balance;
	tRcvdtl.out_bala = out_balance;
	tRcvdtl.amount = trade_fee;
	tRcvdtl.manage_fee = man_fee;

	tRcvdtl.card_no= rPack->lvol5;							//交易卡号
	tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号						
	tRcvdtl.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	tRcvdtl.tx_code = 930031;								//交易代码
 	snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsystimestamp(tRcvdtl.col_timestamp);
	ret=check(&tRcvdtl);
	if(ret)
	{
		tRcvdtl.err_code=ret;
		if(tRcvdtl.tx_mark==2)
			tRcvdtl.status[0]='6';								//中途拔卡交易
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
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",tRcvdtl.serial_no,tRcvdtl.card_no,tRcvdtl.device_id,tRcvdtl.tx_date,tRcvdtl.tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}

