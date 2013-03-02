// TSmartRegister.cpp: implementation of the TSmartRegister class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartRegister.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TSmartRegister::TSmartRegister()
{
	char  szDir[MAX_PATH];
	GetCurPath(szDir);
	sprintf(strServerINI, "%s\\SmartServer.ini", szDir);
	Reset();
}

TSmartRegister::~TSmartRegister()
{

}

void TSmartRegister::Reset()
{
	m_nPort = 3691 ;
	m_nMaxDev = 3000 ;

	strcpy(m_szTaskDLL, "Task.DLL"); 
	strcpy(m_szProtocol, "SmartTerminal.dll");

	m_nModule = 0 ;
	m_nMonitor = 0 ;	

	strcpy(m_szChannels, "");
	strcpy(m_szCenter, "");

	m_nCenterPort = 0; 
	m_nEncode = 0;
	m_nChannelsNotify = 0;

	m_nFunc = 9991;
	m_nServerNo = 0 ;
}

void TSmartRegister::ReadParameter()
{
    m_nMaxDev = GetPrivateProfileInt("SYSTEM", "MAXDEV", 4500, strServerINI);
    m_nPort   = GetPrivateProfileInt("SYSTEM", "PORT", 3896, strServerINI);

	GetPrivateProfileString("SYSTEM", "TASKDLL", "Task.DLL", m_szTaskDLL, 256, strServerINI);
	GetPrivateProfileString("SYSTEM", "PROTOCOL", "SmartTerminal.dll", m_szProtocol, 256, strServerINI);

    m_nMonitor = GetPrivateProfileInt("MONITOR", "COUNT", 0, strServerINI);
    m_nModule = GetPrivateProfileInt("MODULE", "COUNT", 0, strServerINI);

	if( m_nPort <= 1024 || m_nMaxDev <=10 || m_nMaxDev > 8500 ) 
	{
		throw TException("系统参数不正确, 请用SmartMonitor.exe重新设置!");
	}

	GetPrivateProfileString("INTERFACE", "FILENAME", "", m_szChannels, 256, strServerINI);
	GetPrivateProfileString("INTERFACE", "HOSTNAME", "127.0.0.1", m_szCenter, 256, strServerINI);
    m_nCenterPort = GetPrivateProfileInt("INTERFACE", "PORT", 4000, strServerINI);
    m_nChannelsNotify = GetPrivateProfileInt("INTERFACE", "PORT", 4000, strServerINI);
    m_nEncode = GetPrivateProfileInt("INTERFACE", "ENDCODE", 0, strServerINI);
	m_nFunc = GetPrivateProfileInt("INTERFACE", "CHILDFUNC", 9991, strServerINI);
	m_nServerNo = GetPrivateProfileInt("INTERFACE", "SERVERNO", 0, strServerINI);
	m_nCollData_Tick=GetPrivateProfileInt("INTERFACE", "CollDATA_TICK", 5000, strServerINI);
	m_nNoTask_Tick=GetPrivateProfileInt("INTERFACE", "NOTASK_TICK", 2000, strServerINI);
}

bool TSmartRegister::GetModule(char *pszFileName, int nIndex)
{
	TCHAR  szItem[64];
	TCHAR  szFileName[MAX_PATH];

	wsprintf(szItem, "MODULE%d", nIndex);
	if( GetPrivateProfileString("MODULE", szItem, "", szFileName, MAX_PATH, strServerINI) > 0 )
	{
		TCHAR  szDir[MAX_PATH];
		GetCurPath(szDir);
		sprintf(pszFileName, "%s\\%s", szDir, szFileName);
		return true;
	}

	return false;
}

bool TSmartRegister::GetMonitor(char *pHost, char *pUser, char *pPass)
{
	TCHAR  szItem[64];
	long   nIndex = 1 ;

	wsprintf(szItem, "HOST%d", nIndex);
	if( GetPrivateProfileString("MONITOR", szItem, "", pHost, 128, strServerINI) > 0 )
	{
		wsprintf(szItem, "USER%d", nIndex);
		if( GetPrivateProfileString("MONITOR", szItem, "", pUser, 32, strServerINI) > 0 )
		{
			wsprintf(szItem, "PASS%d", nIndex);
			GetPrivateProfileString("MONITOR", szItem, "", pPass, 32, strServerINI);
			return true;
		}
	}

	return false;
}

