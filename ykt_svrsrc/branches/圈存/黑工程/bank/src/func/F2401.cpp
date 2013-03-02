/* --------------------------------------------
 * ��������: F2401.sqc
 * ��������: 2009-08-8
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���ɲƾ�Ȧ��ת��
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "bank_interface.h"


int F2401(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int tradecode = rPack->lcert_code;

	switch(tradecode)
	{
		case TRADE_TRANS:													// ת��
			return Bank_Trans(handle,rPack,pRetCode,szMsg);			
			break;
			
		case TRADE_REVERSE:												// ����
			return Bank_Reverse(handle,rPack,pRetCode,szMsg);
			break;
		case BANK_QUERYBALA:
			return Bank_Querybala(handle,rPack,pRetCode,szMsg);				// ��ѯ���п����
			break;
		default:
			writelog(LOG_INFO,"This trade can't supplied,tradecode=[%d]!",tradecode);
			return E_TRANS_FUNC_NONSUPPORT;
	}

	return 0;
}

