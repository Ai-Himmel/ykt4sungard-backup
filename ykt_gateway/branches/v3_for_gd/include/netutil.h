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
	//! ����ָ����IP����ȡMAC��ַ
	/*!
	 \param ip IP��ַ
	 \param mac [out] MAC��ַ
	 \return �ɹ�����0, ʧ�ܷ��� -1
	 */
	static int GetMacByIP(const std::string ip,std::string &mac);
	//! ��ȡ����������IP��ַ
	/*!
	 \param ip_list [out] IP��ַ�б�
	 */
	static void GetLocalIP(std::list<std::string>&ip_list);

	static int ftp_upload_file(ftp_upload_conf_t *conf);
	//!
	/*!
	 \param handle
	 \param buf - ���͵����ݰ� 
	 \param len - �������ݰ�����
	 \param timeout - NULL ��ʾһֱ�ȴ�
	 \return 0��ʾ�ɹ������򷵻ش�����
	 */
	static int send_buffer(ACE_HANDLE handle,unsigned char *buf,size_t buflen,ACE_Time_Value *timeout);
	static ssize_t recv_buffer(ACE_HANDLE handle,unsigned char *buf,size_t maxlen,ACE_Time_Value *timeout);
};
#endif // _NETUTIL_H_

