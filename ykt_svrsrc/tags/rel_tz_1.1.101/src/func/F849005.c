/* --------------------------------------------
 * ��������: F849005.c
 * ��������: 2006-7-31
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���²�������
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F849005(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_pif_card tCard;
	T_t_water_info tWater;

	memset(&tCard,0,sizeof tCard);
	ret = DB_t_pif_card_read_by_card_id(in_pack->lvol1,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}
	
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ret = DB_t_water_info_read_lock_by_c1_and_cust_no(tCard.cosumer_id,&tWater);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			*pRetCode = E_DB_WATER_INFO_N;
		}
		else
			*pRetCode = E_DB_WATER_INFO_R;
		goto L_RETU;
	}
	des2src(tWater.card_phyid,tCard.physical_no);
	ret = DB_t_water_info_update_lock_by_c1_and_cust_no(&tWater);
	if(ret)
	{
		*pRetCode = E_DB_WATER_INFO_U;
		goto L_RETU;
	}
	DB_t_water_info_free_lock_by_c1();
	return 0;
	
L_RETU:
	return -1;
}

