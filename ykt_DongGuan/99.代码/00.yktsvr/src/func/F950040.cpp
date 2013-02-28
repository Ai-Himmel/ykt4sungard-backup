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
#include "busqc.h"
#include "acctrans.h"

int F950040(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret,i,j;
	T_t_device tDevice;
	T_t_msglist tMsg;
	int retries = 0;
	int msgid;
	char cardgroup[257] = "";
	unsigned char out_data[128] = "";
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	
	memset(&tDevice,0,sizeof tDevice);
	

	if(rPack->lcert_code < 1)
	{
		return E_NOTEXIST_DEVICE;
	}
	if(strlen(rPack->vsvarstr0) != 254)
	{
		writelog(LOG_DEBUG,"card right [%s] ",rPack->vsvarstr0);
		return E_DEVICE_PARAM_ERR;
	}
	if((ret = DB_t_device_read_by_deviceid(rPack->lcert_code,&tDevice)))
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_DEVICE,rPack->lcert_code);
		else
			return E_DB_DEVICE_R;

	}
	if(tDevice.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_NOTEXIST_DEVICE,tDevice.devphyid);
	}
	memset(&tMsg,0,sizeof tMsg);
	//cardgroup[0] = '0';
	strcpy(cardgroup,rPack->vsvarstr0);
	cardgroup[254] = '0';
	for(i = 0;i < 255;i+=8)
	{
		out_data[i/8] = 0;
		for(j = 0;j < 8;++j)
		{
			unsigned char t = (*(cardgroup+i+j) == '1') ? 1 : 0; 
			out_data[i/8] |= (t << (7-j)); 
		}
	}
	memset(cardgroup,0,sizeof cardgroup);
	for(i = 0,j = 0;i < 256 / 8;++i,j+=2)
	{
		sprintf(cardgroup+j,"%02X",out_data[i]);
	}
	cardgroup[256/4] = '\0';
	tMsg.funcno = 950040;
	tMsg.msglevel=1;
	tMsg.maxsendcnt = 1;
	//des2src(tMsg.devphyid,tDevice.devphyid);
	tMsg.deviceid= tDevice.deviceid;
	AddXmlItemStr(tMsg.reqdata,XML_KEY_CARDRIGHTTYPE,cardgroup);
	if((ret = AddMsgLst(&tMsg)))
	{
		return  ret;
	}
	strcpy(out_pack->vsvarstr0,"成功");
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
