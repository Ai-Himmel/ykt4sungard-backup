#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _TOOL__H_
#define	_TOOL__H_
/*=================================================================
Copyright (C) 2002 - 2004 广东三九智慧电子信息产业有限公司
File name:    tool.h
Author:       DengJun
Version:      1.0
Date:         2005.03.12
Description:  
Others:       
Revision history:	
	Date:
	Author:
	Modifiacation:	
=================================================================*/

typedef	unsigned char    uchar;

class Tool
{
public:
	Tool();
	~Tool();
	/*=================================================================
	 * Function ID :  AscToBcd
	 * Input       :  unsigned char* ascbuf, int ascbuf_len
	 * Output      :  unsigned char* bcdbuf
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  返回转换的字符BCD
	 * Description :  将ASC码转换成BCD码
	 * Notice	   :  
	 *					
	 *=================================================================*/
	uchar* BcdToAsc(uchar* bcdbuf, int bcdbuf_len,uchar* ascbuf );

	/*=================================================================
	 * Function ID :  BcdToAsc
	 * Input       :  unsigned char* bcdbuf, int bcdbuf_len
	 * Output      :  unsigned char* ascbuf
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  返回转换的字符
	 * Description :  将BCD码转换成ASC码
	 * Notice	   :  
	 *					
	 *=================================================================*/
	uchar* AscToBcd(uchar* ascbuf, int ascbuf_len, uchar* bcdbuf);


	/*=================================================================
	 * Function ID :  IntToHex
	 * Input       :  int data
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  返回转换成的16进制数
	 * Description :  将一个整数转换成16进制形式
	 * Notice	   :  
	 *					
	 *=================================================================*/
	uchar* IntToHex(unsigned int data);

	/*=================================================================
	 * Function ID :  HexToInt
	 * Input       :  int data
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  返回转换成的10进制数
	 * Description :  将一个16进制数换成整数形式
	 * Notice	   :  
	 *					
	 *=================================================================*/
	unsigned int   HexToInt(uchar* HexData, int len);

	/*=================================================================
	 * Function ID :  l_trim
	 * Input       :  char* str
	 * Output      :  char* str
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  str
	 * Description :  
	 * Notice	   :  去掉字符串左边的空格
	 *					
	 *=================================================================*/
	char*  rtrim(char* str);

	/*=================================================================
	 * Function ID :  rtrim
	 * Input       :  char* str
	 * Output      :  char* str
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  str
	 * Description :  
	 * Notice	   :  去掉字符串右边的空格
	 *					
	 *=================================================================*/
	char*  ltrim(char* str);

	/*=================================================================
	 * Function ID :  trim
	 * Input       :  char* str
	 * Output      :  char* str
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  str
	 * Description :  
	 * Notice	   :  去掉字符串左右两边的空格
	 *					
	 *=================================================================*/
	char*  trim(char* str);

	/*=================================================================
	 * Function ID :  HeadAddStr
	 * Input       :  char* str,int num, char type
	 * Output      :  char* str
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  str
	 * Description :  
	 * Notice	   :  在字符串前面增加num个type字符
	 *					
	 *=================================================================*/
	char*  HeadAddStr(char* str, int num, char type);

	/*=================================================================
	 * Function ID :  GetSysTime
	 * Input       :  void
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  返回本机的时间(格式:YYYYMMDDHHMMSS)
	 * Description :  
	 * Notice	   :  取本机时间
	 *					
	 *=================================================================*/
	 uchar*  GetSysTime();	 
	/*=================================================================
	 * Function ID :  CheckStrHex
	 * Input       :  char* str
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  str
	 * Description :  检查输入的字符串是否为HEX字符
	 * Notice	   :  0~9和A(a)~F(f)
	 *					
	 *=================================================================*/
	bool CheckStrHex(char* str );
	void AddLineToFile(char *cData, int nDataLen);

};
#endif   //_TOOL__H_
