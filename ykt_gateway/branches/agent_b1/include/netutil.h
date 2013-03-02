#ifndef _NETUTIL_H_
#define _NETUTIL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <list>

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
};
#endif // _NETUTIL_H_

