#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H
//////////////////////////////////////////////////////////////////////////
// 定义 cardman dll
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

#define CHARGE_TERMINAL			0x01			// 收费终端
#define MANAGE_CENTER			(0x01 << 1)		// 管理中心
#define SAVING_POS				(0x01 << 2)		// 充值终端
#define DOOR_DEVICE				(0x01 << 3)		// 门禁
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// 认证终端
#define AREA_CONTROL			(0x01 << 5)		// 区域控制
#define REMAIN_BIT_SEVEN		0				// 保留
#define REMAIN_BIT_EIGHT		0				// 保留

#pragma pack(1)
/******************************************************/
// 费率结构
/******************************************************/
typedef struct  
{
	BYTE time_ladder[1];				// 时间阶梯
	BYTE deduct_time[1];				// 扣费的单位时间，以秒为单位
	BYTE deduct_fee[1];					// 扣费的单位金额，以分为单位
}FEE_RATE;

/******************************************************/
// 当前权限的费率个数
/******************************************************/
typedef struct
{
	short right_flag;					// 权限标志, 1打开, 0关闭
	short right_num;					// 传入当前权限下的费率个数
	FEE_RATE fee_rate[5];				// 最大设置为5个, 其实有一些没有用到
}FEE_RIGHT_NO;

/*******************************************************/
// 费率卡结构说明
/*******************************************************/
typedef struct  
{
	BYTE water_card_flag[5];			// 水控卡标志
	char packet_num;					// 水控钱包号
	BYTE main_work_key[9];				// 主工作密钥(明文)
	BYTE packet_work_key[9];			// 小钱包工作密钥(明文)
	BYTE data_length[3];				// 数据长度
	BYTE check_crc[2];					// 效验字节
	FEE_RIGHT_NO fee_right_num[256];	// 设置费率的个数
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