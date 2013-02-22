/* --------------------------------------------
 * ��������: F249999.cpp
 * ��������: 2007-11-21
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���Գ���, ͨ��ͨѶƽ̨��bank��̨
 *           ��ת�����ɺ�̨
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "mypub.h"  
#include "tcp.h"
#include "cpack.h"
#include "svrlink.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "bank.h"

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

int F249999(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 999999;
	SetHeadCol(&sPack, F_SCLOSE_EMP, F_SORDER2, F_SSERIAL0, F_SEMP_PWD, F_DAMT0, F_LVOL3, 0);

	memcpy(&(sPack.pack), rPack, sizeof(sPack.pack));
		
	writelog(LOG_ERR,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);
	
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	writelog(LOG_ERR,"Call 999999 retCode=[%d]", ret);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		memcpy(szMsg, aPack.pack.vsmess, sizeof(aPack.pack.vsmess) -1);
		
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 999999 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			*pRetCode = ret;
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call 999999 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			*pRetCode = ret;
			return aPack.head.retCode;
		}
	}
	
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_DAMT10,F_DAMT11,F_DAMT12,F_VSMESS,0);
	
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;

}

