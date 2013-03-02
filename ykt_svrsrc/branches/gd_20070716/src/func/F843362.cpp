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
#include "fdsqc.h"

int F843362(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=1;

	T_t_deposit_operpos tDepositOperPos;
	T_t_deposit_oper tDepositOper;
	T_t_deposit_shoppos  tDepositShopPos;
	
	memset(&tDepositOperPos,0,sizeof(tDepositOperPos));
	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tDepositShopPos,0,sizeof(tDepositShopPos));
	
	if(!strlen(rPack->vsvarstr1))
	{
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}	
	ret=DB_t_deposit_oper_read_by_oper_code(rPack->scust_auth,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_OPER_N;
		else
			*pRetCode=E_DB_DEPOSIT_OPER_R;
		goto L_RETU;
	}
	if(tDepositOper.usedevlimit_flag[0]!='1')
	{
		*pRetCode=E_OPER_NO_NEED_DEVICE;
		goto L_RETU;
	}
	des2src(tDepositOperPos.oper_code,rPack->scust_auth);
	des2src(tDepositOperPos.open_oper,rPack->semp);
	getdatetime(tDepositOperPos.last_saved);
	for(i=1;i<50;i++)
	{
		memset(tDepositOperPos.device_id,0,sizeof(tDepositOperPos.device_id));
		ret=GetValueFromFmtBuf(rPack->vsvarstr1,",",i,tDepositOperPos.device_id);
		if(ret||strlen(tDepositOperPos.device_id)==0)
			break;
		{
			//如果操作员不是充值商户操作员则不允许绑定充值商户设备
			ret=DB_t_deposit_shoppos_read_by_device_id(tDepositOperPos.device_id, &tDepositShopPos);
			if(ret)
			{
				if(ret==DB_NOTFOUND)
				{
					if(tDepositOper.shopoper_flag[0]=='1')
					{
						*pRetCode=E_DEVICE_NOTIS_DEPOSITSHOP;
						goto L_RETU;
					}
				}	
				else
				{
					*pRetCode=E_DB_DEPOSIT_SHOPPOS_R;
					goto L_RETU;

				}
			}
			else
			{
				if(tDepositOper.shopoper_flag[0]=='0')
				{
					*pRetCode=E_DEVICE_IS_DEPOSITSHOP;
					goto L_RETU;
				}
			}

		}
		SQLCODE=0;
		ret=DB_t_deposit_operpos_add(&tDepositOperPos);
		if(ret)
		{
			writelog(LOG_ERR,"oper_code[%s]",tDepositOperPos.oper_code);
			if(DB_REPEAT==ret)
			{
				SQLCODE=0;
				continue;
			}
			else
			{
				*pRetCode=E_DB_DEPOSIT_OPERPOS_I;
				goto L_RETU;
			}
		}
	}
	return 0;
L_RETU:
	return -1;
}
