/* --------------------------------------------
 * 程序名称: F950042.sqc
 * 创建日期: 2008-6-30
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传设备搭伙费(2)
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
	T_t_cif_shop_feerate feerate;
	int rate = 0;
	int retries = 0;
	char cardlist[1024] = "";
	int rows = 0;
	int i,j;
	int device_id,shop_id;
	char sysdate[9],systime[7];
	CBccExtPack bcc_call;
	BCC_EXT_PACK call_pack;

	memset(&tDevice,0,sizeof tDevice);
	memset(&tShopPos,0,sizeof tShopPos);
	memset(sysdate,0,sizeof sysdate);
	memset(systime,0,sizeof systime);
	getsysdate(sysdate);
	getsystime(systime);

	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,F_VSMESS,0);
	
	device_id = in_pack->lvol0;
	ret = get_shpId_by_devId_date_time(&shop_id,device_id,sysdate,systime);
	if(ret)
	{
		if(E_DB_SHOP_POS_N == ret)
		{
			shop_id = 1;
			device_id = 1;
		}
		else
		{
			*pRetCode = ret;
			goto LRet;
		}
	}

	ret = DB_t_cif_shop_feerate_open_select_by_c0_and_shop_id(shop_id);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
		}
		else
			*pRetCode = E_DB_SHOPRATE_R;
		goto LRet;
	}
	while(1)
	{
		memset(&shoprate,0,sizeof &shoprate);
		ret = DB_t_cif_shop_feerate_fetch_select_by_c0(&shoprate);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				break;
			}
			else
			{
				*pRetCode = E_DB_SHOPRATE_R;
				goto LRet;
			}
		}
		sprintf(cardlist+shoprate.feetype*2,"%02X",shoprate.rate); 
	}

	ret = DB_t_pif_device_read_by_device_id(in_pack->lvol0,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_DEVICE_N;
		else
			*pRetCode = E_DB_DEVICE_R;
		goto LRet;

	}
	ret = init_bccextpack(&tDevice,&call_pack);
	if(ret)
	{
		*pRetCode = ret;
		goto LRet;
	}
	
	// 要填写上传的设备ID
	call_pack.lvol0 = in_pack->lvol0;

	PutRow(handle,out_pack,pRetCode,szMsg);
	AnswerData(handle,*pRetCode,szMsg);
	return 0;

LRet:
	return -1;
}

