#include <Windows.h>
#include "DataType.h"
#include "HandleCard.h"
#include "LoadAppDll.h"
#include "ErrCode.h"

BOOL bCommOpenFlag = FALSE;

int __stdcall ConnectMF(int port, int baud)
{
	int nRetCode = 0;
	if (nRetCode = LoadV23PosDll())
		return nRetCode;

	if ((nRetCode = SMT_ConnectMF280(port, baud)) == 0)
		bCommOpenFlag = TRUE;
	
	SMT_ControlBuzzer();
	return nRetCode;
}

int __stdcall CloseMF()
{
	if (bCommOpenFlag)
		 return SMT_CloseMF280();
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall DelMomey(int nMoney,int &nFlowNo)
{
	if (bCommOpenFlag)
		return SMT_PacketDelMomey(nMoney, nFlowNo);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall MendPacket(int &BnMoney,int &AnMoney)
{
	if (bCommOpenFlag)
		return SMT_MendPacket(BnMoney, AnMoney);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall ReadStuEmpNo(unsigned char ucStuEmpNo[21])
{
	if (bCommOpenFlag)
		return SMT_ReadCardNo(ucStuEmpNo);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall ReadBalance(int &nMoney)
{
	if (bCommOpenFlag)
		return SMT_ReadBalance(nMoney);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall GetCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo)
{
	if (bCommOpenFlag)
		return SMT_ReadCustomerInfo(CutInfo);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall ReadCutName(unsigned char ucCutName[9])
{
	if (bCommOpenFlag)
		return SMT_ReadName(ucCutName);
	else
		return KS_ERR_NOTOPENCOM;
}

int __stdcall ReadCutSex(unsigned char ucCutSex[2])
{
	if (bCommOpenFlag)
		return SMT_ReadSex(ucCutSex);
	else
		return KS_ERR_NOTOPENCOM;
}