/* --------------------------------------------
 * ��������: F240007.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ��Ӧǰ�û�������,�������ж����ļ����ж���
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

	T_t_tif_bank_comp	bank_comp;				// ���ж����ļ����ݴ洢��
	T_t_tif_report_trans_comp trans_comp;		// ����ͳ�Ʊ���
	T_t_tif_tradeserial	tradeserial;			// ��ǰ��ˮ��
	T_t_tif_tradeserial_his his_tradeserial;	// ��ʷ��ˮ��	
	T_t_tif_diff_transfer  diff_transfer;		// ���ж����ļ�����ˮ�ļ����˲����

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";					// ����ʱ����ļ�����ȡ��

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	memcpy(forward_date, rPack->scard1 + 6, 8);		// BANK + ���б�ʶ(04) + ���� + txt
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
	des2src(bank_comp.bankcard, rPack->scust_auth);		// ���п���
	des2src(bank_comp.bank_sn, rPack->scust_auth2);		// ���ж���ˮ��
	bank_comp.card_id = atoi(rPack->sorder0);			// У԰�����׿���
	bank_comp.local_sn = atoi(rPack->semp_no);			// У԰����ˮ��		
	des2src(bank_comp.op_date, forward_date);			// ���˵Ľ���ʱ��
	des2src(bank_comp.trans_money, rPack->sorder1);		// ת�ʽ��
	des2src(bank_comp.tx_code, rPack->scust_type);		// ���״���
	writelog(LOG_ERR, "bank_card=[%20.20s], bank_sn=[%20.20s], card_id=[%d], local_sn=[%d], date=[%8.8s], trade_code=[%2.2s], trans_money=[%9.9s]", bank_comp.bankcard, bank_comp.bank_sn, bank_comp.card_id, bank_comp.local_sn, bank_comp.op_date, bank_comp.tx_code, bank_comp.trans_money);
	
	// �ļ������ʶ, ����ļ��Ѿ�������, ��ʼ���ж���, 0��ʾ�����ȡ��¼, 1��ʾû�м�¼�ɶ�
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
	
	//��ʼ���ж���
	cnt=0;

	// ��һ��ͨת������
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	// ��һ��ͨת���ܽ��
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

		// �����ж˵Ĵ洢��һ��ͨ��ˮ�ŵ�һ��ͨ��ˮ���в�ѯ����
		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		if(ret)
		{
			if(100==ret)
			{
				// һ��ͨ�в����ڵ���ˮ, ���ж˴��ڵ���ˮ, ������˲������
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
			// һ��ͨ�д��ڵ���ˮ, ����δ����, ���ж˶Դ���ˮ�Ѿ�����, ������˲������	
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


