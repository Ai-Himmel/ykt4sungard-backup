/* --------------------------------------------
* ��������: F847357.cpp
* ��������: 2007-09-11
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ���´�ѧ���ת��
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

int F847357(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_LVOL0, F_LVOL1, F_DAMT0, F_DAMT1, F_SPHONE, F_SORDER0, F_LVOL10, 0);
	
	out_pack->damt0 = CNectDB(true);
	if ((error_code = SellElec(in_pack->lvol0, in_pack->lvol1, in_pack->sorder0)) != 1)	// �����, ������, ����������
	{
		g_LogFile.WriteLogEx(1003, "ת�ʳ���--[%d]--�������[%d]--������[%d]--��������[%s]", error_code, in_pack->lvol0, in_pack->lvol1, in_pack->sorder0);
		error_code = DLLFUN_ERR_TRANSFER_ELEC;
		goto L_RETU;
	}

	error_code = 0;
L_RETU:
	out_pack->lvol0 = in_pack->lvol0;
	out_pack->lvol1 = in_pack->lvol1;
	memcpy(out_pack->sorder0, in_pack->sorder0, sizeof(out_pack->sorder0) - 1);
	out_pack->damt1 = CNectDB(false);
	out_pack->lvol10 = *pRetCode = error_code;
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif