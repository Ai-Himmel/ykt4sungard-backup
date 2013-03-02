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
#include "fdsqc.h"

int F930037(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int    ret=0;
	int    row=0;
	int dev_id=0;
	char devphy999_id[9]="";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_pif_device 	p;

#ifdef DEBUG
	writelog(LOG_DEBUG,"subsystem_id[%d]",rPack->lcert_code);
	writelog(LOG_DEBUG,"dyn_key[%s]",rPack->scust_limit2);
#endif

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SDATE2,F_SDATE1,F_LVOL4,F_SEMP,F_SDATE3,F_SHOLDER_TYPE,F_SNOTE2,F_LVOL5,F_STIME0,F_LVOL6,F_LVOL7,F_LVOL8,F_SSTATION0,F_SBANK_CODE,F_LVOL9,F_LVOL10,F_SSERIAL0,F_SSERIAL1,F_LVOL11,F_SCUST_AUTH,F_LVOL12,F_SCUST_AUTH2,F_LVOL0,0);

	writelog(LOG_DEBUG,"前置机%d下载设备档案",rPack->lcert_code);

	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	strncpy(devphy999_id,rPack->sdate1,sizeof(devphy999_id)-1);
	trim(devphy999_id);
	if(strlen(devphy999_id)&&strncmp(devphy999_id,"00000000",8)!=0)
	{
		memset(&p,0,sizeof(p));
		ret = GetDevIdByDevPhyId(&dev_id,devphy999_id);
		if(ret)
		{
			*pRetCode=ret;
			goto L_RETU;
		}
		ret=DB_t_pif_device_read_by_devphy999_id(devphy999_id, &p);
		if(ret)
		{
			writelog(LOG_ERR,"devphy999_id[%s]",devphy999_id);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_DB_DEVICE_N;
			else
				*pRetCode=E_DB_DEVICE_R;
			goto L_RETU;
		}
		if(p.state_id==DEVISTAT_LOGOUT)
		{
			*pRetCode=E_DB_DEVICE_N;
			goto L_RETU;
		}
		p.state_id=DEVISTAT_REGIST;
		if((strncmp(p.dev999_id,"FFFFFFFF",8)==0)||(strlen(p.dev999_id)==0))
		{
			*pRetCode=E_DB_DEVICE_N;
			goto L_RETU;
		}
		if(strncmp(p.fdevphy_id,"FFFFFFFF",8)==0)
			memset(out_pack->stime0,0,sizeof(out_pack->stime0));
		else
			strncpy(out_pack->stime0,p.fdevphy_id,sizeof(out_pack->stime0)-1);
		strncpy(out_pack->sdate2,p.dev999_id,sizeof(out_pack->sdate2)-1);
		strncpy(out_pack->sdate1,p.devphy999_id,sizeof(out_pack->sdate1)-1);
		out_pack->lvol4=p.dev999_no;
		strncpy(out_pack->semp,p.devtype,sizeof(out_pack->semp)-1);
		strncpy(out_pack->sdate3,p.devversion,sizeof(out_pack->sdate3)-1);
		strncpy(out_pack->sholder_type,p.cardstr,sizeof(out_pack->sholder_type)-1);
		strncpy(out_pack->snote2,p.cardtype,sizeof(out_pack->snote2)-1);
		out_pack->lvol5=p.portcount;

		out_pack->lvol6=p.portno;
		out_pack->lvol7=p.state_id;
		out_pack->lvol8=p.joinmode;
		strncpy(out_pack->sstation0,p.comadd,sizeof(out_pack->sstation0)-1);
		strncpy(out_pack->sbank_code,p.port,sizeof(out_pack->sbank_code)-1);
		out_pack->lvol9=p.baudrate;
		out_pack->lvol10=p.comtype;
		strncpy(out_pack->sserial0,p.bsheetvdate,sizeof(out_pack->sserial0)-1);
		strncpy(out_pack->sserial1,p.bsheetver,sizeof(out_pack->sserial1)-1);
		out_pack->lvol11=p.lasttraserno;
		strncpy(out_pack->scust_auth,p.lasttradate,sizeof(out_pack->scust_auth)-1);
		out_pack->lvol12=p.lastshutserno;
		strncpy(out_pack->scust_auth2,p.lastshutdate,sizeof(out_pack->scust_auth2)-1);
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}

	ret=DB_t_pif_device_open_select_by_c1_and_subsystem_id(rPack->lcert_code);
	if(ret)
	{
			writelog(LOG_ERR,"sub_system_id[%d]",rPack->lcert_code);
			*pRetCode=E_DB_DEVICE_R;
			goto L_RETU;
	}
	while(1)
	{

		memset(&p,0,sizeof(p));
		ret=DB_t_pif_device_fetch_select_by_c1(&p);
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
		if(p.state_id==DEVISTAT_LOGOUT)
			continue;
		p.state_id=DEVISTAT_REGIST;
		if((strncmp(p.dev999_id,"FFFFFFFF",8)==0)||(strlen(p.dev999_id)==0))
			continue;
		if(strncmp(p.fdevphy_id,"FFFFFFFF",8)==0)
			memset(out_pack->stime0,0,sizeof(out_pack->stime0));
		else
			strncpy(out_pack->stime0,p.fdevphy_id,sizeof(out_pack->stime0)-1);
		out_pack->lvol0 = p.device_id;
		out_pack->lvol7=p.state_id;
		strncpy(out_pack->sdate2,p.dev999_id,sizeof(out_pack->sdate2)-1);
		strncpy(out_pack->sdate1,p.devphy999_id,sizeof(out_pack->sdate1)-1);
		out_pack->lvol4=p.dev999_no;
		strncpy(out_pack->semp,p.devtype,sizeof(out_pack->semp)-1);
		strncpy(out_pack->sdate3,p.devversion,sizeof(out_pack->sdate3)-1);
		strncpy(out_pack->sholder_type,p.cardstr,sizeof(out_pack->sholder_type)-1);
		strncpy(out_pack->snote2,p.cardtype,sizeof(out_pack->snote2)-1);
		out_pack->lvol5=p.portcount;
		out_pack->lvol6=p.portno;
		out_pack->lvol8=p.joinmode;
		strncpy(out_pack->sstation0,p.comadd,sizeof(out_pack->sstation0)-1);
		strncpy(out_pack->sbank_code,p.port,sizeof(out_pack->sbank_code)-1);
		out_pack->lvol9=p.baudrate;
		out_pack->lvol10=p.comtype;
		strncpy(out_pack->sserial0,p.bsheetvdate,sizeof(out_pack->sserial0)-1);
		strncpy(out_pack->sserial1,p.bsheetver,sizeof(out_pack->sserial1)-1);
		out_pack->lvol11=p.lasttraserno;
		strncpy(out_pack->scust_auth,p.lasttradate,sizeof(out_pack->scust_auth)-1);
		out_pack->lvol12=p.lastshutserno;
		strncpy(out_pack->scust_auth2,p.lastshutdate,sizeof(out_pack->scust_auth2)-1);
		row++;
		PutRow(handle,out_pack,pRetCode,szMsg);
		if(row%15==0)
			AnswerDataPart(handle,*pRetCode,szMsg);
	}
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
