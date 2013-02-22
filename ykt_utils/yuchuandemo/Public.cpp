#include "StdAfx.h"
#include ".\public.h"


CString CPublic::strTemp="";

CPublic::CPublic(void)
{
}

CPublic::~CPublic(void)
{
}
CPublic:: Str2BCD(const char *str_buf,size_t len,unsigned char *bcd_str)
	{
		for (size_t i = 0;i < len;i+=2)
		{
			bcd_str[i/2] = (((str_buf[i]-'0') << 4) & 0xF0) | ((str_buf[i+1]-'0') & 0x0F);
		}
	}

CPublic:: BCD2Str(const unsigned char *bcd_str,size_t len,char *str_buf)
	{
		for (size_t i = 0;i < len;++i)
		{
			str_buf[i*2] = ((bcd_str[i] >> 4) & 0x0F)+'0';
			str_buf[i*2+1] = (bcd_str[i] & 0x0F)+'0';
		}
	}

CPublic::  Str2Hex(const char* str,unsigned char* obuf,size_t buflen)
	{
		char temp[3] = "";
		size_t i;
		if(str == NULL)
			return -1;
		for(i = 0;i < buflen;++i)
		{
			memcpy(temp,str+i*2,2);
			unsigned long t = strtoul(temp,NULL,10);
			if(t == -1)
				return -1;
			obuf[i] = (unsigned char)t;
		}
		return (int)i;
	}


CPublic::  Hex2Str(const unsigned char *hexbuf,size_t buflen,char* str)
	{
		int j = 0;
		for(size_t i = 0;i < buflen; ++i)
		{
			j+= sprintf(str+j,"%02d",hexbuf[i]);
		}
		return j;
	}

CPublic::  Hex2Strx(const unsigned char *hexbuf,size_t buflen,char* str)
	{
		int j = 0;
		for(size_t i = 0;i < buflen; ++i)
		{
			j+= sprintf(str+j,"%02x",hexbuf[i]);
		}
		return j;
	}
CPublic:: charTowchar(const char *chr, wchar_t *wchar, int size)   
{      
    MultiByteToWideChar( CP_ACP, 0, chr,   
        strlen(chr)+1, wchar, size/sizeof(wchar[0]) );   
}   
  
//function: wcharTochar   
//purpose:WCHAR ¡¢wchar_t¡¢LPWSTR to char   
CPublic:: wcharTochar(const wchar_t *wchar, char *chr, int length)   
{   
    WideCharToMultiByte( CP_ACP, 0, wchar, -1,   
        chr, length, NULL, NULL );   
}
