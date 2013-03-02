/* --------------------------------------------
 * 程序名称: F848268.c
 * 创建日期: 2007-04-10
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:门禁名单删除
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

static int do_848268(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	int row = 0;
	T_t_door_device_cardlist door_card;
	T_t_pif_device device;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	memset(&door_card,0,sizeof door_card);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_VSMESS,0);

	writelog(LOG_INFO,"cutid[%d],ctlid[%d]",in_pack->lvol0,in_pack->lvol1);
	if(unlike_tbl_id(in_pack->lvol0))
	{
		sprintf(out_pack->vsmess,"警告: 客户号不正确[%d]",in_pack->lvol0);
		out_pack->lvol0 = 0;
		goto L_PUTROW_RET;
	}
	if(unlike_tbl_id(in_pack->lvol1))
	{
		sprintf(out_pack->vsmess,"警告: 门禁号不正确[%d]",in_pack->lvol1);
		out_pack->lvol0 = 0;
		goto L_PUTROW_RET;
	}

	
	ret = DB_t_door_device_cardlist_read_by_device_id_and_cust_id(
		in_pack->lvol1,in_pack->lvol0,&door_card);

	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			sprintf(out_pack->vsmess,"警告: 客户号[%d]门禁[%d]不存在"
				,in_pack->lvol0,in_pack->lvol1);
			out_pack->lvol0 = 0;
			goto L_PUTROW_RET;
		}
		else
			return E_DB_DOOR_CARDLIST_R;
	}
	// 判断是否已经删除过
	/*
	if(door_card.status >= DOOR_FLAG_WAITING_DEL)
	{
		sprintf(out_pack->vsmess,"警告: 客户号[%d]门禁[%d]已被删除"
				,in_pack->lvol0,in_pack->lvol1);
		out_pack->lvol0 = 2;
		goto L_PUTROW_RET;
	}
	*/
	db_getsysdatetime2(door_card.update_time);
	//door_card.status = DOOR_FLAG_WAITING_DEL;
	door_card.add_del_flag[0] = ADDDELFLAG_DEL;
	ret = DB_t_door_device_cardlist_update_by_device_id_and_cust_id(
		in_pack->lvol1,in_pack->lvol0,&door_card);
	if(ret)
	{
		return E_DB_DOOR_CARDLIST_U;
	}
	
	sprintf(out_pack->vsmess,"成功: 客户号[%d]门禁[%d]已删除"
				,in_pack->lvol0,in_pack->lvol1);
	out_pack->lvol0 = 1;
L_PUTROW_RET:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int F848268(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_848268(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	return 0;
}
