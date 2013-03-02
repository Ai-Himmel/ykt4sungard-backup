#ifndef _CSTRING_H_
#define _CSTRING_H_

#include <string>
#include <sstream>
#include "cutilconfig.h"

namespace cutil
{
	
	//! string 类定义
	typedef std::basic_string<TCHAR> myString;
	//! stringbuf 类定义
	typedef std::basic_stringstream<TCHAR> myStringbuf;
	//! unicode 到 char 的转换
	class Convert
	{
	public:
		static wchar_t * ansiToUnicode(wchar_t * dst, const char * src)
		{
			::mbstowcs(dst, src, 512);
			return dst;
		}

		static char * unicodeToAnsi(char * dst, const wchar_t * src)
		{
			::wcstombs(dst, src, 512);
			return dst;
		}

		static void int64ToString(wchar_t * dst, size_t maxlen, const int64_t& ll)
		{
#ifdef WIN32
			_snwprintf(dst, maxlen, L"%I64d", ll);
#else
			swprintf(dst, maxlen, L"%lld", ll);
#endif
		}

		static void int64ToString(char * dst, size_t maxlen, const int64_t& ll)
		{
#ifdef WIN32
			_snprintf(dst, maxlen, "%I64d", ll);
#else
			snprintf(dst, maxlen, "%lld", ll);
#endif
		}
	};
	template<class FromChar,class ToChar>
	class UnicodeConvert;

	template<> class UnicodeConvert<char,wchar_t>
	{
	public:
		static std::wstring Convert(const char * from)
		{
			int len = strlen(from);
			wchar_t * buf = new wchar_t[len];
			int retlen = ::mbstowcs(buf,from,len);
			if(retlen < 0)
			{
				delete [] buf;
				return std::wstring(L"");
			}
			delete [] buf;
			return std::wstring(buf,retlen);
		}
		static std::wstring Convert(const std::string& from)
		{
			return Convert(from.c_str());
		}
	};
	template<> class UnicodeConvert<wchar_t,char>
	{
	public:
		static std::string Convert(const wchar_t * from)
		{
			int len = wcslen(from);
			char * buf = new char[len* 2];
			int retlen = ::wcstombs(buf,from,len);
			if(retlen < 0)
			{
				delete[] buf;
				return std::string("");
			}
			delete[] buf;
			return std::string(buf,retlen);
		}
		static std::string Convert(const std::wstring& from)
		{
			return Convert(from.c_str());
		}
	};

	template<> class UnicodeConvert<char,char>
	{
	public:
		static std::string Convert(const char* from)
		{
			return std::string(from);
		}
		static const std::string& Convert(const std::string& from)
		{
			return from;
		}
	};
	template<> class UnicodeConvert<wchar_t,wchar_t>
	{
	public:
		static std::wstring Convert(const wchar_t* from)
		{
			return std::wstring(from);
		}
		static const std::wstring& Convert(const std::wstring& from)
		{
			return from;
		}
	};

#ifdef MUST_UNDEF_T
#undef _T
#endif

#define CONVERSION_BUF_LEN 1024

#ifdef WIN32
#ifndef USES_CONVERSION
#include <malloc.h>
#define USES_CONVERSION void * _dst = _alloca(CONVERSION_BUF_LEN);
#endif
#else
#include <alloca.h>
#define USES_CONVERSION void * _dst = alloca(CONVERSION_BUF_LEN);
#endif

#ifndef W2A
#define W2A(src) Convert::unicodeToAnsi((char *)_dst, src)
#endif

#ifndef WS2AS
#define WS2AS(src) UnicodeConvert<wchar_t,char>::Convert(src)
#endif

#ifndef A2W
#define A2W(src) Convert::ansiToUnicode((wchar_t *)_dst, src)
#endif

#ifndef AS2WS
#define AS2WS(src) UnicodeConvert<char,wchar_t>::Convert(src)
#endif

#ifndef TS2AS
#define TS2AS(src) UnicodeConvert<myString::value_type,char>::Convert(src)
#endif

#ifndef TS2WS
#define TS2WS(src) UnicodeConvert<myString::value_type,wchar_t>::Convert(src)
#endif

#ifndef AS2TS
#define AS2TS(src) UnicodeConvert<char,myString::value_type>::Convert(src)
#endif

#ifndef WS2TS
#define WS2TS(src) UnicodeConvert<wchar_t,myString::value_type>::Convert(src)
#endif

#ifdef UNICODE
#include <wctype.h>

#ifndef _T
#define _T(x) L ## x
#endif

#ifndef TCHAR
	typedef wchar_t TCHAR;
#endif
#define totupper towupper
#define totlower towlower
#define tcout std::wcout
#define tcerr std::wcerr
#ifdef WIN32
#define tstrncasecmp _wcsnicmp
#else
#define tstrncasecmp wcsncasecmp
#endif // WIN32

#ifndef T2A
#define T2A(src) W2A(src)
#endif

#ifndef T2W
#define T2W(src) src
#endif

#ifndef A2T
#define A2T(src) A2W(src)
#endif

#ifndef W2T
#define W2T(src) src
#endif

#define ttol(s) wcstol(s, 0, 10)
#define itot _itow
#define tcscmp wcscmp
#else // Not UNICODE
#include <ctype.h>

#ifndef _T
#define _T(x) x
#endif

	typedef char TCHAR;
#define totupper toupper
#define totlower tolower
#define tcout std::cout
#define tcerr std::cerr
#ifdef WIN32
#define tstrncasecmp _strnicmp
#else
#define tstrncasecmp strncasecmp
#endif // WIN32

#ifndef T2A
#define T2A(src) src
#endif

#ifndef T2W
#define T2W(src) A2W(src)
#endif

#ifndef A2T
#define A2T(src) src
#endif

#ifndef W2T
#define W2T(src) W2A(src)
#endif

#define ttol atol
#define itot itoa
#define tcscmp strcmp
#endif // UNICODE
}
#endif // _CSTRING_H_
