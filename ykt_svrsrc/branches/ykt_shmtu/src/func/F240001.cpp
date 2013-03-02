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
	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}

int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	//double unique=0;
	//int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	double trans_amt=0.0;
	char sMsg[255]="";
	char sDebugMsg[255]="";

	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_aif_account	tAccount;		//帐户表
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_pif_card		card;
	InAcc	IA;

	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,0);


	//memset(&tradeserial_bak,0,sizeof(tradeserial_bak));

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
	//判断是否处于日终结算状态
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		goto L_RETU;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		*pRetCode=E_TRANS_BANK_SERVICE_NOEXIT;
		writelog(LOG_ERR,"System is balance now!");
		goto L_RETU;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(rPack->sserial0),&card);
	if(ret)
	{
		*pRetCode=E_TRANS_SCHACC_NOEXIT;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		*pRetCode=E_TRANS_SCHACC_DESTORY;
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		goto L_RETU;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_LOSTING;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_FREEZE;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_WFAIL;
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		goto L_RETU;
	}

	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		goto L_RETU;
	}

	//开始填充流水数据
	//流水号
	//模式修改为，测试入帐产生流水号，记录流水结构，正式入账只修改该
	//流水的出卡值以及流水状态
/*
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}
*/

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol7, &tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_R;
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",ret,rPack->lvol7);
		goto L_RETU;
	}

	if(tradeserial.serial_state == SERISTAT_DEBT)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		goto L_FINISHED;
	}
	/*
	tradeserial.serial_no=D2I(unique);
	//记录流水号，作为冲正使用
	//temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=rPack->lvol0;	//上传端流水号
	tradeserial.serial_type=TXCODE_BANK_SCHOOL;	//交易代码
	tradeserial.serial_state=SERISTAT_NODEBT;	//流水状态
	tradeserial.card_id=atoi(rPack->sserial0);
	tradeserial.purse_id=0;
	tradeserial.in_balance=double((rPack->lvol6)/100.00);	//入卡金额
	tradeserial.out_balance=tradeserial.in_balance;			//出卡金额
	tradeserial.trade_count=rPack->lvol1+1;				//当前卡中交易次数

	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//采集日期
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//采集时间
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//入帐日期
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//入帐时间
	tradeserial.maindevice_id=GetTransferSystemId();		//子系统号码
	tradeserial.device_id=atoi(rPack->sorder2);			//终端ID
	tradeserial.trade_fee=(rPack->lvol5)/100.0;	//转帐金额
	Strncpy_t(tradeserial.b_act_id,rPack->scust_auth,sizeof(tradeserial.b_act_id));
	tradeserial.sys_id=rPack->lvol2;						//表示银行
	tradeserial.condition_id=SELF_TRANS;						//自动/自助转帐标识
	tradeserial.customer_id=card.cosumer_id;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//操作员代码
*/
	//判断转帐金额是否超出钱包最大限额
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_TRANS_SCHACC_NOEXIT;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
	}

	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		goto L_RETU;
	}
	//读取客户收费类别字段
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_TRANS_UNKNOW_ERROR;
			goto L_RETU;
		}
	}

	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				*pRetCode=E_TRANS_UNKNOW_ERROR;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//填写入账结构,问问闻剑
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tAccount.account_id);			//贷方帐户,持卡人账户
	des2src(IA.sArrInActno[2],rPack->sstation0);				//借方帐号，由前置机上传
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
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
	
L_FINISHED:
	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;

	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
	
L_RETU:
	return -1;
}

