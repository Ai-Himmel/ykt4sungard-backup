
#include "stdafx.h"
#include "mobileterm.h"
#include "importdef.h"
/** 
 * 模块名						39手持机动态库
 * 文件名						importdef.cpp
 * 文件实现功能					39手持机接口函数定义
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-10-17
 * 备注							
 * $Id$
 */

#define SMARTCOM411SCJ_DLL "SmartCom411SCJ.dll"

static HMODULE gs_SmartCom411SCJHandle = NULL;

DEF_SMCFUNC(IniCom);
DEF_SMCFUNC(CloseCom);
DEF_SMCFUNC(ReadId);
DEF_SMCFUNC(SetCommision);
DEF_SMCFUNC(WriteJh);
DEF_SMCFUNC(ReadDate);
DEF_SMCFUNC(UpRecordOne);
DEF_SMCFUNC(EndUpRecordOne);
DEF_SMCFUNC(UpHisBySerial);
DEF_SMCFUNC(ReadType);
DEF_SMCFUNC(SetWorkKey);
DEF_SMCFUNC(EmptyFlash);
DEF_SMCFUNC(WriteId);
DEF_SMCFUNC(UserUpParam);
DEF_SMCFUNC(DownDelBlack);
DEF_SMCFUNC(DownDelBAll);
DEF_SMCFUNC(DownBlackCard);
DEF_SMCFUNC(DownBlackVersion);
DEF_SMCFUNC(UpBlackVersion);
DEF_SMCFUNC(DownBlackExpire);
DEF_SMCFUNC(UpBlackExpire);

static int do_load_procs()
{
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,IniCom);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,CloseCom);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,ReadId);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,SetCommision);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,WriteJh);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,ReadDate);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,UpRecordOne);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,EndUpRecordOne);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,UpHisBySerial);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,ReadType);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,SetWorkKey);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,EmptyFlash);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,WriteId);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,UserUpParam);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,DownDelBlack);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,DownDelBAll);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,DownBlackCard);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,DownBlackVersion);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,UpBlackVersion);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,DownBlackExpire);
	LOAD_SMCFUNC(gs_SmartCom411SCJHandle,UpBlackExpire);
	return 0;
}
int LoadSmartCom411SCJ()
{
	if(gs_SmartCom411SCJHandle != NULL)
	{
		return 0;
	}
	gs_SmartCom411SCJHandle = LoadLibrary(SMARTCOM411SCJ_DLL);
	if(NULL == gs_SmartCom411SCJHandle)
	{
		return -1;
	}
	if(do_load_procs() == -1)
	{
		CloseSmartCom411SCJ();
		return -1;
	}
	return 0;
}

void CloseSmartCom411SCJ()
{
	if(gs_SmartCom411SCJHandle != NULL)
	{
		FreeLibrary(gs_SmartCom411SCJHandle);
		gs_SmartCom411SCJHandle = NULL;
	}
}
