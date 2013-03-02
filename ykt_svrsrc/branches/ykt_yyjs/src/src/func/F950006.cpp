/* --------------------------------------------
 * ��������: F950006.c
 * ��������: 2006-8-12
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ϵͳ����
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
#include "fdsqc.h"
#include "pubfunc.h"
#include "dbfunc_foo.h"

int F950006(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	char buf[256] = "";

	char static_key[17]="4343232323231111";
	if(0!=strncmp(static_key,rPack->scust_limit,sizeof(static_key)))
	{
	int sysid = rPack->lcert_code;
	ret = CheckGatewayDynKey(sysid,rPack->scust_limit);
	if(ret)
	{
			writelog(LOG_ERR,"��̬��Կ����");
		*pRetCode = ret;
		goto L_RETU;
		}
	}
	ret = GetParameter(rPack->lvol0,buf);
	writelog(LOG_DEBUG,"�������parameter[%d]",rPack->lvol0);
	if(ret)
	{
		writelog(LOG_ERR,"��ȡ����ʧ��[%d]",rPack->lvol0);
		*pRetCode = ret;
		goto L_RETU;
	}
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SCARD0,0);
	des2src(out_pack->scard0,buf);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

