#include <stdio.h>
#include <comdef.h>
#include "DrcomInterface.h"
#include "NetChargeErrCode.h"
#include "ComFunNetCharge.h"
#include <atlstr.h>

int GetAccoutInfo(char *szStuEmpNo, double *dRemainBalance)
{
	::CoInitialize( NULL );

	HRESULT hResult = 0;
	IBusiness *pIBus = NULL;
	BOOL bRetFlag = FALSE;
//	DATE tmDate;
	int nOffSetTime = 0;
	int nRetCode = 0;
	int nAccoutState = 0;
	int nErrCode = 0;
//	SYSTEMTIME sysTime;
	_bstr_t bstrAccount(szStuEmpNo);
	hResult = CoCreateInstance(CLSID_Business, 
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IBusiness,
		(void**)&pIBus);

	if (!SUCCEEDED(hResult))
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_NO_INTERFACE, L_RETU)

/************************************************************************/
/* 测试数据库会花去超时大约将近20秒钟(无数据库情况)                     */
/************************************************************************/
/*
	pIBus->TestConnectDB(&bRetFlag);
	if (!bRetFlag)
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_CONNECT_DB, L_RETU)
*/

/*
	pIBus->IsExist(bstrAccount, &bRetFlag);
	if (!bRetFlag)
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_NO_ACCOUNT, L_RETU)
		//		return NETCHARGE_ERR_NO_ACCOUNT;
*/

	pIBus->GetState(bstrAccount, &nAccoutState, &nRetCode);
	if (0 == nRetCode)
	{
		/*
		if (0 == nAccoutState)
			RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_STOP_SERVICE, L_RETU)
			//			return NETCHARGE_ERR_STOP_SERVICE;

		
		if (2 == nAccoutState)
				RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_STOP_OWE_FEE, L_RETU)
				//			return NETCHARGE_ERR_STOP_OWE_FEE;
	    */
	}
	else
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)
		//		return nRetCode;				// 从错误码列表中读取

	pIBus->GetBalance(bstrAccount, dRemainBalance, &nRetCode);
	if (nRetCode != 0)
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)
/*
	pIBus->GetBill(bstrAccount, dOweBalance, &nRetCode);
	if (nRetCode != 0)
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)
*/
	/*
	pIBus->GetTermDate(bstrAccount, &tmDate, &nRetCode);
	if (0 == nRetCode)
	{
		// OLE时间转换成char*类型的字符串
		if (VariantTimeToSystemTime(tmDate, &sysTime) != TRUE)
			RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_CONVERSION_TIME, L_RETU)

		nOffSetTime = sprintf(szAccSerOutOfDate, "%d", sysTime.wYear);
		nOffSetTime += sprintf(szAccSerOutOfDate + nOffSetTime, "%02d", sysTime.wMonth);
		nOffSetTime += sprintf(szAccSerOutOfDate + nOffSetTime, "%02d", sysTime.wDay); 	
	}
	else
		nErrCode = nRetCode;
	*/

L_RETU:
	pIBus->Release();
	CoUninitialize();
	return nErrCode;
}

int NetChargeTrans(char *szStuEmpNo, double *dRemainBalance, double *dTransBalance,char *oper)
{
	::CoInitialize( NULL );

	HRESULT hResult = 0;
	IBusiness *pIBus = NULL;
	BOOL bRetFlag = FALSE;
	int nRetCode = 0;
	int nAccoutState = 0;
	int nErrCode = 0;
	_bstr_t bstrAccount(szStuEmpNo);
	_bstr_t bstrOper(oper);
	hResult = CoCreateInstance(CLSID_Business, 
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IBusiness,
		(void**)&pIBus);

	if (!SUCCEEDED(hResult))
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_NO_INTERFACE, L_RETU)

/*
	pIBus->TestConnectDB(&bRetFlag);
	if (!bRetFlag)
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_CONNECT_DB, L_RETU)
*/

/*
	pIBus->IsExist(bstrAccount, &bRetFlag);
	if (!bRetFlag)
		RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_NO_ACCOUNT, L_RETU)
*/

	pIBus->GetState(bstrAccount, &nAccoutState, &nRetCode);
	if (0 == nRetCode)
	{
		/*
		if (0 == nAccoutState)
			RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_STOP_SERVICE, L_RETU)
	
			if (2 == nAccoutState)
				RETURN_ERRCODE(nErrCode, NETCHARGE_ERR_STOP_OWE_FEE, L_RETU)
	*/
	}
	else
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)

	pIBus->GetBalance(bstrAccount, dRemainBalance, &nRetCode);
	if (nRetCode != 0)
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)

	
	//pIBus->Deposit(bstrAccount, *dTransBalance, (L""), (L""), 0, &nRetCode);
	pIBus->Deposit(bstrAccount, *dTransBalance,bstrOper, (L""), 0, &nRetCode);
	if (nRetCode != 0)
		RETURN_ERRCODE(nErrCode, nRetCode, L_RETU)
	/*
	pIBus->ForceUpdateBalance(bstrAccount, *dRemainBalance + *dTransBalance, &nRetCode);
	if (nRetCode != 0)
		nErrCode = nRetCode;
	*/
	*dRemainBalance += *dTransBalance;

L_RETU:
	pIBus->Release();
	CoUninitialize();
	return nErrCode;
}