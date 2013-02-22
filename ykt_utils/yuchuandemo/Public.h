#pragma once

class CPublic
{
public:
	CPublic(void);
	~CPublic(void);
public:
	static CString strTemp;
	static BCD2Str(const unsigned char *bcd_str,size_t len,char *str_buf);
    static Str2BCD(const char *str_buf,size_t len,unsigned char *bcd_str);
    static int  Hex2Str(const unsigned char *hexbuf,size_t buflen,char* str);
	static int  Hex2Strx(const unsigned char *hexbuf,size_t buflen,char* str);
    static int  Str2Hex(const char* str,unsigned char* obuf,size_t buflen);
    static charTowchar(const char *chr, wchar_t *wchar, int size) ;
	static  wcharTochar(const wchar_t *wchar, char *chr, int length); 

};
