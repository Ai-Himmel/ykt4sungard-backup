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
#include "PersonInfoApi.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// 声明动态加载第三方动态库		
#define _DYNAMIC_LOAD
#endif

#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif

#endif