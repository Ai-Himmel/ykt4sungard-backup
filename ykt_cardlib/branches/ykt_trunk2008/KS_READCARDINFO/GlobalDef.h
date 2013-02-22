#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#pragma once 

#include "..\include\carddll_def.h"
#include "..\include\pubfunc.h"

#define CHARGE_TERMINAL			0x01			// 收费终端
#define MANAGE_CENTER			(0x01 << 1)		// 管理中心
#define SAVING_POS				(0x01 << 2)		// 充值终端
#define DOOR_DEVICE				(0x01 << 3)		// 门禁
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// 认证终端
#define AREA_CONTROL			(0x01 << 5)		// 区域控制
#define REMAIN_BIT_SEVEN		0				// 保留
#define REMAIN_BIT_EIGHT		0				// 保留

#define  CARDSTAT_TYPE_REG	 		0     	//卡状态:挂失1-正常2-挂失
#define  CARDSTAT_TYPE_LOST	 		1     	//卡状态:挂失0-正常1-挂失
#define  CARDSTAT_TYPE_FREEZE		2     	//卡状态 冻结0-正常1-冻结
#define  CARDSTAT_TYPE_WFAIL 		3  		//卡状态:写卡失败0-正常1-写卡失败

#define  CARDFLAG_SHOWID	 				1     	// 显示卡号
#define  CARDFLAG_DEALID	 				2     	// 交易卡号
#define  CARDFLAG_SEPID						3     	// 学工号
#define  CARDFLAG_CUTID						4  		// 客户号
#define  CARDFLAG_PHYSICALID				5  		// 物理卡号

typedef int (__stdcall* LPConnectMF)(int port, int baud);
typedef int (__stdcall* LPCloseMF)(void);
typedef int (__stdcall* LPSMT_ControlBuzzer)(void);	// 硬件
typedef int (__stdcall* LPSMT_SleepCard)(void);
typedef int (__stdcall* LPReadCardInfo)(TPublishCard* pCI);
typedef int (__stdcall* LPGetLastErrMsg)(int ecode[1],char *errmsg);
typedef int (__stdcall* LPReadSerial)(unsigned char *serial);
typedef int (__stdcall* LPSMT_PacketDelMomey)(int nPacketNo,int nMoney);
//typedef int (__stdcall* LPSMT_PacketAddMoney)(int nPacketNo,int nMoney);
//typedef int (__stdcall* lp_WriteBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
//typedef int (__stdcall* lp_ReadBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
typedef int (__stdcall* LPReadBalance)(int nPacketNo,int nBalance[1],int nCnt[1]);
typedef int (__stdcall* LPSMT_ReadAuthCard2)(unsigned char ucWorkKey[8],short * flag);
typedef int (__stdcall* LPSMT_AutoDll)(unsigned char *ucWorkingKey);	
typedef int (__stdcall* LPLoad_WorkKey)(char *ascWorkKey);
typedef int (__stdcall* LPSMT_ReadCardMainKey)(int wantflag);
typedef int (__stdcall *LPSMT_AuthDevice)(int mode,int wantflag);
/*
typedef BOOL (__stdcall* LPSkinStart)(char* SkinFile  ,
char* CheckSum          ,
int   Type              ,
DWORD hInstance         ,
char* szResType ) ;
*/
//typedef void (__stdcall* LPSkinRemove)() ;       

typedef BOOL  (__stdcall* LPUSkinInit)(LPCTSTR lpszUserName,LPCTSTR lpszRegCode,LPCTSTR lpszFileName);
typedef BOOL  (__stdcall* LPUSkinExit)();

int LoadAppFace();
int LoadCardManDLL();
void FreeCardManDLL();

extern HINSTANCE hCardManDLL;
extern HINSTANCE hKS;

extern LPConnectMF			ConnectMF;
extern LPCloseMF			CloseMF;
extern LPSMT_ControlBuzzer	SMT_ControlBuzzer;
extern LPSMT_SleepCard		SMT_SleepCard;
extern LPReadCardInfo		ReadCardInfo;
extern LPGetLastErrMsg	    GetLastErrMsg;
extern LPReadSerial			ReadSerial;
extern LPSMT_PacketDelMomey SMT_PacketDelMomey;
extern LPReadBalance		ReadBalance;
extern LPSMT_ReadAuthCard2	SMT_ReadAuthCard2;
//extern LPSMT_AutoDll		SMT_AutoDll;
//extern LPLoad_WorkKey       Load_WorkKey;
extern LPUSkinInit			USkinInit;
extern LPUSkinExit			USkinExit;
extern LPSMT_AuthDevice     SMT_AuthDevice;

#endif	_GLOBAL_DEF_H_