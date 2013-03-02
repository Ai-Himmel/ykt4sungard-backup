/* --------------------------------------------
 * 程序名称: F847223.sqc
 * 创建日期: 2006-9-29
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  上大账务商户消费结算冲正
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

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iSerialNo = p->serial_no;				//流水号
	IA->iTradeNo = p->serial_type;		//交易码
	IA->iFeeType = 1;
	IA->iUseCardFlag = 0;
	// 冲正交易
	IA->iTxFlag = ACC_TYPE_RUSH;
	
	des2src(IA->sTxDate,p->operate_date);			//交易日期
	des2src(IA->sTxTime,p->operate_time);			//交易时间
	des2src(IA->sTxCollectDate,p->collect_date);		//采集日期
	des2src(IA->sTxCollectTime,p->collect_time);		//采集时间
	des2src(IA->sTxAccDate,p->enteract_date);		//记账日期
	des2src(IA->sTxAccTime,p->enteract_time);		//记账时间
	des2src(IA->sMdeOper,p->oper_code);			//操作员(发生错帐的操作员)

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//无卡交易
	IA->iTxCnt=0;								//交易次数
	IA->dInCardBala=p->in_balance;				//入卡值
	IA->dOutCardBala=0;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance = IA->dOutCardBala;			//出卡值
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}


static int do_rush_balance(T_t_tif_tradelog * tradelog,InAcc * pIA,T_t_tif_tradeserial* pSerial)
{
	int ret;
	int subindex;
	T_t_aif_account account;
	// 初始化入账模块
	subindex = pIA->iSubIndex;
	memset(pIA,0,sizeof(InAcc));
	pIA->dArrInAmt[0] = tradelog->op_fee * -1;
	des2src(pIA->sArrInActno[0],tradelog->act_id);
	pIA->iSubIndex = subindex;
	ret = process(pIA,pSerial);
	if(ret)
	{
		writelog(LOG_ERR,"消费解款冲正,账号[%s]失败[%.2lf]"
			,tradelog->act_id,tradelog->op_fee);
		return ret;
	}
	memset(&account,0,sizeof account);
	ret = DB_t_aif_account_read_by_account_id(tradelog->act_id,&account);
	if(ret)
	{
		writelog(LOG_ERR,"查询商户账户失败ret[%d]",ret);
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	// 更新账户余额
	account.last_bala += tradelog->op_fee;
	ret = DB_t_aif_account_update_by_account_id(tradelog->act_id,&account);
	if(ret)
	{
		writelog(LOG_ERR,"冲正后更新账户可用解款金额失败account[%s]"
			,tradelog->act_id);
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_U;
	}
	pSerial->trade_fee += tradelog->op_fee;
	return 0;
}

static int do_calc_shop_balance(int shop_id,double * balance)
{
	int ret;
	double free_bala = 0;
	int rows;
	T_v_cif_shop_tree shop_node;
	T_t_aif_account account;
	T_t_cif_shop shop;

	ret = DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(shop_id);
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
		memset(&shop,0,sizeof shop);
		ret = DB_t_cif_shop_read_by_shop_id(shop_node.leaf_id,&shop);
		if(ret)
		{
			DB_v_cif_shop_tree_close_select_by_c1();
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
			DB_v_cif_shop_tree_close_select_by_c1();
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		free_bala += account.last_bala;
	}
	*balance = free_bala;
	return 0;
}

int F847223(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char  ia_buf[1024]="";
	char sMsg[256]="";
	int rows;
	double dUniNo;
	InAcc IA;
	T_t_tif_tradelog tradelog;
	T_t_tif_tradeserial serial;
	T_t_tif_tradeserial old_serial;
	int shop_id;
	int i;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);


	if(strlen(rPack->scard0) <= 0)
	{
		*pRetCode = E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	ret = CheckOperatorPwd(rPack->scard0,rPack->semp_pwd);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	memset(&old_serial,0,sizeof old_serial);
	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(rPack->lvol1,&old_serial);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_FAN_SERIAL_NOT_EXISTS;
		else
			*pRetCode = E_DB_TRADESERIAL_N;
		goto L_RETU;
	}
	if(SERISTAT_RUSH == old_serial.serial_state)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"流水重复冲正,serial[%d] operator[%s]"
			,old_serial.serial_no,rPack->scard0);
		*pRetCode = E_FAN_ALREADY_RUSHED;
		goto L_RETU;
	}
	old_serial.serial_state = SERISTAT_RUSH;
	ret = DB_t_tif_tradeserial_update_lock_by_cur(&old_serial);
	if(ret)
	{
		writelog(LOG_ERR,"流水状态更新失败");
		*pRetCode = E_DB_TRADESERIAL_U;
		goto L_RETU;
	}
	DB_t_tif_tradeserial_free_lock_cur();
	//////////////////////////////////////////////////////////////////////////////////
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniNo);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	//初始化流水记录
	memset(&serial,0,sizeof serial);
	serial.serial_no = D2I(dUniNo);
	serial.serial_state = SERISTAT_DEBT;
	serial.serial_type = TXCODE_FAN_RUSH_BALANCE;
	getsysdate(serial.operate_date);
	getsystime(serial.operate_time);
	des2src(serial.collect_date,serial.operate_date);
	des2src(serial.collect_time,serial.operate_time);
	des2src(serial.enteract_date,serial.operate_date);
	des2src(serial.enteract_time,serial.operate_time);

	des2src(serial.oper_code,rPack->scard0);
	des2src(serial.reserve_1,rPack->scert_addr);
	serial.in_balance = serial.trade_fee;
	
	// 查询流水明细
	ret = DB_t_tif_tradelog_open_select_by_c2_and_serino_and_seri_type_and_outorin(
		old_serial.serial_no,old_serial.serial_type,DBCR_DEBIT);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_FAN_SERIAL_NOT_EXISTS;
		else
			*pRetCode = E_DB_TRADELOG_R;
		goto L_RETU;
	}
	rows= 0;
	memset(&IA,0,sizeof IA);
	while(1)
	{
		memset(&tradelog,0,sizeof tradelog);
		ret = DB_t_tif_tradelog_fetch_select_by_c2(&tradelog);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				else
					*pRetCode = E_FAN_SERIAL_NOT_EXISTS;
			}
			else
				*pRetCode = E_DB_TRADELOG_R;
			goto L_RETU;
		}
		rows++;
		ret = do_rush_balance(&tradelog,&IA,&serial);
		if(ret)
		{
			DB_t_tif_tradelog_close_select_by_c2();
			*pRetCode = ret;
			goto L_RETU;
		}
	}

	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LVOL1,F_DAMT1,F_DAMT2,F_SBANK_ACC,0);
	sprintf(out_pack->vsmess,"流水号:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			//sprintf(sMsg,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			//strcat(out_pack->vsmess,sMsg);
			writelog(LOG_INFO,"%s:%.2lf元 ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
		}
	}
	out_pack->lvol1 = serial.serial_no;
	// 冲正金额
	out_pack->damt1 = serial.trade_fee;
	des2src(out_pack->sbank_acc,old_serial.showid);
	// 计算商户余额
	shop_id = strtoul(old_serial.showid,NULL,10);
	ret = do_calc_shop_balance(shop_id,&(out_pack->damt2));
	if(ret)
	{
		writelog(LOG_ERR,"计算商户余额失败ret[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	//strcat(out_pack->vsmess,IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);

	serial.trade_fee *= -1;
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
