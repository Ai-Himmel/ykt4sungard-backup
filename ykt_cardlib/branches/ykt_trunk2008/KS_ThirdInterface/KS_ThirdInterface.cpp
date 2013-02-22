#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "KS_ThirdInterface.h"
#include "DataType.h"
#include "..\include\carddll_def.h"

extern CLogFile g_log_file;

char buf_dll[512] = "";
char card_id_num[8] = "";
char iniFilePathBuf[512] = "";
char dll_version[] = "KS_ThirdInterface v1.03";
char str_card_length[20] = "";
char msg[128] = "";

static char pre_phycardno[9]="";
static TPublishCard gs_pc;

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
typedef int (CALLBACK *LPTHIRD_GetCard)(char *card_id,int *cur_bala,int nLen);
typedef int (CALLBACK *LPTHIRD_GetCardNumAndMoney)(char *strCardNum, int *curBalance, int Len);
typedef int (CALLBACK *LPSMT_ReadCardMainKey)(int wantflag);
typedef int (CALLBACK *LPSMT_SleepCard)();
typedef int (CALLBACK *LPTHIRD_AuthDevice)(int mode,int wantflag);

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
LPTHIRD_GetCard			THIRD_GetCard = NULL;
LPTHIRD_GetCardNumAndMoney THIRD_GetCardNumAndMoney = NULL;
LPTHIRD_AuthDevice		THIRD_AuthDevice = NULL;

LPSMT_SleepCard THIRD_SleepCard = NULL;

THIRD_DEF_RECALL_DLL(int,YKTSVR_Login,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Create,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Close,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_Exit,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetCardInfo,(char physical_no[9], CardInfo *card_info),(physical_no,card_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetCustomerInfo,(int cut_id, CutInfo *card_info),(cut_id,card_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_GetDataInfo,(char physical_no[9],  char stuemp_no[22], DataInfo *data_info),(physical_no,stuemp_no,data_info))
THIRD_DEF_RECALL_DLL(int,YKTSVR_SetCardKey,(),())
THIRD_DEF_RECALL_DLL(int,YKTSVR_ReadCardInfo,(char physical_no[9],TPublishCard *pc),(physical_no,pc))

BOOL APIENTRY DllMain( HINSTANCE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL_THIRD", "", buf_dll, sizeof(buf_dll), iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "CRAD_IDORNUM", "", card_id_num, sizeof(card_id_num), iniFilePathBuf);

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
		THIRD_GetCard				= (LPTHIRD_GetCard)GetProcAddress(hDLL,"THIRD_GetCard");
		THIRD_GetCardNumAndMoney    = (LPTHIRD_GetCardNumAndMoney)GetProcAddress(hDLL,"THIRD_GetCardNumAndMoney");
		THIRD_AuthDevice		= (LPTHIRD_AuthDevice)GetProcAddress(hDLL,"THIRD_AuthDevice");
		THIRD_SleepCard = (LPSMT_SleepCard)GetProcAddress(hDLL,"HaltCard");
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
			(!THIRD_GetLastRecord)		||
			(!THIRD_GetCard)			||
			(!THIRD_GetCardNumAndMoney) ||
			(!THIRD_AuthDevice)    ||
			(!THIRD_SleepCard)
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
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_GetDataInfo);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_SetCardKey);
		THIRD_LOAD_RECALL_DLL(hDLL,YKTSVR_ReadCardInfo);

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

int _stdcall SMT_ReadCardInfo(TPublishCard *pc)
{
	int ret = 0;
	unsigned char serial_no[5]="";
	char phy_no[9]="";
	char strCardNum[21] = "";
	int balance = 0;

	ret = THIRD_ReadSerial(serial_no);
	if (ret < 0)
	{
		return -1;
	}

	dec2hex(serial_no, 4, phy_no);
	ret = YKTSVR_ReadCardInfo(phy_no,pc);
	if(ret)
		return ret;
	ret = THIRD_ReadBalance(balance);
	if(ret)
		return ret;

	pc->Money = balance;

	memcpy(pre_phycardno,phy_no,8);
	memcpy(&gs_pc,pc,sizeof(gs_pc));
	return 0;
}

/*================================================================ 
* 函数名：    SMT_ReadCardInfoExA
* 参数：      [in] (const char *field_name)获取数据的域名称
*			  showno----显示卡号
*             cardno----交易卡号
*			  deallinedate----用户卡截至日期
*			  righttype----用户卡权限类型
*			  name---姓名
*			  dutyno----职位代码
*			  cerno----证件号码
*			  departno----部门代码
*			  sex----性别
*			  stuempno----学工号
*			  //pwd----密码
*             [out] (char *field_value)获取卡片中名称所对应的数据 					
* 功能描述:   读取卡信息字段
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int _stdcall SMT_ReadCardInfoExA(const char *field_name, 
								 unsigned char *field_value)
{
	int ret = 0;
	unsigned char serial_no[5]="";
	char phy_no[9]="";

	if (!field_name)
	{
		return 2;
	}

	ret = THIRD_ReadSerial(serial_no);
	if (ret < 0)
	{
		return -1;
	}
	dec2hex(serial_no, 4, phy_no);
	
	if(strncmp(pre_phycardno,phy_no,8) != 0)
	{
		memcpy(pre_phycardno,phy_no,8);
		ret = SMT_ReadCardInfo(&gs_pc);
		if(ret)
			return ret;		
	}

	if (0 == strcmp(field_name, "showno"))
	{
		memcpy(field_value, gs_pc.ShowCardNo, sizeof(gs_pc.ShowCardNo));
	}
	else if (0 == strcmp(field_name, "cardno"))
	{
		memcpy(field_value, gs_pc.CardNo, sizeof(gs_pc.CardNo));
	}
	else if (0 == strcmp(field_name, "deallinedate"))
	{
		memcpy(field_value, gs_pc.DeadLineDate, sizeof(gs_pc.DeadLineDate));
	}
	else if (0 == strcmp(field_name, "righttype"))
	{
		sprintf((char *)field_value, "%d", gs_pc.CardRightType);
	}
	else if (0 == strcmp(field_name, "name"))
	{
		memcpy(field_value, gs_pc.ucName, sizeof(gs_pc.ucName));			
	}
	else if (0 == strcmp(field_name, "dutyno"))
	{
		memcpy(field_value, gs_pc.ucDutyNo, sizeof(gs_pc.ucDutyNo));			
	}
	else if (0 == strcmp(field_name, "cerno"))
	{
		memcpy(field_value, gs_pc.ucCertificateNo, sizeof(gs_pc.ucCertificateNo));			
	}
	else if (0 == strcmp(field_name, "departno"))
	{
		memcpy(field_value, gs_pc.ucDepartmentNo, sizeof(gs_pc.ucDepartmentNo));			
	}
	else if (0 == strcmp(field_name, "sex"))
	{
		memcpy(field_value, gs_pc.ucSexNo, sizeof(gs_pc.ucSexNo));			
	}
	else if (0 == strcmp(field_name, "stuempno"))
	{
		memcpy(field_value, gs_pc.ucCardNo, sizeof(gs_pc.ucCardNo));			
	}
	else if (0 == strcmp(field_name, "pwd"))
	{
		memcpy(field_value, gs_pc.ucPwd, sizeof(gs_pc.ucPwd));			
	}
	else
	{
		return 0;
	}

	return 0;

	return 0;
}

int __stdcall SMT_AuthDevice(int mode,int wantflag)
{
	return THIRD_AuthDevice(mode,wantflag);
}

int __stdcall SMT_SleepCard()
{
	return THIRD_SleepCard();
}
