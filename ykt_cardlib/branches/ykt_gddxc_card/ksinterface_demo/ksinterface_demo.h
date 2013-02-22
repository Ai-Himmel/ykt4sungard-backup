// ksinterface_demo.h : PROJECT_NAME 应用程序的主头文件
//
#ifndef _KSINTERFACE_DEAMO_H_
#define _KSINTERFACE_DEAMO_H_

#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号
#include "..\ksinterface\Pubdef.h"

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
	return -1; } while(0)

// Cksinterface_demoApp:
// 有关此类的实现，请参阅 ksinterface_demo.cpp
//

class Cksinterface_demoApp : public CWinApp
{
private:
	int load_dll();
	HMODULE m_interface_;
public:
	Cksinterface_demoApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Cksinterface_demoApp theApp;


DCLR_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_DLLFUNC(int,CloseMF,());
DCLR_DLLFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_DLLFUNC(int,Load_Dll,());
DCLR_DLLFUNC(int,ReadBalance,(int nPacketNo,int *nBalance,int *nCnt));
DCLR_DLLFUNC(int,QueryBalance,(const int nPort,PPURCHSEARCH pPurSearch));
DCLR_DLLFUNC(int,CashIncrease,(const int nPort, const DWORD dwValue, PPURCHASEINCREASE pIncrease, BOOL bMustCmp));

#endif // _KSINTERFACE_DEAMO_H_

