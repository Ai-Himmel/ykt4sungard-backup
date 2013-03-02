/* --------------------------------------------
 * 程序名称: F950040.sqc
 * 创建日期: 2006-7-10
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传设备分组权限
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

int F950040(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_pif_device tDevice;
	T_t_tif_meslist tMsg;
	int retries = 0;
	int msgid;
	char cardgroup[257] = "";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	
	memset(&tDevice,0,sizeof tDevice);
	

	if(rPack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if(strlen(rPack->vsvarstr0) != 254)
	{
		writelog(LOG_DEBUG,"card right [%s] ",rPack->vsvarstr0);
		*pRetCode = E_DEVICE_PARAM_ERR;
	}
	else if((ret = DB_t_pif_device_read_by_device_id(rPack->lcert_code,&tDevice)))
	{
		*pRetCode = ret;

	}
	else if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else
	{
		memset(&tMsg,0,sizeof tMsg);
		cardgroup[0] = '0';
		strcat(cardgroup,rPack->vsvarstr0);
		cardgroup[255] = '0';
		tMsg.funid = 950040;
		//des2src(tMsg.devphy999_id,tDevice.devphy999_id);
		tMsg.devid = tDevice.device_id;
		AddXmlItemStr(tMsg.incontent,XML_KEY_CARDRIGHTTYPE,cardgroup);
		if((ret = AddMsgLst(&tMsg)))
		{
			*pRetCode = ret;
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
