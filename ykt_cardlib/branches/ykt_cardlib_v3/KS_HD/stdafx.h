// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

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
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
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

// TODO: reference additional headers your program requires here
