/* --------------------------------------------
 * 程序名称: F47107.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:  现金支取
 * --------------------------------------------
 * 修改日期:2004-10-12
 * 修改人员:	闻剑
 * 修改描述: 增加记账交易处理
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
#include "account.h"
#include "fdsqc.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;
	//根据卡号和钱包号得到消费者账号(借方)
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

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
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

int F847107(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	int svrfee_feetype[30]; 
	int feetype_cnt=0;
	bool bsrvfee=false;
	
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";
	int card_id=0;
	char sMsg[256]="";
	char physical_no[41]="";
	T_t_tif_tradeserial  tradeserial;
	T_t_pif_card		tCard;
	T_t_tif_savdtl tSavdtl;
	T_t_cif_customer tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;		//帐户表
	InAcc	IA;
	double dSerialNo = 0;
	double self_money = 0; 
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	*pRetCode=0;

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&IA,0,sizeof(IA));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_VSMESS,0);

	card_id=rPack->lvol0;
	des2src(physical_no, rPack->sbank_acc);				//物理卡号

	if(amtcmp(rPack->damt0,0)<=0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt1,0)<0)
	{
		*pRetCode=E_INPUT_CARD_BALA;
		goto L_RETU;
	}
	if(rPack->lvol10<1)
	{
		*pRetCode=E_INPUT_CARD_TXCNT;
		goto L_RETU;
	}

	if(amtcmp(rPack->damt1,rPack->damt0)<0)
	{
		writelog(LOG_ERR,"tCard balance[%lf] amount[%lf]",rPack->damt1,rPack->damt0);
		*pRetCode= E_BALANCE_SHORTAGE;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}

	ret = Get_svrfee_feetype(svrfee_feetype, &feetype_cnt);
	if(ret)
		return ret;	
	
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			*pRetCode=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			*pRetCode=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	trim(physical_no);
	trim(tCard.physical_no);
	if(strcmp(tCard.physical_no,physical_no)!=0)
	{
		writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,physical_no);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	tradeserial.trade_fee = rPack->damt0;													//支取金额
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]purse_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= 	E_ACTNO_NOT_EXIST;
		else
			*pRetCode= 	E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	if(amtcmp(tradeserial.trade_fee,tAccount.cur_freebala)>0)
	{
		writelog(LOG_ERR,"tradeserial.trade_fee[%lf]tAccount.cur_freebala[%lf]",tradeserial.trade_fee,tAccount.cur_freebala);
		*pRetCode=  E_BALANCE_SHORTAGE;
		goto L_RETU;
	}

	//查询支票经费本有无充值记录
	ret=ChkSavdtl(card_id,&tSavdtl);
	if(ret)
	{
		writelog(LOG_ERR,"ChkSavdtl ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(tSavdtl.bill_type)
	{
		case TYPE_CASH:	//现金
			IA.iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//支票
			IA.iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//经费本
			IA.iArrInFeeSwitch[3]=1;
			break;
		default:
			writelog(LOG_ERR,"type[%d]",tSavdtl.bill_type);
			IA.iArrInFeeSwitch[1]=1;
			break;
	}
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//得到收费类别
	if(tCustomer.fee_type<1)
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
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_cif_customer_free_lock_cur();

	for(i=0;i<feetype_cnt;i++)
	{
		if(tCustomer.fee_type == svrfee_feetype[i])
		{
			bsrvfee = true;
			break;
		}
	}
	
	if(bsrvfee)
	{
		self_money = get_person_acc_in(tAccount.account_id ,tAccount.open_date,sysdate) +
					subsidy_in_card(tAccount.customer_id,tAccount.open_date,sysdate) - 
					get_draw_money(tAccount.account_id ,tAccount.open_date,sysdate);
		if(amtcmp(tradeserial.trade_fee,self_money)>0)
			return E_SELF_MONEY_SHORT;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  	//获得流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = D2I(dSerialNo);						//流水号
	tradeserial.other_seri_no = 0;							//上传端流水号
	tradeserial.serial_type = TXCODE_DRAW_DEPOSIT_LOG;		//交易代码
	tradeserial.serial_state = SERISTAT_DEBT;					//流水状态
	des2src(tradeserial.operate_date,sysdate);				//发生日期
	des2src(tradeserial.operate_time,systime);				//发生时间
	des2src(tradeserial.collect_date,sysdate);					//采集日期
	des2src(tradeserial.collect_time,systime);					//采集时间
	des2src(tradeserial.enteract_date,logicdate);				//处理日期
	des2src(tradeserial.enteract_time,systime);				//处理时间
	tradeserial.maindevice_id = rPack->lvol6;					//上传工作站标
	tradeserial.device_id = rPack->lvol7;						//采集设备标识
	tradeserial.card_id = rPack->lvol0;						//卡号
	tradeserial.purse_id = rPack->lvol1;						//钱包号
	tradeserial.customer_id = rPack->lvol2;					//客户标识
	tradeserial.in_balance=rPack->damt1;					//入卡值
	tradeserial.trade_count=rPack->lvol10+1;				//交易次数
	des2src(tradeserial.oper_code , rPack->scust_limit);		//操作员代码
	tradeserial.sys_id = 0;									//外部系统标识

	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	strcpy(IA.sArrInActno[0],tAccount.account_id);
	IA.dArrInAmt[0]=tradeserial.trade_fee;					//账号

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

	//	调用入账子模块
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"流水号:%d 卡号:%d ",IA.iSerialNo,IA.iCardNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial.cost_fee=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	sprintf(sMsg,"支取前卡余额:%.2lf元 卡当前余额:%.2lf元",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	//	插入卡操作流水表
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
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	out_pack->damt2=tradeserial.out_balance;							//出卡值
	out_pack->lserial1=tradeserial.serial_no;								//流水号
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
