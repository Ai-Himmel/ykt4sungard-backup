// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_)
#define AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int HOSTNAME_LEN = 256 ;
const int IP_ADDRESS_LEN = 32 ;
const int MAC_ADDRESS_LEN = 64;

//******************************************************************************
//*名称: CSystemInfo
//*功能: 得到系统信息
//******************************************************************************
class CSystemInfo  
{
public:
	char	szHostName[256];		//主机名
	char	szMAC[MAC_ADDRESS_LEN];	//第一块网卡的MAC地址
	char	szIP[32];				//第一块网卡的IP地址
	long	nCPU;					//CPU使用率
	long	nDiskTotalSpace;		//磁盘总空间
	long	nDiskFreeSpace;			//磁盘剩余空间
	long	nProcessNumber;			//当前系统进程数
	long	nThreadNumber;			//当前系统线程数
	long	nMemoryTotal;			//总共内存数K (包括虚拟内存)
	long	nUserMemory;			//已用内存数K (包括虚拟内存)
	long	nTCPNumber;				//系统中已建立的 TCP连接个数

	int		nNetCardNumber;			//网卡数量

protected:
	bool GetSysItemInfo(HQUERY	hQuery, char *pszPath, DWORD nType, PDH_FMT_COUNTERVALUE& fmtValue);

public:
	CSystemInfo();
	virtual ~CSystemInfo();

	void Clear();
	void GetNetcardInfo();
	void GetWinSystemInfo();
};

#endif // !defined(AFX_SYSTEMINFO_H__B4EDCBCE_5054_4A0A_96FE_2F9D433BEDAE__INCLUDED_)
