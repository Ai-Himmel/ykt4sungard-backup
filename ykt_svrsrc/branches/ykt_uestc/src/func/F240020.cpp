/* --------------------------------------------
 * 程序名称: F240020.cpp
 * 创建日期: 2010-10-22
 * 程序作者: xlh
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台记录流水
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
#include "busqc.h"
static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret = 0;

	//根据卡号和钱包号得到消费者账号(借方)
	IA->iMainDevId=p->maindevice_id;			//工作站标识
	IA->iDevId=p->device_id;					//设备ID
	IA->iSerialNo=p->serial_no;					//流水号
	IA->iTradeNo=p->serial_type;				//交易码
	strcpy(IA->sTxDate,p->operate_date);		//交易日期
	strcpy(IA->sTxTime,p->operate_time);		//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);	//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);	//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);	//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);	//记账时间
	strcpy(IA->sMdeOper,p->oper_code);		//录入 操作员
	strcpy(IA->sChkOper,p->reserve_1);		//复核 操作员
	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;	//联机交易
        IA->iTxCnt=p->trade_count;
	IA->dInCardBala=p->in_balance;				//入卡值						//入卡值
	IA->dOutCardBala=-1;						//出卡值
	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;		//出卡值
	return 0;
}

int F240020(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int i=0;
	char sysdate[11]="";
	char systime[9]="";
	char logicdate[11] = "";
	char buffer[16]="";
	char sMaxCardBalance[20]="";
	double unique=0;
	char dateserialno[30]="";
	char sDebugMsg[1024]="";
	double trans_amt=0.0;
	char sMsg[300]="";
	char serial_nostr[30]="";
	char customer_idstr[30]="";
	T_t_tif_tradeserial  tradeserial;
	double dMaxCardBalance=0;
	InAcc  IA;
	T_t_pif_device t_device;
	T_t_pif_card		card;
	T_t_aif_account	tAccount;		//帐户表
	T_t_bankcard 	bankcard;
	T_t_cfgbank     cfgbank;
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	memset(&t_device,0,sizeof(t_device));
	memset(&card,0,sizeof(card));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&bankcard,0,sizeof(bankcard));
	memset(&cfgbank,0,sizeof(cfgbank));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCUST_AUTH,F_SNAME,F_SNAME2,F_LSERIAL0,F_STX_PWD,F_LVOL5,F_LVOL6,0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);											//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	//判断是否处于日终结算状态
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		*pRetCode=GET_BALANCE_ERR;
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		goto L_RETU;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		*pRetCode=E_TRANS_BANK_SERVICE_NOEXIT;
		writelog(LOG_ERR,"System is balance now!");
		goto L_RETU;
	}
	
	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额必须是整数");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	if(rPack->lvol5<1)
	{
		writelog(LOG_ERR,"trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		strcpy(szMsg,"转账金额不能为0");
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}	
	writelog(LOG_ERR,"lvol5[%d]",rPack->lvol5);
	ret=DB_t_pif_device_read_by_device_id(rPack->lcert_code, &t_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_device_id err,errcode=[%d],device_id=[%d]",ret,tradeserial.device_id);
		return E_DB_DEVICE_R;
	}
	
	ret=DB_t_pif_card_read_by_card_id(rPack->lvol0,&card);
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
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_A;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no=D2I(unique);




	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//采集日期
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//采集时间
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//入帐日期
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//入帐时间
	tradeserial.maindevice_id=GetTransferSystemId();		//子系统号码
	tradeserial.device_id=rPack->lcert_code;			//终端ID
	tradeserial.serial_no=D2I(unique);
	tradeserial.serial_type=TXCODE_BANK_SCHOOL;
	tradeserial.serial_state=SERISTAT_NODEBT;	//流水状态				
	tradeserial.condition_id=SELF_TRANS;	
	tradeserial.sys_id=rPack->lcert_code;	//表示银行		
	tradeserial.trade_fee= rPack->lvol5/100.0;
	tradeserial.in_balance=rPack->lvol6/100.00;
	tradeserial.trade_count=rPack->lvol1+1;	//充值次数
	tradeserial.card_id=rPack->lvol0;
	tradeserial.out_balance=tradeserial.in_balance;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//操作员代码
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
	writelog(LOG_ERR,"lvol5[%lf]",dMaxCardBalance);
	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		goto L_RETU;
	}

	tradeserial.customer_id=card.cosumer_id;
	//读取客户收费类别字段
	writelog(LOG_ERR," card.cosumer_id[%d]",card.cosumer_id);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
		{
			*pRetCode=E_DB_CUTINFO_UPD_N;
			goto L_RETU;
		}
		else
		{
			*pRetCode=E_DB_CUTINFO_UPD_R;
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
				*pRetCode=E_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//校验绑定关系
	ret = DB_t_bankcard_read_by_custid(card.cosumer_id, &bankcard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			strcpy(szMsg,"学工号和银行卡号未绑定");
			return E_DB_BANKCARD_N;
		}
		else
		{
			return E_DB_BANKCARD_R;
		}
	}
	
	ret = DB_t_cfgbank_read_by_bankcode(bankcard.bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}
	
	if(strncmp(tradeserial.enteract_time,cfgbank.bankstarttime,6) < 0
		|| strncmp(tradeserial.enteract_time,cfgbank.bankendtime,6) > 0)
	{
		return E_OUT_BANKTIME;
	}
         writelog(LOG_DEBUG,sDebugMsg);
	T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));	
	get_random(tRefno.mac);
	ret= GetNewRefno(tRefno.refno);
	if(ret)
		return ret;
	des2src(tRefno.lastsaved,tradeserial.operate_time);
	des2src(tRefno.accdate,tradeserial.enteract_date);
	tRefno.termid = tradeserial.sys_id;
	tRefno.termseqno = tradeserial.serial_no;
	des2src(dateserialno,tradeserial.operate_date);
	sprintf(serial_nostr,"%d",tradeserial.serial_no);
	strcat(dateserialno, serial_nostr);
	des2src(tRefno.dateserialno,dateserialno);
	ret=DB_t_refno_add(&tRefno);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_REFNO_E;
		else
			return E_DB_REFNO_I;
	}
	des2src(tradeserial.b_act_id,bankcard.bankcardno);
	des2src(tradeserial.showid,card.showid);
	tradeserial.reviseserial_no=atoi(tRefno.refno);
	//记录流水数据，用于提供正确的流水号，以及银行业务不成功供查询
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		*pRetCode=E_DB_TRADESERIAL_I;
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		goto L_RETU;
	}

	ret=db_commit();
	if(ret)
	{
		*pRetCode=E_DB_COMMIT;
		writelog(LOG_ERR,"db_commit error,error code=[%d]",ret);
		goto L_RETU;

	}
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
		*pRetCode=E_ACC_BANK;
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


	sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
		//业务结束后，回滚事务
	ret=db_rollback();
	if(ret)
	{
		*pRetCode=E_DB_ROLLBACK;
		writelog(LOG_ERR,"db_rollback error,error code=[%d]",ret);
		goto L_RETU;
	}
	
	des2src(out_pack->scust_auth,bankcard.bankcardno);					// 银行卡号
	sprintf(customer_idstr,"%d",tradeserial.customer_id);
	des2src(out_pack->sname,customer_idstr);							// 学工号
	des2src(out_pack->sname2,tRefno.refno);							// 交易参考号 目前没有
	des2src(out_pack->stx_pwd,tRefno.mac);								// 随机数
	out_pack->lserial0=tradeserial.serial_no;									// 终端流水号
	out_pack->lvol5 = D2I(tradeserial.trade_fee*100);									// 交易金额 (分)
	out_pack->lvol6 = D2I(tradeserial.in_balance*100);									// 入卡值(分)

	writelog(LOG_INFO,"bankcardno[%s],stuempno[%s],refno[%s],termseqno[%d],inputamt[%d],befbal[%d]",out_pack->scust_auth,
		out_pack->sname,out_pack->sname2,out_pack->lserial0,out_pack->lvol5,out_pack->lvol6);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
	L_RETU:
	return -1;
}
