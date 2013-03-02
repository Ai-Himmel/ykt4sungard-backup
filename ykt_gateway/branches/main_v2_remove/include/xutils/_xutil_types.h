#ifndef _XUTIL_TYPES_H_
#define _XUTIL_TYPES_H_

namespace xutil {
//! namespace ∂®“Â
# ifdef XUTIL
# undef XUTIL
# define XUTIL xutil
# endif

# ifndef XUTIL_NAMESPACE_BEGIN
# define XUTIL_NAMESPACE_BEGIN	namespace xutil {
# endif 

# ifndef XUTIL_NAMESPACE_END
# define XUTIL_NAMESPACE_END  }
# endif

# ifdef WIN32

typedef __int64	int64;
//typedef unsigned short wchar_t;
	
#	ifndef XUTIL_API
#	define XUITL_API __declspec(dllexport)
#	endif

# else

typedef long long int64;

#	ifndef XUTIL_API
#	define XUITL_API
#	endif

# endif

}
#endif // _XUTIL_TYPES_H_
