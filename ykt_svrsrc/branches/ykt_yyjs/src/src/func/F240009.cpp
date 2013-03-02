/* --------------------------------------------
 * 程序名称: F240009.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 判断设备是否签到成功状态
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"



int F240009(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_pif_device t_device;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&t_device,0,sizeof(t_device));
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCARD0,0);

	//writelog(LOG_ERR," device_id=[%s]",rPack->sorder2);
	ret=DB_t_pif_device_read_by_device_id(atoi(rPack->sorder2),&t_device);
	if(ret)
	{
		writelog( LOG_ERR,"DB_t_pif_device_read_by_device_id error,errcode=[%d],device_id=[%d]",ret,t_device.device_id);
		*pRetCode=E_DB_DEVICE_R;
		goto L_RETU;
	}
	//writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",device_id,t_device.state_id);
	if(DEVISTAT_ONLINE!=t_device.state_id)
	{
		writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",t_device.device_id,t_device.state_id);
		*pRetCode=E_DB_DEVI_LOGIN;
		goto L_RETU;
	}
	
	return 0;
L_RETU:
	return -1;
}


