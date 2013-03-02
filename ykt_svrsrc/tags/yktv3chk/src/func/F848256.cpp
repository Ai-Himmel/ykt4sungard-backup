/* --------------------------------------------
 * ��������: F848256.c
 * ��������: 2007-04-03
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:�Ž��ڼ��չ���
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
#include "busqc.h"
#include "dbfunc_foo.h"

static int do_848256(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_doorholiday holiday;
	T_t_doorholidaytime times;
	T_t_doortimesectgrp tgroup;
	int ret;

	memset(&holiday,0,sizeof holiday);
	memset(&times,0,sizeof times);
	memset(&tgroup,0,sizeof tgroup);

	if(unlike_tbl_id(in_pack->lvol0))
		return E_INPUT_ERROR;

	ret = IsInvalidDateTime(in_pack->sdate0,"YYYYMMDD");
	if(ret)
	{
		sprintf(szMsg,"���ڸ�ʽ����[%s]",in_pack->sdate0);
		writelog(LOG_ERR,szMsg);
		return ret;
	}

	if(unlike_tbl_id(in_pack->lvol1))
	{
		sprintf(szMsg,"����[%s] ��ѡ��ʱ�����",in_pack->sdate0);
		writelog(LOG_ERR,szMsg);
		return E_INPUT_ERROR;
	}
	
	ret = DB_t_doorholiday_read_by_holidayid(in_pack->lvol0,&holiday);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			return E_DB_DOOR_HOLIDAY_N;
		}
		return E_DB_DOOR_HOLIDAY_R;
	}

	ret = DB_t_doortimesectgrp_read_by_timesectgrpid(in_pack->lvol1,&tgroup);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DOOR_TIME_GROUP_N;
		return E_DB_DOOR_TIME_GROUP_R;
	}
	
	if(in_pack->sstatus0[0] == '1'
	|| in_pack->sstatus0[0] == '3' )
	{
		ret = DB_t_doorholidaytime_del_by_holidayid(in_pack->lvol0);
		if(ret)
		{
			if(ret != DB_NOTFOUND)
				return E_DB_DOOR_HOLIDAY_TIME_D;
		}
	}
	times.holidayid = in_pack->lvol0;
	des2src(times.holidaydate,in_pack->sdate0);
	times.timegrpid = in_pack->lvol1;
	times.flag = DOOR_FLAG_NORMAL;
	getsysdatetime(times.lastsaved);

	ret = DB_t_doorholidaytime_add(&times);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			// ����
			ret = DB_t_doorholidaytime_update_by_holidayid_and_holidaydate(
			in_pack->lvol0,in_pack->sdate0,&times);
			if(ret)
			{
				writelog(LOG_ERR,"���½ڼ���������Ϣʧ��,holidayid[%d] date[%s]"
				,in_pack->lvol0,in_pack->sdate0);
				sprintf(szMsg,"���½ڼ���[%s] ʧ��",in_pack->sdate0);
				return E_DB_DOOR_HOLIDAY_TIME_U;
			}
		}
		else
		{
			sprintf(szMsg,"����ʱ���[%s] ʧ��",in_pack->sdate0);
			writelog(LOG_ERR,szMsg);
			return E_DB_DOOR_HOLIDAY_TIME_I;
		}
	}

	if(in_pack->sstatus0[0] == '2'
	||in_pack->sstatus0[0] == '3' )
	{
		// ����ʱ������
		des2src(holiday.lastsaved,times.lastsaved);
		ret = count_times_of_holiday(holiday.holidayid,&(holiday.daycnt));
		if(ret)
		{
			sprintf(szMsg,"ͳ�ƽڼ���[%s] ʱ�δ���",holiday.holidayname);
			writelog(LOG_ERR,szMsg);
			return ret;
		}
		ret = DB_t_doorholiday_update_by_holidayid(holiday.holidayid,&holiday);
		if(ret)
		{
			
			sprintf(szMsg,"��ɽڼ�������,����ʱ���ʧ��,[%s]",holiday.holidayname);
			writelog(LOG_ERR,szMsg);
			if(DB_NOTFOUND == ret)
				return E_DB_DOOR_HOLIDAY_N;
			return E_DB_DOOR_HOLIDAY_U;
		}
	}
	return 0;
}

int F848256(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_848256(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	return 0;
}

