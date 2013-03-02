/* ----------------------------------------------------------
 * 程序名称：F847313.sqc
 * 创建日期：2007-02-06
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/
 /*----------------------------------------------------

 * 修改日期：2009-05-21
 * 修改人员: 王彦兵
 * 修改描述: 根据用户输入设备，日期，金额信息，手工补流水
 *-----------------------------------------------------*/


#define _IN_SQC_                                  
#include <string.h>                               
#include <stdio.h>    
#include "errdef.h"  
#include "pubdb.h"  
#include "pubfunc.h"      
#include "fdsqc.h"                                

static int check(T_t_tif_rcvdtl *p)
{
	int ret=0;

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
	
	if(p->in_bala- p->out_bala!=p->amount)
	{
		return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
	}

	if(p->amount <= 0)
		return E_999_AMT;
	
	return 0;
}

int F847313(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	
	int ret=0;
	
	T_t_tif_rcvdtl tRcvdtl;
	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	tRcvdtl.tx_code = 930031;				
	tRcvdtl.tx_mark=153;								//999交易标记
	tRcvdtl.status[0]='1';									//999交易标记
	des2src(tRcvdtl.crc,"9999");						//CRC校验

	if (!strlen (in_pack->scust_no)) 
	{
		writelog(LOG_ERR,"hi_operator[%s]errcode[%d]!",in_pack->scust_no,E_INPUT_NOOPERATOR);
		return E_INPUT_NOOPERATOR;
	}
	des2src(tRcvdtl.oper_no,in_pack->scust_no);

	if(in_pack->lvol0 <=0)
		return E_INPUT_CARDNO_CANNOT_NULL;
	tRcvdtl.card_no= in_pack->lvol0;					//交易卡号

	if(in_pack->lvol1 <=0)
		return E_INPUT_CARD_TXCNT;
	tRcvdtl.total_cnt= in_pack->lvol1;					//交易次数

	tRcvdtl.in_bala=D2I(in_pack->damt2*100);			//入卡金额
	tRcvdtl.out_bala = D2I(in_pack->damt3*100);			//出卡金额
	tRcvdtl.amount = D2I(in_pack->damt1*100);			//本次消费金额

	des2src(tRcvdtl.tx_date,in_pack->sdate1);			//发生日期(格式化输入的日期)
	des2src(tRcvdtl.tx_time,in_pack->stime1);			//发生时间(格式化输入的时间)
	getsystimestamp(tRcvdtl.col_timestamp);

	if(in_pack->lvol2 <=0)							//设备号
		return E_INPUT_DEVICE_ID;

	T_t_pif_device tDevice;
	memset(&tDevice,0,sizeof tDevice);
	ret = DB_t_pif_device_read_by_device_id(in_pack->lvol2, &tDevice);
	if(ret)
		return E_DB_DEVICE_R;

	if(tDevice.state_id >= DEVISTAT_LOGOUT )
		return E_DEVICE_LOGOUT;

	tRcvdtl.sys_id  = tDevice.subsystem_id;
	des2src(tRcvdtl.device_id, tDevice.dev999_id);			//物理设备ID

	if(in_pack->lvol3 > 0)
		tRcvdtl.serial_no= in_pack->lvol3;					//上传端流水号
	else
		tRcvdtl.serial_no = atoi(tRcvdtl.tx_time) %100;
	
	ret=check(&tRcvdtl);
	if(ret)
		return ret;
	
	ret = DB_t_tif_rcvdtl_add(&tRcvdtl);
	if (ret)
	{
		if(ret == DB_REPEAT)				//可能是流水号重复了，换一个流水号重试
		{
			tRcvdtl.serial_no++;
			return DB_t_tif_rcvdtl_add(&tRcvdtl);
		}
		return  E_DB_TRADESERIAL_I;				
	}

	return 0;
}

