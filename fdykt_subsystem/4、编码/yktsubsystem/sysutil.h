#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_
/** 
 * ģ����					�����ϵͳ
 * �ļ���					sysutil.h
 * �ļ�ʵ�ֹ���				ϵͳ���ܺ���
 * ����						����
 * �汾						V0.1
 * ����						2005-07-21
 * ��ע
 * $Id: sysutil.h 21 2005-08-29 09:22:34Z cheng.tang $
 */
#include <string>
#include <vector>
#include <shellapi.h>
#include "../include/def.h"
#include "subsystem.h"

/** 
 * @brief �ж��ļ��Ƿ����
 * 
 * @param file_path - �ļ�����·��
 * 
 * @return - ���ڷ��� true, ���򷵻� false
 */
bool ksf_file_exists(const char * file_path);

/** 
 * @brief ȡ��ϵͳ����MAC��ַ
 * 
 * @param mac - [out]������MAC��ַ
 * 
 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
 */
int ksf_get_computer_mac(std::string & mac);
/**
 * @brief ͨ��IP��ַȡ��MAC��ַ
 * @param ip - [in] ָ��IP��ַ
 * @param mac - [out] ���MAC��ַ
 * @return - �ɹ�����0��ʧ�ܷ��� -1
 */
int ksf_get_mac_by_ip(const std::string &ip,std::string &mac);
/** 
 * @brief ȡ��ϵͳ��IP��ַ
 * 
 * @param ip - [out]ϵͳIP��ַ
 * 
 * @return - �ɹ�����0��ʧ�ܷ��� -1
 */
int ksf_get_computer_ip(std::string &ip);
/** 
 * @brief ȡ��ϵͳ���е�IP��ַ
 * 
 * @param std::vector<std::string>&ip_list [out] ϵͳIP��ַ�б�
 */
void ksf_get_local_ip(std::vector<std::string>&ip_list);
/** 
 * @brief ���ַ������� sect_len �ı����ĳ���
 * 
 * @param buf - �ַ���
 * @param len - �ַ����ĳ���
 * @param pad_char - ���ϵ��ַ�
 * @param sect_len - �εĳ���
 */
void ksf_padding_str(unsigned char * buf,int len,
                char pad_char='&',int sect_len=8);
/** 
 * @brief ͨ�� IP �� MAC �����һ�� 8 λ����Կ
 * 
 * @param svr_conf - �����������ԣ�����IP �� MAC
 * @param static_key - ��Կ
 * @param mkey - ���������Կ
 * 
 * @return - ���� 0 ��ʾ�ɹ���-1 ��ʾ���ɹ�
 */
int ksf_gen_key(ksf_server_conf * svr_conf,unsigned char * static_key
                ,unsigned char * mkey);

/** 
 * @brief ͨ��ָ������Կ�����ַ���
 * 
 * @param buf - Ҫ���ܵ��ַ���
 * @param len - ���ܵ��ַ����ĳ���
 * @param mkey - ����ʹ�õ���Կ
 * @param mtext - ���ܺ������
 * 
 * @return - ���� 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
int ksf_encrypt_buf(char * buf,int len,
                unsigned char * mkey,unsigned char * mtext);
/** 
 * @brief ͨ��ָ������Կ�����ַ���
 * 
 * @param buf - Ҫ���ܵ��ַ���
 * @param len - Ҫ���ܵ��ַ����ĳ���
 * @param mkey - ��Կ
 * @param text - ���ܺ���ַ���
 * 
 * @return - ���� 0 ��ʾ�ɹ������� -1 ��ʾʧ��
 */
int ksf_decrypt_buf(char * buf,int len,
                unsigned char * mkey,unsigned char * text);

//int ksf_des_str(char * buf,int len,unsigned char * )

/** 
 * @brief ����MD5
 * 
 * @param value - ��Ҫ����MD5������
 * @param result - �������MD5��16���ֽ�
 * @param len - �������ĳ���
 */
void ksf_md5_helper(unsigned char * value ,
					unsigned char result[16],unsigned int len);


/** 
 * @brief ��ʼ��״̬��ͼ��ṹ
 * 
 * @param lpNotify - NOTIFYICONDATA �ṹָ��
 * @param tip_msg -	��ʾ��Ϣ
 * @param callback_msg - ��Ϣ�ص�����
 * @param hIcon	- ͼ���� 
 * @param hHandle - �����ھ��
 */
void ksf_init_notify_sh(NOTIFYICONDATA * lpNotify,const char * tip_msg,
						UINT callback_msg,HICON hIcon,HWND hHandle);

/** 
 * @brief ����״̬��ͼ����Ϣ
 * 
 * @param lpNotify - NOTIFYICONDATA �ṹָ�룬ָ����Ҫ���µ�ͼ��
 * @param title - ͼ�����
 * @param msg - ��ʾ����
 */
void ksf_update_notify_tip(NOTIFYICONDATA * lpNotify,
						   const char * title,const char * msg);

/** 
 * @brief �ͷ�״̬��ͼ��
 * 
 * @param lpNotify - NOTIFYICONDATA �ṹָ��
 */
void ksf_delete_notify(NOTIFYICONDATA * lpNotify);
#endif // _SYSUTIL_H_
