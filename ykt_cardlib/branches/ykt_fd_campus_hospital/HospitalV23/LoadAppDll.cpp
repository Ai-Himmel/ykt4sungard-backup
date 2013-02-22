#include <Windows.h>
#include "LoadAppDll.h"
#include "ErrCode.h"

DEF_DLLFUNC(KInitLocal);
DEF_DLLFUNC(KGetCurBalance);
DEF_DLLFUNC(KGetTradeSerial);
DEF_DLLFUNC(SMT_ConnectMF280);
DEF_DLLFUNC(SMT_CloseMF280);
DEF_DLLFUNC(SMT_PacketDelMomey);
DEF_DLLFUNC(SMT_MendPacket);
DEF_DLLFUNC(SMT_ReadCardNo);
DEF_DLLFUNC(SMT_ReadBalance);
DEF_DLLFUNC(SMT_ControlBuzzer);
DEF_DLLFUNC(SMT_ReadCustomerInfo);
DEF_DLLFUNC(SMT_ReadName);
DEF_DLLFUNC(SMT_ReadSex);

HINSTANCE hGateWayDll = NULL, 
		  hFuDanV23Dll = NULL;

int LoadKingStarDll()
{
	return 0;
}

int LoadV23PosDll()
{
	hFuDanV23Dll = ::LoadLibrary("FunDan_V23.dll");
	if (hFuDanV23Dll == NULL)
		return KS_ERR_NOFUDANLIBRARY;

	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ConnectMF280);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_CloseMF280);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_PacketDelMomey);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_MendPacket);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ReadCardNo);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ReadBalance);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ControlBuzzer);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ReadCustomerInfo);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ReadName);
	LOAD_DLLFUNC(hFuDanV23Dll,SMT_ReadSex);
	return 0;
}

int LoadGateWayDll()
{
	hGateWayDll = ::LoadLibrary("gwdll.dll");
	if (hGateWayDll == NULL)
		return KS_ERR_NOGWLIBRARY;

	LOAD_DLLFUNC(hGateWayDll,KInitLocal);
	LOAD_DLLFUNC(hGateWayDll,KGetCurBalance);
	LOAD_DLLFUNC(hGateWayDll,KGetTradeSerial);
	return 0;
}

void UnLoadKingStarDll()
{
	if (hGateWayDll)
	{
		::FreeLibrary(hGateWayDll);
		hGateWayDll = NULL;
	}

	if (hFuDanV23Dll)
	{
		::FreeLibrary(hFuDanV23Dll);
		hFuDanV23Dll = NULL;
	}

	return;
}
