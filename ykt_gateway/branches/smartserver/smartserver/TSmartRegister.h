// TSmartRegister.h: interface for the TSmartRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_)
#define AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//************************************************************************************
//*名称: TSmartRegister  
//*功能: 服务器参数
//************************************************************************************
class TSmartRegister  
{
public:
	TCHAR   strServerINI[MAX_PATH];

	int     m_nPort;
	long    m_nMaxDev;
	char    m_szTaskDLL[MAX_PATH];

	int     m_nModule;
	int     m_nMonitor;
	
	char    m_szProtocol[MAX_PATH];

	//对外接口通道
	char    m_szChannels[MAX_PATH];
	char    m_szCenter[128];
	int     m_nCenterPort;
	int     m_nEncode;
	int     m_nChannelsNotify;
	int		m_nFunc;
	int		m_nServerNo;
	long	m_nCollData_Tick;	//采集数据任务的间隔时间
	long	m_nNoTask_Tick;		//没有任务时的心跳间隔时间

public:
	TSmartRegister();
	virtual ~TSmartRegister();

	void Reset();
	void ReadParameter();

	bool GetModule(char *pszFileName, int nIndex);
	bool GetMonitor(char *pHost, char *pUser, char *pPass);
};

#endif // !defined(AFX_TSMARTREGISTER_H__18559704_303A_46A8_9C19_DFDE871011A4__INCLUDED_)
