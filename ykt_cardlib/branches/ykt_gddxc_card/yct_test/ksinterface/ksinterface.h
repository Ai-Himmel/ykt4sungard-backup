#ifndef _KS_INTERFACE_H_
#define _KS_INTERFACE_H_

#include <windows.h>
#include "Pubdef.h"

#pragma pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				
	unsigned char ucCertificateNo[21];		
	unsigned char ucDepartmentNo[11];		
	unsigned char ucIdentifyNo[5];			
	unsigned char ucSexNo[2];				
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					
	unsigned char ucLibraryNo[21];			
	int Money;								
	unsigned char isFormat;					
}TPublishCard;

typedef struct
{
	int price1;
	int price2;
	int price3;
	int balance;
}WATER_PACK_INFO3;

#pragma pack()

#ifndef CARDAPI
#define CARDAPI __stdcall
#endif

#define DCLR_DLLFUNC(p,r,name,arg) \
	typedef r (__stdcall * LP##p##name) arg; \
	extern LP##p##name p##name

#define DEF_DLLFUNC(p,name) \
	LP##p##name p##name = NULL

#define LOAD_DLLFUNC(handle,p,name) do { \
	p##name = (LP##p##name)GetProcAddress(handle,#name); \
	if (NULL == p##name) \
	return -1; } while(0)

#define DCLR_CARD_DLLFUNC(r,name,arg) DCLR_DLLFUNC(Card,r,name,arg)
#define DEF_CARD_DLLFUNC(name) DEF_DLLFUNC(Card,name)
#define LOAD_CARD_DLLFUNC(h,name) LOAD_DLLFUNC(h,Card,name)

//#define DCLR_YCT_DLLFUNC(r,name,arg) DCLR_DLLFUNC(YCT,r,name,arg)
#define DCLR_YCT_DLLFUNC(r,name,arg) \
	typedef r (* LPYCT##name) arg; \
	extern LPYCT##name YCT##name

#define DEF_YCT_DLLFUNC(name) DEF_DLLFUNC(YCT,name)
#define LOAD_YCT_DLLFUNC(h,name) LOAD_DLLFUNC(h,YCT,name)

DCLR_CARD_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_CARD_DLLFUNC(int,CloseMF,());
DCLR_CARD_DLLFUNC(int,Load_Dll,());
DCLR_CARD_DLLFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_CARD_DLLFUNC(int,ReadCardNO,(int CardNo[1]));
DCLR_CARD_DLLFUNC(int,ReadBalance,(int nPacketNo,int *nBalance,int *nCnt));
DCLR_CARD_DLLFUNC(int,SMT_SetNormalFlagByBlkVerion,(char *blkversion));
DCLR_CARD_DLLFUNC(int,SMT_WritePersonalPassword,(unsigned char newpwd[3]));
DCLR_CARD_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_CARD_DLLFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));

DCLR_CARD_DLLFUNC(int,SMT_TransWaterPacket,(int main_money,WATER_PACK_INFO3* info));
DCLR_CARD_DLLFUNC(int,SMT_ReadWaterPackInfo2,(WATER_PACK_INFO3* info));
DCLR_CARD_DLLFUNC(int,SMT_WriteWaterPackInfo2,(WATER_PACK_INFO3* info));
DCLR_CARD_DLLFUNC(int,ReadCardInfo,(TPublishCard *pc));
DCLR_CARD_DLLFUNC(int,SMT_ReadWaterPackInfo_XT,(WATER_PACK_INFO3* info));
DCLR_CARD_DLLFUNC(int,SMT_TransWaterPacket_XT,(int main_money,WATER_PACK_INFO3* info));
DCLR_CARD_DLLFUNC(int,JD2XT_Card,());
DCLR_CARD_DLLFUNC(int,XT2JD_Card,());
DCLR_CARD_DLLFUNC(int,SMT_GetCOMHandle,(void));

//////////////////////////////////////////////////////////////////////////
// 羊城通部分
DCLR_YCT_DLLFUNC(int,ConfigParamters,(char * lpAddrServer, int nPortHost,					// 普通钱包服务器地址
								 char * lpCommTickAddrServer, int nCTPortHost,			// 月票钱包服务器地址
								 char * lpEplink_AddrServer, int nEplink_HostPort,		// 易票联后台服务器地址
								 char * lpDeviceID));

DCLR_YCT_DLLFUNC(int,Common_Initialize_RW,(const int nPort, int Baud, int nSamSlot, char * lpPKIPin, LPBYTE lpInitKey, int hdVersion, char * SvrCode, int Only,HANDLE Comm));
DCLR_YCT_DLLFUNC(int,Common_Destroy_RW,(const int nPort));
DCLR_YCT_DLLFUNC(int,QueryBalance,(const int nPort,PPURCHSEARCH pPurSearch));
DCLR_YCT_DLLFUNC(int,CashIncrease,(const int nPort, const DWORD dwValue, PPURCHASEINCREASE pIncrease, BOOL bMustCmp));


//


#endif // _KS_INTERFACE_H_

