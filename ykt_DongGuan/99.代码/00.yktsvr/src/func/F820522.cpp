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

	CAccTrans& ats=CAccTrans::GetInst();
	ret=ats.Reset();
	if(ret)
		return ret;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle, F_VSMESS, F_SDATE0, F_SDATE1, F_SDATE2, F_SDATE3, F_SSTATUS0, F_STIME0, 0);
	sprintf(out_pack->sdate0,"%d",ats.hostdate);
	sprintf(out_pack->stime0,"%06d",ats.hosttime);
	sprintf(out_pack->sdate1,"%d",ats.settledate);
	calcEndDate(out_pack->sdate1,-1,out_pack->sdate2);
	calcEndDate(out_pack->sdate1,1,out_pack->sdate3);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}
