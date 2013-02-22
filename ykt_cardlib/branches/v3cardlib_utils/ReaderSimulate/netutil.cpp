#include "StdAfx.h"
#include "netutil.h"

#ifdef WIN32
#include <WinSock2.h>
#include <IPHlpApi.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Ws2_32.lib")

int KSGNetUtil::GetMacByIP(const std::string ip, std::string &mac)
{
	char mac_str[30] = "";
	int nRemoteAddr = inet_addr( ip.c_str() );
	hostent host;
	hostent * remoteHostent= &host;
	struct in_addr sa;
	memset(&host,0,sizeof(host));
	//获取远程机器名
	sa.s_addr = nRemoteAddr;
	remoteHostent = gethostbyaddr((char*)&nRemoteAddr,4, AF_INET);
	if ( NULL == remoteHostent )
		return -1;
	//发送ARP查询包获得远程MAC地址

	unsigned char macAddress[6];
	ULONG macAddLen = 6;
	DWORD iRet=SendARP(nRemoteAddr, (unsigned long)NULL,(PULONG)&macAddress, &macAddLen);
	if ( NO_ERROR == iRet )
	{
		int i =0;
		int j = 0;
		for( ; i<5; i++ )
		{
			j += sprintf(mac_str+j,"%.2X-", macAddress[i] );
		}
		sprintf(mac_str+j,"%.2X",macAddress[i]);
		mac = mac_str;
	}
	else
		return -1;
	return 0;
}

#else
int KSGNetUtil::GetMacByIP(const std::string ip, std::string &mac)
{
	return -1;
}

#endif

void KSGNetUtil::GetLocalIP(std::vector<std::string>&ip_list)
{
	char HostName[512];
	int i;
	hostent* lpHostEnt;
	struct in_addr addr[5];
	for (i=0; i<2; i++)
		memset(&addr[i],0,sizeof(in_addr));
	// 得到本主机名
	if(gethostname(HostName,sizeof(HostName))==SOCKET_ERROR)
	{
		return ;
	}
	lpHostEnt=gethostbyname(HostName);//利用得到的主机名去获得主机结构
	if (!lpHostEnt)
	{
		return ;
	}

	for (i=0; lpHostEnt->h_addr_list[i]!=0; i++)
		//从主机地址表中得到IP地址
	{
		memcpy(&addr[i],lpHostEnt->h_addr_list[i],sizeof(in_addr));
		ip_list.push_back(std::string(inet_ntoa(addr[i])));
	}
}