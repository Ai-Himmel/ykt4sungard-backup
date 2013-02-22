#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H

#define CHARGE_TERMINAL			0x01			// �շ��ն�
#define MANAGE_CENTER			(0x01 << 1)		// ��������
#define SAVING_POS				(0x01 << 2)		// ��ֵ�ն�
#define DOOR_DEVICE				(0x01 << 3)		// �Ž�
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// ��֤�ն�
#define AREA_CONTROL			(0x01 << 5)		// �������
#define REMAIN_BIT_SEVEN		0				// ����
#define REMAIN_BIT_EIGHT		0				// ����

#pragma pack(1)
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
	BYTE work_mode;
	BYTE data_length[3];				// ���ݳ���
	BYTE check_crc[2];					// Ч���ֽ�
	FEE_RIGHT_NO fee_right_num[256];	// ���÷��ʵĸ���
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

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
#pragma pack()
//////////////////////////////////////////////////////////////////////////
typedef int (CALLBACK * LPSMT_ClearCard)();
typedef void (CALLBACK * LPProcessCallBack)(int step);
typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf,BYTE *key,long flag);
typedef int (CALLBACK* LPReadCardMainKey)(BYTE * main_key, short wantFlag, short * readFlag); 
typedef int (CALLBACK* LPInitNewCard)(int * err_code, const char* showcardno, LPProcessCallBack lpCallBack);
typedef void (CALLBACK* LPSetCardSectLength)(const int card_sect_length);
typedef int (CALLBACK* LPConnectMF)(int,int);
typedef int (CALLBACK* LPCloseMF)();
typedef int (CALLBACK* LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
typedef int (CALLBACK* LPSMT_AutoDll)(unsigned char *ucWorkingKey);
typedef int (CALLBACK* LPReadCardBlock)(int startSect,int endSect,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPRefineCard)(int *err_code, LPProcessCallBack lpFunc);
typedef int (CALLBACK *LPResetAuthCard)(int * err_code,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPReadWaterCardBlock)(int startSect, int endSect
									 ,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK *LPInitNewCollectionCard)(int *err_code, LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPRefineWaterCard)(int *err_code, LPProcessCallBack lpFunc);
typedef int (CALLBACK *LPInitNewFeeRateCard)(int *err_code, LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPPublishFeeRateCard)(FEE_RATE_CARD_INFO *fee_rate_card_info);
typedef int (CALLBACK *LPReadCollectCardInfo)(FEE_RATE_CARD_INFO *fee_rate_card_info);
typedef int (CALLBACK *LPCollectionCardReceiveData)(int *err_code, COLLECT_BALANCE collect_balance[90], int *collect_count);
typedef int (CALLBACK *LPSMT_ReadAuthorWorkKeyAndFlag)(BYTE auth_work_key[8], BYTE *flag);
typedef int (CALLBACK* LPSMT_LoginSJCard)(int school_index, short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPSMT_CheckCard)(int in_school_index, int *out_school_index);
typedef int (CALLBACK* LPSMT_RefineOldCard)(int blk_flag, int school_index, TPublishCard *CardInfo);
typedef int (CALLBACK* LPInitNewCard2)(int *err_code, const char* showcardno, int school_index);
//////////////////////////////////////////////////////////////////////////

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
extern LPSMT_ClearCard SMT_ClearCard;
extern LPReadCardMainKey ReadCardMainKey;
extern LPInitNewCard InitNewCard;
extern LPSetCardSectLength SetCardSectLength;
extern LPConnectMF ConnectMF;
extern LPCloseMF CloseMF;
extern LPReadCardPhyID ReadCardPhyID;
extern LPSMT_AutoDll SMT_AutoDll;
extern LPReadCardBlock ReadCardBlock;
extern LPRefineCard RefineCard;
extern LPResetAuthCard		ResetAuthCard;
extern LPReadWaterCardBlock ReadWaterCardBlock;
extern LPInitNewCollectionCard InitNewCollectionCard;
extern LPRefineWaterCard RefineWaterCard;
extern LPInitNewFeeRateCard InitNewFeeRateCard;
extern LPPublishFeeRateCard PublishFeeRateCard;
extern LPReadCollectCardInfo ReadCollectCardInfo;
extern LPCollectionCardReceiveData CollectionCardReceiveData;
extern LPSMT_ReadAuthorWorkKeyAndFlag SMT_ReadAuthorWorkKeyAndFlag;
extern LPSMT_LoginSJCard SMT_LoginSJCard;
extern LPSMT_CheckCard SMT_CheckCard;
extern LPSMT_RefineOldCard SMT_RefineOldCard;
extern LPInitNewCard2 InitNewCard2;
#endif // _CARDMAN_UTIL_H