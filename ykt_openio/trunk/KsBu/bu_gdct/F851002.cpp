/* --------------------------------------------
* ��������: F851002.cpp
* ��������: 2009-12-16
* ��������: ����
* �汾��Ϣ: 1.0.0.0
* ������: ���г�ֵ�ʻ�֧��(�����������Խ�)
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
#include "bufunc.h"
#include "gdctpub.h"
#include "logfile.h"

extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851002(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	TRUSERID answer_handle;
	char request_data[512];
	char drtphandle[129];
	int req_len,offset,t;
	ST_CPACK aPack;
	ST_CPACK sPack;
	ST_PACK *out_pack = &(aPack.pack);
	gdct_msg_t mymsg;

	memcpy(&answer_handle,handle,sizeof answer_handle);
	memset(&mymsg,0,sizeof mymsg);
	strcpy(mymsg.msgtype,"DCCZ");
	strcpy(mymsg.msgcode,"000005");
	if(strlen(in_pack->sphone3)>4)
		mymsg.seqno = atoi(in_pack->sphone3+4);

	offset = 0;
	memcpy(mymsg.body,g_gdct_pswd,32); // ����
	offset += 32;
	memcpy(mymsg.body+offset,in_pack->sbank_code2,6);  // ֧����ʽ
	offset += 6;
	sprintf(mymsg.body+offset,"%010d",in_pack->lvol1); // ֧�����
	offset += 10;
	// �ֻ���
	memset(mymsg.body+offset,' ',13); 
	t = strlen(in_pack->sbank_acc2);
	if(t > 13)
	{
		*pRetCode = 1000;
		return -1;
	}
	memcpy(mymsg.body+offset+13-t,in_pack->sbank_acc2,t);
	offset += 13;
	// ���ײο���
	memset(mymsg.body+offset,' ',20);
	memcpy(mymsg.body+offset+6,in_pack->sphone3,14);
	offset += 20;
	// �������ֻ���
	memcpy(mymsg.body+offset,g_gdct_phone_num,13);
	offset += 13;
	mymsg.bodylen = offset;
	// drtphandle
	strcpy(drtphandle,in_pack->vsvarstr1);
	g_LogFile.WriteLogEx(1000,"[%s][%d]",in_pack->sbank_code2,in_pack->lvol1);




	PackCTRequest(&mymsg,request_data,req_len);
	// �������
	ret = CTSendAndRecv(request_data,req_len,&mymsg,g_timeout);
	
	// ����̨ȷ��
	ResetNormalCPack(&sPack,0,1);
	sPack.head.RequestType = 850005;
	SetHeadCol(&sPack,F_LVOL0,F_LBANK_ACC_TYPE,F_SPHONE2,F_SPHONE3,F_SHOLDER_AC_NO,
		F_LVOL1,F_LVOL2,F_VSMESS,F_SBANK_ACC,0);
	sPack.pack.lbank_acc_type = 255;
	strcpy(sPack.pack.sphone3,in_pack->sphone3);
	if(ret!=0)
	{
		sPack.pack.lvol0 = ret;
		strcpy(sPack.pack.vsmess,"ͨѶ����");
	}
	else
	{
		// DEBUG
		strcpy(mymsg.respcode,"0000");
		sPack.pack.lvol0 = atoi(mymsg.respcode);
		TranslateErrMsg(mymsg.respcode,sPack.pack.vsmess);
		if(strncmp(mymsg.respcode,"0000",4)==0)
		{
			// ���׳ɹ�
			offset = 0;
			GetRespDataAsString(&mymsg,22,10,sPack.pack.sphone2); // ѶԴ��ˮ��
			offset += 32;
			GetRespDataAsString(&mymsg,offset,14,sPack.pack.sholder_ac_no); // ѶԴ����ʱ��
			offset += 14;
			GetRespDataAsString(&mymsg,offset,16,sPack.pack.sbank_acc); // �����̻��˻����
			offset += 16;
			GetRespDataAsInteger(&mymsg,offset,16,t); // ��ֵ�˻����
			sPack.pack.lvol2 = t;
			offset += 16;
			g_LogFile.WriteLogEx(1000,"֧���ɹ�,refno[%s]recvno[%s],bala[%s]",sPack.pack.sphone3
				,sPack.pack.sphone2,sPack.pack.sbank_acc);
		}
	}
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
	// ���ͻ���Ӧ��
	ResetNormalCPack(&sPack,0,1);
	//memcpy(sPack.head.ParmBits,aPack.head.ParmBits,sizeof sPack.head.ParmBits);
	memcpy(&(sPack.pack),&(aPack.pack),sizeof sPack.pack);
	//g_pSvrLink->SetAnswerMode(AM_CONFIRM);
	//SetTransHandle(&answer_handle,drtphandle);
	//AnswerDataEx(&answer_handle,&sPack,NULL,0,szMsg);
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle,&(sPack.pack),pRetCode,szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif