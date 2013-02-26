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
#include "PaymentProtocol.h"
#include "bufunc.h"
extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851002(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char dt[15];
	ST_CPACK aPack,sPack;
	ST_PACK *out_pack = &(aPack.pack);
	PaymentProtocol protocol;
	payment_request_t payment;
	int needret;

	ResetNormalCPack(&aPack, 0, 1);

	SetHeadCol(&aPack,0);
	SetHeadCol(&aPack,F_LSAFE_LEVEL,F_VSMESS, F_SCUST_LIMIT, F_SBANK_CODE,F_SBANK_ACC,
		F_SCUSTTYPES,F_LVOL1,F_SPHONE3,F_VSVARSTR0, 0);

	// [1000,2000)Ϊˮ��ת�˽��ף����ཻ�ײ���Ҫ��������ϵͳ�Ƿ񷵻سɹ�
	if(in_pack->lcert_code >=1000 && in_pack->lcert_code < 2000)
		needret = 0;
	else
		needret = 1;

	protocol.begin_filed();
	protocol.add_field(in_pack->scust_limit);
	protocol.add_field(in_pack->sbank_code);
	protocol.add_field(in_pack->sbank_acc);
	protocol.add_field(in_pack->sbank_acc2);
	protocol.add_int_field(in_pack->lvol2);
	protocol.add_field(in_pack->spager);
	protocol.add_field(in_pack->sall_name);
	protocol.add_field(in_pack->sbranch_code0);
	protocol.add_int_field(in_pack->lwithdraw_flag);
	protocol.add_int_field(in_pack->lvol7);
	protocol.add_int_field(in_pack->lvol1);
	sprintf(dt,"%s%s",in_pack->sdate0,in_pack->stime0);
	protocol.add_field(dt);
	protocol.add_field(in_pack->sphone3);
	protocol.add_int_field(in_pack->lcert_code);
	protocol.add_field(in_pack->sbank_code2);
	protocol.add_field(in_pack->vsvarstr0);

	if(protocol.final_add_field(payment.req,1))
	{
		out_pack->lsafe_level = PYM_INPUT_DATA;
		strcpy(out_pack->vsmess,"�����������");
		*pRetCode = out_pack->lsafe_level;
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


		if(payment_process(&payment,needret))
		{
			out_pack->lsafe_level = payment.retcode;
			strcpy(out_pack->vsmess,payment.retmsg.c_str());
			*pRetCode = payment.retcode;
			strcpy(szMsg,out_pack->vsmess);
			PutRow(handle, out_pack, pRetCode, szMsg);
			return -1;
		}
		else
		{
			if(needret)
			{
				if(protocol.parse(payment.resp.c_str(),0))
				{
					out_pack->lsafe_level = PYM_RET_ERR;
					strcpy(out_pack->vsmess,"�������������ݵĸ�ʽ����");
					*pRetCode = PYM_RET_ERR;
					strcpy(szMsg,out_pack->vsmess);
					PutRow(handle, out_pack, pRetCode, szMsg);
					return -1;
				}
				else
				{
					GET_STR_FIELD(protocol,1,out_pack->scust_limit);
					GET_STR_FIELD(protocol,2,out_pack->sbank_code);
					GET_STR_FIELD(protocol,3,out_pack->sbank_acc);
					GET_STR_FIELD(protocol,4,out_pack->scusttypes);
					protocol.get_int_field(5,out_pack->lvol1);
					GET_STR_FIELD(protocol,6,out_pack->sphone3);
					protocol.get_int_field(7,out_pack->lsafe_level);
					GET_STR_FIELD(protocol,8,out_pack->vsvarstr0);
					strcpy(out_pack->vsmess,out_pack->vsvarstr0);
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
				}
			}
			else
			{
				strcpy(out_pack->scust_limit,in_pack->scust_limit);
				strcpy(out_pack->sbank_code,in_pack->sbank_code);
				strcpy(out_pack->sbank_acc,in_pack->sbank_acc);
				strcpy(out_pack->scusttypes,"");
				out_pack->lvol1 = 0;
				strcpy(out_pack->sphone3,in_pack->sphone3);
				out_pack->lsafe_level = 0;
				strcpy(out_pack->vsvarstr0,"�ɹ�");
				strcpy(out_pack->vsmess,out_pack->vsvarstr0);
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
			}
		}
	}
	/*
	// ����ȷ������, aPack �е����ݷ��ظ��ͻ���
	memset(&aPack,0,sizeof aPack);
	ret = ExtCall(0,g_mainsvr_drtpno,g_mainsvr_func,0,2,&sPack,&aPack,NULL);
	if(ret >= 0)
	{
		if(aPack.head.retCode==0)
			g_LogFile.WriteLogEx(1000,"����ȷ�ϳɹ�,refno[%s]",in_pack->sphone3);
		else
		{
			g_LogFile.WriteLogEx(1000,"����ȷ��ʧ��,refno[%s],ret[%d]",in_pack->sphone3,aPack.head.retCode);
			return -1;
		}
	}
	else
	{
		g_LogFile.WriteLogEx(1000,"����ȷ��ʧ��,refno[%s],ret[%d],err[%d]"
			,in_pack->sphone3,ret,aPack.head.retCode);
		// ȷ��ʧ��
		return -1;

	}
	*/
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif