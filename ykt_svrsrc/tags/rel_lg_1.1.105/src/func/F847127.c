/* --------------------------------------------
 * 程序名称: F847127.c
 * 创建日期: 2005-11-18
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 手工借-手工贷
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

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//工作站标识
	IA->iDevId=p->device_id;						//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;					//交易码
	strcpy(IA->sTxDate,p->operate_date);			//交易日期
	strcpy(IA->sTxTime,p->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,p->oper_code);			//操作员(发生错帐的操作员)
	strcpy(IA->sChkOper,p->reserve_1);			//复核操作员

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//无卡交易
	IA->iTxCnt=0;								//交易次数
	IA->dInCardBala=0;							//入卡值
	IA->dOutCardBala=0;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//出卡值
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}

int F847127(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	double dUniqno = 0;
	char sMsg[256]="";
	T_t_tif_tradeserial tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);

	if(amtcmp(rPack->damt0,0)==0)
	{
		*pRetCode=E_INPUT_AMT_NULL;
		goto L_RETU;
	}
	trim(rPack->sbank_acc);
	trim(rPack->sbank_acc2);
	if(strcmp(rPack->sbank_acc,rPack->sbank_acc2)==0)
	{
		*pRetCode=E_INPUT_2ACTNO_EQ;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper1[%s]oper2[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_INPUT_2OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_INPUT_OPER_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_INPUT_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.trade_fee = rPack->damt0;						//发生金额
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  		//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = (int)dUniqno;							//流水号
	tradeserial.other_seri_no = 0;								//上传端流水号
	tradeserial.serial_type  = TXCODE_CARD_DBCR;				//交易码
	tradeserial.serial_state = SERISTAT_DEBT;						//流水状态
	des2src(tradeserial.operate_date,sysdate);					//发生日期
	des2src(tradeserial.operate_time,systime);					//发生时间
	des2src(tradeserial.collect_date,sysdate);						//采集日期
	des2src(tradeserial.collect_time,systime);						//采集时间
	des2src(tradeserial.enteract_date,logicdate);					//处理日期
	des2src(tradeserial.enteract_time,systime);					//处理时间
	tradeserial.maindevice_id = rPack->lvol6;						//上传工作站标识
	tradeserial.in_balance=rPack->damt0;						//入卡值
	tradeserial.trade_count=0;									//交易次数
	des2src(tradeserial.oper_code,rPack->scust_limit2);			//错帐操作员代码
	des2src(tradeserial.reserve_1,rPack->scust_limit);			//操作员代码
	tradeserial.sys_id = 0;										//外部系统标识

	IA.iCardNo=0;
	IA.iFeeType=1;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	des2src(IA.sArrInActno[0],rPack->sbank_acc);				//借方帐号
	des2src(IA.sArrInActno[1],rPack->sbank_acc2);				//贷方帐号
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"流水号:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	strcat(out_pack->vsmess,IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//流水号
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

