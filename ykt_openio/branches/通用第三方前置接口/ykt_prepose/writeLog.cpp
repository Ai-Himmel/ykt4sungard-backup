/*=================================================================
Copyright (C) 2002 - 2005 广东三九智慧电子信息产业有限公司
File name:    readfile.cpp
Author:       DengJun
Version:      1.0
Date:         2005.5
Description:  
Others:       
Revision history:
	1:
	Date:
	Author:
	Modifiacation:	
================================================================*/

#include "stdafx.h"
#include "writelog.h"
#include "readfile.h"
#include "data.h"
CMyLog::CMyLog()
{
}

CMyLog::~CMyLog()
{

}

/*=================================================================
 * Function ID :  CheckIsChangeYear
 * Input       :  char* cpath
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  检查是否已经是新的一年开始
 *			   :  cpath-->路径
 *=================================================================*/
void CMyLog::CheckIsChangeYear(char* cpath)
{
	char  oldPath[256],cyear[16];
	char  NewPath[256];
	int   len=0;
	CData mData;

	memset(cyear,  0x00,sizeof cyear);
	memset(oldPath,0x00,sizeof oldPath);
	memset(NewPath,0x00,sizeof NewPath);
	
	memcpy(cyear,mData.GetSysTime(),6);
	strcpy(oldPath,cpath);
	len=strlen(cpath);
	if( !len ) return ;
	while( len--)
	{
		if( cpath[len]=='\\')
		{			
			if( memcmp(cpath+len+6,cyear,6) )
			{
				memcpy(NewPath,cpath,len+6);
				strcat(NewPath,cyear);
				CreateDirectory(NewPath,NULL);
				memcpy(cpath+len+4,cyear,6);				
			}
			break;
		}
	}
}

/*=================================================================
 * Function ID :  WriteDeviceLog
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  写设备的日志
 *			   :  cpath-->路径 ucpID-->设备ID号 str-->日志内容
 *=================================================================*/
void CMyLog::WriteDeviceLog(char* cpath, char* ucpID,char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	

	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,"Log");		
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}		
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcat(lpBuffer,(char*)m_Data.GetSysTime());
	strcat(lpBuffer," ");
	memset(str,0x00,sizeof str);	
	strcat(lpBuffer,(char*)m_Data.BcdToAsc((BYTE*)ucpID,4,str));
	strcat(lpBuffer," ");
	strcat(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}

/*=================================================================
 * Function ID :  WriteSysLog
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  写设备的日志
 *			   :  cpath-->路径 ucpID-->设备ID号 str-->日志内容
 *=================================================================*/
void CMyLog::WriteSysLog(char* cpath, char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	
	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,"LogSys");		
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcat(lpBuffer,(char*)m_Data.GetSysTime());
	strcat(lpBuffer," ");	
	strcat(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}
void CMyLog::Writedata(char* cpath,char*filename, char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	
	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,filename);
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcat(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}

void CMyLog::readdata(char* cpath,char*filename, char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	FILE* p;
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		;
	m_Data.trim(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,filename);		
	strcat(pszFileName,".txt");		
	if( (p = mfile.OpenFile(pszFileName,"a+")) == NULL )
	{		
		return;
	}
	mfile.ReadFileLine(p,msg);
	mfile.CloseFile(p);
	return ;
}


void CMyLog::deldata(char* cpath,char*filename)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	FILE* p;
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		;
	m_Data.trim(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,filename);		
	strcat(pszFileName,".txt");
	if( !m_Data.FileIsExist(pszFileName) )
	{
		return;
	}
     remove( pszFileName );
	return ;
}
/*=================================================================
 * Function ID :  WriteDeviceLog
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  写设备的费率日志
 *			   :  cpath-->路径 ucpID-->设备ID号 str-->日志内容
 *=================================================================*/
void CMyLog::WriteDeviceRateLog(char* cpath, char* ucpID,char* msg,char *cfilename)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	

	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");
	}			
	strcat(pszFileName,cfilename);
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}		
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcat(lpBuffer,(char*)m_Data.GetSysTime());
	strcat(lpBuffer," ");
	memset(str,0x00,sizeof str);	
	strcat(lpBuffer,ucpID);
	strcat(lpBuffer," ");
	strcat(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}

/*=================================================================
 * Function ID :  WriteDeviceData
 * Input       :  char* cpath, char* msg
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2006
 * Return	   :  void
 * Description :  
 * Notice	   :  写设备的日志
 *			   :  cpath-->路径 ucpID-->设备ID号 msg-->数据内容
 *=================================================================*/
bool CMyLog::WriteDeviceData(char* cpath, char* ucpID,char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];
	char	  lpBuffer[1024];
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);	
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");
	}
	strcat(pszFileName,"Data");		
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,"_");
	strcat(pszFileName,(char*)m_Data.BcdToAsc((BYTE*)ucpID,4,str));
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}	
	
	memset(lpBuffer,0x00,sizeof lpBuffer);

	strcat(lpBuffer,(char*)m_Data.GetSysTime());
	strcat(lpBuffer,",");
	strcat(lpBuffer,msg);
	if( mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer)) )
	{
		return false;
	}
	return true;
}


/*=================================================================
 * Function ID :  WriteDeviceLog
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  写插入数据库时不成功的SQL语句
 *			   :  cpath-->路径 ucpID-->设备ID号 str-->日志内容
 *=================================================================*/
void CMyLog::WriteDeviceSQL(char* cpath, char* ucpID,char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	

	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,"Sql");		
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}		
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcpy(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}

/*=================================================================
 * Function ID :  WriteDeviceLog
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  写插入数据库时不成功的SQL语句
 *			   :  cpath-->路径 ucpID-->设备ID号 str-->日志内容
 *=================================================================*/
void CMyLog::WriteDeviceMaxMoney(char* cpath, char* ucpID,char* msg)
{
	FileBase  mfile;
	CData     m_Data;
	char	  pszFileName[128];	
	char	  lpBuffer[2048];	
	BYTE	  str[30];
	
	memset(str,		   0x00,sizeof str);		
	memset(lpBuffer,   0x00,sizeof lpBuffer);
	memset(pszFileName,0x00,sizeof pszFileName);		
	

	if( !strlen(msg) ) return ;
	m_Data.trim(cpath);
	CheckIsChangeYear(cpath);
	if( strlen(cpath) )
	{
		strcpy(pszFileName,cpath);
		strcat(pszFileName,"\\");		
	}
	strcat(pszFileName,"Sql");		
	memcpy(pszFileName+strlen(pszFileName),(char*)m_Data.GetSysTime(),8);
	strcat(pszFileName,".txt");		
	if( !m_Data.FileIsExist(pszFileName) )
	{
		CreateDirectory(cpath,NULL);
	}		
	memset(lpBuffer,0x00,sizeof lpBuffer);
	strcpy(lpBuffer,msg);
	mfile.AddLineToFile(pszFileName,lpBuffer,strlen(lpBuffer));
	return ;
}
/*=================================================================
 * Function ID :  SMT_GetLastInvoiceNo
 * Input       :  char* cpath, char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Apr   2005
 * Return	   :  void
 * Description :  
 * Notice	   :  
 *			   :  
 *=================================================================*/
bool CMyLog::SMT_GetLastInvoiceNo(char* sID, int *nInvoiceNo )
{
	char		sValue[20];
	char		sKeyName[20];
	int			nValue=0;
	CData		cData;
	FileBase	mfile;

	memset(sValue,0,sizeof sValue);
	memset(sKeyName,0,sizeof sKeyName);
	
	cData.BcdToAsc((byte*)sID,4,(byte*)sKeyName);
	EnterCriticalSection(&g_cs);

	
	//g_CriticalSectionLock.Lock();
	//if( g_WriteFileLock ) 
	//{
	//	g_CriticalSectionLock.Unlock();
//		return false;
//	}
//	g_WriteFileLock=true;
	GetPrivateProfileString(sKeyName, "NO", "-1",sValue,sizeof(sValue),g_sCommRec);
	if( atoi(sValue)==-1 )
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"[%s]",sKeyName);
		mfile.AddLineToFile(g_sCommRec,sValue,strlen(sValue));
		memset(sValue,0,sizeof sValue);
		strcpy(sValue,"NO=1");
		mfile.AddLineToFile(g_sCommRec,sValue,strlen(sValue));
		*nInvoiceNo=0;
	}
	else
	{
		*nInvoiceNo=atol(sValue);
		if( *nInvoiceNo>=65535 ) nValue=-1;		
		else					 nValue=*nInvoiceNo;
		sprintf(sValue,"%ld",++nValue);
		WritePrivateProfileString(sKeyName, "NO",sValue,g_sCommRec);		
	}
//	g_WriteFileLock=false;
//	g_CriticalSectionLock.Unlock();
	 LeaveCriticalSection(&g_cs);
	return true;
}
