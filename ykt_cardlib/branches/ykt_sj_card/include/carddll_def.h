#ifndef _CARDDLL_DEF_H_
#define _CARDDLL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif 
#pragma pack(1)

#ifndef WIN32
#ifndef DWORD
#define DWORD int
#endif

#ifndef WORD
#define WORD short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif
	
#ifndef ULONG
#define ULONG unsigned long
#endif
#else
#include <windows.h>
#endif

typedef struct               
{
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char CardNo[8];				//�û������׿���
	unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
	int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
	unsigned char ucName[9];				//����
	unsigned char ucDutyNo[9];				//ְ�����
	unsigned char ucCertificateNo[21];		//֤������
	unsigned char ucDepartmentNo[11];		//���ű��
	unsigned char ucIdentifyNo[5];			//��ݴ���
	unsigned char ucSexNo[2];				//�Ա����
	unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
	unsigned char ucPwd[6];					//������
	unsigned char ucLibraryNo[21];			//ͼ��֤��
	int Money;								//���֣�
	unsigned char isFormat;					//�Ƿ��ʽ����һ����
}TPublishCard;

typedef struct
{
		DWORD RemainMoney;			// ����Ǯ�����
		WORD DealTimes;				// �û���������ˮ��
		BYTE DealYear;				// ��������
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// �ۼƽ��״���(��ǰʱ�����)
		BYTE DealTimes_CurDay;		// �ۼƽ��״���(������)
} LOOPPURSEINFO ,*LPLOOPPURSEINFO;

typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

/******************************************************/
// ���ʽṹ
/******************************************************/
typedef struct  
{
	BYTE time_ladder[1];				// ʱ�����
	BYTE deduct_time[1];				// �۷ѵĵ�λʱ�䣬����Ϊ��λ
	BYTE deduct_fee[1];					// �۷ѵĵ�λ���Է�Ϊ��λ
}FEE_RATE;

/******************************************************/
// ��ǰȨ�޵ķ��ʸ���
/******************************************************/
typedef struct
{
	short right_flag;					// Ȩ�ޱ�־, 1��, 0�ر�
	short right_num;					// ���뵱ǰȨ���µķ��ʸ���
	FEE_RATE fee_rate[5];				// �������Ϊ5��, ��ʵ��һЩû���õ�
}FEE_RIGHT_NO;

/*******************************************************/
// ���ʿ��ṹ˵��
/*******************************************************/
typedef struct  
{
	BYTE water_card_flag[5];			// ˮ�ؿ���־
	char packet_num;					// ˮ��Ǯ����
	BYTE main_work_key[9];				// ��������Կ(����)
	BYTE packet_work_key[9];			// СǮ��������Կ(����)
	BYTE work_mode;						// ����ģʽ
	int water_packet_limit;				// ˮ��Ǯ���޶�
	int transfer_limit;					// ˮ��ת���޶�
	BYTE data_length[3];				// ���ݳ���
	BYTE check_crc[2];					// Ч���ֽ�
	FEE_RIGHT_NO fee_right_num[256];	// ���÷��ʵĸ���
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

/*******************************************************/
// �������ÿ��ṹ˵��
/*******************************************************/
typedef struct  
{
	int card_id;					// ���׿���
	int sum_elec_volume;			// �ܵ���
	int local_elec_volume;			// ���ε���
	int limit_elec_power;			// ������ݹ���
	int alarm_elec_volume;			// ������ʾ����
	int brake_elec_volume;			// ��բ����
}ELEC_VOLUME_CARD_INFO;

/*******************************************************/
// У԰���ṹ˵��
/*******************************************************/
typedef struct _CardInfo 
{
	int 	 card_id;			//���׿���
	int 	 customer_id;		//�ͻ���
	char     physical_no[9];	//������
	char     state_id[5];		//��״̬
	char     password[33];		//������
} CardInfo;

/*******************************************************/
// �ͻ���Ϣ�ṹ˵��
/*******************************************************/
typedef struct _CutInfo 
{
	int 	 customer_id;				//�ͻ���
	char 	 cut_name[21];				//�ͻ�����
	char     classdept_no[11];			//���ű��
	char     class_no[11];				//�༶
	char     classdept_name[151];		//��ϵ�˲��Ż��߰༶����
} CutInfo;

/*******************************************************/
// ��ȡ���Լ��ͻ���Ҫ��Ϣ����
/*******************************************************/
typedef struct _DataInfo              
{
	int      cut_id;                //�ͻ�ID��      
	char	 cut_name[21];			//�ͻ�����
	char     class_no[11];			//�༶
	char     classdept_no[11];		//���ű��
	char 	 classdept_name[151];	//��ϵ�˲��Ż��߰༶����
	char     password[33];			//������, ��ʱ��Ϊ�����ֶ�
	char     state_id[5];			//��״̬, �����ֶ�
} DataInfo;

/*******************************************************/
// �ɽ���ѧ�ǲ�ͬѧУ��¼��Կ
/*******************************************************/
typedef struct _SJSector
{
	unsigned char card_flag;
	unsigned char card_key[7];
}SJSector;

static struct SJCard              
{
	SJSector sector[16];
}SJCard[] = 
{
	// ������ѧ, SJCard[0]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x52, 0x48}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x22, 0x96}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD3, 0x26}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA3, 0x60}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x13, 0x98}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB4, 0x40}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x64, 0x86}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA5, 0x36}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE5, 0x90}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA6, 0x48}},		// sector[10].card_key, ����10
			{0, {0xED, 0xDD, 0xDD, 0xAB, 0xB7, 0x10}},		// sector[11].card_key, ����11
			{0, {0xED, 0xDD, 0xDD, 0xDE, 0xF7, 0x76}},		// sector[12].card_key, ����12
			{0, {0xED, 0xDD, 0xDD, 0xBF, 0xA8, 0x46}},		// sector[13].card_key, ����13
			{0, {0xED, 0xDD, 0xDD, 0xEC, 0xA9, 0x20}},		// sector[14].card_key, ����14
			{0, {0xED, 0xDD, 0xDD, 0xCE, 0xF9, 0x98}}		// sector[15].card_key, ����15		
		}
	},
	// ����������ѧ, SJCard[1]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x53, 0x02}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x23, 0x50}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD3, 0x80}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA4, 0x14}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x14, 0x52}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB4, 0x94}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x65, 0x40}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA5, 0x90}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE6, 0x44}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA7, 0x02}},		// sector[10].card_key, ����10
			{0, {0xED, 0xDD, 0xDD, 0xAB, 0xB7, 0x64}},		// sector[11].card_key, ����11
			{0, {0xED, 0xDD, 0xDD, 0xDE, 0xF8, 0x30}},		// sector[12].card_key, ����12
			{0, {0xED, 0xDD, 0xDD, 0xBF, 0xA9, 0x00}},		// sector[13].card_key, ����13
			{0, {0xED, 0xDD, 0xDD, 0xEC, 0xA9, 0x74}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x10, 0x52}}		// sector[15].card_key, ����15
		}
	},
	// �Ϻ����̼�����ѧ, SJCard[2]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x53, 0x62}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x24, 0x10}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD4, 0x40}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA4, 0x74}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x15, 0x12}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB5, 0x54}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x66, 0x00}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA6, 0x50}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE7, 0x04}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA7, 0x62}},		// sector[10].card_key, ����10
			{0, {0xED, 0xDD, 0xDD, 0xAB, 0xB8, 0x24}},		// sector[11].card_key, ����11
			{0, {0xED, 0xDD, 0xDD, 0xDE, 0xF8, 0x90}},		// sector[12].card_key, ����12
			{0, {0xED, 0xDD, 0xDD, 0xBF, 0xA9, 0x60}},		// sector[13].card_key, ����13
			{0, {0xDD, 0xDD, 0xDE, 0xCA, 0x10, 0x34}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x11, 0x12}}		// sector[15].card_key, ����15
		}
	},
	// �Ϻ�������ѧ, SJCard[3]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x54, 0x28}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x24, 0x76}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD5, 0x06}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA5, 0x40}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x15, 0x78}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB6, 0x20}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x66, 0x66}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA7, 0x16}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE7, 0x70}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA8, 0x28}},		// sector[10].card_key, ����10
			{0, {0xED, 0xDD, 0xDD, 0xAB, 0xB8, 0x90}},		// sector[11].card_key, ����11
			{0, {0xED, 0xDD, 0xDD, 0xDE, 0xF9, 0x56}},		// sector[12].card_key, ����12
			{0, {0xDD, 0xDD, 0xDB, 0xFA, 0x10, 0x26}},		// sector[13].card_key, ����13
			{0, {0xDD, 0xDD, 0xDE, 0xCA, 0x11, 0x00}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x11, 0x12}}		// sector[15].card_key, ����15
		}
	},
	// �Ϻ�����ó��ѧԺ, SJCard[4]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x55, 0x00}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x25, 0x48}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD5, 0x78}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA6, 0x12}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x16, 0x50}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB6, 0x92}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x67, 0x38}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA7, 0x88}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE8, 0x42}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA9, 0x00}},		// sector[10].card_key, ����10
			{0, {0xED, 0xDD, 0xDD, 0xAB, 0xB9, 0x62}},		// sector[11].card_key, ����11
			{0, {0xDD, 0xDD, 0xDD, 0xEF, 0x10, 0x28}},		// sector[12].card_key, ����12
			{0, {0xDD, 0xDD, 0xDB, 0xFA, 0x10, 0x98}},		// sector[13].card_key, ����13
			{0, {0xDD, 0xDD, 0xDE, 0xCA, 0x11, 0x72}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x12, 0x50}}		// sector[15].card_key, ����15
		}
	},
	// �Ϻ����Ż��ѧԺ, SJCard[5]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x55, 0x78}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x26, 0x26}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD6, 0x56}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA6, 0x90}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x17, 0x28}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB7, 0x70}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x68, 0x16}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA8, 0x66}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0xE9, 0x20}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0xA9, 0x78}},		// sector[10].card_key, ����10
			{0, {0xDD, 0xDD, 0xDA, 0xBB, 0x10, 0x40}},		// sector[11].card_key, ����11
			{0, {0xDD, 0xDD, 0xDD, 0xEF, 0x11, 0x06}},		// sector[12].card_key, ����12
			{0, {0xDD, 0xDD, 0xDB, 0xFA, 0x11, 0x76}},		// sector[13].card_key, ����13
			{0, {0xDD, 0xDD, 0xDE, 0xCA, 0x12, 0x50}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x13, 0x28}}		// sector[15].card_key, ����15
		}
	},
	// �����Ӿ�, SJCard[6]
	{
		// sector
		{
			{0, {0xDD, 0xDD, 0xD1, 0x43, 0x56, 0x62}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xDD, 0xDD, 0xD6, 0x53, 0x27, 0x10}},		// sector[2].card_key, ����2
			{0, {0xDD, 0xDD, 0xDA, 0xBC, 0xD7, 0x40}},		// sector[3].card_key, ����3
			{0, {0xDD, 0xDD, 0xDF, 0xDE, 0xA7, 0x74}},		// sector[4].card_key, ����4
			{0, {0xDD, 0xDD, 0xD1, 0x11, 0x18, 0x12}},		// sector[5].card_key, ����5
			{0, {0xDD, 0xDD, 0xDE, 0xDA, 0xB8, 0x54}},		// sector[6].card_key, ����6
			{0, {0xDD, 0xDD, 0xD9, 0x87, 0x69, 0x00}},		// sector[7].card_key, ����7
			{0, {0xDD, 0xDD, 0xDC, 0xDE, 0xA9, 0x50}},		// sector[8].card_key, ����8
			{0, {0xDD, 0xDD, 0xDC, 0xEE, 0x10, 0x04}},		// sector[9].card_key, ����9
			{0, {0xDD, 0xDD, 0xDC, 0xAA, 0x10, 0x62}},		// sector[10].card_key, ����10
			{0, {0xDD, 0xDD, 0xDA, 0xBB, 0x11, 0x24}},		// sector[11].card_key, ����11
			{0, {0xED, 0xDD, 0xDD, 0xDE, 0x11, 0x90}},		// sector[12].card_key, ����12
			{0, {0xDD, 0xDD, 0xDB, 0xFA, 0x12, 0x60}},		// sector[13].card_key, ����13
			{0, {0xDD, 0xDD, 0xDE, 0xCA, 0x13, 0x34}},		// sector[14].card_key, ����14
			{0, {0xDD, 0xDD, 0xDC, 0xEF, 0x14, 0x12}}		// sector[15].card_key, ����15
		}	
	},
	// default, SJCard[7]
	{
		{
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[2].card_key, ����2
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[3].card_key, ����3
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[4].card_key, ����4
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[5].card_key, ����5
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[6].card_key, ����6
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[7].card_key, ����7
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[8].card_key, ����8
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[9].card_key, ����9
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[10].card_key, ����10
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[11].card_key, ����11
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[12].card_key, ����12
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[13].card_key, ����13
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}},		// sector[14].card_key, ����14
			{0, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}}		// sector[15].card_key, ����15
		}
	},
	// default2, SJCard[8]
	{
		{
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[0].card_key, ����0
			{0, {0xED, 0xF7, 0x45, 0x07, 0x20, 0x4E}},		// sector[1].card_key, ����1		
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[2].card_key, ����2
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[3].card_key, ����3
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[4].card_key, ����4
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[5].card_key, ����5
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[6].card_key, ����6
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[7].card_key, ����7
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[8].card_key, ����8
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[9].card_key, ����9
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[10].card_key, ����10
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[11].card_key, ����11
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[12].card_key, ����12
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[13].card_key, ����13
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}},		// sector[14].card_key, ����14
			{0, {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}}		// sector[15].card_key, ����15
		}
	}
};

// �ɽ���ѧ������ѧУ����1�����ĳ�ʼ��Կ
typedef struct _SJSector2
{
	unsigned char card_key[7];
}SJSector2;

static SJSector2 sector2[] = 
{
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC2, 0x70},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC3, 0x24},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC3, 0x84},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC4, 0x50},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC5, 0x22},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC6, 0x00},
	{0xDD, 0xDD, 0xDF, 0xAD, 0xC6, 0x84},
	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
};

typedef struct DongHua
{
	unsigned char card_right_type;
	unsigned char personal_id[10];
}DongHua;

#pragma pack()

//////////////////////////////////////////////////////////////////////////
// IMPLEMENT MACRO
#define CHARGE_TERMINAL			0x01			// �շ��ն�
#define MANAGE_CENTER			(0x01 << 1)		// ��������
#define SAVING_POS				(0x01 << 2)		// ��ֵ�ն�
#define DOOR_DEVICE				(0x01 << 3)		// �Ž�
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// ��֤�ն�
#define AREA_CONTROL			(0x01 << 5)		// �������
#define REMAIN_BIT_SEVEN		0				// ����
#define REMAIN_BIT_EIGHT		0				// ����

#define KS_ERR_EXIT						-1
#define KS_ERR_LOADLIBRARY				1001			
#define KS_ERR_LOADFUNC_ADDRESS			1002			
#define KS_ERR_GETVERSION				1003			
#define KS_ERR_NOINITFILE				1004
#define KS_ERR_NOLOCALEXE				1005
#define KS_ERR_PORTNOEXIST				1006
#define KS_ERR_OPENCOM					1007
#define KS_ERR_NOTOPENCOM				1008
#define KS_ERR_CLOSECOM					1009
#define KS_ERR_READAUTHCARD				1010
#define KS_ERR_CHANGECARDID				1011
#define KS_ERR_CHANGESHOWCARDID			1012
#define KS_ERR_READCARDINFO				1013
#define KS_ERR_CHANGESEPNO				1014
#define KS_ERR_INPUTWORKKEYLENGTH	    1015
#define KS_ERR_INITAUTHCARD				1016
#define KS_ERR_RESETAUTHCARD			1017
#define KS_ERR_INPUTSHOWIDLENGTH		1018
#define KS_ERR_NOMANAGEAUTHCARDFLAG		1019
#define KS_ERR_INPUTNULLFAILED			1020			
#define KS_ERR_INPUTZEROFAILED			1021			
#define KS_ERR_REFINECARDSECTOR			1022
#define KS_ERR_WRITECARDMONEY			1023
#define KS_ERR_WRTIECARDRIGHTTYPE		1024
#define KS_ERR_WRTIEDEADLINEDATE		1025
#define KS_ERR_WRTIEDPUBSECT			1026

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#ifdef NOUSE_MFC
#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return -1; } while(0)
#else
#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS);
#endif
	
//////////////////////////////////////////////////////////////////////////
// ERROR INFOMATION
static struct Err_Def 
{
	int err_code;
	char err_info[32];
}g_Err_Def[] = 
{
	{KS_ERR_LOADLIBRARY, "��ȡ��̬�����"},
	{KS_ERR_LOADFUNC_ADDRESS, "��ȡ������ַ����"},
	{KS_ERR_GETVERSION, "��ȡ��̬��汾����"},
	{KS_ERR_NOINITFILE, "û��ini�����ļ�"},
	{KS_ERR_NOLOCALEXE, "û�б���exe����"},
	{KS_ERR_PORTNOEXIST, "�˿ڲ�����"},
	{KS_ERR_OPENCOM, "�򿪴��ڴ���"},
	{KS_ERR_NOTOPENCOM, "û�д򿪴���"},
	{KS_ERR_CLOSECOM, "�رմ��ڴ���"},
	{KS_ERR_READAUTHCARD, "��ȡ��Ȩ������"},
	{KS_ERR_CHANGECARDID, "�޸Ľ��׿��Ŵ���"},
	{KS_ERR_CHANGESHOWCARDID, "�޸���ʾ���Ŵ���"},
	{KS_ERR_READCARDINFO, "��ȡ����Ϣ����"},
	{KS_ERR_CHANGESEPNO, "�޸�ѧ���Ŵ���"},
	{KS_ERR_INPUTWORKKEYLENGTH, "������Ȩ������Կ���ȳ���"},
	{KS_ERR_INITAUTHCARD, "��ʼ����Ȩ��ʧ��"},
	{KS_ERR_RESETAUTHCARD, "������Ȩ��ʧ��"},
	{KS_ERR_INPUTSHOWIDLENGTH, "������ʾ���ų��ȳ���"},
	{KS_ERR_REFINECARDSECTOR, "���տ�����ʧ��"},
	{KS_ERR_WRITECARDMONEY, "д�����ʧ��"},
	{KS_ERR_WRTIECARDRIGHTTYPE, "д��Ȩ�����ʧ��"},
	{KS_ERR_WRTIEDEADLINEDATE, "д����ֹ����ʧ��"},
	{KS_ERR_WRTIEDPUBSECT, "д��������ʧ��"},
	{KS_ERR_EXIT, "�޴��������Ϣ"}
};

//////////////////////////////////////////////////////////////////////////
// IMPORT FUNCTION
#ifndef CARDDLL_EXPORTS
DCLR_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_DLLFUNC(int,CloseMF,());
DCLR_DLLFUNC(int,SMT_ChangeShowCardNo,(unsigned char ucShowCardNo[5]));
DCLR_DLLFUNC(int,SMT_ChangeDealCardNo,(int nDealCardNo));
DCLR_DLLFUNC(int,SMT_ReadCardStateInfo,(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1]));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,SMT_AutoDll,(unsigned char *ucWorkingKey));
DCLR_DLLFUNC(int,ControlBuzzer,(void));
DCLR_DLLFUNC(int,ReadCardInfo,(TPublishCard *pc));
DCLR_DLLFUNC(int,SMT_ChangeCardNo,(unsigned char ucCardNo[20]));
DCLR_DLLFUNC(int,ProcessCallBack,(int step));
DCLR_DLLFUNC(int,InitNewAuthCard,(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,ResetNewAuthCard,(int * err_code, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,SMT_ReadAuthorWorkKeyAndFlag,(BYTE auth_work_key[8], BYTE *flag));
DCLR_DLLFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_DLLFUNC(int,ReadPacketInfo,( LPLOOPPURSEINFO LoopPurseInfo ));
DCLR_DLLFUNC(int,SMT_ReadPacketInfo,(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)); 
DCLR_DLLFUNC(int,ReadCardNO,(int CardNo[1]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_DLLFUNC(int,SMT_GetPacketInfo,(int nPacketNo, MONEY_PACK_INFO *pPackInfo));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,RefineCardSector,(int sector, unsigned char login_key[7]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney2,(int nPacketNo, int nMoney, int nCnt));
DCLR_DLLFUNC(int,SMT_ChangeCardRightType,(unsigned char ucCardRightType[1]));
DCLR_DLLFUNC(int,SMT_ChangeDeadLineDate,(unsigned char ucDeadLineDate[3]));
DCLR_DLLFUNC(int,SMT_ModifyDongHuaSector,(DongHua *dh));

#endif 

#ifdef __cplusplus
}
#endif

#endif