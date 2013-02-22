// TExportFunc.h: interface for the TExportFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXPORTFUNC_H__FB055868_1E22_4313_9BBD_408E920B7546__INCLUDED_)
#define AFX_TEXPORTFUNC_H__FB055868_1E22_4313_9BBD_408E920B7546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TSmartServer;

//******************************************************************************
//*名称: TExportFunc 
//*功能: 为业务模块定义的API集
//******************************************************************************
class TExportFunc 
{
public:
	TExportFunc();
	virtual ~TExportFunc();

	static TSmartServer *pServer;

public:
	static void FillAPI(TSSmartFunction *pFuncArray);

	static long SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
	static long BroadData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);
	static long SendMessage(char *pBuffer, long nLength);
	static long AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc);
	static long DelSmartDoc(long nAuthID);
	static long BroadcastPro(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize);

	static long __stdcall SendData(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
	static long __stdcall RecvData(char *pszBuffer, int nLen, int nTimeOut);
	static long __stdcall OutputRealData(TSSmartTask *pTask, TSSmartDoc *pDoc, int nType, unsigned char *ucRawData, int nDataLen);
	static long __stdcall GetParam(int nType, TSSystemParam *pParam);
	static long __stdcall ReportTaskResult(TSSmartTask *pTask, long iResult, TSResultData *pData);
	static long __stdcall ReadCardGSInfo(int nflag, TSGSJRecord *pRecord);
	static long __stdcall DownloadBlackCard(TSSmartDoc *pDoc, int nFlag, char *pszFileName);
	static long __stdcall OutputBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard);

	static long __stdcall SignIn(TSSmartDoc *pDoc);
	static long __stdcall SignOut(TSSmartDoc *pDoc);
};

#endif // !defined(AFX_TEXPORTFUNC_H__FB055868_1E22_4313_9BBD_408E920B7546__INCLUDED_)
