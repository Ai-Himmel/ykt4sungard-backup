#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "busqc.h"
#include "acctrans.h"

int F820522(TRUSERID * handle, int iRequest, ST_PACK * in_pack, int *pRetCode, char *szMsg)
{
	int ret;

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	ret=pAccTrans->Reset();
	if(ret)
	{
		return ret;
	}
	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
		return ret;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle, F_VSMESS, F_SDATE0, F_SDATE1, F_SDATE2, F_SDATE3, F_SSTATUS0, F_STIME0, 0);
//	getsysdate(out_pack->sdate0);
//	getsystime(out_pack->stime0);
	ret=db_getsysdatetime(out_pack->sdate0,out_pack->stime0);
	if(ret)
	{
		writelog(LOG_ERR,"db_getsysdatetime err=%d",ret);
		return ERRIF_DATABASE_DIS;
	}
	des2src(out_pack->sdate1,pAccTrans->sysPara.sSettleDate);
	des2src(out_pack->sdate2,pAccTrans->sysPara.sPreSettleDate);
	des2src(out_pack->sdate3,pAccTrans->sysPara.sNextSettleDate);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}
