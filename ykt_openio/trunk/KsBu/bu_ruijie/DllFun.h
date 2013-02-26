/********************************************************
* 文件内容: 实现与第三方对接时候进行动态加载动态库
* 文件名:	DllFun.h
* 说明:		动态加载数据结构在此,静态加载由第三方给出.h文件
* 创建:		李翔
* 时间:		2007-07-02
* 修改原因: 
**********************************************************/

#ifndef _DLL_FUN_H_
#define _DLL_FUN_H_
#pragma once

#include "DllFunErrCode.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// 声明动态加载第三方动态库		
#define _DYNAMIC_LOAD
#endif

#ifndef SYNJONES_FUNC		// 声明加载新中新函数		
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
/* 全局参数                            
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
/* 加载动态库宏定义                                                                     
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
/* 加载动态库函数, 对接第三方信息名单
/************************************************************************/
// 锐捷网络收费
DCLR_DLLFUNC(char *,fCommandTS,(char *managerId, char *managerPass, char *ip, int port, char *cmdString));
DCLR_DLLFUNC(char *,fInit,());


int GetRGRetData(char *result, char *key_name, char *value_name);

#ifdef __cplusplus
}
#endif

#endif