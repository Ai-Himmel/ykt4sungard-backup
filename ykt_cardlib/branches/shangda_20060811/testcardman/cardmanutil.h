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

// typedef int (CALLBACK *LPNewAuthCard)(BYTE main_key[8],short pri_sect
// 								   ,short pri_block,short pri_startpos
// 								   ,LPProcessCallBack lpCallBack);
// typedef int (CALLBACK *LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
// typedef int (CALLBACK *LPReadCardBlock)(int startSect,int endSect,
// 										short block,LPGetBlockData lpFunc);
// typedef int (CALLBACK *LPSetCardMainKey)(BYTE key[8]);

//发行卡结构定义
#pragma pack(1)

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
typedef void (CALLBACK * LPProcessCallBack)(int step);
typedef void (*LPGetBlockData)(int sect,int block,BYTE *buf,BYTE *key,long flag);
typedef int (CALLBACK* LPReadCardMainKey)(BYTE * main_key, short wantFlag, short * readFlag); 
typedef int (CALLBACK* LPInitNewCard)(int * err_code, const char* showcardno, LPProcessCallBack lpCallBack);
typedef int (CALLBACK* LPConnectMF)(int,int);
typedef int (CALLBACK* LPCloseMF)();
typedef int (CALLBACK* LPReadCardPhyID)(BYTE card_id[4],BYTE card_type[2]);
typedef int (CALLBACK* LPSMT_AutoDll)(unsigned char *ucWorkingKey);
typedef int (CALLBACK* LPReadCardBlock)(int startSect,int endSect,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPRefineCard)(int *err_code, LPProcessCallBack lpFunc);
typedef int (CALLBACK *LPResetNewAuthCard)(int * err_code,LPProcessCallBack lpCallBack);
typedef int (CALLBACK *LPSMT_CheckForCard)(void);
typedef int (CALLBACK* LPReadAuthCardBlock)(int startSect,int endSect,short block, LPGetBlockData lpFunc);
typedef int (CALLBACK* LPInitNewAuthCard)(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack);
typedef int (CALLBACK* LPPublishAuthCard)(TPublishCard *pc);
typedef int (CALLBACK* LPReadAuthCardInfo)(TPublishCard *pc);
typedef int (CALLBACK* LPSMT_ReadAuthorWorkKeyAndFlag)(BYTE auth_work_key[8], BYTE *flag);
typedef int (CALLBACK* LPSMT_ReadAuthBlackNameListVersion)(int *nflag, char *sVersion);
typedef int (CALLBACK* LPSMT_ModifyDeadLineDateAndFlag)(BYTE DeadLineDate[8], BYTE flag);
//////////////////////////////////////////////////////////////////////////

int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
extern LPReadCardMainKey ReadCardMainKey;
extern LPInitNewCard InitNewCard;
extern LPConnectMF ConnectMF;
extern LPCloseMF CloseMF;
extern LPReadCardPhyID ReadCardPhyID;
extern LPSMT_AutoDll SMT_AutoDll;
extern LPReadCardBlock ReadCardBlock;
extern LPRefineCard RefineCard;
// extern LPInitNewCard		InitNewCard;
// extern LPReadCardMainKey	ReadCardMainKey;
// extern LPRefineCard			RefineCard;
// extern LPOpenCOM			OpenCOM;
// extern LPCloseCOM			CloseCOM;
extern LPResetNewAuthCard	ResetNewAuthCard;
extern LPSMT_CheckForCard	SMT_CheckForCard;
extern LPReadAuthCardBlock  ReadAuthCardBlock;
extern LPInitNewAuthCard	InitNewAuthCard;
extern LPPublishAuthCard	PublishAuthCard;
extern LPReadAuthCardInfo	ReadAuthCardInfo;
// extern LPNewAuthCard		NewAuthCard;
// extern LPReadCardPhyID		ReadCardPhyID;
// extern LPReadCardBlock		ReadCardBlock;
// extern LPSetCardMainKey		SetCardMainKey;
extern LPSMT_ReadAuthorWorkKeyAndFlag SMT_ReadAuthorWorkKeyAndFlag;
extern LPSMT_ReadAuthBlackNameListVersion SMT_ReadAuthBlackNameListVersion;
extern LPSMT_ModifyDeadLineDateAndFlag SMT_ModifyDeadLineDateAndFlag;
#endif // _CARDMAN_UTIL_H