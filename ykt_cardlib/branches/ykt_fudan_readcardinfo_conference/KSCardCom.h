/****************************************************************************
* ��������
* 1������ComOpen�򿪴���
* 2���򿪴��ں󣬵���ReadCardInfo������Ϣ
* 3������ComClose�رմ���
* 4������GetLastErrMsg��ȡ�ô�����Ϣ
****************************************************************************/
//���е���������ֵ����0�������Ϊ0�����Ե���GetLastErrMsg��ȡ�ô�����Ϣ

#ifndef __KSCARDCOM_H__
#define __KSCARDCOM_H__

#pragma once

#pragma pack(1)
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