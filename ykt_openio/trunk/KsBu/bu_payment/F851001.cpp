/* --------------------------------------------
* ��������: F847307.cpp
* ��������: 2007-5-11
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: �����շ��ʻ���ѯ(�����������Խ�)
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
#include <string>
#include "PaymentProtocol.h"
#include "svrlink.h"
#include "bufunc.h"
extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851001(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szStuEmpNo[21] = "";
	char szAccSerOutOfDate[9] = "";
	double dRemainBalance = 0.0;
	double dOweBalanece = 0.0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	PaymentProtocol protocol;
	payment_request_t payment;

	
	ResetNormalCPack(&aPack, 0, 1);

	SetHeadCol(&aPack,0);
	SetHeadCol(&aPack,F_LSAFE_LEVEL,F_VSMESS, F_SCUST_LIMIT, F_SBANK_CODE,F_SBANK_ACC,
		F_SCUSTTYPES,F_LVOL1,F_SSTATION0,F_LVOL0,F_LVOL8,F_LSAFE_LEVEL2,F_SDATE3,F_STIME3,
		F_SPHONE3,F_SADDR,F_SEMP,0);

	
	protocol.begin_filed();
	protocol.add_field(in_pack->scust_limit);
	protocol.add_field(in_pack->sbank_code);
	protocol.add_field(in_pack->sbank_acc);
	protocol.add_field(in_pack->spager);
	protocol.add_field(in_pack->sall_name);
	protocol.add_int_field(in_pack->lwithdraw_flag);
	protocol.add_int_field(in_pack->lvol1);
	protocol.add_field(in_pack->vsvarstr0);
	if(protocol.final_add_field(payment.req,1))
	{
		out_pack->lsafe_level = PYM_INPUT_DATA;
		strcpy(out_pack->vsmess,"�����������");
		*pRetCode = PYM_INPUT_DATA;
		strcpy(szMsg,out_pack->vsmess);
		PutRow(handle, out_pack, pRetCode, szMsg);
		return -1;
	}
	else
	{
		payment.host = in_pack->sholder_ac_no2;
		payment.port = in_pack->lvol4;
		payment.timeout = in_pack->lsafe_level*1000;
		payment.protocol = &protocol;

		if(payment_process(&payment,1))
		{
			out_pack->lsafe_level = payment.retcode;
			strcpy(out_pack->vsmess,payment.retmsg.c_str());
			*pRetCode = payment.retcode;
			strcpy(szMsg,out_pack->vsmess);
			PutRow(handle, out_pack, pRetCode, szMsg);
			return -1;
		}
		else if(protocol.parse(payment.resp.c_str(),0))
		{
			out_pack->lsafe_level = PYM_RET_ERR;
			strcpy(out_pack->vsmess,"������ת������ʧ��");
			*pRetCode = PYM_RET_ERR;
			strcpy(szMsg,out_pack->vsmess);
			PutRow(handle, out_pack, pRetCode, szMsg);
			return -1;
		}
		else
		{
			
			
			// ���ױ�ʶ
			GET_STR_FIELD(protocol,1,out_pack->scust_limit);
			// ������
			GET_STR_FIELD(protocol,2,out_pack->sbank_code);
			// �տ�˺�
			GET_STR_FIELD(protocol,3,out_pack->sbank_acc);
			// �˺���Ϣ
			GET_STR_FIELD(protocol,4,out_pack->scusttypes);
			// ���ӽ��
			protocol.get_int_field(5,out_pack->lvol1);
			// ״̬��Ϣ
			GET_STR_FIELD(protocol,6,out_pack->sstation0);
			// ������Ϣ
			GET_STR_FIELD(protocol,7,out_pack->vsmess);
			// �ն˺�
			out_pack->lwithdraw_flag = in_pack->lwithdraw_flag;
			// �ն���ˮ��
			out_pack->lserial1=in_pack->lserial1;
			// ����
			out_pack->lvol0=in_pack->lvol0;
			// 
			//out_pack->lvol1=in_pack->lvol1;
			// �������
			out_pack->lvol8=in_pack->lvol8;
			// ˮ��Ǯ�����
			out_pack->lsafe_level2=in_pack->lsafe_level2;
			// ��������
			strcpy(out_pack->sdate3,in_pack->sdate3);
			// ����ʱ��
			strcpy(out_pack->stime3,in_pack->stime3);
			// ���ײο���
			strcpy(out_pack->sphone3,in_pack->sphone3);
			// ����Ա��
			strcpy(out_pack->semp,in_pack->semp);		
			// MAC�� ��Ϊ����ʹ��
			strcpy(out_pack->saddr,in_pack->saddr);
			// ����״̬
			if (strncmp(out_pack->sstation0,"1",1)==0)
			{
			out_pack->lsafe_level = 1;
			}
			else
			{
			out_pack->lsafe_level = 2;
			if(strlen(out_pack->vsmess) <= 0) // ����д�����Ϣ���򷵻���ʵ������Ϣ
				strcpy(out_pack->vsmess,"�Է��ʺŲ�ѯ����");

			*pRetCode = PYM_INPUT_DATA;
			PutRow(handle, out_pack, pRetCode, szMsg);
			return -1;

			}
		}
	}

	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif