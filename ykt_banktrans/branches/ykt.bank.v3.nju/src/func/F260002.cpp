/* ----------------------------------------------------------
 * �������ƣ�F260002.cpp
 * �������ڣ�2007-08-24
 * �������ߣ�����
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�ת��д��ʧ��
 * ----------------------------------------------------------*/

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

int F260002(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	// ���̨��д��ʧ��
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 847304;
	
	SetHeadCol(&sPack, F_LVOL1, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ

	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	
	writelog(LOG_ERR,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);

	
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 847316 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			goto L_retu;
		}
		else
		{
			writelog(LOG_ERR,"Call 847316 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,aPack.pack.vsmess);
			goto L_retu;
		}
	}

	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	
	PutRow(handle, &aPack.pack, pRetCode, szMsg);
	
	return 0;
L_retu:

	return -1;
	
}

