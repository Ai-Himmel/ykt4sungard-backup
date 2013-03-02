#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _TOOL__H_
#define	_TOOL__H_
/*=================================================================
Copyright (C) 2002 - 2004 �㶫�����ǻ۵�����Ϣ��ҵ���޹�˾
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
	 * Return	   :  ����ת�����ַ�BCD
	 * Description :  ��ASC��ת����BCD��
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
	 * Return	   :  ����ת�����ַ�
	 * Description :  ��BCD��ת����ASC��
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
	 * Return	   :  ����ת���ɵ�16������
	 * Description :  ��һ������ת����16������ʽ
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
	 * Return	   :  ����ת���ɵ�10������
	 * Description :  ��һ��16����������������ʽ
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
	 * Notice	   :  ȥ���ַ�����ߵĿո�
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
	 * Notice	   :  ȥ���ַ����ұߵĿո�
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
	 * Notice	   :  ȥ���ַ����������ߵĿո�
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
	 * Notice	   :  ���ַ���ǰ������num��type�ַ�
	 *					
	 *=================================================================*/
	char*  HeadAddStr(char* str, int num, char type);

	/*=================================================================
	 * Function ID :  GetSysTime
	 * Input       :  void
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Dec  12  2004
	 * Return	   :  ���ر�����ʱ��(��ʽ:YYYYMMDDHHMMSS)
	 * Description :  
	 * Notice	   :  ȡ����ʱ��
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
	 * Description :  ���������ַ����Ƿ�ΪHEX�ַ�
	 * Notice	   :  0~9��A(a)~F(f)
	 *					
	 *=================================================================*/
	bool CheckStrHex(char* str );
	void AddLineToFile(char *cData, int nDataLen);

};
#endif   //_TOOL__H_
