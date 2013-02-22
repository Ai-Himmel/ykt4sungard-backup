// TSmartChannels.cpp: implementation of the TSmartChannels class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartChannels.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartChannels::TSmartChannels()
{
	m_pServer = NULL;
	m_hModule = NULL;

	m_bConnect = FALSE;
	m_bNotify  = FALSE;

	ZeroMemory(m_szServer, sizeof(m_szServer));

	m_nPort = 0 ;
	m_nEncode = 0 ;
	m_nNotify = 0 ;

	InitChannels = NULL ;
	DestoryChannels = NULL ;
	ConnectToCenter = NULL ;
	DisConnect = NULL ;
	CreateNotify = NULL ;
	CloseNotify = NULL ;

	SendData = NULL;
	RecvData = NULL;
	SendTick = NULL;
	SendDataPro = NULL ;
	RecvDataPro = NULL ;

    ReadSmartDocList = NULL;
    ReadSmartTaskPlan = NULL;
    ReportFinished = NULL;
    OutputRealData = NULL;
	GetParam = NULL ;
	SignIn = NULL ;
	SignOut = NULL;

	ReReloadSmartDocList = NULL;
	ReReadSmartTaskPlan  = NULL;	
}

TSmartChannels::~TSmartChannels()
{
	Destroy();
}

//初始化接口
void TSmartChannels::Initialized(char *pszModule, char *pszServer, int nPort, int nEndcode, int nNotify, 
		TSmartServer *pServer, int nFunc, int nServiceNo)
{
	if( pszModule == NULL || pszServer == NULL )
		return ;

	m_hModule = LoadLibrary(pszModule);
	if( m_hModule == NULL )
		throw TException("不能装入接口传输层动态库!", GetLastError());

    InitChannels = (lpfnInitChannels)GetProcAddress(m_hModule, "InitChannels");
    DestoryChannels = (lpfnDestoryChannels)GetProcAddress(m_hModule, "DestoryChannels");
    ConnectToCenter = (lpfnConnectToCenter)GetProcAddress(m_hModule, "ConnectToCenter");
    DisConnect = (lpfnDisConnect)GetProcAddress(m_hModule, "DisConnect");
    CreateNotify = (lpfnCreateNotify)GetProcAddress(m_hModule, "CreateNotify");
    CloseNotify = (lpfnCloseNotify)GetProcAddress(m_hModule, "CloseNotify");
    SendData = (lpfnSendData)GetProcAddress(m_hModule, "SendData");
    RecvData = (lpfnRecvData)GetProcAddress(m_hModule, "RecvData");
    SendTick = (lpfnSendTick)GetProcAddress(m_hModule, "SendTick");
    SendDataPro = (lpfnSendDataPro)GetProcAddress(m_hModule, "SendDataPro");
    RecvDataPro = (lpfnRecvDataPro)GetProcAddress(m_hModule, "RecvDataPro");

    ReadSmartDocList = (lpfnReadSmartDocList)GetProcAddress(m_hModule, "ReadSmartDocList");
    ReadSmartTaskPlan = (lpfnReadSmartTaskPlan)GetProcAddress(m_hModule, "ReadSmartTaskPlan");
    ReportFinished = (lpfnReportFinished)GetProcAddress(m_hModule, "ReportFinished");
    OutputRealData = (lpfnOutputRealData)GetProcAddress(m_hModule, "OutputRealData");
	GetParam = (lpfnGetParam)GetProcAddress(m_hModule, "GetParam");
	ReportTaskResult = (lpfnReportTaskResult)GetProcAddress(m_hModule, "ReportTaskResult");
	ReadCardGSInfo = (lpfnReadCardGSInfo)GetProcAddress(m_hModule, "ReadCardGSInfo");
	DownloadBlackCard = (lpfnDownloadBlackCard)GetProcAddress(m_hModule, "DownloadBlackCard");
	OutputBlackCard = (lpfnOutputBlackCard)GetProcAddress(m_hModule, "OutputBlackCard");
	SendDeviceTick =  (lpfnSendDeviceTick)GetProcAddress(m_hModule, "SendDeviceTick");
	SignIn = (lpfnSignIn)GetProcAddress(m_hModule, "SignIn");
	SignOut = (lpfnSignOut)GetProcAddress(m_hModule, "SignOut");
	ReReloadSmartDocList =  (lpfnReReloadSmartDocList)GetProcAddress(m_hModule, "ReReloadSmartDocList");	
	ReReadSmartTaskPlan  = (lpfnReReadSmartTaskPlan)GetProcAddress(m_hModule, "ReReadSmartTaskPlan");
	if( !InitChannels || !DestoryChannels || !ConnectToCenter || 
		!DisConnect || !CreateNotify || !CloseNotify || !RecvData || !SendData 
		|| !SendTick || !RecvDataPro || !SendDataPro || !OutputRealData || !ReadCardGSInfo
		|| !DownloadBlackCard || !OutputBlackCard || !SendDeviceTick || !SignIn || !SignOut
		|| !ReReloadSmartDocList || !ReReadSmartTaskPlan)
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL ;
		throw TException("不是合法的接口传输层动态库!");
	}

	if( InitChannels(nServiceNo, nFunc) != RET_OK )
	{
		FreeLibrary(m_hModule);
		m_hModule = NULL ;
		throw TException("不能连接到业务服务器!");
	}

	strcpy(m_szServer, pszServer);

	m_nPort = nPort;
	m_nEncode = nEndcode;
	m_nNotify = nNotify;
	m_pServer = pServer;

	if( ConnectToCenter(m_szServer, m_nPort, m_nEncode) != RET_OK )
	{
		m_bConnect = FALSE;
		throw TException("不能连接到金仕达业务服务器!");
	}
	else
	{
		printf("----连接金仕达业务服务器成功!\n");
		m_bConnect = TRUE;
	}


	if( CreateNotify(m_szServer, m_nPort) != RET_OK )
	{
		m_bNotify = FALSE;
		throw TException("不能连接到金仕达业务服务器!");
	}
	else
	{
		printf("----连接金仕达业务服务器成功!\n");
		m_bNotify = TRUE;
	}
}

//销毁接口
void TSmartChannels::Destroy()
{
/*	if( m_bConnect && DisConnect )
		DisConnect();

	if( m_bNotify && CloseNotify )
		CloseNotify();
*/
	if( m_hModule != NULL )
	{
		if( DestoryChannels )
		{
			DestoryChannels();
		}

		FreeLibrary(m_hModule);
		m_hModule = NULL ;
	}
}

bool TSmartChannels::ReadSmartDoc(TSSmartDoc *pSmartDoc, long *nRecCount)
{
	return ReadSmartDocList(pSmartDoc, nRecCount)==RET_OK?true:false;
}

bool TSmartChannels::ReConnect()
{
	if( !m_bConnect )
	{
		if( ConnectToCenter(m_szServer, m_nPort, m_nEncode) != RET_OK )
		{
			printf("----连接金仕达通讯平台接口失败!\n");
			m_bConnect = FALSE;
		}
		else
		{
			printf("----连接金仕达通讯平台接口成功!\n");
			m_bConnect = TRUE;
		}
	}

	if( !m_bNotify )
	{
		if( CreateNotify(m_szServer, m_nPort) != RET_OK )
		{
			m_bNotify = FALSE;
		}
		else
		{
			m_bNotify = TRUE;
		}
	}
	return true;
}

bool TSmartChannels::GetSmartTaskPlan(TSmartTaskObj *pTaskPlan)
{
	return ReadSmartTaskPlan(pTaskPlan)==RET_OK?true:false;
}

