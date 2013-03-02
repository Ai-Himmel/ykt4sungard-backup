/* ----------------------------------------------------------
 * 程序名称：F847315
 * 创建日期：2007-04-25
 * 程序作者：何林青
 * 版本信息：1.0.0.0
 * 程序功能：多媒体补助领取
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "pubdb.h"
#include "fdsqc.h"
#include "dbfunc.h"
#include "pubfunc.h"
#include "account.h"

#ifndef	SEGSIZE
	#define 	SEGSIZE	1024
#endif
#ifndef DEBUG
	#define DEBUG
#endif


#ifdef __cplusplus
extern "C" {
#endif 

#define RETSET_WRITE_ERR_CARD		240107		//写卡失败更新卡状态
#define GET_ASSISTANCE				240104		//领取补助
#define TRADE_INNER_TRANS_FUNC	240001		//自助转帐

// EXEC SQL INCLUDE SQLCA;
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

//写卡失败冲正(实际并不冲正，只是改写卡状态)
static int Reset_WriteErrCard(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg)
{
  int ret = 0;
    T_t_pif_card tCard;
    T_t_tif_tradeserial tTradeSerial;
    T_t_tif_writefailed tWriteFailed;
    char logicdate[11] = "";
    double dUniqNo = 0; 
    
    memset(&tCard, 0, sizeof tCard);
    memset(&tTradeSerial, 0, sizeof tTradeSerial);
    memset(&tWriteFailed, 0, sizeof tWriteFailed);
    

    ret = DB_t_tif_tradeserial_read_by_serial_no(in_pack->lvol1,&tTradeSerial);  //消费流水号
    if (ret)
    {
        writelog(LOG_DEBUG,"输入号不存在消费流水号[%d]",in_pack->lvol1);
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_TRADESERIAL_N;
        }
        else
        {
            *pRetCode = E_DB_TRADESERIAL_R;
        }
        goto L_RETU;
    }
    
    ret = DB_t_pif_card_read_lock_by_cur_and_card_id(tTradeSerial.card_id,&tCard);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_CARD_N;
        }
        else
        {
            *pRetCode = E_DB_CARD_R;
        }
        goto L_RETU;
    }
    
    GetLogicDate(logicdate);
    tWriteFailed.card_id = tCard.card_id;
    des2src(tWriteFailed.tx_date,logicdate);
    writelog(LOG_INFO,"大钱包交易金额[%f]",tTradeSerial.trade_fee);


    tCard.state_id[CARDSTAT_TYPE_WFAIL] = STATE_TRUE;
    ret = DB_t_pif_card_update_lock_by_cur(&tCard);
    if (ret)
    {
        *pRetCode = E_DB_CARD_U;
         goto L_RETU;
    }
    DB_t_pif_card_free_lock_by_cur();

        // 大钱包写卡失败
        ret = getNewUniqNo(KEYTYPE_WRITEFAILED, &dUniqNo);              //获得写卡失败表最大ID号
        if (ret)
        {
            writelog(LOG_ERR,"ret[%d]",ret);
            *pRetCode = ret;
            goto L_RETU;
        }
        tWriteFailed.id = D2I(dUniqNo);
        tWriteFailed.serial_no = tTradeSerial.serial_no;
        tWriteFailed.serial_type = tTradeSerial.serial_type;
        tWriteFailed.purese_no = PURSE_NO_ONE;
        tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
        tWriteFailed.deal_bala = tTradeSerial.trade_fee;
        des2src(tWriteFailed.comments, "大钱包写卡失败");
        ret = DB_t_tif_writefailed_add(&tWriteFailed);
        if (ret)
        {
            *pRetCode = E_DB_WRITEFAILED_I;
            goto L_RETU;
        }        
    return 0;
L_RETU:
	return -1;	

}

static int get_assistance(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg)
{

//	char key[32+1]="";
  	int ret = 0;
	int i=0;
	int row=0;
	int next_flag=0;
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double dUniqno = 0;
	char sMaxCardBalance[20]="";
	char sMsg[256]="";
	double dMaxCardBalance=0;

//	INNER_TRANS_REQUEST  from_pos;

	T_t_tif_tradeserial  tradeserial;
	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;
	T_t_tif_subsidy	tSubsidy;
	T_t_pif_card	tCard;
	InAcc	IA;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
   	SetCol(handle,F_SSERIAL1,F_LVOL2,F_DAMT1,F_DAMT2,F_DAMT3,F_VSMESS,F_SEMAIL,0);

//	memset(&from_pos,0,sizeof(from_pos));
//	memcpy(&from_pos,pNode,sizeof(from_pos));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
	memset(&IA,0,sizeof(IA));

	card_id=in_pack->lvol0;
	
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}


	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}
	/*
	ret=get_stuemp_no_by_card_no(tCard.card_id,stuemp_no);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		return ret;
	}
	*/
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		return ret;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	//根据卡号和钱包号得到消费者账号(借方)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	
	ret=DB_t_tif_subsidy_open_select_for_update_by_c1_and_cust_no_and_status(tCard.cosumer_id, "2");
	if(ret)
	{
		return E_DB_SUBSIDY_R;
	}
	while(1)
	{
		memset(&tSubsidy,0,sizeof(tSubsidy));
		ret=DB_t_tif_subsidy_fetch_select_by_c1(&tSubsidy);
		if(ret)
		{			
			if(DB_NOTFOUND==ret)
			{
				DB_t_tif_subsidy_close_select_by_c1();
				if(row)
					break;
				else
					return E_USER_NO_SUBSIDY;
			}
			else
				return E_DB_SUBSIDY_R;
		}
		
		row++;

		if(amtcmp(tAccount.cur_bala+tSubsidy.amount,dMaxCardBalance)>0)
		{
			DB_t_tif_subsidy_close_select_by_c1();
			return E_AMT_EXCEED_MAX;
		}
		tradeserial.trade_fee+=tSubsidy.amount;			//补助金额
		if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
		{
			tradeserial.trade_fee-=tSubsidy.amount;
			DB_t_tif_subsidy_close_select_by_c1();
			next_flag=1;
			break;
		}
		strcpy(tSubsidy.status,"3");
		getsysdate(tSubsidy.get_date);
		getsystime(tSubsidy.get_time);
		tSubsidy.card_no=card_id;
		des2src(out_pack->semail,tSubsidy.summary); //备注说明
		ret=DB_t_tif_subsidy_update_lock_by_c1(& tSubsidy);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_USER_NO_SUBSIDY;
			else
				return E_DB_SUBSIDY_U;
		}
	}
	
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	//得到收费类别
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
				return E_DB_SPEFEE_R;
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
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();

	des2src(Operator,"web");						       	//操作员

	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}
	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//发生日期
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial.collect_date,tradeserial.operate_date);					//采集日期
	des2src(tradeserial.collect_time,tradeserial.operate_time);					//采集时间
	des2src(tradeserial.enteract_date,logicdate);							//处理日期
	des2src(tradeserial.enteract_time,tradeserial.operate_time);							//处理时间
	tradeserial.serial_no = D2I(dUniqno);									//流水号
	tradeserial.serial_type = TXCODE_GET_SUBSIDY;						//补贴
	tradeserial.serial_state = SERISTAT_DEBT;								//流水状态
	tradeserial.maindevice_id = maindevice_id;						//上传工作站标识
	tradeserial.device_id = device_id;							//采集设备标识
	tradeserial.card_id = card_id;										//交易卡号
	tradeserial.customer_id=tCard.cosumer_id;								//客户号
	des2src(tradeserial.oper_code,Operator);
//	tradeserial.other_seri_no=;
	tradeserial.trade_count=in_pack->lvol1+1;		//交易次数
	// writelog(LOG_DEBUG,"上传入卡值%.2lf",in_pack->damt0);
	tradeserial.in_balance=in_pack->damt0;			//入卡值
	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
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
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
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
	tradeserial.out_balance=IA.dOutCardBala;
	out_pack->lvol2=next_flag;//是否还有下一笔补助
	out_pack->damt1=tradeserial.trade_fee;		//补助金额
	out_pack->damt2=tradeserial.out_balance;	//出卡值
	out_pack->damt3=tradeserial.boardfee;		//搭伙费金额
//	out_pack->lserial0 = tradeserial.serial_no;		//流水号
	sprintf(out_pack->sserial1,"%d", tradeserial.serial_no);	//流水号
	
	sprintf(sMsg,"交易前卡余额:%.2lf元 卡当前余额:%.2lf元",tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_DB_COMMIT;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


int F847315(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int sendNo = 0;
	char BankCardNo[21]="";
	char TerminalId[11]="";
	char tradecode[6+1]="";
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	// 用于根据请求包整理本CPACK包的头清空包头位图和包体中的数据
	ResetNormalCPack(&aPack,0,1);


	//判断交易代码，进行相应处理

	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	memcpy(tradecode,in_pack->sclose_emp,sizeof(in_pack->sclose_emp));
	sendNo = in_pack->lvol0;
	memcpy(BankCardNo,in_pack->scust_auth,sizeof(BankCardNo));	//银行卡号
	memcpy(TerminalId,in_pack->sorder2,sizeof(TerminalId));
	tradecode[6]=0;
	writelog(LOG_INFO,"Trade start,trade code=[%6.6s],card_id=[%d],bankcardno=[%s],TerminalId=[%s]!",tradecode,sendNo,BankCardNo,TerminalId);
	switch(atoi(tradecode))
	{
	//写卡失败处理重置卡信息
		case RETSET_WRITE_ERR_CARD:
			ret=Reset_WriteErrCard(in_pack,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			return 0;
		//领取补助
		case GET_ASSISTANCE:
			ret=get_assistance(in_pack,handle,pRetCode,szMsg);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
			return 0;
		default:
			writelog(LOG_INFO,"This trade can't supplied,tradecode=[%d]!",atoi(tradecode));
			*pRetCode=E_TRANS_FUNC_NONSUPPORT;
			goto L_RETU;
	}

L_RETU:

	//writelog(LOG_ERR,"Trade faild,trade code=[%s],return code=[%d]!",to_pos.TradeCode,*pRetCode);
	return *pRetCode;

}

#ifdef __cplusplus
}
#endif 



