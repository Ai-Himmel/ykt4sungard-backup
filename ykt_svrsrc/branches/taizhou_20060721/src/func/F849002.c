/* --------------------------------------------
 * 程序名称: F849002.c
 * 创建日期: 2006-7-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 定点卡申请与取消
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

int F849002(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_water_info tWater;
	T_t_pif_card tCard;
	int cardid = 0;
	int watermeterno = 0;
	int maxmeterno = 0;
	char buf[101] = "";
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof tCard);
	
	cardid = in_pack->lvol0;
	
	if(cardid <= 0 )
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;	
	}

	watermeterno = in_pack->lvol1;
	if(watermeterno == 0)
	{
		//通用卡
		
	}
	else
	{
		ret = GetParameter(GLB_WATER_METER_NO_MAX,buf);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		maxmeterno = atoi(buf);
		if(watermeterno < 1 || watermeterno > maxmeterno )
		{
			*pRetCode = E_WATER_METER_NO_ERROR;
			goto L_RETU;
		}
	}
	
	ret = DB_t_pif_card_read_by_card_id(cardid,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}

	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		*pRetCode = ret;
		goto L_RETU;
	}

	memset(&tWater,0,sizeof tWater);
	ret = DB_t_water_info_read_lock_by_c1_and_cust_no(tCard.cosumer_id,&tWater);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
		{
			*pRetCode = E_DB_WATER_INFO_R;
			goto L_RETU;
		}
		tWater.cust_no = tCard.cosumer_id;
		getsysdate(tWater.bind_date);
		getsystime(tWater.bind_time);
		tWater.water_meter_no = watermeterno;
		des2src(tWater.card_phyid,tCard.physical_no);
		ret = DB_t_water_info_add(&tWater);
		if(ret)
		{
			*pRetCode = E_DB_WATER_INFO_I;
			goto L_RETU;
		}
	}
	else
	{
		getsysdate(tWater.bind_date);
		getsystime(tWater.bind_time);
		tWater.water_meter_no = watermeterno;
		des2src(tWater.card_phyid,tCard.physical_no);
		ret = DB_t_water_info_update_lock_by_c1_and_cust_no(&tWater);
		if(ret)
		{
			*pRetCode = E_DB_WATER_INFO_U;
			goto L_RETU;
		}
		DB_t_water_info_free_lock_by_c1();
	}
	
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,0);

	out_pack->lvol1 = watermeterno;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}


