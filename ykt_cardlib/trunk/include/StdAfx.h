// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#if !defined(AFX_STDAFX_H__D2F1FFF1_9C5D_4667_8F7D_42E3E3D8D862__INCLUDED_)
#define AFX_STDAFX_H__D2F1FFF1_9C5D_4667_8F7D_42E3E3D8D862__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifdef WIN32
#pragma warning( disable:4786) 
#endif

#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <queue>

#ifdef  UNIX
#endif
#ifdef AIX
#include <strings.h>
#endif
#ifdef HP_UX
#include <strings.h>
#endif

#ifdef WIN32
#include <io.h>
#include <winsock2.h>
#include <conio.h>
#else
#include <sys/socket.h>
//#include <sys/socketvar.h>
#include <netinet/in.h> /* sockaddr_in */
#include <sys/select.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#endif

using namespace std;

#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#end if 
// !defined(AFX_STDAFX_H__D2F1FFF1_9C5D_4667_8F7D_42E3E3D8D862__INCLUDED_)
