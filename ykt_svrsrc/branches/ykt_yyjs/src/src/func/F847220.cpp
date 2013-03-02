/* --------------------------------------------
 * 程序名称: F847220.sqc
 * 创建日期: 2006-9-25
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  上大账务解款
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
#include "dbfunc_foo.h"

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

int F847220(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	double 	tx_money = 0.0;
	char  ia_buf[1024]="";
	char sMsg[256]="";
	double	dUniNo = 0;
	T_t_tif_tradeserial serial;
	T_t_group_cash_report group_cash;
	int group_id;
	T_t_groups groups;
	InAcc IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int i;

	ResetNormalCPack(&aPack,0,1);

	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		writelog(LOG_ERR,"操作员密码错误operator[%s]",rPack->scard0);
		*pRetCode = ret;
		goto L_RETU;
	}

	if(strlen(rPack->sbank_acc) <= 0)
	{
		*pRetCode = E_ACTNO_NOT_EXIST;
		goto L_RETU;
	}

	tx_money = rPack->damt1;
	if(amtcmp(tx_money,0.0)<=0)
	{
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;
	}

	memset(&groups,0,sizeof groups);

	//ret = DB_t_groups_read_by_group_acc(rPack->sbank_acc,&groups);
	ret = DB_t_groups_read_by_group_id(rPack->sbank_acc,&groups);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_ACTNO_NOT_EXIST;
		else
			*pRetCode = E_DB_GROUP_R;
		goto L_RETU;
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniNo);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	
	// 查询组可解款余额
	memset(&group_cash,0,sizeof group_cash);
	ret = DB_t_group_cash_report_read_lock_by_c1_and_group_id(groups.group_id,&group_cash);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_FAN_ACC_NOT_EXISTS;
		else
			*pRetCode = E_DB_GRP_CASH_RPT_R;
		goto L_RETU;
	}

	if(amtcmp(tx_money,group_cash.cur_money)>0)
	{
		writelog(LOG_ERR,"操作员组余额[%.2lf], 解款金额[%.2lf]",group_cash.cur_money,tx_money);
		*pRetCode = E_FAN_ACC_INSUFFICIENT;
		DB_t_group_cash_report_free_lock_by_c1();
		goto L_RETU;
	}

	// 生成流水
	memset(&serial,0,sizeof serial);
	serial.serial_no = D2I(dUniNo);
	serial.serial_state = SERISTAT_DEBT;
	serial.serial_type = TXCODE_FAN_PAY_MONEY;
	getsysdate(serial.operate_date);
	getsystime(serial.operate_time);
	des2src(serial.collect_date,serial.operate_date);
	des2src(serial.collect_time,serial.operate_time);
	GetLogicDate(serial.enteract_date);
	des2src(serial.enteract_time,serial.operate_time);

	des2src(serial.oper_code,rPack->scard0);
	des2src(serial.reserve_1,rPack->scert_addr);
	serial.in_balance = tx_money;
	serial.trade_fee = tx_money;
	des2src(serial.showid,group_cash.group_id);

	// 入账
	memset(&IA,0,sizeof IA);
	//IA.dInCardBala = serial.in_balance;
	IA.dArrInAmt[0] = serial.trade_fee;
	IA.iCardNo = 0;
	//收费类别为 1
	IA.iFeeType = 1;
	IA.pVoidPointer = ia_buf;
	ret = process(&IA,&serial);
	if(ret)
	{
		writelog(LOG_ERR,"入账失败ret [%d]",ret);
		*pRetCode  = ret;
		DB_t_group_cash_report_free_lock_by_c1();
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LVOL1,F_DAMT1,0);
	
	sprintf(out_pack->vsmess,"流水号:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	//serial.out_balance = 
	strcat(out_pack->vsmess,(char*)IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	out_pack->lvol1 = serial.serial_no;
	group_cash.cur_money = group_cash.cur_money - serial.trade_fee;

	des2src(group_cash.last_check_date,serial.operate_date);
	des2src(group_cash.last_check_time,serial.operate_time);
	out_pack->damt1 = group_cash.cur_money;

	//更新组未解款金额
	ret = DB_t_group_cash_report_update_lock_by_c1(&group_cash);
	if(ret)
	{
		*pRetCode = E_DB_GRP_CASH_RPT_U;
		goto L_RETU;
	}
	// add 
	DB_t_group_cash_report_free_lock_by_c1();
	//保存流水
	ret = DB_t_tif_tradeserial_add(&serial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

