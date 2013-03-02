/* --------------------------------------------
 * 程序名称: F930203.sqc
 * 创建日期: 2007-04-23
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 采集门禁流水与事件
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
#include "dbfunc_foo.h"


int F930203(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_door_txdtl txdtl;
	T_t_pif_card tCard;
	T_t_pif_device device;
	T_t_door_events event;
	int ret;
	memset(&device,0,sizeof device);
	ret = get_door_dev_by_parent_and_termid(&device,in_pack->lvol2,in_pack->lvol1);
	if(ret)
	{
		if(ret == E_DB_DEVICE_N)
			return 0;
		return ret;
	}
	if(strlen(in_pack->sdate1) == 0)
	{
		//事件
		memset(&event,0,sizeof event);
		event.device_id = device.device_id;
		event.event_code = atoi(in_pack->semp_no);
		des2src(event.event_msg,in_pack->vsmess);
		event.sysid = in_pack->lcert_code;
		des2src(event.tx_date,in_pack->sdate0);
		des2src(event.tx_time,in_pack->stime0);
		getsysdate(event.col_date);
		getsystime(event.col_time);
		ret = DB_t_door_events_add(&event);
		if(ret)
		{
			if(DB_REPEAT == ret)
				return 0;
			return E_DB_DOOR_TXDTL_I;
		}
		return 0;
		
	}
	else if(strlen(in_pack->sdate1) !=8)
	{
		// 流水卡号错误
		writelog(LOG_DEBUG,"数据有误");
		return 0;
	}
	else
	{
		ret = get_card_by_phyno(&tCard,in_pack->sdate1);
		if(ret)
		{
			// 没有这张卡
			if(ret != E_DB_CARD_N)
				return ret;
		}
		memset(&txdtl,0,sizeof txdtl);
		txdtl.device_id = device.device_id;
		txdtl.card_no = tCard.card_id;
		txdtl.sys_id = in_pack->lcert_code;
		des2src(txdtl.phycard_no,in_pack->sdate1);
		writelog(LOG_DEBUG,"door serial date[%s] time[%s]",in_pack->sdate0,in_pack->stime0);
		des2src(txdtl.tx_date,in_pack->sdate0);
		des2src(txdtl.tx_time,in_pack->stime0);
		getsysdate(txdtl.col_date);
		getsystime(txdtl.col_time);
		txdtl.tx_mark = atoi(in_pack->semp_no);
		
		ret = DB_t_door_txdtl_add(&txdtl);
		if(ret)
		{
			// 重复流水忽略
			if(DB_REPEAT == ret)
			{
				writelog(LOG_DEBUG,"流水重复card[%s],date[%s],time[%s]",in_pack->sdate1
					,in_pack->sdate0,in_pack->stime0);
				return 0;
			}
			writelog(LOG_ERR,"保存流水失败card[%s],date[%s],time[%s]",in_pack->sdate1
					,in_pack->sdate0,in_pack->stime0);
			return E_DB_DOOR_TXDTL_I;
		}
		return 0;
	}
	
}
