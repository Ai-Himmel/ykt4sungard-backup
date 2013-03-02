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
#include "acctrans.h"
#include "busqc.h"

int F930033(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	
	int ret=0;
	T_t_posdtl posdtl;
	
	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&posdtl,0,sizeof(posdtl));
	
	posdtl.devseqno= rPack->lvol4;							//上传端流水号
	posdtl.transmark=rPack->lvol12;							//999交易标记
	posdtl.sysid  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(posdtl.devphyid, rPack->sdate1);				//物理设备ID
//	des2src(posdtl.inpower_no,rPack->stx_pwd);				//终端设备授权号	
//	posdtl.comu_ver=rPack->lbank_acc_type;					//通信版本号
//	posdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
//	des2src(posdtl.crc,rPack->sbank_code2);				//CRC校验

	posdtl.cardno= rPack->lvol5;							//交易卡号
	posdtl.purseno = rPack->lvol6;						//消费钱包号
	posdtl.cardbefbal= rPack->lvol9;							//入卡金额
	posdtl.cardaftbal = rPack->lvol10;						//出卡金额
	posdtl.amount = rPack->lvol8;							//本次消费金额
	posdtl.cardcnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	posdtl.transcode = 930033;								//交易代码
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(posdtl.transtime,rPack->spost_code2);			//发生时间(格式化输入的时间)
	posdtl.subsidyno = rPack->lvol11;						//补助批次号
	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);
	posdtl.status[0]='1';
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_posdtl_add ret[%d]",ret);
		if(DB_REPEAT==ret)
			return 0;	
		else
			*pRetCode = E_DB_POSDTL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;		
}
