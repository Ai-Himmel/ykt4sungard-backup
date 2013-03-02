/* --------------------------------------------
 * 程序名称: F848012.c
 * 创建日期: 2005-09-23
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:门禁组节假日管理
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

int F930109(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

static int Add848012(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int rows = 0;
	T_t_door_group_member tDoorGrpMem;
	T_t_door_holiday tHoliday;
	T_t_door_oper_right tOper;
	ST_PACK send_pack;
	int holiday_count = 0;
	char holiday[241] = "";
	int subsysid;
	if(in_pack->lvol0 < 1 )
	{
		return E_INPUT_GROUP_ID;
	}
	if(in_pack->lvol1 < 1)
	{
		return E_INPUT_DOOR_HOLIDAY_ID;
	}
	if(strlen(in_pack->scust_limit) < 1)
	{
		return E_INPUT_DATA_INVAILD;
	}
	//writelog(LOG_DEBUG,"lvol0				: [%d]",in_pack->lvol0);
	//writelog(LOG_DEBUG,"lvol1				: [%d]",in_pack->lvol1);
	
	memset(&tHoliday,0,sizeof tHoliday);
	ret = DB_t_door_holiday_read_by_holiday_id(in_pack->lvol1,&tHoliday);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			return E_DB_DOOR_HOLIDAY_N;
		}
		return E_DB_DOOR_HOLIDAY_R;
	}
	
	ret = DB_t_door_group_member_open_select_by_cur1_and_group_id(in_pack->lvol0);
	if(ret)
	{
		return E_DB_DOOR_GROUP_MEMBER_R;
	}
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
		ret = get_subsysid_by_phyid(tDoorGrpMem.device_id,&subsysid);
		if(ret)
		{
			// 设备不存在，继续下一个设备
			continue;
		}
		rows++;
		memset(&tOper,0,sizeof tOper);
		ret = DB_t_door_oper_right_read_by_oper_no_and_device_id(
			in_pack->scust_limit,tDoorGrpMem.device_id,&tOper);
		if(ret )
		{
			DB_t_door_group_member_close_select_by_cur1();
			// 只对该操作员有权限的设备处理
			if(DB_NOTFOUND == ret)
			{
				sprintf(szMsg,"操作员对设备%s没有操作权限",tDoorGrpMem.device_id);
				return E_OPER_NO_RIGHT_FOR_DEVICE;
			}
			return E_DB_DOOR_OPER_RIGHT_R;
		}
		memset(holiday,0,sizeof holiday);
		holiday_count = 0;
		ret = AddDoorDevHld(tDoorGrpMem.device_id,in_pack->lvol1,holiday,&holiday_count);
		if(ret)
		{
			// 一个门禁已经设置了该节假日就跳过
			if(E_DB_DOOR_DEV_HLD_E == ret)
			{
				continue;
			}
			DB_t_door_group_member_close_select_by_cur1();
			return ret;
		}
		memset(&send_pack,0,sizeof send_pack);
		send_pack.lvol1 = 930109;
		des2src(send_pack.sdate0,tDoorGrpMem.device_id);
		send_pack.lvol5 = holiday_count;
		des2src(send_pack.vsvarstr0,holiday); 
		ret = F930109(handle,iRequest,&send_pack,pRetCode,szMsg);
		if(ret)
		{
			DB_t_door_group_member_close_select_by_cur1();
			return *pRetCode;
		}
	}
	return 0;
}

int F848012(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	ntrim(in_pack->sall_name,sizeof(in_pack->sall_name));
	switch(in_pack->sstatus0[0])
	{
		case 'A':
			ret=Add848012(handle,iRequest,in_pack,pRetCode,szMsg);
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





