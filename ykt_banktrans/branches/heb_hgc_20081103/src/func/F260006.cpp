/* ----------------------------------------------------------
 * �������ƣ�F260006.cpp
 * �������ڣ�2008-05-03
 * �������ߣ�����
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�Ȧ����˴���
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

int F260006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	FILE *fp = NULL;

	BANK_COMPARE_RECODE compare_record;			// �����ļ���¼����
	memset(&compare_record, 0, sizeof(compare_record));

	char comp_file_path[256] = "";
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	// ���̨��д��ʧ��
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240007;
	
	SetHeadCol(&sPack, F_LVOL0, F_LVOL1, F_SCUST_AUTH, F_SCUST_AUTH2, F_SORDER0, F_SEMP_NO, F_SCUST_TYPE, F_SORDER1, F_SCARD1, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ

	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	des2src(comp_file_path, in_pack->vsvarstr0);		// �����ļ�·����:BANK0320080414.txt
	writelog(LOG_ERR,"branch_no[%d], base_funcno[%d]",g_Bank.DRTP_BRANCH,g_Bank.BCC_BASEFUNCNO);

	if ((fp = fopen(comp_file_path, "rb")) == NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]", comp_file_path);
		goto L_retu;	
	}


	while (1)
	{
		if (NULL == fgets((char *)(&compare_record), sizeof(BANK_COMPARE_RECODE), fp))	// ��ȡ�����ļ������ݼ�¼
		{
			writelog(LOG_ERR,"fgets error local_sn=[%s]", compare_record.LocalSn);
			break;	
		}
		sPack.pack.lvol0 = 0;
		des2src(sPack.pack.scust_auth, compare_record.BankCard);
		des2src(sPack.pack.scust_auth2, compare_record.BankSn);
		des2src(sPack.pack.sorder0, compare_record.GDCAccount);
		des2src(sPack.pack.semp_no, compare_record.LocalSn);
		des2src(sPack.pack.scust_type, compare_record.TradeCode);
		des2src(sPack.pack.sorder1, compare_record.TransMomoy);
		des2src(sPack.pack.scard1, in_pack->sbank_acc);			// �ļ���:BANK0320080414.txt

		ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
		if (ret < 0 || aPack.head.retCode != 0)
		{
			if (ret < 0)
			{
				writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
				strcpy(szMsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
				goto L_retu;
			}
			else
			{
				writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
				strcpy(szMsg,aPack.pack.vsmess);
				goto L_retu;
			}
		}
	}

	sPack.pack.lvol0 = 1;
	des2src(sPack.pack.scard1, in_pack->sbank_acc);
		
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			goto L_retu;
		}
		else
		{
			writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,aPack.pack.vsmess);
			goto L_retu;
		}
	}
		
	if (fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]", comp_file_path);
		goto L_retu;
	}
	
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	
	PutRow(handle, &aPack.pack, pRetCode, szMsg);
	
	return 0;
L_retu:

	return -1;
	
}

