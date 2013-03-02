// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3D706050_C656_4A5D_AA7F_614E9F885F5C__INCLUDED_)
#define AFX_STDAFX_H__3D706050_C656_4A5D_AA7F_614E9F885F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define	  WM_USER_TRAY_NOTIFICATION (WM_USER+0x102)
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <winsock2.h>
#include <iostream>
#include <list>
#include <vector>
#include <afxmt.h> 
#include <pdh.h>
#include <nb30.h>
#include "SmartCommunication.h"
#include "SmartBlackListMemoryOper.h"
#include "public.h"
#include "Smart.h"
#include "SmartCom.h"
#include "SmartSocket.h"
#include "systeminfo.h"
#include "readfile.h"
#include "interface.h"

#include "../export/include/bccclt.h"
#pragma comment(lib, "../export/lib/bccclt.lib")
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "NETAPI32.LIB")
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "Winmm.lib")

#ifndef FAIL
#define	  FAIL  -1
#endif

#ifndef SUCCESS
#define   SUCCESS 0
#endif

//用来保存启动的线程
#define		SAVEBLACKLISTTOTAL	1000000				//保存黑名单的总数(1百万)
extern CInterface				g_CInterface;			//第三方接口
extern SMARTINIFILEPARA			g_IniFilePara;			//配置文件中的参数
extern list<CSocketSmart>		g_LTcpsmart;
extern list<SMARTTASKRESULT>	g_LSaveTaskResult;		 //保存任务执行的结果
extern vector<SMARTPOS>			g_VSmartPos;			//所有设备
extern vector<SMARTPOS>			g_VLinkIP;				//所有链路的IP地址
extern int						g_StartFlag;
extern bool						g_bStartFlag;
extern char						g_sWorkKey[33];			//工作密钥
extern int						g_nWalletNo;			//钱包号
extern char						g_PathIniFileName[256];	//配置文件
extern CCriticalSection			g_CriticalSectionLock;	//全局锁;
extern byte						g_SaveBlackList[SAVEBLACKLISTTOTAL/8];	//用位图的方式保存100万条名单 bit为1时为黑卡，0时为白卡
extern byte						g_SaveAssistantList[SAVEBLACKLISTTOTAL/8];	//用位图的方式保存100万条名单 bit为1时为补助名单，0时为无效
extern int						g_nSaveAssistantVer;						//补助名单版本
extern CSmartBlackMemoryOper    g_CSmartBlackMemoryOper;//黑名单内存操作
extern DWORD					g_nTotalCount;			//总设备数量
extern long						g_nMsgID;				//任务内部消息ID号
extern char						g_sCommRec[256];		//期末流水号文件
extern bool						g_WriteFileLock;		//文件锁
#define   SMT_SERVERNAME		"智慧电子前置通讯系统"
#define   SMT_WAITFORTIME1		g_IniFilePara.lSleepTime1
#define   SMT_WAITFORTIME2		g_IniFilePara.lSleepTime2
#define   SMT_WAITFORTIME3		g_IniFilePara.lSleepTime3
void Smart_UserDes(unsigned char* InputData,unsigned char* OutputData,char CodeFlag);
#endif