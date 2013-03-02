#ifndef _CUTILCONFIG_H_
#define _CUTILCONFIG_H_

#ifdef WIN32
#include <tchar.h>
#else
#endif

//////////////////////////////////////////////////////////////////////////
// type
#ifdef WIN32
#pragma warning( disable : 4786)
typedef __int64 int64_t;
#define LIKELY(exp) (!!(exp))
#define UNLIKELY(exp) (!!(exp))
#else
typedef long long int64_t;
#endif

#endif // _CUTILCONFIG_H_
