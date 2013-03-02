/* --------------------------------------------
 * 程序名称: F848012.c
 * 创建日期: 2005-10-20
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:门禁组权限设置
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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
		// 如果已经存在就处理下一个
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





