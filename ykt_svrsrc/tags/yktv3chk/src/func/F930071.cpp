/* ----------------------------------------------------------
 * 程序名称：F930071.cpp
 * 创建日期：2007-8-16
 * 程序作者：
 * 版本信息：1.0.0.0
 * 程序功能：设备应答
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
#include "busqc.h"


static int do_check_buffer(const char *status_buffer,const char *op_time)
{
	int count,i;
	int buf_len;
	int ret;
	char dev_phyno[9]= "";
	int dev_state = 0;
	T_t_device tDevice;
	T_t_mif_devmonitor dev_monitor;
	char temp[3] = "";
	static const int sect_len = 10;
	//writelog(LOG_DEBUG,"status buffer [%s]",status_buffer);
	buf_len = strlen(status_buffer);
	if(buf_len <= 0)
	{
		return 0;
	}
	for(i = 0;i < buf_len;i+=sect_len)
	{
		strncpy(dev_phyno,status_buffer+i,8);
		dev_phyno[8] = '\0';
		strncpy(temp,status_buffer+i+8,2);
		dev_state = strtoul(temp,NULL,16);
		memset(&tDevice,0,sizeof tDevice);
		ret = get_devinfo_by_phyid(dev_phyno,&tDevice);
		if(ret)
		{
			if(E_DEVICE_NOT_EXIST== ret)
			{
				writelog(LOG_ERR,"前置机心跳,设备不存在[%s]",dev_phyno);
				continue;
			}
			continue;
		}
		memset(&dev_monitor,0,sizeof dev_monitor);
		ret = DB_t_mif_devmonitor_read_by_deviceid(tDevice.deviceid,&dev_monitor);
		des2src(dev_monitor.op_time,op_time);
		getsysdatetime(dev_monitor.collect_time);
		des2src(dev_monitor.devtime,op_time);
		dev_monitor.deviceid = tDevice.deviceid;
		dev_monitor.beatstate = dev_state;
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				dev_monitor.is_ws[0] = '1';
				ret = DB_t_mif_devmonitor_add(&dev_monitor);
				if(ret)
				{
					writelog(LOG_ERR,"增加设备监控记录失败!dev[%d] phyno[%s]"
					,dev_monitor.deviceid,dev_phyno);
					return -1;
				}
				continue;
			}
			return -1;
		}
		else
		{
			ret = DB_t_mif_devmonitor_update_by_deviceid(tDevice.deviceid,&dev_monitor);
			if(ret)
			{
				writelog(LOG_ERR,"更新设备监控记录失败!");
				if(DB_NOTFOUND == ret)
					continue;
				return -1;
			}
		}
	}
	if(buf_len < 250)
	{
		return 0;
	}
	return 1;
}

int F930071(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	writelog(LOG_DEBUG,"前置机密钥sysid[%d][%s]",in_pack->lcert_code,in_pack->scust_limit2);
	ret=chk_dyn_key(in_pack->lcert_code,in_pack->scust_limit2);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	writelog(LOG_DEBUG,"前置机时钟sysid[%d][%s]",in_pack->lcert_code,in_pack->sphone3);	
	ret = do_check_buffer(in_pack->vsmess,in_pack->sphone3);
	if(ret < 0)
	{
		*pRetCode = E_DB_DEVMONITOR_U;
		goto L_RETU;
	}
	else if(ret == 0)
	{
		return 0;
	}
	ret = do_check_buffer(in_pack->vsvarstr0,in_pack->sphone3);
	if(ret < 0)
	{
		*pRetCode = E_DB_DEVMONITOR_U;
		goto L_RETU;
	}
	else if(ret == 0)
	{
		return 0;
	}
	ret = do_check_buffer(in_pack->vsvarstr1,in_pack->sphone3);
	if(ret < 0)
	{
		*pRetCode = E_DB_DEVMONITOR_U;
		goto L_RETU;
	}
	else if(ret == 0)
	{
		return 0;
	}
	ret = do_check_buffer(in_pack->vsvarstr2,in_pack->sphone3);
	if(ret < 0)
	{
		*pRetCode = E_DB_DEVMONITOR_U;
		goto L_RETU;
	}
	else if(ret == 0)
	{
		return 0;
	}
	ret = do_check_buffer(in_pack->vsvarstr3,in_pack->sphone3);
	if(ret < 0)
	{
		*pRetCode = E_DB_DEVMONITOR_U;
		goto L_RETU;
	}
	else if(ret == 0)
	{
		return 0;
	}
	return 0;
L_RETU:
	return  -1;

}

