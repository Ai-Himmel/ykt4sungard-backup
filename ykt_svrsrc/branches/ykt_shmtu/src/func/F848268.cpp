/* --------------------------------------------
 * ��������: F848268.c
 * ��������: 2007-04-10
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:�Ž�����ɾ��
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

static int do_848268(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	int row = 0;
	T_t_door_device_cardlist door_card;
	T_t_pif_device device;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	memset(&door_card,0,sizeof door_card);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_VSMESS,0);

	writelog(LOG_INFO,"cutid[%d],ctlid[%d]",in_pack->lvol0,in_pack->lvol1);
	if(unlike_tbl_id(in_pack->lvol0))
	{
		sprintf(out_pack->vsmess,"����: �ͻ��Ų���ȷ[%d]",in_pack->lvol0);
		out_pack->lvol0 = 0;
		goto L_PUTROW_RET;
	}
	if(unlike_tbl_id(in_pack->lvol1))
	{
		sprintf(out_pack->vsmess,"����: �Ž��Ų���ȷ[%d]",in_pack->lvol1);
		out_pack->lvol0 = 0;
		goto L_PUTROW_RET;
	}

	
	ret = DB_t_door_device_cardlist_read_by_device_id_and_cust_id(
		in_pack->lvol1,in_pack->lvol0,&door_card);

	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			sprintf(out_pack->vsmess,"����: �ͻ���[%d]�Ž�[%d]������"
				,in_pack->lvol0,in_pack->lvol1);
			out_pack->lvol0 = 0;
			goto L_PUTROW_RET;
		}
		else
			return E_DB_DOOR_CARDLIST_R;
	}
	// �ж��Ƿ��Ѿ�ɾ����
	/*
	if(door_card.status >= DOOR_FLAG_WAITING_DEL)
	{
		sprintf(out_pack->vsmess,"����: �ͻ���[%d]�Ž�[%d]�ѱ�ɾ��"
				,in_pack->lvol0,in_pack->lvol1);
		out_pack->lvol0 = 2;
		goto L_PUTROW_RET;
	}
	*/
	db_getsysdatetime2(door_card.update_time);
	//door_card.status = DOOR_FLAG_WAITING_DEL;
	door_card.add_del_flag[0] = ADDDELFLAG_DEL;
	ret = DB_t_door_device_cardlist_update_by_device_id_and_cust_id(
		in_pack->lvol1,in_pack->lvol0,&door_card);
	if(ret)
	{
		return E_DB_DOOR_CARDLIST_U;
	}
	
	sprintf(out_pack->vsmess,"�ɹ�: �ͻ���[%d]�Ž�[%d]��ɾ��"
				,in_pack->lvol0,in_pack->lvol1);
	out_pack->lvol0 = 1;
L_PUTROW_RET:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int F848268(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_848268(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	return 0;
}
