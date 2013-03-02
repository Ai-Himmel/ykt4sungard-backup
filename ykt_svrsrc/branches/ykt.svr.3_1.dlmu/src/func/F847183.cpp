/* --------------------------------------------
 * 程序名称: F847183.sqc
 * 创建日期: 2005-04-11
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  交易冲正
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

static int process_847106(InAcc *IA,T_t_tif_tradeserial *p)
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

static int do_flush_847106(T_t_tif_tradeserial *tTradeserial,T_t_card *tCard)
{
	InAcc	IA;
	T_t_aif_account	tAccount;		//帐户表
	T_t_tif_savdtl		tSavdtl;
	T_t_customer tCustomer;
	int ret;

	memset(&IA,0,sizeof IA);
	memset(&tAccount,0,sizeof tAccount);
	memset(&tSavdtl,0,sizeof tSavdtl);
	memset(&tCustomer,0,sizeof tCustomer);

	// 读取账户信息
	ret=DB_t_aif_account_read_by_cardno_and_purseno(
			tTradeserial->cardno,tTradeserial->purseno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_cardno_and_purseno ret[%d]cardno[%d]"
			,ret,tTradeserial->cardno);
		if(DB_NOTFOUND==ret)
			return E_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}

	ret = DB_t_tif_savdtl_read_lock_by_cur_and_tx_date_and_seqno(
		tTradeserial->operate_date,tTradeserial->reviseserial_no,&tSavdtl);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_SAVDTL_R;
	}
	else
	{
		//不是现金充值流水不能冲正
		DB_t_tif_savdtl_free_lock_cur();
		return E_NOT_CASH_TRANSACTION;
	}

	ret = DB_t_customer_read_by_custid(tCard->custid,&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_CUSTOMER_N;
		return E_DB_CUSTOMER_R;
	}

	des2src(IA.sArrInActno[0],tAccount.account_id);						//帐户
	//strcpy(IA.sArrInActno[1],INNER_ACCOUNT_CASH);	// 现金科目帐号
	IA.iCardNo=tTradeserial->cardno; // 交易卡号
	IA.iFeeType=tCustomer.feetype; // 卡权限类型
	IA.iArrInFeeSwitch[1]=1;
	IA.dArrInAmt[0]=tTradeserial->trade_fee;
	// 冲正交易
	IA.iTxFlag=ACC_TYPE_RUSH;

	ret = process_847106(&IA,tTradeserial);
	return ret;
}

int F847183(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg)
{

	int ret = 0;
	char    	tx_date[8+1] = "";              	//发生日期
//		char    	tx_time[6+1]="";      		//发生时间
	int		cardno = 0;                    	//卡号
	char    	deviceid[8+1] = "";            	//终端机ID
	int		serial_no = 0;                  	//终端机流水号
	int 		flag = 0;
	double 	iSeqNo = 0;
	T_t_tif_tradeserial		tOldTradeserial;	//当日流水表
	T_t_tif_tradeserial		tTradeserial;	//当日流水表
	T_t_tif_tradeserial_his	tTradeserialhis;	//历史流水表
	T_t_tradecode tTradeCode;
	T_t_card tCard;
	char sysdate[11] = "";
	char systime[9] = "";
	char sYear[5] = "";
	char sMonDay[5] = "";
	char logic_date[9] = "";
	int days = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ST_PACK next_pack;

	ResetNormalCPack(&aPack, 0, 1);
	memset(&tTradeserial, 0, sizeof(tTradeserial));
	memset(&tOldTradeserial, 0, sizeof(tOldTradeserial));
	memset(&tTradeserialhis, 0, sizeof(tTradeserialhis));
	memset(&tTradeCode, 0, sizeof tTradeCode);
	memset(&tCard, 0, sizeof tCard);
	getsysdate(sysdate);
	getsystime(systime);
	des2src(tTradeserial.enteract_time, systime);

	des2src(tx_date, rPack->sbank_pwd);
//		des2src(tx_time,rPack->sbank_code);
	cardno = rPack->lvol0;
	des2src(deviceid, rPack->sbank_pwd2);
	serial_no = rPack->lvol1;
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	des2src(sYear, tx_date);
	des2src(sMonDay, tx_date + 4);

	if (strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if (strlen(rPack->scust_limit2) == 0)
	{
		*pRetCode = E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if (strcmp(rPack->scust_limit, rPack->scust_limit2) == 0)
	{
		writelog(LOG_ERR, "oper[%s]auth_oper[%s]", rPack->scust_limit, rPack->scust_limit2);
		*pRetCode = E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret = chk_oper_pwd(rPack->scust_limit2, rPack->semp_pwd);
	if (ret)
	{
		if (E_OPER_NOT_EXIST == ret)
			*pRetCode = E_AUTH_OPER_NOT_EXIST;
		else if (E_PASSWORD_WRONG == ret)
			*pRetCode = E_AUTH_OPER_PWD;
		else
			*pRetCode = ret;
		goto L_RETU;
	}
	ret = DB_t_card_read_by_cardno(cardno, &tCard);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			*pRetCode = E_CARDNO_NOT_EXIST;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}
	if (tCard.cardattr[CARDSTAT_TYPE_REG] == '2')
	{
		writelog(LOG_ERR, "冲正交易卡号已注销cardid[%d]", tCard.cardno);
		*pRetCode = E_ACTNO_LOGOUT;
		goto L_RETU;
	}
	//查询当前流水表
	ret = DB_t_tif_tradeserial_read_lock_by_c4_and_operate_date_and_serial_no_and_cardno(tx_date, serial_no, cardno, &tOldTradeserial);
	if (ret)
	{
		writelog(LOG_ERR, "tx_date[%s]serial_no[%d]ret[%d]", tx_date, serial_no, ret);
		if (DB_NOTFOUND != ret)
		{
			*pRetCode = E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
	}
	else
	{
		flag = 1;
		memcpy(&tTradeserial, &tOldTradeserial, sizeof(tTradeserial));
		tTradeserial.other_seri_no = tOldTradeserial.serial_no;					//上传端流水号
		tOldTradeserial.serial_state = SERISTAT_RUSH;				//冲正
		ret = DB_t_tif_tradeserial_update_lock_by_c4(&tOldTradeserial);
		if (ret)
		{
			*pRetCode = E_DB_TRADESERIAL_U;
			writelog(LOG_ERR, "DB_t_tif_tradeserial_update_lock_by_c4[%d]", ret);
			goto L_RETU;
		}
		DB_t_tif_tradeserial_free_lock_c4();
	}
	if (!flag)
	{
		//查询历史流水表
		ret = DB_t_tif_tradeserial_his_read_lock_by_c0_and_trans_year_and_trans_mon_day_and_serial_no_and_cardno(sYear, sMonDay, serial_no, cardno, &tTradeserialhis);
		if (ret)
		{
			writelog(LOG_ERR, "year[%s]date[%d]serialno[%d]ret[%d]", sYear, sMonDay, serial_no, ret);
			if (DB_NOTFOUND == ret)
			{
				*pRetCode = E_SERIALNO_NOT_EXIST;
				goto L_RETU;
			}
			else
			{
				*pRetCode = E_DB_TRADESERIAL_R;
				goto L_RETU;
			}
		}
		tTradeserial.other_seri_no = tTradeserialhis.serial_no;						//上传端流水号
		tTradeserial.serial_state = tTradeserialhis.serial_state;						//流水状态
		tTradeserial.tmark = tTradeserialhis.tmark;								//999交易标记
		tTradeserial.maindeviceid = tTradeserialhis.maindeviceid;							//上传工作站标识(前置机注册号)
		tTradeserial.sys_id = tTradeserialhis.sys_id;
		tTradeserial.comu_ver = tTradeserialhis.comu_ver;							//通信版本号
		// add by 汤成 2007-10-31
		tTradeserial.deviceid = tTradeserialhis.deviceid;
		des2src(tTradeserial.devphyid, tTradeserialhis.devphyid);				//物理设备ID
		des2src(tTradeserial.dev_auth, tTradeserialhis.dev_auth);					//终端设备授权号
		des2src(tTradeserial.crc, tTradeserialhis.crc);								//CRC校验
		tTradeserial.cardno = tTradeserialhis.cardno;								//交易卡号
		tTradeserial.purseno = tTradeserialhis.purseno;							//消费钱包号
		tTradeserial.in_balance = tTradeserialhis.in_balance;						//入卡金额
		tTradeserial.out_balance = tTradeserialhis.out_balance;					//出卡金额
		tTradeserial.trade_fee = tTradeserialhis.trade_fee;						//本次消费金额
		tTradeserial.trade_count = tTradeserialhis.trade_count;							//当前卡中帐户消费次数(累计使用次数)
		tTradeserial.serial_type = tTradeserialhis.serial_type;							//交易代码
		tTradeserial.managefee = tTradeserialhis.managefee	;						//搭伙费
		des2src(tTradeserial.operate_date, tTradeserialhis.operate_date);					//发生日期(格式化输入的日期)
		des2src(tTradeserial.operate_time, tTradeserialhis.operate_time);					//发生时间(格式化输入的时间)
		tTradeserial.condition_id = tTradeserialhis.condition_id;							// 收费科目
		tTradeserialhis.serial_state = SERISTAT_RUSH;				//冲正
		// 保存被冲正交易的操作员号
		des2src(tTradeserialhis.opercode, tTradeserialhis.opercode);
		ret = DB_t_tif_tradeserial_his_update_lock_by_c0(&tTradeserialhis);
		if (ret)
		{
			*pRetCode = E_DB_TRADESERIAL_U;
			writelog(LOG_ERR, "DB_t_tif_tradeserial_update_lock_by_c4[%d]", ret);
			goto L_RETU;
		}
		DB_t_tif_tradeserial_his_free_lock_by_c0();
	}
	if (tTradeserial.cardno != cardno)
	{
		writelog(LOG_ERR, "流水中卡号不符cardid[%d]serial[%d]", cardno, tTradeserial.cardno);
		*pRetCode = E_SERIALNO_NOT_EXIST;
		goto L_RETU;
	}
	if (tTradeserial.serial_state == SERISTAT_RUSH)
	{
		*pRetCode = E_TX_SERIAL_CZ;
		goto L_RETU;
	}
	if (tTradeserial.serial_state != SERISTAT_DEBT)
	{
		*pRetCode = E_TX_SERIAL_CANNOT_CZ;
		goto L_RETU;
	}
	if (amtcmp(tTradeserial.trade_fee, 0) == 0)
	{
		*pRetCode = E_TX_SERIAL_CANNOT_CZ;
		strcpy(szMsg,"交易金额有误!");
		goto L_RETU;
	}

	ret = DB_t_tradecode_read_by_tradecode(tTradeserial.serial_type, &tTradeCode);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			*pRetCode = E_DB_TRADECODE_N;
		else
			*pRetCode = E_DB_TRADECODE_R;
		goto L_RETU;
	}

	if (tTradeCode.rush_flag != IS_YES)
	{
		*pRetCode = E_TX_SERIAL_CANNOT_CZ;
		strcpy(szMsg,"该交易不能被冲正");
		goto L_RETU;
	}

	ret = GetLogicDate(logic_date);						//业务日期
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR, "GetLogicDate  err ret[%d]", ret);
		goto L_RETU;
	}
	// 小于 0 , 则不判断
	if (tTradeCode.rush_max_day >= 0)
	{
		ret = DiffDay(logic_date, tTradeserial.enteract_date, &days);
		if (ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		if (days > tTradeCode.rush_max_day)
		{
			writelog(LOG_ERR, "流水入账日期[%s],已超过期限[%d]天",
					 tTradeserial.enteract_date, days);
			*pRetCode = E_TX_SERIAL_CANNOT_CZ;
			strcpy(szMsg, "流水日期已超过可冲正期限!");
			goto L_RETU;
		}
	}

	if (tTradeCode.restrict_oper == IS_YES)
	{
		if (strcmp(rPack->scust_limit, tTradeserial.opercode) != 0)
		{
			strcpy(szMsg, "必须由作此次交易的操作员来冲正");
			*pRetCode = E_TX_SERIAL_CANNOT_CZ;
			goto L_RETU;
		}
	}

	// 保存上传的操作员号
	des2src(tTradeserial.operate_date, sysdate);
	des2src(tTradeserial.operate_time, systime);
	des2src(tTradeserial.collect_date, sysdate);
	des2src(tTradeserial.collect_time, systime);

	des2src(tTradeserial.enteract_date, logic_date);						//业务日期
	des2src(tTradeserial.enteract_time, systime);
	tTradeserial.in_balance = rPack->damt1;
	tTradeserial.trade_fee = -1 * tTradeserial.trade_fee;					//本次消费金额
	tTradeserial.managefee = -1 * tTradeserial.managefee;					//本次消费管理费
	tTradeserial.out_balance = tTradeserial.in_balance - tTradeserial.trade_fee;
	if (rPack->lvol10 > 0)
		tTradeserial.trade_count = rPack->lvol10 + 1;
	tTradeserial.maindeviceid = rPack->lvol6;
	// 上传的操作员号
	des2src(tTradeserial.opercode, rPack->scust_limit);
	tTradeserial.reviseserial_no = tTradeserial.other_seri_no;

	//取流水号,从帐处理
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL, &iSeqNo);
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR, "getNewUniqNo err[%d]", ret);
		goto L_RETU;
	}
	tTradeserial.serial_no = iSeqNo;
	//######################################################
	//入账处理
	switch (tTradeserial.serial_type)
	{
	case 930031:
		// 交易冲正
		if (amtcmp(tTradeserial.trade_fee, 0) == 0)
			break;
		tTradeserial.serial_type = TXCODE_TX_REVEAL;
		ret = process930031(&tTradeserial);
		if (ret)
		{
			//业务处理失败处理
			*pRetCode = ret;
			goto L_RETU;
		}
		break;
	case 930034:
		// 充值冲正
		if (amtcmp(tTradeserial.trade_fee, 0) == 0)
			break;
		tTradeserial.serial_type = TXCODE_TX_REVEAL;
		ret = process930034(&tTradeserial);
		if (ret)
		{
			//业务处理失败处理
			*pRetCode = ret;
			goto L_RETU;
		}
		break;
	case 930036:
		// 搭伙费冲正
		if (amtcmp(tTradeserial.trade_fee, 0) == 0)
			break;
		tTradeserial.serial_type = TXCODE_TX_REVEAL;
		ret = process930036(&tTradeserial);
		if (ret)
		{
			//业务处理失败处理
			*pRetCode = ret;
			goto L_RETU;
		}
		break;
	case 847106: // 现金充值冲正
		memset(&next_pack,0,sizeof next_pack);
		tTradeserial.serial_type = TXCODE_SAVING_CASH;
		ret = do_flush_847106(&tTradeserial,&tCard);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		break;
	default:
		*pRetCode = E_TXCODE_NOT_EXIST;	//交易码错误
		goto L_RETU;
	}
	//######################################################
	//添加交易流水
	tTradeserial.serial_state = SERISTAT_DEBT;
	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if (ret)
	{
		writelog(LOG_ERR, "DB_t_tif_tradeserial_add ret[%d]", ret);
		if (DB_REPEAT == ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	if (amtcmp(tTradeserial.out_balance, 0) < 0)
	{
		*pRetCode = E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	SetCol(handle, 0);
	SetCol(handle, F_LSERIAL1, F_DAMT2, F_DAMT3, F_VSMESS, 0);
	out_pack->lserial1 = tTradeserial.serial_no;
	out_pack->damt2 = tTradeserial.out_balance;
	out_pack->damt3 = -tTradeserial.trade_fee;
	sprintf(out_pack->vsmess, "流水号:%d 冲正金额:%.2lf元 冲正前卡余额:%.2lf元 卡当前余额:%.2lf元", tTradeserial.serial_no, -tTradeserial.trade_fee, tTradeserial.in_balance, tTradeserial.out_balance);
	writelog(LOG_DEBUG, out_pack->vsmess);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
L_RETU:
	return -1;
}
