/* --------------------------------------------
 * 程序名称: F950042.cpp
 * 创建日期: 2007-8-10
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能:  下传设备的刷卡时段餐次
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"

	
int F950042(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_pif_device tDevice;
	T_t_tif_meslist tMsg;
	int retries = 0;
	int msgid;
	char cardgroup[257] = "";
	char temp[8]="";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	int cnt=0;
	T_t_pif_meal_type t_meal;
	memset(&t_meal,0,sizeof(t_meal));
	char *pch;
	int i=0;
		writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	
	memset(&tDevice,0,sizeof tDevice);
	

	if(rPack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
		writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
	}
	/*
	else if(strlen(rPack->vsvarstr0) != 254)
	{
		writelog(LOG_DEBUG,"card right [%s] ",rPack->vsvarstr0);
		*pRetCode = E_DEVICE_PARAM_ERR;
	}
	*/
	else if((ret = DB_t_pif_device_read_by_device_id(rPack->lcert_code,&tDevice)))
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
	}
	else if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
		writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
	}
	else
	{
				writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
		memset(&tMsg,0,sizeof tMsg);
		pch = strtok (rPack->vsvarstr0," ");
		while (pch != NULL)
		{
			i = atoi(pch);
			memset(&t_meal,0,sizeof t_meal);
			ret=DB_t_pif_meal_type_read_by_meal_id(i,&t_meal);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_pif_meal_type_read_by_meal_id ERR, [%d] ",ret);
				*pRetCode = E_DEVICE_PARAM_ERR;
			}
			memcpy(temp,t_meal.begin_time,4);
			strcat(cardgroup,temp);
			memcpy(temp,t_meal.end_time,4);
			strcat(cardgroup,temp);
			pch = strtok (NULL, " ");
		}
		//strcat(cardgroup,rPack->vsvarstr0);
		tMsg.funid = 950042;
		//des2src(tMsg.devphy999_id,tDevice.devphy999_id);
		tMsg.devid = tDevice.device_id;
		AddXmlItemStr(tMsg.incontent,XML_KEY_CONCODE,cardgroup);
		if((ret = AddMsgLst(&tMsg)))
		{
			*pRetCode = ret;
			return -1;
		}
		else
		{
			if(db_commit())
			{
				*pRetCode = E_DB_COMMIT;
				return -1;
			}
			msgid = tMsg.mesid;
			retries = 3;
			sleep(2);
			while(retries-- > 0)
			{
				memset(&tMsg,0,sizeof tMsg);
				ret = DB_t_tif_meslist_read_by_mesid(msgid,&tMsg);
				if(!ret)
				{
					if(0 == tMsg.ecode)
					{
						des2src(out_pack->vsvarstr0,tMsg.emsg);
						ret = 0;
						break;
					}
					else if(9999 == tMsg.ecode)
					{
						des2src(out_pack->vsvarstr0,"前置机无应答");
					}
					else
					{
						des2src(out_pack->vsvarstr0,tMsg.emsg);
					}
				}
				else
				{
					strcpy(out_pack->vsvarstr0,"读取指令失败");
				}
				sleep(1);
			}
			*pRetCode = 0;
			PutRow(handle,out_pack,pRetCode,szMsg);
		}
	}
	if(*pRetCode == 0 )
	{
		AnswerData(handle,*pRetCode,szMsg);
		return 0;
	}
	return -1;
}


