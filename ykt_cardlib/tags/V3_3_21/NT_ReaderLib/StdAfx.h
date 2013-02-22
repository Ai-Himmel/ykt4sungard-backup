// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D40F33BB_56C9_4068_A6CE_71A8B4B30580__INCLUDED_)
#define AFX_STDAFX_H__D40F33BB_56C9_4068_A6CE_71A8B4B30580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <vector>
#include "dcrf32.h"
#include "public.h"
using namespace std;

//1为羊城通读写器  0为金仕达读写器
#define		YCT_READER		1
//1为通过PSAM卡进行修改     0为装载密钥后软件仿真PSAM
#define		YCT_PASM		1
extern HANDLE			g_nHandle;

#endif // !defined(AFX_STDAFX_H__D40F33BB_56C9_4068_A6CE_71A8B4B30580__INCLUDED_)

