/* --------------------------------------------
* ��������: F847308.cpp
* ��������: 2007-5-14
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: �����շ��ʻ�ת��(�����������Խ�)
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
#include "bupub.h"
#include "ComFunNetCharge.h"

#ifdef __cplusplus
extern "C" {
#endif

int F847308(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szStuEmpNo[21] = "";
	double dRemainBalance = 0.0;
	double dTransferBalance = in_pack->damt0; 
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_LVOL3, F_LVOL11, 0);

	out_pack->lvol11 = NetChargeTrans(in_pack->scust_auth, &dRemainBalance, &dTransferBalance,in_pack->scusttypes);
//	if (ret)
//		out_pack->lvol11 = ret;				// L_LVOL11��Ϊ������鿴
//	else
//		out_pack->lvol11 = 0;
	
	out_pack->damt0 = dRemainBalance;		// �����շ�ʣ�����
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif