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
#include "fdsqc.h"

static int do_check_card_state(int card_id,T_t_pif_card *card)
{
	int ret;
	ret = DB_t_pif_card_read_by_card_id(card_id,card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		if(DB_NOTFOUND == ret)
			return E_DB_CARD_N;
		else
			return E_DB_CARD_R;
	}
	if(strncmp(card->state_id,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"card->state_id=[%d]",card->card_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_LOST])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_FREEZE])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	else if(STATE_TRUE==card->state_id[CARDSTAT_TYPE_WFAIL])
	{
		writelog(LOG_ERR,"card_state=[%s]",card->state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}
	return 0;
}
static int do_check_elec_pwd(T_t_aif_account *account,const char *pwd)
{
	char temp[128] = "";
	char new_pwd[20] = "";
	int ret;
	ret = GetParameter(GLOBE_999_DEVAUTHKEY ,temp);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_PASSWORD_WRONG;
		return E_GLOBAL_PARAM_ERROR;
	}
	ret = decrypt_elec_card_pwd(0,temp,account->password,new_pwd);
	if(ret)
	{
		return E_GLOBAL_PARAM_ERROR;
	}
	if(strcmp(pwd,new_pwd) == 0)
	{
		return 0;
	}
	return E_PASSWORD_WRONG;
}
static int do_precheck(T_t_cif_customer *customer,ST_PACK *in_pack,char sAccount[][30],InAcc *IA)
{
	int ret;
	T_t_pif_card card;
	T_t_tradecode_shop tradecode_shop;
	T_t_cif_shop shop;
	char sMaxCardBalance[128] = "";
	double dMaxCardBalance = 0.0;
	double trade_fee;
	T_t_aif_account tAccount;
	memset(&card,0,sizeof card);
	card.card_id = atoi(in_pack->sserial0);
	memset(sAccount[0],0,sizeof sAccount[0]);
	des2src(sAccount[0],in_pack->sstation0); // 借方账号
	trade_fee = D4U5(in_pack->lvol5/100.0,2);
	switch(in_pack->lvol4)
	{
	case TXCODE_BANK_SCHOOL:
		IA->iUseCardFlag = IS_YES;
		ret = do_check_card_state(card.card_id,&card);
		if(ret)
			return ret;
		memset(&tAccount,0,sizeof tAccount);
		//判断转帐金额是否超出钱包最大限额
		ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
			if(DB_NOTFOUND==ret)
			{
				return E_TRANS_SCHACC_NOEXIT;
			}
			else
			{
				return E_TRANS_UNKNOW_ERROR;
			}
		}

		ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
		if(ret)
		{
			writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		dMaxCardBalance=atof(sMaxCardBalance);
		if(amtcmp(tAccount.cur_bala+trade_fee,dMaxCardBalance)>0)
		{
			return E_TRANS_TRANSMONEY_OUTRANGE;
		}
		ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id,customer);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				return E_DB_CUSTOMER_N;
			return E_DB_CUSTOMER_R;
		}
		// 贷方账号
		des2src(sAccount[1],tAccount.account_id);
		break;
	case TXCODE_BANK_ELEC:
		IA->iUseCardFlag = IS_NO;
		// 电子钱包账号
		ret = find_cutid_by_outsideno(&card.cosumer_id,in_pack->scust_auth,1);
		if(ret)
		{
			writelog(LOG_ERR,"find outside_no error,outside_no[%s]",in_pack->scust_auth);
			return ret;
		}
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(card.cosumer_id,ACCTYPE_PEREACC,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account error,cut_id[%d]type[%d]",card.cosumer_id,ACCTYPE_PEREACC);
			if(DB_NOTFOUND == ret)
				return E_NOTEXIST_EACCNO;
			return E_DB_ACCOUNT_R;
		}
		if(tAccount.current_state == ACCOUNTSTAT_LOGOUT)
			return E_ACTNO_LOGOUT;
		ret = do_check_elec_pwd(&tAccount,in_pack->semp_pwd);
		if(ret)
			return ret;
		ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id,customer);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				return E_CUSTOMER_NOT_EXIST;
			return E_DB_CUSTOMER_R;
		}
		des2src(sAccount[1],tAccount.account_id);
		break;
	case TXCODE_BANK_YCT:
		IA->iUseCardFlag = IS_NO;
		ret = do_check_card_state(card.card_id,&card);
		if(ret)
			return ret;
		memset(&tradecode_shop,0,sizeof tradecode_shop);
		ret = DB_t_tradecode_shop_read_by_trade_code(in_pack->lvol4,&tradecode_shop);
		if(ret)
		{
			writelog(LOG_ERR,"query tradecode shop error,tradecode[%d]",in_pack->lvol4);
			if(DB_NOTFOUND == ret)
				return E_DB_TRADECODE_SHOP_N;
			return E_DB_TRADECODE_SHOP_R;
		}	
		memset(&shop,0,sizeof shop);
		ret = DB_t_cif_shop_read_by_shop_id(tradecode_shop.shop_id,&shop);
		if(ret)
		{
			writelog(LOG_ERR,"query shop error,shopid[%d]",tradecode_shop.shop_id);
			if(DB_NOTFOUND == ret)
				return E_DB_SHOP_N;
			return E_DB_SHOP_R;
		}
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(shop.cut_id,ACCTYPE_SHOPMAIN,&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"query account error,cut_id[%d]",shop.cut_id);
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			return E_DB_ACCOUNT_R;
		}
		if(tAccount.current_state == ACCOUNTSTAT_LOGOUT)
			return E_ACTNO_LOGOUT;
		// 贷方账号
		writelog(LOG_ERR,"query tradecode[%d],shopid[%d]",in_pack->lvol4,shop.cut_id);
		memset(sAccount[1],0,sizeof sAccount[1]);
		des2src(sAccount[1],tAccount.account_id);
		customer->fee_type = 0;
		customer->cut_id = shop.cut_id;
		break;
	default:
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_ERR,"cractno[%s]dbactno[%s][%s]",sAccount[0],sAccount[1],tAccount.account_id);
	return ret;
}
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

	// IA->iUseCardFlag=IS_YES;						//卡交易
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
	if(IA->iUseCardFlag == IS_YES)
		p->out_balance=IA->dOutCardBala;			//出卡值
	else
	{
		// 读取贷方账户余额
		memset(&tAccount,0,sizeof tAccount);
		ret = DB_t_aif_account_read_by_account_id(IA->sArrInActno[1],&tAccount);
		if(ret)
		{
			writelog(LOG_ERR,"read account error!,actno[%s]",IA->sArrInActno[1]);
			return E_DB_ACCOUNT_R;
		}
		p->out_balance = tAccount.cur_freebala;
	}
	return 0;
}

// modify by 汤成 2008-08-30 
// 重新设计 转账模块, 校园卡密码检验由圈存前置机完成 , 转账可分为两种交易:
// 1 : 有卡转账交易 , 这种交易需要检查校园卡状态
// 2 : 无卡转账交易 , 根据指定账户号来检查账户当前状态
int F240002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
	char sAccount[2][30];

	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account tAccount;
	InAcc	IA;

	memset(&tCustomer,0,sizeof tCustomer);
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&IA,0,sizeof(IA));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(sAccount,0,sizeof sAccount);
	//填写入账结构,问问闻剑
	memset(&IA,0,sizeof(IA));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_SDATE0,0);


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

	//转账不允许转小数金额
	if((rPack->lvol5)%100>0)
	{
		*pRetCode=E_TRANS_TRANSMONEY_OUTRANGE;
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",rPack->lvol5/100.0);
		goto L_RETU;
	}
	if(rPack->lvol4 == 0)
	{
		// 兼容以前版本, 默认交易转 圈存转账
		rPack->lvol4 = TXCODE_BANK_SCHOOL;
	}

	//开始填充流水数据
	ret = do_precheck(&tCustomer,rPack,sAccount,&IA);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//流水号

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		*pRetCode=E_TRANS_UNKNOW_ERROR;
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		goto L_RETU;
	}


	tradeserial.serial_no=D2I(unique);
	//记录流水号，作为冲正使用
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=rPack->lvol0;	//上传端流水号
	tradeserial.serial_type=rPack->lvol4;	//交易代码
	tradeserial.serial_state=SERISTAT_NODEBT;	//流水状态
	tradeserial.card_id=atoi(rPack->sserial0);
	tradeserial.purse_id=0;
	tradeserial.in_balance=D4U5(rPack->lvol6/100.00,2);	//入卡金额
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
	tradeserial.trade_fee=D4U5(rPack->lvol5/100.0,2);	//转帐金额
	Strncpy_t(tradeserial.b_act_id,rPack->scust_auth,sizeof(tradeserial.b_act_id));
	tradeserial.sys_id=rPack->lvol2;						//表示银行
	tradeserial.condition_id=SELF_TRANS;						//自动/自助转帐标识
	tradeserial.customer_id=tCustomer.cut_id;
	Strncpy_t(tradeserial.oper_code,OPER_SYSTEM_KEY,sizeof(tradeserial.oper_code));	//操作员代码
	tradeserial.comu_ver=tCustomer.fee_type;
	des2src(tradeserial.in_account_id,sAccount[1]);
	des2src(tradeserial.out_account_id,sAccount[0]);

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
	// 这一行保留, 保证与现在已上线的系统兼容
	//des2src(IA.sArrInActno[0],sAccount[1]);			//贷方帐户,持卡人账户
	// 修改入账参数,这样可以统一所以银行转账交易
	des2src(IA.sArrInActno[1],sAccount[1]);			//贷方帐户,持卡人账户
	des2src(IA.sArrInActno[0],sAccount[0]);			//借方帐号，由前置机上传 , 银行账号
	
	IA.iCardNo=tradeserial.card_id;
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


	sprintf(sMsg,"充值前卡余额:%.2lf 转帐后卡余额:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);

	out_pack->damt0=tradeserial.out_balance;
	out_pack->damt1=tradeserial.trade_fee;
	out_pack->damt2=tradeserial.boardfee;
	out_pack->lvol1=tradeserial.serial_no;
	des2src(out_pack->sdate0,logicdate);

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


