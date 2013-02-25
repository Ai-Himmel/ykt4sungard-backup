#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_
/** 
 * 模块名					外接子系统
 * 文件名					sysutil.h
 * 文件实现功能				系统功能函数
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-07-21
 * 备注
 * $Id: sysutil.h 21 2005-08-29 09:22:34Z cheng.tang $
 */
#include <string>
#include <vector>
#include <shellapi.h>
#include "../include/def.h"
#include "subsystem.h"

/** 
 * @brief 判断文件是否存在
 * 
 * @param file_path - 文件完整路径
 * 
 * @return - 存在返回 true, 否则返回 false
 */
bool ksf_file_exists(const char * file_path);

/** 
 * @brief 取得系统网卡MAC地址
 * 
 * @param mac - [out]网卡的MAC地址
 * 
 * @return - 成功返回 0 ，失败返回 -1
 */
int ksf_get_computer_mac(std::string & mac);
/**
 * @brief 通用IP地址取得MAC地址
 * @param ip - [in] 指定IP地址
 * @param mac - [out] 输出MAC地址
 * @return - 成功返回0，失败返回 -1
 */
int ksf_get_mac_by_ip(const std::string &ip,std::string &mac);
/** 
 * @brief 取得系统的IP地址
 * 
 * @param ip - [out]系统IP地址
 * 
 * @return - 成功返回0，失败返回 -1
 */
int ksf_get_computer_ip(std::string &ip);
/** 
 * @brief 取得系统所有的IP地址
 * 
 * @param std::vector<std::string>&ip_list [out] 系统IP地址列表
 */
void ksf_get_local_ip(std::vector<std::string>&ip_list);
/** 
 * @brief 将字符串补到 sect_len 的倍数的长度
 * 
 * @param buf - 字符串
 * @param len - 字符串的长度
 * @param pad_char - 补上的字符
 * @param sect_len - 段的长度
 */
void ksf_padding_str(unsigned char * buf,int len,
                char pad_char='&',int sect_len=8);
/** 
 * @brief 通过 IP 与 MAC 计算出一个 8 位的密钥
 * 
 * @param svr_conf - 服务器的属性，包括IP 与 MAC
 * @param static_key - 密钥
 * @param mkey - 计算出的密钥
 * 
 * @return - 返回 0 表示成功，-1 表示不成功
 */
int ksf_gen_key(ksf_server_conf * svr_conf,unsigned char * static_key
                ,unsigned char * mkey);

/** 
 * @brief 通过指定的密钥加密字符串
 * 
 * @param buf - 要加密的字符串
 * @param len - 加密的字符串的长度
 * @param mkey - 加密使用的密钥
 * @param mtext - 加密后的密文
 * 
 * @return - 返回 0 表示成功，-1 表示失败
 */
int ksf_encrypt_buf(char * buf,int len,
                unsigned char * mkey,unsigned char * mtext);
/** 
 * @brief 通过指定的密钥解密字符串
 * 
 * @param buf - 要解密的字符串
 * @param len - 要解密的字符串的长度
 * @param mkey - 密钥
 * @param text - 解密后的字符串
 * 
 * @return - 返回 0 表示成功，返回 -1 表示失败
 */
int ksf_decrypt_buf(char * buf,int len,
                unsigned char * mkey,unsigned char * text);

//int ksf_des_str(char * buf,int len,unsigned char * )

/** 
 * @brief 计算MD5
 * 
 * @param value - 需要计算MD5的数据
 * @param result - 计算出的MD5，16个字节
 * @param len - 数据区的长度
 */
void ksf_md5_helper(unsigned char * value ,
					unsigned char result[16],unsigned int len);


/** 
 * @brief 初始化状态栏图标结构
 * 
 * @param lpNotify - NOTIFYICONDATA 结构指针
 * @param tip_msg -	提示信息
 * @param callback_msg - 消息回调函数
 * @param hIcon	- 图标句柄 
 * @param hHandle - 主窗口句柄
 */
void ksf_init_notify_sh(NOTIFYICONDATA * lpNotify,const char * tip_msg,
						UINT callback_msg,HICON hIcon,HWND hHandle);

/** 
 * @brief 更新状态栏图标信息
 * 
 * @param lpNotify - NOTIFYICONDATA 结构指针，指向需要更新的图标
 * @param title - 图标标题
 * @param msg - 提示内容
 */
void ksf_update_notify_tip(NOTIFYICONDATA * lpNotify,
						   const char * title,const char * msg);

/** 
 * @brief 释放状态栏图标
 * 
 * @param lpNotify - NOTIFYICONDATA 结构指针
 */
void ksf_delete_notify(NOTIFYICONDATA * lpNotify);
#endif // _SYSUTIL_H_
