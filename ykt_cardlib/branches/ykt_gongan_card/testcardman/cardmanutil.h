#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H
//////////////////////////////////////////////////////////////////////////
// ���� cardman dll
// typedef void (CALLBACK * LPProcessCallBack)(int step);
// typedef void (* LPGetBlockData)(int sect,int block,BYTE buf[16]
// 							   ,BYTE key[6],long flag);
// 
// typedef int (CALLBACK *LPInitNewCard) (int * err_code,const char *showcardno
// 									   ,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPReadCardMainKey) (BYTE * main_key
// 										   ,short wantflag,short * readflag);
// typedef int (CALLBACK *LPRefineCard) (int * err_code,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPOpenCOM) (int port,long band);
// typedef int (CALLBACK *LPCloseCOM) ();
// typedef int (CALLBACK *LPResetAuthCard)(int * err_code,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPNewAuthCard)(BYTE main_key[8],short pri_sect
// 								   ,short pri_block,short pri_startpos
// 								   ,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
// typedef int (CALLBACK *LPReadCardBlock)(int startSect,int endSect,
// 										short block,LPGetBlockData lpFunc);
// typedef int (CALLBACK *LPSetCardMainKey)(BYTE key[8]);
// 
// int LoadCardManDLL();
// void FreeCardManDLL();
// 
// extern HINSTANCE hCardManDLL;
// 
// extern LPInitNewCard		InitNewCard;
// extern LPReadCardMainKey	ReadCardMainKey;
// extern LPRefineCard			RefineCard;
// extern LPOpenCOM			OpenCOM;
// extern LPCloseCOM			CloseCOM;
// extern LPResetAuthCard		ResetAuthCard;
// extern LPNewAuthCard		NewAuthCard;
// extern LPReadCardPhyID		ReadCardPhyID;
// extern LPReadCardBlock		ReadCardBlock;
// extern LPSetCardMainKey		SetCardMainKey;
//////////////////////////////////////////////////////////////////////////

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
	BYTE data_length[3];				// ���ݳ���
	BYTE check_crc[2];					// Ч���ֽ�
	FEE_RIGHT_NO fee_right_num[256];	// ���÷��ʵĸ���
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

#pragma pack()
//////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
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

#endif // _CARDMAN_UTIL_H