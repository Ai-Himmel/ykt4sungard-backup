/* --------------------------------------------
 * ��������: F847225.sqc
 * ��������: 2006-10-25
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:  ��ֵƽ̨��⿨״̬
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

int F847225(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	/*
	int card_id = 0;
	char card_phy_id[9] = "";
	// �ͻ���
	int cust_id = 0;
	// δ������״̬
	int card_state = 0;
	// ����ҵ�������ܺ�
	int trade_request = 0;
	double paymoney = 0;
	int lost_card_id = 0;
	T_tab_card_info sync_card;
	T_t_pif_card card_info;
	T_t_cif_customer customer;
	T_t_aif_account account;

	ST_CPACK aPack;
	ST_PACK * out_pack = &(aPack.pack);
	int ret;

	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_VSMESS,F_LVOL1,F_SEMAIL,F_SCUST_AUTH
		,F_SDATE0,F_LVOL2,F_LVOL3,F_SBANK_ACC,F_LVOL4,0);
	
	card_id = in_pack->lvol0;
	des2src(card_phy_id,in_pack->sname);
	if(card_id > 0)
	{
		// ��鿨��
		memset(&card_info,0,sizeof card_info);
		ret = DB_t_pif_card_read_by_card_id(card_id,&card_info);
		if(ret)
		{
			writelog(LOG_ERR,"��ȡ����Ϣʧ��cardid[%d]",card_id);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_CARD_N;
			else
				*pRetCode = E_DB_CARD_R;
			goto L_RETU;
		}
		// ���������
		if(strcmp(card_info.physical_no,card_phy_id))
		{
			// ���׿����������Ų���
			writelog(LOG_ERR,"�ϴ�������[%s] ʵ��������[%s]"
				,card_phy_id,card_info.physical_no);
			*pRetCode = E_INPUT_CARDNO;
			goto L_RETU;
		}
		// ����ȷ,��鿨״̬
		ret = CheckCardStatus(card_info.state_id);
		if(ret)
		{
			writelog(LOG_ERR,"��״̬�쳣cardid[%d] status[%d]",card_id,ret);
			switch(ret)
			{
				case E_CARDNO_LOGOUT:
					out_pack->lvol0 = UNI_CARD_CANCEL;
					*pRetCode = E_CARDNO_LOGOUT;
					goto L_RETU;
				case E_CARDNO_FREEZE:
					out_pack->lvol0 = UNI_CARD_FROZEN;
					break;
				case E_CARDNO_LOST:
					out_pack->lvol0 = UNI_CARD_LOSS;
					break;
				case E_CARDNO_WFAIL:
					out_pack->lvol0 = UNI_CARD_REWRITE_CARD;
					sprintf(out_pack->vsmess,"��Ŀǰ״̬Ϊд��ʧ��,������д!");
					break;
				default:
					*pRetCode = E_CARDNORMAL;
					goto L_RETU;
			}
			// ����ǲ�д����Ϣ
			
		}
		else
		{
			// ����������ǳ�ֵ
			out_pack->lvol0 = UNI_CARD_ADD_MONEY;
		}
		// ��״̬����, 
		memset(&customer,0,sizeof customer);
		ret = DB_t_cif_customer_read_by_cut_id(card_info.cosumer_id,&customer);
		if(ret)
		{
			writelog(LOG_DEBUG,"δ�ҵ� �ͻ���[%d]",card_info.cosumer_id);
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_CUSTOMER_N;
			else
				*pRetCode = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
		
		out_pack->lvol1 = cust_id;
		des2src(out_pack->semail,customer.cut_name);
		des2src(out_pack->scust_auth,customer.stuemp_no);
		des2src(out_pack->sdate0,customer.can_time);
		out_pack->lvol2 = customer.cut_type;
		out_pack->lvol3 = customer.fee_type;
		memset(&account,0,sizeof account);
		//ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		//	customer.cut_id,ACCTYPE_PERMAIN,&account);
		ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&account);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				// �ͻ����˻�,Ӧ���ǰ��¿�
				*pRetCode = E_DB_ACCOUNT_N;
				goto L_RETU;
			}
			else
			{
				writelog(LOG_ERR,"��ѯ�˻���Ϣʧ��cutid [%d]",customer.cut_id);
				*pRetCode = E_DB_ACCOUNT_R;
				goto L_RETU;
			}
		}
		des2src(out_pack->sbank_acc,account.account_id);
		
	}
	else
	{
		// ����������Ƿ��Ѿ����ϴ�ͬ������.
		memset(&sync_card,0,sizeof sync_card);
		ret = queryCustidAndExpTime(card_phy_id,CARDINF_NEW_STATE,&cust_id,&sync_card);
		if(ret)
		{
			memset(&sync_card,0,sizeof sync_card);
			ret = queryCustidAndExpTime(card_phy_id,CARDINF_AGAIN_STATE,&cust_id,&sync_card);
			if(ret)
			{
				writelog(LOG_DEBUG,"����Ϣδ�ҵ�phyid[%s] ",card_phy_id);
				sprintf(szMsg,"�ÿ�����ʶ��!!");
				*pRetCode = ret;
				goto L_RETU;
			}
			else
			{
				//card_state = CARDINF_AGAIN_STATE;
				sprintf(out_pack->vsmess,"�¿�");
			}
		}
		ret = IsExistCardByPhyCardNo(card_phy_id);
		if(ret)
		{
			*pRetCode = E_CARD_PUBLISHED;
			goto L_RETU;
		}
		// TODO: ���ý��ɽ��
		paymoney = sync_card.fee;
		memset(&customer,0,sizeof customer);
		ret = DB_t_cif_customer_read_by_cut_id(cust_id,&customer);
		if(ret)
		{
			writelog(LOG_ERR,"��ѯ�ͻ���Ϣʧ��custid[%d]cardphyid[%s] ret[%d] ",
				cust_id,card_phy_id,ret);
			if(DB_NOTFOUND == ret)
				*pRetCode = ret;
			else
				*pRetCode = E_DB_CUSTOMER_R;
			goto L_RETU;
		}
		
		out_pack->lvol1 = cust_id;
		des2src(out_pack->semail,customer.cut_name);
		des2src(out_pack->scust_auth,customer.stuemp_no);
		des2src(out_pack->sdate0,customer.can_time);
		out_pack->lvol2 = customer.cut_type;
		out_pack->lvol3 = customer.fee_type;
		// �жϽ��׹��ܺ�
		memset(&account,0,sizeof account);
		
		//ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		//	customer.cut_id,ACCTYPE_PERMAIN,&account);
		ret=GetLostCardIdByCustomId_TypeId(customer.cut_id,CT_NORMAL,&lost_card_id);
		if(ret)
		{
			if(E_DB_CARD_R != ret)
			{
				// �ͻ����˻�,Ӧ���ǰ��¿�
				if(5 == customer.fee_type)
				{
					trade_request = 847124;
					sprintf(out_pack->vsmess,"�ÿ���Ҫ��ȡѺ��%.2lfԪ",paymoney);
				}
				else
				{
					trade_request = 847101;
					sprintf(out_pack->vsmess,"�ÿ���Ҫ��ȡ�ɱ���%.2lfԪ",paymoney);
				}
				out_pack->damt0 = paymoney;
				card_state = UNI_CARD_NEW_CARD;
			}
			else
			{
				writelog(LOG_ERR,"��ѯ����Ϣʧ��cutid [%d]",customer.cut_id);
				*pRetCode = E_DB_CARD_R;
				goto L_RETU;
			}
		}
		else
		{
			
			// ���쿨
			trade_request = 847104;
			out_pack->damt0 = paymoney; //- account.cur_freebala;
			
			if(out_pack->damt0 > 0)
			{
				//
				sprintf(out_pack->vsmess,"���иÿ�Ҫ���˻�����п۳�%.2lf Ԫ�ɱ���\
					,��Ŀǰ�˻�����,������Ҫ��ֵ%.2lfԪ",paymoney,out_pack->damt0);
			}
			else
			{
			
				// �˻�����Ѿ��㹻������.
			sprintf(out_pack->vsmess,"���иÿ���Ҫ%.2lf Ԫ�ɱ���,������Ҫ��ֵ%.2lfԪ",
				paymoney,paymoney);
			out_pack->damt0 = paymoney;
			//}
			card_state = UNI_CARD_REISSUE_CARD;
			writelog(LOG_DEBUG,out_pack->vsmess);
		}
		out_pack->lvol4 = trade_request;
		out_pack->lvol0 = card_state;
	}

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	*/
L_RETU:
	return -1;
}
