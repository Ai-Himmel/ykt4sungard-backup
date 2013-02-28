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
#include "acctrans.h"

static int do_848256(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_doorholiday holiday;
	T_t_doorholidaytime holidaytime;
	T_t_doortimegrp timegrp;
	int ret;

	memset(&holiday,0,sizeof holiday);
	memset(&holidaytime,0,sizeof holidaytime);
	memset(&timegrp,0,sizeof timegrp);

	int holidayid=in_pack->lvol0;
	int timegrpid=in_pack->lvol1;
	if(!holidayid)
		return E_INPUT_ERROR;
	if(!timegrpid)
	{
		sprintf(szMsg,"����[%s] ��ѡ��ʱ�����",in_pack->sdate0);
		writelog(LOG_ERR,szMsg);
		return E_INPUT_ERROR;
	}
	ret = IsInvalidDateTime(in_pack->sdate0,"YYYYMMDD");
	if(ret)
	{
		sprintf(szMsg,"���ڸ�ʽ����[%s]",in_pack->sdate0);
		writelog(LOG_ERR,szMsg);
		return ret;
	}
	ret = DB_t_doorholiday_read_by_holidayid(holidayid,&holiday);
	if(ret)
	{
			if(DB_NOTFOUND == ret)
			{
				return E_DB_DOORHOLIDAY_N;
			}
			return E_DB_DOORHOLIDAY_R;
	}

	ret = DB_t_doortimegrp_read_by_timegrpid(timegrpid,&timegrp);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DOOR_TIME_GROUP_N;
		return E_DB_DOOR_TIME_GROUP_R;
	}
	
	if(in_pack->sstatus0[0] == '1'
	|| in_pack->sstatus0[0] == '3' )
	{
		ret = DB_t_doorholidaytime_del_by_holidayid(holidayid);
		if(ret)
		{
			if(ret != DB_NOTFOUND)
				return E_DB_DOOR_HOLIDAY_TIME_D;
		}
	}
	holidaytime.holidayid = holidayid;
	des2src(holidaytime.holidaydate,in_pack->sdate0);
	holidaytime.timegrpid = timegrpid;
	holidaytime.adddelflag=ADDDELFLAG_ADD;
	holidaytime.downstatus=DOWNSTATUS_SUCCESS;
	des2src(holidaytime.updatetime,CAccTrans::GetInst().hostdatetime);
	ret = DB_t_doorholidaytime_add(&holidaytime);
	if(ret)
	{
//		if(DB_REPEAT == ret)
//		{
//			// ����
//			ret = DB_t_doorholidaytime_update_by_holidayid_and_holidaydate(
//			in_pack->lvol0,in_pack->sdate0,&holidaytime);
//			if(ret)
//			{
//				writelog(LOG_ERR,"���½ڼ���������Ϣʧ��,holidayid[%d] date[%s]"
//				,in_pack->lvol0,in_pack->sdate0);
//				sprintf(szMsg,"���½ڼ���[%s] ʧ��",in_pack->sdate0);
//				return E_DB_DOOR_HOLIDAY_TIME_U;
//			}
//		}
//		else
//		{
//			sprintf(szMsg,"����ʱ���[%s] ʧ��",in_pack->sdate0);
//			writelog(LOG_ERR,szMsg);
			return E_DB_DOOR_HOLIDAY_TIME_I;
//		}
	}

	if(in_pack->sstatus0[0] == '2'
	||in_pack->sstatus0[0] == '3' )
	{
		// ����ʱ������
		des2src(holiday.updatetime,holidaytime.updatetime);
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
				return E_DB_DOORHOLIDAY_N;
			return E_DB_DOORHOLIDAY_U;
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
		 return  ret;
	}
	return 0;
}

