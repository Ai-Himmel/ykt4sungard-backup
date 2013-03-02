/* --------------------------------------------
 * ��������: F240011.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: �ж�У԰�������п��İ󶨶�Ӧ��ϵ
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



int F240011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int cut_id=0;
	char stuemp_no[20+1]="";
	char bankcard_no[30+1]="";
	int card_id=0;
	int area_id=0;

	T_t_pif_card t_card;
	T_t_cif_customer t_customer;
	T_t_pif_cut_relation cut_relation;

	memset(&t_card,0,sizeof(t_card));
	memset(&t_customer,0,sizeof t_customer);
	memset(&cut_relation,0,sizeof cut_relation);
	
	cut_id=rPack->lvol8;
	des2src(stuemp_no,rPack->scust_auth);
	card_id=rPack->lvol0;
	des2src(bankcard_no,rPack->sphone);
	area_id=rPack->lvol1;
	if(0==cut_id)
	{
		if(0==card_id)
		{
			ret=DB_t_cif_customer_read_by_stuemp_no_and_area(stuemp_no,area_id,&t_customer);			//����ʶ
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_cif_customer_read_by_stuemp_no_and_area error,errcode=[%d]",ret);
				*pRetCode=E_DB_CUSTOMER_R;
				goto L_RETU;
			}
			cut_id=t_customer.cut_id;
		}
		else
		{
			ret=DB_t_pif_card_read_by_card_id(card_id, &t_card);
			if(ret)
			{
				writelog(LOG_ERR,"GetLostCardIdByCustomId error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
			cut_id=t_card.cosumer_id;
		}
	}
	//�ж϶�Ӧ��ϵ�Ƿ����
	ret=DB_t_pif_cut_relation_read_by_cut_id_and_outside_no(cut_id,bankcard_no, &cut_relation);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_cut_relation_read_by_cut_id_and_outside_no error,error code=[%d]",ret);
		if(DB_NOTFOUND==ret)	
		{
			*pRetCode=E_TRANS_RELATION_NOEXIT;
		}
		else *pRetCode=E_DB_CUT_RLTN_R;
		goto L_RETU;
	}
	
	return 0;
L_RETU:
	return -1;
}


