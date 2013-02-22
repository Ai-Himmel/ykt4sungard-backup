/****************************************************************************
* 操作步骤
* 1、调用ComOpen打开串口
* 2、打开串口后，调用ReadCardInfo读卡信息
* 3、调用ComClose关闭串口
* 4、调用GetLastErrMsg来取得错误信息
****************************************************************************/
//所有的正常返回值都是0，如果不为0，可以调用GetLastErrMsg来取得错误信息

#ifndef __KSCARDCOM_H__
#define __KSCARDCOM_H__

#pragma once

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
extern HINSTANCE hKS_MH;

extern LPConnectMF			ConnectMF;
extern LPCloseMF			CloseMF;
extern LPSMT_ControlBuzzer	SMT_ControlBuzzer;
extern LPSMT_SleepCard		SMT_SleepCard;
extern LPReadCardInfo		ReadCardInfo;
extern LPGetLastErrMsg	    GetLastErrMsg;
extern LPReadSerial			ReadSerial;
extern LPSMT_PacketDelMomey SMT_PacketDelMomey;
//extern LPSMT_PacketAddMoney SMT_PacketAddMoney;
// extern lp_WriteBlock        WriteBlock;
// extern lp_ReadBlock         ReadBlock;
extern LPReadBalance		ReadBalance;
extern LPSMT_ReadAuthCard2	SMT_ReadAuthCard2;
extern LPSMT_AutoDll		SMT_AutoDll;
extern LPLoad_WorkKey       Load_WorkKey;
// extern LPSkinStart			SkinStart;
// extern LPSkinRemove			SkinRemove;
extern LPUSkinInit			USkinInit;
extern LPUSkinExit			USkinExit;

#endif