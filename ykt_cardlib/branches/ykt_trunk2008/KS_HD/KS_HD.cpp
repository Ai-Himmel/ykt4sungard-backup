// ICCash.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "KS_HD.h"
#include "..\include\carddll_def.h"

extern CLogFile g_log_file;

char bufSmartCom[512] = "";
char iniFilePathBuf[512] = "";
char des_port[10] = "";
char src_port[10] = "";
char des_ip[20] = "";
char dll_version[] = "KS_HD v1.00";
char dll_com[20] = "";
char dll_device_id[20] = "";
char str_card_length[20] = "";

#define COM_OPEN_FLAG(com_open_flag) do{ if (!com_open_flag) { return 102; } }while(0)

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
typedef INT (CALLBACK* LPSMT_GetCardNumAndMoney)(char *strCardNum, int *curBalance, int Len);
typedef INT (CALLBACK* LPSMT_GetCardSerial)(unsigned long *nCardSerial);
typedef INT (CALLBACK* LPSMT_ReduceCash)(char *strCardID, int curAmount,unsigned long *TraceOfPos);
typedef INT (CALLBACK* LPSMT_GetLastRecord)(POSRECORD *pCardRecord);
typedef INT (CALLBACK* LPSMT_ReadCardBlock)(unsigned char *Data, unsigned char ucSector, unsigned char ucBlock);
typedef char * (CALLBACK * LPSMT_GetDllVersion)();
typedef long (CALLBACK  *LPSMT_GetCardNum)(char *strCardNum, int strLen);
typedef int (CALLBACK *LPSMT_ControlBuzzer)(unsigned short beep);

LPSMT_OpenPort				SMT_OpenPort = NULL;
LPSMT_ClosePort				SMT_ClosePort = NULL;
LPSMT_ConnectDevice			SMT_ConnectDevice = NULL;
LPSMT_GetCardID				SMT_GetCardID = NULL;
LPSMT_GetCardNumAndMoney    SMT_GetCardNumAndMoney = NULL;
LPSMT_GetCardSerial			SMT_GetCardSerial = NULL;
LPSMT_ReduceCash			SMT_ReduceCash = NULL;
LPSMT_GetLastRecord			SMT_GetLastRecord = NULL;
LPSMT_ReadCardBlock			SMT_ReadCardBlock = NULL;
LPSMT_GetDllVersion			SMT_GetDllVersion = NULL;
LPSMT_GetCardNum			SMT_GetCardNum = NULL;
LPSMT_ControlBuzzer			SMT_ControlBuzzer = NULL;


static int do_load_dll()
{
	LOAD_DLLFUNC_NAME(hDLL,SMT_OpenPort,OpenPort,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_ClosePort,ClosePort,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_ConnectDevice,ConnectDevice,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetCardID,GetCardID,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetCardNumAndMoney,GetCardNumAndMoney,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetCardSerial,GetCardSerial,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_ReduceCash,ReduceCash,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetLastRecord,GetLastRecord,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_ReadCardBlock,ReadCardBlock,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetDllVersion,GetDllVersion,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_GetCardNum,GetCardNum,-1);
	LOAD_DLLFUNC_NAME(hDLL,SMT_ControlBuzzer,ControlBuzzer,-1);
	return 0;

}
int __stdcall Load_Dll()
{
	char msg[512];
	if (NULL == hDLL)
	{
		hDLL = LoadLibrary(bufSmartCom);
		if (!hDLL)
		{
			sprintf(msg,"加载DLL,[%s]失败",bufSmartCom);
			DEBUG_CARD_MSGOUT(0,msg);
			return KS_ERR_LOADLIBRARY;
		}
/*
		SMT_OpenPort				= (LPSMT_OpenPort)GetProcAddress(hDLL,"OpenPort");
		SMT_ClosePort				= (LPSMT_ClosePort)GetProcAddress(hDLL,"ClosePort");
		SMT_ConnectDevice           = (LPSMT_ConnectDevice)GetProcAddress(hDLL,"ConnectDevice");
		SMT_GetCardID  				= (LPSMT_GetCardID)GetProcAddress(hDLL,"GetCardID");
		SMT_GetCardNumAndMoney      = (LPSMT_GetCardNumAndMoney)GetProcAddress(hDLL,"GetCardNumAndMoney");
		SMT_GetCardSerial			= (LPSMT_GetCardSerial)GetProcAddress(hDLL,"GetCardSerial");
		SMT_ReduceCash				= (LPSMT_ReduceCash)GetProcAddress(hDLL, "ReduceCash");
		SMT_GetLastRecord			= (LPSMT_GetLastRecord)GetProcAddress(hDLL, "GetLastRecord");
		SMT_ReadCardBlock			= (LPSMT_ReadCardBlock)GetProcAddress(hDLL, "ReadCardBlock");
		SMT_GetDllVersion			= (LPSMT_GetDllVersion)GetProcAddress(hDLL, "GetDllVersion");
		SMT_GetCardNum				= (LPSMT_GetCardNum)GetProcAddress(hDLL, "GetCardNum");
		SMT_ControlBuzzer			= (LPSMT_ControlBuzzer)GetProcAddress(hDLL, "ControlBuzzer");

		if ((!SMT_OpenPort)					||
			(!SMT_ClosePort)				||
			(!SMT_ConnectDevice)			||
			(!SMT_GetCardID)				||
			(!SMT_GetCardNumAndMoney)       ||
			(!SMT_GetCardSerial)			||
			(!SMT_ReduceCash)				||
			(!SMT_GetLastRecord)			||
			(!SMT_ReadCardBlock)			||
			(!SMT_GetDllVersion)			||
			(!SMT_GetCardNum)				||
			(!SMT_ControlBuzzer)
			)
*/
		if(do_load_dll())
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			sprintf(msg,"加载dll函数失败,[%s]",bufSmartCom);
			DEBUG_CARD_MSGOUT(KS_ERR_LOADFUNC_ADDRESS, msg);
			return KS_ERR_LOADFUNC_ADDRESS;
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

	if (!strCommDef) { return KS_ERR_OPENCOM; }

	if (ret = Load_Dll()) { return ret; }

	if ((ret = SMT_OpenPort(hWnd, str_comm_msg)) != 1) { return KS_ERR_OPENCOM; }
	
	com_is_open = TRUE;
	return 1;
}

long __stdcall ConnectDevice(int nDevAddr)
{
	int ret = 0;
	unsigned long device_id = 0;
//	if (!com_is_open) { return 102; }

	COM_OPEN_FLAG(com_is_open);
	device_id = atoi(dll_device_id);
	ret = SMT_ConnectDevice(device_id);
	
	if (ret != 1)
	{
		return KS_ERR_CONNECTDEVICE;	
	}

	return 1;
}

long __stdcall ClosePort()
{
	int ret = 0;
//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);

	ret = SMT_ClosePort();
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

long __stdcall GetCardID(char *strCardID, int *curBalance, int nLen)
{
	int ret = 0;
	int card_id = 0;
	int amoney = 0;
	char hex_card_id[128] = "";
	char dec_card_id[11] = "00000000";
	char err_msg[128] = "";
	int card_length = 0;
	int length = 0;

//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);

	nLen = 14;
	ret = SMT_GetCardID(hex_card_id, &amoney, nLen);
	if (ret != 1)
	{
		sprintf(err_msg, "卡号[%s]--金额[%lf]--长度[%d]--读取卡号失败", hex_card_id, *curBalance, nLen);
		DEBUG_CARD_MSGOUT(ret, err_msg)
		return KS_ERR_READCARDID;
	}
	
//	hex2dec1(hex_card_id, strCardID);
	card_id = atoi(hex_card_id);		// 去掉空格
	
	if (0 == card_id) 
	{
		DEBUG_CARD_MSGOUT(ret, "读取卡号为空")
		return KS_ERR_READCARDID;
	}

	card_length = atoi(str_card_length);
	memset(hex_card_id, 0, sizeof(hex_card_id));
	sprintf(hex_card_id, "%d", card_id);

	if (8 == card_length)
	{
		// 交易卡号补足8位, 从左到右补0
		length = strlen(hex_card_id);
		strncpy(dec_card_id + 8 - length, hex_card_id, length);
		strncpy(strCardID, dec_card_id, strlen(dec_card_id));
	}
	else
	{
		// 交易卡号不需补足
		strncpy(strCardID, hex_card_id, strlen(hex_card_id));
	}
	
	*curBalance = amoney;
	/*
	sprintf(err_msg, "卡号[%s]--卡号2[%d]--金额[%lf]--长度[%d]", strCardID, card_id, *curBalance, nLen);
	DEBUG_CARD_MSGOUT(0, err_msg)
	*/

	return 1;
}

//读取学工号和余额
long __stdcall GetCardNumAndMoney(char *strCardNum, int *curBalance, int Len)
{
	int ret = 0;
	COM_OPEN_FLAG(com_is_open);
	ret = SMT_GetCardNumAndMoney(strCardNum,curBalance,Len);
	if (ret != 1)
	{
		return KS_ERR_READCARDMONEY;
	}
	return 1;
}

long __stdcall GetCardSerial(unsigned long *nCardSerial)
{
	int ret = 0;
//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);

	// 会出现负数, 物理卡号数值超出了整形的范围, 外部程序用UINT接受可转换
	ret = SMT_GetCardSerial(nCardSerial);		
	if (ret != 1)
	{
		return KS_ERR_READSERIAL;
	}

	return 1;
}

long __stdcall ReduceCash(char *strCardID, int curAmount,unsigned long &serial_no)
{
	int ret = 0;
	int amoney = 0;
	double curBalance = 0.0;
	char error_msg[128] = "";
	char hex_card_id[15] = "";
	int card_id = 0;

//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);
	// 判断扣款金额是否在范围[0.01~10000.00]
	/*
	if ((curAmount < 0.01 && curAmount > -0.01) || ((10000 - curAmount) < 0.01 && (10000 - curAmount) > -0.01))
	{
		sprintf(error_msg, "金额超出范围[%d]", curAmount * 100);
		DEBUG_CARD_MSGOUT(KS_ERR_INPUTMONEY, error_msg)
		return KS_ERR_INPUTMONEY;
	}
	*/
	if(curAmount < 0 || curAmount > 1000000)
	{
		sprintf(error_msg, "金额超出范围[%d]", curAmount);
		DEBUG_CARD_MSGOUT(KS_ERR_INPUTMONEY, error_msg);
		return KS_ERR_INPUTMONEY;
	}
	
	ret = SMT_ReduceCash(strCardID, curAmount,&serial_no);
	if (ret != 1)
	{
		DEBUG_CARD_MSGOUT(ret, "扣款失败")
		return KS_ERR_WRITECARDMONEY;
	}
	
	return 1;
}

long __stdcall GetLastRecord(POSRECORD *pCardRecord)
{
	int ret = 0;
//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);

	if ((ret = SMT_GetLastRecord(pCardRecord)) != 1) { return KS_ERR_READPOSSERIAL; }

	return 1;
}

char * __stdcall GetDllVersion()
{ 
	return dll_version;
}

long __stdcall GetCardNum(char *strCardNum, int strlen)
{
	int ret = 0;
//	if (!com_is_open) { return 102; }
	COM_OPEN_FLAG(com_is_open);
	if ((ret = SMT_GetCardNum(strCardNum, strlen)) != 1) { return KS_ERR_READSTUEMPNO; }

	return 0;
}

long __stdcall POS_ConnectMF(int port, int baud, int hwnd)
{
	int ret = 0;
	ret = OpenPort(hwnd, "");
	if (ret != 1) { return ret; }
	
	ret = ConnectDevice(0);
	if (ret != 1) { return ret; }

	return 0;
}

long __stdcall POS_CloseMF()
{
	return ClosePort();
}

int __stdcall POS_PacketDelMoney(int money, int &flow_no)
{
	int ret = 0;
	char card_id[20] = "";
	unsigned long serial_no = 0;
	sprintf(card_id,"%d",flow_no);
	ret = ReduceCash(card_id, money,serial_no);
	if (ret != 1) { return ret; }
	
	flow_no = serial_no;			// 2008/10/08添加流水号
	return 0;
}

int __stdcall POS_ReadBalance(int &money)
{
	int ret = 0; 
	int card_money = 0;
	char card_id[20] = "";
	COM_OPEN_FLAG(com_is_open);

	ret = SMT_GetCardID(card_id, &card_money, sizeof(card_id));
	if (ret != 1) { return KS_ERR_READCARDMONEY; }

	money = card_money;
	return 0;
}

int __stdcall POS_MendPacket(int &bmoney, int &amoney)
{
	return 0;
}

int __stdcall POS_ControlBuzzer(unsigned short beep)
{
	SMT_ControlBuzzer(beep);
	return 0;
}

int __stdcall POS_ReadStuempNo(unsigned char stuemp_no[21])
{
	int ret = 0;
	int length = 20;
	COM_OPEN_FLAG(com_is_open);

	ret = GetCardNum((char *)stuemp_no, length);
	if (ret != 0) { return KS_ERR_READSTUEMPNO; }

	if (0 == strlen((char *)stuemp_no)) { return  KS_ERR_READSTUEMPNULL; }
	return 0;
}

int __stdcall POS_ReadSerial(unsigned char serial[5])
{
	int ret = 0;
	unsigned long serial_no = 0;
	ret = GetCardSerial(&serial_no);
	if (ret != 1) { return ret; }

	memcpy(serial, &serial_no, sizeof(serial_no));

	return 0;
}

int __stdcall POS_ReadCardNO(int nCardNo[1])
{
	int ret = 0;
	int money = 0;
	char card_id[20] = "";
	COM_OPEN_FLAG(com_is_open);

	ret = SMT_GetCardID(card_id, &money, sizeof(card_id));
	if (ret != 1) { return ret; }

	nCardNo[0] = atoi(card_id);
	return 0;
}