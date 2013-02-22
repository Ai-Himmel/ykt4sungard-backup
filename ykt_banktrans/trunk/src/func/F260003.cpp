/* ----------------------------------------------------------
 * �������ƣ�do_mobile.cpp
 * �������ڣ�2007-08-23
 * �������ߣ�����
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ƶ���ֵ����
 * ----------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "cpack.h"
#include "errdef.h"
#include "bank.h"
#include "pubdef.h"
#include "pubdb.h"
#include "mypub.h"
#include "cpack.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "svrlink.h"
#include "do_trade.h"

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

int do_mobile_transfer(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	char device_id[10+1]="";
	char card_id[12+1]="";
	
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
//	ST_PACK *out_pack = &(aPack.pack);
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	//���̨��ˮ��ת��
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 847316;
	SetHeadCol(&sPack, F_LVOL1,F_LVOL2,F_SCUST_LIMIT,F_LVOL6,F_LVOL7, 0);       // ���÷���windows BU��ͷ����ͼ��Ϣ
	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	
	ret = ExtCall(0, g_Bank.DRTP_BRANCH, g_Bank.BCC_BASEFUNCNO, 0, g_Bank.TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 847317 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return E_TRANS_UNKNOW_ERROR;
		}
		else
		{
			writelog(LOG_ERR,"Call 847317 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}	
	return 0;
}



