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
#include "PersonInfoApi.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// ������̬���ص�������̬��		
#define _DYNAMIC_LOAD
#endif

#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif

#endif