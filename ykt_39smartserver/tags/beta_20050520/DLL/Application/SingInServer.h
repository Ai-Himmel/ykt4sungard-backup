// SingInServer.h: interface for the CSingInServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGINSERVER_H__B3414195_4375_44E9_BB3C_C102C4C64155__INCLUDED_)
#define AFX_SINGINSERVER_H__B3414195_4375_44E9_BB3C_C102C4C64155__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************
//*名称: CJZHistoryData
//*功能: 终端机签到
//*******************************************************************************
class CSingInServer : public COperator  
{
protected:
	void OnPacketError(long nResult);
	bool InsertTask(TSSmartDoc *pDoc);
	long ProcessSingIn(TSDeviceInfo *pDevInfo, TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	bool GetAuthKey(char *pszString);
	bool GetSmartDocInfo(char *pszRegNo, TSSmartDoc *pDoc);

public:
	CSingInServer();
	virtual ~CSingInServer();

	long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);

	long SignInProcess(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, long nPort, TSSmartTask *pTask);
};

#endif // !defined(AFX_SINGINSERVER_H__B3414195_4375_44E9_BB3C_C102C4C64155__INCLUDED_)
