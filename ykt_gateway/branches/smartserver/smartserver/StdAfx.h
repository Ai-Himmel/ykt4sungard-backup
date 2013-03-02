// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h>
#include <process.h>
#include <tchar.h>
#include <winsock2.h>
#include <objbase.h>
#include <icrsint.h>
#include <crtdbg.h>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <pdh.h>
#define ASSERT _ASSERT

#include "resource.h"
#include "..\include\Common.h"
#include "SmartServer.h"
#include "TSmartDoc.h"
//#include <module.h>

#pragma warning(disable: 4146)

#pragma comment(lib, "ws2_32.lib")

#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
