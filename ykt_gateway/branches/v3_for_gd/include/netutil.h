#ifndef _NETUTIL_H_
#define _NETUTIL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <list>
#include <ace/ACE.h>

typedef struct {
	const char *ftp_url;
	const char *user_name;
	const char *user_pwd;
	const char *from_file;
	int time_out;
}ftp_upload_conf_t;

class KSGNetUtil
{
public:
	//! 根据指定的IP，获取MAC地址
	/*!
	 \param ip IP地址
	 \param mac [out] MAC地址
	 \return 成功返回0, 失败返回 -1
	 */
	static int GetMacByIP(const std::string ip,std::string &mac);
	//! 获取本机的所有IP地址
	/*!
	 \param ip_list [out] IP地址列表
	 */
	static void GetLocalIP(std::list<std::string>&ip_list);

	static int ftp_upload_file(ftp_upload_conf_t *conf);
	//!
	/*!
	 \param handle
	 \param buf - 发送的数据包 
	 \param len - 发送数据包长度
	 \param timeout - NULL 表示一直等待
	 \return 0表示成功，否则返回错误码
	 */
	static int send_buffer(ACE_HANDLE handle,unsigned char *buf,size_t buflen,ACE_Time_Value *timeout);
	static ssize_t recv_buffer(ACE_HANDLE handle,unsigned char *buf,size_t maxlen,ACE_Time_Value *timeout);
};
#endif // _NETUTIL_H_

