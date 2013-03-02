/* --------------------------------------------
 * 创建日期: 2010-10-22 
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 汇多充值机签到功能
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
#include "acctrans.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"


int addPOSCheckPOS(int deviceid,T_t_device &tDevice)
{
	int ret;
	if(deviceid == 0)
	{
		ret = GetDevIdByDevPhyId(&(tDevice.deviceid),tDevice.devphyid);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				writelog(LOG_ERR,"device [%s] not exists",tDevice.devphyid);
				return ERRIF_POS_NOREG;
			}
			else
			{
				writelog(LOG_ERR,"GetDevIdByDevPhyId error");
				return ERRIF_SYSTEM;
			}
		}
	}
	else
	{
		tDevice.deviceid = deviceid;
	}
	ret = DB_t_device_read_by_deviceid(tDevice.deviceid,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			writelog(LOG_ERR,"deviceid [%d] not exists",tDevice.deviceid);
			return ERRIF_POS_NOREG;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_device_read_by_deviceid error");
			return ERRIF_SYSTEM;
		}
	}
	if(tDevice.status[0] == STATUS_DELETE)
	{
		writelog(LOG_ERR,"device[%s]has been unregister!",tDevice.devphyid);
		return ERRIF_FRONT_CLOSE;
	}
	if(strcmp(tDevice.devtypecode,DEVITYPE_ADDPOS)!=0)
	{
		writelog(LOG_ERR,"device[%s] [%s]is not addpos !",tDevice.devphyid,tDevice.devtypecode);
		return ERRIF_POS_NOFUNC;
	}
	return 0;
}
static int doCard(const T_t_card& tCard)
{
	char sysdate[9]={0};
	getsysdate(sysdate);
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRIF_CARD_CLOSE;
	}	
	if('1'==tCard.lockflag[0])
	{
		return ERRIF_CARD_LOCKED;
	}
	if('1'==tCard.frozeflag[0])
	{
		return ERRIF_CARD_FROZED;
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRIF_CARD_LOST;
	}	
	if('1'==tCard.badflag[0])
	{
		return ERRIF_CARD_BAD;
	}	
	
	//检查卡的有效期
	if(strcmp(tCard.expiredate,sysdate)<=0)
		return ERRIF_CARD_EXPIRED;
	return 0;
}

static int do950070(T_t_device &tDevice,T_t_card &tCard,T_t_dpsopercard &tDpsCard,
	T_t_dpsoper &tOperator,ST_PACK *rPack)
{
	int ret;
	des2src(tDevice.devphyid,rPack->sphone3);
	ret = addPOSCheckPOS(rPack->lwithdraw_flag,tDevice);
	if(ret)
		return ret;
	
	ret = DB_t_card_read_by_cardno(rPack->lvol0,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"card [%d] is not exists!",rPack->lvol0);
			return ERRIF_CARD_NOTEXIST;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_card_read_by_cardno error");
			return ERRIF_SYSTEM;
		}
	}

	ret = DB_t_dpsopercard_read_by_cardno_and_disableflag(tCard.cardno,ADDDELFLAG_ADD,&tDpsCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"card[%d] has not been auth!",tCard.cardno);
			return ERRIF_AUTHCARD_NORIGHT;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_dpsopercard_read_by_cardno_and_disableflag error");
			return ERRIF_SYSTEM;
		}
	}

	ret = DB_t_dpsoper_read_by_opercode(tDpsCard.opercode,&tOperator);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"oper[%s] not exists!",tDpsCard.opercode);
			return ERRIF_AUTHCARD_EXPIRED;
		}
		else
		{
			writelog(LOG_ERR,"DB_t_dpsoper_read_by_opercode error");
			return ERRIF_SYSTEM;
		}
	}

	if(tOperator.status[0] == STATUS_DELETE)
	{
		writelog(LOG_ERR,"oper[%s] has been cancled ",tOperator.opercode);
		return ERRIF_AUTHCARD_EXPIRED;
	}

	ret = doCard(tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card[%d] error , ret=[%d]",tCard.cardno,ret);
		return ret;
	}
	
	ret = chk_cardpwd_by_cardno(tCard.cardno,rPack->stx_pwd);
	if(ret)
	{
		writelog(LOG_ERR,"card[%d] password error",tCard.cardno);
		if(E_CARD_PWD_DIFFER == ret)
			return ERRIF_AUTHCARD_PWD;
		else
		{
			writelog(LOG_ERR,"chk_cardpwd_by_cardno error");
			return ERRIF_SYSTEM;
		}
	}
	return 0;
}

int F950070(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	T_t_device tDevice;
	T_t_card tCard;
	T_t_dpsopercard tDpsCard;
	T_t_dpsoper tOperator;
	int ret;
	char temp[64] = {0};
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tDevice,0,sizeof tDevice);
	memset(&tCard,0,sizeof tCard);
	memset(&tDpsCard,0,sizeof tDpsCard);
	memset(&tOperator,0,sizeof tOperator);

	

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LCERT_CODE,F_SPHONE3,F_LSAFE_LEVEL,F_LWITHDRAW_FLAG,F_LVOL0,F_SEMP_NO,
		F_SNAME,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,F_SDATE3,F_STIME3,F_SHOLDER_AC_NO,F_LVOL5,0);

	out_pack->lcert_code = ERRIF_SYSTEM;
	ret = do950070(tDevice,tCard,tDpsCard,tOperator,rPack);
	if(ret)
	{
		out_pack->lcert_code = ret;
		writelog(LOG_ERR,"do950070 error ,ret[%d]",ret);
	
	}
	else
	{
		des2src(out_pack->sphone3,tDevice.devphyid);
		out_pack->lcert_code = 0;  //
		// TODO : 增加批次号
		ret = GetSysParaVal(SYSPARA_CMCCENTERPRICECODE,temp);
		if(ret)
		{
			writelog(LOG_ERR,"GetSysPara[%d] error",SYSPARA_CMCCENTERPRICECODE);
			out_pack->lcert_code = ERRIF_SYSTEM;
		}
		des2src(out_pack->sholder_ac_no,temp);
		ret = GetSysParaVal(SYSPARA_CMCCSUBAPPID,temp);
		if(ret)
		{
			writelog(LOG_ERR,"GetSysPara[%d] error",SYSPARA_CMCCSUBAPPID);
			out_pack->lcert_code = ERRIF_SYSTEM;
		}
		out_pack->lvol5 = atoi(temp);

		ret = DB_t_dpsoper_read_lock_by_c0_and_opercode(tDpsCard.opercode,&tOperator);
		if(ret)
		{
			writelog(LOG_ERR,"deposit operator not exists[%s]",tDpsCard.opercode);
			out_pack->lcert_code = ERRIF_SYSTEM;
		}
		
		
		if(out_pack->lcert_code == 0)
		{
			tOperator.batchno++;
			tOperator.authcode = get_int_random();
			des2src(tOperator.devphyid,tDevice.devphyid);
			ret = DB_t_dpsoper_update_lock_by_c0(&tOperator);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_dpsoper_update_lock_by_c0 error");
				out_pack->lvol0 = ERRIF_SYSTEM;
			}				
			out_pack->lwithdraw_flag = tDevice.deviceid;
			out_pack->lvol0 = tCard.cardno;
			out_pack->lvol1 = tOperator.batchno; // 充值批次号
			out_pack->lvol2 = tOperator.authcode; // 充值授权码
			out_pack->lvol3 = 1000000; // 充值授权金额
			out_pack->lvol4 = 0; //是否根据主机校对时钟
			getsysdate(out_pack->sdate3);
			getsystime(out_pack->stime3);
			out_pack->lsafe_level = 0; // 是否收取手续费
			memset(out_pack->sname,0,sizeof (out_pack->sname)); // 操作员姓名
			des2src(out_pack->semp_no,tOperator.opercode);
		}
		
	}

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
}

