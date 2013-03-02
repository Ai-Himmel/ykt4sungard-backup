#ifndef _XUTIL_CONFIG_H_
#define _XUTIL_CONFIG_H_

# ifdef UNICODE
# define XUTIL_UNICODE
# else
#  ifdef XUTIL_UNICODE
#  undef XUTIL_UNICODE
#  endif
# endif
#endif // _XUTIL_CONFIG_H_

