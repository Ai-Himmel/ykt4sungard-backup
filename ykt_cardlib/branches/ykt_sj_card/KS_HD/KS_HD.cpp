// ICCash.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "KS_HD.h"

char bufSmartCom[512] = "";
char iniFilePathBuf[512] = "";
char des_port[10] = "";
char src_port[10] = "";
char des_ip[20] = "";
char dll_version[] = "KS_HD v1.00";
char dll_com[20] = "";
char dll_device_id[20] = "";
char str_card_length[20] = "";

// �жϴ����Ƿ��Ѿ���
static BOOL com_is_open = FALSE;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLLPOS", "", bufSmartCom, sizeof(bufSmartCom), iniFilePathBuf);
	GetPrivateProfileString("KS_HD", "DLL_COM", "", dll_com, sizeof(dll_com), iniFilePathBuf);
	GetPrivateProfileString("KS_HD", "DLL_DEVICE_ID", "", dll_device_id, sizeof(dll_device_id), iniFilePathBuf);
	GetPrivateProfileString("KS_HD", "CARD_LEN", "", str_card_length, sizeof(str_card_length), iniFilePathBuf);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

HINSTANCE hDLL = NULL;
typedef INT (CALLBACK* LPSMT_OpenPort)(int hWnd, char *strCommDef);
typedef INT (CALLBACK* LPSMT_ClosePort)(void);
typedef INT (CALLBACK* LPSMT_ConnectDevice)(int nDevAddr);
typedef INT (CALLBACK* LPSMT_GetCardID)(char *strCardID, int *curBalance, int nLen);
//typedef INT (CALLBACK* LPSMT_GetCardID)(char *strCardID, double *curBalance, int nLen);
typedef INT (CALLBACK* LPSMT_GetCardSerial)(int *nCardSerial);
//typedef INT (CALLBACK* LPSMT_ReduceCash)(char *strCardID, double curAmount);
typedef INT (CALLBACK* LPSMT_ReduceCash)(char *strCardID, int curAmount,unsigned long &serial_no);
typedef INT (CALLBACK* LPSMT_GetLastRecord)(POSRECORD *pCardRecord);
typedef INT (CALLBACK* LPSMT_ReadCardBlock)(unsigned char *Data, unsigned char ucSector, unsigned char ucBlock);
typedef char * (__stdcall * LPSMT_GetDllVersion)();
typedef int (CALLBACK *LPSMT_ControlBuzzer)(unsigned short beep);

LPSMT_OpenPort				SMT_OpenPort = NULL;
LPSMT_ClosePort				SMT_ClosePort = NULL;
LPSMT_ConnectDevice			SMT_ConnectDevice = NULL;
LPSMT_GetCardID				SMT_GetCardID = NULL;
LPSMT_GetCardSerial			SMT_GetCardSerial = NULL;
LPSMT_ReduceCash			SMT_ReduceCash = NULL;
LPSMT_GetLastRecord			SMT_GetLastRecord = NULL;
LPSMT_ReadCardBlock			SMT_ReadCardBlock = NULL;
LPSMT_GetDllVersion			SMT_GetDllVersion = NULL;
LPSMT_ControlBuzzer			SMT_ControlBuzzer = NULL;

int __stdcall Load_Dll()
{
	if (NULL == hDLL)
	{
		hDLL = LoadLibrary(bufSmartCom);
		if (!hDLL)
		{
			return -1;
		}

		SMT_OpenPort				= (LPSMT_OpenPort)GetProcAddress(hDLL,"OpenPort");
		SMT_ClosePort				= (LPSMT_ClosePort)GetProcAddress(hDLL,"ClosePort");
		SMT_ConnectDevice           = (LPSMT_ConnectDevice)GetProcAddress(hDLL,"ConnectDevice");
		SMT_GetCardID  				= (LPSMT_GetCardID)GetProcAddress(hDLL,"GetCardID");
		SMT_GetCardSerial			= (LPSMT_GetCardSerial)GetProcAddress(hDLL,"GetCardSerial");
		SMT_ReduceCash				= (LPSMT_ReduceCash)GetProcAddress(hDLL, "ReduceCash");
		SMT_GetLastRecord			= (LPSMT_GetLastRecord)GetProcAddress(hDLL, "GetLastRecord");
		SMT_ReadCardBlock			= (LPSMT_ReadCardBlock)GetProcAddress(hDLL, "ReadCardBlock");
		SMT_GetDllVersion			= (LPSMT_GetDllVersion)GetProcAddress(hDLL, "GetDllVersion");
		SMT_ControlBuzzer			= (LPSMT_ControlBuzzer)GetProcAddress(hDLL, "ControlBuzzer");
		if ((!SMT_OpenPort)					||
			(!SMT_ClosePort)				||
			(!SMT_ConnectDevice)			||
			(!SMT_GetCardID)				||
			(!SMT_GetCardSerial)			||
			(!SMT_ReduceCash)				||
			(!SMT_GetLastRecord)			||
			(!SMT_ReadCardBlock)			||
			(!SMT_GetDllVersion)			||
			(!SMT_ControlBuzzer)
			)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			DEBUG_CARD_MSGOUT(103, "����dll����ʧ��")
			return 103;
		}
	}
	
	return 0;
}

long __stdcall OpenPort(int hWnd, char *strCommDef)
{
	int ret = 0;
	int port = 0;
	int baud_rate = 0;
	char str_comm_msg[50] = "";
//	port = atoi(dll_com);
	strcat(str_comm_msg, "COM");
	strcat(str_comm_msg, dll_com);
	strcat(str_comm_msg, ":");
	strcat(str_comm_msg, "Baud=38400,Parity=n,Data=8,Stop=1");

	if (!strCommDef) { return 102; }

	if (ret = Load_Dll()) { return ret; }

	if ((ret = SMT_OpenPort(hWnd, str_comm_msg)) != 1) { return 102; }
	
	com_is_open = TRUE;
	return 1;
}

long __stdcall ConnectDevice(int nDevAddr)
{
	int ret = 0;
	unsigned long device_id = 0;
	if (!com_is_open) { return 102; }

	device_id = atoi(dll_device_id);
	ret = SMT_ConnectDevice(device_id);
	
	if (ret != 1)
	{
		return 101;	
	}

	return 1;
}

long __stdcall ClosePort()
{
	int ret = 0;
	if (!com_is_open) { return 102; }

	ret = SMT_ClosePort();

	com_is_open = FALSE;
	return 1;
}

char * __stdcall GetErrorMsg(long ErrorCode)
{
	if (101 == ErrorCode) { return "�޷������豸���Ӿ��"; }
	
	if (102 == ErrorCode) { return "�޷�����ͨѶ�˿�,��ȷ�϶˿��Ƿ���Ч���ѱ�ռ��"; }
	
	if (103 == ErrorCode) { return "ICDM.dll�⺯��δ����"; }

	if (104 == ErrorCode) { return "���ų��ȴ���,��Ӧ����15"; }
	
	if (105 == ErrorCode) { return "û�м�⵽�û���"; }

	if (106 == ErrorCode) { return "�ۿ�ʱû��ָ������"; }

	if (107 == ErrorCode) { return "�ۿ������Χ[0.01~10000.00]"; }
	
	if (122 == ErrorCode) { return "ͨѶ�˿�δ����,�޷������豸"; }
	
	if (125 == ErrorCode) { return "ͨѶ����"; }

	if (130 == ErrorCode) { return "��Ƭ����"; }
	
	if (136 == ErrorCode) { return "�������ݴ���"; }
	
	if (1000 == ErrorCode) { return "ϵͳ����"; }
	
	if (1001 == ErrorCode) { return "����"; }

	return "";
}

long __stdcall GetCardID(char *strCardID, double *curBalance, int card_length)
{
	int ret = 0;
	int card_id = 0;
//	int amount = 0;
	int amoney = 0;
	char hex_card_id[128] = "";
	char dec_card_id[11] = "00000000";
	char err_msg[128] = "";
	int length = 0;

	if (!com_is_open) { return 102; }

	int nLen = 14;
	ret = SMT_GetCardID(hex_card_id, &amoney, nLen);
	if (ret != 1)
	{
		sprintf(err_msg, "����[%s]--���[%d]--����[%d]--��ȡ����ʧ��", hex_card_id, amoney, nLen);
		DEBUG_CARD_MSGOUT(ret, err_msg)
		return 1000;
	}
	SMT_ControlBuzzer(10);
	
//	hex2dec1(hex_card_id, strCardID);
	card_id = atoi(hex_card_id);		// ȥ���ո�
	
	if (0 == card_id) 
	{
		DEBUG_CARD_MSGOUT(ret, "��ȡ����Ϊ��")
		return 1001;
	}

	card_length = atoi(str_card_length);
	memset(hex_card_id, 0, sizeof(hex_card_id));
	sprintf(hex_card_id, "%d", card_id);

	if (8 == card_length)
	{
		// ���׿��Ų���8λ, �����Ҳ�0
		length = strlen(hex_card_id);
		strncpy(dec_card_id + 8 - length, hex_card_id, length);
		strncpy(strCardID, dec_card_id, strlen(dec_card_id));
	}
	else
	{
		// ���׿��Ų��貹��
		strncpy(strCardID, hex_card_id, strlen(hex_card_id));
	}
	
	*curBalance = amoney / 100.0;
	sprintf(err_msg, "����[%s]--����2[%d]--���[%d]--����[%d]", strCardID, card_id, *curBalance, nLen);
	DEBUG_CARD_MSGOUT(0, err_msg)

	return 1;
}

long __stdcall GetCardSerial(int *nCardSerial)
{
	int ret = 0;
	if (!com_is_open) { return 102; }

	// ����ָ���, ��������ֵ���������εķ�Χ, �ⲿ������UINT���ܿ�ת��
	ret = SMT_GetCardSerial(nCardSerial);		
	if (ret)
	{
		return 105;
	}

	return 1;
}

long __stdcall ReduceCash(char *strCardID, double curAmount)
{
	int ret = 0;
	double curBalance = 0.0;
	int amoney = 0;
	unsigned long serial_no =0;
	char error_msg[128] = "";
	char hex_card_id[15] = "";
	int card_id = 0;
	long card_amount = 0;

	if (!com_is_open) { return 102; }

	// �жϿۿ����Ƿ��ڷ�Χ[0.01~10000.00]
	if ((curAmount < 0.01 && curAmount > -0.01) || ((10000 - curAmount) < 0.01 && (10000 - curAmount) > -0.01))
	{
		sprintf(error_msg, "������Χ[%d]", curAmount * 100);
		DEBUG_CARD_MSGOUT(107, error_msg)
		return 107;
	}
	


	// �޸ĳɷ�Ϊ��λ
	card_amount = (int)(curAmount * 100.0 + 0.5);

	ret = SMT_ReduceCash(strCardID, card_amount,serial_no);
	if (ret != 1)
	{
		DEBUG_CARD_MSGOUT(ret, "�ۿ�ʧ��")
		return 106;
	}
	SMT_ControlBuzzer(10);
	sprintf(error_msg,"���׳ɹ�������[%s],���[%d],��ˮ��[%ld]",strCardID,card_amount,serial_no);
	DEBUG_CARD_MSGOUT(9999,error_msg)
	return 1;
}

long __stdcall ReduceCash2(char *strCardID, int curAmount)
{
	int ret = 0;
	char error_msg[1024] = "";
	unsigned long serial_no =0;
	if (!com_is_open) { return 102; }

	// �жϿۿ����Ƿ��ڷ�Χ[0.01~10000.00]
	if (curAmount < 0 || curAmount > 10000)
	{
		sprintf(error_msg, "������Χ[%d]", curAmount);
		DEBUG_CARD_MSGOUT(107, error_msg)
		return 107;
	}
	ret = SMT_ReduceCash(strCardID, curAmount,serial_no);
	if (ret != 1)
	{
		DEBUG_CARD_MSGOUT(ret, "�ۿ�ʧ��")
		return 106;
	}
	SMT_ControlBuzzer(10);
	sprintf(error_msg,"���׳ɹ�������[%s],���[%d],��ˮ��[%ld]",strCardID,curAmount,serial_no);
	DEBUG_CARD_MSGOUT(9999,error_msg)
	return 1;
}

long __stdcall GetLastRecord(POSRECORD *pCardRecord)
{
	int ret = 0;
	if (!com_is_open) { return 102; }
	
	if ((ret = SMT_GetLastRecord(pCardRecord)) != 1) { return 136; }

	return 1;
}

char * __stdcall GetDllVersion()
{ 
	return dll_version;
}