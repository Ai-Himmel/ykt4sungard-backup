#ifndef _CARDMAN_UTIL_H
#define _CARDMAN_UTIL_H

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
	BYTE work_mode;
	BYTE data_length[3];				// 数据长度
	BYTE check_crc[2];					// 效验字节
	FEE_RIGHT_NO fee_right_num[256];	// 设置费率的个数
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						//用户卡使用权限类型（1--254）
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				//职务代码
	unsigned char ucCertificateNo[21];		//证件号码
	unsigned char ucDepartmentNo[11];		//部门编号
	unsigned char ucIdentifyNo[5];			//身份代码
	unsigned char ucSexNo[2];				//性别代码
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					//卡密码
	unsigned char ucLibraryNo[21];			//图书证号
	int Money;								//金额（分）
	unsigned char isFormat;					//是否格式化第一扇区
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