#ifndef _LOAD_APP_DLL_H_
#define _LOAD_APP_DLL_H_
#pragma once

#include "DataType.h"

/*================================================================ 
* ��������    LoadKingStarDll
* ������      [in] ��
* ��������:   ����V23�����ͻ�ȡ��̨��Ϣ��̬��
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int LoadKingStarDll();

/*================================================================ 
* ��������    LoadV23PosDll
* ������      [in] ��
* ��������:   ����V23������Ϣ��̬��
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int LoadV23PosDll();

/*================================================================ 
* ��������    LoadGateWayDll
* ������      [in] ��
* ��������:   ��ȡ��̨��Ϣ��̬��
* ����ֵ��    ��
================================================================*/
int LoadGateWayDll();

/*================================================================ 
* ��������    UnLoadKingStarDll
* ������      [in] ��
* ��������:   ж��V23�����ͻ�ȡ��̨��Ϣ��̬��
* ����ֵ��    ��
================================================================*/
void UnLoadKingStarDll();

/*================================================================ 
* ��������:   win32 dll���ض�̬���
================================================================*/
#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) { ::FreeLibrary(handle); handle = NULL; \
	return KS_ERR_LOADFUNC_ADDRESS; }
	
DCLR_DLLFUNC(int,KInitLocal,());
DCLR_DLLFUNC(int,KGetCurBalance,(const char szStuempNo[21], double *dCurBalance));
DCLR_DLLFUNC(int,KGetTradeSerial,(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11]));
DCLR_DLLFUNC(int,SMT_ConnectMF280,(int port, int baud));
DCLR_DLLFUNC(int,SMT_CloseMF280,());
DCLR_DLLFUNC(int,SMT_PacketDelMomey,(int nMoney,int &nFlowNo));
DCLR_DLLFUNC(int,SMT_MendPacket,(int &BnMoney,int &AnMoney));
DCLR_DLLFUNC(int,SMT_ReadCardNo,(unsigned char ucCardNo[21]));
DCLR_DLLFUNC(int,SMT_ReadBalance,(int &nMoney));
DCLR_DLLFUNC(int,SMT_ControlBuzzer,());
DCLR_DLLFUNC(int,SMT_ReadCustomerInfo,(CustomerInfo *CutInfo));
DCLR_DLLFUNC(int,SMT_ReadName,(unsigned char ucCutName[9]));
DCLR_DLLFUNC(int,SMT_ReadSex,(unsigned char ucCutSex[2]));

#endif