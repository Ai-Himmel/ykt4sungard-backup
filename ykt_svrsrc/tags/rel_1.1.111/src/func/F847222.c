/* --------------------------------------------
 * 程序名称: F847222.sqc
 * 创建日期: 2006-9-26
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  上大账务商户消费结算
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
#include "dbfunc_foo.h"

typedef struct  _t_Trade_Param
{
	InAcc* pIA;			//入账模块
	int shop_id;					//输入商户号	
	double trade_fee;				//交易金额
	int serial_no;				//流水号
	double free_balance;			//商户余额
	double remain_balance;		//交易剩余金额
	int out_shop_id;				//交易叶子结点商户号
	int index;					//交易子流水号
	char tx_date[9];
	char tx_time[7];
	char oper_code[11];
} trade_param_t;

static int process(InAcc *IA,trade_param_t *p)
{
	int ret=0;

	IA->iSerialNo = p->serial_no;				//流水号
	IA->iSubIndex = p->index;
	IA->iTradeNo = TXCODE_FAN_BALANCE;		//交易码
	IA->dArrInAmt[0] = p->trade_fee;
	IA->iFeeType = 1;
	IA->iUseCardFlag = 0;				
	
	des2src(IA->sTxDate,p->tx_date);			//交易日期
	des2src(IA->sTxTime,p->tx_time);			//交易时间
	des2src(IA->sTxCollectDate,p->tx_date);		//采集日期
	des2src(IA->sTxCollectTime,p->tx_time);		//采集时间
	des2src(IA->sTxAccDate,p->tx_date);		//记账日期
	des2src(IA->sTxAccTime,p->tx_time);		//记账时间
	des2src(IA->sMdeOper,p->oper_code);			//操作员(发生错帐的操作员)

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//无卡交易
	IA->iTxCnt=0;								//交易次数
	IA->dInCardBala=0;							//入卡值
	IA->dOutCardBala=0;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	//p->remain_balance -= IA->dOutCardBala;			//出卡值
	if(amtcmp(IA->dOutCardBala,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	p->index = IA->iSubIndex;
	p->remain_balance -= p->trade_fee;
	return 0;
}

static int do_process_trade(trade_param_t * param)
{
	int ret;
	T_t_cif_shop shop;
	T_t_aif_account account;
	void * pTmp;
	InAcc * IA; 
	
	memset(&shop,0,sizeof shop);
	ret = DB_t_cif_shop_read_by_shop_id(param->out_shop_id,&shop);
	//writelog(LOG_DEBUG,"trade shop id[%d]",param->out_shop_id);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SHOP_N;
		else
			return E_DB_SHOP_R;
	}

	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		writelog(LOG_ERR,"shop id[%d] custid[%d]",shop.shop_id,shop.cut_id);
		if(DB_NOTFOUND == ret)
			return E_FAN_ACC_NOT_EXISTS;
		return E_DB_ACCOUNT_R;
	}
	//writelog(LOG_DEBUG,"对叶子商户[%d]进行解款[%.2lf]金额[%.2lf]",
	//	param->out_shop_id,account.last_bala,param->remain_balance);
	if(amtcmp(account.last_bala,0) <= 0)
	{
		// 商户无余额不处理
		return 0;
	}
	// 检查是否已经解款完成
	if(amtcmp(param->remain_balance,0) == 0)
	{
		//只计算商户余额
		param->free_balance += account.last_bala;
		return 0;
	}
	// 计算交易金额
	if(amtcmp(param->remain_balance,account.last_bala) >= 0)
	{
		param->trade_fee = account.last_bala;
	}
	else
	{
		param->trade_fee = param->remain_balance;
	}
	// 入账
	IA = param->pIA;
	//pTmp =  IA->pVoidPointer;
	memset(IA,0,sizeof(InAcc));
	des2src(IA->sArrInActno[1],account.account_id);
	IA->pVoidPointer = pTmp;
	ret = process(IA,param);
	if(ret)
	{
		writelog(LOG_ERR,"process account failed,ret [%d]shopid[%d]subindex[%d]",
			ret,param->out_shop_id,param->index);
		return ret;
	}
	// 更新账户余额
	// 入账之后账户余额已经被更新,需要重新读取
	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_FAN_ACC_NOT_EXISTS;
		return E_DB_ACCOUNT_R;
	}
	account.last_bala -= param->trade_fee;
	account.last_freebala -= param->trade_fee;
	if(amtcmp(account.last_bala,0)< 0)
	{
		account.last_bala = 0.0;
		account.last_freebala = 0.0;
	}
	else
	{
		param->free_balance += account.last_bala;
	}
	ret = DB_t_aif_account_update_by_account_id(account.account_id,&account);
	if(ret)
	{
		writelog(LOG_ERR,"更新商户账户余额失败ret[%d]",ret);
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	writelog(LOG_DEBUG,"商户[%d]解款金额[%.2lf]余额[%.2lf]"
		,shop.shop_id,param->trade_fee,account.last_bala);
	return ret;
}

static int do_parse_shop(trade_param_t * param)
{
	int ret;
	int rows;
	T_v_cif_shop_tree shop_node;
	//writelog(LOG_DEBUG,"对商户[%d]进行消费解款[%.2lf元]"
	//	,param->shop_id,param->remain_balance);
	ret = DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(param->shop_id);
	if(ret)
	{
		writelog(LOG_ERR,"查询商户信息失败[%d]",ret);
		if(DB_NOTFOUND == 0)
			return E_SHOP_HAVE_SUB_NODE;
		else
			return E_DB_SHOP_R;
	}
	rows = 0;
	while(1)
	{
		memset(&shop_node,0,sizeof shop_node);
		ret = DB_v_cif_shop_tree_fetch_select_by_c1(&shop_node);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				else
					return E_FAN_SHOP_HAS_NO_LEAF;
			}
			return E_DB_SHOP_R;
		}
		rows++;
		param->out_shop_id = shop_node.leaf_id;
		ret = do_process_trade(param);
		if(ret)
		{
			writelog(LOG_ERR,"叶子商户解款失败shop[%s],ret[%d]"
				,shop_node.shop_name,ret);
			DB_v_cif_shop_tree_close_select_by_c1();
			return ret;
		}
		
	}
	// 如果还有金额,则认为余额不足
	if(amtcmp(param->remain_balance,0) > 0)
	{
		writelog(LOG_ERR,"解款商户余额不足");
		return E_FAN_ACC_INSUFFICIENT;
	}
	return 0;
}

int F847222(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char  ia_buf[1024]="";
	char sMsg[256]="";
	double dUniNo;
	InAcc IA;
	T_t_tif_tradeserial serial;
	T_t_aif_account account;
	T_t_cif_shop shop;
	trade_param_t param;
	int shop_id;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int i;

	ResetNormalCPack(&aPack,0,1);

	shop_id = atoi(rPack->sbank_acc);
	if(shop_id <= 0)
	{
		*pRetCode = E_SHOP_ACTNO_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(amtcmp(rPack->damt1,0)<=0)
	{
		*pRetCode = E_INPUT_AMT;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	memset(&account,0,sizeof account);
	memset(&shop,0,sizeof shop);
	
	ret = DB_t_cif_shop_read_by_shop_id(shop_id,&shop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode  = E_SHOP_ACTNO_NOT_EXIST;
		else
			*pRetCode = E_DB_SHOP_R;
		goto L_RETU;
	}
	if(strcmp(shop.is_indep, TYPE_YES))
	{
		*pRetCode = E_FAN_SHOP_NOT_INDEP;
		goto L_RETU;
	}
	memset(&IA,0,sizeof IA);
	memset(&param,0,sizeof param);
	param.pIA = &IA;
	IA.pVoidPointer = ia_buf;
	param.shop_id = shop.shop_id;
	param.remain_balance = rPack->damt1;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniNo);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	param.serial_no = D2I(dUniNo);

	//初始化流水记录
	memset(&serial,0,sizeof serial);
	serial.serial_no = param.serial_no;
	serial.serial_state = SERISTAT_DEBT;
	serial.serial_type = TXCODE_FAN_BALANCE;
	// 借用显示卡号字段保存商户号
	sprintf(serial.showid,"%d",param.shop_id);
	getsysdate(serial.operate_date);
	getsystime(serial.operate_time);
	des2src(serial.collect_date,serial.operate_date);
	des2src(serial.collect_time,serial.operate_time);
	des2src(serial.enteract_date,serial.operate_date);
	des2src(serial.enteract_time,serial.operate_time);

	des2src(serial.oper_code,rPack->scard0);
	des2src(serial.reserve_1,rPack->scert_addr);
	serial.in_balance = param.remain_balance;
	serial.trade_fee = param.remain_balance;

	des2src(param.tx_date,serial.operate_date);
	des2src(param.tx_time,serial.operate_time);
	des2src(param.oper_code,rPack->scard0);
	
	ret = do_parse_shop(&param);
	if(ret)
	{
		writelog(LOG_ERR,"商户解款失败shop[%d] ret [%d]",param.shop_id,ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LVOL1,F_DAMT1,0);
	
		
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			//sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			//strcat(out_pack->vsmess,sMsg);
			writelog(LOG_INFO,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
		}
	}
	out_pack->lvol1 = IA.iSerialNo;
	out_pack->damt1 = param.free_balance;
	sprintf(out_pack->vsmess,"流水号:%d 解款金额[%.2lf]元,余额[%.2lf]元"
		,IA.iSerialNo,rPack->damt1,out_pack->damt1);
	//strcat(out_pack->vsmess,IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	
	//保存流水
	ret = DB_t_tif_tradeserial_add(&serial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
L_RETU:
	return -1;
}

