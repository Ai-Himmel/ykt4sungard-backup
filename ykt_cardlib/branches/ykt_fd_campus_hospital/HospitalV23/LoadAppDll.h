#ifndef _LOAD_APP_DLL_H_
#define _LOAD_APP_DLL_H_
#pragma once

#include "DataType.h"

/*================================================================ 
* 函数名：    LoadKingStarDll
* 参数：      [in] 无
* 功能描述:   加载V23读卡和获取后台信息动态库
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int LoadKingStarDll();

/*================================================================ 
* 函数名：    LoadV23PosDll
* 参数：      [in] 无
* 功能描述:   加载V23读卡信息动态库
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int LoadV23PosDll();

/*================================================================ 
* 函数名：    LoadGateWayDll
* 参数：      [in] 无
* 功能描述:   获取后台信息动态库
* 返回值：    无
================================================================*/
int LoadGateWayDll();

/*================================================================ 
* 函数名：    UnLoadKingStarDll
* 参数：      [in] 无
* 功能描述:   卸载V23读卡和获取后台信息动态库
* 返回值：    无
================================================================*/
void UnLoadKingStarDll();

/*================================================================ 
* 功能描述:   win32 dll加载动态库宏
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