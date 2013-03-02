
#include "netutil.h"
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <ace/SOCK_Stream.h>
#include <ace/Time_Value.h>

#ifdef WIN32
#include "ksglobal.h"
#undef _WINSOCKAPI_ // _WINSOCK2API_ 
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
	remoteHostent = gethostbyaddr( (char*)&nRemoteAddr,4, AF_INET );
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

void KSGNetUtil::GetLocalIP(std::list<std::string>&ip_list)
{
	char HostName[512];
	int i;
	struct hostent* lpHostEnt;
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

#else
#include "iptool.h"

void KSGNetUtil::GetLocalIP(std::list<std::string>&ip_list)
{
	struct ifi_info *ifi, *ifihead;
	struct sockaddr *sa;
	u_char *ptr;
	char * ip_addr;
	int i, family, doaliases;
	family = AF_INET;
	doaliases = 1;

	for(ifi = ifihead = get_ifi_info(family,doaliases);
		ifi != NULL; ifi = ifi->ifi_next)
	{
		if((sa = ifi->ifi_addr) != NULL)
		{
			ip_addr = strdup(sock_ntop(sa,sizeof(*sa)));
			ip_list.push_back(std::string(ip_addr));
		}
	}
	free_ifi_info(ifihead);
}

int KSGNetUtil::GetMacByIP(const std::string ip, std::string &mac)
{
	struct ifi_info *ifi, *ifihead;
	struct sockaddr *sa;
	u_char *ptr;
	char mac_str[20] = "";
	std::string ipaddr;
	int i,j,ret, family, doaliases;

	family = AF_INET;
	doaliases = 1;
	ret = -1;

	for(ifi = ifihead = get_ifi_info(family,doaliases);
		ifi != NULL; ifi = ifi->ifi_next)
	{
		if((sa = ifi->ifi_addr) != NULL)
		{
			ipaddr = sock_ntop(sa,sizeof(*sa));
			if(ipaddr == ip)
			{
				if(( i = ifi->ifi_hlen) > 0)
				{
					ptr = ifi->ifi_haddr;
					j = 0;
					do{
						j += sprintf(mac_str+j,"%s%02X",(i == ifi->ifi_hlen) ? " " : "-", *ptr++);
					}while(--i>0);
					mac = mac_str;
				}
				ret = 0;
				break;
			}
		}
	}

	free_ifi_info(ifihead);
	return ret;
}

#endif

int KSGNetUtil::ftp_upload_file(ftp_upload_conf_t *conf)
{
	CURL *curl;
	CURLcode res = CURL_LAST;
	char user_pwd[128] = "";
	int time_out;
	//struct stat file_info;
	//int fd;
	FILE *fp;
	time_out = (conf->time_out > 0 && conf->time_out < 30) ? conf->time_out : 3;
	/*
	fd = open(conf->from_file,O_RDONLY);
	if(fd == -1)
		return -1;

	fstat(fd,&file_info);

	fp = fdopen(fd,"rb");
	*/
	fp = fopen(conf->from_file,"rb");
	if(!fp)
	{
		return -1;
	}

	if(conf->user_name && conf->user_pwd)
	{
		sprintf(user_pwd,"%s:%s",conf->user_name,conf->user_pwd);
	}
	curl = curl_easy_init();
	if(curl)
	{
		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, TRUE) ;

		/* specify target */
		curl_easy_setopt(curl,CURLOPT_URL, conf->ftp_url);

		/* now specify which file to upload */
		curl_easy_setopt(curl, CURLOPT_READDATA, fp);
#ifdef WIN32
		curl_easy_setopt(curl ,CURLOPT_READFUNCTION, fread);
#endif 
		//curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
		//	(curl_off_t)file_info.st_size);
#ifdef _DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);
#endif
		curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, CURLFTPMETHOD_NOCWD);
		curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 0);
		// 设置登陆用户名与密码
		if(strlen(user_pwd) > 0)
			curl_easy_setopt(curl ,CURLOPT_USERPWD,user_pwd);
		// 设置连接超时时间为 3 秒
		curl_easy_setopt(curl, CURLOPT_TIMEOUT,time_out);
		// 设置 FTP 超时时间为 3 秒
		curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT,time_out);

		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

	}
	fclose(fp);
	return (res == CURLE_OK) ? 0 : -1;
}

int KSGNetUtil::send_buffer(ACE_HANDLE handle,unsigned char *buf,size_t buflen,ACE_Time_Value *timeout)
{
	ssize_t ret;
	if(ACE_INVALID_HANDLE == handle)
		return -1;
	ACE_SOCK_Stream stream(handle);
	size_t transfered = 0;

	ACE_Time_Value tv = *timeout;
	ret = ACE::handle_write_ready(handle,&tv);
	if(ret == 0)
		return TASK_ERR_TIMEOUT;
	else if(ret<0)
	{
		return TASK_INVALID_CONN;
	}
	ssize_t l = 0;
	do 
	{
		tv = *timeout;
		ret = stream.send_n(buf+l,buflen-l,&tv,&transfered);
		if(ret<0)
		{
			// socket error
			return TASK_INVALID_CONN;
		}
		if(transfered >= 0)
		{
			l += transfered;
			if(l >= buflen)
				return 0;
			// continue send
		}
		else
		{
			return TASK_ERR_SOCK_SEND_RECV;
		}
	} while (l <= buflen);
	return TASK_ERR_SOCK_SEND_RECV;
}
ssize_t KSGNetUtil::recv_buffer(ACE_HANDLE handle,unsigned char *buf,size_t maxbuf,ACE_Time_Value *timeout)
{
	ssize_t ret;
	ACE_SOCK_Stream stream(handle);
	// USE recv_n 收取数据
	size_t transfered =	0;
	ACE_Time_Value tv(0);
	ret = ACE::handle_read_ready(handle,timeout);
	if(ret==0)
		return TASK_ERR_TIMEOUT;
	else if(ret == -1)
		return TASK_INVALID_CONN;
	ssize_t l = 0;
	do 
	{
		ret = stream.recv_n(buf+l,maxbuf-l,&tv,&transfered);
		if(ret<0)
		{
			return TASK_INVALID_CONN;
		}
		if(transfered >= 0)
		{
			l += transfered;
			if(l >= maxbuf)
				return l;
		}
		else
		{
			if(l > 0)
				return l;
			return -2;
		}
	} while (l < maxbuf);

}
