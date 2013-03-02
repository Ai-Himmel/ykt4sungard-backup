/* --------------------------------------------
 * 程序名称: F950041.sqc
 * 创建日期: 2006-7-10
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传设备搭伙费比率
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

int F950041(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_pif_device tDevice;
	T_t_cif_shop_pos tShopPos;
	T_t_cif_shop tShop;
	T_t_tif_meslist tMsg;
	int rate = 0;
	int retries = 0;
	int msgid;

	memset(&tDevice,0,sizeof tDevice);
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	
	if(rPack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if((ret = DB_t_pif_device_read_by_device_id(rPack->lcert_code,&tDevice)))
	{
		*pRetCode = ret;

	}
	else if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if((ret = DB_t_cif_shop_pos_open_select_by_c0_and_device_id(rPack->lcert_code)))
	{
		*pRetCode = ret;
	}
	else
	{
		while(1)
		{
			memset(&tShopPos,0,sizeof tShopPos);
			memset(&tShop,0,sizeof tShop);
			if((ret = DB_t_cif_shop_pos_fetch_select_by_c0(&tShopPos)))
			{
				*pRetCode = ret;
				if(ret == DB_NOTFOUND)
					*pRetCode  = 0;
				break;
			}
			if((ret = DB_t_cif_shop_read_by_shop_id(tShopPos.shop_id,&tShop)))
			{
				*pRetCode = ret;
				break;
			}
			if('1' == tShop.is_leaf[0] && '1' == tShop.is_getfee[0]
				&& amtcmp(tShop.ratio,0.00)>0 )
			{
				int newrate = D2I(tShop.ratio * 100);
				writelog(LOG_DEBUG,"搭伙费比率[%d]",newrate);
				if(newrate > rate)
					rate = newrate;
			}
		}
		
	}
	if(*pRetCode)
		return -1;
	memset(&tMsg,0,sizeof tMsg);
	tMsg.funid = 950041;
	//des2src(tMsg.devphy999_id,tDevice.devphy999_id);
	tMsg.devid = tDevice.device_id;
	tMsg.level = 2;
	AddXmlItemInt(tMsg.incontent,XML_KEY_FEE,rate);
	tMsg.max_send_cnt = 5;
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
		retries = 3;
		msgid = tMsg.mesid;
		while(retries-- > 0)
		{
			memset(&tMsg,0,sizeof tMsg);
			ret = DB_t_tif_meslist_read_by_mesid(msgid,&tMsg);
			des2src(out_pack->vsvarstr0,tMsg.emsg);
			if(!ret && !tMsg.ecode)
			{
				break;
			}
			// 等待1秒
			sleep(1);
		}
		PutRow(handle,out_pack,pRetCode,szMsg);
		AnswerData(handle,*pRetCode,szMsg);
		return 0;
		
	}
	return -1;
}

