/* --------------------------------------------
* ��������: F847356.cpp
* ��������: 2007-09-10
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ���´�ѧ���ת�˲�ѯ
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
#include "BasicMath.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

#define FLOAT_BIT 2

int F847356(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int error_code = 0;
	char room_name[81] = "";
	double elec_price = 0.0;
	bool conncet_flag = false;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SBANKNAME, F_LVOL10, 0);
	
	elec_price = CNectDB(true);

	if (elec_price >= -0.01 && elec_price <= 0.01)	// ���Ϊ0��ʾִ��ʧ��, �������Ϊ��
	{
		g_LogFile.WriteLogEx(1002, "���ݿ�����--[%d]", error_code);
		error_code = DLLFUN_ERR_CONNECT_ELEC;
		goto L_RETU;	
	}

	round_float(&elec_price, 2);

	if ((error_code = GetRoomName(in_pack->lvol0, room_name)) != 1)
	{
		g_LogFile.WriteLogEx(1002, "��ȡ�������ƴ���[%d]--�������[%d]--������[%s]", error_code, in_pack->lvol0, room_name);
		error_code = DLLFUN_ERR_GET_ROOM_NAME;
		goto L_RETU;
	}

	error_code = 0;
L_RETU:
	out_pack->damt0 = elec_price;
	memcpy(out_pack->sbankname, room_name, sizeof(out_pack->sbankname) - 1);
	out_pack->lvol10 = *pRetCode = error_code;
	out_pack->damt1 = CNectDB(false);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return error_code;
}

#ifdef __cplusplus
}
#endif