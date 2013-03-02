/** 
 * 模块名 - 圈存转账交易冲正
 * 文件名 F240015.cpp
 * 文件实现功能
 * 作者 
 * 版本
 * 日期 2008-08-29
 * 备注
 * $Id$
 */

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

int F240003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

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

	p->in_balance=0;						//入卡值
	IA->dInCardBala=0;					//入卡值
	IA->dOutCardBala=-1;					//出卡值
	IA->iTxCnt=1;						//交易次数
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


static int do_enteract(T_t_tif_tradeserial *reverse_serial,T_t_tif_tradeserial *tradeserial,InAcc *IA)
{
	int ret;
	double new_serial;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&new_serial);
	if(ret)
	{
		writelog(LOG_ERR,"生成交易流水号错误");

		return ret;
	}
	tradeserial->serial_no = D2I(new_serial);
	tradeserial->serial_state = SERISTAT_DEBT;
	tradeserial->in_balance = reverse_serial->out_balance;
	tradeserial->out_balance = reverse_serial->in_balance;
	tradeserial->trade_fee = -reverse_serial->trade_fee;
	getsysdate(tradeserial->operate_date);
	getsystime(tradeserial->operate_time);
	des2src(tradeserial->enteract_time,tradeserial->operate_time);


	// 贷方账号
	des2src(IA->sArrInActno[1],tradeserial->in_account_id);
	// 借方账号
	des2src(IA->sArrInActno[0],tradeserial->out_account_id);
	// 交易金额
	IA->dArrInAmt[0] = tradeserial->trade_fee;
	IA->iFeeType = tradeserial->comu_ver;
	// 冲正标志
	IA->iTxFlag = ACC_TYPE_RUSH;
	ret = process(IA,tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process account ret[%d]",ret);
		return ret;
	}
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	// 记录水流水号
	reverse_serial->reviseserial_no = tradeserial->serial_no;
	
	return 0;
}
// 
static int do_reverse(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	// 先在后台冲正流水,然后标记流水为冲正状态, 由 bankguard 进行冲正
	int ret;
	InAcc IA;
	char logic_date[9] = "";
	ST_PACK req_pack;
	T_t_tif_tradeserial reverse_serial;
	T_t_tif_tradeserial tradeserial;
	memset(&reverse_serial,0,sizeof reverse_serial);
	memset(&tradeserial,0,sizeof tradeserial);
	memset(&IA,0,sizeof IA);

	int serial_no;
	char oper_code[11] = "";
	serial_no = in_pack->lvol0;
	des2src(oper_code,in_pack->scust_limit);
	GetLogicDate(logic_date);
	
	if(strcmp(logic_date,in_pack->sdate0) != 0)
	{
		writelog(LOG_ERR,"reverse logic date error,system[%s],input[%s]",logic_date,in_pack->sdate0);
		return E_INPUT_DATE;
	}
	

	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(serial_no,&reverse_serial);
	if(ret)
	{
		writelog(LOG_ERR,"read serial error,serialno[%d]",serial_no);
		// 无对应流水,就返回冲正成功
		if(DB_NOTFOUND == ret)
			return 0;
		return E_DB_TRADESERIAL_R;
	}
	if(reverse_serial.serial_state == SERISTAT_DEBT)
	{
		IA.iUseCardFlag = in_pack->lvol1; // 是否卡交易 
		memcpy(&tradeserial,&reverse_serial,sizeof tradeserial);
		ret = do_enteract(&reverse_serial,&tradeserial,&IA);
		if(!ret)
		{
			// 流水状态标志成 已冲正
			reverse_serial.serial_state = SERISTAT_RUSH;
			ret = DB_t_tif_tradeserial_update_lock_by_cur(&reverse_serial);
			if(ret)
			{
				writelog(LOG_ERR,"更新被冲正流水失败,ret[%d]",ret);
				ret = E_DB_TRADESERIAL_U;
			}
			else
			{
				// 生成一笔圈存冲正流水
				memset(&req_pack,0,sizeof req_pack);
				sprintf(req_pack.sserial0,"%d",reverse_serial.card_id);
				req_pack.lvol5 = D2I(reverse_serial.trade_fee * 100.0);
				req_pack.lvol6 = D2I(reverse_serial.in_balance * 100.0);
				des2src(req_pack.scust_auth,reverse_serial.b_act_id);
				req_pack.lvol2 = reverse_serial.sys_id;
				req_pack.lvol1 = reverse_serial.trade_count;
				req_pack.lvol3 = reverse_serial.purse_id;
				req_pack.lvol0 = reverse_serial.serial_no; // 被冲正的流水号
				sprintf(req_pack.sorder2,"%d",reverse_serial.device_id);
				ret = F240003(handle,iRequest,&req_pack,pRetCode,szMsg);
				if(ret)
				{
					writelog(LOG_ERR,"登记圈存冲正流水失败,ret[%d]",*pRetCode);
					ret = *pRetCode;
				}
			}
		}
	}
	else
	{
		writelog(LOG_ERR,"交易流水已被冲正,不能再次冲正,serial[%d]logicdate[%s]",
				 reverse_serial.serial_no,reverse_serial.enteract_date);
		ret = 0;
	}
	// 关闭游标
	DB_t_tif_tradeserial_free_lock_cur();
	return ret;
}


int F240015(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_reverse(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	writelog(LOG_ERR,"冲正成功,logic_date[%s],serial_no[%d]",rPack->sdate0,rPack->lvol0);
	return 0;
}

