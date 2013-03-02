// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2D4F7577_3771_4379_87B2_6B3C294D0D92__INCLUDED_)
#define AFX_STDAFX_H__2D4F7577_3771_4379_87B2_6B3C294D0D92__INCLUDED_

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

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>
#include <afxsock.h>
#include <math.h>
#include <Mmsystem.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <nb30.h>

#pragma comment(lib, "NETAPI32.LIB")
#pragma comment(lib, "pdh.lib")

#pragma comment(lib, "Winmm.lib")
#define __DEBUG_INTERFACE__		1
//#include <afxsock.h>		// MFC socket extensions
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//#define __DEBUG_DATA__ 1 
#endif // !defined(AFX_STDAFX_H__2D4F7577_3771_4379_87B2_6B3C294D0D92__INCLUDED_)
