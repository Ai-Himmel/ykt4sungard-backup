#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "busqc.h"
#include "actfunc.h"

int F820522(TRUSERID * handle, int iRequest, ST_PACK * in_pack, int *pRetCode, char *szMsg)
{
	int ret;

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
	{
		writelog(LOG_ERR,"checkupdate err ret=%d",ret);
		return ERRIF_DATABASE_QRY;
	}
	ret=GetSysAcctPara(pAccTrans->sysAcctPara);
	if(ret)
		return ret;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle, F_VSMESS, F_SDATE0, F_SDATE1, F_SDATE2, F_SDATE3, F_SSTATUS0, F_STIME0, 0);
	des2src(out_pack->sdate0,pAccTrans->trans.accdate);
	des2src(out_pack->stime0,pAccTrans->trans.acctime);
	sprintf(out_pack->sdate1,"%d",pAccTrans->sysAcctPara.iSettleDate);
	sprintf(out_pack->sdate2,"%d",pAccTrans->sysAcctPara.iPreSettleDate);
	sprintf(out_pack->sdate3,"%d",pAccTrans->sysAcctPara.iNextSettleDate);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}
