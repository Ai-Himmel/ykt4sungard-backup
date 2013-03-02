/* --------------------------------------------
 * 程序名称: F849009.cpp
 * 创建日期: 2008-03-31 
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 下发补助
 * --------------------------------------------
 * 修改日期: 
 * 修改人员: 
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"

int do_849008_query(ST_PACK *in_pack,int *cust_id,int *card_id);
/**
 * \brief 入账处理
 */
static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//工作站标识
	IA->iDevId=p->device_id;						//设备ID
	IA->iSerialNo=p->serial_no;						//流水号
	IA->iTradeNo=p->serial_type;					//交易码
	strcpy(IA->sTxDate,p->operate_date);			//交易日期
	strcpy(IA->sTxTime,p->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,p->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,p->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,p->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,p->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,p->oper_code);			    //操作员
	strcpy(IA->sChkOper,p->reserve_1);				//复核操作员

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//无卡交易
	//if(p->trade_fee<0)	p->trade_fee=0-p->trade_fee;
	ret = AccountProcess(IA);

	return ret;

}

/**
 * \brief 处理网银转账入账业务
 * \param in_pack 请求报文包
 * \param out_pack 输出报文包
 * \param online_tx 联机交易，当为1时，如果个人账户已注销，则不能交易，
 *					当为0时，如果个人账户已注销，则借记 现金，贷记 营业成本
 */
int do_849009(ST_PACK *in_pack,char *szMsg,ST_PACK *out_pack,int online_tx)
{
	int cust_id,card_id;
	int subsidy_no;
	int ret,count;
	char temp[64];
	double max_subsidy_money = 0.0;
	double total_money,dSerial;
	T_t_tif_subsidy subsidy;
	T_t_tif_tradeserial tSerial;
	T_t_pif_syskey syskey;
	T_t_aif_account account;
	T_t_tif_meslist tMesList;
	InAcc IA;
	if(amtcmp(in_pack->damt0,0.0) <= 0)
	{
		writelog(LOG_DEBUG,"input money error!");
		return E_INPUT_AMT;
	}

	memset(temp,0,sizeof temp);
	ret = GetParameter(GLOBAL_MAX_PER_SUBSIDY,temp);
	if(ret)
	{
		return ret;
	}
	max_subsidy_money = D4U5(atof(temp),2);
	
	// 流水号
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial);
	if(ret)
	{
		return ret;
	}
	// 查询卡信息
	ret = do_849008_query(in_pack,&cust_id,&card_id);
	if(ret)
	{
		writelog(LOG_DEBUG,"query customer information error!,ret[%d]",ret);
		return ret;
	}

	// 账户信息
	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,in_pack->lvol3,&account);
	if(ret)
	{
		// 账户表无信息
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;

	}
	
	// 生成流水记录
	memset(&tSerial,0,sizeof tSerial);
	memset(&IA,0,sizeof IA);

	tSerial.serial_no = D2I(dSerial);
	tSerial.serial_type = TXCODE_ONLINE_BANK; // 网银转账
	tSerial.serial_state = SERISTAT_DEBT;
	des2src(tSerial.oper_code,in_pack->scust_no2);
	des2src(tSerial.operate_date,in_pack->sdate0);
	des2src(tSerial.operate_time,in_pack->stime0);
	GetLogicDate(tSerial.enteract_date);
	getsystime(tSerial.enteract_time);
	getsysdate(tSerial.collect_date);
	des2src(tSerial.collect_time,tSerial.enteract_time);
	tSerial.customer_id = cust_id;
	tSerial.card_id = card_id;
	tSerial.in_balance = 0.0;
	tSerial.out_balance = 0.0;
	tSerial.trade_fee = in_pack->damt0;
	tSerial.other_seri_no = in_pack->lvol2; // 银行端流水号

	if(account.current_state >= ACCOUNTSTAT_LOGOUT)
	{
		// 个人账户已经注销
		if(online_tx)
			return E_ACTNO_LOGOUT;
		// 借记 银行存款 贷记 营业成本
		des2src(IA.sArrInActno[3],"1021");
		IA.dArrInAmt[1] = tSerial.trade_fee;
	}
	else
	{
		// 个人账户号
		des2src(IA.sArrInActno[0],account.account_id);
		IA.dArrInAmt[0] = tSerial.trade_fee;
	}
	IA.iFeeType=1;
	ret = process(&IA,&tSerial);
	if(ret)
	{
		writelog(LOG_ERR,"入账失败,cust_id[%d],card_id[%d],ret[%d]"
				 ,cust_id,card_id,ret);
		return ret;
	}

	ret = DB_t_tif_tradeserial_add(&tSerial);
	if(ret)
	{
		writelog(LOG_ERR,"记录流水失败");
		return E_DB_TRADESERIAL_I;
	}
	// 先入账 
	total_money = 0.0;
	count = 0;
	memset(&subsidy,0,sizeof subsidy);
	subsidy.cust_no = cust_id;
	getsysdatetime(subsidy.batch_no);
	des2src(subsidy.oper_code,tSerial.oper_code);
	strcpy(subsidy.summary,"网银转账");
	strcpy(subsidy.expire_date,"20500101");
	subsidy.bill_type = TYPE_CASH;
	subsidy.card_no = card_id;
	des2src(subsidy.tx_date,tSerial.operate_date);
	des2src(subsidy.tx_time,tSerial.operate_time);
	subsidy.status[0] = SUBSIDY_STAT_NORMAL;
	strcpy(subsidy.subsidytype,"1");

	// 锁表
	memset(&syskey,0,sizeof syskey);
	ret = DB_t_pif_syskey_read_lock_by_cur_and_key_code(KEYTYPE_TIF_SUBSIDY_NO,&syskey);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SYSKEY_N;
		else
			return E_DB_SYSKEY_U;
	}
	// 记录补助信息
	do
	{
		subsidy.amount = D4U5(in_pack->damt0 - total_money,2);
		if(amtcmp(subsidy.amount,0.0) <= 0)
		{
			// 剩余金额为 0, 不可能出现小于 0
			break;
		}
		else if(amtcmp(subsidy.amount,max_subsidy_money) > 0.0)
		{
			// 单笔金额不能大于最大值
			subsidy.amount = max_subsidy_money;
		}

		total_money = D4U5(total_money+subsidy.amount,2);

		ret = calc_card_max_subsidy_no(cust_id,card_id,&subsidy_no);
		if(ret)
		{
			writelog(LOG_DEBUG,"cannot calculate max subsidy NO,cust[%d],card[%d],ret[%d]",
					 cust_id,card_id,ret);
			DB_t_pif_syskey_free_lock_cur();
			return ret;
		}
		subsidy.subsidy_no = subsidy_no;
		ret = DB_t_tif_subsidy_add(&subsidy);
		if(ret)
		{
			DB_t_pif_syskey_free_lock_cur();
			// 记录信息失败
			if(DB_REPEAT == ret)
				return E_DB_SUBSIDY_E;
			else
				return E_DB_SUBSIDY_I;
		}
		count++;
		// 下发补助信息
	}while(1);

	if(count > 0)
	{
		// 广播消息队列
		memset(&tMesList,0,sizeof tMesList);
		tMesList.funid=930077;
		tMesList.level = MESLIST_PRIORITY_REALTIME;
		tMesList.msgtype = MESLIST_TYPE_NORMAL;
		tMesList.max_send_cnt = 5;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			DB_t_pif_syskey_free_lock_cur();
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			return E_DB_MESLIST_I;
		}
	}
	DB_t_pif_syskey_free_lock_cur();
	out_pack->lvol0 = card_id;
	out_pack->lvol1 = tSerial.serial_no;
	out_pack->lvol2 = tSerial.customer_id;
	out_pack->damt0 = tSerial.trade_fee;
	return 0;	
}

int F849009(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL2,F_DAMT0,0);
	ret = do_849009(in_pack,szMsg,out_pack,1);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

