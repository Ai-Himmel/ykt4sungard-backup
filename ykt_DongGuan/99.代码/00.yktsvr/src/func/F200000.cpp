/* --------------------------------------------
 * 创建日期: 2010-09-06
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 卡状态校验
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "transcode.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"

int GetCardStatusCode(int cardno,char* statuscode,char *statusinfo)
{
	*statuscode=0;
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));
	int ret=DB_t_card_read_by_cardno(cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		*statuscode=CARDSTATUS_EXCEPT;
		return 0;
	}
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		strcpy(statusinfo,"卡已注销");
		*statuscode=CARDSTATUS_CLOSE;
		return 0;
	}	
	if('1'==tCard.lockflag[0])
	{
		strcpy(statusinfo,"卡已锁定");
		*statuscode=CARDSTATUS_LOCK;
		return 0;
	}	
	if('1'==tCard.lossflag[0])
	{
		strcpy(statusinfo,"卡已挂失");
		*statuscode=CARDSTATUS_LOST;
		return 0;
	}	
	if('1'==tCard.frozeflag[0])
	{
		strcpy(statusinfo,"卡已冻结");
		*statuscode=CARDSTATUS_FROZE;
		return 0;
	}
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	if(strncmp(tCard.expiredate,trans.transdate,8)<0)
	{
		strcpy(statusinfo,"卡已过期");
		*statuscode=CARDSTATUS_EXPIRE;
		return 0;
	}	
	if('1'==tCard.badflag[0])
	{
		strcpy(statusinfo,"卡已登记为坏卡");
		*statuscode=CARDSTATUS_EXCEPT;
		return 0;
	}	
	return 0;
}
int F200000(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_SSTATUS0,F_VSMESS,0);

	trans.cardno=rPack->lvol0;	
	if(trans.cardno<1)
	{
		ERRTIP("卡号不能为空");
		return E_COMMON_ERR;
	}
	ret=GetCardStatusCode(trans.cardno,out_pack->sstatus0,out_pack->vsmess);
	if(ret)
	{
		writelog(LOG_ERR,"GetCardStatusCode ret[%d]cardno[%d]",ret,trans.cardno);
		return ret;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

