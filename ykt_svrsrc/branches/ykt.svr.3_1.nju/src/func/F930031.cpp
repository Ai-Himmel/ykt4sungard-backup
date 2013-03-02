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
int F930031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	CAccTrans *pAccTrans=CAccTrans::getInstance();
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

	des2src(posdtl.coldate,pAccTrans->trans.transdate);
	des2src(posdtl.coltime,pAccTrans->trans.transtime);
	posdtl.devseqno= rPack->lvol4;							//上传端流水号
	posdtl.transmark=rPack->lvol12;							//999交易标记
	posdtl.sysid  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	des2src(posdtl.devphyid, rPack->sdate1);				//物理设备ID
	GetDeviceidByDevphyid(posdtl.devphyid,&(posdtl.termid));
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
	posdtl.status[0]='1';
	if(strcmp(posdtl.transdate,"20000000") != 0)
	{
		ret=IsInvalidDateTime(posdtl.transdate,"YYYYMMDD");
		if(ret)
		{
			posdtl.errcode=E_999_DATE;//上传流水交易日期有误
			posdtl.status[0]='4';
			strcpy(posdtl.errmsg,"发生日期格式错误");
		}
		ret=IsInvalidDateTime(posdtl.transtime,"HHMMSS");
		if(ret)
		{
			posdtl.errcode=E_999_TIME;//上传流水交易时间有误
			posdtl.status[0]='4';
			strcpy(posdtl.errmsg,"发生时间格式错误");			
		}
	}
	else
	{
		des2src(posdtl.transdate,posdtl.coldate);
		des2src(posdtl.transtime,posdtl.coltime);
	}
	if((amtcmp(posdtl.amount,-500)<0)||(amtcmp(posdtl.amount,500)>0))
	{
		posdtl.errcode=E_999_AMT;//金额错误
		posdtl.status[0]='4';
		strcpy(posdtl.errmsg,"发生金额太大");
	}
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
