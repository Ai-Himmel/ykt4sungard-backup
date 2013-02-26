/****************************************************************************
 *  Convert - demonstrate convertion functions using iconv
 *  File:
 *    Convert.c
 *  Description:
 *    demonstrate convertion functions using iconv
 *    you can use code_convert() to make many new conversion functions like Utf8ToGb2312()...
 *  Author:
 *    XCyber   email:XCyber@sohu.com
 *  Date:
 *    Sept 11, 2008
 *  Other:
 *    visit http://www.gnu.org/software/libiconv/ for more help of iconv
 ***************************************************************************/

#include "stdafx.h"
#include <windows.h>
#include "iconv.h"
#include <stdio.h>
#include "utf8.h"
#include <string>


/*
 *  Description:
 *    convert one type of encoding string to another type of encoding string using iconv
 *  Parameters:
 *    form_encoding:   type of source encoding
 *    to_encoding:     type of target encoding
 *    from_str:        encoding string of source type
 *    from_str_len:    length of encoding string of source type
 *    to_str[out]:     encoding string of target type, ending of string will be set to double zero "\00\00"
 *    to_str_len[out]: length of encoding string of target type
 *  Return:
 *    returns the number of characters converted in a non-reversible way during this call; reversible conversions are not counted. 
 *    In case of error, return -1
 *  WARNING:
 *    don't forget to call free() to release memory allocated for "to_str" pointer
 */

size_t code_convert(const char *from_encoding, const char *to_encoding,const char *from_str, const size_t from_str_len,char **to_str, size_t *to_str_len)
{
	iconv_t icv;
	int     argument = 1;
	size_t  ret      = 0;
	size_t  n        = 1;

	const char *from = NULL;
	char *to         = NULL;
	char *p          = NULL;
	
	size_t from_len = 0;
	size_t to_len  = 0;

	 if((!from_encoding) || (!to_encoding) || (!from_str) || (from_str_len == 0)||(!to_str) || (!to_str_len))
		 return -1;

	icv = iconv_open(to_encoding,from_encoding);
	if(icv == 0)
		return -1;

	//enable "illegal sequence discard and continue" feature, so that if met illeagal sequence, 
	//conversion will continue instead of being terminated
	if(iconvctl (icv ,ICONV_SET_DISCARD_ILSEQ,&argument) != 0)
		return -1;

	do
	{
		from = from_str;
		from_len = from_str_len;
     //   if (strcmp(from_encoding,"UTF-8")==0)
	//	{
	//	to_len = from_len * n*2/3;
	//	}
	//	else
		{
		to_len = from_len * n*3/2;
		}
		*to_str_len = to_len;
		to = (char*)malloc(to_len);
		if(!to)
		{
			iconv_close(icv);
			return -1;
		}
		*to_str = to;
		ret = iconv(icv,&from,&from_len,&to,&to_len);
		if(ret == -1)
		{
			// not enougt room of output buffer, we should reallocate more room for output buffer
			// just simply enlarge size of output buffer to x2 (x3 x4 and so on) size of input buffer
			if(errno == E2BIG)
			{
				n++;
				free(*to_str);
				*to_str = NULL;
			}
			else
			{
				//something wrong, we should terminate conversation
				if(to)
					free(to);
				iconv_close(icv);
				return -1;
			}
		}
	}while(ret == -1);

	iconv_close(icv);

	//size of output string
	*to_str_len -= to_len;

	//set the ending characters of output string to double zero "\00\00"
	p = *to_str;
	*to_str = (char*)malloc(*to_str_len + 2);
	memcpy(*to_str,p,*to_str_len);
	*(*to_str + *to_str_len) = 0;
	*(*to_str + *to_str_len + 1) = 0;
	free(p);

	return ret;
}


/*
 *  Description:
 *    convert ucs-2le to gb2312
 *  Parameters:
 *    from_str:        ucs-2le encoding string
 *    from_str_len:    length of ucs-2le encoding string
 *    to_str[out]:     gb2312 encoding string
 *    to_str_len[out]: length of gb2312 encoding string
 *  Return:
 *    returns the number of characters converted in a non-reversible way during this call; reversible conversions are not counted. 
 *    In case of error, return -1
 *  WARNING:
 *    don't forget to call free() to release memory allocated for "to_str" pointer
 */
size_t Ucs2leToGb2312(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len)
{
	return code_convert("UCS-2LE","GB2312",from_str,from_str_len,to_str,to_str_len);
}


/*
 *  Description:
 *    convert gb2312 to ucs-2le
 *  Parameters:
 *    from_str:        gb2312 encoding string
 *    from_str_len:    length of ascii encoding string
 *    to_str[out]:     ucs-2le encoding string
 *    to_str_len[out]: length of ucs-2le encoding string
 *  Return:
 *    returns the number of characters converted in a non-reversible way during this call; reversible conversions are not counted. 
 *    In case of error, return -1
 *  WARNING:
 *    don't forget to call free() to release memory allocated for "to_str" pointer
 */
size_t Gb2312ToUcs2le(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len)
{
	return code_convert("GB2312","UCS-2LE",from_str,from_str_len,to_str,to_str_len);
}

/*
 *  Description:
 *    convert utf-8 to gb2312
 *  Parameters:
 *    from_str:        utf-8 encoding string
 *    from_str_len:    length of utf-8 encoding string
 *    to_str[out]:     gb2312 encoding string
 *    to_str_len[out]: length of gb2312 encoding string
 *  Return:
 *    returns the number of characters converted in a non-reversible way during this call; reversible conversions are not counted. 
 *    In case of error, return -1
 *  WARNING:
 *    don't forget to call free() to release memory allocated for "to_str" pointer
 */
size_t Utf8ToGb2312(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len)
{
	//return code_convert("UTF-8","GB2312",from_str,from_str_len,to_str,to_str_len);
	return code_convert("UTF-8","GBK",from_str,from_str_len,to_str,to_str_len);
}


/*
 *  Description:
 *    convert gb2312 to utf8
 *  Parameters:
 *    from_str:        gb2312 encoding string
 *    from_str_len:    length of ascii encoding string
 *    to_str[out]:     utf-8 encoding string
 *    to_str_len[out]: length of utf-8 encoding string
 *  Return:
 *    returns the number of characters converted in a non-reversible way during this call; reversible conversions are not counted. 
 *    In case of error, return -1
 *  WARNING:
 *    don't forget to call free() to release memory allocated for "to_str" pointer
 */
size_t Gb2312ToUtf8(const char *from_str, size_t from_str_len, char **to_str, size_t *to_str_len)
{
	return code_convert("GBK","UTF-8",from_str,from_str_len,to_str,to_str_len);
	//return code_convert("GB2312","UTF-8",from_str,from_str_len,to_str,to_str_len);
}


