/* --------------------------------------------
 * 创建日期: 2009-10-10 
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 读卡器签到-CPU卡
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
#include "dbfunc_foo.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "acctrans.h"

int F850003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret; 
	int deviceid=0;
	int shopid = 0;
	char termno[13]={0};

	CAccTrans& ats=CAccTrans::GetInst();
	ST_CPACK aPack;
	ST_PACK *out_pack;
	out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL3,F_SALL_NAME,0);
	
	deviceid=rPack->lwithdraw_flag;
	des2src(termno,rPack->sserial0);
	
	// 检查 psam 中的机器号
	T_t_device tDevice;

	memset(&tDevice,0,sizeof(tDevice));

	ret=DB_t_device_read_by_deviceid(deviceid,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_DEVICE;
		else
			return E_DB_DEVICE_R;
	}
	if(tDevice.status[0]!=STATUS_NORMAL)
		return E_DEVICE_LOGOUT;
    if(strcmp(termno,"FFFFFFFFFFFF")!=0)
    {
    	T_t_psamcard psamcard;

    	memset(&psamcard,0,sizeof(psamcard));
    	ret=DB_t_psamcard_read_lock_by_c1_and_termno(termno,&psamcard);
    	if(ret)
    	{
    		writelog(LOG_ERR,"termno[%s]",termno);
    		CHECK_DB_ERR;
    		if(DB_NOTFOUND == ret)
    			return E_DB_PSAMCARD_N;
    		else
    			return E_DB_PSAMCARD_R;
    	}
    	if(psamcard.status!=0)
    	{
    		writelog(LOG_ERR,"termno[%s] status err",termno);
    		DB_t_psamcard_free_lock_by_c1();
    		return ERRIF_POS_CLOSE;
    	}
    	if(psamcard.deviceid>0)
    	{
    		DB_t_psamcard_free_lock_by_c1();		
    		if(deviceid!=psamcard.deviceid)
    		{
    			writelog(LOG_ERR,"termno[%s]deviceid[%d],psam deviceid[%d] diff",termno,deviceid,psamcard.deviceid);
    			return ERRIF_POS_TERMID;
    		}
    	}
    	else
    	{
    		psamcard.deviceid=deviceid;
    		des2src(psamcard.devjointime,pAccTrans.hostdatetime);
    		des2src(psamcard.lastsaved,psamcard.devjointime);
    		ret=DB_t_psamcard_update_lock_by_c1(&psamcard);
    		if(ret)
    		{
    			return E_DB_PSAMCARD_U;
    		}
    	}
    }
	char devstatus[2]="";
	devstatus[0]=DEVRUNSTATUS_ONLINE;
	ret=UpdDevRunstatusByDeviceid(deviceid,devstatus);
	if(ret)
	{
		writelog(LOG_ERR,"UpdDevRunstatusByDeviceid deviceid[%d]",deviceid);
		return ret;
	}
	SetCol(handle,0);
	SetCol(handle,F_SNAME,F_LVOL3,F_SCUST_LIMIT,0);

	// 获取mifare 卡密钥
	ret=GetSysParaVal(GLOBLE_SYSPARA_STATIC_KEY,out_pack->scust_limit);
	if(ret)
		return ERRIF_DATABASE_QRY;

	ret = GetShopidByDeviceid(deviceid,ats.trans.transdate,ats.trans.transtime,&shopid);
	if(ret)
	{
		return ret;
	}
	T_t_shop tShop;
	memset(&tShop,0,sizeof(tShop));
	ret=DB_t_shop_read_by_shopid(shopid,&tShop);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			ERRTIP("该设备分配的商户号%d不存在",shopid);
			return E_COMMON_ERR;
		}
		else
			return E_DB_SHOP_R;
	}
	if(tShop.status[0]!=STATUS_NORMAL)
	{
		DB_t_shop_free_lock_by_c0();
		ERRTIP("该设备分配的商户号%d已注销",shopid);
		return E_COMMON_ERR;
	}
	if(tShop.shoptype!=SHOPTYPE_COSUMESHOP)
	{
		ERRTIP("该设备分配的商户号%d不是收费商户",shopid);
		return E_COMMON_ERR;
	}
	out_pack->lvol3 = shopid;
	des2src(out_pack->sall_name,tShop.shopname);
	writelog(LOG_INFO,"签到商户号%d商户名[%s]",shopid,tShop.shopname);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

