// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
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

// TODO: 在此处引用程序要求的附加头文件
