// ICCash.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "ICCash.h"

char bufSmartCom[512] = "";
char iniFilePathBuf[512] = "";
char des_port[10] = "";
char src_port[10] = "";
char des_ip[20] = "";
char dll_version[] = "ICCash v1.00";

#define YKT_DONGHUA 1
#define VOICE_INDEX_DI               50  //50di.wav
#define VOICE_INDEX_DIDI             51  //51didi.wav
#define VOICE_INDEX_DIDIDI           52  //52dididi.wav

// 判断串口是否已经打开
static BOOL com_is_open = FALSE;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLLPOS", "", bufSmartCom, sizeof(bufSmartCom), iniFilePathBuf);
	GetPrivateProfileString("YONGTUO", "DES_PORT", "", des_port, sizeof(des_port), iniFilePathBuf);
	GetPrivateProfileString("YONGTUO", "DES_IP", "", des_ip, sizeof(des_ip), iniFilePathBuf);
	GetPrivateProfileString("YONGTUO", "LOCAL_PORT", "", src_port, sizeof(src_port), iniFilePathBuf);
	
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
typedef INT (CALLBACK* LPSMT_OpenPort)(int, int);
typedef INT (CALLBACK* LPSMT_ClosePort)(void);
typedef INT (CALLBACK* LPSMT_ConnectDevice)(int nDevAddr);
typedef INT (CALLBACK* LPSMT_GetCardID)(char *strCardID, int *curBalance, int nLen);
typedef INT (CALLBACK* LPSMT_GetCardSerial)(int *nCardSerial);
typedef INT (CALLBACK* LPSMT_ReduceCash)(char *strCardID, int curAmount);
typedef INT (CALLBACK* LPSMT_GetLastRecord)(POSRECORD *pCardRecord);
typedef INT (CALLBACK* LPSMT_ReadCardBlock)(unsigned char *Data, unsigned char ucSector, unsigned char ucBlock);
typedef INT (CALLBACK* LPSMT_HD_Init)(UINT nLocalPort);
typedef INT (CALLBACK* LPSMT_HD_Term)(void);
typedef INT (CALLBACK* LPSMT_HD_SetRemoteDevice)(UINT nPort,char *pszIPAddr);
typedef INT (CALLBACK* LPSMT_SF2006ReadTime)(BYTE *pszTime);
typedef char* (CALLBACK* LPSMT_GetDllVersion)(void);
typedef INT (CALLBACK* LPSMT_SF2006WriteTime)(void);
typedef INT (CALLBACK* LPSMT_SF2006GetVersion)(BYTE *pszInfo);
typedef INT (CALLBACK* LPSMT_SF2006Lock)(void);
typedef INT (CALLBACK* LPSMT_SF2006Unlock)(void);
typedef INT (CALLBACK* LPSMT_SF2006DisplayTurn)(BYTE nOpt);
typedef INT (CALLBACK* LPSMT_SF2006DisplayFloat)(long f);
typedef INT (CALLBACK* LPSMT_SF2006PlayFloat)(long f);
typedef INT (CALLBACK* LPSMT_GetRecordNum)(unsigned short *nNum);
typedef INT (CALLBACK* LPSMT_GetRecord)(unsigned short nIndex, POSRECORD *pCardRecord);
typedef INT (CALLBACK* LPSMT_UpdateRecordPointer)(unsigned short nIndex);
typedef INT	(CALLBACK* LPSMT_SF2006PlayCustome)(BYTE nNum, BYTE *pszData);

LPSMT_OpenPort				SMT_OpenPort = NULL;
LPSMT_ClosePort				SMT_ClosePort = NULL;
LPSMT_ConnectDevice			SMT_ConnectDevice = NULL;
LPSMT_GetCardID				SMT_GetCardID = NULL;
LPSMT_GetCardSerial			SMT_GetCardSerial = NULL;
LPSMT_ReduceCash			SMT_ReduceCash = NULL;
LPSMT_GetLastRecord			SMT_GetLastRecord = NULL;
LPSMT_ReadCardBlock			SMT_ReadCardBlock = NULL;
LPSMT_HD_Init				SMT_HD_Init = NULL;
LPSMT_HD_Term				SMT_HD_Term = NULL;
LPSMT_HD_SetRemoteDevice	SMT_HD_SetRemoteDevice = NULL;
LPSMT_SF2006ReadTime		SMT_SF2006ReadTime = NULL;
LPSMT_GetDllVersion			SMT_GetDllVersion = NULL;
LPSMT_SF2006WriteTime		SMT_SF2006WriteTime = NULL;
LPSMT_SF2006GetVersion		SMT_SF2006GetVersion = NULL;
LPSMT_SF2006Lock			SMT_SF2006Lock = NULL;
LPSMT_SF2006Unlock			SMT_SF2006Unlock = NULL;
LPSMT_SF2006DisplayTurn		SMT_SF2006DisplayTurn = NULL;
LPSMT_SF2006DisplayFloat	SMT_SF2006DisplayFloat = NULL;
LPSMT_SF2006PlayFloat		SMT_SF2006PlayFloat = NULL;
LPSMT_GetRecordNum			SMT_GetRecordNum = NULL;
LPSMT_GetRecord				SMT_GetRecord = NULL;
LPSMT_UpdateRecordPointer	SMT_UpdateRecordPointer = NULL;
LPSMT_SF2006PlayCustome		SMT_SF2006PlayCustome = NULL;

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
		SMT_HD_Init					= (LPSMT_HD_Init)GetProcAddress(hDLL, "HD_Init");
		SMT_HD_Term					= (LPSMT_HD_Term)GetProcAddress(hDLL, "HD_Term");
		SMT_HD_SetRemoteDevice		= (LPSMT_HD_SetRemoteDevice)GetProcAddress(hDLL, "HD_SetRemoteDevice");
		SMT_SF2006ReadTime			= (LPSMT_SF2006ReadTime)GetProcAddress(hDLL, "SF2006ReadTime");
		SMT_SF2006WriteTime			= (LPSMT_SF2006WriteTime)GetProcAddress(hDLL, "SF2006WriteTime");
		SMT_SF2006GetVersion		= (LPSMT_SF2006GetVersion)GetProcAddress(hDLL, "SF2006GetVersion");
		SMT_SF2006Lock				= (LPSMT_SF2006Lock)GetProcAddress(hDLL, "SF2006Lock");
		SMT_SF2006Unlock			= (LPSMT_SF2006Unlock)GetProcAddress(hDLL, "SF2006Unlock");
		SMT_SF2006DisplayTurn		= (LPSMT_SF2006DisplayTurn)GetProcAddress(hDLL, "SF2006DisplayTurn");
		SMT_SF2006DisplayFloat		= (LPSMT_SF2006DisplayFloat)GetProcAddress(hDLL, "SF2006DisplayFloat");
		SMT_SF2006PlayFloat			= (LPSMT_SF2006PlayFloat)GetProcAddress(hDLL, "SF2006PlayFloat");
		SMT_GetRecordNum			= (LPSMT_GetRecordNum)GetProcAddress(hDLL, "GetRecordNum");
		SMT_GetRecord				= (LPSMT_GetRecord)GetProcAddress(hDLL, "GetRecord");
		SMT_UpdateRecordPointer		= (LPSMT_UpdateRecordPointer)GetProcAddress(hDLL, "UpdateRecordPointer");
		SMT_SF2006PlayCustome       = (LPSMT_SF2006PlayCustome)GetProcAddress(hDLL, "SF2006PlayCustome");

		if ((!SMT_OpenPort)					||
			(!SMT_ClosePort)				||
			(!SMT_ConnectDevice)			||
			(!SMT_GetCardID)				||
			(!SMT_GetCardSerial)			||
			(!SMT_ReduceCash)				||
			(!SMT_GetLastRecord)			||
			(!SMT_ReadCardBlock)			||
			(!SMT_HD_Init)					||
			(!SMT_HD_Term)					||
			(!SMT_HD_SetRemoteDevice)		||
			(!SMT_SF2006ReadTime)			||
			(!SMT_SF2006WriteTime)			||
			(!SMT_SF2006GetVersion)			||
			(!SMT_SF2006Lock)				||
			(!SMT_SF2006Unlock)				||
			(!SMT_SF2006DisplayTurn)		||
			(!SMT_SF2006DisplayFloat)		|| 
			(!SMT_SF2006PlayFloat)			||
			(!SMT_GetRecordNum)				||
			(!SMT_GetRecord)				||
			(!SMT_UpdateRecordPointer)		||
			(!SMT_SF2006PlayCustome)
			)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			DEBUG_CARD_MSGOUT(103, "加载dll函数失败")
			return 103;
		}
	}
	
	return 0;
}

long __stdcall OpenPort(int hWnd, char *strCommDef)
{
	int ret = 0;
	int i = 0;
	int port = 0;
	int baud_rate = 0;
	int local_port = atoi(src_port);
	int server_port = 0;

	char *pos = NULL;
	char com[4] = "";
	char baud[6] = "";

	if (!strCommDef) { return 102; }

	if (ret = Load_Dll()) { return ret; }

	ret = SMT_HD_Init(local_port);
	if (ret)
	{
		DEBUG_CARD_MSGOUT(ret, "初始化本地端口失败")
		return 122;
	}
	
	server_port = atoi(des_port);
	SMT_HD_SetRemoteDevice(server_port, des_ip);

/*
	pos = strCommDef;
	if (pos = strstr(strCommDef, "COM"))
	{
		pos += 3;
		while (*pos != ':')
		{
			com[i] = *pos;
			pos++;
			i++;
			if (3 == i) { break; }
		}
	}

	i = 0;

	if (pos = strstr(strCommDef, "Baud"))
	{
		pos += 5;
		while (*pos != ';')
		{
			baud[i] = *pos;
			pos++;
			i++;
			if (5 == i) { break; }
		}
	}

	port = atoi(com);
	baud_rate = atoi(baud);

	if (ret = SMT_OpenPort(port, baud_rate)) { return 102; }
*/

	ret = SMT_SF2006Lock();
	if (ret)
	{
		DEBUG_CARD_MSGOUT(ret, "锁定POS机失败")
		return 1000;
	}
	
	com_is_open = TRUE;
	return 1;
}

long __stdcall ConnectDevice(int nDevAddr)
{
	int ret = 0;
	if (!com_is_open) { return 102; }
/*
	ret = ConnectDevice(nDevAddr);
	if (ret)
	{
		return 101;	
	}
*/
	return 1;
}

long __stdcall ClosePort()
{
	int ret = 0;
	if (!com_is_open) { return 102; }

	SMT_SF2006Unlock();

	if (ret = SMT_HD_Term())
	{
		return 1000;
	}
	
//	ret = SMT_ClosePort();

	com_is_open = FALSE;
	return 1;
}

char * __stdcall GetErrorMsg(long ErrorCode)
{
	if (101 == ErrorCode) { return "无法创建设备连接句柄"; }
	
	if (102 == ErrorCode) { return "无法连接通讯端口,请确认端口是否有效或已被占用"; }
	
	if (103 == ErrorCode) { return "ICDM.dll库函数未载入"; }

	if (104 == ErrorCode) { return "卡号长度错误,不应大于15"; }
	
	if (105 == ErrorCode) { return "没有检测到用户卡"; }

	if (106 == ErrorCode) { return "扣款时没有指定卡号"; }

	if (107 == ErrorCode) { return "扣款金额超出范围[0.01~10000.00]"; }
	
	if (122 == ErrorCode) { return "通讯端口未连接,无法访问设备"; }
	
	if (125 == ErrorCode) { return "通讯错误"; }

	if (130 == ErrorCode) { return "卡片已锁"; }
	
	if (136 == ErrorCode) { return "返回数据错误"; }
	
	if (1000 == ErrorCode) { return "系统错误"; }
	
	if (1001 == ErrorCode) { return "余额不足"; }

	return "";
}

long __stdcall GetCardID(char *strCardID, double *curBalance, int nLen)
{
	int ret = 0;
	int serial_no = 0;
	int amount = 0;
	char hex_card_id[15] = "";
	char dec_card_id[11] = "00000000";
	int length = 0;

	if (!com_is_open) { return 102; }

	ret = SMT_GetCardSerial(&serial_no);				
	if (ret)
	{
		DEBUG_CARD_MSGOUT(ret, "读取物理卡号失败")
		return 105;
	}

	if (nLen > 15) { return 104; }
	ret = SMT_GetCardID(hex_card_id, &amount, nLen);
	if (ret)
	{
		DEBUG_CARD_MSGOUT(ret, "读取卡号失败")
		return 1000;
	}
	
	hex2dec1(hex_card_id, strCardID);

#ifdef YKT_DONGHUA		
	// 交易卡号补足8位, 从左到右补0
	length = strlen(strCardID);
	strncpy(dec_card_id + 8 - length, strCardID, length);
	strncpy(strCardID, dec_card_id, strlen(dec_card_id));
#endif

	*curBalance = (double)amount / (double)100;
	
	return 1;
}

long __stdcall GetCardSerial(int *nCardSerial)
{
	int ret = 0;
	if (!com_is_open) { return 102; }

	// 会出现负数, 物理卡号数值超出了整形的范围, 外部程序用UINT接受可转换
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
	int amount = 0;
	double curBalance = 0.0;
	char error_msg[128] = "";
	char hex_card_id[15] = "";
	BYTE pszData[2] = "";

	if (!com_is_open) { return 102; }

	// 判断扣款金额是否在范围[0.01~10000.00]
	if ((curAmount < 0.01 && curAmount > -0.01) || ((10000 - curAmount) < 0.01 && (10000 - curAmount) > -0.01))
	{
		sprintf(error_msg, "金额超出范围[%d]", curAmount * 100);
		DEBUG_CARD_MSGOUT(107, error_msg)
		return 107;
	}
	
	ret = GetCardID(strCardID, &curBalance, 8);
	if (ret != 1) { return ret; }
	
	amount = (int)(curAmount * 100);
	
	// 判断扣款金额是否大于当前余额
	if ((int)((curBalance - curAmount) * 100) < 0) { return 1001; }

	ret = SMT_ReduceCash(hex_card_id, amount);
	if (ret)
	{
		DEBUG_CARD_MSGOUT(ret, "扣款失败")
		return 106;
	}
	
	SMT_SF2006DisplayTurn(1);
	SMT_SF2006DisplayFloat((long)(curBalance * 100) - amount);
//	SMT_SF2006PlayFloat((long)(curBalance * 100) - amount);
	SMT_SF2006DisplayTurn(0);
	pszData[0] = 51;
	SMT_SF2006PlayCustome(1, pszData);

	return 1;
}

long __stdcall GetLastRecord(POSRECORD *pCardRecord)
{
	int ret = 0;
	unsigned short record_num = 0;

	if (!com_is_open) { return 102; }
	
	SMT_GetRecordNum(&record_num);
//	if (ret = SMT_GetLastRecord(pCardRecord)) { return 136; }
	if (ret = SMT_GetRecord(record_num - 1, pCardRecord)) { return 136; }

	return 1;
}

char * __stdcall GetDllVersion()
{ 
	return "ICCash v1.00";
//	return dll_version;
}