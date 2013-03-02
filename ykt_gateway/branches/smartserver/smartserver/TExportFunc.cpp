// TExportFunc.cpp: implementation of the TExportFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TExportFunc.h"
#include "TSmartServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartServer *TExportFunc::pServer = NULL ;

TExportFunc::TExportFunc()
{

}

TExportFunc::~TExportFunc()
{

}

long TExportFunc::SendRequest(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	return pServer->SendRequest(pDoc, pBuffer);
}

long TExportFunc::BroadData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer)
{
	return pServer->BroadData(pDoc, pBuffer);
}

long TExportFunc::BroadcastPro(char *pszCmd, TSSmartDoc *pDoc, void *pData, long nSize)
{
	pServer->BroadcastPro(pszCmd, pDoc, pData, nSize);
	return RET_OK;
}

long TExportFunc::SendMessage(char *pBuffer, long nLength)
{
	pServer->BroadDataEx(pBuffer, nLength);
	return RET_OK;
}

long TExportFunc::AddNewSmartDoc(long nParentID, long nPort, TSSmartDoc *pDoc)
{
	return pServer->AddNewSmartDoc(nParentID, nPort, pDoc);
}

long TExportFunc::DelSmartDoc(long nAuthID)
{
	return pServer->DelSmartDoc(nAuthID);
}

long TExportFunc::SendData(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter)
{
	return pServer->m_Channels.SendData(nDest, nFunc, pszData, nLen, nPriority, bRouter);
}

long TExportFunc::RecvData(char *pszBuffer, int nLen, int nTimeOut)
{
	return pServer->m_Channels.RecvData(pszBuffer, nLen, nTimeOut);
}

long TExportFunc::OutputRealData(TSSmartTask *pTask, TSSmartDoc *pDoc, int nType, unsigned char *ucRawData, int nDataLen)
{
	return pServer->m_Channels.OutputRealData(pTask, pDoc, nType, ucRawData, nDataLen);
}

long TExportFunc::GetParam(int nType, TSSystemParam *pParam)
{
	return pServer->m_Channels.GetParam(nType, pParam);
}

long TExportFunc::ReportTaskResult(TSSmartTask *pTask, long iResult, TSResultData *pData)
{
	return pServer->m_Channels.ReportTaskResult(pTask, iResult, pData);
}

long TExportFunc::DownloadBlackCard(TSSmartDoc *pDoc, int nFlag, char *pszFileName)
{
	return pServer->m_Channels.DownloadBlackCard(pDoc, nFlag, pszFileName);
}

long TExportFunc::OutputBlackCard(TSSmartDoc *pDoc, long nFlag, TSBlackCard *pCard)
{
	return pServer->m_Channels.OutputBlackCard(pDoc, nFlag, pCard);
}

long TExportFunc::ReadCardGSInfo(int nflag, TSGSJRecord *pRecord)
{
	return pServer->m_Channels.ReadCardGSInfo(nflag, pRecord);
}

long TExportFunc::SignIn(TSSmartDoc *pDoc)
{
	return pServer->m_Channels.SignIn(pDoc);
}

long TExportFunc::SignOut(TSSmartDoc *pDoc)
{
	return pServer->m_Channels.SignOut(pDoc);
}

void TExportFunc::FillAPI(TSSmartFunction *pFuncArray)
{
	pFuncArray->fnSendRequest = SendRequest ;
	pFuncArray->fnBroadData = BroadData ;
	pFuncArray->fnAddNewSmartDoc = AddNewSmartDoc;
	pFuncArray->fnDelSmartDoc = DelSmartDoc;
	pFuncArray->fnBroadMessage = SendMessage;
	pFuncArray->fnBroadcastPro = BroadcastPro;

	pFuncArray->fnSendData = SendData;
	pFuncArray->fnRecvData = RecvData;
	pFuncArray->fnOutputRealData = OutputRealData;
	pFuncArray->fnGetParam = GetParam;
	pFuncArray->fnReportTaskResult = ReportTaskResult;
	pFuncArray->fnReadCardGSInfo = ReadCardGSInfo;
	pFuncArray->fnDownloadBlackCard = DownloadBlackCard;
	pFuncArray->fnOutputBlackCard = OutputBlackCard;

	pFuncArray->fnSignIn = SignIn;
	pFuncArray->fnSignOut = SignOut;

	SendMsg = SendMessage;
}
