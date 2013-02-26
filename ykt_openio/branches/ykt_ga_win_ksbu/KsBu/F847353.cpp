/* --------------------------------------------
* ��������: F847353.cpp
* ��������: 2007-10-12
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ����ר��ˮ��ת�˽���ѯ
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

//#ifdef _DEBUG
extern CLogFile g_LogFile;	
int count2 = 0;
//#endif

int F847353(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	int cut_id = in_pack->lvol0;
	int money = 0;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	Save_Info save_info;
	memset(&save_info, 0, sizeof(save_info));

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, F_LVOL0, 0);

	CheckAccountNo(cut_id, &money, &error_code);
	out_pack->lvol0 = money;

	if (error_code != 0)
	{
		g_LogFile.WriteLogEx(1001, "�ͻ���[%d]--ת�ʽ��[%d]--������[%d]--���[%d]", 
			cut_id, money, error_code, ++count2);
		error_code = DLLFUN_ERR_CHECK_ACC_THIRD_PART_FAIL;
	}	

	*pRetCode = error_code;
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif