/* --------------------------------------------
 * ��������: F950010.c
 * ��������: 2006-10-9
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: �ϴ�����ӿ�
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

int F847220(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847221(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847222(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847223(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847224(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);

int F950010(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	char buf[256] = "";
	int sysid;
	char dyna_key[21] = "";
	int req_no = 0;
	

	sysid = rPack->lcert_code;
	des2src(dyna_key,rPack->scust_limit);
	//writelog(LOG_DEBUG,"����[%d]  ,key[%s]",sysid,rPack->scust_limit);
	ret = CheckGatewayDynKey(sysid,rPack->scust_limit);
	if(ret)
	{
		writelog(LOG_DEBUG,"��̬��Կ����sysid[%d]",sysid);
		*pRetCode = ret;
		goto L_RETU;
	}
	req_no = rPack->lserial0;
	
	ret = 0;
	switch(req_no)
	{
		case 847220:
			ret = F847220(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		case 847221:
			ret = F847221(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		case 847222:
			ret = F847222(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		case 847223:
			ret = F847223(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		case 847224:
			ret = F847224(handle,iRequest,rPack,pRetCode,szMsg);
			break;
		default:
			*pRetCode = E_CUSTOMER_NO_RIGHT;
			ret = -1;
			goto L_RETU;
	}
	if(ret)
	{
		writelog(LOG_ERR,"����ִ�д���reqno[%d] ret [%d]",req_no,*pRetCode);
	}
	return ret;
L_RETU:
	return -1;
}