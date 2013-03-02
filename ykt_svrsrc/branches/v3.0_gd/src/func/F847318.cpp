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
#include "acctrans.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "busqc.h"

int F846307(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F847318(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int cardno=0;
	int custid,ret;
	
	custid = in_pack->lvol0;
	
	if(custid == 0 )
	{
		return E_INPUT_DATA_INVAILD;
	}
	
	if(in_pack->lvol1 >0)
		cardno = in_pack->lvol1;
	else
	{
		ret = get_cardno_by_custid(custid,&cardno);
		if(ret)
		{
			return ret;
		}
	}
	T_t_card tCard;
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_card_read_by_cardno(cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return  ERRINFO(E_NOTEXIST_CARDNO,cardno);
		else
			return E_DB_CARD_R;
	}
	// 检查卡密码
	if(strcmp(in_pack->sstatus0,TYPE_YES) == 0)
	{
		ret = CheckUserPswd(in_pack->semp_pwd,tCard.cardpwd);
		if(ret)
		{
			return  E_CARDPWD;
		}
	}
	des2src(in_pack->semp,in_pack->scust_limit);
	in_pack->lwithdraw_flag = in_pack->lvol6;
	in_pack->lvol0=tCard.cardno;
	in_pack->sstatus1[0]='1';
	ret = F846307(handle,iRequest,in_pack,pRetCode,szMsg);
	if(ret)
		return ret;
	return 0;
}
