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

//���������������߳�
#define		SAVEBLACKLISTTOTAL	1000000				//���������������(1����)
extern CInterface				g_CInterface;			//�������ӿ�
extern SMARTINIFILEPARA			g_IniFilePara;			//�����ļ��еĲ���
extern list<CSocketSmart>		g_LTcpsmart;
extern list<SMARTTASKRESULT>	g_LSaveTaskResult;		 //��������ִ�еĽ��
extern vector<SMARTPOS>			g_VSmartPos;			//�����豸
extern vector<SMARTPOS>			g_VLinkIP;				//������·��IP��ַ
extern int						g_StartFlag;
extern bool						g_bStartFlag;
extern char						g_sWorkKey[33];			//������Կ
extern int						g_nWalletNo;			//Ǯ����
extern char						g_PathIniFileName[256];	//�����ļ�
extern CCriticalSection			g_CriticalSectionLock;	//ȫ����;
extern byte						g_SaveBlackList[SAVEBLACKLISTTOTAL/8];	//��λͼ�ķ�ʽ����100�������� bitΪ1ʱΪ�ڿ���0ʱΪ�׿�
extern byte						g_SaveAssistantList[SAVEBLACKLISTTOTAL/8];	//��λͼ�ķ�ʽ����100�������� bitΪ1ʱΪ����������0ʱΪ��Ч
extern int						g_nSaveAssistantVer;						//���������汾
extern CSmartBlackMemoryOper    g_CSmartBlackMemoryOper;//�������ڴ����
extern DWORD					g_nTotalCount;			//���豸����
extern long						g_nMsgID;				//�����ڲ���ϢID��
extern char						g_sCommRec[256];		//��ĩ��ˮ���ļ�
extern bool						g_WriteFileLock;		//�ļ���
#define   SMT_SERVERNAME		"�ǻ۵���ǰ��ͨѶϵͳ"
#define   SMT_WAITFORTIME1		g_IniFilePara.lSleepTime1
#define   SMT_WAITFORTIME2		g_IniFilePara.lSleepTime2
#define   SMT_WAITFORTIME3		g_IniFilePara.lSleepTime3
void Smart_UserDes(unsigned char* InputData,unsigned char* OutputData,char CodeFlag);
#endif