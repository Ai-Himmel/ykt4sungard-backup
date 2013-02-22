// TSmartChannels.h: interface for the TSmartChannels class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTCHANNELS_H__A51E0BED_A1E1_43FB_9118_C257C9CC8AD7__INCLUDED_)
#define AFX_TSMARTCHANNELS_H__A51E0BED_A1E1_43FB_9118_C257C9CC8AD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SmartServer.h"
#include "TSmartPacket.h"

class TSmartServer;

typedef long (__stdcall *lpfnInitChannels)(int nServer, int nFunc);
typedef long (__stdcall *lpfnDestoryChannels)();
typedef long (__stdcall *lpfnConnectToCenter)(char *pszServer, int nPort, int nEncode);
typedef long (__stdcall *lpfnDisConnect)();
typedef long (__stdcall *lpfnCreateNotify)(char *pszBind, int nPort);
typedef long (__stdcall *lpfnCloseNotify)();
typedef long (__stdcall *lpfnSendTick)();
typedef long (__stdcall *lpfnParseNotify)(unsigned char *pszData, int nLen);
//typedef long (__stdcall *lpfnSendData)(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
//typedef long (__stdcall *lpfnRecvData)(char *pszBuffer, int nLen, int nTimeOut);
typedef long (__stdcall *lpfnSendDataPro)(int nDest, int nFunc, char *pszData, int nLen, int nPriority, bool bRouter);
typedef long (__stdcall *lpfnRecvDataPro)(char *pszBuffer, int nLen, int nTimeOut);
typedef long (__stdcall *lpfnReadSmartDocList)(TSSmartDoc *pSmartDoc, long *nRecCount);
typedef long (__stdcall *lpfnReadSmartTaskPlan)(TSSmartTaskPlan *pTaskPlan);
typedef long (__stdcall *lpfnReportFinished)(TSSmartTaskPlan *pTaskPlan);

typedef long (__stdcall *lpfnReReloadSmartDocList)();
typedef long (__stdcall *lpfnReReadSmartTaskPlan)(TSSmartTaskPlan *pTaskPlan);

//************************************************************************************
//*名称: TSmartChannels
//*功能: 前置采集对外的通道接口(用于复旦的中间传输层)
//************************************************************************************
class TSmartChannels
{
public:
	TSmartServer*			m_pServer;
	HMODULE					m_hModule;

	lpfnInitChannels		InitChannels;
	lpfnDestoryChannels		DestoryChannels;
	lpfnConnectToCenter		ConnectToCenter;
	lpfnDisConnect			DisConnect;
	lpfnCreateNotify		CreateNotify;
	lpfnCloseNotify			CloseNotify;
	lpfnSendData			SendData;
	lpfnRecvData			RecvData;
	lpfnSendTick			SendTick;
	lpfnParseNotify			ParseNotify;
	lpfnSendDataPro			SendDataPro;
	lpfnRecvDataPro			RecvDataPro;
	lpfnReadSmartDocList	ReadSmartDocList;
	lpfnReadSmartTaskPlan	ReadSmartTaskPlan;
	lpfnReportFinished		ReportFinished;
	lpfnOutputRealData		OutputRealData;
	lpfnGetParam			GetParam;
	lpfnReportTaskResult	ReportTaskResult;
	lpfnReadCardGSInfo		ReadCardGSInfo;
	lpfnDownloadBlackCard	DownloadBlackCard;
	lpfnOutputBlackCard		OutputBlackCard;
	lpfnSendDeviceTick		SendDeviceTick;
	lpfnSignIn				SignIn;
	lpfnSignOut				SignOut;
	lpfnReReloadSmartDocList ReReloadSmartDocList;
	lpfnReReadSmartTaskPlan ReReadSmartTaskPlan;
	char                    m_szServer[256];
	int						m_nPort;
	int						m_nEncode;
	int						m_nNotify;
	BOOL					m_bConnect;
	BOOL					m_bNotify;

public:
	TSmartChannels();
	virtual ~TSmartChannels();

	void Initialized(char *pszModule,
					char *pszServer, 
					int nPort, 
					int nEndcode,
					int nNotify,
					TSmartServer *pServer,
					int nFunc,
					int nServiceNo);
	void Destroy();

	bool ReConnect();
	bool ReadSmartDoc(TSSmartDoc *pSmartDoc, long *nRecCount);
	bool GetSmartTaskPlan(TSmartTaskObj *pTaskPlan);

	friend class TSmartServer;
};

#endif // !defined(AFX_TSMARTCHANNELS_H__A51E0BED_A1E1_43FB_9118_C257C9CC8AD7__INCLUDED_)
