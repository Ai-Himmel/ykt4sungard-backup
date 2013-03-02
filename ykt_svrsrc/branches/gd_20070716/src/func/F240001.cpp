/* --------------------------------------------
 * 程序名称: F240001.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转帐正式入账
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
	T_t_aif_account tAccount;

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
	strcpy(IA->sMdeOper,p->oper_code);			//操作员
	strcpy(IA->sChkOper,p->reserve_1);			//复核操作员


	IA->iUseCardFlag=IS_YES;						//卡交易
	IA->iTxCnt=p->trade_count;					//交易次数
	IA->dInCardBala=p->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	switch(IA->iTradeNo)
	{
	case TXCODE_BANK_YCT:
	case TXCODE_BANK_SCHOOL:
		p->out_balance=IA->dOutCardBala;			//出卡值
		break;
	case TXCODE_BANK_ELEC:
		memset(&tAccount,0,sizeof tAccount);
		ret = DB_t_aif_account_read_by_account_id(IA->sArrInActno[1],&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account [%s] error",IA->sArrInActno[1]);
			return E_DB_ACCOUNT_R;
		}
		p->out_balance = tAccount.cur_freebala;
		break;
	}
	return 0;
}

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	double trans_amt=0.0;
	char sMsg[255]="";
	char sDebugMsg[255]="";

	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account	tAccount;
	InAcc	IA;

	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);



	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		goto L_RETU;
	}

	//判断设备是否登陆
	if(0!=device_login_yes_or_no(atoi(rPack->sorder2)))
	{
		*pRetCode=E_TRANS_TERM_NOLOGIN;
		writelog(LOG_ERR,"Device don't login");
		goto L_RETU;
	}

	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		goto L_RETU;
	}

	//模式修改为，测试入帐产生流水号，记录流水结构，正式入账只修改该
	//流水的出卡值以及流水状态

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol7, &tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_R;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",
				 ret,rPack->lvol7);
		goto L_RETU;
	}

	if(tradeserial.serial_state != SERISTAT_NODEBT)
	{
		*pRetCode = E_TRANS_UNKNOW_ERROR;
		sprintf(szMsg,"交易流水状态不正确,serialno[%d]",rPack->lvol7);
		goto L_RETU;
	}
	//填写入账结构,问问闻剑
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tradeserial.out_account_id);			//贷方帐户,持卡人账户
	des2src(IA.sArrInActno[1],tradeserial.in_account_id);			//借方帐号，由前置机上传
	IA.iCardNo=tradeserial.card_id;
	IA.iFeeType=tradeserial.comu_ver; // 在试入账交易中这个字段保存 权限类别
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}

	sprintf(sDebugMsg,"流水号:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_BANK_TRANSFER:
				trans_amt=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(sDebugMsg,sMsg);
		}
	}

	//结束填充流水数据
	tradeserial.serial_state=SERISTAT_DEBT;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_cur error,error code=[%d]",ret);
		goto L_RETU;
	}


	sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);

	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;
	out_pack->lvol2=D2I(tradeserial.out_balance * 100);
	des2src(out_pack->sdate0,logicdate);

	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
	
L_RETU:
	return -1;
}

