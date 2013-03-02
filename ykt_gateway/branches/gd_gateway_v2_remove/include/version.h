#ifndef _KSG_VERSION_H_
#define _KSG_VERSION_H_

#include <ace/Version.h>
#include <boost/version.hpp>
#include <curl/curlver.h>

#define KSG_STRINGIFY(n) KSG_STRINGIFY_HELPER(n)
#define KSG_STRINGIFY_HELPER(n) #n
#define KSG_NUM_HELPER(n) n

#define KSG_GW_MAJOR_VER 1
#define KSG_GW_MINOR_VER 5
#define KSG_GW_BUILT_NUM "008"

#define KSG_VESION_NUMER KSG_STRINGIFY(KSG_GW_MAJOR_VER) "." \
	KSG_STRINGIFY(KSG_GW_MINOR_VER) "." \
	KSG_GW_BUILT_NUM


#define _KSG_RELEASE_VERION "-gdv2-rc1"
#ifdef _DEBUG
#define KSG_RELEASE_VER _KSG_RELEASE_VERION " debug"
#else
#define KSG_RELEASE_VER _KSG_RELEASE_VERION " release"
#endif
#define KSG_FULL_VERSION KSG_VESION_NUMER KSG_RELEASE_VER  " " __DATE__ " " __TIME__

#define KSG_ACE_VERSION ACE_VERSION

#define KSG_BOOST_VERSION BOOST_LIB_VERSION

#define KSG_CURL_VERSION LIBCURL_VERSION

#ifdef _MSC_VER
#define KSG_BUILD_INFO "built msc - " KSG_STRINGIFY(_MSC_VER)
#elif defined _GCC_VER
#define KSG_BUILD_INFO "built " _GCC_VER
#else
#define KSG_BUILD_INFO "built unknown"
#endif

#define KSG_COPYRIGHT_STRING "Copyright 2005-2007 SunGard Kingstar All Rights Reserved"

#endif // _KSG_VERSION_H_
