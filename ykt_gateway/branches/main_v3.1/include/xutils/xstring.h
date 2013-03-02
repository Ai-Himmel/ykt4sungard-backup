#ifndef XSTRING_H_
#define XSTRING_H_

#include "xutils/_xutil_config.h"
#include <string>

#ifdef WIN32
#include <tchar.h>
#else
#endif
XUTIL_NAMESPACE_BEGIN

#ifdef XUTIL_UNICODE

#else

#endif

//typedef std::basic_string<TCHAR> xString;

//! 字符串工具
class StringUtil 
{
public:
	template<class Iter>
	static int SpliteString(const std::string& str,const std::string& sep,Iter outiter)
	{
		size_t i ,j,k ;
		i = j = 0;
		while(i < str.length())
		{
			for(k = 0;k < sep.length();++k)
			{
				if(sep[k] != str[i+k])
					break;
			}
			if(k == sep.length())
			{
				// find
				*outiter++ = str.substr(j,i);
				i += sep.length();
				j = i;
			}
			else
				++i;
		}
		if(j < i)
		{
			// copy last
			*outiter = str.substr(j);
		}
		return 0;
	}
	//! 将16进制字符串转换成BYTE数组
	/*
	 \param str 16进制字符串
	 \param obuf 转换后的 BYTE 数组
	 \param buflen BYTE 数组的长度
	 \return 成功返回转换后的 buf 的长度，失败返回　-1
	 */
	static int Str2Hex(const char* str,unsigned char* obuf,size_t buflen)
	{
		char temp[3] = "";
		size_t i;
		if(str == NULL)
			return -1;
		for(i = 0;i < buflen;++i)
		{
			memcpy(temp,str+i*2,2);
			unsigned long t = strtoul(temp,NULL,16);
			if(t == -1)
				return -1;
			obuf[i] = (unsigned char)t;
		}
		return (int)i;
	}
	//! 将 BYTE 数组转换成 16 进制字符串表示形式
	/*
	 \param hexbuf BYTE 数组
	 \param buflen BYTE数组长度
	 \param str 输出的16进制字符串
	 \return 返回转换后的字段串长度
	 */
	static int Hex2Str(const unsigned char *hexbuf,size_t buflen,char* str)
	{
		int j = 0;
		for(size_t i = 0;i < buflen; ++i)
		{
			j+= sprintf(str+j,"%02x",hexbuf[i]);
		}
		return j;
	}

	static void Str2BCD(const char *str_buf,size_t len,unsigned char *bcd_str)
	{
		for (size_t i = 0;i < len;i+=2)
		{
			bcd_str[i/2] = (((str_buf[i]-'0') << 4) & 0xF0) | ((str_buf[i+1]-'0') & 0x0F);
		}
	}

	static void BCD2Str(const unsigned char *bcd_str,size_t len,char *str_buf)
	{
		for (size_t i = 0;i < len;++i)
		{
			str_buf[i*2] = ((bcd_str[i] >> 4) & 0x0F)+'0';
			str_buf[i*2+1] = (bcd_str[i] & 0x0F)+'0';
		}
	}

	static void revert_str(const char *str,size_t len,char *out_str)
	{
		for (size_t i = 0;i < len/2; ++i)
		{
			out_str[i] = str[len - i - 1];
			out_str[len - i - 1] = str[i];
		}
	}
private:
};
XUTIL_NAMESPACE_END

#endif /*XSTRING_H_*/
