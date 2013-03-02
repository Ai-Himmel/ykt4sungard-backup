/* --------------------------------------------
 * 程序名称: F950041.sqc
 * 创建日期: 2006-7-10
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传设备搭伙费
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

#define BIT_LENGTH (sizeof(unsigned char) * 8)

#define _SET_BIT(tSet,x)  do { \
	tSet[ (x) / BIT_LENGTH ] |= (1 << (BIT_LENGTH - 1 - (x) % BIT_LENGTH)); \
	 } while(0)
	

int F930006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F950041(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_pif_device tDevice;
	T_t_cif_shop_pos tShopPos;
	T_t_cif_shop tShop;
	T_t_tif_meslist tMsg;
	T_t_pif_feetype tFeeType;
	int rate = 0;
	int retries = 0;
	int msgid;
	unsigned char buf[32] = "";
	char cardlist[100] = "";
	int rows = 0;
	int i,j;

	memset(&tDevice,0,sizeof tDevice);
	memset(&tFeeType,0,sizeof tFeeType);
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,F_VSMESS,0);
	
	if(rPack->lcert_code < 1)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	else if((ret = DB_t_pif_device_read_by_device_id(rPack->lcert_code,&tDevice)))
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_DEVICE_N;
		else
			*pRetCode = E_DB_DEVICE_R;

	}
	else if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		*pRetCode = E_DEVICE_NOT_EXIST;
	}
	// 如果是 39 的充值机
	else if(strcmp(tDevice.devtype,"0201") == 0 && tDevice.phytype == 1000)
	{
		des2src(rPack->sdate0,tDevice.devphy999_id);
		ret = F930006(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)	
		{
			goto LRet;
		}
		return 0;
	}
	else if((ret = DB_t_cif_shop_pos_open_select_by_c0_and_device_id(rPack->lcert_code)))
	{
		*pRetCode = E_DB_SHOP_POS_R;
	}
	else
	{
		
		while(1)
		{
			memset(&tShopPos,0,sizeof tShopPos);
			memset(&tShop,0,sizeof tShop);
			if((ret = DB_t_cif_shop_pos_fetch_select_by_c0(&tShopPos)))
			{
				if(ret == DB_NOTFOUND)
				{
					writelog(LOG_DEBUG,"shop doesn't find [%d]!");
					*pRetCode  = 0;
				}
				else
					*pRetCode = E_DB_SHOP_POS_R;
				break;
			}
			writelog(LOG_DEBUG,"find shop [%d]",tShopPos.shop_id);
			if((ret = DB_t_cif_shop_read_by_shop_id(tShopPos.shop_id,&tShop)))
			{
				*pRetCode = ret;
				break;
			}
			if('1' == tShop.is_leaf[0] && '1' == tShop.is_getfee[0]
				&& amtcmp(tShop.ratio,0.00)>0 )
			{
				writelog(LOG_DEBUG,"shop rate [%.02f]",tShop.ratio);
				int newrate = D2I(tShop.ratio * 100);
				if(newrate > rate)
					rate = newrate;
			}
		}
		
	}
	if(*pRetCode)
		return -1;
	
	ret = DB_t_pif_feetype_open_select_by_cur1();
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_FEETYPE_N;
		else
			*pRetCode = E_DB_FEETYPE_R;
		return -1;
	}
	memset(buf,0,sizeof buf);
	while(1)
	{
		memset(&tFeeType,0,sizeof &tFeeType);
		ret = DB_t_pif_feetype_fetch_select_by_cur1(&tFeeType);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				*pRetCode = E_DB_FEETYPE_N;
			}
			else
				*pRetCode = E_DB_FEETYPE_R;
		}
		rows++;
		if(tFeeType.fee_type < 0 || tFeeType.fee_type > 255
			|| tFeeType.is_outfee[0] != '1' )
			continue;
		writelog(LOG_DEBUG,"fee[%s][%d][%c]",tFeeType.fee_name,tFeeType.fee_type
			,tFeeType.is_outfee[0]);
		_SET_BIT(buf,tFeeType.fee_type-1);
		
	}
	//writelog(LOG_DEBUG,"bit length %d",BIT_LENGTH);
	memset(&tMsg,0,sizeof tMsg);
	tMsg.funid = 950041;
	tMsg.level = 1;
	tMsg.devid = tDevice.device_id;
	for(i = 0,j = 0;i < sizeof buf;++i)
	{
		j += sprintf(cardlist+j,"%02x",buf[i]);
	}
	AddXmlItemInt(tMsg.incontent,XML_KEY_FEE,rate);
	AddXmlItemStr(tMsg.incontent,XML_KEY_CARDRIGHTTYPE,cardlist);
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
		retries = 10;
		msgid = tMsg.mesid;
		for(retries=0;(retries<10)&&(tMsg.ecode!=0);retries++)
		{
			memset(&tMsg,0,sizeof tMsg);
			ret = DB_t_tif_meslist_read_by_mesid(msgid,&tMsg);
			if(ret)
			{
				strcpy(out_pack->vsvarstr0,"读取指令失败");
				*pRetCode=E_DB_MESLIST_R;
				strcpy(szMsg,"读取指令失败");
				return -1;
			}
			// 等待1秒
			sleep(1);
		}
		switch(tMsg.ecode)
		{
			case 0:		//成功
				des2src(out_pack->vsmess,"成功");
				strcpy(szMsg,"成功");
				break;
			case 9999:		//交易未处理
				des2src(out_pack->vsmess,"前置机无应答");
				strcpy(szMsg,"前置机无应答");
				goto LRet;
			default:			//交易已经处理,但结果是失败
				des2src(out_pack->vsmess,tMsg.emsg);				
				goto LRet;
		}	

		PutRow(handle,out_pack,pRetCode,szMsg);
		AnswerData(handle,*pRetCode,szMsg);
		return 0;
		
	}
LRet:
	return -1;
}

