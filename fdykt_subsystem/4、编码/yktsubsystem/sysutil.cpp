/** 
 * 模块名					外接子系统
 * 文件名					sysutil.cpp
 * 文件实现功能				系统功能函数
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-07-21
 * 备注
 * $Id: sysutil.cpp 21 2005-08-29 09:22:34Z cheng.tang $
 */

#include "StdAfx.h"
#include <NB30.H>
#include <assert.h>
#include "mac.h"
#include "md5.h"
#include "sysutil.h"
#include <IPHlpApi.h>

//#pragma comment(lib,"Netapi32.lib")

using namespace std;

bool ksf_file_exists(const char * file_path)
{
	bool bExist = false;
	HANDLE hFile;
	
	if (NULL != file_path)
	{
		// Use the preferred Win32 API call and not the older OpenFile.
		hFile = CreateFile(file_path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, 0);
		
		if (hFile != INVALID_HANDLE_VALUE)
		{
			// If the handle is valid then the file exists.
			CloseHandle(hFile);
			bExist = true;
		}
	}
	
	return (bExist);
}

int ksf_get_computer_mac(std::string & mac)
{
	LANA_ENUM lenum;
	NCB ncb = {0};
	char szMac[18] = "";
	// 取网卡数
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (UCHAR *)&lenum;
	ncb.ncb_length = sizeof(lenum);
	UCHAR ucRetCode = Netbios(&ncb);
	
	ADAPTER_STATUS adapter = {0};
	for (int i = 0; i < lenum.length; i ++)
	{
		// Bios 复位
		memset(&ncb, 0, sizeof(ncb));
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lenum.lana[i];
		ucRetCode = Netbios(&ncb);
		
		// 取某一块网卡的地址
		memset(&ncb, 0, sizeof(ncb));
		ncb.ncb_command = NCBASTAT;
		ncb.ncb_lana_num = lenum.lana[i];
		strcpy((char *)ncb.ncb_callname, "*               ");
		ncb.ncb_buffer = (BYTE *)&adapter;
		ncb.ncb_length = sizeof(adapter);
		ucRetCode = Netbios(&ncb);
		if (ucRetCode == 0)
		{
			if (adapter.adapter_address[0] + 
				adapter.adapter_address[1] +
				adapter.adapter_address[2] +
				adapter.adapter_address[3] +
				adapter.adapter_address[4] +
				adapter.adapter_address[5] != 0)
			{
				int k = 0;
				for (int j = 0;j < 6;++j) 
				{
					k += sprintf(szMac+k,"%02X",adapter.adapter_address[j]);
				}
				mac = szMac;
				return 0;
			}
		}
	}
    return -1;
}

int ksf_get_mac_by_ip(const string &ip,string &mac)
{
	char mac_str[19] = "";
	int nRemoteAddr = inet_addr( ip.c_str() );
	hostent host;
	hostent * remoteHostent= &host;
	struct in_addr sa;
	memset(&host,0,sizeof(host));
	//获取远程机器名
	sa.s_addr = nRemoteAddr;
	//printf( "\nIpAddress : %s\n", inet_ntoa( sa ) );
	remoteHostent = gethostbyaddr( (char*)&nRemoteAddr,4, AF_INET );
	if ( NULL == remoteHostent )
		return -1;
	//发送ARP查询包获得远程MAC地址

	unsigned char macAddress[6];
	ULONG macAddLen = 6;
	DWORD iRet=SendARP(nRemoteAddr, (unsigned long)NULL,(PULONG)&macAddress, &macAddLen);
	if ( NO_ERROR == iRet )
	{
		for( int i =0; i<6; i++ )
		{
			sprintf(mac_str+i*2,"%.2X", macAddress[i] );
		}
		mac = mac_str;
	}
	else
		return -1;
	return 0;
}

int ksf_get_computer_ip(std::string computer,std::string &ip)
{
	return -1;
}
void ksf_get_local_ip(std::vector<string>&ip_list)
{
	char HostName[80];
	int i;
    LPHOSTENT lpHostEnt;
    struct in_addr addr[5];
    //本程序假设主机不是多宿主机，即最多只有
    // 一块网卡和一个动态IP
    for (i=0; i<2; i++)
		memset(&addr[i],0,sizeof(in_addr));
    //对in_addr结构清0，以利后面填写
    // 得到本主机名
    if(gethostname(HostName,sizeof(HostName))==SOCKET_ERROR)
	{
		AfxMessageBox("Can't getting local host name.");
		return ;
	}
    lpHostEnt=gethostbyname(HostName);//利用得到的主机名去获得主机结构
    if (!lpHostEnt)
    {
		AfxMessageBox("Yow!  Bad host lookup.");
		return ;
    }
	
    for (i=0; lpHostEnt->h_addr_list[i]!=0; i++)
		//从主机地址表中得到IP地址
	{
		memcpy(&addr[i],lpHostEnt->h_addr_list[i],sizeof(in_addr));
		ip_list.push_back(string(inet_ntoa(addr[i])));
	}
}

void ksf_padding_str(unsigned char * buf,int len,
					 char pad_char,int sect_len)
{
	int pad_len = 0;
	if( len % sect_len != 0)
		pad_len = sect_len - (len % sect_len);
	
	for (int i = 0;i < pad_len;++i) 
	{
		buf[len + i] = pad_char;
	}
}
void ksf_xor_key_8len(unsigned char * buf,int len,unsigned char output[8])
{
	int i = 0;
	if(len > 8)
	{
		memcpy(output,buf,8);
		for (i = 8; i < len;++i)
		{
			output[i%8] ^= buf[i];
		}
	}
	else
	{
		memset(output,0,8);
		memcpy(output,buf,len);
	}
}
int ksf_gen_key(ksf_server_conf * svr_conf,unsigned char * static_key,
				unsigned char * mkey)
{
	unsigned char key[8] = "";
	unsigned char text[IP_LEN + MAC_LEN + 8] = "";
	unsigned char mtext[IP_LEN + MAC_LEN + 8] = "";
	unsigned char tmp[IP_LEN + MAC_LEN + 8]= "";
	// 将 IP 与 MAC 组合成一个字符串
	memcpy(text,svr_conf->ip,strlen(svr_conf->ip));
	memcpy(text+strlen(svr_conf->ip),svr_conf->mac,strlen(svr_conf->mac));
	int len = strlen(svr_conf->ip) + strlen(svr_conf->ip);
	memcpy(key,static_key,sizeof(key));
	// 补为 8 位
	ksf_padding_str(text,len);
	// 使用 DES 加密
	DES(key,text,mtext);
	_DES(key,mtext,tmp);
	// XOR 计算出 8 位密钥
	ksf_xor_key_8len(mtext,len,mkey);
	return 0;
}

int ksf_encrypt_buf(char * buf,int len,
					unsigned char * mkey,unsigned char * mtext)
{
	char * tmpbuf;
	int tmp_len = (8 - len % 8) + len;
	tmpbuf = (char *)malloc(tmp_len);
	memcpy(tmpbuf,buf,len);
	DES(mkey,(unsigned char*)tmpbuf,mtext);
	free(tmpbuf);
	return 0;
}

int ksf_decrypt_buf(char * buf,int len, 
					unsigned char * mkey,unsigned char * text)
{
	_DES((unsigned char *)buf,text,mkey);
	return 0;
}

//{{{ MD5Helper() method
/**
* 计算MD5值的方法
* @param value - 被计算的字符串
* @param result - MD5摘要值
* @param len - 长度
*/
void ksf_md5_helper(unsigned char * value ,
					unsigned char result[16],unsigned int len)
{
    assert(value != NULL);
    assert(result != NULL);
    MD5_CTX md5ctx;
    MD5Init(&md5ctx);
    MD5Update(&md5ctx,value,len);
    MD5Final(result,&md5ctx);
	//memcpy(result,&md5ctx,16);
}
//}}}

void ksf_init_notify_sh(NOTIFYICONDATA * lpNotify,const char * tip_msg,
						UINT callback_msg,HICON hIcon,HWND hHandle)
{
    memset(lpNotify,0,sizeof(NOTIFYICONDATA));
	
    lpNotify->cbSize = sizeof(NOTIFYICONDATA);
    lpNotify->hWnd = hHandle;
    lpNotify->hIcon = hIcon;
    lpNotify->uID = 0;
    //lpNotify->DUMMYUNIONNAME.uVersion = NOTIFYICON_VERSION;
    lpNotify->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    lpNotify->uCallbackMessage = callback_msg;
    strcpy(lpNotify->szTip,tip_msg);
    Shell_NotifyIcon(NIM_ADD, lpNotify);
}

void ksf_update_notify_tip(NOTIFYICONDATA * lpNotify,
						   const char * title,const char * msg)
{
	lpNotify->cbSize = sizeof(NOTIFYICONDATA);
	lpNotify->uFlags = NIF_TIP;
	//lpNotify->uTimeout = 500;
	//lpNotify->dwInfoFlags = NIIF_INFO;
	//strcpy(lpNotify->szInfoTitle,title);
	//strcpy(lpNotify->szInfo,msg);
	Shell_NotifyIcon(NIM_MODIFY, lpNotify);
}

void ksf_delete_notify(NOTIFYICONDATA * lpNotify)
{
	Shell_NotifyIcon(NIM_DELETE,lpNotify);
}
