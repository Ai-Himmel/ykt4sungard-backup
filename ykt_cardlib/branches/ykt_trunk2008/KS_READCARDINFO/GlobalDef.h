#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#pragma once 

#include "..\include\carddll_def.h"
#include "..\include\pubfunc.h"

#define CHARGE_TERMINAL			0x01			// �շ��ն�
#define MANAGE_CENTER			(0x01 << 1)		// ��������
#define SAVING_POS				(0x01 << 2)		// ��ֵ�ն�
#define DOOR_DEVICE				(0x01 << 3)		// �Ž�
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// ��֤�ն�
#define AREA_CONTROL			(0x01 << 5)		// �������
#define REMAIN_BIT_SEVEN		0				// ����
#define REMAIN_BIT_EIGHT		0				// ����

#define  CARDSTAT_TYPE_REG	 		0     	//��״̬:��ʧ1-����2-��ʧ
#define  CARDSTAT_TYPE_LOST	 		1     	//��״̬:��ʧ0-����1-��ʧ
#define  CARDSTAT_TYPE_FREEZE		2     	//��״̬ ����0-����1-����
#define  CARDSTAT_TYPE_WFAIL 		3  		//��״̬:д��ʧ��0-����1-д��ʧ��

#define  CARDFLAG_SHOWID	 				1     	// ��ʾ����
#define  CARDFLAG_DEALID	 				2     	// ���׿���
#define  CARDFLAG_SEPID						3     	// ѧ����
#define  CARDFLAG_CUTID						4  		// �ͻ���
#define  CARDFLAG_PHYSICALID				5  		// ������

typedef int (__stdcall* LPConnectMF)(int port, int baud);
typedef int (__stdcall* LPCloseMF)(void);
typedef int (__stdcall* LPSMT_ControlBuzzer)(void);	// Ӳ��
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