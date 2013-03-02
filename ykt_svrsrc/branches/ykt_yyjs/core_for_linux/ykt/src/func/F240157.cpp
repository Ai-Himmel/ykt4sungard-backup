/* --------------------------------------------
 * 程序名称: F240157.c
 * 创建日期: 2005-06-24
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存补帐
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
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}

int F240157(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	double dUniqno = 0;
	int card_id=0;
	int iSerialno=0;
	char physical_no[41]="";
	char sMaxCardBalance[20]="";
	char sMsg[256]="";
	double dMaxCardBalance=0;
	T_t_pif_card		tCard;
	T_t_cif_customer tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;		//帐户表
	T_t_tif_tradeserial tradeserial;
	T_t_tif_diff_transfer tDiffTransfer;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tDiffTransfer,0,sizeof(tDiffTransfer));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	ResetNormalCPack(&aPack,0,1);

	if(amtcmp(rPack->damt1,0)==0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_AUTH_OPER_NOT_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_AUTH_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	card_id=rPack->lvol0;
	des2src(physical_no, rPack->sbank_acc);				//物理卡号
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(card_id!=tCard.card_id)
	{
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode=E_CARD_CHANGE;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_LOST])
			*pRetCode=E_CARDNO_LOST;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
			*pRetCode=E_CARDNO_FREEZE;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_WFAIL])
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
	iSerialno=rPack->lserial0;
	ret=DB_t_tif_diff_transfer_read_lock_by_c0_and_op_date_and_local_sn(rPack->sdate0,iSerialno,&tDiffTransfer);
	if(ret)
	{
		writelog(LOG_ERR,"operater_date[%s]Serialno[%d]",rPack->sdate0,iSerialno);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_SERIALNO_NOT_EXIST;
		else
			*pRetCode=E_DB_TRADESERIAL_R;
		goto L_RETU;
	}
	if(card_id!=tDiffTransfer.card_id)
	{
		writelog(LOG_ERR,"input card_id [%d],DiffTransfer card_id[%d]",card_id,tDiffTransfer.card_id);
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_CARDNO_SERIAL_NE;
		goto L_RETU;
	}
	if(SERISTAT_NODEBT!=tDiffTransfer.status)
	{
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		goto L_RETU;
	}
	if(amtcmp(tDiffTransfer.diff_amt,rPack->damt1)!=0)
	{
		DB_t_tif_diff_transfer_free_lock_by_c0();
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	tDiffTransfer.status=SERISTAT_DEBT;
	ret=DB_t_tif_diff_transfer_update_lock_by_c0(&tDiffTransfer);
	if(ret)
	{
		*pRetCode=E_DB_DIFF_TRANSFER_U;
		goto L_RETU;
	}
	DB_t_tif_diff_transfer_free_lock_by_c0();
	//根据卡号和钱包号得到消费者账号(借方)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_NOT_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	tradeserial.trade_fee = rPack->damt1;				//充值金额
	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode= E_AMT_EXCEED_MAX;
		goto L_RETU;
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

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = D2I(dUniqno);					//流水号
	tradeserial.other_seri_no = 0;								//上传端流水号
	tradeserial.serial_type  = TXCODE_MAKEUPSERIAL;
	tradeserial.serial_state = SERISTAT_DEBT;						//流水状态
	des2src(tradeserial.operate_date,sysdate);					//发生日期
	des2src(tradeserial.operate_time,systime);					//发生时间
	des2src(tradeserial.collect_date,sysdate);						//采集日期
	des2src(tradeserial.collect_time,systime);						//采集时间
	des2src(tradeserial.enteract_date,logicdate);					//处理日期
	des2src(tradeserial.enteract_time,systime);					//处理时间
	tradeserial.maindevice_id = rPack->lvol6;						//上传工作站标识
//	tradeserial.device_id = rPack->lvol7;							//采集设备标识
	tradeserial.card_id =card_id;									//卡号
	tradeserial.purse_id = PURSE_NO_ONE;						//钱包号
	tradeserial.customer_id = tCard.cosumer_id;					//客户标识
	tradeserial.in_balance=rPack->damt0;						//入卡值
	tradeserial.trade_count=rPack->lvol1+1;					//交易次数
	des2src(tradeserial.oper_code,rPack->scust_limit);			//操作员代码
	tradeserial.sys_id = 0;										//外部系统标识

	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

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
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
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
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//流水号
	out_pack->damt2=tradeserial.trade_fee;			//充值金额
	out_pack->damt3=tradeserial.boardfee;			//搭伙费
	out_pack->damt4=tradeserial.out_balance;		//出卡值
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
