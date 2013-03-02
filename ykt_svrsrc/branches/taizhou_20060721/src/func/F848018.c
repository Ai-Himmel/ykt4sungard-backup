/* --------------------------------------------
 * ��������: F848012.c
 * ��������: 2005-10-20
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:�Ž���Ȩ������
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"


static int Add848018(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int rows = 0;
	T_t_door_group_member tDoorGrpMem;
	T_t_door_oper_right tOper;
	if(strcmp(in_pack->scust_limit,OPER_SYSTEM_KEY))
	{
		return E_OPER_NO_RIGHT_FOR_DOOR_GROUP;
	}
	ret = DB_t_door_group_member_open_select_by_cur1_and_group_id(in_pack->lvol0);
	while(1)
	{
		memset(&tDoorGrpMem,0,sizeof tDoorGrpMem);
		ret = DB_t_door_group_member_fetch_select_by_cur1(&tDoorGrpMem);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
				{
					return 0;
				}
				return E_DB_DOOR_GROUP_MEMBER_N;
			}
			return E_DB_DOOR_GROUP_MEMBER_R;
		}
		rows++;
		memset(&tOper,0,sizeof tOper);
		ret = DB_t_door_oper_right_read_by_oper_no_and_device_id(
			in_pack->scust_limit2,tDoorGrpMem.device_id,&tOper);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				//add 
				memset(&tOper,0,sizeof tOper);
				des2src(tOper.device_id,tDoorGrpMem.device_id);
				des2src(tOper.oper_no,in_pack->scust_limit2);
				ret = DB_t_door_oper_right_add(&tOper);
				if(ret)
				{
					DB_t_door_group_member_close_select_by_cur1();
					return E_DB_DOOR_OPER_RIGHT_I;
				}
			}
			else
			{
				DB_t_door_group_member_close_select_by_cur1();
				return E_DB_DOOR_OPER_RIGHT_R;
			}
		}
		// ����Ѿ����ھʹ�����һ��
	}
	return 0;
}

int F848018(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	ntrim(in_pack->sall_name,sizeof(in_pack->sall_name));
	switch(in_pack->sstatus0[0])
	{
		case 'A':
			ret=Add848018(handle,iRequest,in_pack,pRetCode,szMsg);
			break;
		default:
			*pRetCode=E_INPUT_DATA_INVAILD;
			goto L_RETU;
	}

	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	return 0;
L_RETU:
	return  -1;
}





