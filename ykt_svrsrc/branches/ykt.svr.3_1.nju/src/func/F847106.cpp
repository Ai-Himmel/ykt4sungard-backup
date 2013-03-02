/* --------------------------------------------
 * 程序名称: F47106.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:  现金充值
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

	IA->iMainDevId=p->maindeviceid;				//工作站标识
	IA->iDevId=p->deviceid;						//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;					//交易码
	strcpy(IA->sTxDate,p->operate_date);			//交易日期
	strcpy(IA->sTxTime,p->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);		//记账时间

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
	IA->iTxCnt=p->trade_count;					//交易次数
	IA->dInCardBala=p->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值

	// 修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//出卡值
	return 0;
}

int F847106(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//业务日期
	char sysdate[11]="";
	char systime[9]="";
	int	type=0;
	InAcc	IA;
	double dSerialNo = 0;
	int cardno=0;
	char cardphyid[17]="";
	char sMaxCardBalance[20]="";
	char sMsg[256]="";
	double dMaxCardBalance=0;
	T_t_tif_tradeserial  tradeserial;
	T_t_card		tCard;
	T_t_tif_savdtl		tSavdtl;
	T_t_customer tCustomer;
	T_t_spefee 	tSpeFee;
	T_t_aif_account	tAccount;		//帐户表

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tCard,0,sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&IA,0,sizeof(IA));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_VSMESS,0);
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
	cardno=rPack->lvol0;
	tradeserial.trade_fee = rPack->damt0;					//充值金额
	des2src(cardphyid, rPack->sbank_acc);				//物理卡号
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=DB_t_card_read_by_cardno(cardno, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.cardattr,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.cardattr[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARD_CLOSE;
		else if('3'==tCard.cardattr[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARD_CHANGE;
		else if(tCard.cardattr[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			*pRetCode=E_CARD_LOST;
		else if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			*pRetCode=E_CARD_FREEZE;
		else if(tCard.cardattr[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	trim(cardphyid);
	trim(tCard.cardphyid);
	if(strcmp(tCard.cardphyid,cardphyid)!=0)
	{
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,cardphyid);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	//根据卡号和钱包号得到消费者账号(借方)
	ret=DB_t_aif_account_read_by_cardno_and_purseno(cardno, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_cardno_and_purseno ret[%d]cardno[%d]",ret,cardno);
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

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode= E_AMT_EXCEED_MAX;
		goto L_RETU;
	}
	ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"custid[%d]",tCard.custid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//得到收费类别
	if(0==tCustomer.feetype)
	{
		ret=DB_t_spefee_read_by_deptcode_and_custtype(tCustomer.deptcode, tCustomer.custtype,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.feetype=tCustomer.custtype;
			}
			else
			{
				DB_t_customer_free_lock_cur();
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.feetype=tSpeFee.feetype;
		}
		//更新客户表的收费类别字段
		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_customer_free_lock_cur();
	type=rPack->lvol4;										//交易类型
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(type)
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
			*pRetCode=E_INPUT_DEPOSIT_TYPE;
			goto L_RETU;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(dSerialNo);											//流水号
	tradeserial.other_seri_no = 0;															//上传端流水号
	tradeserial.serial_type = TXCODE_SAVING_CASH;
	tradeserial.serial_state = SERISTAT_DEBT;												//流水状态
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.maindeviceid = rPack->lvol6;												//上传工作站标识
	tradeserial.deviceid = rPack->lvol7;													//采集设备标识
	tradeserial.cardno =cardno;														//卡号
	tradeserial.purseno = rPack->lvol1;													//钱包号
	//tradeserial.custid = rPack->lvol2;													//客户标识
	tradeserial.custid = tCustomer.custid;
	tradeserial.in_balance=rPack->damt1;
	tradeserial.trade_count=rPack->lvol10+1;		//交易次数
	Strncpy_t(tradeserial.opercode , rPack->scust_limit, sizeof(tradeserial.opercode));		//操作员代码

	T_t_cardbitmap tCardBitmap;

	memset(&tCardBitmap,0,sizeof(tCardBitmap));
	ret=DB_t_cardbitmap_read_lock_by_cur_and_cardno(cardno,&tCardBitmap);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_DB_CARD_N;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(tradeserial.trade_count-tCardBitmap.base_no%2000>2000)
	{
		memcpy(tCardBitmap.bitmap,tCardBitmap.bitmap+1000,1000);
		memset(tCardBitmap.bitmap+1000,'0',1000);
		tCardBitmap.base_no+=1000;
	}
	tCardBitmap.bitmap[tradeserial.trade_count-tCardBitmap.base_no-1]='1';
	ret=DB_t_cardbitmap_update_lock_by_cur(&tCardBitmap);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_DB_CARD_N;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_cardbitmap_free_lock_cur();
	tradeserial.sys_id = 0;																//外部系统标识
	switch(type)
	{
		case TYPE_CASH:		//现金
			break;
 		case TYPE_BILL:		//支票
		case TYPE_FUNDBOOK:	//经费本
		case TYPE_OTHER:	//其他
 			tSavdtl.amount=rPack->damt0;				//发生额
 			if(amtcmp(tSavdtl.amount,0)<=0)
				break;
			des2src(tSavdtl.billno,rPack->sphone);		//票据号码
			if(strlen(tSavdtl.billno)<1)
			{
				*pRetCode=E_INPUT_BILLNO;
				goto L_RETU;
			}
			tSavdtl.cardno=tCard.cardno;				//卡号
			des2src(tSavdtl.oper_no,rPack->scust_limit);	//操作员
			tSavdtl.seqno=tradeserial.serial_no;			//流水号
			des2src(tSavdtl.tx_date,sysdate);			//发生日期
			des2src(tSavdtl.tx_time,systime);			//发生时间
			tSavdtl.cnt=1;								//票据数量
			tSavdtl.billtype=type;						//票据类型
			tSavdtl.tx_code=tradeserial.serial_type;		//交易码
			ret=DB_t_tif_savdtl_add(&tSavdtl);
			if(ret)
			{
				if(DB_REPEAT==ret)
					*pRetCode = E_DB_SAVDTL_E;
				else
					*pRetCode = E_DB_SAVDTL_I;
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_TXCODE_NOT_EXIST;
			goto L_RETU;
	}
	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	IA.iCardNo=tCard.cardno;
	IA.iFeeType=tCustomer.feetype;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

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
				tradeserial.depositfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial.managefee=IA.dArrOutAmt[i];
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
	sprintf(sMsg,"充值前卡余额:%.2lf元 卡当前余额:%.2lf元",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
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
	out_pack->damt2=tradeserial.out_balance;		//出卡值
	out_pack->damt3=tradeserial.managefee;			//搭伙费
	out_pack->lserial1=tradeserial.serial_no;			//流水号
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
