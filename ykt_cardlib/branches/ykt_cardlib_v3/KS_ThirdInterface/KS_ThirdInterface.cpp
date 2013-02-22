#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "KS_ThirdInterface.h"
#include "DataType.h"
#include "..\include\carddll_def.h"

extern CLogFile g_log_file;

char buf_dll[512] = "";
char iniFilePathBuf[512] = "";
char dll_version[] = "KS_ThirdInterface v1.00";
char str_card_length[20] = "";
char msg[128] = "";

static int g_pos_handle = -1;
// 判断串口是否已经打开
static BOOL com_is_open = FALSE;

#define THIRD_DEF_RECALL_DLL(r,n,p,t) \
	typedef r (CALLBACK *LP##n) p; \
	static LP##n I##n = NULL; \
	r CALLBACK n p { return I##n t;} 

#define THIRD_LOAD_RECALL_DLL(h,n)  do { \
	I##n = (LP##n)GetProcAddress(h,#n); \
	if(I##n == NULL) {FreeLibrary(h); return -1;} }while(0)



typedef long (CALLBACK *LPTHIRD_ConnectMF)(int port, int baud, int hwnd);
typedef long (CALLBACK *LPTHIRD_CloseMF)(void);
typedef int (CALLBACK *LPTHIRD_PacketDelMoney)(int money, int &flow_no);
typedef int (CALLBACK *LPTHIRD_ReadBalance)(int &money);
typedef int (CALLBACK *LPTHIRD_MendPacket)(int &bmoney, int &amoney);
typedef int (CALLBACK *LPTHIRD_ControlBuzzer)();
typedef int (CALLBACK *LPTHIRD_ReadStuempNo)(unsigned char stuemp_no[21]);
typedef int (CALLBACK *LPTHIRD_ReadSerial)(unsigned char serial[5]);
typedef int (CALLBACK *LPTHIRD_ReadCardNO)(int nCardNo[1]);
typedef int (CALLBACK *LPTHIRD_GetLastRecord)(POSRECORD *pCardRecord);

LPTHIRD_ConnectMF		THIRD_ConnectMF = NULL;
LPTHIRD_CloseMF			THIRD_CloseMF = NULL;
LPTHIRD_PacketDelMoney	THIRD_PacketDelMoney = NULL;
LPTHIRD_ReadBalance		THIRD_ReadBalance = NULL;
LPTHIRD_MendPacket		THIRD_MendPacket = NULL;
LPTHIRD_ControlBuzzer	THIRD_ControlBuzzer = NULL;
LPTHIRD_ReadStuempNo	THIRD_ReadStuempNo = NULL;
LPTHIRD_ReadSerial		THIRD_ReadSerial = NULL;
LPTHIRD_ReadCardNO		THIRD_ReadCardNO = NULL;
LPTHIRD_GetLastRecord	THIRD_GetLastRecord = NULL;


THIRD_DEF_RECALL_DLL(int,YKTSVR_Login,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Create,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Close,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Exit,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetCardInfo,(char physical_no[9], CardInfo *card_info),(physical_no,card_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetCustomerInfo,(int cut_id, CutInfo *card_info),(cut_id,card_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetDataInfo,(char physical_no[9],  char stuemp_no[22], DataInfo *data_info),(physical_no,stuemp_no,data_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_SetCardKey,(),())

BOOL APIENTRY DllMain( HINSTANCE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL_THIRD", "", buf_dll, sizeof(buf_dll), iniFilePathBuf);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// 获取句柄
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

HINSTANCE hDLL = NULL;

int __stdcall Load_Dll()
{
	if (NULL == hDLL)
	{
		hDLL = LoadLibrary(buf_dll);
		if (!hDLL)
		{
			return KS_ERR_LOADLIBRARY;
		}

		THIRD_ConnectMF				= (LPTHIRD_ConnectMF)GetProcAddress(hDLL, "THIRD_ConnectMF");
		THIRD_CloseMF				= (LPTHIRD_CloseMF)GetProcAddress(hDLL, "CloseMF");
		THIRD_PacketDelMoney		= (LPTHIRD_PacketDelMoney)GetProcAddress(hDLL, "THIRD_PacketDelMoney");
		THIRD_ReadBalance			= (LPTHIRD_ReadBalance)GetProcAddress(hDLL, "THIRD_ReadBalance");
		THIRD_MendPacket			= (LPTHIRD_MendPacket)GetProcAddress(hDLL, "THIRD_MendPacket");
		THIRD_ControlBuzzer			= (LPTHIRD_ControlBuzzer)GetProcAddress(hDLL, "THIRD_ControlBuzzer");
		THIRD_ReadStuempNo			= (LPTHIRD_ReadStuempNo)GetProcAddress(hDLL, "THIRD_ReadStuempNo");
		THIRD_ReadSerial			= (LPTHIRD_ReadSerial)GetProcAddress(hDLL, "THIRD_ReadSerial");	
		THIRD_ReadCardNO			= (LPTHIRD_ReadCardNO)GetProcAddress(hDLL, "THIRD_ReadCardNO");
		THIRD_GetLastRecord			= (LPTHIRD_GetLastRecord)GetProcAddress(hDLL, "THIRD_GetLastRecord");
		if (
			(!THIRD_ConnectMF)			||
			(!THIRD_CloseMF)			||
			(!THIRD_PacketDelMoney)		||
			(!THIRD_ReadBalance)		||
			(!THIRD_MendPacket)			||
			(!THIRD_ControlBuzzer)		||
			(!THIRD_ReadStuempNo)		||
			(!THIRD_ReadSerial)			||
			(!THIRD_ReadCardNO)			||
			(!THIRD_GetLastRecord)
			)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			sprintf(msg, "加载dll-[%s]函数失败", buf_dll);
			DEBUG_CARD_MSGOUT(KS_ERR_LOADFUNC_ADDRESS, msg)
			return KS_ERR_LOADFUNC_ADDRESS;
		}
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_Login);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_Create);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_Close);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_Exit);
		//THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_GetCardInfo);
		//THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_GetCustomerInfo);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_GetDataInfo);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_SetCardKey);
	}
	
	return 0;
}

int __stdcall ConnectMF(int port, int baud, int hwnd)
{
	int ret = 0;
	if (ret = Load_Dll()) { return ret; }

	return THIRD_ConnectMF(port, baud, hwnd);
}
int __stdcall SMT_ConnectMF280(int port, int baud)
{
	//g_pos_handle = 
	return ConnectMF(port,baud,(int)GetDesktopWindow());
}

int __stdcall CloseMF()
{
	return THIRD_CloseMF();
}

int __stdcall SMT_CloseMF280()
{
	return CloseMF();
}

int __stdcall PacketDelMoney(int money, int &flow_no)
{
	return THIRD_PacketDelMoney(money, flow_no);
}
int _stdcall SMT_PacketDelMomey(int nMoney,int &nFlowNo)
{
	return PacketDelMoney(nMoney,nFlowNo);
}

int __stdcall ReadBalance(int &money)
{
	return THIRD_ReadBalance(money);
}

int _stdcall SMT_ReadBalance(int &nMoney)
{
	return ReadBalance(nMoney);
}

int __stdcall MendPacket(int &bmoney, int &amoney) 
{
	return THIRD_MendPacket(bmoney, amoney);
}
int _stdcall SMT_MendPacket(int &BnMoney,int &AnMoney)
{
	return MendPacket(BnMoney,AnMoney);
}

int __stdcall ControlBuzzer()
{
	return THIRD_ControlBuzzer();
}
int _stdcall SMT_ControlBuzzer()
{
	return ControlBuzzer();
}

int __stdcall GetLastErrMsg(int ErrorCode, char *err_msg)
{
	return 0;
}

int __stdcall ReadStuempNo(unsigned char stuemp_no[21])
{
	return THIRD_ReadStuempNo(stuemp_no);
}
int _stdcall SMT_ReadCardNo(unsigned char ucCardNo[21])
{
	return ReadStuempNo(ucCardNo);
}

int __stdcall ReadSerial(unsigned char serial[5])
{
	return THIRD_ReadSerial(serial);
}


int __stdcall GetLastRecord(POSRECORD *pCardRecord)
{
	return THIRD_GetLastRecord(pCardRecord);
}
int _stdcall SMT_GetCardRecord()
{
	POSRECORD record;
	memset(&record,0,sizeof record);
	return GetLastRecord(&record);
}

char * __stdcall GetDllVersion()
{ 
	return dll_version;
}

int __stdcall ReadCardNO(int nCardNo[1])
{
	return THIRD_ReadCardNO(nCardNo);
}


int _stdcall SMT_ReadBlackCardFlag(unsigned char *ucBlackFlag)
{
	return -1;
}
int _stdcall SMT_ReadCardInfoExA(const char *field_name, 
								 unsigned char *field_value)
{
	return -1;
}
int _stdcall SMT_ReadCardInfo(TPublishCard *pc)
{
	return -1;
}

