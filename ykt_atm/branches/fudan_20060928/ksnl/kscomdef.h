#ifndef _KSCOMDEF_H_
#define _KSCOMDEF_H_

// 水控钱包里的信息
#pragma pack(1)
typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

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

// 卡标志
#define WATER_AUTH_CARD 1                  // 授权卡
#define WATER_COMMON_CARD 2				   // 通用卡
#define WATER_CLEAR_CARD 3				   // 清零卡
#define WATER_NEW_CARD 4                   //  	
#define WATER_FIXED_CARD 5                 // 定点卡

#define DCLR_KSFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_KSFUNC(name) \
	LP##name name = NULL;	\

#define LOAD_KSFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
	return -1;

DCLR_KSFUNC(int,Load_Dll,());
DCLR_KSFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_KSFUNC(int,SMT_PacketAddMomey,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,SMT_PacketDelMomey,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,ReadBalance,(int nPacketNo,int nBalance[1],int nCnt[1]));
DCLR_KSFUNC(int,ReadCardNO,(int nCardNo[1]));
DCLR_KSFUNC(int,SMT_SetBlackCardFlag,());
DCLR_KSFUNC(int,ConnectMF,(int port, int baud));
DCLR_KSFUNC(int,CloseMF,());
DCLR_KSFUNC(int,ReadSerial,(unsigned char* serial));
DCLR_KSFUNC(int,SMT_SetNormalFlag,());
DCLR_KSFUNC(int,SMT_WritePersonalPassword,(unsigned char newpwd[3]));
DCLR_KSFUNC(int,SMT_ReadWaterPackInfo,(WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_WriteWaterPackInfo,(WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_InitWaterInfo,(const WATER_PACK_INFO* info));
DCLR_KSFUNC(int,SMT_WaterNewAuthCard,());
DCLR_KSFUNC(int,UpdateCardInfo,(TPublishCard *CardInfo));
DCLR_KSFUNC(int,ReadInfoFromCard,(TPublishCard *pc));

#endif