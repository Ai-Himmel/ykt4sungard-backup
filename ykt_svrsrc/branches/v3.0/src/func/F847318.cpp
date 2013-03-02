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
#include "busqc.h"

int F846307(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F847318(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_card tCard;
	int custid,ret;
	memset(&tCard,0,sizeof tCard);
	
	custid = in_pack->lvol0;
	
	if(custid == 0 )
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	if(in_pack->lvol1 == 0)
	{
		ret = get_curr_card_by_custid(custid,&tCard);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		in_pack->lvol1 = tCard.cardno;
	}
	else
	{
		ret = DB_t_card_read_by_cardno(in_pack->lvol1,&tCard);
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
		ret = CheckUserPswd(in_pack->semp_pwd,tCard.cardpwd);
		if(ret)
		{
			*pRetCode = E_OPERPWD;
			goto L_RETU;
		}
	}
	in_pack->lvol0=tCard.cardno;
	in_pack->sstatus1[0]='1';
//	in_pack->lwithdraw_flag;
	ret = F846307(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
		goto L_RETU;
		
	return 0;
L_RETU:
	return -1;
}
