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
#include "acctrans.h"
#include "busqc.h"

static int check(T_t_posdtl *p)
{
	int ret=0;
//	if(strlen(p->crc)==0)
//	{
//		return E_999_CRC;							//上传流水CRC校验错误
//	}
	if(strcmp(p->transdate,"20000000") != 0)
	{
		ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
		if(ret)
		{
			return E_999_DATE;						//上传流水交易日期有误
		}
	}
	else
		getsysdate(p->transdate);
	if(strcmp(p->transtime,"000000") != 0)
	{
		ret=IsInvalidDateTime(p->transtime,"HHMMSS");
		if(ret)
		{
			return E_999_TIME;							//上传流水交易时间有误
		}
	}
	else
		getsystime(p->transtime);
	// &&(p->transmark!=0xF0)
	
	if((p->transmark!=0XFA))
	{
		return 	p->transmark+E_999_0X00;			//把返回码置为交易标记
	}
	if(p->cardbefbal - p->amount != p->cardaftbal)
	{
		return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
	}
	return 0;
}

int F950029(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
//	int ver = posdtl.comu_ver / 10;
//	if( 0x81 == posdtl.comu_ver || 0x81 == ver )
//	{
//	posdtl.run_reason = rPack->lbank_acc_type2;				//启动原因
//		posdtl.fee_code = rPack->lbank_acc_type2;				// 将启动原因保存到收费科目中
//	}
//	else
//	{
//		posdtl.fee_code = 0;
//	}
//	des2src(posdtl.crc,rPack->sbank_code2);				//CRC校验

	//posdtl.man_fee = rPack->lvol11;						//
	posdtl.cardno= rPack->lvol5;							//交易卡号
	//posdtl.purseno = rPack->lvol6;						//消费钱包号
	posdtl.purseno = 0;
	posdtl.cardbefbal= rPack->lvol9;							//入卡金额
	posdtl.cardaftbal = rPack->lvol10;						//出卡金额
	posdtl.amount = rPack->lvol8;							//本次消费金额
	if(posdtl.amount>0)
		posdtl.amount = -posdtl.amount;
	posdtl.cardcnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	posdtl.transcode = 930031;								//交易代码
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(posdtl.transtime,rPack->spost_code2);			//发生时间(格式化输入的时间)
	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);	
	ret=check(&posdtl);
	if(ret)
	{
		posdtl.errcode=ret;
		if(posdtl.transmark==240 || posdtl.transmark==2)
		{
			posdtl.status[0]='6';							//中途拔卡交易
			// 标记为中途拔卡
			posdtl.transmark = 2;
		}
		else
		{
			posdtl.status[0]='5';								//无效交易
			strcpy(posdtl.accdate,posdtl.coldate);
			strcpy(posdtl.acctime,posdtl.coltime);
		}
	}
	else
		posdtl.status[0]='1';
	g_dbchkerr=0;
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		g_dbchkerr=1;
		writelog(LOG_DEBUG,"serial_no[%d]cardno[%d]deviceid[%s]transdate[%s]transtime[%s]",posdtl.devseqno,posdtl.cardno,posdtl.devphyid,posdtl.transdate,posdtl.transtime);
		if(DB_REPEAT==ret)
			return 0;
		else
			*pRetCode = E_DB_POSDTL_I;
		goto L_RETU;
	}
	g_dbchkerr=1;
	return 0;
L_RETU:
	return -1;
}

