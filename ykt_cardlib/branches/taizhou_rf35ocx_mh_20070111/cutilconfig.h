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

namespace cutil
{
	//! Selector
	/*!
	 * \param T 第一个类型
	 * \param U 第二个类型
	 * \param bool 选择标志, 为 true 选择第一个类型,false 选择第二个类型
	 */
	template<bool,class T,class U>
	struct Selector
	{
		typedef T Result;
	};
	template<class T,class U>
	struct Selector<false,T,U>
	{
		typedef U Result;
	};
}
#endif // _CUTILCONFIG_H_
