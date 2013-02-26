/*=================================================================
Copyright (C) 2002 - 2005 广东三九智慧电子信息产业有限公司
File name:    readfile.h
Author:       DengJun
Version:      1.0
Date:         2005.4
Description:  
Others:       
Revision history:
	1:
	Date:
	Author:
	Modifiacation:	
=================================================================*/
#ifndef __READFILE__H_
#define __READFILE__H_

//*---------------------------------------------------------------------------
//*名称: FileBase
//*功能: 文件读写操作通讯类
//*---------------------------------------------------------------------------
class FileBase
{
public:
	FileBase();
	~FileBase();
	
	/*=================================================================
	 * Function ID :  OpenFile
	 * Input       :  char* filename,char* open_mode
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  FILE*
	 * Description :  
	 * Notice	   :  打开一个文件
	 *					
	 *=================================================================*/
	FILE* OpenFile(char* filename,char* open_mode);

	/*=================================================================
	 * Function ID :  CloseFile
	 * Input       :  void
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  void
	 * Description :  
	 * Notice	   :  关闭文件
	 *					
	 *=================================================================*/
	void CloseFile(FILE* p);

	/*=================================================================
	 * Function ID :  FileEOF
	 * Input       :  FILE* p
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  到文件尾/1 未到文件尾/0
	 * Description :  
	 * Notice	   :  判断是否到文件尾
	 *					
	 *=================================================================*/
	int FileEOF(FILE* p);

	/*=================================================================
	 * Function ID :  ReadFile
	 * Input       :  FILE* p, int data_len
	 * Output      :  char* buf
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  到文件中读出指定长度的数据
	 *					
	 *=================================================================*/
	int ReadFile(FILE* p, size_t data_len,char* buf );

	/*=================================================================
	 * Function ID :  ReadFileLine
	 * Input       :  FILE* p
	 * Output      :  char* buf
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  读文件中一行数据
	 *					
	 *=================================================================*/
	int ReadFileLine(FILE* p, char* buf );


	/*=================================================================
	 * Function ID :  WriteFile
	 * Input       : char* buf, int buf_len
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  向文件写数据
	 *					
	 *=================================================================*/
	int WriteFile( FILE* p, char* buf, size_t buf_len );

	/*=================================================================
	 * Function ID :  WriteFileLine
	 * Input       : char* buf, int buf_len
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  向文件写一行数据
	 *					
	 *=================================================================*/
	int WriteFileLine( FILE* p, char* buf, int buf_len );
	/*=================================================================
	 * Function ID :  AddLineToFile
	 * Input       :  char* filename char* buf, int buf_len
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  向文件末尾增加一行数据
	 *					
	 *=================================================================*/
	int AddLineToFile( char* filename, char* buf, int buf_len );

	/*=================================================================
	 * Function ID :  GetProfileString
	 * Input       :  char* filename, char* module1, char* module2 
	 * Output      :  char* buf
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  SUCCESS/FAIL
	 * Description :  
	 * Notice	   :  读文件指定的某块的某个内容
	 *				某个文件中有如下内容：
	 *				[MODULE1]
	 *				MODULE2=test
	 *				参数：
	 *				module1="MODULE1"
	 *				module2="MODULE1"
	 *				则buf中返回的值应为test
	 *=================================================================*/
	int GetProfileStr( char* filename, char* module1, char* module2 ,char* buf);

};
#endif
