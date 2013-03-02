/* --------------------------------------------
 * 程序名称: F930031.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  收集消费流水入账
 * --------------------------------------------
 * 修改日期:2004-10-12
 * 修改人员:	闻剑
 * 修改描述:增加记账交易处理
 * 版本信息:1.0.0.1
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
#include "interfacefunc.h"
#include "busqc.h"
/*
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
		return E_999_DATE;							//上传流水交易日期有误
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
	if((p->transmark!=0X99)&&(p->transmark!=0xFE)&&	(p->transmark!=0X02))
	{
		return 	p->transmark+E_999_0X00;			//把返回码置为交易标记
	}
	if(amtcmp(p->cardbefbal- p->cardaftbal,p->amount)!=0)
	{
			return E_999_CARD_BALANCE;					//上传流水出入卡余额有误
	}
	if(0X99==p->transmark||0x02==p->transmark)
	{
		if(amtcmp(p->amount,0)<0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	else
	{
		//冲正交易,发生额为负数
		if(amtcmp(p->amount,0)>=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	return 0;
}
*/
int F930031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
//	writelog(LOG_INFO,"cpack:[%s]",pAccTrans->cpackdata);
//	writelog(LOG_INFO,"%s:930031 Start",getdbtimestamp(NULL));
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

	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);
	posdtl.devseqno= rPack->lvol4;							//上传端流水号
	posdtl.transmark=rPack->lvol12;							//999交易标记
	posdtl.sysid  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(posdtl.devphyid, rPack->sdate1);				//物理设备ID
	ret=GetDeviceidByDevphyid(posdtl.devphyid,&(posdtl.termid));
	if(ret)
		return ret;
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
	posdtl.cardbefbal= rPack->lvol9/100.0;							//入卡金额
	posdtl.cardaftbal = rPack->lvol10/100.0;						//出卡金额
	posdtl.amount = rPack->lvol8/100.0;							//本次消费金额
	posdtl.cardcnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
	posdtl.transcode = 930031;								//交易代码
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
	des2src(posdtl.transtime,rPack->spost_code2);			//发生时间(格式化输入的时间)
	if(strcmp(posdtl.transdate,"20000000") != 0)
	{
		ret=IsInvalidDateTime(posdtl.transdate,"YYYYMMDD");
		if(ret)
		{
			return E_999_DATE;							//上传流水交易日期有误
		}
		ret=IsInvalidDateTime(posdtl.transtime,"HHMMSS");
		if(ret)
		{
			return E_999_TIME;							//上传流水交易时间有误
		}
	}
	else
	{
		des2src(posdtl.transdate,posdtl.coldate);
		des2src(posdtl.transtime,posdtl.coltime);
	}
	posdtl.status[0]='1';
	*pRetCode=0;

	g_dbchkerr=0;
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		g_dbchkerr=1;
		if(DB_REPEAT==ret)
		{	
			writelog(LOG_ERR,"serial_no[%d]cardno[%d]devphyid[%s]transdate[%s]transtime[%s]ret[%d]",posdtl.devseqno,posdtl.cardno,posdtl.devphyid,posdtl.transdate,posdtl.transtime,ret);
			return 0;
		}
		else
			return E_DB_POSDTL_I;
	}
	g_dbchkerr=1;
//	writelog(LOG_INFO,"%s:930031 OK",getdbtimestamp(NULL));
	return 0;
}
