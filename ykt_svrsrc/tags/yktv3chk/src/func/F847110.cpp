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
#include "busqc.h"
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
	int cardno=0;
	T_t_card	tCard;
//	T_t_spefee 	tSpeFee;
	T_t_customer  tCustomer;
//	T_t_aif_account   tAccount;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	memset(&tCard,0,sizeof(tCard));
//	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
//	memset(&tAccount,0,sizeof(tAccount));
	cardno = in_pack->lvol0;				//����ʶ
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	ret=DB_t_card_read_by_cardno(cardno, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			return  E_CARDNO_NOT_EXIST;
		else
			return  E_DB_CARD_R;
	}
	if(cardno!=tCard.cardno)
	{
		writelog(LOG_ERR,"cardno[%d] db cardno[%d]",cardno,tCard.cardno);
		return E_DB_CARD_R;
	}
	if(strncmp(tCard.cardattr,CARDSTAT_REG,4)!=0)
	{
		if(tCard.cardattr[CARDSTAT_TYPE_REG]!=STATE_TRUE)
		{
			return E_CARDNO_LOGOUT;
		}
		else if(tCard.cardattr[CARDSTAT_TYPE_LOST]==STATE_TRUE)
		{
			return E_CARDNO_LOST;
		}

		else if(tCard.cardattr[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
		{
			return E_CARDNO_FREEZE;
		}
		//else if(tCard.cardattr[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			//return E_CARDNO_WFAIL;
	}
	//�õ��շ����
//	ret=DB_t_customer_read_lock_by_cur_and_custid(tCard.custid, &tCustomer);
//	if(ret)
//	{
//		writelog(LOG_ERR,"custid[%d]",tCard.custid);
//		if(DB_NOTFOUND==ret)
//			return  E_CUSTOMER_NOT_EXIST;
//		else
//			return  E_DB_CUSTOMER_R;
//		goto L_RETU;
//	}
//	if(tCustomer.feetype<1)
//	{
//		ret=DB_t_spefee_read_by_deptcode_and_custtype(tCustomer.deptcode, tCustomer.custtype,&tSpeFee);
//		if(ret)
//		{
//			if(DB_NOTFOUND==ret)
//			{
//				tCustomer.feetype=tCustomer.custtype;
//			}
//			else
//			{
//				DB_t_customer_free_lock_cur();
//				return E_DB_SPEFEE_R;
//				goto L_RETU;
//			}
//		}
//		else
//		{
//			tCustomer.feetype=tSpeFee.feetype;
//		}
//		//���¿ͻ�����շ�����ֶ�
//		ret=DB_t_customer_update_lock_by_cur(&tCustomer);
//		if(ret)
//		{
//			if(DB_NOTFOUND==ret)
//				return  E_CUSTOMER_NOT_EXIST;
//			else
//				return  E_DB_CUSTOMER_U;
//			goto L_RETU;
//		}
//	}
//	DB_t_customer_free_lock_cur();
	T_t_account cardaccount;

	memset(&cardaccount,0,sizeof(cardaccount));
	ret=DB_t_account_read_by_cardno_and_purseno(cardno,0,&cardaccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDACCNO;
		else
			return E_DB_ACCOUNT_R;
	}

	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_LVOL1,F_LVOL5,F_SDATE0,F_LVOL0,F_SNAME,F_SNAME2,F_SCUST_AUTH,F_SSERIAL0,F_SCUST_AUTH2,F_SCUST_TYPE,F_SCUST_LIMIT,F_SCUST_NO,F_SBANK_ACC,0);
	out_pack->lvol0 = tCard.cardno;							//����ʶ
	out_pack->damt0=D4U5(cardaccount.availbal,2);			//�����
	des2src(out_pack->sdate0,tCard.expiredate);				//��Ч��ֹ����
	out_pack->lvol1 = tCustomer.custtype;					//�ͻ����
	out_pack->lvol5 = tCard.feetype;						//�շ����
	des2src(out_pack->sname,tCustomer.custname);			//ѧ��\Ա������
	des2src(out_pack->sserial0,tCustomer.deptcode);			//��λ����
	des2src(out_pack->scust_auth2,tCustomer.idno);		//���֤��
	des2src(out_pack->scust_type,tCustomer.sex);			//�Ա�
	des2src(out_pack->scust_limit,tCustomer.stuempno);		//ѧ��\Ա����
//	des2src(out_pack->sname2,tCustomer.lib_cardid);			//ͼ��֤��
	des2src(out_pack->scust_no,tCard.showcardno);				//��ʾ����
	des2src(out_pack->sbank_acc,tCard.cardphyid);			//������
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
