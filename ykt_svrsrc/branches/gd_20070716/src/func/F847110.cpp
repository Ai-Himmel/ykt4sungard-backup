/* --------------------------------------------
 * ��������: F847110.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ���¿���Ϣǰ��ѯ����Ϣ
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "fdsqc.h"
#include "pubdef.h"
#include "errdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dictionary.h"
#include "dbfunc_foo.h"

int F847110(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int card_id=0;
	char physical_no[8+1]="";
	T_t_pif_card	tCard;
	T_t_pif_spefee 	tSpeFee;
	T_t_cif_customer  tCustomer;
	T_t_aif_account   tAccount;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	char seed_key[17] = "";							//������Կ
	
	ResetNormalCPack(&aPack,0,1);
	memset(&tCard,0,sizeof(tCard));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	card_id = in_pack->lvol0;				//����ʶ
	des2src(physical_no,in_pack->sbank_acc);
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	if(card_id==0)
	{
		ret=get_card_no_by_physical_no(&card_id,physical_no);
		if(ret)
		{
			*pRetCode= E_CARDNO_NOT_EXIST;
			writelog(LOG_ERR,"get_card_no_by_physical_no error,ret=[%d] physical_no=[%s]",ret,physical_no);
			goto L_RETU;
		}
	}
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(card_id!=tCard.card_id)
	{
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(tCard.state_id[CARDSTAT_TYPE_REG]!=STATE_TRUE)
	{
		*pRetCode=E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	//�õ��շ����
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	if(tCustomer.fee_type<1)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//���¿ͻ�����շ�����ֶ�
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode= E_CUSTOMER_NOT_EXIST;
			else
				*pRetCode= E_DB_CUSTOMER_U;
			goto L_RETU;
		}
	}
	DB_t_cif_customer_free_lock_cur();

	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,0,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_ACTNO_NOT_EXIST;
		else
			*pRetCode= E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	if(tAccount.cur_freebala<0)
	{
		*pRetCode=E_ACCOUNT_OVERDRAFT;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_LVOL1,F_LVOL5,F_SDATE0,F_LVOL0,F_LVOL10,F_LVOL11,F_SNAME,F_SNAME2,
					F_SCUST_AUTH,F_SSERIAL0,F_SCUST_AUTH2,F_SCUST_TYPE,
					F_SCUST_LIMIT,F_SCUST_NO,F_SBANK_ACC, F_SBANK_ACC2,F_SORDER0,
					F_SORDER1,F_SORDER2,F_SHOLDER_AC_NO,F_SSTAT_TYPE,
					F_SSTAT_TYPE2,F_SNATION_CODE,F_SBRANCH_CODE0,0);
	out_pack->lvol0 = tCard.card_id;						//����ʶ
	out_pack->damt0=D4U5(tAccount.cur_freebala,2);			//�����
	des2src(out_pack->sdate0,tCard.end_time);				//��Ч��ֹ����
	out_pack->lvol1 = tCustomer.cut_type;					//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;					//�շ����
	des2src(out_pack->sname,tCustomer.cut_name);			//ѧ��\Ա������
	des2src(out_pack->sserial0,tCustomer.classdept_no);		//��λ����
	des2src(out_pack->scust_auth2,tCustomer.man_id);		//���֤��
	des2src(out_pack->scust_type,tCustomer.sex);			//�Ա�
	des2src(out_pack->scust_limit,tCustomer.stuemp_no);		//ѧ��\Ա����
	des2src(out_pack->sname2,tCustomer.lib_cardid);			//ͼ��֤��
	des2src(out_pack->scust_no,tCard.showid);				//��ʾ����
	des2src(out_pack->sbank_acc,tCard.physical_no);			//������
	out_pack->lvol10=tAccount.consume_count;				//���н��״���
	out_pack->lvol11=tAccount.subsidy_no;					//���в������κ�
	memcpy(seed_key,STATIC_SEED_KEY,16);				//��������Կ
	EncodePwd(seed_key,out_pack->sbank_acc2,tCard.password,1);	//������
	
	strcpy(out_pack->sorder0,CARD_STRUCT_VERSION);			//�ƿ��汾��
	strcpy(out_pack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//����ע���ʶ��
	strcpy(out_pack->sorder2,CARD_REGISTER_SERVICE_CODE);	//����ע���ʶ��
	sprintf(out_pack->sholder_ac_no,"%d",tCustomer.cut_id);		//�ͻ���
	des2src(out_pack->sstat_type,tCustomer.man_idtype);			//֤������
	des2src(out_pack->snation_code,tCustomer.country);			//����
	sprintf(out_pack->sstat_type2,"%d",tCustomer.nation);			//����
	des2src(out_pack->sbranch_code0,tCustomer.school_code);		//ԺУ����

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return  -1;
}
