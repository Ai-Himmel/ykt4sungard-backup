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

int netfee_trans(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	char szAccount[20] = "";			
	char szPassword[12]="";				
	char szTradeTime[20]="";
	char szReqCode[4]="";
	char szResMes[12]="";
	double dRemainBalance = 0;
	double dTransferBalance = 0;
	int iSerino = 0;
	Cdeposit cdeposit;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	SetCol(handle,0);
	SetCol(handle, F_LVOL11, 0);

	if(in_pack->damt1 <= 0)
	{
		sprintf(szMsg,"���[%f]����",in_pack->damt1);
		g_LogFile.WriteLogEx(1004,"���[%f]Ϊ��",in_pack->damt1);
		out_pack->lvol11 = -16;
		goto L_RET;
	}
	iSerino = in_pack->lvol6;
	dTransferBalance = in_pack->damt1;		//ת�˽��	

	strncpy(szAccount,in_pack->scust_auth,sizeof(szAccount));		//�˺�,��ѧ��
	
	strncpy(szPassword,in_pack->sserial1,sizeof(szPassword));		//����

	strncpy(szReqCode,in_pack->sroom_no,sizeof(szReqCode));			//������ 008 or 009

	strncpy(szTradeTime,in_pack->scust_auth2,sizeof(szTradeTime));	//ת��ʱ��
	
	//1.��֯���ݰ�
	cdeposit.genMessage(szReqCode,szAccount,szPassword,szTradeTime,dTransferBalance,iSerino);
	
	//2.���ͽ������ݰ�
	ret = cdeposit.send();
	if (ret < 0)
	{	
		strcpy(szMsg,"ͨѶ����");
		g_LogFile.WriteLogEx(1004,"���ͱ��Ĵ���,ret[%d]",ret);
		out_pack->lvol11 = -17;
		goto L_RET;
	}
	g_LogFile.WriteLogEx(1004,"���ͱ��ĳɹ�,ret[%d]",ret);

	ret = cdeposit.recv();
	if(ret <= 0)
	{
		strcpy(szMsg,"ͨѶ����");
		if (ret == 0)
			g_LogFile.WriteLogEx(1004,"���ձ��ĳ�ʱ");
		else
			g_LogFile.WriteLogEx(1004,"���ձ��Ĵ���,ret[%d]",ret);
		out_pack->lvol11 = -17;
		goto L_RET;
	}
	//3.�������ݰ�
	ret = cdeposit.parseMessage(dRemainBalance,szResMes);
	if (ret < 0)
	{
		if (ret == -1)
		{
			strcpy(szMsg,"����У������һ��");
			g_LogFile.WriteLogEx(1004,"����У�����");
			out_pack->lvol11 = -17;
		}
		else if(ret == -2)
		{
			if(strncmp(szResMes,"E15",3) == 0)
				strcpy(szMsg,"�˺Ż��������");
			else
				sprintf(szMsg,"��������[%s]",szResMes);
			g_LogFile.WriteLogEx(1004,"�����շѴ������,��Ӧ����[%s]",szResMes);
			out_pack->lvol11 = -18;
		}
		else
			g_LogFile.WriteLogEx(1004,"�����շѽ��[%f]����",dRemainBalance);
		
		goto L_RET;
	}
	
	//	out_pack->damt3 = dRemainBalance;		// �����շ�ʣ�����
	//Ϊ�˺���ϵͳ����
	if(strncmp(szReqCode,"008",3) == 0)
		out_pack->lvol11 = 1;
	else
		out_pack->lvol11 = 0;

L_RET:
	PutRow(handle, out_pack, pRetCode, szMsg);
	return 0;
}


#ifdef __cplusplus
}
#endif
