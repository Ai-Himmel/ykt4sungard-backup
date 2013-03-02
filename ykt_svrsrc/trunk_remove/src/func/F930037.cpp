/* --------------------------------------------
 * 程序名称: F930037.sqc
 * 创建日期: Sep 24 2004
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 下传设备档案信息
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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

int F930037(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int    ret=0;
	int    row=0;
	int dev_id=0;
	char devphyid[31]="";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_device 	tDevice;
	T_t_device	tParentDevice;


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SDATE2,F_SDATE1,F_LVOL4,F_SEMP,F_SDATE3,F_SHOLDER_TYPE,F_SNOTE2,F_LVOL1,F_LVOL5,F_STIME0,F_LVOL6,F_LVOL7,F_LVOL8,F_SSTATION0,F_SBANK_CODE,F_LVOL9,F_LVOL10,F_SSERIAL0,F_SSERIAL1,F_LVOL11,F_SCUST_AUTH,F_LVOL12,F_SCUST_AUTH2,F_LVOL0,0);

	writelog(LOG_DEBUG,"前置机%d下载设备档案",rPack->lcert_code);

	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	des2src(devphyid,rPack->sdate1);
	if(strlen(devphyid)&&strncmp(devphyid,"00000000",8)!=0)
	{
		memset(&tDevice,0,sizeof(tDevice));
		ret = GetDevIdByDevPhyId(&dev_id,devphyid);
		if(ret)
		{
			*pRetCode=ret;
			goto L_RETU;
		}
		ret=DB_t_device_read_by_deviceid(dev_id, &tDevice);
		if(ret)
		{
			writelog(LOG_ERR,"devphyid[%s]",devphyid);
			if(DB_NOTFOUND==ret)
				return E_DB_DEVICE_N;
			else
				return E_DB_DEVICE_R;
			goto L_RETU;
		}
		if(tDevice.status[0]!=STATUS_NORMAL)
		{
			return E_DEVICE_LOGOUT;
		}
		if((strncmp(tDevice.devphyid,"FFFFFFFF",8)==0)||(strlen(tDevice.devphyid)==0))
		{
			*pRetCode=E_DB_DEVICE_N;
			goto L_RETU;
		}
		if(ROOT_deviceid == tDevice.fdeviceid)
			memset(out_pack->stime0,0,sizeof(out_pack->stime0));
		else
		{
			out_pack->lvol0 = tDevice.deviceid;
			memset(&tParentDevice,0,sizeof tParentDevice);
			ret = DB_t_device_read_by_deviceid(tDevice.fdeviceid,&tParentDevice);
			if(ret)
			{
				des2src(out_pack->stime0,"FFFFFFFF");
			}
			else
			{
				des2src(out_pack->stime0,tParentDevice.devphyid);
			}
		}
		des2src(out_pack->sdate2,tDevice.devphyid);
		des2src(out_pack->sdate1,tDevice.devphyid);
		out_pack->lvol4=tDevice.deviceno;
		des2src(out_pack->semp,tDevice.devtypecode);
		des2src(out_pack->sdate3,tDevice.devverno);
		des2src(out_pack->sholder_type,tDevice.cardset);
		des2src(out_pack->snote2,tDevice.cardphytype);
		out_pack->lvol5=tDevice.svrportcnt;
		out_pack->lvol6=tDevice.svrportno;
		out_pack->lvol7=1;
		out_pack->lvol8=tDevice.commtype;
		des2src(out_pack->sstation0,tDevice.ip);
		sprintf(out_pack->sbank_code,"%d",tDevice.portno);
		out_pack->lvol9=tDevice.baudrate;
//		out_pack->lvol10=tDevice.comtype;
		des2src(out_pack->sserial0,"991231235959");
		des2src(out_pack->sserial1,tDevice.cardverno);
		out_pack->lvol11=tDevice.lastseqno;
		des2src(out_pack->scust_auth,tDevice.lasttranstime);
//		out_pack->lvol12=tDevice.last;
//		des2src(out_pack->scust_auth2,tDevice.lastshutdate);
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}

	ret=DB_t_device_open_select_by_c1_and_sysid(rPack->lcert_code);
	if(ret)
	{
			writelog(LOG_ERR,"sub_system_id[%d]",rPack->lcert_code);
			return E_DB_CURSOR_DECLARE;
	}
	while(1)
	{

		memset(&tDevice,0,sizeof(tDevice));
		ret=DB_t_device_fetch_select_by_c1(&tDevice);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(row)
					break;
				else
					*pRetCode=E_DB_DEVICE_N;
			}
			else
				*pRetCode=E_DB_DEVICE_R;
			goto L_RETU;
		}
		if(tDevice.status[0]!=STATUS_NORMAL|| PHYTYPE_999_DEV != tDevice.devphytype)
			continue;
		if((strncmp(tDevice.devphyid,"FFFFFFFF",8)==0)||(strlen(tDevice.devphyid)==0))
			continue;
		if(ROOT_deviceid == tDevice.fdeviceid)
		{
			memset(out_pack->stime0,0,sizeof(out_pack->stime0));
			out_pack->lvol1 = -1;
		}
		else
		{
			out_pack->lvol1 = tDevice.fdeviceid;
			memset(&tParentDevice,0,sizeof tParentDevice);
			ret = DB_t_device_read_by_deviceid(tDevice.fdeviceid,&tParentDevice);
			if(ret)
			{
				des2src(out_pack->stime0,"FFFFFFFF");
			}
			else
			{
				des2src(out_pack->stime0,tParentDevice.devphyid);
			}
		}
		out_pack->lvol0 = tDevice.deviceid;
		out_pack->lvol7=1;
		des2src(out_pack->sdate2,tDevice.devphyid);
		des2src(out_pack->sdate1,tDevice.devphyid);
		out_pack->lvol4=tDevice.deviceno;
		des2src(out_pack->semp,tDevice.devtypecode);
		des2src(out_pack->sdate3,tDevice.devverno);
		des2src(out_pack->sholder_type,tDevice.cardset);
		des2src(out_pack->snote2,tDevice.cardphytype);
		out_pack->lvol5=tDevice.svrportcnt;
		out_pack->lvol6=tDevice.svrportno;
		out_pack->lvol8=tDevice.commtype;
		des2src(out_pack->sstation0,tDevice.ip);
		sprintf(out_pack->sbank_code,"%d",tDevice.portno);
		out_pack->lvol9=tDevice.baudrate;
//		out_pack->lvol10=tDevice.comtype;
		des2src(out_pack->sserial0,"991231235959");
		des2src(out_pack->sserial1,tDevice.cardverno);
		out_pack->lvol11=tDevice.lastseqno;
		des2src(out_pack->scust_auth,tDevice.lasttranstime);
//		out_pack->lvol12=tDevice.lastshutserno;
//		des2src(out_pack->scust_auth2,tDevice.lastshutdate,sizeof(out_pack->scust_auth2)-1);
		row++;
		PutRow(handle,out_pack,pRetCode,szMsg);
		if(row%10==0)
			AnswerDataPart(handle,*pRetCode,szMsg);
	}
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
