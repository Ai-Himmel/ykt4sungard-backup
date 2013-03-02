/* --------------------------------------------
 * 程序名称: F847227
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡回收
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "busqc.h"

int F847227(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char sysdate[9] = "";
	char systime[7] = "";
	char cardphyid[17] = "";
	int authcardno = 0;
	T_t_authcard tAuthCard;

	memset(&tAuthCard,0,sizeof tAuthCard);

	authcardno = rPack->lvol0;
	if(authcardno <= 0)
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;
	}

	des2src(cardphyid,rPack->sdate0);
	
	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	ret = DB_t_authcard_read_by_cardno(authcardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_AUTHCARD_NOT_EXISTS;
		else
			*pRetCode = E_DB_OPER_AUTHCARD_R;
		goto L_RETU;
	}
	
	if(tAuthCard.status[0] == STATUS_LOGOUT)
	{
		writelog(LOG_ERR,"授权卡已经回收，不能重复卡号[%d]",authcardno);
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}

	if(strcmp(tAuthCard.cardphyid,cardphyid))
	{
		writelog(LOG_ERR,"card id / phyid diff , card id[%d] db phyid[%s] input phyid[%s]"
			,authcardno,tAuthCard.cardphyid,cardphyid);
		*pRetCode = E_INPUT_CARDPHYID;
		goto L_RETU;
	}

	tAuthCard.status[0] = STATUS_LOGOUT;
	memset(tAuthCard.cardstatus,'0',sizeof(tAuthCard.cardstatus));
	getsysdate(tAuthCard.closedate);
	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update auth card status error , cardno[%d]", authcardno);
		*pRetCode = E_DB_AUTHCARD_U;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;		
}

