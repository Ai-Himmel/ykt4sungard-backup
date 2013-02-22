#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_
#pragma once

#pragma pack(1)
typedef struct _hCustomerInfo 
{
	char szName[20 + 1];					// ��ϵ������
	char szStuempNo[20 + 1];			    // ѧ����
	char szSex[1 + 1];					    // �Ա�
	char szManId[20 + 1];					// ���֤��
	char szClassDeptName[150 + 1];		    // ��������
	char szTel[20 + 1];						// ��ϵ�绰
	int  nMendFeeType;						// ҽ���շ�����(1Ϊ����, 2Ϊ�Է�)
	int  nCustomerId;						// �ͻ���
}CustomerInfo;

typedef struct _hTradeSerial 
{
	int	   nSerialNo;						// ��ˮ��
	int	   nOtherSerialNo;					// �ϴ�����ˮ��
	int    nSerialType;						// ��ˮ����
	int    nSerialState;					// ��ˮ״̬
	char   szOperateDate[10 + 1];			// ��������
	char   szOperateTime[8 + 1];			// ����ʱ��
	char   szCollectDate[10 + 1];			// �ɼ�����
	char   szCollectTime[8 + 1];			// �ɼ�ʱ��
	char   szEnteractDate[10 + 1];			// ��������
	char   szEnteractTime[8 + 1];			// ����ʱ��
	int    nMainDeviceId;					// �ϴ�����վ��ʶ
	int    nDeviceId;						// ���׷����豸��ʶ
	char   szDevphy999Id[8 + 1];			// �����豸����ID
	char   szShowId[10 + 1];				// ��ʾ����
	int    nCardId;							// ���׿���
	int    nPurseId;						// Ǯ����
	int	   nTradeCount;						// ���״���
	double dTradeFee;						// ���׽��
	double dInBalance;						// �뿨ֵ
	double dOutBalance;						// ����ֵ
	double dDepositFee;						// Ѻ����
	double dInFee;							// ������
	double dCostFee;						// ���ɱ���
	double dBoardFee;						// ����
	int    nCoustomerId;					// �ͻ�ID��
	char   szOperCode[10 + 1];				// ����Ա��
	char   szOutAccountId[16 + 1];			// �����ʺ�
	char   szInAccountId[16 + 1];			// �����ʺ�
	int    nSysId;							// �ⲿϵͳ��ʶ
	int    nTmark;							// ���ױ��
	int    nErrCode;						// ������
	int    nReviseSerialNo;					// ������ˮ��
}TradeSerial;
#pragma pack()

#endif