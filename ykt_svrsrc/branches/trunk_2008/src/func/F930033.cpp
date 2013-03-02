/* --------------------------------------------
 * 程序名称: F930033.sqc
 * 创建日期: 20050306
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  采集补助流水
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

int F930033(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
	tRcvdtl.comu_ver=rPack->lbank_acc_type;					//补助批次号
	tRcvdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
	des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRC校验

	tRcvdtl.card_no= rPack->lvol5;							//交易卡号
	tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号
	tRcvdtl.in_bala= rPack->lvol9;							//入卡金额
	tRcvdtl.out_bala = rPack->lvol10;						//出卡金额
	tRcvdtl.amount = rPack->lvol8;							//本次消费金额
	tRcvdtl.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	tRcvdtl.tx_code = 930033;								//交易代码
 	snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	tRcvdtl.fee_code = rPack->lvol11;						
	getsystimestamp(tRcvdtl.col_timestamp);
	if(tRcvdtl.tx_mark==2)
		tRcvdtl.status[0]='6';								//中途拔卡交易
	else if(tRcvdtl.tx_mark==153 || tRcvdtl.tx_mark == 251)
		tRcvdtl.status[0]='1';
	else
		tRcvdtl.status[0]='5';
	ret = DB_t_tif_rcvdtl_add(&tRcvdtl);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_rcvdtl_add ret[%d]",ret);
		if(DB_REPEAT==ret)
			return 0;	
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	//回滚事务
	return -1;		
}
