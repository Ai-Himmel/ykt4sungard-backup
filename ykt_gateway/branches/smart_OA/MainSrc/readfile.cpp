/*=================================================================
Copyright (C) 2002 - 2005 �㶫�����ǻ۵�����Ϣ��ҵ���޹�˾
File name:    readfile.cpp
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
================================================================*/

#include "stdafx.h"
#include "readfile.h"
#include "data.h"

FileBase::FileBase()
{

}

FileBase::~FileBase()
{

}

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
FILE* FileBase::OpenFile(char* filename,char* open_mode)
{
	FILE* p=NULL;	  

	p=fopen(filename,open_mode);
	if( p== NULL )
	{
		return p;
	}
	else
	{
		return p;
	}
}


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
void FileBase::CloseFile(FILE* p)
{	
	if( p != NULL )
	{
		fclose(p);
		p=NULL;
	}
}


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
int FileBase::FileEOF(FILE* p)
{
	if( feof(p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*=================================================================
 * Function ID :  ReadFile
 * Input       :  FILE* p, int data_len
 * Output      :  char* buf
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  SUCCESS/FAIL
 * Description :  
 * Notice	   :  ���ļ��ж���ָ�������ݳ���
 *					
 *=================================================================*/
int FileBase::ReadFile( FILE* p, int data_len, char* buf )
{
	char	buffer[1024];
	int		ret;
	
	ret = 0;
	memset(buffer, 0x00, sizeof buffer );
	ret = fread(buffer,1,data_len,p);
	if( ret != data_len )
	{
		return FAIL;
	}
	memcpy(buf, buffer, data_len);
	return SUCCESS;
}

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
int FileBase::ReadFileLine( FILE* p, char* buf )
{
	char	buffer[1024],ch=0;
	int		ret,i;

	ret = 0;
	i   = 0;
	memset(buffer, 0x00, sizeof buffer );

	while( !feof(p) )
	{	
		ch=0x00;
		ret = fread(&ch,1,1,p);
		if( !ret && feof(p) )
		{
			strcpy(buf,buffer);
			return SUCCESS;
		}		
		else if( ret != 1 )
		{
			return FAIL;
		}
		if( ch == '\n' )
		{
			strcpy(buf,buffer);
			break;
		}
		buffer[i++]=ch;	
	}
	return SUCCESS;
}

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
int FileBase::WriteFile( FILE* p, char* buf, int buf_len )
{	
	int	ret=0;

	ret = fwrite(buf,1,buf_len,p);
	if( ret != buf_len )
	{
		return FAIL;
	}
	return SUCCESS;
}

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
int FileBase::WriteFileLine( FILE* p, char* buf, int buf_len )
{	
	int		ret=0;	
	char	*ptr=NULL;

	if( buf_len <=0 )
	{
		return SUCCESS;
	}

	ptr = (char*)malloc(buf_len+1);
	if( ptr == NULL )
	{
		return FAIL;
	}

	memset(ptr, 0x00, buf_len+1 );
	memcpy(ptr,buf,buf_len);
	ptr[buf_len]='\n';

	ret = fwrite(ptr,1,buf_len+1,p);	
	if( ret != buf_len+1 )
	{
		free(ptr);
		return FAIL;
	}
	free(ptr);
	return SUCCESS;
}

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
int FileBase::AddLineToFile( char* filename, char* buf, int buf_len )
{
	FILE* p;
	if( (p = OpenFile(filename,"a+")) == NULL )
	{		
		return FAIL;
	}
	if( WriteFileLine(p,buf,buf_len) != SUCCESS )
	{
		CloseFile(p);
		return FAIL;
	}
	CloseFile(p);
	return SUCCESS;
}

/*=================================================================
 * Function ID :  GetProfileString
 * Input       :  char* fileanme, char* module1, char* module2 
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
 *				module2="MODULE2"
 *				��buf�з��ص�ֵӦΪtest
 *=================================================================*/
int FileBase::GetProfileStr( char* filename, char* module1, char* module2 ,char* buf)
{
	char	buffer[1024],ch;
	char	data[1024];
	int		ret,i,flag=0;
	CData	tool;	
	FILE	*p=NULL;

	i   = 0;
	ch  = 0;
	ret = 0;
	memset( data,   0x00, sizeof data   );
	
	if( !(p=OpenFile(filename,"r")) )	
	{
		return FAIL;
	}
	//�ҵ��ļ���ָ����module1������ʼ��
	while( !FileEOF(p) )
	{
		memset(buffer, 0x00, sizeof buffer );
		//���ļ��ɹ�,���Ѿ����ļ�ĩβ,��ʱҲ��Ҫ�˳���д�ļ�
		if( (ReadFileLine( p,buffer) != SUCCESS) )
		{
			CloseFile(p);
			return FAIL;
		}		
		tool.trim(buffer);
		if( buffer[0] != '[' )
		{
			continue;
		}
		buffer[0]=' ';
		tool.trim(buffer);
		if( !memcmp(buffer,module1,strlen(module1) ) )
		{
			break;
		}
	}
	//��ʼ��module2�ұߵ�ֵ
	while( !FileEOF(p))
	{
		memset(buffer, 0x00, sizeof buffer );
		if( (ReadFileLine( p,buffer) != SUCCESS) )
		{
			CloseFile(p);
			return FAIL;
		}
		tool.trim(buffer);
		//��ֹ��ѡ���е�[]��,�ҵ�������[]��,�������������
		if( buffer[0] == '[') 
		{
			CloseFile(p);
			return FAIL;
		}
		else if( buffer[0]==0x10)
		{
			CloseFile(p);
			return FAIL;
		}
		if( !memcmp(buffer,module2,strlen(module2)))
		{
			flag=1;
			break;
		}
	}
	if( FileEOF(p) && !flag )
	{
		CloseFile(p);
		buf[0]=0x00;
		return FAIL;
	}
	CloseFile(p);
	//ȥ���ȺźͿո�
	memcpy(data,buffer+strlen(module2),strlen(buffer)-strlen(module2) );
	tool.trim(data);
	data[0]=' ';
	tool.trim(data);		
	memcpy(buf,data,strlen(data));	
	return SUCCESS;
}

