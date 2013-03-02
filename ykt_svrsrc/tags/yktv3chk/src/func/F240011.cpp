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
#include "busqc.h"



int F240011(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

#if 0
	int ret=0;
	int custid=0;
	char stuempno[20+1]="";
	char bankcardno[30+1]="";
	int cardno=0;
	int area_id=0;

	T_t_card t_card;
	T_t_customer t_customer;
	T_t_cut_relation cut_relation;

	memset(&t_card,0,sizeof(t_card));
	memset(&t_customer,0,sizeof t_customer);
	memset(&cut_relation,0,sizeof cut_relation);
	
	custid=rPack->lvol8;
	des2src(stuempno,rPack->scust_auth);
	cardno=rPack->lvol0;
	des2src(bankcardno,rPack->sphone);
	area_id=rPack->lvol1;
	if(0==custid)
	{
		if(0==cardno)
		{
			ret=DB_t_customer_read_by_stuempno_and_area(stuempno,area_id,&t_customer);			//����ʶ
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_customer_read_by_stuempno_and_area error,errcode=[%d]",ret);
				*pRetCode=E_DB_CUSTOMER_R;
				goto L_RETU;
			}
			custid=t_customer.custid;
		}
		else
		{
			ret=DB_t_card_read_by_cardno(cardno, &t_card);
			if(ret)
			{
				writelog(LOG_ERR,"GetLostCardIdByCustomId error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
			custid=t_card.custid;
		}
	}
	//�ж϶�Ӧ��ϵ�Ƿ����
	ret=DB_t_cut_relation_read_by_custid_and_outside_no(custid,bankcardno, &cut_relation);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_cut_relation_read_by_custid_and_outside_no error,error code=[%d]",ret);
		if(DB_NOTFOUND==ret)	
		{
			*pRetCode=E_TRANS_RELATION_NOEXIT;
		}
		else *pRetCode=E_DB_CUT_RLTN_R;
		goto L_RETU;
	}
#endif
	return 0;
L_RETU:
	return -1;
}


