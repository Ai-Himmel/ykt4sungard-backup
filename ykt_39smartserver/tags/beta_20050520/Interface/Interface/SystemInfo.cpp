// SystemInfo.cpp: implementation of the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemInfo::CSystemInfo()
{
	Clear();
	GetNetcardInfo();
	GetWinSystemInfo();
}

CSystemInfo::~CSystemInfo()
{

}

//清除
void CSystemInfo::Clear()
{
	ZeroMemory(szHostName, sizeof(szHostName));
	ZeroMemory(szMAC, sizeof(szMAC));
	ZeroMemory(szIP, sizeof(szIP));

	nDiskTotalSpace = 1 ;
	nDiskFreeSpace = 1 ;
	nProcessNumber = 0 ;
	nThreadNumber = 0 ;
	nMemoryTotal = 1 ;
	nUserMemory = 1 ;
	nTCPNumber = 0 ;
	nNetCardNumber = 0 ;

	SOCKADDR_IN sockAddr;

	ZeroMemory(&sockAddr, sizeof(sockAddr));
	gethostname(szHostName, sizeof(szHostName));

	LPSTR lpszAscii = (LPSTR)szHostName;
	LPHOSTENT lphost;
	lphost = gethostbyname(lpszAscii);
	if (lphost != NULL)
	{
		sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		sprintf(szIP, "%d.%d.%d.%d", 
			sockAddr.sin_addr.S_un.S_un_b.s_b1, 
			sockAddr.sin_addr.S_un.S_un_b.s_b2, 
			sockAddr.sin_addr.S_un.S_un_b.s_b3, 
			sockAddr.sin_addr.S_un.S_un_b.s_b4);
	}
}

//得到网卡信息(基于Netbios)
void CSystemInfo::GetNetcardInfo()
{
	NCB  ncb;
	LANA_ENUM  lanEnum;

	ZeroMemory(&ncb, sizeof(ncb));

	ncb.ncb_length = sizeof(lanEnum);
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (PUCHAR)&lanEnum;

	Netbios(&ncb);

	if( lanEnum.length > 0 )
	{
		ZeroMemory(&ncb, sizeof(ncb));
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lanEnum.lana[0];

		Netbios(&ncb);

		if( ncb.ncb_retcode == NRC_GOODRET )
		{
			ZeroMemory(&ncb, sizeof(ncb));
			ncb.ncb_command = NCBASTAT;
			ncb.ncb_lana_num = lanEnum.lana[0];
			strcpy((char*)ncb.ncb_callname, "*");

			struct astat
			{
				ADAPTER_STATUS adapt;
			    NAME_BUFFER namebuff[30];
			}adapter;

			ZeroMemory(&adapter, sizeof(adapter));
			ncb.ncb_buffer = (PUCHAR)&adapter;
			ncb.ncb_length = sizeof(adapter);

			Netbios(&ncb);

			sprintf(szMAC,"%.2X-%.2X-%.2X-%.2X-%.2X-%.2X", 
				adapter.adapt.adapter_address[0], 
				adapter.adapt.adapter_address[1], 
				adapter.adapt.adapter_address[2], 
				adapter.adapt.adapter_address[3], 
				adapter.adapt.adapter_address[4], 
				adapter.adapt.adapter_address[5]);
		}
	}

	//得到C:盘空间
	TCHAR szDir[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, szDir);

	DWORD n1 = 0, n2 = 0, n3 = 0, n4=0 ;
	GetDiskFreeSpace("C:\\", &n1, &n2, &n3, &n4);

	nDiskTotalSpace = (n1*n2/1024)*n4;
	nDiskFreeSpace = (n1*n2/1024)*n3;
}

void CSystemInfo::GetWinSystemInfo()
{
	HQUERY	hQuery = NULL ;
	char   szPathBuffer[MAX_PATH];

	if( PdhOpenQuery(NULL, NULL, &hQuery) != ERROR_SUCCESS )
		return ;

	ZeroMemory(szPathBuffer, sizeof(szPathBuffer));

	PDH_FMT_COUNTERVALUE  fmtValue;

	//CPU使用率
//	strcpy(szPathBuffer, "\\Processor(_Total)\\% Processor Time");
	strcpy(szPathBuffer, "\\Processor(0)\\% Processor Time");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nCPU = fmtValue.longValue ;
	}

	//进程数
	strcpy(szPathBuffer, "\\System\\Processes");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nProcessNumber = fmtValue.longValue;
	}

	//线程数
	strcpy(szPathBuffer, "\\System\\Threads");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nThreadNumber =fmtValue.longValue;
	}

	strcpy(szPathBuffer, "\\Memory\\Commit Limit");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nMemoryTotal =fmtValue.longValue;
	}

	strcpy(szPathBuffer, "\\Memory\\Committed Bytes");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nUserMemory =fmtValue.longValue;
	}

	PdhCloseQuery(hQuery);
}

bool CSystemInfo::GetSysItemInfo(HQUERY	hQuery, 
								 char *pszPath, 
								 DWORD nType, 
								 PDH_FMT_COUNTERVALUE& fmtValue)
{
	DWORD dwType;
	HCOUNTER  hCounter ;
	if( PdhAddCounter(hQuery, pszPath, 0, &hCounter) != ERROR_SUCCESS )
		return false;

	if( PdhCollectQueryData(hQuery) != ERROR_SUCCESS )
		return false;

	if( PdhGetFormattedCounterValue(hCounter, nType, &dwType, &fmtValue) != ERROR_SUCCESS )
		return false;

	return true;
}


