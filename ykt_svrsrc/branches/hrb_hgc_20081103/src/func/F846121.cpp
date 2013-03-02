/* --------------------------------------------
 * 创建日期: 200-5-18
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 写卡失败修卡
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "fdsqc.h"

int F846121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int card_no = rPack->lvol0;
	int serial_type = rPack->lvol4;				//写卡失败交易类型
	int trade_cnt = rPack->lvol1;				//写卡失败交易次数
	double trade_amt = rPack->damt2;			//写卡失败交易金额
	double boardfee = rPack->damt3;			//写卡失败大伙费
	double curr_amt = rPack->lvol3/100.0;			//卡片当前金额
	char phy_cardno[9] = "";
	char op_date[9] = "";
	char oper_code[11] = "";					//修卡操作员
	char sysdate[9] = "";
	char systime[7] = "";

	writelog(LOG_INFO,"curr_amt[%d][%f]",rPack->lvol3,curr_amt);
	if(card_no <=0)
		return E_CARDNO_INVALID;

	if(trade_cnt < 1)
		return E_INPUT_CARD_TXCNT;
	
	if(amtcmp(curr_amt, 0)<0)
		return E_INPUT_CARD_BALA;

	if(amtcmp(trade_amt, 0)<0 )
	{	
		if(serial_type != TXCODE_TX_REVEAL)
			return E_INPUT_AMT;
		trade_amt = -trade_amt;
		boardfee = 0;
	}
	if(strlen(rPack->sstock_code) != 8)			//物理卡号
		return E_INPUT_CARDPHYID;
	des2src(phy_cardno,rPack->sstock_code);
	
	if(strlen(rPack->sdate1) != 8)				// 写卡失败的交易日期
		return E_INPUT_DATE;
	des2src(op_date,rPack->sdate1);
	des2src(oper_code,rPack->scust_no);		//操作员
	
	T_t_pif_card tCard;
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_pif_card_read_by_card_id(card_no, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_no);
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARD_CHANGE;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_LOST])
			return E_CARDNO_LOST;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
			return E_CARDNO_FREEZE;
		else if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_WFAIL])
			return E_CARDNO_WFAIL;
	}
	
	trim(tCard.physical_no);
	if(strcmp(tCard.physical_no,phy_cardno)!=0)
	{
		writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,phy_cardno);
		return E_CARD_PHYNO_DIFFER;
	}	

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,F_VSMESS,F_LVOL0,F_LVOL2,0);	

	getsysdate(sysdate);
	getsystime(systime);

	T_t_pif_fixcard tFixcard;
	memset(&tFixcard,0,sizeof tFixcard);
	ret = DB_t_pif_fixcard_read_by_cardno_and_tradecnt_and_operate_date(card_no, trade_cnt, op_date, &tFixcard);
	if(ret ==0)			
		return E_FIXCARD_ALREADY;			// 查询到记录，证明这条写卡失败的记录已经被修复过
	else
	{
		if(DB_NOTFOUND != ret)
			return E_FIXCARDLOG_R;
		tFixcard.cardno = card_no;
		tFixcard.tradecnt = trade_cnt;
		des2src(tFixcard.operate_date,op_date);
		des2src(tFixcard.physicalno,phy_cardno);
		des2src(tFixcard.fix_date,sysdate);
		tFixcard.fix_amt = trade_amt - boardfee;
		des2src(tFixcard.oper_code,oper_code);
		ret = DB_t_pif_fixcard_add(&tFixcard);
		if(ret)
			return E_FIXCARDLOG_I;
	}

	double dUniqno = 0;
	T_t_tif_tradeserial tTradeserial;
	memset(&tTradeserial,0,sizeof tTradeserial);

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if (ret)
		return ret;

	tTradeserial.serial_no = D2I(dUniqno);
	tTradeserial.serial_type= 846121;
	tTradeserial.serial_state= SERISTAT_NONEEDDEBT;
	
	des2src(tTradeserial.operate_date, sysdate);
	des2src(tTradeserial.operate_time, systime);
	des2src(tTradeserial.collect_date, sysdate);
	des2src(tTradeserial.collect_time, systime);
	des2src(tTradeserial.enteract_date, sysdate);						//业务日期
	des2src(tTradeserial.enteract_time, systime);

	tTradeserial.card_id= card_no;
	tTradeserial.trade_count= rPack->lvol2+1;						//卡片当前交易次数
	tTradeserial.trade_fee= trade_amt;								//写卡失败的交易金额
	tTradeserial.boardfee = boardfee;
	tTradeserial.in_balance= curr_amt;								//卡片当前金额
	tTradeserial.out_balance= curr_amt + trade_amt - boardfee;			//卡片当前出卡值
	tTradeserial.customer_id= tCard.cosumer_id;
	des2src(tTradeserial.oper_code,oper_code);

	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if(ret)
		return E_DB_TRADESERIAL_I;

	T_t_aif_account tAccount;
	memset(&tAccount,0,sizeof tAccount);
	ret = DB_t_aif_account_read_lock_by_c0_and_card_id_and_purse_id(card_no, 0, &tAccount);
	if(ret)
		return E_DB_ACCOUNT_R;
	tAccount.card_balance = tTradeserial.out_balance;
	tAccount.consume_count = tTradeserial.trade_count;
	des2src(tAccount.reserve_1,sysdate);
	ret = DB_t_aif_account_update_lock_by_c0(&tAccount);
	if(ret)
	{
		DB_t_aif_account_free_lock_c0();
		return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_c0();
	
	outPack->lvol0 = card_no;
	outPack->lvol2= D2I(tTradeserial.out_balance*100);				//出卡值，写卡
	des2src(outPack->vsmess,"修卡成功");
	PutRow(handle,outPack,pRetCode,szMsg);
	
	return 0;
}
