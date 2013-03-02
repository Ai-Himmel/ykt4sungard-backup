/* --------------------------------------------
 * 程序名称: F843362.sqC
 * 创建日期: 2007-11-02
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 充值操作员设备添加
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
#include "acctrans.h"

int F843362(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=1;
	char deviceid[31]="";

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	pAccTrans->trans.transcode=MAKETRANSCODEADD(TCM_DEPOSITOPERPOS);
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	if(ret)
		return ret;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;	

	T_t_depositoperpos tDepositOperPos;
	T_t_depositoper tDepositOper;
	T_t_depositshoppos  tDepositShopPos;
	
	memset(&tDepositOperPos,0,sizeof(tDepositOperPos));
	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tDepositShopPos,0,sizeof(tDepositShopPos));
	
	if(!strlen(rPack->vsvarstr1))
	{
		return E_INPUT_DATA_INVAILD;
	}	
	ret=DB_t_depositoper_read_by_opercode(rPack->scust_auth,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPER_N;
		else
			return E_DB_DEPOSITOPER_R;
	}
	if(tDepositOper.usedevlimitflag[0]!='1')
	{
		return E_OPER_NO_NEED_DEVICE;
	}
	des2src(tDepositOperPos.opercode,rPack->scust_auth);
	des2src(tDepositOperPos.openoper,rPack->semp);
	getfmtsysdatetime(tDepositOperPos.lastsaved);
	for(i=1;i<50;i++)
	{
		tDepositOperPos.deviceid=0;
		ret=GetValueFromFmtBuf(rPack->vsvarstr1,",",i,deviceid);
		if(ret||strlen(deviceid)==0)
			break;
		{
			tDepositOperPos.deviceid=atoi(deviceid);
			//如果操作员不是充值商户操作员则不允许绑定充值商户设备
			ret=DB_t_depositshoppos_read_by_deviceid(tDepositOperPos.deviceid, &tDepositShopPos);
			if(ret)
			{
				if(ret==DB_NOTFOUND)
				{
					if(tDepositOper.shopoperflag[0]=='1')
					{
						return E_DEVICE_NOTIS_DEPOSITSHOP;
					}
				}	
				else
				{
					return E_DB_DEPOSITSHOPPOS_R;

				}
			}
			else
			{
				if(tDepositOper.shopoperflag[0]=='0')
				{
					return E_DEVICE_IS_DEPOSITSHOP;
				}
			}

		}
		SQLCODE=0;
		ret=DB_t_depositoperpos_add(&tDepositOperPos);
		if(ret)
		{
			writelog(LOG_ERR,"opercode[%s]",tDepositOperPos.opercode);
			if(DB_REPEAT==ret)
			{
				SQLCODE=0;
				continue;
			}
			else
			{
				return E_DB_DEPOSITOPERPOS_I;
			}
		}
	}
	return 0;
}
