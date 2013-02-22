#include <Windows.h>
#include "DataType.h"
#include "RequestBGInfo.h"
#include "LoadAppDll.h"
#include "ErrCode.h"

BOOL bLoginFlag = FALSE;

int __stdcall Login()
{
	int nRetCode = 0;
	if (nRetCode = LoadGateWayDll())
		return nRetCode;

	if (nRetCode = KInitLocal())
		return nRetCode;

	bLoginFlag = TRUE;
	return 0;
}

int __stdcall GetCurBalance(const char szStuempNo[21], double *dCurBalance)
{
	int nRetCode = 0;
	if (!bLoginFlag)
		return KS_ERR_NOTLOGIN;

	if (nRetCode = KGetCurBalance(szStuempNo, dCurBalance))
		return nRetCode;

	return 0;
}

int __stdcall GetDataInfo(const char szStuempNo[21], double *dCurBalance)
{
	int nRetCode = 0;
	if (!bLoginFlag)
		return KS_ERR_NOTLOGIN;

	if (nRetCode = KGetCurBalance(szStuempNo, dCurBalance))
		return nRetCode;

	return 0;
}

//int __stdcall GetTradeSerial(const char szStuempNo[21], TradeSerial Serial[], int *nNextFlag, int nInputFlag, const char szSerialYear[5], const char szSerialMonth[3], const char szBeginDay[3], const char szEndDay[3])
int __stdcall GetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11])
{
	int nRetCode = 0;
	if (!bLoginFlag)
		return KS_ERR_NOTLOGIN;

	if (nRetCode = KGetTradeSerial(nDeviceId, Serial, nNextFlag, nInputFlag, szBeginDate, szEndDate))
		return nRetCode;

	return 0;
}