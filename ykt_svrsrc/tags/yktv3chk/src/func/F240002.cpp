/* --------------------------------------------
 * 程序名称: F240002.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 圈存转账后台模拟入账交易
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
#include "busqc.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
#if 0
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
#endif
	return 0;
}

int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int iSeqno=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	double trans_amt=0.0;
	char sMsg[255]="";
	char sDebugMsg[255]="";

	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_account	tAccount;		//帐户表
	T_t_customer	tCustomer;
	T_t_spefee 	tSpeFee;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_card		card;
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
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,0);


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

	ret=DB_t_card_read_by_cardno(atoi(rPack->sserial0),&card);
	if(ret)
	{
		*pRetCode=E_TRANS_SCHACC_NOEXIT;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}

	if(strncmp(card.cardattr,CARDSTAT_LOGOUT,4)==0)
	{
		*pRetCode=E_TRANS_SCHACC_DESTORY;
		writelog(LOG_ERR,"card.cardattr=[%d]",card.cardno);
		goto L_RETU;
	}

	if(STATE_TRUE==card.cardattr[CARDSTAT_TYPE_LOST])
	{
		DB_t_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_LOSTING;
		writelog(LOG_ERR,"card_state=[%s]",card.cardattr);
		goto L_RETU;
	}

	if(STATE_TRUE==card.cardattr[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_FREEZE;
		writelog(LOG_ERR,"card_state=[%s]",card.cardattr);
		goto L_RETU;
	}
	if(STATE_TRUE==card.cardattr[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_card_free_lock_by_cur();
		*pRetCode=E_TRANS_SCHCARD_WFAIL;
		writelog(LOG_ERR,"card_state=[%s]",card.cardattr);
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

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &iSeqno);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}


	tradeserial.serial_no=iSeqno;
	//记录流水号，作为冲正使用
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=rPack->lvol0;	//上传端流水号
	tradeserial.serial_type=TXCODE_BANK_SCHOOL;	//交易代码
	tradeserial.serial_state=SERISTAT_NODEBT;	//流水状态
	tradeserial.cardno=atoi(rPack->sserial0);
	tradeserial.purseno=0;
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
	tradeserial.maindeviceid=GetTransferSystemId();		//子系统号码
	tradeserial.deviceid=atoi(rPack->sorder2);			//终端ID
	tradeserial.trade_fee=(rPack->lvol5)/100.0;	//转帐金额
	Strncpy_t(tradeserial.b_act_id,rPack->scust_auth,sizeof(tradeserial.b_act_id));
	tradeserial.sys_id=rPack->lvol2;						//表示银行
	tradeserial.condition_id=SELF_TRANS;						//自动/自助转帐标识
	tradeserial.custid=card.custid;
	Strncpy_t(tradeserial.opercode,OPER_SYSTEM_KEY,sizeof(tradeserial.opercode));	//操作员代码

	//判断转帐金额是否超出钱包最大限额
	ret=DB_t_account_read_by_cardno_and_purseno(card.cardno, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_cardno_and_purseno ret[%d]cardno[%d]",ret,card.cardno);
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

	if(amtcmp(tAccount.availbal+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		goto L_RETU;
	}
	//读取客户收费类别字段
	ret=DB_t_customer_read_lock_by_cur_and_custid(card.custid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"custid[%d]",card.custid);
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
				writelog(LOG_ERR,"DB_t_spefee_read_by_deptcode_and_custtype error,errcode=[%d]",ret);
				*pRetCode=E_TRANS_UNKNOW_ERROR;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.feetype=tSpeFee.feetype;
		}
	}
	DB_t_customer_free_lock_cur();
	//记录流水数据，用于提供正确的流水号，以及银行业务不成功供查询
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
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
	des2src(IA.sArrInActno[0],tAccount.accno);			//贷方帐户,持卡人账户
	des2src(IA.sArrInActno[2],rPack->sstation0);				//借方帐号，由前置机上传
	IA.iCardNo=card.cardno;
	IA.iFeeType=tCustomer.feetype;
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
				tradeserial.depositfee=IA.dArrOutAmt[i];
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
	writelog(LOG_DEBUG,sDebugMsg);

	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;
	out_pack->lvol2=D2I(tradeserial.out_balance*100);
	

	PutRow(handle,out_pack,pRetCode,szMsg);

	//业务结束后，回滚事务
	ret=db_rollback();
	if(ret)
	{
		*pRetCode=E_DB_ROLLBACK;
		writelog(LOG_ERR,"db_rollback error,error code=[%d]",ret);
		goto L_RETU;
	}
	
	return 0;
	
L_RETU:
	return -1;
}


