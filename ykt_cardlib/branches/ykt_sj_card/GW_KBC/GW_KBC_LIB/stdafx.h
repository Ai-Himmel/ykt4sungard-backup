// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
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

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
