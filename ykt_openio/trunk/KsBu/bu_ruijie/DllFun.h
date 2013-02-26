/********************************************************
* �ļ�����: ʵ����������Խ�ʱ����ж�̬���ض�̬��
* �ļ���:	DllFun.h
* ˵��:		��̬�������ݽṹ�ڴ�,��̬�����ɵ���������.h�ļ�
* ����:		����
* ʱ��:		2007-07-02
* �޸�ԭ��: 
**********************************************************/

#ifndef _DLL_FUN_H_
#define _DLL_FUN_H_
#pragma once

#include "DllFunErrCode.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// ������̬���ص�������̬��		
#define _DYNAMIC_LOAD
#endif

#ifndef SYNJONES_FUNC		// �������������º���		
#define SYNJONES_FUNC
#endif

#ifdef __cplusplus
extern "C" {
#endif

//RG FLAG
#define RG_END_MARK			";"
#define RG_SPLIT1			","
#define RG_SPLIT2			"\""
#define RG_SPLIT3			":"

#define RG_FLAG_LEN			3
#define RG_SUCC				"SUC"
#define RG_ERR				"ERR"
#define RG_ACK				"ACK"
#define RG_QUERYUSER_FLAG	"QUERYUSER:"
#define RG_PAY_FLAG			"PAY:"
#define RG_USER_ID			"USERID="
#define RG_FEE				"FEE="
#define RG_USER_IP			"USERIP="
#define RG_USER_NAME		"USERNAME="

/************************************************************************/
/* ȫ�ֲ���                            
/************************************************************************/
typedef struct _ini_pack_para
{
	int flash_dealy;
	int dynamic_load_flag;
	int sysjones_func;
	char third_part_dll_name[50];
	char user_id[33];
	char pwd[20];
	int port;
	char ip[20];
	char des_dll_name[50];
	int des_flag;
	char encrypt_pwd[20];
	int debug_log;
}ini_pack_para;

extern ini_pack_para g_ini_para;

/************************************************************************/
/* ���ض�̬��궨��                                                                     
/************************************************************************/
#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
	{ \
		::FreeLibrary(handle); \
		handle = NULL; \
		return DLLFUN_ERR_NO_FUNADDRESS; \
	}

/************************************************************************/
/* ���ض�̬�⺯��, �Խӵ�������Ϣ����
/************************************************************************/
// ��������շ�
DCLR_DLLFUNC(char *,fCommandTS,(char *managerId, char *managerPass, char *ip, int port, char *cmdString));
DCLR_DLLFUNC(char *,fInit,());


int GetRGRetData(char *result, char *key_name, char *value_name);

#ifdef __cplusplus
}
#endif

#endif