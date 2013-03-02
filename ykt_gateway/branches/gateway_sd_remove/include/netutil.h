#ifndef _NETUTIL_H_
#define _NETUTIL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <list>
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
};
#endif // _NETUTIL_H_

