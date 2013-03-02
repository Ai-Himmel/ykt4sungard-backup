/* --------------------------------------------
 * 程序名称: F950043.sqc
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

int F950043(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret,shop_id,rows;
	T_t_pif_device tDevice;
	T_t_cif_shop_feerate shoprate;
	char sysdate[9];
	char systime[7];
	ST_CPACK aPack;
	ST_PACK *out_pack;
	out_pack = &(aPack.pack);


	memset(&tDevice,0,sizeof tDevice);
	memset(sysdate,0,sizeof sysdate);
	memset(systime,0,sizeof systime);

	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_LVOL2,0);

	ret = DB_t_pif_device_read_by_device_id(in_pack->lvol0,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_DEVICE_N;
		else
			*pRetCode = E_DB_DEVICE_R;
		goto L_RETU;
	}

	getsysdate(sysdate);
	getsystime(systime);
	writelog(LOG_DEBUG,"device[%d],date[%s]time[%s]",in_pack->lvol0,sysdate,systime);
	ret = get_shpId_by_devId_date_time(&shop_id,in_pack->lvol0,sysdate,systime,0);
	if(ret)
	{
		if(E_DB_SHOP_POS_N == ret)
			*pRetCode = E_DB_SHOP_POS_N;
		else
			*pRetCode = ret;
		goto L_RETU;
	}

	ret = DB_t_cif_shop_feerate_open_select_by_c0_and_shop_id(shop_id);
	if(ret)
	{
		*pRetCode = E_DB_SHOPRATE_R;
		goto L_RETU;
	}

	rows = 0;
	while(1)
	{
		memset(&shoprate,0,sizeof shoprate);
		ret = DB_t_cif_shop_feerate_fetch_select_by_c0(&shoprate);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows == 0 && shop_id != 1 )
				{
					shop_id = 1;
					// 使用通用配置
					ret = DB_t_cif_shop_feerate_open_select_by_c0_and_shop_id(shop_id);
					if(ret)
					{
						*pRetCode = E_DB_SHOPRATE_R;
						goto L_RETU;
					}
					continue;
				}
				break;
			}
			else
			{
				*pRetCode = E_DB_SHOPRATE_R;
				goto L_RETU;
			}
		}
		rows++;
		shop_id = 1;
		out_pack->lvol1 = shoprate.feetype;
		out_pack->lvol2 = shoprate.rate;
		PutRow(handle,out_pack,pRetCode,szMsg);
		if( rows % 15 == 0)
			AnswerDataPart(handle,*pRetCode,szMsg);
	}
	if(rows > 0)
		AnswerData(handle,*pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

