/* --------------------------------------------
* ��������: F847351.cpp
* ��������: 2007-07-04
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ����ר����Ϣͬ��(�����������Խ�, �˰汾ͨ��)
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
//#include "ComFunNetCharge.h"
//#include "LoadDll.h"
#include "DllFun.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
	extern CLogFile g_LogFile;	
	int count = 0;
#endif

#define  CARDSTAT_TYPE_REG	 		0     	//��״̬:��ʧ1-����2-��ʧ
#define  CARDSTAT_TYPE_LOST	 		1     	//��״̬:��ʧ0-����1-��ʧ
#define  CARDSTAT_TYPE_FREEZE		2     	//��״̬ ����0-����1-����
#define  CARDSTAT_TYPE_WFAIL 		3  		//��״̬:д��ʧ��0-����1-д��ʧ��

int F847351(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
//	::CoInitialize(NULL);				// ���SQL SERVER2000ʹ��

	int ret = 0;
	int error_code = 0;
	Data_Info data_info;
	memset(&data_info, 0, sizeof(data_info));

	char state_id[5] = "";
	int card_flag = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle, F_DAMT0, F_DAMT1, F_SPHONE, F_LVOL10, 0);

	memcpy(state_id, in_pack->spost_code, sizeof(state_id) - 1);	// ״̬	
	card_flag = in_pack->lvol9;										// ����־

	memcpy(data_info.physical_no, in_pack->sname, sizeof(data_info.physical_no));	// �ȿ�����������
	// �жϿ���־
	if ('1' == state_id[CARDSTAT_TYPE_REG])							// ע��
	{
		if ('1' == state_id[CARDSTAT_TYPE_LOST])					// ��ʧ
		{
			data_info.card_state = 3;
			out_pack->lvol10 = 0;
			PutRow(handle, out_pack, pRetCode, szMsg);
			return 0;
		}
		else if ('1' == state_id[CARDSTAT_TYPE_FREEZE])				// ����
		{
			data_info.card_state = 4;
			out_pack->lvol10 = 0;
			PutRow(handle, out_pack, pRetCode, szMsg);
			return 0;
		}
		else if ('1' == state_id[CARDSTAT_TYPE_WFAIL])				// д��ʧ�ܱ�ʾΪ����
			data_info.card_state = 1;
		else
		{
			if (3 == card_flag)										// �����ľɿ�
			{
				memcpy(data_info.old_physical_no, in_pack->sname, sizeof(data_info.old_physical_no));
				memset(data_info.physical_no, 0, sizeof(data_info.physical_no));
				data_info.card_state = 2;
			}
			else if ((4 == card_flag) || (2 == card_flag) || (-1 == card_flag))		// �������¿�, ���¿�, ���, �ⶳ����������, 
				data_info.card_state = 1;							
			else if (1 == card_flag)
				data_info.card_state = 2;							// ע����
			else 
			{
				NULL;
			}
		}
	}
	
	if ('2' == state_id[CARDSTAT_TYPE_REG])							// ע����
		data_info.card_state = 2;

	if ('3' == state_id[CARDSTAT_TYPE_REG])							// ����
	{
		if (3 == card_flag)											// �����ľɿ�					
		{
			memcpy(data_info.old_physical_no, in_pack->sname, sizeof(data_info.old_physical_no));
			memset(data_info.physical_no, 0, sizeof(data_info.physical_no));
			data_info.card_state = 2;
		}
		
		if (4 == card_flag)
			data_info.card_state = 1;								// ����Ϊ�������¿�
	}
	
	// ���붯̬��������ֶ�
	memcpy(data_info.classdept_name, in_pack->vsvarstr0, sizeof(data_info.classdept_name));
	memcpy(data_info.stuemp_no, in_pack->sname2, sizeof(data_info.stuemp_no));
	data_info.cut_id = in_pack->lvol6;
	data_info.cut_type = in_pack->lvol4;
	memcpy(data_info.cut_type_name, in_pack->vsvarstr1, sizeof(data_info.cut_type_name));
	memcpy(data_info.volume, in_pack->sholder_ac_no, sizeof(data_info.volume));
	memcpy(data_info.cut_name, in_pack->semail, sizeof(data_info.cut_name));
//	memcpy(data_info.show_id, in_pack->scust_no, sizeof(data_info.show_id));
//	data_info.card_id = in_pack->lvol2;
//	data_info.type_id = in_pack->lvol5;
//	data_info.cut_state = in_pack->lvol7;
//	data_info.area = in_pack->lvol8;
//	memcpy(data_info.main_id, in_pack->scust_auth, sizeof(data_info.main_id));
//	memcpy(data_info.state_id, in_pack->spost_code, sizeof(data_info.state_id));
//	memcpy(data_info.reg_time, in_pack->sphone3, sizeof(data_info.reg_time));
//	memcpy(data_info.can_time, in_pack->spager, sizeof(data_info.can_time));
//	memcpy(data_info.sex, in_pack->sstatus2, sizeof(data_info.sex));
//	memcpy(data_info.area_name, in_pack->scert_no, sizeof(data_info.area_name));
//	data_info.curBalance = in_pack->damt0;
//	data_info.frozenBalance = in_pack->damt1;
//	data_info.acc_current_state = in_pack->lvol10;
//	data_info.card_flag = in_pack->lvol9;
#ifdef _DEBUG
	g_LogFile.WriteLogEx(1001, "���׿���[%d]--�ͻ���[%d]--������[%s]--��״̬���[%d]--���[%d]--���[%d]", 
	in_pack->lvol2, data_info.cut_id, data_info.physical_no, data_info.card_state, data_info.cut_type, ++count);
#endif

	GetDataInfo(&data_info, &error_code);
	if (error_code == 0)
		out_pack->lvol10 = 10;
	else
		out_pack->lvol10 = 0;
	
	PutRow(handle, out_pack, pRetCode, szMsg);

	return 0;
}

#ifdef __cplusplus
}
#endif