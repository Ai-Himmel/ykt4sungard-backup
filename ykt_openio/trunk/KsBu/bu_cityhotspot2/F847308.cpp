/* --------------------------------------------
* ��������: 
* ��������: 2009-3-4
* ��������: �����
* �汾��Ϣ: 1.0.0.0
* ������: �����շ��ʻ�ת��(�����������Խ�)
* --------------------------------------------
* �޸�����:
* �޸���Ա:
* �޸�����:
* �汾��Ϣ:
* ��ע��Ϣ:
* --------------------------------------------*/

#include "netfeetrans.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
int F847308(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	if (strncmp(in_pack->sroom_no,"009",3) != 0)
	{
		g_LogFile.WriteLogEx(1004,"������[%s]����",in_pack->sroom_no);
		return -1;
	}
	g_LogFile.WriteLogEx(1004,"ѧ��[%s],����[%s],������[%s],���[%f],����ʱ��[%s]",in_pack->scust_auth,in_pack->sserial1,
		in_pack->sroom_no,in_pack->damt1,in_pack->scust_auth2);
	return netfee_trans(handle,iRequest,in_pack,pRetCode,szMsg);
}

#ifdef __cplusplus
}
#endif