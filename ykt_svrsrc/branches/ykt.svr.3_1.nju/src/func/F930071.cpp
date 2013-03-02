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
#include "dictionary.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"

static int g_flag = 0;
static int g_FrontType=SUBSYSTYPE_XSQ;
static int do_check_buffer(const char *status_buffer,const char *op_time)
{
	int count,i;
	int buf_len;
	int ret;
	int deviceid=0;
	char dev_phyno[31]= "";
	int dev_state = 0;
	T_t_devmonitor dev_monitor;
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
		//鑫三强采用设备ID
		strncpy(dev_phyno,status_buffer+i,8);
		dev_phyno[8] = '\0';
		strncpy(temp,status_buffer+i+8,2);
		dev_state = strtoul(temp,NULL,16);
        if(g_flag == 1)
        {
			ret=GetDevIdByDevPhyId(&deviceid,dev_phyno);
			if(ret)
			{
				writelog(LOG_ERR,"devphyid[%s]",dev_phyno);
				return ret;
			}
        }
        else
        {
    		deviceid=atoi(dev_phyno);
			T_t_device tDevice;
    		memset(&tDevice,0,sizeof tDevice);
    		ret = DB_t_device_read_by_deviceid(deviceid,&tDevice);
    		if(ret)
    		{
    			if(E_NOTEXIST_DEVICE== ret)
    			{
    				writelog(LOG_ERR,"前置机心跳,设备不存在[%s]",dev_phyno);
    				continue;
    			}
    			continue;
    		}
        }
		memset(&dev_monitor,0,sizeof dev_monitor);
		ret = DB_t_devmonitor_read_by_deviceid(deviceid,&dev_monitor);
		des2src(dev_monitor.optime,op_time);
		des2src(dev_monitor.coltime,CAccTrans::getInstance()->trans.sysdatetime);
		des2src(dev_monitor.devtime,op_time);
		dev_monitor.deviceid = deviceid;
		dev_monitor.beatstatus = dev_state;
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				//dev_monitor.is_ws[0] = '1';
				ret = DB_t_devmonitor_add(&dev_monitor);
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
			ret = DB_t_devmonitor_update_by_deviceid(deviceid,&dev_monitor);
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
	T_t_subsystem  subsystem;

	memset(&subsystem,0,sizeof(subsystem));

	ret=DB_t_subsystem_read_by_sysid(in_pack->lcert_code,&subsystem);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_SUBSYSTEM_N;
		else
			return E_DB_SUBSYSTEM_R;
	}
	g_FrontType=subsystem.systype;
	
    // 1 : 表示用设备物理ID 号
    // 0 : 表示用设备ID 号
    g_flag = in_pack->lvol1;

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

