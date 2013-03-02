/* --------------------------------------------
 * 程序名称: F847318.cpp
 * 创建日期: 2007-07-27
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 外接系统 挂失卡
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "fdsqc.h"

int F847102(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F847318(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_pif_card tCard;
	int cut_id,ret;
	memset(&tCard,0,sizeof tCard);
	
	cut_id = in_pack->lvol0;
	
	if(cut_id == 0 )
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	if(in_pack->lvol1 == 0)
	{
		ret = get_curr_card_by_custid(cut_id,&tCard);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		in_pack->lvol1 = tCard.card_id;
	}
	else
	{
		ret = DB_t_pif_card_read_by_card_id(in_pack->lvol1,&tCard);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				*pRetCode = E_DB_CARD_N;
			else
				*pRetCode = E_DB_CARD_R;
			goto L_RETU;
		}
	}
	// 检查卡密码
	if(strcmp(in_pack->sstatus0,TYPE_YES) == 0)
	{
		ret = CheckUserPswd(in_pack->semp_pwd,tCard.password);
		if(ret)
		{
			*pRetCode = E_PASSWORD_WRONG;
			goto L_RETU;
		}
	}
	ret = F847102(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
		goto L_RETU;
		
	return 0;
L_RETU:
	return -1;
}
