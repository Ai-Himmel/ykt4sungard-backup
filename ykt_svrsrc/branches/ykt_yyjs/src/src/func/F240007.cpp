/* --------------------------------------------
 * 程序名称: F240007.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 响应前置机的请求,根据银行对帐文件进行对帐
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
#include "profile.h"

int F240007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	T_t_tif_bank_comp	bank_comp;				// 银行对账文件数据存储表
	T_t_tif_report_trans_comp trans_comp;		// 财务统计报表
	T_t_tif_tradeserial	tradeserial;			// 当前流水表
	T_t_tif_tradeserial_his his_tradeserial;	// 历史流水表	
	T_t_tif_diff_transfer  diff_transfer;		// 银行对账文件和流水文件对账差异表

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";					// 结算时间从文件名中取得

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	memcpy(forward_date, rPack->scard1 + 6, 8);		// BANK + 银行标识(04) + 日期 + txt
	writelog(LOG_ERR,"bank compare name=[%s]", rPack->scard1);

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	des2src(bank_comp.bankcard, rPack->scust_auth);		// 银行卡号
	des2src(bank_comp.bank_sn, rPack->scust_auth2);		// 银行端流水号
	bank_comp.card_id = atoi(rPack->sorder0);			// 校园卡交易卡号
	bank_comp.local_sn = atoi(rPack->semp_no);			// 校园卡流水号		
	des2src(bank_comp.op_date, forward_date);			// 对账的交易时间
	des2src(bank_comp.trans_money, rPack->sorder1);		// 转帐金额
	des2src(bank_comp.tx_code, rPack->scust_type);		// 交易代码
	writelog(LOG_ERR, "bank_card=[%20.20s], bank_sn=[%20.20s], card_id=[%d], local_sn=[%d], date=[%8.8s], trade_code=[%2.2s], trans_money=[%9.9s]", bank_comp.bankcard, bank_comp.bank_sn, bank_comp.card_id, bank_comp.local_sn, bank_comp.op_date, bank_comp.tx_code, bank_comp.trans_money);
	
	// 文件读完标识, 如果文件已经读完了, 则开始进行对账, 0表示还需读取记录, 1表示没有记录可读
	if (0 == rPack->lvol0)
	{
		ret = DB_t_tif_bank_comp_add(&bank_comp);
		if (ret)
		{
			writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
			goto LRet;
		}

		ret = db_commit();
		if (ret)
		{
			writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
			goto LRet;
		}

		goto L_RETU;
	}
	
	//开始进行对帐
	cnt=0;

	// 对一卡通转帐总数
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	// 对一卡通转帐总金额
	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
					break;
				}
				else		
					break;
			}
			else
				goto LRet;
		}

		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));

		// 以银行端的存储的一卡通流水号到一卡通流水表中查询数据
		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		if(ret)
		{
			if(100==ret)
			{
				// 一卡通中不存在的流水, 银行端存在的流水, 记入对账差异表中
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		if(his_tradeserial.serial_state!=2)
		{
			// 一卡通中存在的流水, 发起未入账, 银行端对此流水已经入账, 记入对账差异表中	
			strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
			strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
			diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
			strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
			diff_transfer.card_id=bank_comp.card_id;
			diff_transfer.local_amt=0;
			diff_transfer.local_sn=bank_comp.local_sn;
			diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
			diff_transfer.status=1;
			ret=DB_t_tif_diff_transfer_add(&diff_transfer);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
				break;
			}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

L_RETU:
	return ret;
}


