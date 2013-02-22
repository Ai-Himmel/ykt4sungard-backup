
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DESDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DESDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the desdll.dll
//使用预编译指令保证头文件只能被包含一次
#ifndef __DESDLL_H__
#define __DESDLL_H__

#if _MSC_VER > 1000
# pragma once
#endif
//用预编译指令使C函数能被C++程序直接调用
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CALLAPI
# define CALLAPI __declspec(dllimport)
#endif

int	__stdcall encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
int	__stdcall dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
int	__stdcall encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
int	__stdcall dencrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result);
int	__stdcall gen_work_key(unsigned char* buf1,unsigned char* buf2,unsigned char*buf3,unsigned char* key);
int	__stdcall encrypt_work_key(unsigned char* text,unsigned char* mtext);
int	__stdcall decrypt_work_key(unsigned char* text,unsigned char* mtext);
int	__stdcall get_check_char(unsigned char buf[16]);
int	__stdcall check_valid(unsigned char buf[16],unsigned char check_char);
int	__stdcall gen_user_card_keyA(unsigned char *key,unsigned char *text,unsigned char *keyA);
int	__stdcall gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB);
int	__stdcall gen_auth_card_keyA(unsigned char *text,unsigned char *keyA);
int	__stdcall gen_auth_card_keyB(unsigned char *text,unsigned char *keyB);
int __stdcall gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA);
int __stdcall gen_auth_card_ks(unsigned char *src_key, unsigned char *text, unsigned char *des_key);
void __stdcall cal_des(unsigned char *key, unsigned char *text, unsigned char *mtext);
void __stdcall cal_dedes(unsigned char *key, unsigned char *text, unsigned char *mtext);

#ifdef __cplusplus
}
#endif

#endif
