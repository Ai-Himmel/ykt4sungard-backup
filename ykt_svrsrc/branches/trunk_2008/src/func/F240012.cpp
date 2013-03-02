/* --------------------------------------------
 * 程序名称: F240012.sqc
 * 创建日期: 2008-05-22
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 应上海工行要求单独进行对账设计
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
#include "banktype.h"

int F240012(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	FILE *fp = NULL;
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
	BANK_SHGH_TRADE_COMP_STRUCT shgh_bank_comp, shgh_bank_comp_bak;	// 上海工行对账文件记录
	
	memset(&shgh_bank_comp, 0, sizeof(shgh_bank_comp));
	memset(&shgh_bank_comp_bak, 0, sizeof(shgh_bank_comp_bak));
	
	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";					// 结算时间从文件名中取得

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;
	double temp=0;

	memcpy(forward_date, rPack->scard1, 8);

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	ret = GetParameter(GLOBAL_UPLOAD_PATH, path_name);
	if (ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	strcat(file_name, path_name);
	strcat(file_name, "/");
	strcat(file_name, rPack->scard0);
	
	if ((fp = fopen(file_name, "rb")) == NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]", file_name);
		ret = E_TRANS_COMP_OPENFILE;
		goto L_RETU;
	}

	// 获取对账文件第一条记录
	if (NULL == fgets((char *)(&shgh_bank_comp), sizeof(BANK_SHGH_TRADE_COMP_STRUCT), fp))	
	{
		writelog(LOG_ERR,"fgets error");
		ret = E_TRANS_COMP_GETRECORD;
		goto L_RETU;
	}

	strncpy(forward_date, shgh_bank_comp.cmp_date, sizeof(shgh_bank_comp.cmp_date));
	
	ret = DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date, &trans_comp);
	if (ret != 100 && ret != 0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	
	if (1 == trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}

	writelog(LOG_ERR, "bank_card=[%25.25s], date=[%8.8s], trans_money=[%9.9s], device_id=[%40.40s]", shgh_bank_comp.bank_account, shgh_bank_comp.cmp_date, shgh_bank_comp.trans_money, shgh_bank_comp.device_id);
	
	while (1)
	{	
		memset(&bank_comp,0,sizeof(bank_comp));
		strncpy(bank_comp.bankcard, shgh_bank_comp.bank_account, sizeof(shgh_bank_comp.bank_account));					// 银行卡号
		des2src(bank_comp.bank_sn, rPack->scust_auth2);								// 银行端流水号
		if (!strlen(bank_comp.bank_sn)) { des2src(bank_comp.bank_sn, "2501"); } 
		bank_comp.card_id = atoi(rPack->sorder0);									// 校园卡交易卡号
		if (0 == bank_comp.card_id) { bank_comp.card_id = 2501; }		
		bank_comp.local_sn = atoi(rPack->semp_no);									// 校园卡流水号		
		if (0 == bank_comp.local_sn) { bank_comp.local_sn = cnt; }
		des2src(bank_comp.op_date, forward_date);									// 对账的交易时间
		des2src(bank_comp.trans_money, shgh_bank_comp.trans_money);					// 转帐金额
		des2src(bank_comp.tx_code, rPack->scust_type);								// 交易代码
		if (!strlen(bank_comp.tx_code)) { des2src(bank_comp.tx_code, "01"); }
		strncpy(bank_comp.device_id, shgh_bank_comp.device_id, sizeof(shgh_bank_comp.device_id));

		writelog(LOG_ERR, "bank_card=[%25.25s], bank_sn=[%25.25s], card_id=[%d], local_sn=[%d], date=[%8.8s], trade_code=[%2.2s], trans_money=[%9.9s], device_id=[%40.40s]", bank_comp.bankcard, bank_comp.bank_sn, bank_comp.card_id, bank_comp.local_sn, bank_comp.op_date, bank_comp.tx_code, bank_comp.trans_money, bank_comp.device_id);
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

		cnt++;
		if (NULL == fgets((char *)(&shgh_bank_comp), sizeof(BANK_SHGH_TRADE_COMP_STRUCT), fp))	
		{
			writelog(LOG_ERR,"no more records get!");
			break;
		}
	}
	
	if (fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]", file_name);
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
		bank_amt=bank_amt+atof(bank_comp.trans_money);
	}

	// 上海银行不对差异, 仅仅对总数
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
	if (ret)
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

