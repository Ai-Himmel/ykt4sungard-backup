/*=================================================================
Copyright (C) 2002 - 2005 �㶫�����ǻ۵�����Ϣ��ҵ���޹�˾
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
//*����: FileBase
//*����: �ļ���д����ͨѶ��
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
	 * Notice	   :  ��һ���ļ�
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
	 * Notice	   :  �ر��ļ�
	 *					
	 *=================================================================*/
	void CloseFile(FILE* p);

	/*=================================================================
	 * Function ID :  FileEOF
	 * Input       :  FILE* p
	 * Output      :  void
	 * Author      :  DengJun
	 * Date        :  Apr   2005
	 * Return	   :  ���ļ�β/1 δ���ļ�β/0
	 * Description :  
	 * Notice	   :  �ж��Ƿ��ļ�β
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
	 * Notice	   :  ���ļ��ж���ָ�����ȵ�����
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
	 * Notice	   :  ���ļ���һ������
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
	 * Notice	   :  ���ļ�д����
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
	 * Notice	   :  ���ļ�дһ������
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
	 * Notice	   :  ���ļ�ĩβ����һ������
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
	 * Notice	   :  ���ļ�ָ����ĳ���ĳ������
	 *				ĳ���ļ������������ݣ�
	 *				[MODULE1]
	 *				MODULE2=test
	 *				������
	 *				module1="MODULE1"
	 *				module2="MODULE1"
	 *				��buf�з��ص�ֵӦΪtest
	 *=================================================================*/
	int GetProfileStr( char* filename, char* module1, char* module2 ,char* buf);

};
#endif
