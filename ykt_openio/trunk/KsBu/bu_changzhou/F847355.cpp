/* --------------------------------------------
* ��������: F847355.cpp
* ��������: 2007-09-10
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ���´�ѧ���ת�˲����������ݿ�
* --------------------------------------------
* �޸�����:
* �޸���Ա:
* �޸�����:
* �汾��Ϣ:
* ��ע��Ϣ:
* --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "mypub.h"
#include "bupub.h"
#include "logfile.h"
#include "DllFun.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

int F847355(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	float elec_price = 0.0;
	bool conncet_flag = false;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	out_pack->damt0 = elec_price = CNectDB(true);

	if (elec_price >= -0.01 && elec_price <= 0.01)	// ���Ϊ0��ʾִ��ʧ��, �������Ϊ��
	{
		error_code = DLLFUN_ERR_GET_ELEC_PRICE;
		g_LogFile.WriteLogEx(1001, "���ݿ����ӳ���--[%d]", error_code);
		goto L_RETU;	
	}
	
	if (GetDBStatus() != 1)
	{
		error_code = DLLFUN_ERR_CONNECT_ELEC;
		g_LogFile.WriteLogEx(1001, "������ݿ�״̬����--[%d]", error_code);
		goto L_RETU;
	}

L_RETU:
	out_pack->lvol10 = *pRetCode = error_code;
	out_pack->damt1 = CNectDB(false);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif