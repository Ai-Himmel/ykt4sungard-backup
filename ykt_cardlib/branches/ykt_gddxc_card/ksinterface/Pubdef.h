// Pubdef.h
#pragma once

//enum ESAM_SLOT{ SAM1 = 1,						// SAM���۱��
//                SAM2 = 2
//};

// ����Ӳ���汾ʹ��
#define HD_DAMIN        0 // ������д������LCD��ʾ��
#define HD_SUOTIAN    1 // �����д��

// ����ѡ��
#define ONLY_ALL        0 // ��ֵ���Ѷ���
#define ONLY_PSAM       1 // ֻ������
#define ONLY_PKI        2   // ֻ�г�ֵ

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
	DWORD		dwTradeSeq;					// �ѻ�������ˮ��
	BYTE		ucLogicalID[8];					// Ʊ���߼�����
	DWORD		dwPhysicalID;					// Ʊ��������
	DWORD		dwLastDeviceID;					// �ϴν��׵��豸��
	BYTE		ucLastTime[7];					// �ϴν���ʱ��
	DWORD		dwDeviceID;						// ���ν����豸��
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

// ��Ʊ��ֵ���ݽṹ
typedef struct _CommTicket_Increase {
	BYTE	CommTicketType;						// ��Ʊ����
	BYTE	SetMealType;						// �ײ�����
	BYTE	SetMealLevel;						// �ײ͵���
	BYTE	StartDate[4];						// ��ʼ����
	BYTE	Counts[4];							// ����
	BYTE	Line1[6];							// ��·��1
	BYTE	Line2[6];							// ��·��2
	BYTE	Line3[6];							// ��·��3
}CommTicket_Increase_t, *pCommTicket_Increase_t;

typedef struct _CommTicket_Info{
	BYTE	LogicId[8];							// Ʊ���߼�����
	BYTE	PhyId[4];							// ������
	BYTE	Type;								// Ʊ������
	BYTE	StartDate[4];						// ��ʼ����
	DWORD	dwValue;							// �۸�
	BYTE	SysCounts[5];						// ϵͳ��ˮ��
	BYTE	ServerTime[7];						// ������ʱ��
	BYTE	Line1Name[20];						// ��·1����
	BYTE	Line2Name[20];						// ��·2����
	BYTE	Line3Name[20];						// ��·3����
	BYTE	IncCounts[4];						// ��ֵ����
}CommTicket_Info_t, *pCommTicket_Info_t;

typedef struct _CommTicket_Charge_Info{
	BYTE	SysCounts[5];						// ϵͳ��ˮ��
	BYTE	ChargeTime[7];						// ����ʱ��
	BYTE	AuthCode[4];						// ��Ȩ��
	BYTE	Flag;								// ������־
}CommTicket_Charge_Info, *pCommTicket_Charge_Info;

typedef struct _MT_Info_Block4
{
	BYTE	CityCode[2];	// ���д���2
	BYTE	TradeCode[2];	// ��ҵ����2
	BYTE	CardType;		// ������1
	BYTE	Marker_Ver;		// Ǯ����ʶ+�汾1
	BYTE	LogicId[4];		// �߼��������к� 4
	BYTE	AuthCode[4];	// ������֤�� 4
	BYTE	LifeTime[2];	// ��Ч�� 2	
}MT_Info_Block4_t;

typedef struct _MT_Info_Block21
{
	BYTE	CIDName[2];					// ֤�����ƴ���2
	BYTE	CIDUsefulLife[2];			// ֤����Ч��2 bcd
	BYTE	CIDCode[2];					// ���˻��豸����2 hex
	BYTE	CIDNum[10];					// ��Ч֤������	10 BCD
}MT_Info_Block21_t;

// �ѻ���Ʊ��Ϣ
typedef struct _MT_CommTicket_Info
{
	BYTE	Cycle1_StartDate[3];	// ����1��ֵ��Ч��	3	BCD��YYMMDD��
	BYTE	Cycle1_EndDate[3];		// ����1��ֵ��ֹ��	3	BCD��YYMMDD��
	BYTE	Cycle1_Flag;			// ����1ͨƱ��־	1	HEX
	
	BYTE	Cycle2_StartDate[3];	// ����2��ֵ��Ч��	3	BCD��YYMMDD��
	BYTE	Cycle2_EndDate[3];		// ����2��ֵ��ֹ��	3	BCD��YYMMDD��
	BYTE	Cycle2_Flag;			// ����2ͨƱ��־	1	HEX
	
	BYTE	RFU[2];					// ����	2	HEX
	
	BYTE	Cycle1_ChargeTime[2];	// ����1��ֵ����	2	HEX
	BYTE	Cycle1_ChargeCode[2];	// ����1��ֵ������	2	BCD
	BYTE	Cycle1_ChargeDate[3];	// ����1��ֵʱ��	3	BCD��YYMMDD��
	BYTE	Cycle1_LineCode[9];		// ����1��·���루������	9	BCD
	
	BYTE	Cycle2_ChargeTime[2];	// ����2��ֵ����	2	HEX
	BYTE	Cycle2_ChargeCode[2];	// ����2��ֵ������	2	BCD
	BYTE	Cycle2_ChargeDate[3];	// ����2��ֵʱ��	3	BCD��YYMMDD��
	BYTE	Cycle2_LineCode[9];		// ����2��·���루������	9	BCD
}MT_CommTicket_Info_t;

typedef struct _CommTicket_ReadInfo_Offline{
	DWORD					dwPhysicalID;	// Ʊ��������
	MT_Info_Block4_t		Block4;			// ���ڿ�4��Ϣ
	MT_Info_Block21_t		Block21;		// ���ڿ�21��Ϣ
	MT_CommTicket_Info_t	CommTickInfo;	// ��Ʊ��Ϣ 
	DWORD					dwBalance;		// ��Ʊ�˴�����λ����
	BYTE					Mac[4];			// MAC(��Ҫ���ݵ�У����)4
}CommTicket_ReadInfo_Offline_t, *pCommTicket_ReadInfo_Offline_t;

typedef struct _CommTicket_SignIn_Info{
	BYTE	SHID[8];			// ������ˮ��
	BYTE	SK[32];				// �Ự��Կ��ȡǰ16���ֽڣ���3DES��Կ
	BYTE	SERVER_TIME[6];		// ������ʱ��
}CommTicket_SignIn_Info_t, *pCommTicket_SignIn_Info_t;

typedef struct _CommTicket_Online_Info{
	BYTE	AdminLogicId[4];		// �����߼����� BCD
	BYTE	SysCounts[5];			// ϵͳ��ˮ�� BCD
	BYTE	Retval;					// ������ HEX
	WORD	wInfolen;				// ��Ʊ��Ϣ���� HEX ��λ��ǰ
	BYTE	Info[512];				// ��Ʊ��Ϣ(���ȿɱ�)
}CommTicket_Online_Info_t, *pCommTicket_Online_Info_t;

// ��Ʊ���۷ѽӿ�
typedef struct _CommTicket_Deduction_Struct{
	DWORD	dwAdminID;							// PKI����Ա����
	BYTE	LogicId[8];							// Ʊ���߼�����
	BYTE	PhyId[4];							// ������
	BYTE	Type;								// Ʊ������
	DWORD	dwValue;							// �۸�
	BYTE	SysCounts[5];						// ϵͳ��ˮ��
	BYTE	ChargeTime[7];						// ����ʱ��
	BYTE	IncCounts[4];						// ��ֵ����
}CommTicket_Deduction_Struct_t, *pCommTicket_Deduction_Struct_t;
