// Pubdef.h
#pragma once

//enum ESAM_SLOT{ SAM1 = 1,						// SAM���۱��
//                SAM2 = 2
//};

// ����Ӳ���汾ʹ��
#define HD_DAMIN        0 // ������д������LCD��ʾ��
#define HD_SUOTIAN    1 // �����д��


typedef struct _Purchase_Search {
	DWORD		dwPhysicalID;					// Ʊ��������
	BYTE		ucLogicalID[8];					// Ʊ���߼�����
	BYTE		ucCardType;						// Ʊ������
	WORD		wDeposite;						// Ʊ��Ѻ��
	BYTE		ucEndDate[2];					// Ʊ����Ч��
	BYTE		ucPSCert_Type[2];				// ����֤������
	BYTE		ucPSCert_EndDate[2];			// ����֤����Ч��
	WORD		wTs_SN;							// Ʊ�����׼���
	WORD		wMaxBalance;					// Ʊ������޶��λ��Ԫ
	DWORD		dwBalance;						// Ʊ������λ����
	BYTE		ucTs_Flag;						// Ʊ������״̬
}PURCHSEARCH, *PPURCHSEARCH;

/* ��ֵ���ݽṹ */
typedef struct _Purchase_Increase {
	BOOL				bVaild;					// ָʾ�����Ƿ���Ч
    DWORD               dwAdminID;				// �����߼�����
    DWORD               dwSysSeq;				// ϵͳ��ˮ��
    WORD				wStatus1;				// ����״̬
    WORD				wStatus2;				// Ʊ������״̬
    // Ʊ����ֵǰ����
    DWORD				dwPhysicalID;			// Ʊ��������
    BYTE		        ucLogicalID[8];			// Ʊ���߼�����
    BYTE		        ucCardType;				// Ʊ������
    WORD		        wDeposite;				// Ʊ��Ѻ��
    BYTE		        ucEndDate[2];			// Ʊ����Ч��
    BYTE		        ucPSCert_Type[2];		// ����֤������
    BYTE		        ucPSCert_EndDate[2];	// ����֤����Ч��
    WORD		        wTs_SN;					// Ʊ�����׼���
    WORD		        wMaxBalance;			// Ʊ������޶��λ��Ԫ
    DWORD				dwPreBalance;			// Ʊ����ֵǰ����λ����
    BYTE		        ucTs_Flag;				// Ʊ������״̬
    // Ʊ����ֵ������
    DWORD           dwSithBalance;				// ��ֵ��Ʊ�����,��λ����
}PURCHASEINCREASE, *PPURCHASEINCREASE;

typedef struct _Purchase_Prepare {
	DWORD		dwTradeSeq;						// �ѻ�������ˮ��
	BYTE		ucLogicalID[8];					// Ʊ���߼�����
	DWORD		dwPhysicalID;					// Ʊ��������
	DWORD		dwLastDeviceID;					// �ϴν��׵��豸��
	BYTE		ucLastTime[7];					// �ϴν���ʱ��
	BYTE		dwDeviceID;						// ���ν����豸��
	BYTE		ucThisTime[7];					// ���ν���ʱ��
	DWORD		dwValue;						// ���׽��
	DWORD		dwBalance;						// ���ν��׺�����
	BYTE		ucTradeType;					// ���ν�������
	DWORD		dwTradeCount;					// ���׼���
	DWORD		dwEntryDeviceID;				// ���ν�������豸���
	BYTE		ucEntryTime[7];					// ���ν����������ʱ��
	BYTE		ucAI;							// ������Ϣ
	BYTE		ucVC;							// У����
	DWORD		dwTAC;							// TAC��
}PURCHPREPARE, *PPURCHPREPARE;


typedef struct _Ticket_Lock {
	BYTE		ucTime[7];						// ���״���ʱ��
	BYTE		ucLogicalID[8];					// Ʊ���߼�����
	BYTE		ucPhysicalID[4];				// Ʊ��������
	BYTE		ucListType;						// ����������
}TICKETLOCK, *PTICKETLOCK;
